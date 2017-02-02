/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              rpm_type.h
*                 ���ļ�ΪRIP��OSPF��RTM �ṩ�������ֵĶ���
*******************************************************************************/

#ifndef _RPM_TYPE_H_
#define _RPM_TYPE_H_

#ifdef  __cplusplus
    extern "C"{
#endif


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef BOOL_T
#define BOOL_T  short   /* boolean */  
#endif 


#define NBASE_MSG_SWITCH_VALUE    10
#define SCKSTUB_MSG_SWITCH_VALUE  10
#define DCL_TASK_SWITCH_INTERVAL  1/*�л�CPUʱ��1ms*/
/*�ڲ�����GET FIRST����µ���GET NEXT����ʧ��

���������ʾ ��ѯ״̬

ֻ���ڲ�ѯ��һ����ɣ�����MORE ״̬��������
GET NEXT ����

OPEN ��״̬ΪGET_STATE_BEGIN
��ѯFIRST �����سɹ���״̬ΪGET_STATE_MORE
GET_STATE_END ��ʾ��ѯ����
*/
#define  GET_STATE_BEGIN  0x01   
#define  GET_STATE_MORE   0x02
#define  GET_STATE_END     0x04

typedef enum tagSI_ERROR_E  
{
    SI_INIT_SUCSESS,
    SI_RRR_GEN_ERROR = MID_COMP_MIB + 2, 
    SI_RRR_WRONG_VALUE, /*MIB���õ�ֵ����*/
    SI_RRR_INCONSISTENT_VALUE,/*MIB���õ�ֵ��һ��*/
    SI_RRR_RESOURCE_UNAVAILABLE,/*MIB���õ���Դ��Ч*/
    SI_RRR_NO_SUCH_OBJECT, /*���󲻴���*/
    SI_RRR_END_OF_TABLE,/*�������*/
    SI_RRR_AGENT_ERROR, 
    SI_RRR_INCOMPLETE,  
    SI_RRR_PARTIAL_FAMILY_OK,
    SI_RRR_PRODUCT_NOT_READY,
    SI_RRR_CFG_TIMEOUT = MID_COMP_MIB + 15,/*���ó�ʱ*/   
    SI_RRR_POINTER_IS_NULL ,
    SI_RRR_CONF_DATA_IS_NULL,
    SI_ERR_CONN_CB_IS_NULL,
    SI_ERR_RET_IPS_IS_NULL,
    SI_ERR_MAX = MID_COMP_MIB + 255,
}SI_ERROR_E; /*ϵͳMIB */

typedef struct tagRM_Rpm_Plcy_Id_s
{
    USHORT usSrcType;   /*ԴЭ������*/
    USHORT usSrcProcId; /*ԴЭ��ID*/
    ULONG  ulDirection; /*���˵ķ���:����߳�*/
    USHORT usDstType;   /*Ŀ��Э��ID*/
    USHORT usDstProcId; /*Ŀ��ʵ����*/
    ULONG  ulPolicyId; /*����ID*/
    /* Begin BC3D03313 liangjicheng 2010-06-22 */
    ULONG  ulUseFlag;      /*��ʾ��ǰ���Ա�˭ʹ��-��λ��ʹ��*/
    ULONG  ulACLNo;        /*���˲���ACL*/
    /* End   BC3D03313 liangjicheng 2010-06-22 */
    NBB_LLQE  stListNode;   /*����*/
} RM_RPM_PLCY_ID_S;


typedef ULONG (*OSPF_IF_UPDATE_HOOK_FUNC)(CHAR *, ULONG , ULONG ,ULONG);
typedef ULONG (*RIP_IPADDR_UPDATE_HOOK_FUNC)(USHORT, USHORT ,ULONG, ULONG);

#ifdef  __cplusplus
}
#endif

#endif

