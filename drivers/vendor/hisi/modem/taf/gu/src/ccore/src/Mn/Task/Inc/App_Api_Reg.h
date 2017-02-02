/******************************************************************************

            ��Ȩ���� (C), 2005-2007, ��Ϊ�������޹�˾


  �� �� ��   : App_Api_Reg.h
  �� �� ��   : ����
  ��    ��   : liuyang id:48197
  ��������   : 2006��2��17��
  ����޸�   :
  ��������   : App_Api_Reg.c ��ͷ�ļ�
  �����б�   :
                ---
                ---
                ---
  �޸���ʷ   :
        1.��    ��   : 2006��2��17��
          ��    ��   : liuyang id:48197
          �޸�����   : �����ļ�
        2.��    ��   : 2006��2��17��
          ��    ��   : ---
          �޸�����   : Add function ... ���ⵥ��:

******************************************************************************/

#ifndef __APP_API_REG_H__
#define __APP_API_REG_H__


#ifdef __cplusplus
  #if __cplusplus
    extern "C"{
  #endif
#endif /* __cplusplus */

/******************************************************************************
   1 ͷ�ļ�����
 *****************************************************************************/

/*****************************************************************************
   2 �ڲ�����ԭ��˵��
 *****************************************************************************/

/*****************************************************************************
   3 ȫ�ֱ�������
 *****************************************************************************/

/*****************************************************************************
   4 ģ�鼶����
 *****************************************************************************/

/*****************************************************************************
   5 ��������
 *****************************************************************************/

/*****************************************************************************
   6 �궨��
 *****************************************************************************/
#define OP_ID_MMA       3      /*����ͬһAPP�Ĳ�ͬ��������������,APP�������ʱȡֵ��Χ[1,127]*/
#define OP_ID_GNA       9
#define OP_ID_SMS       2
#define OP_ID_PS        1
#define OP_ID_CS        0
#define OP_ID_PB        10
#define OP_ID_QUERY     7
#define OP_ID_SET       8
#define OP_ID_ERROR     13

#define APP_SUCCESS     0
#define APP_ERROR       1

#define TAF_SMS_SAVE_SM 0
#define TAF_SMS_SAVE_ME 1

/*****************************************************************************
   7 ��������
 *****************************************************************************/

extern  TAF_VOID Demo_Init(	TAF_VOID);

extern  TAF_VOID Demo_CsCallCallBack(   TAF_CS_CALL_EVENT_INFO_STRU *pEvent);
extern  TAF_VOID Demo_PhoneCallCallBack(TAF_PHONE_EVENT_INFO_STRU   *pEvent);

extern  TAF_VOID Demo_PhoneBookCallBack(TAF_PB_EVENT_INFO_STRU  *pEvent);

extern  TAF_VOID Demo_SatCallCallBack(  TAF_SAT_EVENT_INFO_STRU     *pEvent);

extern  TAF_VOID Demo_SmsCallCallBack(  TAF_UINT8                    ucLastReport,
                                        TAF_SMS_EVENT_INFO_STRU     *pEvent);

extern  TAF_VOID    Demo_SsCallCallBack(TAF_SS_CALL_INDEPENDENT_EVENT_STRU * pEvent);


extern  TAF_VOID Demo_DataIndCallBack(
                                        MN_CLIENT_ID_T      ClientId,
                                        TAF_UINT8           ucDomain,
                                        TAF_UINT8           ucRabId,
                                        TAF_UINT32          ulDataLen,
                                        TAF_UINT8          *pData);

extern  TAF_VOID Demo_DataStatusCallBack(
                                        MN_CLIENT_ID_T      ClientId,
                                        TAF_UINT8           ucDomain,
                                        TAF_UINT8           ucRabId,
                                        TAF_UINT8           ucStatus,
                                        TAF_UINT8           ucCause);

extern  TAF_VOID Demo_ParaSetResultCallback(
                                        MN_CLIENT_ID_T          ClientId,
                                        MN_OPERATION_ID_T       OpId,
                                        TAF_PARA_SET_RESULT     Result,
                                        TAF_PARA_TYPE           ParaType,
                                        TAF_VOID                *pPara);

extern  TAF_VOID Demo_ParaQueryReportCallback(
                                        MN_CLIENT_ID_T      ClientId,
                                        MN_OPERATION_ID_T   OpId,
                                        TAF_PARA_TYPE       ParaType,
                                        TAF_VOID           *pPara);

extern  TAF_VOID Demo_DsFlowReportCallBack(
                                        MN_CLIENT_ID_T      ClientId,
                                        TAF_UINT8           ucDomain,
                                        TAF_UINT8           ucRabId,
                                        TAF_DS_FLOW_REPORT_STRU *pDSFlowReport );

extern  TAF_VOID Demo_SmsParaSetErr(    TAF_PARA_SET_RESULT Result,
                                        TAF_PARA_TYPE       ParaType);

extern  TAF_VOID Demo_CsParaSetErr(     TAF_PARA_SET_RESULT Result,
                                        TAF_PARA_TYPE       ParaType);

extern  TAF_VOID Demo_PdpParaSetErr(    TAF_PARA_SET_RESULT Result,
                                        TAF_PARA_TYPE       ParaType);

extern  TAF_VOID Demo_PhParaSetErr(     TAF_PARA_SET_RESULT Result,
                                        TAF_PARA_TYPE       ParaType);

extern TAF_VOID    Demo_SatCallBackFunc(TAF_SAT_EVENT_INFO_STRU *pSatInfo );

extern TAF_VOID Demo_Taf_PhoneStart(          TAF_VOID );



#ifdef __cplusplus
   #if __cplusplus
   }
   #endif
#endif /* __cplusplus */


#endif /* __APP_API_REG_H__ */

