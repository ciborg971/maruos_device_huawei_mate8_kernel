/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                                3ah_hdr.h
*
*  Project Code: VR7C03
*   Module Name: 3ah  
*  Date Created: 2009-02-28
*        Author: L00105073/L00111779
*   Description: 3ah��챨��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-02-28   L00105073/L00111779     Create
*
*******************************************************************************/

#ifndef _3AH_HDR_H_
#define _3AH_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif



/* 3ah�ӿ���챨�����ݽṹ */

/* �ӿ�ͳ����Ϣ */
typedef struct tagOAM3AH_HEALTH_IFSTATISTIC
{
    ULONG ulIfIndex;
    OAM3AH_PDUSTAT_S stPduStat;
}OAM3AH_HEALTH_IFSTATISTIC_S ;

/* 3ah״̬��״̬ */
typedef struct tagOAM3AH_HEALTH_FSMSTATE
{
    ULONG ulIfIndex;
    ULONG ulFsmState;                   /* �ӿ�3AH״̬��״̬            */
    UCHAR aucPeerMacAddr[MACADDRLEN];   /* �Զ�physical��ַ              */
    UCHAR ucReserve[2];
}OAM3AH_HEALTH_FSMSTATE_S;


extern VOID OAM_3AH_Health_BatchCheckup(VOID);
extern ULONG OAM_3AH_Health_IfStatisticCheckup(VOID);
extern ULONG OAM_3AH_Health_FsmStateCheckup(VOID);

#ifdef  __cplusplus
}
#endif
#endif

