/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_ha.h
*
*  Project Code: VISPV100R007
*   Module Name: IGMP  
*  Date Created: 2008-03-14
*        Author: zengshaoyang62531
*   Description: IGMP HAͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-14   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_HA_H
#define _IGMPV3_HA_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define IGMPTLLENGTH  4        /* T + L �ĳ���*/
#define IGMPSUBMSGHEADLEN 4    /* ����Ϣ���ͺͳ�����ռ�ռ�*/

/*��������*/
typedef enum tagIGMPOPERATION
{
    IGMP_HA_SET = 1             /* ����*/
}IGMPOPERATION_E;

/*����Ϣ����*/
typedef enum tagIGMPSUBMSGTYPE
{
    IGMP_HA_SETTIME = 1,
    IGMP_HA_SETCOMP
}IGMPSUBMSGTYPE_E;

typedef struct tagIGMPSUBMSG
{
    USHORT usType;             /*����Ϣ����*/
    USHORT usLength;           /*����Ϣ����*/
}IGMPSUBMSG_S;

typedef struct tagIGMPTYPELENGTH
{
    USHORT usType;             /*type*/
    USHORT usLength;           /*length*/
}IGMPTYPELENGTH_S;

/*T*/
typedef enum tagIGMPBAKTYPE
{
    IGMP_HA_SETCOMPVAR = 0x1000
}IGMPBAKTYPE_E;

/*V*/
typedef struct tagIGMP_RPTTIME_BAK
{
    ULONG  ulTimerType;
    ULONG  ulRptTime;
}IGMP_RPTTIME_BAK_S;

/*V*/
typedef struct tagIGMP_COMPVAR_BAK
{
    ULONG  ulCompVar;
    ULONG  ulIfIndex;
}IGMP_COMPVAR_BAK_S;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
