/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_func.h
*
*  Project Code: VISPV100R005
*   Module Name: AM4  
*  Date Created: 2006-01-04
*        Author: Li LiXiang
*   Description: ������AM4�еĹ��ܺ���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                ���ݱ�̹淶�����ļ����й淶������ 
*  2006-05-11   luyao(60000758)         Ϊ֧��ARM CPU�ֽڶ������ԣ��޸Ľṹ
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _AM4_FUNC_H_
#define _AM4_FUNC_H_

typedef struct tagIPAm4Addrmsg
{
    ULONG   ulIntfIndex;
    USHORT  usMsgType;
    UCHAR   ucPadding[2]; 
    ULONG   ulIpFlag;           /* ����IP�ȱ�־��new in 3.0 */
    SOCKADDR_S  sLocalAddr;
    SOCKADDR_S  sNetMask;
    SOCKADDR_S  sPrimaryAddr;   /* �µ�����ַ, new in 3.0*/
}IP_AM4_ADDRMSG_S;

/*�ṹIP_ADDR_NOTIFY_MSG_S�Ѿ�Ų��am4_api.h*/

extern ULONG IP_AM4_SendMsgToRm(struct tagIPAm4Addrmsg* pstIPMsg);


#endif  /* end of _AM4_FUNC_H_ */ 


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

