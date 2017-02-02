/**
 * @file sre_tskmon.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������������ģ��Ķ���ͷ�ļ��� \n
 */

/**
 *@defgroup SRE_tskmon ������
 *@ingroup SRE_kernel
 */

#ifndef _SRE_TSKMON_H
#define _SRE_TSKMON_H

#include "sre_base.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif/* __cpluscplus */
#endif /* __cpluscplus */

//֧�ֹ��ܺ�ü�,sre_buildef.h�ļ���֧�ֵĹ��ܺ�
#if (OS_OPTION_TASK_MON == YES) 

/* =================================������ģ�鳣������============================== */
/**
 *@ingroup SRE_tskmon
 *������������ID
 */
#define  OS_TSK_ALL                  0xFFFFFFFF

/**
 *@ingroup SRE_tskmon
 *��������ģʽ���ϱ���������
 */
#define  OS_TSKMON_MODE_REPORT_ERROR 0x01

/**
 *@ingroup SRE_tskmon
 *��������ģʽ����������
 */
#define  OS_TSKMON_MODE_REAVE        0x02

/**
 *@ingroup SRE_tskmon
 *��Ϣ����:�������
 */
#define TSKMON_INFO_TYPE_OVERRUN     0x01

/**
 *@ingroup SRE_tskmon
 *��Ϣ����:�������
 */
#define TSKMON_INFO_TYPE_STRVATION   0x02

/**
 *@ingroup SRE_tskmon
 *��Чָ��
 */
#define OS_INVALID_HOOK              NULL

/* =================================������ģ������붨��============================== */
/**
 *@ingroup SRE_tskmon
 *��ʼ��ʱ�����ڴ�ʧ��
 *
 * ֵ: 0x02000830
 *
 *�������:���������ģ����Ӧ����
 */
#define OS_ERRNO_TSKMON_NO_MEMORY        SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x30)

/**
 *@ingroup SRE_tskmon
 *������⹦��δ����
 *
 * ֵ: 0x02000831
 *
 *�������:���������ģ����Ӧ����
 */
#define OS_ERRNO_TSK_OVERRUN_UNINSTALL   SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x31)

/**
 *@ingroup SRE_tskmon
 *������⹦��δ����
 *
 * ֵ: 0x02000832
 *
 *�������:��
 */
#define OS_ERRNO_TSK_STRVATION_UNINSTALL SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x32)

/**@ingroup SRE_tskmon
 *�Ѿ������˳���������
 *
 * ֵ: 0x02000833
 *
 *�������:��
 */
#define OS_ERRNO_TSK_OVERRUNCK_EXIST     SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x33)

/**@ingroup SRE_tskmon
 *δ����������
 *
 * ֵ: 0x02000834
 *
 *�������:��
 */
#define OS_ERRNO_TSK_OVERRUNCK_UNEXIST   SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x34)

/**@ingroup SRE_tskmon
 *�Ѿ������˶���������
 *
 * ֵ: 0x02000835
 *
 *�������:��
 */
#define OS_ERRNO_TSK_STRVATIONCK_EXIST   SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x35)

/**@ingroup SRE_tskmon
 *δ����������
 *
 * ֵ: 0x02000836
 *
 *�������:��
 */
#define OS_ERRNO_TSK_STRVATIONCK_UNEXIST SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x36)

/**@ingroup SRE_tskmon
 *����������𣬲�����ȡ�����
 *
 * ֵ: 0x02000837
 *
 *�������:��
 */
#define OS_ERRNO_TSK_OVERRUN_SUPPEND     SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x37)

/**@ingroup SRE_tskmon
 *����������û����ô���ʽΪ�ϱ���������
 *
 * ֵ: 0x03000838
 *
 *�������:��
 */
#define OS_ERRNO_TSK_OVERRUN             SRE_ERRNO_OS_FATAL(OS_MID_TSK,0x38)


/* =================================������ģ�����ݽṹ���Ͷ���============================== */
/**@ingroup SRE_tskmon
 *������ѭ�����������Ϣ���ݽṹ���Ͷ���
 */
typedef struct tagTskMonModInfo
{
    UINT32 uwThresHold;                                    /**< ��ֵ����tickΪ��λ�� */
    UINT32 uwProcType;                                     /**< ����ģʽ */
} TSKMON_MOD_INFO_S;

/**@ingroup SRE_tskmon
 * ������ѭ�������Ϣ���ݽṹ����
 */
typedef struct tagTskMonInfo
{
    UINT32 uwTaskPID;                                      /**< ����PID*/
    UINT16 usSize;                                         /**< ��Ϣ����*/
    UINT16 usType;                                         /**< ��Ϣ����*/
    UINT32 uwTickCnt;                                      /**< ��������ʱ��*/
}TSKMON_INFO_S;

/**
 * @ingroup  SRE_tskmon
 * @brief �����ػص��������Ͷ���
 *
 * @par ����:
 * ͨ�������ػص��������Ͷ��������ػص������������ڳ����Ͷ���ʱ���øù��ӽ��д���
 *
 * @attention
 * ��
 *
 * @param  para   [IN] ����#TSKMON_INFO_S*��������ѭ�������Ϣ��
 *
 * @retval �ޡ�
 * @par ����:
 * <ul><li>sre_tskmon.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since UniDSP V100R001C02
 * @see �ޡ�
 */
typedef VOID (*TSKMON_HOOK_FUNC)(TSKMON_INFO_S*);

/* =================================������ģ��ӿ����Ͷ���============================== */

/**
 * @ingroup  SRE_tskmon
 * @brief �������������
 *
 * @par ����:
 * �趨ָ������ļ�ؿ��ƿ������־���Ѹ�������������⡣�������ΪOS_TSK_ALL��ʾ�������񶼼��������⡣
 *
 * @attention  ��
 *
 * @param  uwTaskPID   [IN] ����#UINT32������PID��
 *
 * @retval #SRE_OK                              0x00000000��ע��ɹ�
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814�������PIDΪIDLE����PID
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������ID��Ч
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080A������δ����
 * @retval #OS_ERRNO_TSK_OVERRUNCK_EXIST        0x02000833�������Ѿ����������⣬�������ظ�����
 * @retval #OS_ERRNO_TSK_OVERRUN_UNINSTALL      0x02000831���������ü�����δ��,�������δ����
 * @par ����:
 * <ul><li>sre_tskmon.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since UniDSP V100R001C02
 * @see SRE_TskMonOverrunExclude
 */
extern UINT32 SRE_TskMonOverrunInclude(UINT32 uwTaskPID);

/**
 * @ingroup  SRE_tskmon
 * @brief ȡ������������
 *
 * @par ����:
 * ��������ؿ��ƿ�ĳ�����־��ȡ���Ը����������⡣�������ΪOS_TSK_ALL��ʾȡ����������ĳ�����⡣
 *
 * @attention  ��
 *
 * @param  uwTaskPID   [IN] ����#UINT32������PID��
 *
 * @retval #SRE_OK                              0x00000000��ע��ɹ�
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814�������PIDΪIDLE����PID
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������ID��Ч
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080A������δ����
 * @retval #OS_ERRNO_TSK_OVERRUNCK_UNEXIST      0x02000834������δ�������⣬������ȡ������
 * @retval #OS_ERRNO_TSK_OVERRUN_UNINSTALL      0x02000831���������ü�����δ�򿪣��������δ����
 * @retval #OS_ERRNO_TSK_OVERRUN_SUPPEND        0x02000837, ���������������ȡ�����
 * @par ����:
 * <ul><li>sre_tskmon.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since UniDSP V100R001C02
 * @see SRE_TskMonOverrunInclude
 */
extern UINT32 SRE_TskMonOverrunExclude(UINT32 uwTaskPID);

/**
 * @ingroup  SRE_tskmon
 * @brief �������������
 *
 * @par ����:
 * �趨ָ������ļ�ؿ��ƿ������־���Ѹ�������������⡣�������ΪOS_TSK_ALL��ʾ�������񶼼��������⡣
 *
 * @attention  ��
 *
 * @param  uwTaskPID   [IN] ����#UINT32������PID��
 *
 * @retval #SRE_OK                              0x00000000��ע��ɹ�
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814�������PIDΪIDLE����PID
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID��Ч
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080A������δ����
 * @retval #OS_ERRNO_TSK_STRVATIONCK_EXIST      0x02000835�������Ѿ�����������
 * @retval #OS_ERRNO_TSK_STRVATION_UNINSTALL    0x02000832���������ü�����δ�򿪣��������δ����
 * @par ����:
 * <ul><li>sre_tskmon.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since UniDSP V100R001C02
 * @see SRE_TskMonStrvationExclude
 */
extern UINT32 SRE_TskMonStrvationInclude(UINT32 uwTaskPID);

/**
 * @ingroup  SRE_tskmon
 * @brief ����ȡ���������
 *
 * @par ����:
 * ��������ؿ��ƿ�Ķ�����־��ȡ���Ը����������⡣�������ΪOS_TSK_ALL��ʾȡ����������Ķ�����⡣
 *
 * @attention  ��
 *
 * @param  uwTaskPID   [IN] ����#UINT32������PID��
 *
 * @retval #SRE_OK                              0x00000000��ע��ɹ�
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814�������PIDΪIDLE����PID
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID��Ч
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080A������δ����
 * @retval #OS_ERRNO_TSK_STRVATIONCK_UNEXIST    0x02000836������δ����������
 * @retval #OS_ERRNO_TSK_STRVATION_UNINSTALL    0x02000832���������ü�����δ�򿪣����������δ����
 * @par ����:
 * <ul><li>sre_tskmon.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since UniDSP V100R001C02
 * @see SRE_TskMonStrvationInclude
 */
extern UINT32 SRE_TskMonStrvationExclude(UINT32 uwTaskPID);

/**
 * @ingroup  SRE_tskmon
 * @brief ע�������صļ����Ϣ�ص�������
 *
 * @par ����:
 * ע����������Ϣ�ص�����������⵽������������ʱ��ϵͳͨ���ص�������֪�û���<br/>
 * @attention
 * <ul>
 * <li>��ע��Ļص������У���Ҫ��������������������Ӱ�쵽ϵͳ������������ȡ�</li>
 * </ul>
 *
 * @param  pfnHook         [IN] ����#TSKMON_HOOK_FUNC��������ص���������ΪNULL����ʾ����ص����ӡ�
 *
 * @retval #SRE_OK                          0x00000000��ע��ɹ�
 * @par ����:
 * <ul><li>sre_tskmon.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since UniDSP V100R001C02
 * @see ��
 */
extern UINT32 SRE_TskMonHookReg(TSKMON_HOOK_FUNC  pfnHook);

#endif //if (OS_OPTION_TASK_MON == YES) 

#ifdef __cplusplus
 #if __cplusplus
}
 #endif/* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_TSKMON_H */

