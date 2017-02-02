#ifndef __MDRV_CCORE_MAILBOX_H__
#define __MDRV_CCORE_MAILBOX_H__
#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum tagMAILBOX_INT_TYPE_E
    {
        EN_MAILBOX_INT_SUBFRAME = 0,        /* ��֡�ж� */
        EN_MAILBOX_INT_COM_IPC,             /* IPC�ж� */
        EN_MAILBOX_INT_SP_IPC,              /* ר������IPC�ж� */
        EN_MAILBOX_INT_BUTT
    }MAILBOX_INT_TYPE_E;

#if defined(CHIP_BB_HI6210)
    typedef enum tagMAILBOX_SERVICE_TYPE_E
    {
        EN_MAILBOX_SERVICE_LTE_PS = 0,      /* LTE PS���� */
        EN_MAILBOX_SERVICE_LTE_CT,          /* LTE CT���� */
        EN_MAILBOX_SERVICE_LTE_BT,          /* LTE BT���� */
        EN_MAILBOX_SERVICE_LTE_OM,          /* LTE OM�������� */
        EN_MAILBOX_SERVICE_LTE_COEX,        /* LTE WIFI coex */
        EN_MAILBOX_SERVICE_LTE_HS_DIAG,     /* LTE ��ά�ɲ�͹����������� */
        EN_MAILBOX_SERVICE_LTE_RCM,         /* LTE RCM���� */

        EN_MAILBOX_SERVICE_TDS_PS,          /* TDS PS���� */
        EN_MAILBOX_SERVICE_TDS_CT,          /* TDS CT���� */
        EN_MAILBOX_SERVICE_TDS_BT,          /* TDS BT���� */
        EN_MAILBOX_SERVICE_TDS_OM,          /* TDS OM�������� */
        EN_MAILBOX_SERVICE_TDS_HS_DIAG,     /* TDS ��ά�ɲ�͹����������� */
     	EN_MAILBOX_SERVICE_TDS_RCM,         /* TDS RCM���� */
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
        EN_MAILBOX_SERVICE_XSYS_RL,
        EN_MAILBOX_SERVICE_XSYS_OM,
        EN_MAILBOX_SERVICE_XSYS_BT,
        EN_MAILBOX_SERVICE_XSYS_CT,
        EN_MAILBOX_SERVICE_XSYS_HS_DIAG,
#endif
        EN_MAILBOX_SERVICE_RTT_SYS_CTRL,    /* DSP��ά�ɲ����ҵ�� */
        EN_MAILBOX_SERVICE_RTT_AGENT,       /* tlphy CHRҵ�� */
        EN_MAILBOX_SERVICE_RTT_CBT,         /* װ���ں� */

        EN_MAILBOX_SERVICE_RTT_HIFI_AGENT,  //for AMR voice relay between TPHY and HIFI;
                                                                           //add by jiangtao 00348559 on 2015.5.24

        EN_MAILBOX_SERVICE_BUTT
    }MAILBOX_SERVICE_TYPE_E;
#else
typedef enum tagMAILBOX_SERVICE_TYPE_E
    {
        EN_MAILBOX_SERVICE_LTE_PS = 0,      /* LTE PS���� */
        EN_MAILBOX_SERVICE_LTE_CT,          /* LTE CT���� */
        EN_MAILBOX_SERVICE_LTE_BT,          /* LTE BT���� */
        EN_MAILBOX_SERVICE_LTE_OM,          /* LTE OM�������� */
        EN_MAILBOX_SERVICE_LTE_COEX,        /* LTE WIFI coex */
        EN_MAILBOX_SERVICE_LTE_HS_DIAG,     /* LTE ��ά�ɲ�͹����������� */
        EN_MAILBOX_SERVICE_LTE_RCM,         /* LTE RCM���� */

        EN_MAILBOX_SERVICE_TDS_PS,          /* TDS PS���� */
        EN_MAILBOX_SERVICE_TDS_CT,          /* TDS CT���� */
        EN_MAILBOX_SERVICE_TDS_BT,          /* TDS BT���� */
        EN_MAILBOX_SERVICE_TDS_OM,          /* TDS OM�������� */
        EN_MAILBOX_SERVICE_TDS_HS_DIAG,     /* TDS ��ά�ɲ�͹����������� */
     	EN_MAILBOX_SERVICE_TDS_RCM,         /* TDS RCM���� */

        EN_MAILBOX_SERVICE_RTT_SYS_CTRL,    /* DSP��ά�ɲ����ҵ�� */
        EN_MAILBOX_SERVICE_RTT_AGENT,       /* tlphy CHRҵ�� */
		EN_MAILBOX_SERVICE_RTT_CBT,         /* tlphy CBTҵ�� */
		EN_MAILBOX_SERVICE_RTT_HIFI_AGENT,  /* for AMR voice relay between TPHY and HIFI */

        EN_MAILBOX_SERVICE_BUTT,

        EN_MAILBOX_SERVICE_XSYS_RL = EN_MAILBOX_SERVICE_BUTT,
        EN_MAILBOX_SERVICE_XSYS_OM,
        EN_MAILBOX_SERVICE_XSYS_BT,
        EN_MAILBOX_SERVICE_XSYS_CT,
        EN_MAILBOX_SERVICE_XSYS_HS_DIAG,

        EN_MAILBOX_SERVICE_TOTAL_BUTT
    }MAILBOX_SERVICE_TYPE_E;

#endif

    typedef enum tagMAILBOX_SLEEP_PROC_E
    {
        EN_MAILBOX_SLEEP_WAKEUP = 0,        /* ǿ�ƻ���DSP�������� */
        EN_MAILBOX_SLEEP_LOST,              /* DSP����˯��ģʽʱ���������� */
        EN_MAILBOX_SLEEP_DIRECT,            /* ���ж�DSP״̬��ֱ��д���� ����*/
        EN_MAILBOX_SLEEP_BUTT
    }MAILBOX_SLEEP_PROC_E;

    typedef enum tagMAILBOX_ERRORCODE_E
    {
        ERR_MAILBOX_NOT_INIT = 1,           /* δ��ʼ�� */
        ERR_MAILBOX_PARAM_INCORRECT,        /* �������� */
        ERR_MAILBOX_MEMORY_NOTENOUGH,       /* �ռ䲻�� */
        ERR_MAILBOX_TIMEOUT,                /* ��ʱ */
        ERR_MAILBOX_COVER,                  /* ר������д����ʱԭ��δ���ߣ�ִ�и��ǲ��� */
        ERR_MAILBOX_WRITE_FAILED,           /* ����дʧ�� */
        ERR_MAILBOX_READ_FAILED,            /* �����ʧ�� */
        ERR_MAILBOX_READ_NULL,              /* �����������Ϣ */
        ERR_MAILBOX_DSP_POWERDOWN,          /* DSP���ڵ͹���״̬ */
        ERR_MAILBOX_OTHER,                  /* �������� */
        ERR_MAILBOX_ERRORCODE_BUTT
    }MAILBOX_ERRORCODE_E;
	typedef enum tagMAILBOX_CALLBACK_TYPE_E
	{
        EN_MAILBOX_CALLBACK_DSP_RUN = 0,        /*DSP RUN CALLBACK*/
        EN_MAILBOX_CALLBACK_DSP_RESUME,         /*DSP RESUME IRQ CALLBACK*/
        EN_MAILBOX_CALLBACK_DSP_BUTT
	}MAILBOX_CALLBACK_TYPE;
	typedef void (*BSP_MBX_RCM_CALLBACK_FUNC)(MAILBOX_CALLBACK_TYPE e);
	void BSP_MailBox_Rcm_CallBackReg(BSP_MBX_RCM_CALLBACK_FUNC pFunc);

    typedef void (*BSP_MBX_NOTIFY_FUNC)(MAILBOX_INT_TYPE_E enIntType);
    typedef int (*BSP_MBX_GET_STATUS_FUNC)(void);
    typedef void (*BSP_MBX_DSP_AWAKE_FUNC)(void);

    /*****************************************************************************
     * Prototype      : BSP_MailBox_ComMsgInit
     * Description    : ͨ������ĳ�ʼ��(�ṩ��Э��ջ���ã�
     *                  �ӿ��ڲ�ʵ����DSP������Ϣ�ĳ�ʼ��)
     * Input          : ulworkingmode
     * Return Value   : None
     ******************************************************************************/
    void BSP_MailBox_ComMsgInit(unsigned int ulworkingmode);

    /*****************************************************************************
     * Prototype      : BSP_MailBox_IsDspOk
     * Description    : ��DSP�����ֺ������ж�DSP�Ƿ��ʼ������
     *                  (�ṩ��Э��ջ���ã�������ֲ��ɹ���Э��ջ��Ҫѭ����ε���)
     * Input          : None
     * Return Value   : BSP_TRUE:   DSP��ʼ�����������ֳɹ�
     *                  BSP_FALSE:  DSPû�г�ʼ�����������ֲ��ɹ�
     ******************************************************************************/
    int BSP_MailBox_IsDspOk(void);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_IntTypeSet
     * Description     : ����PS�����ж�Դ�ӿ�(Ĭ��IPC�жϷ�ʽ)
     *                   ֻ����PS���䣬OM�������ж��ϱ�
     * Param           : None
     * Return Value    : 0: �ɹ�; ����: ���õ�type�Ƿ�
     ******************************************************************************/
    unsigned int BSP_MailBox_IntTypeSet(MAILBOX_INT_TYPE_E enIntType);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_ComMsgWrite
     * Description     : ����д�ӿ�(ÿ��ֻ֧��дһ��ԭ��)
     * Input           : enMbxType    �����ҵ������
     *                   pData        ����ָ��
     *                   ulLen        ���ݳ���(���ֽ�Ϊ��λ)
     *                   enProcType   DSP˯��ʱ�Ĵ�������
     * Output          : None.
     * Return Value    : BSP_OK: �ɹ�
     *                     ����: ʧ��
     ******************************************************************************/
    unsigned int BSP_MailBox_ComMsgWrite(MAILBOX_SERVICE_TYPE_E enMbxType,
            void* pData,
            unsigned int ulLen,
            MAILBOX_SLEEP_PROC_E enProcType);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_ComNotifyReg
     * Description     : �������ݵ���֪ͨע��ӿڣ���֡�жϼ�ʹû����ҲҪ�ص���
     * Param           : enMbxType        �����ҵ������
     *                   pFun             �������ݵ��ﴦ����
     * Return Value    : BSP_OK: �ɹ�
     *                   ERR_MAILBOX_NOT_INIT
     *                   ERR_MAILBOX_PARAM_INCORRECT
     ******************************************************************************/
    unsigned int BSP_MailBox_ComNotifyReg(MAILBOX_SERVICE_TYPE_E enMbxType,
            BSP_MBX_NOTIFY_FUNC pFun);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_ComMsgSize
     * Description     : ��ȡͨ�������е�һ��ԭ��ĳ���
     *                   (�ṩ���ϲ���ã��������ṩ������ԭ�������ӿڣ���Ҫ�ϲ�ѭ��
     *                    �����Ա����ϲ�©���ж�֪ͨʱ���������ԭ�ﻺ��)
     * Param           : enMbxType        �����ҵ������
     * Return Value    : 0:  û�л�ȡԭ�����Ϊ�գ������������͵�ԭ��δ���ߣ�
     *                   ����ֵ: �����һ��ԭ��ĳ���
     ******************************************************************************/
    unsigned int BSP_MailBox_ComMsgSize(MAILBOX_SERVICE_TYPE_E enMbxType);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_ComMsgRead
     * Description     : ������ӿ�
     *                   (�˽ӿڻỽ��DSP����ҪBSP_MailBox_ComMsgSize���طǿ�ʱ����)
     * Param           : enMbxType    �����ҵ������
     *                   pData        ���յ����ݻ�����ָ��(�洢ԭ����Ϣ��������ԭ�ﳤ��)
     *                   ulLen        pData��������size(���ֽ�Ϊ��λ)
     *                   enProcType   DSP˯��ʱ�Ĵ�������
     * Return Value    : 0 : �ɹ�
     *                   ���� : ʧ��
     ******************************************************************************/
    unsigned int BSP_MailBox_ComMsgRead(MAILBOX_SERVICE_TYPE_E enMbxType,
                               void* pData,
                               unsigned int ulLen,
                               MAILBOX_SLEEP_PROC_E enProcType);

    /*****************************************************************************
     * Prototype      : BSP_MailBox_SpULMsgHeadInit
     * Description    : ר�У�Special Mailbox�������������Ϣͷ��ʼ���ӿ�
     *                  (��ʼ����������ÿ��ԭ�����Ϣͷ���ṩ��Э��ջ����Ҫ���ö��
     *                   �ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
     * Input          :
     *                  ulAddr : ר������ĵ�ַ
     *                  ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
     *                  ucData : ��ʼֵ
     * Return Value   : None
     ******************************************************************************/
    void BSP_MailBox_SpULMsgHeadInit(unsigned int ulAddr, unsigned int ulSize, unsigned char ucData);

    /*****************************************************************************
     * Prototype      : BSP_MailBox_SpDLMsgHeadInit
     * Description    : ר�У�Special Mailbox�������������Ϣͷ��ʼ���ӿ�
     *                  (��ʼ����������ÿ��ԭ�����Ϣͷ���ṩ��Э��ջ����Ҫ���ö��
     *                   �ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
     * Input          :
     *                  ulAddr : ר������ĵ�ַ
     *                  ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
     *                  ucData : ��ʼֵ
     * Return Value   : None
     ******************************************************************************/
    void BSP_MailBox_SpDLMsgHeadInit(unsigned int ulAddr, unsigned int ulSize, unsigned char ucData);

    /*****************************************************************************
     * Prototype      : BSP_MailBox_SpMsgWrite
     * Description    : ר�����䣨Special Mailbox����д�ӿ�
     *                  (�ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
     * Input          :
     *                  ulAddr : ר�������ƫ�Ƶ�ַ������Ϣͷ��ʼ�ĵ�ַ��
     *                  ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
     *                  pData  : ������Ϣ(��������Ϣͷ��Ϣ)
     * Return Value   :
     *                  BSP_OK: ��ʾ�����ɹ�
     *                  ERR_MAILBOX_COVER: ��ʾǰһ��ԭ��δ�����ߣ�����
     *                  ERR_MAILBOX_WRITE_FAILED: дʧ��
     *                  ERR_MAILBOX_NOT_INIT: ����δ��ʼ��
     *                  ERR_MAILBOX_PARAM_INCORRECT: ��������
     ******************************************************************************/
    unsigned int BSP_MailBox_SpMsgWrite(unsigned int ulAddr, unsigned int ulSize, void* pData);

    /*****************************************************************************
     * Prototype      : BSP_MailBox_SpMsgRead
     * Description    : ר�����䣨Special Mailbox���Ķ��ӿ�
     *                  (�ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
     * Input          :
     *                  ulAddr : ר�������ƫ�Ƶ�ַ������Ϣͷ��ʼ�ĵ�ַ��
     *                  ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
     *                  pData  : ������Ϣ(��������Ϣͷ��Ϣ)
     * Return Value   :
     *                  BSP_OK: ��ȡ�ɹ�
     *                  ERR_MAILBOX_READ_NULL: ������
     *                  ERR_MAILBOX_NOT_INIT: ����δ��ʼ��
     *                  ERR_MAILBOX_PARAM_INCORRECT: ��������
     ******************************************************************************/
    unsigned int BSP_MailBox_SpMsgRead(unsigned int ulAddr, unsigned int ulSize, void* pData);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_SpNotifyReg
     * Description     : ר���������ݵ���֪ͨע��ӿ�
     * Param           : pFun             �������ݵ��ﴦ����
     * Return Value    : BSP_OK: �ɹ�
     *                     ����: ʧ��
     ******************************************************************************/
    unsigned int BSP_MailBox_SpNotifyReg(BSP_MBX_NOTIFY_FUNC pFun);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_SpNotifyEnable
     * Description     : ר���������ݵ���֪ͨ�ж�ʹ�ܽӿ�
     * Param           : None
     * Return Value    : void
     ******************************************************************************/
    void BSP_MailBox_SpNotifyEnable(void);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_SpNotifyDisable
     * Description     : ר���������ݵ���֪ͨ�ж�ȥʹ�ܽӿ�
     * Param           : None
     * Return Value    : void
     ******************************************************************************/
    void BSP_MailBox_SpNotifyDisable(void);

    /*****************************************************************************
     * Prototype       : BSP_Mailbox_ForbidDspSleep
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
    unsigned int BSP_Mailbox_ForbidDspSleep(MAILBOX_SLEEP_PROC_E enProcType);


    /*****************************************************************************
     * Prototype       : BSP_Mailbox_AllowDspSleep
     * Description     : ����DSP˯�߽ӿ�
     * Input           : None
     * Return Value    : None
     ******************************************************************************/
    void BSP_Mailbox_AllowDspSleep(void);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_GetDspStatusReg
     * Description     : ��ȡDSP˯��״̬�ص�����ע��ӿڣ��͹���ģ�����
     * Param           : pFun             ��ȡDSP˯��״̬������
     * Return Value    : void
     ******************************************************************************/
    void BSP_MailBox_GetDspStatusReg(BSP_MBX_GET_STATUS_FUNC pFun);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_DspForceAwakeReg
     * Description     : DSPǿ�ƻ��ѻص�����ע��ӿڣ��͹���ģ�����
     * Param           : pFun             DSPǿ�ƻ��Ѵ�����
     * Return Value    : void
     ******************************************************************************/
    void BSP_MailBox_DspForceAwakeReg(BSP_MBX_DSP_AWAKE_FUNC pFun);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_GetSpMsgStatusReg
     * Description     : ��ȡר����������DSP˯��״̬�ص�����ע��ӿڣ�PS����
     * Param           : pFun             ��ȡDSP˯��״̬������
     * Return Value    : void
     ******************************************************************************/
    void BSP_MailBox_GetSpMsgStatusReg(BSP_MBX_GET_STATUS_FUNC pFun);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_DspAwakeProc
     * Description     : DSP���Ѻ�����䴦��ӿڣ��͹���ģ�����
     * Param           : void
     * Return Value    : void
     ******************************************************************************/
    void BSP_MailBox_DspAwakeProc(MAILBOX_CALLBACK_TYPE cbType);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_IsAllowDspSleep
     * Description     : ��ѯ�Ƿ�����DSP˯�ߵĴ���ӿڣ��͹���ģ�����
     *                   ���ô˽ӿ�ʱ�͹���ģ�鱣֤DSPδ˯��
     *                   �˽ӿ�ֻ���PS�����ר�����䣬�����OM����(OMԭ����ʱ��Ҫ��)
     * Param           : void
     * Return Value    : int: TRUE-allow;FALSE-forbid
     ******************************************************************************/
    int BSP_MailBox_IsAllowDspSleep(void);

    /*****************************************************************************
     * Prototype       : BSP_UniMailboxWrite
     * Description     : �����ͨ��д�ӿ�(�ɵ����߱�֤����ĵ�ַ�ĺϷ���)
     *                   ���ӿ�ʵ������memcpy����������
     *                   �ӿ��ڲ���֤DSP�Ļ��Ѳ������������ʧ�ܣ�����ERR_MAILBOX_TIMEOUT
     * Return Value    :
     *                   BSP_OK
     *                   ERR_MAILBOX_PARAM_INCORRECT
     *                   ERR_MAILBOX_TIMEOUT
     ******************************************************************************/
    unsigned int BSP_UniMailboxWrite(void *pDst, void *pSrc, unsigned int ulLen);

    /*****************************************************************************
     * Prototype       : BSP_MailboxAbnormalProc
     * Description     : �����쳣����
     *                   Э��ջ������Ϣ��ʱ����ô˽ӿڱ������������Ϣ
     *                   ��Э��ջ�̶���ǰ0.5K����Э��ջ��Ϣ����3.5K����������Ϣ
     * Input           : ucData       �����׵�ַ
     * Return Value    : NONE
     *****************************************************************************/
    void BSP_MailboxAbnormalProc(unsigned char *ucData);

    /*****************************************************************************
     *  Prototype    : Mbx_ComPsPreProc
     *  Description  : PS�����Ԥ������(��Ҫ�����Ǹ���PS/CTBT��Ϣ������Ϣ)
     *                 1. ��������PS��Ϣ�������PS��Ϣ����
     *                 2. ��������CT/BT��Ϣ�������PS��Ϣ����
     *                 3. �������ж��е��ã����ܴ�ӡ��malloc
     *                 4. DSP��֤�����е�ԭ��δ����ʱ��˯��
     * Param         : None
     * Return Value  : void
     ******************************************************************************/
    void Mbx_ComPsPreProc();

    /*****************************************************************************
     *  Prototype    : Mbx_ComOmPreProc
     *  Description  : PS�����Ԥ������(��Ҫ�����Ǹ���PS/CTBT��Ϣ������Ϣ)
     *                 1. ��������PS��Ϣ�������PS��Ϣ����
     *                 2. ��������CT/BT��Ϣ�������PS��Ϣ����
     *                 3. �������ж��е��ã����ܴ�ӡ��malloc
     *                 4. DSP��֤�����е�ԭ��δ����ʱ��˯��
     * Param         : None
     * Return Value  : void
     ******************************************************************************/
    void Mbx_ComOmPreProc();
#ifdef __cplusplus
}
#endif
#endif
