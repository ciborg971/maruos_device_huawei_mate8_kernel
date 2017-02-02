
#ifndef __TTF_CAUSE_H__
#define __TTF_CAUSE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#include "vos.h"


/*******************************************************************************
�궨��
˵��:����Ĵ���Χ��0x0000��0x0FFF
*******************************************************************************/
/*��������ԭ��*/
#define TTF_CAUSE_INPUT_PARAMS          0x0101      /*�����������*/
#define TTF_CAUSE_STATE                 0x0102      /*�յ���Ϣ�Ĵ���״̬����*/


/*ϵͳ����ԭ��*/
#define TTF_CAUSE_MEM_OVERLOAD          0x0201      /*�ڴ泬����������*/
#define TTF_CAUSE_MEM_ALLOC             0x0202      /*ϵͳ����ALLOCʧ��*/

#define TTF_CAUSE_QUEUE_NOTEMPTY        0x0203      /*���в���*/


/*SN��LLC���õ�ʧ��ԭ��*/
#define SN_CAUSE_INVALID_XID_RSP        0x0301      /*Cause "invalid XID response"*/
#define SN_CAUSE_INVALID_XID_CMD        0x0302      /*Cause "invalid XID command"*/
#define SN_CAUSE_NO_PEER_RSP            0x0303      /*Cause "no peer response"*/
#define SN_CAUSE_NORMAL_REL             0x0304      /*Cause "normal release"*/
#define SN_CAUSE_DM_RCV                 0x0305      /*Cause "DM received"*/
#define SN_CAUSE_OTHER                  0x0306      /*Cause "other cause"*/

/*LLC�Լ����ӵĿ�ά�ɲ���Ϣ*/
#define SN_CAUSE_LL_NU_OUT_OFF_ORDER    0x0307      /*Cause "NU out of order"*/

#define SN_CAUSE_LL_RCV_RNR             0x0308      /*Cause "LL receive RNR frame"*/
#define SN_CAUSE_LL_RCV_ACK             0x0309      /*Cause "LL receive ACK frame"*/
#define SN_CAUSE_LL_RCV_SACK            0x030A      /*Cause "LL receive SACK frame"*/
#define SN_CAUSE_LL_RCV_FRMR            0x030B      /*Cause "LL receive FRMR frame"*/
#define SN_CAUSE_LL_SND_RNR             0x030C      /*Cause "LL send RNR frame"*/
#define SN_CAUSE_LL_SND_ACK             0x030D      /*Cause "LL send ACK frame"*/
#define SN_CAUSE_LL_SND_SACK            0x030E      /*Cause "LL send SACK frame"*/
#define SN_CAUSE_LL_SND_FRMR            0x030F      /*Cause "LL send FRMR frame"*/

#define SN_CAUSE_LL_RCV_SABM            0x0310      /*Cause "LL receive SABM frame"*/
#define SN_CAUSE_LL_RCV_DISC            0x0311      /*Cause "LL receive DISC frame"*/
#define SN_CAUSE_LL_RCV_UA              0x0312      /*Cause "LL receive UA frame"*/
#define SN_CAUSE_LL_RCV_DM              0x0313      /*Cause "LL receive DM frame"*/
#define SN_CAUSE_LL_RCV_XID             0x0314      /*Cause "LL receive XID frame"*/
#define SN_CAUSE_LL_SND_SABM            0x0315      /*Cause "LL send SABM frame"*/
#define SN_CAUSE_LL_SND_DISC            0x0316      /*Cause "LL send DISC frame"*/
#define SN_CAUSE_LL_SND_UA              0x0317      /*Cause "LL send UA frame"*/
#define SN_CAUSE_LL_SND_DM              0x0318      /*Cause "LL send DM frame"*/
#define SN_CAUSE_LL_SND_XID             0x0319      /*Cause "LL send XID frame"*/
#define SN_CAUSE_LL_CHK_PARAM_FAIL      0x031A      /*����������*/
#define SN_CAUSE_LL_CIPH_FAIL           0x031B      /*�ӽ��ܴ���"*/
#define SN_CAUSE_LL_LEN_Exceed_N201U    0x031C      /*֡���ȳ���N201-U"*/

/*******************************************************************************
�ṹ����
*******************************************************************************/
#pragma pack(4)


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/*******************************************************************************
�����ṩ�ĺ�������
*******************************************************************************/



/******************************************************************************/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif





