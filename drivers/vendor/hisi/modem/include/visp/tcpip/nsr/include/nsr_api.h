#ifndef NSR_API_INCLUDED
#define NSR_API_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "tcpip/nsr/include/nsr_api_def.h"

/*******************************************************************************
*    Func Name: NSR_SetNSRCapability
* Date Created: 2013-09-27
*       Author: guojianjun178934
*      Purpose: NSRʹ��/ȥʹ�ܿ���
*  Description: 
*        Input: UCHAR  ucNSRCapability: NSR_CAPABILITY_ENABLE       NSRʹ��
*                                       NSR_CAPABILITY_DISENABLE    NSRȥʹ��
*       Output: 
*       Return: �ɹ���NSR_OK
*               ʧ�ܣ�������
*      Caution: 
*        Since: V300R002C00
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-09-27   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_SetNSRCapability(UCHAR  ucNSRCapability);
/*******************************************************************************
*    Func Name: NSR_RegFunSendBackupMsgHook
* Date Created: 2012-11-28
*       Author: guojianjun178934
*      Purpose: ע�����巢�ͱ������ݹ��Ӻ���
*  Description: 
*        Input: NSR_SEND_BACKUP_MSG_FUNC pfFunc: ���ͱ������ݹ��Ӻ���
*                                       
*       Output: 
*       Return: �ɹ���NSR_OK
*               ʧ�ܣ�������
*      Caution: 
*        Since: V300R002C00
*    Reference: NSR_SEND_BACKUP_MSG_FUNC
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-28   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_RegFunSendBackupMsgHook(NSR_SEND_BACKUP_MSG_FUNC pfFunc);
/*******************************************************************************
*    Func Name: NSR_RegFunSendControlMsgHook
* Date Created: 2012-11-28
*       Author: guojianjun178934
*      Purpose: ע��֪ͨ��Ʒ�������������Ӻ���(�����嶼���Ե���)
*  Description: 
*        Input: NSR_SEND_BACKUP_MSG_FUNC pfFunc: ֪ͨ��Ʒ�������������Ӻ���
*                                       
*       Output: 
*       Return: �ɹ���NSR_OK
*               ʧ�ܣ�������
*      Caution: 
*        Since: V300R002C00
*    Reference: NSR_SEND_CONTROL_MSG_FUNC
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-28   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_RegFunSendControlMsgHook(NSR_SEND_CONTROL_MSG_FUNC pfFunc);
/*******************************************************************************
*    Func Name: NSR_ReceiveBackupMsg
* Date Created: 2012-11-28
*       Author: guojianjun178934
*      Purpose: ������ձ�����Ϣ������
*  Description: 
*        Input: UCHAR *pucBuf:  ������Ϣָ��
*               ULONG ulMsgLen: ��Ϣ����                       
*       Output: 
*       Return: �ɹ���NSR_OK
*               ʧ�ܣ�������
*      Caution: 
*        Since: V300R002C00
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-28   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_ReceiveBackupMsg(UCHAR *pucBuf, ULONG ulMsgLen);
/*******************************************************************************
*    Func Name: NSR_ReceiveControlMsg
* Date Created: 2012-11-28
*       Author: guojianjun178934
*      Purpose: ��/������ղ�Ʒ���͵�NSR��������Ϣ
*  Description: 
*        Input: NSR_CONTROL_MSG *pstNSRControlMsg:  ������Ϣָ��                     
*       Output: 
*       Return: �ɹ���NSR_OK
*               ʧ�ܣ�������
*      Caution: 
*        Since: V300R002C00
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-28   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_ReceiveControlMsg(NSR_CONTROL_MSG *pstNSRControlMsg);
/*******************************************************************************
*    Func Name: NSR_Get_NSR_Common_Info
* Date Created: 2013-10-15
*       Author: guojianjun178934
*      Purpose: ��ȡNSR����ģ����Ϣ
*  Description: 
*        Input:                     
*       Output: NSR_COMMON_INFO_SHOW *pstShow: NSR����ģ����Ϣ
*       Return: �ɹ���NSR_OK
*               ʧ�ܣ�������
*      Caution: 
*        Since: V300R002C00
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-10-15   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_Get_NSR_Common_Info(NSR_COMMON_INFO_SHOW *pstShow);
/*******************************************************************************
*    Func Name: NSR_RegFunGetNSRBaseInfoHook
* Date Created: 2013-10-18
*       Author: guojianjun178934
*      Purpose: ��ƷNSR״̬��ȡע�ṹ�캯��
*  Description: 
*        Input: NSR_GET_NSR_BASE_INFO_FUNC pfFunc:  NSR״̬��ȡ����                 
*       Output: 
*       Return: �ɹ���NSR_OK
*               ʧ�ܣ�������
*      Caution: 
*        Since: V300R002C00
*    Reference: NSR_GET_NSR_BASE_INFO_FUNC
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-10-18   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_RegFunGetNSRBaseInfoHook(NSR_GET_NSR_BASE_INFO_FUNC pfFunc);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
