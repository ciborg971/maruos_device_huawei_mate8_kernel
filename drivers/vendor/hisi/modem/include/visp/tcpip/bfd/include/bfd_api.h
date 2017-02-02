/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_api.h
*
*  Project Code: VISPV1R6
*   Module Name:
*  Date Created: 2008-3-10
*        Author: LY(57500)
*   Description: bfd��visp����ʱ�����ṩ�Ľӿ�����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-------------------------------------------------------------------------------
*  2008-3-10  LY(57500)     Create the first version.
*
*******************************************************************************/

#ifndef _BFD_API_H_
#define _BFD_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ��visp����ʱ����bfd_cbb_api.h���ṩ�Ľӿ��⻹���ⶨ�����û��ӿ�,�ο���������� */
#include "bfd_cbb_api.h"

#define BFD_LICENSE_ON   0x01
#define BFD_LICENSE_OFF  0x00

#define BFD_PROTO_DRAFT4    0     /*�ݰ�4Э���BFD*/
#define BFD_PROTO_STD       1     /*RFCЭ���BFD*/


/* PPIͳ����Ϣ */
typedef struct tagBFD_PPI_COUNT_S
{
    /* BFD4����֪ͨ�ܴ��� */
    ULONG ulBFDUpdateTotal;
    /* BFD4����֪ͨʧ�ܴ��� */
    ULONG ulBFDUpdateFailure;
    /*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01, 2009/4/8 */
    /* BFD6����֪ͨ�ܴ��� */
    ULONG ulBFD6UpdateTotal;
    /* BFD6����֪ͨʧ�ܴ��� */
    ULONG ulBFD6UpdateFailure;
    /* End of Added by wangchengyang-xujun62830-57575, 2009/4/8 */
}BFD_PPI_COUNT_S;

/* BFD�Ự������ */
typedef enum tagBFD_API_ACTION_TYPE_E
{
    BFD_API_SESSION_DELETE = 0 ,         /* ɾ���Ự */
    BFD_API_SESSION_ADD ,                /* �����Ự*/
    BFD_API_ACTION_MAX
}BFD_API_ACTION_TYPE_E;

typedef struct tagBFD_SESSION_ADD_DEL_S {
    ULONG ulAction;
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szIfName[BFD_MAX_INTF_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr;
    ULONG ulPeerAddr;
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulDetectMult;
    ULONG ulMinTxInterval;
    ULONG ulMinRxInterval;
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    ULONG ulBfdProtocol;         /*�Ự����   BFD_PROTO_DRAFT4    0  �ݰ�4Э���BFD
                                             BFD_PROTO_STD       1  RFCЭ���BFD*/
    ULONG ulRemoteDiscr;
    /* Added by fengjing209023 for S-BFD-MultiSession.CFG.001 ��ΪBFD_ON����Ч������Ĭ�ϲ���Ч */
    ULONG ulMultiHopFlag;       /* ������ϸñ�ǣ����ڶ�����Ҳ����3784������Ĭ��4784 */
    /* Added end */
}BFD_SESSION_ADD_DEL_S;

/*Added by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/4/8 */
typedef struct tagBFD6_SESSION_ADD_DEL_S {
    ULONG ulAction;
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szIfName[BFD_MAX_INTF_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr[4];
    ULONG ulPeerAddr[4];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulDetectMult;
    ULONG ulMinTxInterval;
    ULONG ulMinRxInterval;
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */    
    ULONG ulBfdProtocol;
    /* wangjiaqi modify for ipv6 bfd 20131026 begin */     
    ULONG ulRemoteDiscr;/*�Զ�������*/                     
    /* wangjiaqi modify for ipv6 bfd end */
    
    /* Added by fengjing209023 for S-BFD-MultiSession.CFG.001 ��ΪBFD_ON����Ч������Ĭ�ϲ���Ч */
    ULONG ulMultiHopFlag;       /* ������ϸñ�ǣ����ڶ�����Ҳ����3784������Ĭ��4784 */
    /* Added end */
}BFD6_SESSION_ADD_DEL_S;
/* End of Added by wangchengyang-xujun62830-57575, 2009/4/8 */

/* BFD�Ự�û��������ݽṹ */
typedef struct tagBFD_SESSION_ADMIN_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    BOOL_T bShutdown;
    UCHAR ucResv[2];
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
}BFD_SESSION_ADMIN_S;

/* BFD�Ự�������ݽṹ */
typedef struct tagBFD_SESSION_UPDATE_S {
    ULONG ulAction;
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    ULONG ulDetectMult;
    ULONG ulMinTxInterval;
    ULONG ulMinRxInterval;
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
}BFD_SESSION_UPDATE_S;

/* ���ݻỰ���ƻ�ȡ�Ự���� �� ���ݻỰ������ȡ�Ự���� */
typedef struct tagBFD_SESSION_GET_ID_OR_NAME_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    ULONG ulSessionId;
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
}BFD_SESSION_GET_ID_OR_NAME_S;

/* �Ự��Ϣ�����еĲ���stSessPara�е�ֵ�������Ϊ0��ʹ��VISP
��Ĭ��ֵ��Ϊ�Ự�Ĳ�����TOSֵ����ֵ����Ч�Ĳ�����VISP������Ч���жϣ�ֱ�Ӹ�ֵ */
typedef struct tagBFD_SESSION_CREATE_WITH_PARA_S {
    ULONG ulOutIfIndex;             /* �����ỰʱΪ���ӿ�����������ʱֵΪ0��*/
    ULONG ulSrcIP;                  /* ָ���Ự��Դ��ַ��������*/
    ULONG ulDstIP;                  /* ָ���Ự��Ŀ�ĵ�ַ��������*/
    ULONG ulBfdProtocol;            /* �ỰЭ������
                                        0  BFD_PROTO_DRAFT4   �ݰ�4Э���BFD
                                        1  BFD_PROTO_STD      RFCЭ���BFD*/
    ULONG ulVrfIndex;               /* VRF Index��*/
    BFD_SESSION_PARA_S stSessPara;  /* �Ự���� */
    UCHAR ucTos;                    /* BFD�Ự����TOSֵ��ֵ����Ч */ 
    UCHAR ucRes[3];
}BFD_SESSION_CREATE_WITH_PARA_S;

/*BFDʱ��ע�ṳ����غ궨��,add by wuhailan,2008-04-11.*/
#define BFD_TIMETEST_INPUT     0x01   /*BFD����̽��ͨ��ʱ�Ӵ��ע���������*/
#define BFD_TIMETEST_OUTPUT    0x02   /*BFD����̽��ͨ��ʱ�Ӵ��ע�ᷢ������*/
typedef ULONG (*pfFuncBFDTimeTestHook)(MBUF_S* pMbuf);

/* api declare - the below functoins is only for visp user */
/****************************************************************************
*    Func Name: BFD_SetPpiDebugSwitch
*  Description: ����BFD Debug�Ŀ���
*        Input: ulSwitch Debug���أ�0Ϊ�رգ�1Ϊ��
*       Output: 
*       Return: ʧ�� BFD_ERR_INVALID_PARAMETER
*               �ɹ� BFD_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-11   Wangchengyang    Create
*  2008-04-10   wuhailan         ����Ϊ���Կ���
*******************************************************************************/
extern ULONG BFD_SetPpiDebugSwitch(ULONG ulSwitch);
/*******************************************************************************
*    Func Name: BFD_PPI_Count_Get
*  Description: ��ȡPPIͳ�Ƽ���
*        Input: BFD_PPI_COUNT_S *pstCount: ��ȡ��PPIͳ�Ƽ����ṹ
*       Output:
*       Return: ʧ�� BFD_ERR_NULL_POINTER
*               �ɹ� BFD_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-4-8    LY(57500)        Create the first version.
*
*******************************************************************************/
extern ULONG BFD_PPI_Count_Get(BFD_PPI_COUNT_S *pstCount);
/****************************************************************************
*    Func Name: BFD_PPI_Count_Reset
*  Description: ����PPIͳ�Ƽ���
*        Input: VOID
*       Output: 
*       Return: ʧ�� BFD_ERR
*               �ɹ� BFD_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-11  Wangchengyang    Create
*
*******************************************************************************/
extern ULONG BFD_PPI_Count_Reset(VOID);
/*******************************************************************************
*    Func Name: BFD_ComputeBFDPPIUpdateCost
*  Description: ʹ�ܼ���BFD PPI�·�ʱ�ӿ���
*        Input: ULONG ulSetYes:ʹ�ܿ���:1ʹ��,0ȥʹ��
*       Output: ��
*       Return: �ɹ�BFD_OK,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern ULONG BFD_ComputeBFDPPIUpdateCost(ULONG ulSetYes);
/*******************************************************************************
*    Func Name: BFD_ShowBFDPPIUpdateCost
*  Description: ��ʾBFD PPI�·���ʱ��Ϣ
*        Input: ��
*       Output: ��
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern VOID BFD_ShowBFDPPIUpdateCost(VOID);


extern ULONG BFD_HA_SetDbg(ULONG ulDbg);

extern ULONG BFD_HA_GetDbg(ULONG *pulDbg);

/*******************************************************************************
*    Func Name: BFD_Shell_SessionCreate
*  Description: �趨һ��BFD�Ự�Ļ�������������ʼ�����Ự
*               ����Ҫ��������Ч�ԣ�����CBBʵ�ֹ��ܣ�
*        Input: ULONG ulDstIP      ָ���Ự��Ŀ�ĵ�ַ��������
*               ULONG ulSrcIP      ָ���Ự��Դ��ַ��������
*               ULONG ulOutIfIndex   �����ỰʱΪ���ӿ�����������ʱֵΪ0��
*               ULONG *pulSessionID  ȡֵ��ΧΪ[0,512]�������0����VISP�Զ�����ỰID��
*                                    �������ָ����ID�����Ự
*       Output: ULONG *pulSessionID  �Ự�ı�ʶID
*       Return: �ɹ�����      BFD_OK
*               ʧ�ܷ���      BFD_ERR_EXIST_SESSION
*                             BFD_ERR_NULL_POINTER
*                             BFD_ERR_DISABLE
*                             BFD_ERR_INVALID_ADDR;
*                             BFD_ERR_INTF_NOT_EXIST
*                             BFD_ERR_DISMATCH_IP_INDEX
*                             BFD_ERR_SRC_DST_IP_CONFLICT
*                             BFD_ERR_RECR_SESSION
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-01      Wangchengyang    Create
*  2007-5-17  wujie(61195)         Modified for A82D15480����ε�ַ��Ϊ������
*******************************************************************************/
extern ULONG BFD_Shell_SessionCreate (ULONG ulDstIP, ULONG ulSrcIP, ULONG ulOutIfIndex, ULONG* pulSessionID);

/*******************************************************************************
*    Func Name: BFD_Shell_SessionCreateByVrf
* Date Created: 2009-12-2
*       Author: zhangchunyu(62474)
*  Description: �趨һ��BFD�Ự�Ļ�������������ʼ�����Ự
*               ����Ҫ��������Ч�ԣ�����CBBʵ�ֹ��ܣ�
*        Input: ULONG ulDstIP      ָ���Ự��Ŀ�ĵ�ַ��������
*               ULONG ulSrcIP      ָ���Ự��Դ��ַ��������
*               ULONG ulOutIfIndex   �����ỰʱΪ���ӿ�����������ʱֵΪ0��
*               ULONG *pulSessionID  ȡֵ��ΧΪ[0,2000],�����0����VISP�Զ�����ỰID��
*                                    �������ָ����ID�����Ự
*               ULONG ulVrfIndex   VRF Index
*       Output: ULONG *pulSessionID  �Ự�ı�ʶID
*       Return: �ɹ�����      BFD_OK
*               ����������    ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-2    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_Shell_SessionCreateByVrf(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulOutIfIndex,
                                          ULONG *pulSessionID, ULONG ulVrfIndex);
/* End of Added by chenlong, 2010-10-19 */

/*******************************************************************************
*    Func Name: BFD_AddDelSession
* Date Created: 2008-8-4
*       Author: qinyun
*  Description: ����ɾ��һ��BFD�Ự������ʱͬʱ�趨�Ự����
*        Input: pstSession  ����ɾ���ĻỰ��Ϣ
*       Output: 
*       Return: �ɹ�����       BFD_OK       ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4  qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG BFD_AddDelSession(BFD_SESSION_ADD_DEL_S *pstSession);
/*******************************************************************************
*    Func Name: BFD_AdminSession
* Date Created: 2008-7-29
*       Author: qinyun
*  Description: �Ự���û�����Admindown��undo Admindown
*        Input: pstData  ����ṹ��
*       Output: 
*       Return: �ɹ�����       BFD_OK         ʧ�ܷ���       ������
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4  qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG BFD_AdminSession(BFD_SESSION_ADMIN_S *pstData);
/*******************************************************************************
*    Func Name: BFD_UpdateSession
* Date Created: 2008-7-29
*       Author: qinyun
*  Description: �Ự��������
*        Input: pstPara  �Ự����
*       Output: 
*       Return: �ɹ�����       BFD_OK        ʧ�ܷ���       ������
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4  qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG BFD_UpdateSession(BFD_SESSION_UPDATE_S *pstPara);
/*******************************************************************************
*    Func Name: BFD_GetSessionConfigEntry
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: ͨ��WaitList�������ȡ��һ�����������������ָ��
*        Input: ULONG ulEntryWaitList: WaitList���
*       Output: pstConfigInfo:��ȡ��������
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4     qinyun(62011)           Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetSessionConfigEntry(UINTPTR ulEntryWaitList,BFD_SESSION_CONFIG_INFO_S *pstConfigInfo);
/*******************************************************************************
*    Func Name: BFD_GetSessionCountEntry
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: ͨ��WaitList�������ȡ��һ�����������������ָ��
*        Input: ULONG ulEntryWaitList: WaitList���
*       Output: pstCount:��ȡ��������
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4     qinyun(62011)           Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetSessionCountEntry(UINTPTR ulEntryWaitList,BFD_SESSION_COUNT_S *pstCount);
/*******************************************************************************
*    Func Name: BFD_GetSessionInfoEntry
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: ͨ��WaitList�������ȡ��һ�����������������ָ��
*        Input: ULONG ulEntryWaitList: WaitList���
*       Output: pstSessionInfo:��ȡ��������
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4     qinyun(62011)           Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetSessionInfoEntry(UINTPTR ulEntryWaitList,BFD_SESSION_ALL_INFO_S *pstSessionInfo);
/*******************************************************************************
*    Func Name: BFD_GetSessionBriefEntry
* Date Created: 2008-12-8
*       Author: qinyun(62011)
*  Description: ͨ��WaitList�������ȡ��һ�����������������ָ��
*        Input: ULONG ulEntryWaitList: WaitList���
*       Output: pstBriefInfo:��ȡ��������
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-8    qinyun(62011)           Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetSessionBriefEntry(UINTPTR ulEntryWaitList,BFD_SESSION_BRIEF_INFO_S *pstBriefInfo);
/*******************************************************************************
*    Func Name: BFD_OpenSessionTable
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: ��ȡBFD�Ự���WaitList������������������
*        Input: pstFilter:�������ṹ
*       Output: ULONG *pulWaitListHandle: WaitList���
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4     qinyun(62011)           Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_OpenSessionTable(UINTPTR *pulWaitListHandle,BFD_SESSION_FILTER_S *pstFilter);
/*******************************************************************************
*    Func Name: BFD_CloseSessionTable
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: �ر�BFD�Ự���WaitList���
*        Input: ULONG ulWaitListHandle: WaitList���
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4     qinyun(62011)           Creat the first version.
*******************************************************************************/
extern ULONG BFD_CloseSessionTable(UINTPTR ulWaitListHandle);
/*******************************************************************************
*    Func Name: BFD_ClrSessionCount
* Date Created: 2008-8-4
*       Author: qinyun
*  Description: ���ݹ����������BFD�Ự��ͳ����Ϣ
*        Input: ucSpecSessFlag  ������(TRUE-ʹ��ָ���Ự���,FALSE-ȫ�����)
*               ulLocalDiscr  ��������
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4  qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG BFD_ClrSessionCount(UCHAR ucSpecSessFlag,ULONG ulLocalDiscr);
/*******************************************************************************
*    Func Name: BFD_GetSessionIdByName
* Date Created: 2009-01-07
*       Author: qinyun
*  Description: ���ݻỰ���ƻ�ȡ�Ự����
*        Input: pulSessionId: �Ự����
*       Output: pszSessName: �Ự����
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-07   qinyun(62011)    Creat the first version.
*******************************************************************************/
extern ULONG BFD_GetSessionIdByName(UCHAR *pszSessName,ULONG *pulSessionId);
/*******************************************************************************
*    Func Name: BFD_GetSessionIdByName
* Date Created: 2009-01-07
*       Author: qinyun
*  Description: ���ݻỰ������ȡ�Ự����
*        Input: ulSessionId: �Ự����
*               ulLength���û�������ڴ泤��
*       Output: pszSessName: �Ự����
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-07   qinyun(62011)    Creat the first version.
*******************************************************************************/
extern ULONG BFD_GetNameBySessionId(ULONG ulSessionId,UCHAR *pszSessName,ULONG ulLength);

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-12 */
/*******************************************************************************
*    Func Name: BFD_SessionCreateDelByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: ɾ��ָ���Ự
*        Input: BFD_CREATEDEL_BYVRF_S *pstBfdInfo: BFD����ɾ�����ƿ�ָ��
*               ULONG* pulSessionID               : �����Ự��ʱ���ֵΪ����ָ���ĻỰ���߷��صĻỰֵ
*                                                   ɾ����ʱ��Ϊָ����BFD�Ự
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_SESSION_ID
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SessionCreateDelByVrf(BFD_CREATEDEL_BYVRF_S *pstBfdInfo,ULONG* pulSessionID);

/*******************************************************************************
*    Func Name: BFD_DeleteSingleAppFromSessionByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: ɾ��ָ���Ự�ĵ���Ӧ��
*        Input: ulSessionID �Ự��ʶID��ȡֵ��ΧΪ1��255
*               ulAppID     Ӧ��ID      ȡֵ:2��N����,һ��bitλ��ʾһ��Ӧ��
*
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_ID
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_APP_ID;
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-19      Wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_DeleteSingleAppFromSessionByVrf(ULONG ulSessionID, ULONG ulAppID,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SessionParaUpdateByVrf
* Date Created: 2009-02-19
*       Author: Wangchengyang
*  Description: ����һ���Ự�Ĳ�����������MTI��MRI��Detect Mult��Detect Mode��
*               �����������º�Ĳ���Ӧ�õ��Ự�С�
*        Input: ULONG ulSessionID �Ự��ʶID��ȡֵ��ΧΪ1��255
*               BFD_SESSION_PARA_S *pSessPara ���²����ṹָ��
*
*       Output: 
*       Return: �ɹ�����    BFD_OK
*               ʧ�ܷ���    BFD_ERR_SESSION_ID��      �ỰID�Ƿ�
*                           BFD_ERR_TX_INTERVAL;      ����ʱ�����Ƿ�
*                           BFD_ERR_RX_INTERVAL;      ����ʱ�����Ƿ�
*                           BFD_ERR_DETECT_MULT;      ��ⱶ���Ƿ�
*                           BFD_ERR_SESSION_NOT_EXIST ָ���Ự������
*                           BFD_ERR_DETECT_MODE       ���ģʽ�Ƿ�
*                           BFD_ERR_NULL_POINTER      ����ָ��Ϊ�գ�
*                           BFD_ERR_DISABLE           BFDδʹ��
*                           BFD_ERR_HA_IS_SMOOTHING
*                           BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-19      Wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_SessionParaUpdateByVrf(ULONG ulSessionID, BFD_SESSION_PARA_S *pSessPara,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SessionAdministerByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: �Ự���û�����Admindown��undo Admindown
*        Input: ULONG  ulSessionID ָ���Ự�ı�ʶID��ȡֵ��ΧΪ1��255
*               BOOL_T bShutdown   TRUE���رջỰ��FALSE���򿪻Ự
*
*       Output: 
*       Return: �ɹ�����   BFD_OK
*               ʧ�ܷ���   BFD_ERR_SESSION_ID��      �ỰID�Ƿ�
*                          BFD_ERR_SESSION_NOT_EXIST ָ���Ự������
*                          BFD_ERR_INVALID_PARAMETER
*                          BFD_ERR_DISABLE
*                          BFD_ERR_HA_IS_SMOOTHING
*                          BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-19      Wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_SessionAdministerByVrf(ULONG ulSessionID, BOOL_T bShutdown,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_GetSessionInfoByVrf
* Date Created: 2009-02-01
*       Author: Wangchengyang
*  Description: ��ȡָ���Ự�ĵ�ǰ��Ϣ
*        Input: ULONG  ulSessionID ָ���Ự�ı�ʶID��ȡֵ��ΧΪ1���û�����BFD���
*
*       Output: BFD_SESSION_INFO_S* pSess ���ڴ洢�Ự�����Ļ�������ַָ��
*                                         �������ݶ������������
*       Return: �ɹ�����   BFD_OK
*               ʧ�ܷ���   BFD_ERR_SESSION_ID��      �ỰID�Ƿ�
*                          BFD_ERR_SESSION_NOT_EXIST ָ���Ự������
*                          BFD_ERR_NULL_POINTER
*                          BFD_ERR_DISABLE
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_GetSessionInfoByVrf(ULONG ulSessionID, BFD_SESSION_INFO_S *pSess,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_GetSessionIdByVrf
* Date Created: 2007-02-19
*       Author: Wangchengyang
*  Description: ͨ��ԴĿ��IP�ͳ��ӿ���������ѯBFD �Ựid
*        Input: ulDstIP   Ŀ��IP��������
*               ulSrcIP   ԴIP��������
*               ulIfIndex ���ӿ�����
*               ulVrfIndex VRF����
*
*       Output: 
*       Return: �Ựid,���������ָ���ĻỰ�򷵻�0xFFFFFFFF
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_GetSessionIdByVrf(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulIfIndex,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name:   BFD_DetectDownWithDiagByPrdtByVrf
*    Date Created:2009-02-20
*    Author:      wangchengyang
*    Description: ��Ʒ��NP̽�⵽�ỰDownʱ����Ʋ����֪ͨ�ӿ�,��VRF
*    Input:       ULONG ulSessionID: �ỰID
*                   ULONG ulDiag:�ỰDown��ԭ��(�ο�BFD �����
*                                                  ö�ٱ���BFD_DIAG_E)
*                 ULONG ulVrfIndex VRF
*    Output:      ��
*    Return:      �ɹ�����       BFD_OK
*                 ʧ�ܷ���       BFD_ERR_SESSION_ID
*                                BFD_ERR_SESSION_NOT_EXIST
*    Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-20   wangchengyang    Create for VISP1.7C03,VRF,
*******************************************************************************/
extern ULONG BFD_DetectDownWithDiagByPrdtByVrf(ULONG ulSessionID,ULONG ulDiag,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name:   BFD_DetectDownByPrdtByVrf
*    Date Created:2009-02-20
*    Author:      wangchengyang
*    Description: ��Ʒ��NP̽�⵽�ỰDownʱ����Ʋ����֪ͨ�ӿ�,��VRF
*    Input:       ULONG ulSessionID: �ỰID
*                 ULONG ulVrfIndex VRF
*    Output:      ��
*    Return:      �ɹ�����       BFD_OK
*                 ʧ�ܷ���       BFD_ERR_SESSION_ID
*                                BFD_ERR_SESSION_NOT_EXIST
*    Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-20   wangchengyang    Create for VISP1.7C03,VRF,
*******************************************************************************/
extern ULONG BFD_DetectDownByPrdtByVrf(ULONG ulSessionID,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_BfdNotifyByVrfRegister
* Date Created: 2008-3-8
*       Author: LY(57500)
*  Description: BFD֪ͨע�ắ��
*        Input: BFD_NOTIFY_BYVRF_HOOK_FUNC pBfdNotifyByVrfHookFunc: ���Ӻ���ָ��
*       Output:
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_MEM_ALLOC
*                              BFD_ERR_NOTIFIER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4    qinyun(62011) ��Ϊ����ʽ
*******************************************************************************/
extern ULONG TCPIP_BfdNotifyByVrfRegister(BFD_NOTIFY_BYVRF_HOOK_FUNC pBfdNotifyByVrfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_BfdNotifyByVrfUnRegister
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: BFD֪ͨȥע�ắ��
*        Input: BFD_NOTIFY_BYVRF_HOOK_FUNC pBfdNotifyByVrfHookFunc: ���Ӻ���ָ��
*       Output:
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_MEM_ALLOC
*                              BFD_ERR_NOTIFIER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4    qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG TCPIP_BfdNotifyByVrfUnRegister(BFD_NOTIFY_BYVRF_HOOK_FUNC pBfdNotifyByVrfHookFunc);

/*******************************************************************************
*    Func Name: BFD_ClrSessionCount
* Date Created: 2008-8-4
*       Author: qinyun
*  Description: ���ݹ����������BFD�Ự��ͳ����Ϣ
*        Input: ucSpecSessFlag  ������(TRUE-ʹ��ָ���Ự���,FALSE-ȫ�����)
*               ulLocalDiscr  ��������
*               CHAR *pszVrfName
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4  qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG BFD_ClrSessionCountByVrf(UCHAR ucSpecSessFlag,ULONG ulLocalDiscr,CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: BFD_GetSessionIdByNameByVrf
* Date Created: 2009-01-07
*       Author: qinyun
*  Description: ���ݻỰ���ƻ�ȡ�Ự����
*        Input: BFD_SESSION_GET_ID_OR_NAME_S *pInfo: ���ò���
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-07   qinyun(62011)    Creat the first version.
*******************************************************************************/
extern ULONG BFD_GetSessionIdByNameByVrf(BFD_SESSION_GET_ID_OR_NAME_S *pInfo);

/*******************************************************************************
*    Func Name: BFD_GetNameBySessionIdByVrf
* Date Created: 2009-01-07
*       Author: qinyun
*  Description: ���ݻỰ������ȡ�Ự����
*        Input: BFD_SESSION_GET_ID_OR_NAME_S *pInfo: ���ò���
*       Output: pszSessName: �Ự����
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-07   qinyun(62011)    Creat the first version.
*******************************************************************************/
extern ULONG BFD_GetNameBySessionIdByVrf(BFD_SESSION_GET_ID_OR_NAME_S *pInfo);

/*******************************************************************************
*    Func Name: BFD_GetNextSessionIDByVrf
* Date Created: 2009-02-01
*       Author: Wangchengyang
*  Description: ��ȡָ���Ự����һ���Ự�ı�ʶID���Ự����ʶID�������У�
*        Input: ULONG  ulSessionID ָ���ĻỰID
*                      ���������Ϊ0ʱ�����ص�ǰ���ڵĵ�һ���Ự�ı�ʶIDֵ��
*                      ���������С���û����õ�BFD���ʱ�����ظ�ID֮��ĵ�һ���Ự�ı�ʶIDֵ
*                      ������������ڵ����û����õ�BFD��� ʱֱ�ӷ���0;
*               ulVrfIndex  VRF����
*
*       Output: 
*       Return: �ɹ�����       �Ự��ʶID����0��
*               ʧ�ܷ���       0����ǰ�޻Ự����BFDδʹ�ܣ���������ID���ڵ��� BFD_MAX_SESSION_ID��
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_GetNextSessionIDByVrf(ULONG ulSessionID,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SetDebugSwitchByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: �򿪻�ر�BFD���Կ���
*        Input: ULONG ulSessionID ָ���ỰID�Ϸ���Ϊ1~�û�����BFD���
*                                 ������Ϊ0���ʶ��/�ر����лỰ�ĵ��Կ���
*               ULONG ulDebug  ���õ��Ա��,��(�ر�)����Ӧ��־��λ(����)
*                              BFD_DEBUG_STATE    0x1  BFD״̬��Ǩ����
*                              BFD_DEBUG_INPUT    0x2  ���յ�BFD���ĵ���
*                              BFD_DEBUG_OUTPUT   0x4  ���͵�BFD���ĵ���
*                              ����Ҫ�򿪶�����,���λ��
*               ULONG ulVrfIndex  VRF����
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_INVALID_PARAMETER
*                              BFD_ERR_SESSION_ID
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_SetDebugSwitchByVrf(ULONG ulSessionID, ULONG ulDebug,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_GetDebugSwitchByVrf
* Date Created: 2007-7-31
*       Author: zhangchunyu(62474)
*  Description: ��ȡBFD�ĵ��Կ��أ����ulSessionIDΪ0����ȡȫ��Debug���ء������ȡ
*                                  ָ���ӿڵ��Կ��ء�
*        Input: ULONG ulSessionID: �ỰID(0-�û�����BFD���)
*               ULONG ulVrfIndex              Vrf����
*
*       Output: ULONG *pulDebug: ��ȡ����ָ��
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-7-31    zhangchunyu(62474)     Creat the first version.
*  2009-02-01   wangchengyang          Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_GetDebugSwitchByVrf(ULONG ulSessionID, ULONG *pulDebug,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_DemandQueryByAppByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: ����ָ���Ự�Ĳ�ѯ���еķ���
*        Input: ULONG  ulSessionID ָ���Ự�ı�ʶID��
*                                  ��Чȡֵ��Χ1-�û�����BFD����ұ���Ϊ�Ѵ����ỰID
*               ULONG ulVrfIndex   Vrf����
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_ID
*                              BFD_ERR_SESSION_NOT_UP
*                              BFD_ERR_DETECT_MODE
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_QUE_BUSY
*                              BFD_ERR_WRITEQUE_FAIL
*                              BFD_ERR_HA_IS_SMOOTHING
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_DemandQueryByAppByVrf(ULONG ulSessionID,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SetSingleAppToSessionByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: �趨ĳһ���Ự�ľ���Ӧ��
*        Input: ULONG ulSessionID   �ỰID 1~255
*               ULONG ulAppID       Ӧ��ID 2��N����,һ��bitλ��ʾһ��Ӧ��
*               ULONG ulVrfIndex    Vrf����
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_ID;
*                              BFD_ERR_APP_ID;
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution: �ο����Ự״̬�仯ʱ���ⲿ֪ͨ�����ӿڣ�
*               �Ǳ�Ҫ�ӿڣ����κλỰ��״̬�仯ʱ��
*               ��Ʒ����ġ��Ự״̬�仯ʱ���ⲿ֪ͨ�����ӿڲ���ͳһ����ʱ
*               ����Ʒ��BFDӦ��ģ����٣����������ô˽ӿڣ�
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_SetSingleAppToSessionByVrf(ULONG ulSessionID, ULONG ulAppID,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SetAppsToSessionByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: �趨ĳһ�Ự��Ӧ��ģ��(Ӧ����,��������ЩӦ�ù�ϵ����Ự��״̬�仯)
*        Input: ULONG ulSessionID   �ỰID 1~255
*               ULONG ulAppGroup    �Ự��Ӧ��ģ����ϣ�
*                                   ÿһ��Bit��ʶ�ŸûỰ��һ��Ӧ��ģ�飻
*                                   �����һ������Ϊ׼��
*                                   Ϊ0��ʾȡ������ģ��ԸûỰ��Ӧ�ã�
*                                   ���֧��32���ⲿӦ��ģ�顣
*               ULONG ulVrfIndex    Vrf����
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_ID;
*                              BFD_ERR_APP_ID;
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution: �ο����Ự״̬�仯ʱ���ⲿ֪ͨ�����ӿڣ�
*               �Ǳ�Ҫ�ӿڣ����κλỰ��״̬�仯ʱ��
*               ��Ʒ����ġ��Ự״̬�仯ʱ���ⲿ֪ͨ�����ӿڲ���ͳһ����ʱ
*               ����Ʒ��BFDӦ��ģ����٣����������ô˽ӿڣ�
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_SetAppsToSessionByVrf(ULONG ulSessionID, ULONG ulAppGroup,ULONG ulVrfIndex);


/* End:VISP1.7C03 VRF wangchengyang,2009-02-12 */

/*Added by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/4/8 */
/*******************************************************************************
*    Func Name: BFD6_AddDelSession
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: ����ɾ��һ��IPv6 BFD�Ự������ʱͬʱ�趨�Ự����
*        Input: pstSession  ����ɾ���ĻỰ��Ϣ
*       Output: 
*       Return: �ɹ�����       BFD_OK       ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
extern ULONG BFD6_AddDelSession(BFD6_SESSION_ADD_DEL_S *pstSession);

/*******************************************************************************
*    Func Name: BFD6_GetSessionConfigEntry
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: ͨ��WaitList�������ȡ��һ�����������������ָ��
*        Input: ULONG ulEntryWaitList: WaitList���
*       Output: pstConfigInfo:��ȡ��������
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD6_GetSessionConfigEntry(UINTPTR ulEntryWaitList,BFD6_SESSION_CONFIG_INFO_S *pstConfigInfo);

/*******************************************************************************
*    Func Name: BFD6_GetSessionInfoEntry
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: ͨ��WaitList�������ȡ��һ�����������������ָ��
*        Input: ULONG ulEntryWaitList: WaitList���
*       Output: pstSessionInfo:��ȡ��������
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD6_GetSessionInfoEntry(UINTPTR ulEntryWaitList,BFD6_SESSION_ALL_INFO_S *pstSessionInfo);


/*******************************************************************************
*    Func Name: BFD6_OpenSessionTable
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: ��ȡBFD6�Ự���WaitList������������������
*        Input: pstFilter:�������ṹ
*       Output: ULONG *pulWaitListHandle: WaitList���
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD6_OpenSessionTable(UINTPTR *pulWaitListHandle,BFD6_SESSION_FILTER_S *pstFilter);

/*******************************************************************************
*    Func Name: BFD6_CloseSessionTable
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: �ر�BFD6�Ự���WaitList���
*        Input: ULONG ulWaitListHandle: WaitList���
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
extern ULONG BFD6_CloseSessionTable(UINTPTR ulWaitListHandle);

/*******************************************************************************
*    Func Name: BFD6_GetTotalNumber
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: ��ȡ�ܵ�BFD6�Ự����
*        Input: ULONG *pulBfd6SessionCnt:  �Ự����
*       Output:
*       Return: BFD_OK:�ɹ�;
*               BFD_ERR_NULL_POINTER:ָ�������
*               BFD_ERR_DISABLE:bfdδʹ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
extern ULONG BFD6_GetTotalNumber(ULONG *pulBfd6SessionCnt);

/*******************************************************************************
*    Func Name: TCPIP_Bfd6NotifyRegister
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: BFD6֪ͨע�ắ��
*        Input: BFD6_NOTIFY_BYVRF_HOOK_FUNC pBfd6NotifyHookFunc: ���Ӻ���ָ��
*       Output:
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_MEM_ALLOC
*                              BFD_ERR_NOTIFIER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
extern ULONG TCPIP_Bfd6NotifyRegister(BFD6_NOTIFY_HOOK_FUNC pBfd6NotifyHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_Bfd6NotifyUnRegister
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: BFD6֪ͨȥע�ắ��
*        Input: BFD6_NOTIFY_BYVRF_HOOK_FUNC pBfd6NotifyHookFunc: ���Ӻ���ָ��
*       Output:
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_MEM_ALLOC
*                              BFD_ERR_NOTIFIER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
extern ULONG TCPIP_Bfd6NotifyUnRegister(BFD6_NOTIFY_HOOK_FUNC pBfd6NotifyHookFunc);

/*******************************************************************************
*    Func Name: BFD6_UpdateSession
* Date Created: 2009-4-16
*       Author: wangchengyang-xujun62830-57575
*  Description: BFD6�Ự��������
*        Input: pstPara  �Ự����
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-16  wangchengyang-xujun62830-57575         VISPV1R8C01.
*******************************************************************************/
extern ULONG BFD6_UpdateSession(BFD_SESSION_UPDATE_S *pstPara);

/*******************************************************************************
*    Func Name: BFD6_AdminSession
* Date Created: 2009-4-16
*       Author: wangchengyang-xujun62830-57575
*  Description: BFD6�Ự���û�����Admindown��undo Admindown
*        Input: pstData  ����ṹ��
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-16  wangchengyang-xujun62830-57575         VISPV1R8C01.
*******************************************************************************/
extern ULONG BFD6_AdminSession(BFD_SESSION_ADMIN_S *pstData);

/* End of Added by wangchengyang-xujun62830-57575, 2009/4/8 */

/*******************************************************************************
*    Func Name: TCPIP_GR_BFDRestore
* Date Created: 2008-8-17
*       Author: wujie(61195)
*  Description: BFD GR�ָ�����
*        Input: VOID
*       Output: 
*       Return: BFD_OK �ɹ�
*               BFD_ERR_GR_STATE ��ǰ�����ڱ���״̬
*               BFD_ERR_NO_NP δע��NP���Ӻ���
*               ���� VOS_Ev_Write���صĴ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-17  wujie(61195)         Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GR_BFDRestore(VOID);

/*******************************************************************************
*    Func Name: TCPIP_GR_BFDSmooth
* Date Created: 2008-8-17
*       Author: wujie(61195)
*  Description: BFD GRƽ������
*        Input: VOID
*       Output: 
*       Return: BFD_OK �ɹ�
*               BFD_ERR_GR_STATE ��ǰ��δ���GR�ָ�����
*               ���� VOS_Ev_Write���صĴ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-17  wujie(61195)         Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GR_BFDSmooth(VOID);


/****************************************************************************
*    Func Name: TCPIP_BfdLicenseChgNotify
* Date Created: 2009-01-14
*       Author: zengshaoyang 62531
*  Description: �û�����,֪ͨBFD license���ܴ򿪻��߹ر�
*        Input: ULONG ulLicenseFlag:BFD license���ܴ� or �ر�
*               #define BFD_LICENSE_ON   0x01
*               #define BFD_LICENSE_OFF  0x00
*       Output: 
*       Return: VOS_OK:�ɹ� ��������ʧ��
*      Caution: Ϊ��ֹ����̫æ,ȫ��һ���¼�,������һ��BFD�Ự����һ���¼�
*               �ɿ�������һ���������ڹر���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-14   zengshaoyang         Create
*
*******************************************************************************/
extern ULONG TCPIP_BfdLicenseChgNotify(ULONG ulLicenseFlag);

/****************************************************************************
*    Func Name: TCPIP_BfdGetLicenseStateRegister
* Date Created: 2009-01-14
*       Author: zengshaoyang 62531
*  Description: ע���ȡBFD License���ܿ��صĹ��Ӻ���
*        Input: BFD_GET_LICENSE_STATE_FUNC pfFunc:���Ӻ���
*       Output: 
*       Return: VOS_OK:�ɹ� ��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-14   zengshaoyang         Create
*
*******************************************************************************/
extern ULONG TCPIP_BfdGetLicenseStateRegister(BFD_GET_LICENSE_STATE_FUNC pfFunc);

extern ULONG BFD_SetAutoLocalDiscrGate(ULONG ulGate);

/*******************************************************************************
*    Func Name: BFD_SetNotifyTime
* Date Created: 2010-02-25
*       Author: xujun57575
*  Description:
*        Input: ULONG ulTime:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-02-25   xujun57575              Create
*
*******************************************************************************/
extern ULONG BFD_SetNotifyTime(ULONG ulTime);
/*******************************************************************************
*    Func Name: BFD_SetNotifyTimeFlag
* Date Created: 2010-02-25
*       Author: xujun57575
*  Description:
*        Input: ULONG ulFlag:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-02-25   xujun57575              Create
*
*******************************************************************************/
extern ULONG BFD_SetNotifyTimeFlag( ULONG ulFlag);
/*******************************************************************************
*    Func Name: BFD_SessionResetAll
* Date Created: 2010-02-26
*       Author: xujun57575
*  Description:
*        Input:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-02-26   xujun57575              Create for sgsn Requirement  BC3D02728
*
*******************************************************************************/
extern ULONG BFD_SessionResetAll(VOID);

/*******************************************************************************
*    Func Name: BFD_DownAllSession
* Date Created: 2010-04-13
*       Author: xujun57575
*  Description:
*        Input:
*       Output:
*       Return: ULONG
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   xujun57575              Create
*
*******************************************************************************/
extern ULONG BFD_DownAllSession(VOID);

/*******************************************************************************
*    Func Name: BFD_RegFuncBFDTimeTestHook
* Date Created: 2008-03-15
*       Author: wuhailan
*  Description: BFD����̽��ͨ��ʱ�Ӵ��ע�ṳ��
*        Input: ULONG ulType:ע������,1���շ���,2���ͷ���
*               pfFuncBFDTimeTestHook pfHook:Ҫע��ĺ���ָ��
*       Output: ��
*       Return: BFD_OK�ɹ�,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern ULONG BFD_RegFuncBFDTimeTestHook(ULONG ulType, pfFuncBFDTimeTestHook pfHook);



extern ULONG BFD_Shell_SessionCreateByVrfByRfc(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulOutIfIndex,
                                   ULONG *pulSessionID, ULONG ulVrfIndex, ULONG ulBfdProtocol);
/*******************************************************************************
*    Func Name: BFD_Shell_SessionCreateByParam
* Date Created: 2012-10-11
*       Author: zhongyu206043
*  Description: ����BFD�Ự���������û����õĲ�����Ϣ���ûỰ����
*        Input: ULONG *pulSessionID:ָ���ı��˻ỰID, ȡֵ��ΧΪ[0,512]��
*                   �����0����VISP�Զ�����ỰID���������ָ����ID�����Ự
*               BFD_SESSION_CREATE_WITH_PARA_S *pstSessInfo:
*                   �Ự��Ϣ�����еĲ���stSessPara�е�ֵ�������Ϊ0��ʹ��VISP
*                   ��Ĭ��ֵ��Ϊ�Ự�Ĳ�����TOSֵ����ֵ����Ч�Ĳ�����VISP����
*                   ��Ч���жϣ�ֱ�Ӹ�ֵ
*       Output: pulSessionID���Զ�����ĻỰID
*       Return: 
*               BFD_OK           �ɹ�
*               ����             ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-10-11   zhongyu206043           Create
*
*******************************************************************************/
extern ULONG BFD_Shell_SessionCreateByParam (ULONG *pulSessionID, BFD_SESSION_CREATE_WITH_PARA_S *pstSessInfo);



extern ULONG BFD6_GetNameBySessionIdByVrf(BFD_SESSION_GET_ID_OR_NAME_S *pInfo);



extern ULONG BFD6_GetSessionIdByNameByVrf(BFD_SESSION_GET_ID_OR_NAME_S *pInfo);


ULONG BFD_NSR_SendMsg (ULONG ulMsg, UCHAR *pucData, ULONG ulLength);


ULONG BFD_NSR_PpiDownloadHookRegister(BFD_PPI_HOOK_FUNC pfBfdPpiHook);


ULONG BFD_NSR_SetCheckNsrFinishTimer(ULONG ulTime);


ULONG BFD_NSR_GetCheckNsrFinishTimer(ULONG *pulTime);


ULONG BFD_NSR_GetGlobalInformation(BFD_NSR_GLOBAL_INFO_S *pstBfdNsrGlobalInfo);


ULONG BFD_NSR_OpenSessionStatTable(UINTPTR *pulWaitListHandle,BFD_SESSION_FILTER_S *pstFilter);


ULONG BFD_NSR_GetSessionStateEntry(UINTPTR ulEntryWaitList,BFD_NSR_SESS_INFO_S *pstSessionNsrInfo);


ULONG BFD_NSR_CloseSessionStatTable(UINTPTR ulWaitListHandle);

/* wangjiaqi modify for ipv6 bfd 20131114 begin */
/*******************************************************************************
*    Func Name: BFD6_GetSessionState
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: ��ȡBFD�Ự״̬
*        Input: ULONG ulSessionID:�ỰID
*               ULONG ulVrfIndex: vrf����
*       Output: ULONG *pstState:���صĻỰ״̬
*       Return: �ɹ�BFD_OK,�������ش�����
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi           Create
*
*******************************************************************************/
ULONG BFD6_GetSessionState(ULONG ulSessionID, ULONG ulVrfIndex, ULONG *pstState);

/*******************************************************************************
*    Func Name: BFD6_GetNextSessionID
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: ��ȡָ���Ự����һ���Ự�ı�ʶID���Ự����ʶID�������У�
*        Input: ULONG  ulSessionID ָ���ĻỰID
*                      ���������Ϊ0ʱ�����ص�ǰ���ڵĵ�һ���Ự�ı�ʶIDֵ��
*                      ���������С���û����õ�BFD���ʱ�����ظ�ID֮��ĵ�һ���Ự�ı�ʶIDֵ
*                      ������������ڵ����û����õ�BFD���ʱֱ�ӷ���0;
*       Output: 
*       Return: �ɹ�����       �Ự��ʶID����0��
*               ʧ�ܷ���       0����ǰ�޻Ự����BFDδʹ�ܣ���������ID���ڵ��� BFD_MAX_SESSION_ID��
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_GetNextSessionID(ULONG ulSessionID);

/*******************************************************************************
*    Func Name: BFD6_GetNextSessionIDByVrf
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: ��ȡָ���Ự����һ���Ự�ı�ʶID���Ự����ʶID�������У�
*        Input: ULONG  ulSessionID ָ���ĻỰID
*                      ���������Ϊ0ʱ�����ص�ǰ���ڵĵ�һ���Ự�ı�ʶIDֵ��
*                      ���������С�� g_ulBFDTotalSession ʱ�����ظ�ID֮��ĵ�һ���Ự�ı�ʶIDֵ
*                      ������������ڵ��� g_ulBFDTotalSession ʱֱ�ӷ���0;
*               ulVrfIndex  VRF����
*
*       Output: 
*       Return: �ɹ�����       �Ự��ʶID����0��
*               ʧ�ܷ���       0����ǰ�޻Ự����BFDδʹ�ܣ���������ID���ڵ��� BFD_MAX_SESSION_ID��
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14      wangjiaqi        Create 
*******************************************************************************/
ULONG BFD6_GetNextSessionIDByVrf(ULONG ulSessionID,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD6_GetNameBySessionId
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: ���ݻỰ������ȡ�Ự����
*        Input: ulSessionId: �Ự����
*               ulLength���û�������ڴ泤��
*       Output: pszSessName: �Ự����
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_GetNameBySessionId(ULONG ulSessionId,UCHAR *pszSessName,ULONG ulLength);

/*******************************************************************************
*    Func Name: BFD6_GetSessionInfoByVrf
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: ��ȡָ���Ự�ĵ�ǰ��Ϣ
*        Input: ULONG  ulSessionID ָ���Ự�ı�ʶID��ȡֵ��ΧΪ1���û�����BFD���
*               ulVrfIndex  VRF����
*       Output: BFD_SESSION_INFO_S* pSess ���ڴ洢�Ự�����Ļ�������ַָ��
*                                         �������ݶ������������
*       Return: �ɹ�����   BFD_OK
*               ʧ�ܷ���   BFD_ERR_SESSION_ID��      �ỰID�Ƿ�
*                          BFD_ERR_SESSION_NOT_EXIST ָ���Ự������
*                          BFD_ERR_NULL_POINTER
*                          BFD_ERR_DISABLE
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14      wangjiaqi        Create for BFD VRF6
*******************************************************************************/
ULONG BFD6_GetSessionInfoByVrf(ULONG ulSessionID, BFD6_SESSION_INFO_S *pSess,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD6_GetSessionCountEntry
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: ͨ��WaitList�������ȡ��һ�����������������ָ��
*        Input: ULONG ulEntryWaitList: WaitList���
*       Output: pstCount:��ȡ��������
*       Return: �ɹ����� BFD_OK
*               ʧ�ܷ��� BFD_ERR_GET_ENTRY_END   �ӱ��л�ȡ�������Ϲ�����������ָ��
*                        BFD_ERR_WAITLIST
*                        BFD_ERR_DISABLE
*                        BFD_ERR_HA_IS_SMOOTHING
*                        BFD_ERR_NULL_POINTER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi               Creat the first version.
*******************************************************************************/
ULONG BFD6_GetSessionCountEntry(UINTPTR ulEntryWaitList,BFD_SESSION_COUNT_S *pstCount);

/*******************************************************************************
*    Func Name: BFD6_GetSessionBriefEntry
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: ͨ��WaitList�������ȡ��һ�����������������ָ��
*        Input: ULONG ulEntryWaitList: WaitList���
*       Output: pstBriefInfo:��ȡ��������
*       Return: �ɹ����� BFD_OK
*               ʧ�ܷ��� BFD_ERR_GET_ENTRY_END   �ӱ��л�ȡ�������Ϲ�����������ָ��
*                        BFD_ERR_WAITLIST
*                        BFD_ERR_DISABLE
*                        BFD_ERR_HA_IS_SMOOTHING
*                        BFD_ERR_NULL_POINTER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi               Creat the first version.
*******************************************************************************/
ULONG BFD6_GetSessionBriefEntry(UINTPTR ulEntryWaitList,BFD_SESSION_BRIEF_INFO_S *pstBriefInfo);

/*******************************************************************************
*    Func Name: BFD6_ClrSessionCount
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: ���ݹ����������BFD�Ự��ͳ����Ϣ
*        Input: ucSpecSessFlag  ������(TRUE-ʹ��ָ���Ự���,FALSE-ȫ�����)
*               ulLocalDiscr  ��������
*               CHAR *pszVrfName
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14      wangjiaqi        Creat the first version.
*******************************************************************************/
ULONG BFD6_ClrSessionCountByVrf(UCHAR ucSpecSessFlag,ULONG ulLocalDiscr,CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: BFD6_ShowSessionInfoByVrf
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: ��ʾָ��VRF��BFD6���лỰ��Ϣ
*        Input: CHAR *pszVrfName VRF��
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi        Create
*******************************************************************************/
VOID BFD6_ShowSessionInfoByVrf(CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: BFD6_ShowSessionCountByVrf
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: ��ʾָ��VRF������BFD6���лỰͳ����Ϣ
*        Input: pszVrfName VRF ��
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi        Create
*******************************************************************************/
VOID BFD6_ShowSessionCountByVrf(CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: BFD_GetBfdVersion
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: get BFD ip version
*        Input: ULONG ulVrfIndex
                ULONG ulSessionId
*       Output: ULONG *pulVersion: BFD_OVER_IPV4/BFD_OVER_IPV6
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi               Create    
*
*******************************************************************************/
ULONG BFD_GetBfdSessionVersion(ULONG ulVrfIndex, ULONG ulSessionId, ULONG *pulVersion);
/* wangjiaqi modify for ipv6 bfd end */

/* wangjiaqi modify for ipv6 bfd 20131119 begin */
/*******************************************************************************
*    Func Name: BFD_GetSessionStatics
* Date Created: 2013-11-19
*       Author: wangjiaqi
*  Description: get BFD session statics
*        Input: ULONG ulVrfIndex
                ULONG ulSessionId
*       Output: BFD_STATISTIC_S *pstStat
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-19   wangjiaqi               Create    
*
*******************************************************************************/
ULONG BFD_GetSessionStatics(ULONG ulVrfIndex ,ULONG ulSessionId, BFD_STATISTIC_S * pstStat);

/*******************************************************************************
*    Func Name: BFD_ShowSessionStatics
* Date Created: 2013-11-19
*       Author: wangjiaqi
*  Description: show BFD session statics
*        Input: ULONG ulVrfIndex
                ULONG ulSessionId
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-19   wangjiaqi               Create    
*
*******************************************************************************/
VOID BFD_ShowSessionStatics(ULONG ulVrfIndex ,ULONG ulSessionId);

/*******************************************************************************
*    Func Name: BFD_ClrSessionStatics
* Date Created: 2013-11-19
*       Author: wangjiaqi
*  Description: show BFD session statics
*        Input: ULONG ulVrfIndex
                ULONG ulSessionId
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-19   wangjiaqi               Create    
*
*******************************************************************************/
ULONG BFD_ClrSessionStatics(ULONG ulVrfIndex ,ULONG ulSessionId);
/* wangjiaqi modify for ipv6 bfd end */

/* wangjiaqi modify for ipv6 bfd 20131121 begin */
/*******************************************************************************
*    Func Name: BFD6_SessionResetAll
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description:
*        Input:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-21   wangjiaqi               Create
*
*******************************************************************************/
ULONG BFD6_SessionResetAll(VOID);

/*******************************************************************************
*    Func Name: BFD6_DownAllSession
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description:
*        Input:
*       Output:
*       Return: ULONG
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-21   wangjiaqi               Create
*
*******************************************************************************/
ULONG BFD6_DownAllSession(VOID);

/*******************************************************************************
*    Func Name: BFD6_SetBfdCapability
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description: ʹ�ܻ�ȥʹ��BFD6����
*
*        Input: BOOL_T bBfdCapability TRUE��ʹ�ܣ�FALSE��ȥʹ�ܣ�
*
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_DISABLE_PROCESSING
*                              BFD_ERR_INVALID_PARAMETER
*
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-21      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_SetBfdCapability(BOOL_T bBfdCapability);

/****************************************************************************
*    Func Name: TCPIP6_BfdLicenseChgNotify
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description: �û�����,֪ͨBFD6 license����ͨ����ͨ��
*        Input: ULONG ulLicenseFlag:BFD license����ͨ����ͨ��
*               #define BFD_LICENSE_ON   0x01
*               #define BFD_LICENSE_OFF  0x00
*       Output: 
*       Return: VOS_OK:�ɹ� ��������ʧ��
*      Caution: Ϊ��ֹ����̫æ,ȫ��һ���¼�,������һ��BFD�Ự����һ���¼�
*               �ɿ�������һ���������ڹر���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-21   wangjiaqi        Create
*
*******************************************************************************/
ULONG TCPIP_Bfd6LicenseChgNotify(ULONG ulLicenseFlag);

/****************************************************************************
*    Func Name: TCPIP_BfdGetLicenseStateRegister
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description: ע���ȡBFD6 License���ܿ��صĹ��Ӻ���
*        Input: BFD_GET_LICENSE_STATE_FUNC pfFunc:���Ӻ���
*       Output: 
*       Return: VOS_OK:�ɹ� ��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-21   wangjiaqi        Create
*
*******************************************************************************/
ULONG TCPIP_Bfd6GetLicenseStateRegister(BFD_GET_LICENSE_STATE_FUNC pfFunc);
/* wangjiaqi modify for ipv6 bfd end */

/*******************************************************************************
*    Func Name: BFD6_SetAdaptMultiHopPort
* Date Created: 2013-11-25
*       Author: wangjiaqi
*  Description: �����Ƿ��Զ����������Ự��UDPĿ�Ķ˿ںš�VRP�ɰ�BFD�Ķ����˿ں�
*               �뵥���˿ں�һ������3784��VISPΪ����������Ự�Խ�����һЩ�޸ġ����A82D18150��
*        Input: ULONG ulSwitch: BFD_ON/�� BFD_OFF/�ر�
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_HA_IS_SMOOTHING;
*                              BFD_ERR_INVALID_PARAMETER;
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-25  wangjiaqi        Creat the first version.
*
*******************************************************************************/
ULONG BFD6_SetAdaptMultiHopPort(ULONG ulSwitch);

/****************************************************************************
*    Func Name: BFD6_SetAutoLocalDiscrGate
* Date Created: 2013-11-25
*       Author: wangjiaqi
*  Description: BFD6��̬���ûỰ�����޸�
*        Input: ulGate ���õķ�ֵ
*       Output: 
*       Return: VOS_OK:�ɹ� ��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-25   wangjiaqi        create
*
*******************************************************************************/
ULONG BFD6_SetAutoLocalDiscrGate(ULONG ulGate);
/*******************************************************************************
*    Func Name: BFD_OpenSessionTableEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: ��ȡBFD�Ự��ľ�����������������
*        Input: ULONG *pulWaitListHandle:
*               BFD_SESSION_FILTER_EX_S *pstFilter:
*       Output: 
*       Return: 
*      Caution: ��API�ں�BFD_OpenSessionTable��BFD6_OpenSessionTable�Ļ������ܡ�
*               ����ͬʱ��ѯBFD4��BFD6�ĻỰ��Ϣ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_OpenSessionTableEx(UINTPTR *pulWaitListHandle, BFD_SESSION_FILTER_EX_S *pstFilter);
/*******************************************************************************
*    Func Name: BFD_CloseSessionTableEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: �رջỰ���ͷ�filter��Դ
*        Input: ULONG ulWaitListHandle:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_CloseSessionTableEx(UINTPTR ulWaitListHandle);
/*******************************************************************************
*    Func Name: BFD_GetSessionInfoEntryEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: ͨ��WaitList�������ȡ��һ�����������������ָ��
*        Input: ULONG ulEntryWaitList: WaitList���
*       Output: pstSessionInfo:��ȡ���ĻỰ����
*       Return: �ɹ����� BFD_OK
*               ʧ�ܷ��� BFD_ERR_GET_ENTRY_END   �ӱ��л�ȡ�������Ϲ�����������ָ��
*                        BFD_ERR_WAITLIST
*                        BFD_ERR_DISABLE
*                        BFD_ERR_HA_IS_SMOOTHING
*                        BFD_ERR_NULL_POINTER
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_GetSessionInfoEntryEx(UINTPTR ulEntryWaitList, BFD_SESSION_ALL_INFO_EX_S *pstSessionInfo);
/*******************************************************************************
*    Func Name: BFD_GetSessionConfigEntryEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: ͨ��WaitList�������ȡ��һ�����������������ָ��
*        Input: ULONG ulEntryWaitList: WaitList���
*       Output: pstConfigInfo:��ȡ���ĻỰ��������
*       Return: �ɹ����� BFD_OK
*               ʧ�ܷ��� BFD_ERR_GET_ENTRY_END   �ӱ��л�ȡ�������Ϲ�����������ָ��
*                        BFD_ERR_WAITLIST
*                        BFD_ERR_DISABLE
*                        BFD_ERR_HA_IS_SMOOTHING
*                        BFD_ERR_NULL_POINTER
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_GetSessionConfigEntryEx(UINTPTR ulEntryWaitList, BFD_SESSION_CONFIG_INFO_EX_S *pstConfigInfo);
/*******************************************************************************
*    Func Name: BFD_GetSessionCountEntryEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: ͨ��WaitList�������ȡ��һ�����������������ָ��
*        Input: ULONG ulEntryWaitList: WaitList���
*       Output: pstCount:��ȡ����ͳ������
*       Return: �ɹ����� BFD_OK
*               ʧ�ܷ��� BFD_ERR_GET_ENTRY_END   �ӱ��л�ȡ�������Ϲ�����������ָ��
*                        BFD_ERR_WAITLIST
*                        BFD_ERR_DISABLE
*                        BFD_ERR_HA_IS_SMOOTHING
*                        BFD_ERR_NULL_POINTER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_GetSessionCountEntryEx(UINTPTR ulEntryWaitList, BFD_SESSION_COUNT_EX_S *pstCount);
/*******************************************************************************
*    Func Name: BFD6_NSR_PpiDownloadHookRegister
* Date Created: 2014-07-22
*       Author: likaikun213099
*  Description: 
*        Input: BFD6_PPI_HOOK_FUNC pfBfd6PpiHook:
*       Output: 
*       Return: 
*      Caution: NSR BFD�·�����ע�ắ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-22   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD6_NSR_PpiDownloadHookRegister(BFD6_PPI_HOOK_FUNC pfBfd6PpiHook);

/*******************************************************************************
*    Func Name: BFD6_NSR_OpenSessionStatTable
* Date Created: 2014-07-23
*       Author: likaikun213099
*  Description: 
*        Input: ULONG *pulWaitListHandle:
*               BFD6_SESSION_FILTER_S *pstFilter:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-23   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD6_NSR_OpenSessionStatTable(UINTPTR *pulWaitListHandle,BFD6_SESSION_FILTER_S *pstFilter);
/*******************************************************************************
*    Func Name: BFD6_NSR_GetSessionStateEntry
* Date Created: 2014-07-23
*       Author: likaikun213099
*  Description: 
*        Input: ULONG ulWaitListHandle:
*               BFD6_NSR_SESS_INFO_S *pstSessionNsrInfo:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-23   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD6_NSR_GetSessionStateEntry(UINTPTR ulWaitListHandle, BFD6_NSR_SESS_INFO_S *pstSessionNsrInfo);
/*******************************************************************************
*    Func Name: BFD6_NSR_CloseSessionStatTable
* Date Created: 2014-07-23
*       Author: likaikun213099
*  Description: 
*        Input: ULONG ulWaitListHandle:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-23   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD6_NSR_CloseSessionStatTable(UINTPTR ulWaitListHandle);
/*******************************************************************************
*    Func Name: BFD_Core_GetSessionCount
* Date Created: 2008-8-4
*       Author: qinyun(62011) 
*  Description: ����ָ���ĻỰ������ȡ�Ựͳ����Ϣ
*        Input: ulSessionId: �Ự����
*               ulVrfIndex:  VRF����
*       Output: pstCount: �Ựͳ����Ϣ
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE    
*                              BFD_ERR_HA_IS_SMOOTHING    
*                              BFD_ERR_NULL_POINTER    
*                              BFD_ERR_SESSION_ID    
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-8-4     qinyun(62011)    Creat the first version.
*  2008-02-19   wangchengyang    VISP1.7C03,VRF,����һ�����
*******************************************************************************/
ULONG BFD_Core_GetSessionCount(ULONG ulSessionId,BFD_SESSION_COUNT_S *pstCount,ULONG ulVrfIndex);
#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _BFD_API_H_    */

