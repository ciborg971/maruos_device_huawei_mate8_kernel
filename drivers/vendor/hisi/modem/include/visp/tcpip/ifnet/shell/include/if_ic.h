/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_IC.H 
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2000/11/03 
 *        Author: Zhouxiaoniu
 *   Description: 
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000/11/03      Zhouxiaoniu     Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *  2006-05-10  lu yao(60000758)    Ϊ֧��ARM CPU�ֽڶ������ԣ��޸Ľṹ��
 *
 ************************************************************************/

#ifndef _IF_IC_H_
#define _IF_IC_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* �����Ϣ�����ͺ궨�� */
#define IC_INFO_LOG             1
#define IC_INFO_TRAP            2
#define IC_INFO_DEBUG           3
#define IC_INFO_HIDE            0x8

#define IC_INFOMODU_MASK        0xFFFF0000 /*ULONG�ĸ�16λbit31~bit16Ϊģ���*/
#define IC_INFOTYPE_MASK        0x00007000 /*ULONG��bit15~bit12Ϊ��Ϣ����*/
#define IC_INFONO_MASK          0x00000FFF /*ULONG�ĵ�12λ(bit11~bit0)Ϊ������Ϣ�ڱ�ģ����ڲ����*/

/*��ϢID�궨��*/
#define IC_INFOID_DEF(mid, infotype, infoidx) ( (mid) | ( (infotype) << 12 ) | (infoidx) )

/*����ϢID��ȡ��Ϣ���Ե�ģ���*/
#define IC_INFOMODU(InfoID) ( (InfoID) & IC_INFOMODU_MASK )  

/*����ϢID��ȡ����Ϣ����*/
#define IC_INFOTYPE(InfoID) ( ((InfoID) & IC_INFOTYPE_MASK) >> 12)  

/*����ϢID��ȡ��Ϣ��ģ���ڵı��*/
#define IC_INFONO(InfoID)  ( (InfoID) & IC_INFONO_MASK) 

/*************************************************************************
*                                                                        *
*                  ��־��ʾ��ϢID����                                    *
*                                                                        *
**************************************************************************/
enum{
    IF_INFO_ID_LINKPROTO_UPDOWN = 1,
    IF_INFO_ID_LINKLCPPROTO_UPDOWN,
    IF_INFO_ID_LINKMUXCPPROTO_UPDOWN,
    IF_INFO_ID_LINKLACPPROTO_UPDOWN,  /* Trunk LACP */
    IF_INFO_ID_LINKOSICPPROTO_UPDOWN, /* OSICP */
    IF_INFO_ID_MAX
} ;
/* Э��״̬��Ϣ */
#define IFNET_LOGID_LINKPROTO_UPDOWN            IC_INFOID_DEF(MID_COMP_IFNET, IC_INFO_LOG, IF_INFO_ID_LINKPROTO_UPDOWN)
#define IFNET_LOGID_LINKLCPPROTO_UPDOWN         IC_INFOID_DEF(MID_COMP_IFNET, IC_INFO_LOG, IF_INFO_ID_LINKLCPPROTO_UPDOWN)
#define IFNET_LOGID_LINKMUXCPPROTO_UPDOWN       IC_INFOID_DEF(MID_COMP_IFNET, IC_INFO_LOG, IF_INFO_ID_LINKMUXCPPROTO_UPDOWN)
#define IFNET_LOGID_LINKLACPPROTO_UPDOWN        IC_INFOID_DEF(MID_COMP_IFNET, IC_INFO_LOG, IF_INFO_ID_LINKLACPPROTO_UPDOWN)
#define IFNET_LOGID_LINKOSICPPROTO_UPDOWN       IC_INFOID_DEF(MID_COMP_IFNET, IC_INFO_LOG, IF_INFO_ID_LINKOSICPPROTO_UPDOWN)

/*************************************************************************
*                                                                        *
*                    ���������ʽ                                        *
*                                                                        *
**************************************************************************/
#define MSG_FMT_NONE            1                 /* û�в��� */
#define MSG_FMT_ONEZERO         2                 /* one string */
#define MSG_FMT_TWOZERO         3                 /* two string */
#define MSG_FMT_ONEONE          4                 /* one string, one ULONG */
#define MSG_FMT_TWOONE          5                 /* two string, one ULONG */
#define MSG_FMT_THREETWO        6                 /* three string, two ULONG */
#define MSG_FMT_ZEROONE         7                 /* one ULONG */
#define MSG_FMT_ZEROTWO         8                 /* two ULONG */


#ifndef  _CLI_PUB_H
enum
{
    LANGUAGE_ENGLISH,
    LANGUAGE_CHINESE,
    LANGUAGE_RUSSIAN,
    LANGUAGE_MAX
};

typedef struct tagInformation
{
    ULONG ulInfoID;
    CHAR * szInfo[LANGUAGE_MAX];
} VRP_INFORMATION;
#endif

#define SECTION_NAME_LEN        80

#define   EXEC_DISPLAY_STOP         1  /* added by ljw */
#define   EXEC_DISPLAY_CONTINUE     0  /* added by ljw */

/* �������� */
ULONG IF_SendInfoToIC(ULONG , CHAR** , ULONG ,ULONG , ULONG);

#ifdef  __cplusplus
}
#endif

#endif  /* end of _IF_IC_H_ */

