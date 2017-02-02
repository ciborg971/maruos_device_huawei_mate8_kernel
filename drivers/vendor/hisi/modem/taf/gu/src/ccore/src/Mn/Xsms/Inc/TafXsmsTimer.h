

#ifndef __TAF_XSMS_TIMER_H__
#define __TAF_XSMS_TIMER_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* MT �ĳ�ʱʱ�� */
#define TI_TAF_XSMS_TIMER_MT_IDLE_MAX                          (60 * 1000)
#define TI_TAF_XSMS_TIMER_MT_WAIT_CONN_IND_MAX                 (20 * 1000)
#define TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF_MAX                  (20 * 1000)
#define TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND_MAX               (20 * 1000)
#define TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND_MAX                 (20 * 1000)
#define TI_TAF_XSMS_TIMER_MT_WAIT_WRITE_UIM_CNF_MAX            (20 * 1000)
#define TI_TAF_XSMS_TIMER_MT_WAIT_READ_UIM_CNF_MAX             (20 * 1000)
#define TI_TAF_XSMS_TIMER_MT_WAIT_CSCH_CNF_MAX                 (30 * 1000)
#define TI_TAF_XSMS_TIMER_MT_WAIT_DSCH_CNF_MAX                 (13 * 1000)
#define TI_TAF_XSMS_TIMER_MT_WAIT_CALL_END_MAX                 (20 * 1000)
#define TI_TAF_XSMS_TIMER_MT_END_LINK_PROTECT_MAX              (20 * 1000)

/* �뿨������ʱ��ʱ������λMS */
#define TI_TAF_XSMS_TIMER_USIMM_INIT_LEN                       (10  * 1000)

/* MO �ĳ�ʱʱ�� */
#define TI_TAF_XSMS_TIMER_MO_IDLE_MAX                          (60 * 1000)
#define TI_TAF_XSMS_TIMER_MO_WAIT_FDN_CNF_MAX                  (20 * 1000)
#define TI_TAF_XSMS_TIMER_MO_WAIT_CC_CNF_MAX                   (20 * 1000)
#define TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF_MAX             (20 * 1000)
#define TI_TAF_XSMS_TIMER_MO_WAIT_CSCH_CNF_MAX                 (30 * 1000)
#define TI_TAF_XSMS_TIMER_MO_WAIT_DSCH_CNF_MAX                 (13 * 1000)
#define TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND_MAX               (20 * 1000)
#define TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK_MAX                   (18 * 1000)
#define TI_TAF_XSMS_TIMER_MO_WAIT_END_CALL_MAX                 (1  *  500)
#define TI_TAF_XSMS_TIMER_MO_WAIT_LINK_ABORT_MAX               (4  * 1000)




/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum CNAS_XREG_TIMER_ID_ENUM
{
    TI_TAF_XSMS_TIMER_MT_IDLE                          = 0,
    TI_TAF_XSMS_TIMER_MT_WAIT_CONN_IND                 = 1,
    TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF                  = 2,
    TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND               = 3,
    TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND                 = 4,
    TI_TAF_XSMS_TIMER_MT_WAIT_WRITE_UIM_CNF            = 5,
    TI_TAF_XSMS_TIMER_MT_WAIT_READ_UIM_CNF             = 6,
    TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF                   = 7,
    TI_TAF_XSMS_TIMER_MT_WAIT_CALL_END                 = 8,
    TI_TAF_XSMS_TIMER_MT_RESEND                        = 9,
    TI_TAF_XSMS_TIMER_MT_END_LINK_PROTECT              = 10,
    TI_TAF_XSMS_TIMER_INIT_PROTECT                     = 11,
    TI_TAF_XSMS_TIMER_MO_IDLE                          = 12,
    TI_TAF_XSMS_TIMER_MO_WAIT_FDN_CNF                  = 13,
    TI_TAF_XSMS_TIMER_MO_WAIT_CC_CNF                   = 14,
    TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF             = 15,
    TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF                   = 16,
    TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND               = 17,
    TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK                   = 18,
    TI_TAF_XSMS_TIMER_MO_RELINK                        = 19,
    TI_TAF_XSMS_TIMER_MO_RESEND                        = 20,
    TI_TAF_XSMS_TIMER_MO_WAIT_END_CALL                 = 21,
    TI_TAF_XSMS_TIMER_MO_WAIT_SMS_ABORT                = 22,


    TI_TAF_XSMS_TIMER_BUTT
};
typedef VOS_UINT32  TAF_XSMS_TIMER_ID_ENUM_UINT32;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern HTIMER                                  g_astXsmsTimer[TI_TAF_XSMS_TIMER_BUTT];

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID TAF_XSMS_StartTimer(VOS_UINT32 ulTimerId, VOS_UINT32 ulTimerLen);


VOS_VOID TAF_XSMS_StopTimer(VOS_UINT32 ulTimerId);



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __TAF_XSMS_TIMER_H__ */

