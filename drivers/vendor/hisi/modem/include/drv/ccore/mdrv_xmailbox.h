#ifndef __MDRV_CCORE_XMAILBOX_H__
#define __MDRV_CCORE_XMAILBOX_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <mdrv_mailbox.h>

typedef struct {
    unsigned int ulProtectWord;                  /* 0x5a5a5a5a,   ������             */
    unsigned int ulCphyMbxHpaUpAddr;             /* CPHY<->CCORE, HPA�������л���ַ  */
    unsigned int ulCphyMbxHpaDownAddr;           /* CPHY<->CCORE, HPA�������л���ַ  */
    unsigned int ulCphyMbxOmDownAddr;            /* CPHY<->CCORE, OM�������л���ַ   */
    unsigned int ulCphyMbxLoadMemAddr;           /* CPHY<->CCORE, ���ص�ַ           */
    unsigned int ulCphyMbxWorkModeAddr;          /* CPHY<->CCORE, ����ģʽ��ַ       */
} CPHY_CCORE_DYN_ADDR_SHARE_STRU;

typedef void (*BSP_xMBX_RCM_CALLBACK_FUNC)(MAILBOX_CALLBACK_TYPE e);
void BSP_xMailBox_Rcm_CallBackReg(BSP_xMBX_RCM_CALLBACK_FUNC pFunc);

typedef void (*BSP_xMBX_NOTIFY_FUNC)(MAILBOX_INT_TYPE_E enIntType);
typedef int (*BSP_xMBX_GET_STATUS_FUNC)(void);
typedef void (*BSP_xMBX_DSP_AWAKE_FUNC)(void);

/*****************************************************************************
 * Prototype      : BSP_xMailBox_ComMsgInit
 * Description    : ͨ������ĳ�ʼ��(�ṩ��Э��ջ���ã�
 *                  �ӿ��ڲ�ʵ����DSP������Ϣ�ĳ�ʼ��)
 * Input          : ulworkingmode
 * Return Value   : None
 ******************************************************************************/
void BSP_xMailBox_ComMsgInit(unsigned int ulworkingmode);

/*****************************************************************************
 * Prototype      : BSP_xMailBox_IsDspOk
 * Description    : ��DSP�����ֺ������ж�DSP�Ƿ��ʼ������
 *                  (�ṩ��Э��ջ���ã�������ֲ��ɹ���Э��ջ��Ҫѭ����ε���)
 * Input          : None
 * Return Value   : BSP_TRUE:   DSP��ʼ�����������ֳɹ�
 *                  BSP_FALSE:  DSPû�г�ʼ�����������ֲ��ɹ�
 ******************************************************************************/
int BSP_xMailBox_IsDspOk(void);

/*****************************************************************************
 * Prototype       : BSP_xMailBox_ComMsgWrite
 * Description     : ����д�ӿ�(ÿ��ֻ֧��дһ��ԭ��)
 * Input           : enMbxType    �����ҵ������
 *                   pData        ����ָ��
 *                   ulLen        ���ݳ���(���ֽ�Ϊ��λ)
 *                   enProcType   DSP˯��ʱ�Ĵ�������
 * Output          : None.
 * Return Value    : BSP_OK: �ɹ�
 *                     ����: ʧ��
 ******************************************************************************/
unsigned int BSP_xMailBox_ComMsgWrite(MAILBOX_SERVICE_TYPE_E enMbxType,
        void* pData,
        unsigned int ulLen,
        MAILBOX_SLEEP_PROC_E enProcType);

/*****************************************************************************
 * Prototype       : BSP_xMailBox_ComNotifyReg
 * Description     : �������ݵ���֪ͨע��ӿڣ���֡�жϼ�ʹû����ҲҪ�ص���
 * Param           : enMbxType        �����ҵ������
 *                   pFun             �������ݵ��ﴦ����
 * Return Value    : BSP_OK: �ɹ�
 *                   ERR_MAILBOX_NOT_INIT
 *                   ERR_MAILBOX_PARAM_INCORRECT
 ******************************************************************************/
unsigned int BSP_xMailBox_ComNotifyReg(MAILBOX_SERVICE_TYPE_E enMbxType,
        BSP_xMBX_NOTIFY_FUNC pFun);

/*****************************************************************************
 * Prototype       : BSP_xMailBox_ComMsgSize
 * Description     : ��ȡͨ�������е�һ��ԭ��ĳ���
 *                   (�ṩ���ϲ���ã��������ṩ������ԭ�������ӿڣ���Ҫ�ϲ�ѭ��
 *                    �����Ա����ϲ�©���ж�֪ͨʱ���������ԭ�ﻺ��)
 * Param           : enMbxType        �����ҵ������
 * Return Value    : 0:  û�л�ȡԭ�����Ϊ�գ������������͵�ԭ��δ���ߣ�
 *                   ����ֵ: �����һ��ԭ��ĳ���
 ******************************************************************************/
unsigned int BSP_xMailBox_ComMsgSize(MAILBOX_SERVICE_TYPE_E enMbxType);

/*****************************************************************************
 * Prototype       : BSP_xMailBox_ComMsgRead
 * Description     : ������ӿ�
 *                   (�˽ӿڻỽ��DSP����ҪBSP_MailBox_ComMsgSize���طǿ�ʱ����)
 * Param           : enMbxType    �����ҵ������
 *                   pData        ���յ����ݻ�����ָ��(�洢ԭ����Ϣ��������ԭ�ﳤ��)
 *                   ulLen        pData��������size(���ֽ�Ϊ��λ)
 *                   enProcType   DSP˯��ʱ�Ĵ�������
 * Return Value    : 0 : �ɹ�
 *                   ���� : ʧ��
 ******************************************************************************/
unsigned int BSP_xMailBox_ComMsgRead(MAILBOX_SERVICE_TYPE_E enMbxType,
                           void* pData,
                           unsigned int ulLen,
                           MAILBOX_SLEEP_PROC_E enProcType);

/*****************************************************************************
 * Prototype       : BSP_xMailbox_SetDtcmAddr
 * Description     : xģ�����ַ��ȡ�ӿ�
 * Param           : CPHY_CCORE_DYN_ADDR_SHARE_STRU    Xģ�����ַ�ṹ��
 * Return Value    : ��
 ******************************************************************************/

void BSP_xMailbox_SetDtcmAddr(CPHY_CCORE_DYN_ADDR_SHARE_STRU *addr);


/*****************************************************************************
 * Prototype       : BSP_xMailbox_ForbidDspSleep
 * Description     : ��ֹDSP˯�߽ӿ�
 * Input           : enProcType     DSP˯��ʱ�Ĵ�������
 *                   EN_MAILBOX_SLEEP_WAKEUP : ǿ�ƻ���ʱ���еȴ�����
 *                                             �������жϻص�������˲���
 *                                             ֻ��������������˲���
 *                   EN_MAILBOX_SLEEP_LOST   : �жϻص��������ж�������˲���
 * Return Value    : BSP_OK: �ɹ�,DSP��ǰû˯�ߣ��������ý�ֹDSP����˯��
 *                   ERR_MAILBOX_DSP_POWERDOWN : ������ΪEN_MAILBOX_SLEEP_LOST,
 *                                               DSP��ǰ���ڵ͹���״̬,����ʧ��
 *                   ERR_MAILBOX_TIMEOUT       : ������ΪEN_MAILBOX_SLEEP_WAKEUP,
 *                                               ����DSP��ʱ(10s)
 ******************************************************************************/
unsigned int BSP_xMailbox_ForbidDspSleep(MAILBOX_SLEEP_PROC_E enProcType);


/*****************************************************************************
 * Prototype       : BSP_xMailbox_AllowDspSleep
 * Description     : ����DSP˯�߽ӿ�
 * Input           : None
 * Return Value    : None
 ******************************************************************************/
void BSP_xMailbox_AllowDspSleep(void);

/*****************************************************************************
 * Prototype       : BSP_xMailBox_GetDspStatusReg
 * Description     : ��ȡDSP˯��״̬�ص�����ע��ӿڣ��͹���ģ�����
 * Param           : pFun             ��ȡDSP˯��״̬������
 * Return Value    : void
 ******************************************************************************/
void BSP_xMailBox_GetDspStatusReg(BSP_xMBX_GET_STATUS_FUNC pFun);

/*****************************************************************************
 * Prototype       : BSP_xMailBox_DspForceAwakeReg
 * Description     : DSPǿ�ƻ��ѻص�����ע��ӿڣ��͹���ģ�����
 * Param           : pFun             DSPǿ�ƻ��Ѵ�����
 * Return Value    : void
 ******************************************************************************/
void BSP_xMailBox_DspForceAwakeReg(BSP_xMBX_DSP_AWAKE_FUNC pFun);

/*****************************************************************************
 * Prototype       : BSP_xMailBox_DspAwakeProc
 * Description     : DSP���Ѻ�����䴦��ӿڣ��͹���ģ�����
 * Param           : void
 * Return Value    : void
 ******************************************************************************/
void BSP_xMailBox_DspAwakeProc(MAILBOX_CALLBACK_TYPE cbType);

/*****************************************************************************
 * Prototype       : BSP_xMailBox_IsAllowDspSleep
 * Description     : ��ѯ�Ƿ�����DSP˯�ߵĴ���ӿڣ��͹���ģ�����
 *                   ���ô˽ӿ�ʱ�͹���ģ�鱣֤DSPδ˯��
 *                   �˽ӿ�ֻ���PS�����ר�����䣬�����OM����(OMԭ����ʱ��Ҫ��)
 * Param           : void
 * Return Value    : int: TRUE-allow;FALSE-forbid
 ******************************************************************************/
int BSP_xMailBox_IsAllowDspSleep(void);

/*****************************************************************************
 * Prototype       : BSP_xMailboxAbnormalProc
 * Description     : �����쳣����
 *                   Э��ջ������Ϣ��ʱ����ô˽ӿڱ������������Ϣ
 *                   ��Э��ջ�̶���ǰ0.5K����Э��ջ��Ϣ����3.5K����������Ϣ
 * Input           : ucData       �����׵�ַ
 * Return Value    : NONE
 *****************************************************************************/
void BSP_xMailboxAbnormalProc(unsigned char *ucData);

/*****************************************************************************
 *  Prototype    : xMbx_ComPsPreProc
 *  Description  : PS�����Ԥ������(��Ҫ�����Ǹ���PS/CTBT��Ϣ������Ϣ)
 *                 1. ��������PS��Ϣ�������PS��Ϣ����
 *                 2. ��������CT/BT��Ϣ�������PS��Ϣ����
 *                 3. �������ж��е��ã����ܴ�ӡ��malloc
 *                 4. DSP��֤�����е�ԭ��δ����ʱ��˯��
 * Param         : None
 * Return Value  : void
 ******************************************************************************/
void xMbx_ComPsPreProc();

/*****************************************************************************
 *  Prototype    : xMbx_ComOmPreProc
 *  Description  : PS�����Ԥ������(��Ҫ�����Ǹ���PS/CTBT��Ϣ������Ϣ)
 *                 1. ��������PS��Ϣ�������PS��Ϣ����
 *                 2. ��������CT/BT��Ϣ�������PS��Ϣ����
 *                 3. �������ж��е��ã����ܴ�ӡ��malloc
 *                 4. DSP��֤�����е�ԭ��δ����ʱ��˯��
 * Param         : None
 * Return Value  : void
 ******************************************************************************/
void xMbx_ComOmPreProc();

#ifdef __cplusplus
}
#endif
#endif
