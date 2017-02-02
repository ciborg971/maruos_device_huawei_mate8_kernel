

#ifndef _GMM_CAS_MAIN_H_
#define _GMM_CAS_MAIN_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#pragma pack(4)         /* 1�ֽڶ��룬���ݽṹ���屣֤4�ֽڶ��� */
                        /* ����include�󣬲�Ӱ������ͷ�ļ���pack���� */
/*****************************************************************************
  2 �궨��
*****************************************************************************/
typedef VOS_UINT8 GMM_SYS_CHG_TYPE;
#define GMM_SYS_CHG_NULL                        0           /* �ղ��� */
#define GMM_SYS_CHG_PMMIDLE_TO_GSM_RA_OLD       1
#define GMM_SYS_CHG_PMMIDLE_TO_GSM_RA_NEW       2
#define GMM_SYS_CHG_PMMCONN_TO_GSM_RA           3
#define GMM_SYS_CHG_STANDBY_TO_UTRAN_RA_OLD     4
#define GMM_SYS_CHG_STANDBY_TO_UTRAN_RA_NEW     5
#define GMM_SYS_CHG_READY_TO_UTRAN_RA           6

typedef VOS_UINT8 GMM_CAS_CHG_TYPE;
#define GMM_CAS_CHG_NULL                        0           /* �ղ��� */
#define GMM_CAS_CHG_SUSPEND                     1
#define GMM_CAS_CHG_RESUME_WCDMA                2
#define GMM_CAS_CHG_RESUME_GSM                  3
#define GMM_CAS_CHG_SYNC_WCDMA                  4
#define GMM_CAS_CHG_SYNC_GSM                    5

/* BEGIN: Added by liurui id:40632, 2006/7/26   PN:A32D03975 */
typedef VOS_UINT8 GMM_NETMODE_CHG_TYPE;
#define GMM_NETMODE_CHG_NULL                    0           /* �ղ��� */
#define GMM_NETMODE_CHG_I_II                    1
#define GMM_NETMODE_CHG_I_III                   2
#define GMM_NETMODE_CHG_II_III                  3
#define GMM_NETMODE_CHG_II_I                    4
#define GMM_NETMODE_CHG_III_I                   5
#define GMM_NETMODE_CHG_III_II                  6

typedef VOS_UINT8 GMM_INTERSYS_CHG_TYPE;
#define GMM_INTERSYS_CHG_NULL                   0           /* �ղ��� */
#define GMM_INTERSYS_CHG_GI_UI                  1
#define GMM_INTERSYS_CHG_GII_UI                 2
#define GMM_INTERSYS_CHG_GI_UII                 3
#define GMM_INTERSYS_CHG_GII_UII                4
#define GMM_INTERSYS_CHG_GIII_UI                5
#define GMM_INTERSYS_CHG_GIII_UII               6
#define GMM_INTERSYS_CHG_GC_UC                  7
#define GMM_INTERSYS_CHG_UI_GI                  8
#define GMM_INTERSYS_CHG_UII_GI                 9
#define GMM_INTERSYS_CHG_UI_GII                 10
#define GMM_INTERSYS_CHG_UI_GIII                11
#define GMM_INTERSYS_CHG_UII_GIII               12
#define GMM_INTERSYS_CHG_UC_GC                  13
#define GMM_INTERSYS_CHG_UCS_G                  14
#define GMM_INTERSYS_CHG_U_G_COMMON             20
#define GMM_INTERSYS_CHG_G_U_COMMON             30
/* END:   Added by liurui id:40632, 2006/7/26   PN:A32D03975 */

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

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

VOS_VOID    GMM_CasMsgProc (struct MsgCB* pMsg, VOS_UINT8 *pucFollowOn);

VOS_VOID GMM_CasMsgProc_GmmSuspendNormalService(
    struct MsgCB                       *pMsg,
    VOS_UINT8                          *pucFollowOn
);
VOS_VOID    GMM_CasChangSysMode(VOS_UINT8 ucState);
VOS_VOID    GMM_CasGetRauType(VOS_UINT8 *pucRauType, VOS_UINT32 ulCasNewState);
VOS_VOID    GMM_CasExecRauInSysChg(VOS_UINT8 ucRauType);
VOS_VOID    GMM_InitSelectiveRau(VOS_VOID);
VOS_UINT32  GMM_CasChangState(VOS_UINT8 ucModeChg, VOS_VOID* pRcvMsg);
VOS_UINT8   GMM_CasGetNetChgType(VOS_UINT8 ucNewNetMod);
VOS_VOID    GMM_ProcedureByNetMode(VOS_UINT8 ucNetModChangeType);

/* BEGIN: Added by liurui id:40632, 2006/7/26   PN:A32D03975 */
VOS_VOID GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_TYPE ucNetChgTyp,VOS_UINT8 ucRaiChgFlg);
VOS_UINT8 GMM_CasGetNetChgTypeByUmts(VOS_UINT8 ucNewNetMod);
VOS_UINT8 GMM_CasGetNetChgTypeByGsm(VOS_UINT8 ucNewNetMod);
VOS_VOID GMM_CasInterSystemByUmts(VOS_VOID);
VOS_VOID GMM_CasInterSystemByGsm(VOS_VOID);
/* END:   Added by liurui id:40632, 2006/7/26   PN:A32D03975 */

VOS_VOID GMM_SaveMsg(VOS_VOID *pMsg, VOS_UINT8 *pucFollowOn);
VOS_VOID GMM_SuspendMsgProc(struct MsgCB* pMsg, VOS_UINT8 *pucFollowOn);



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of GmmCasMain.h*/
