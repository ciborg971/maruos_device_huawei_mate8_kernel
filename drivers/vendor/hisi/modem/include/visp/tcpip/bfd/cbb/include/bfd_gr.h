/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_gr.h
*
*  Project Code: VISPV100R006C02B100
*   Module Name: bfd grͷ�ļ�
*  Date Created: 2008-8-16
*        Author: wujie(61195)
*   Description: ����BFD GRģ��ĺ궨�塢ȫ�ֱ��������ͺ�������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-8-16  wujie(61195)         Creat the first version.
*
*******************************************************************************/
#ifndef _BFD_GR_H_
#define _BFD_GR_H_

#ifdef __cplusplus
extern "C"{
#endif

/* BFD��GR״̬ */
enum enumBFD_GR_STATE
{
    BFD_STATE_NORMAL,       /* 0 ����״̬ */
    BFD_STATE_KEEPALIVE,    /* 1 ����״̬, �ȴ��ָ����� */
    BFD_STATE_RESTORING,    /* 2 ���ڽ��лָ����� */
    BFD_STATE_RESTORED,     /* 3 �Ѿ���ɻָ�����, �ȴ�ƽ������ */
    BFD_STATE_SMOOTHING,    /* 4 ���ڽ���ƽ������, ƽ��������Ϻ�ֱ�ӽ��� 0 ����״̬ */
};


/* �Ƚ����õĲ�����NP����Ĳ����Ƿ�һ��, ��һ�����¼��־ */
#define BFD_GR_CMP_PARA(cfg_para, np_para) \
if ((ULONG)(cfg_para) != (ULONG)(np_para)) \
{\
    ulParaDiff = 1;\
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_04DC, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, \
                     "\r\nThe para of session %u mismatch(line %u): CFG(%u) != NP(%u)",\
                     ulSessionID, __LINE__, (ULONG)(cfg_para), (ULONG)(np_para));\
}\


USHORT BFD_GR_CalcCksum(USHORT *pusCalcFrom, LONG lTotalLen);
ULONG BFD_GR_RestoreOneSession(BFD_SESS_ENTRY_S *pstBfdSession);
ULONG BFD_GR_Restore(VOID);
ULONG BFD_GR_SmoothOneSession(ULONG ulVrfIndex,ULONG ulSessionID);
ULONG BFD_GR_Smooth(VOID);

extern VOID VOS_GetCpuTick( ULONG *plow,ULONG *phigh );

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _BFD_GR_H_ */
