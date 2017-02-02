/**
 * @file sre_timer.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ��������ʱ��ģ��Ķ���ͷ�ļ��� \n
 */

/** @defgroup sre_timer ��ʱ��
 *@ingroup SRE_kernel
 */

#ifndef _SRE_TIMER_H
#define _SRE_TIMER_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/**
 * @ingroup sre_timer
 * ��ʱ���������
 */
typedef UINT32  TIMER_HANDLE_T;

/**
 * @ingroup sre_timer
 * ��ʱ����������
 */
typedef UINT32  TIMER_GROUPID_T;

/**
 * @ingroup sre_timer
 * ��ʱ����ʱ���ֻص��������Ͷ���
 */
typedef VOID (* TMR_WHEEL_PROC_FUNC)(VOID);

/**
 * @ingroup sre_timer
 * ��ʱ���ص��������壬��5������������ֵ����Ϊvoid�ĺ���ָ�����ͣ����в���uwTmrHandle�ں���Ӳ����ʱ����ȫ��Ӳ����ʱ���������ʱ���зֱ��ʾ�߼�ID������ID���߼�ID��
 */
typedef VOID (* SRE_TMR_PROC_FUNC)(TIMER_HANDLE_T uwTmrHandle, UINT32 uwArg1, UINT32 uwArg2, UINT32 uwArg3, UINT32 uwArg4);


/**
 * @ingroup sre_timer
 * ��ʱ����ʱ��Դ����ö�ٶ���
 */
typedef enum tagTimerGrpSrcType
{
    SRE_TIMER_GRP_SRC_HARDWARE,                   /**< Ӳ��˽��ʱ��Դ     */
    SRE_TIMER_GRP_SRC_HARDWARE_SHARED,            /**< Ӳ������ʱ��Դ     */
    SRE_TIMER_GRP_SRC_EXTERN,                     /**< �ⲿʱ��Դ         */
    SRE_TIMER_GRP_SRC_TICK,                       /**< TICKʱ��Դ         */
    SRE_TIMER_GRP_SRC_INVALID
}TIMER_GRP_SRC_TYPE_E;


/**
 * @ingroup sre_timer
 * ��ʱ�����û����ýṹ��
 */
typedef struct tagTmrGrpUserCfg
{
    TIMER_GRP_SRC_TYPE_E    enTmrGrpSrcType;  /**< ʱ��Դ����                                */
    UINT32                  uwUsPerStep;      /**< ʱ���ֵĿ̶ȣ���ÿ�̶ȶ��ٸ�us            */
    UINT32                  uwMaxTimerNum;    /**< ���ʱ������                            */
    UINT32                  uwWheelLen2Power; /**< ʱ���ֳ��ȱ�����2��N�η����˴�����N�Ĵ�С */
    UINT32                  uwSwiPrio;        /**< ʹ�õ����ж����ȼ�����ǰ��Ч              */
    TMR_WHEEL_PROC_FUNC     pfnWheelFunc;     /**< ��ʱ����ʱ��Դ������ÿ��һ���ֵ���һ��    */
}SRE_TMR_GRP_USER_CFG_S;

/**
 * @ingroup sre_timer
 * ȫ�ֶ�ʱ��ģ��������Ϣ�Ľṹ�嶨�塣
 *
 * ����ȫ�ֶ�ʱ��ģ�����������Ϣ��
 */
typedef struct tagMcHwtmrModInfo
{
    UINT32 uwMcHwtmrClock;                   /**< ����Ӳ����ʱ��ʱ��Ƶ�� */
} MCHW_TIMER_INFO_S;

/**
 * @ingroup sre_timer
 * ��ʱ������ģʽö�ٶ���
 */
typedef enum tagTmrMode
{
    SRE_TIMER_LOOP,                                     /**< ��ʱ�����ڴ���ģʽ*/
    SRE_TIMER_ONCE,                                     /**< ��ʱ�����δ���ģʽ*/
    SRE_TIMER_INVALID_MODE
}TIMER_MODE_E;

/**
 * @ingroup sre_timer
 * ��ʱ������ö�ٶ���
 */
typedef enum tagTimerType
{
    SRE_TIMER_HARDWARE,                               /**< Ӳ����ʱ��(����˽��Ӳ����ʱ��)         */
    SRE_TIMER_HARDWARE_SHARED,                        /**< ����Ӳ����ʱ��,��SD6182��SD6157��SD6183֧��(���к˹��������ȫ�ֶ�ʱ��)  */
    SRE_TIMER_SOFTWARE,                               /**< �����ʱ��(����˽�������ʱ��)         */
    SRE_TIMER_SOFTWARE_SHARED,                        /**< ���������ʱ�����ݲ�֧��     */
    SRE_TIMER_SOFTWARE_QUERY,                         /**< ��ѯ�����ʱ�����ݲ�֧��     */
    SRE_TIMER_INVALID_TYPE
}TIMER_TYPE_E;

/**
 * @ingroup sre_timer
 * ��ʱ�����������ṹ�嶨��
 */
typedef struct tagTIMER_CREATE_PARA
{
    UINT32              uwModuleId;                     /**< ��ʱ������ģ��ID,��ǰδʹ�ã�����   */
    TIMER_TYPE_E        enType;                         /**< ��ʱ������         */
    TIMER_MODE_E        enMode;                         /**< ��ʱ������ģʽ     */
    UINT32              uwInterval;                     /**< ��ʱ������(����ָ��ʱ����Ӧʱ��)�������ʱ����λ��ms��Ӳ����ʱ����λ��us*/
    UINT32              uwTimerGroupId;                 /**< ��ʱ����ţ�ֻ�������ʱ��ʹ�ã�Ӳ����ʱ����ʹ�ã������������ʱ������ʱ����ID��OS�������û����������OS_TICK_SWTMR_GRPID��ȫ�ֱ���g_uwTickSwTmrGroupID*/
    UINT16              usHwiPrio;                      /**< ��ʱ��Ӳ�ж����ȼ���Tensinicaƽ̨��Ч��SD6183ƽ̨��Ч(��ʾӲ����ʱ����ӦӲ�жϵ����ȼ�)�� */
    UINT16              usTimerIdx;                     /**< ȫ�ֶ�ʱ����������ȫ��Ӳ����ʱ��ʹ�ã���ΧΪ0-7*/
    SRE_TMR_PROC_FUNC   pCallBackFunc;                  /**< ��ʱ���ص�������SD6182/SD6157ƽ̨ȫ��Ӳ����ʱ�����ӱ���ΪNULL    */
    UINT32              uwArg1;                         /**< ��ʱ���û�����1     */
    UINT32              uwArg2;                         /**< ��ʱ���û�����2     */
    UINT32              uwArg3;                         /**< ��ʱ���û�����3     */
    UINT32              uwArg4;                         /**< ��ʱ���û�����4     */
}TIMER_CREATE_PARA_S;

/**@ingroup sre_timer
 * �����ʱ��ͳ����Ϣ�Ľṹ�����Ͷ���
 */
typedef struct tagSwTmrStatInfo
{
    UINT32 uwUsedCnt;   /**< ��ʱ��ʹ����,�������ڴ���̬����ʱ̬�ͳ�ʱ����̬�Ķ�ʱ������*/
    UINT32 uwFreeCnt;   /**< ��ʱ��������*/
    UINT32 uwRunCnt;    /**< ��ʱ�����������������ڼ�ʱ̬�ͳ�ʱ����̬�Ķ�ʱ������*/
} SWTMR_STAT_INFO_S;

/**@ingroup sre_timer
 * �����ʱ����Ϣ�Ľṹ�����Ͷ���
 */
typedef struct tagSwTmrInfo
{
    UINT8             ucState;         /**< ��ʱ��״̬������״̬:Free,Created,Running,Expired */
    UINT8             ucResved;        /**< �����ֶ�*/
    UINT16            usResved;        /**< �����ֶ�*/
    TIMER_MODE_E      enMode;          /**< ��ʱ�����ͣ���������:�����ԡ�һ����*/
    UINT32            uwInterval;      /**< ��ʱ����ʱ���*/
    UINT32            uwRemainMs;      /**< ��ʱ���볬ʱʣ���ms��*/
    SRE_TMR_PROC_FUNC pfnHandler;      /**< ��ʱ����ʱ������*/
} SWTMR_INFO_S;

/**
 * @ingroup sre_timer
 * ��ʱ��״̬ö��ֵ
 */
typedef enum tagTmrFlag
{
    OS_TIMER_FREE             = 1,  /**< ��ʱ������״̬ */
    OS_TIMER_CREATED          = 2,  /**< ��ʱ��û������ */
    OS_TIMER_RUNNING          = 4,  /**< ��ʱ���������� */
    OS_TIMER_EXPIRED          = 8   /**< ��ʱ���Ѿ���ʱ */
}OS_TIMER_FLAG_E;

extern TIMER_GROUPID_T              g_uwTickSwTmrGroupID;
/**
 * @ingroup sre_timer
 * ����tick�������ʱ��ID��
 *
 * �������ʱ���Ŀ��ش򿪺�ϵͳ�ᴴ������tick�������ʱ���飬�û�ͨ���˺꣬��������ʱ����ID��
 */
#define OS_TICK_SWTMR_GRPID    g_uwTickSwTmrGroupID

/**
 * @ingroup sre_timer
 * SRE_timer������: ָ�����Ϊ�ա�
 *
 * ֵ: 0x02002e01
 *
 * �������: �鿴���ָ���Ƿ�Ϊ�ա�
 */
#define OS_ERRNO_TIMER_INPUT_PTR_NULL                       SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x01)

/**
 * @ingroup sre_timer
 * SRE_timer������: ��ʱ���ص�����Ϊ�ա�
 *
 * ֵ: 0x02002e02
 *
 * �������: �鿴��ʱ���ص������Ƿ�Ϊ�ա�
 */
#define OS_ERRNO_TIMER_PROC_FUNC_NULL                       SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x02)

/**
 * @ingroup sre_timer
 * SRE_timer������: ��ʱ������Ƿ���
 *
 * ֵ: 0x02002e03
 *
 * �������: �������Ķ�ʱ������Ƿ���ȷ��
 */
#define OS_ERRNO_TIMER_HANDLE_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x03)

/**
 * @ingroup sre_timer
 * SRE_timer������: ��ʱ�����ڲ����Ƿ���
 *
 * ֵ: 0x02002e04
 *
 * �������: �鿴��ʱ�����ڲ����Ƿ���ȷ��
 */
#define OS_ERRNO_TIMER_INTERVAL_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x04)

/**
 * @ingroup sre_timer
 * SRE_timer������: ��ʱ������ģʽ�����Ƿ���
 *
 * ֵ: 0x02002e05
 *
 * �������: �鿴��ʱ������ģʽ�����Ƿ���ȷ�����չ���ģʽ����ö�ٶ���#TIMER_MODE_E��
 */
#define OS_ERRNO_TIMER_MODE_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x05)

/**
 * @ingroup sre_timer
 * SRE_timer������: ��ʱ�����Ͳ����Ƿ���
 *
 * ֵ: 0x02002e06
 *
 * �������: �鿴��ʱ�����Ͳ����Ƿ���ȷ��������������ö�ٶ���#TIMER_TYPE_E��
 */
#define OS_ERRNO_TIMER_TYPE_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x06)

/**
 * @ingroup sre_timer
 * SRE_timer������: Ӳ����ʱ��û�г�ʼ����
 *
 * ֵ: 0x02002e08
 *
 * �������: �������Ӳ����ʱ������ʼ��Ӳ����ʱ����
 */
#define OS_ERRNO_TIMER_HWTMR_NOT_INIT                       SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x08)

/**
 * @ingroup sre_timer
 * SRE_timer������: ����Ӳ����ʱ��û�г�ʼ����
 *
 * ֵ: 0x02002e09
 *
 * �������: ������򿪹���Ӳ����ʱ������ʼ������Ӳ����ʱ����
 */
#define OS_ERRNO_TIMER_SHARED_HWTMR_NOT_INIT                SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x09)

/*===========================================================HWTMR ERRNO============================================*/
/**
 * @ingroup sre_timer
 * Ӳ����ʱ�������룺û�пɷ����Ӳ����ʱ����
 *
 * ֵ: 0x02002e21
 *
 * �������: �ڴ���Ӳ����ʱ��ǰ����ȷ����Ӳ����ʱ����Դ���á�
 */
#define OS_ERRNO_HWTMR_UNAVAILABLE                          SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x21)

/**
 * @ingroup sre_timer
 * Ӳ����ʱ�������룺Ӳ����ʱ��δ������
 *
 * ֵ: 0x02002e24
 *
 * �������: ���Ӳ����ʱ���Ƿ񴴽���
 */
#define OS_ERRNO_HWTMR_NOT_CREATED                          SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x24)

/**
 * @ingroup sre_timer
 * Ӳ����ʱ�������룺Ӳ����ʱ����ʱ����usת��cycle�����
 *
 * ֵ: 0x02002e25
 *
 * �������: Ӳ����ʱ����ʱ����usתcycle���,��С�����usֵ��
 */
#define OS_ERRNO_HWTMR_US2CYCLE_OVERFLOW                    SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x25)

/**
 * @ingroup sre_timer
 * Ӳ����ʱ�������룺Ӳ����ʱ����ʱδ������
 *
 * ֵ: 0x02002e27
 *
 * �������: ���Ӳ����ʱ���Ƿ�������
 */
#define OS_ERRNO_HWTMR_NOT_START                            SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x27)


/*===========================================================SWTMR ERRNO============================================*/
/**
 * @ingroup sre_timer
 * �����ʱ�������룺�����ʱ�����ʱ��Դ���Ͳ�ΪTICK���͡�
 *
 * ֵ: 0x02002e40
 *
 * �������: �����ʱ�����ʱ��Դ���ͱ���ΪTICK���͡�
 */
#define OS_ERRNO_TIMER_SOURCE_NOT_TICK                      SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x40)

/**
 * @ingroup sre_timer
 * �����ʱ�������룺�����ʱ��������ʱ������Ϊ�㡣
 *
 * ֵ: 0x02002e41
 *
 * �������: �����ʱ��������ʱ��������������㡣
 */
#define OS_ERRNO_TIMER_NUM_ZERO                             SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x41)

/**
 * @ingroup sre_timer
 * �����ʱ�������룺��ʱ����δ������
 *
 * ֵ: 0x02002e43
 *
 * �������: ֻ���ڶ�ʱ�����Ѿ�����������²���ʹ�ö�ʱ����
 */
#define OS_ERRNO_TIMER_GROUP_UNCREATED                      SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x43)

/**@ingroup sre_timer
 * �����ʱ��������:��ʱ�����õĶ�ʱ����ת��ΪTick����Ϊ������
 *
 * ֵ: 0x02002e44
 *
 * �������:��ȷ�����õĶ�ʱ������Tick����������
 */
#define OS_ERRNO_SWTMR_INTERVAL_NOT_SUITED                  SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x44)

/**@ingroup sre_timer
 * �����ʱ��������:����ָ�����Ϊ�ա�
 *
 * ֵ: 0x02002e47
 *
 * �������:������Ч��ָ�������
 */
#define OS_ERRNO_SWTMR_RET_PTR_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x47)

/**@ingroup sre_timer
 * �����ʱ��������:�ﵽ���֧�ֶ�ʱ����Ŀ��
 *
 * ֵ: 0x02002e48
 *
 * �������:�ﵽ���֧�ֶ�ʱ�������������ٴ��������ʱ����
 */
#define OS_ERRNO_SWTMR_MAXSIZE                              SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x48)

/**@ingroup sre_timer
 * �����ʱ��������:��ʱ��δ������
 *
 * ֵ: 0x02002e4a
 *
 * �������:������ʱ������ʹ�á�
 */
#define OS_ERRNO_SWTMR_NOT_CREATED                          SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x4a)

/**@ingroup sre_timer
 * �����ʱ��������:��ʱ���Ѿ�����δ����״̬��
 *
 * ֵ: 0x02002e4d
 *
 * �������:��ʱ������δ����״̬�����ܽ���һЩ��������������ĺϷ��ԡ�
 */
#define OS_ERRNO_SWTMR_UNSTART                              SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x4d)

/**@ingroup sre_timer
 * �����ʱ��������:��ʼ���ڴ治�㡣
 *
 * ֵ: 0x02002e50
 *
 * �������:���ʵ�����ϵͳĬ��FSC������С��
 */
#define OS_ERRNO_SWTMR_NO_MEMORY                            SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x50)

/**@ingroup sre_timer
 * �����ʱ��������:TICKû�г�ʼ����
 *
 * ֵ: 0x02002e53
 *
 * �������:��ʼ��Tick��
 */
#define OS_ERRNO_TICK_NOT_INIT                              SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x53)

/**@ingroup sre_timer
 * �����ʱ��������:�����ʱ�������ָ��Ϊ�ա�
 *
 * ֵ: 0x02002e54
 *
 * �������:����ǿ����ָ�롣
 */
#define OS_ERRNO_TIMERGROUP_INPUT_PTR_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x54)

/**@ingroup sre_timer
 * �����ʱ��������:�����ʱ����ʱ���ڹ���ת��ΪTick������0xFFFFFFFF��
 *
 * ֵ: 0x02002e55
 *
 * �������:��ȷ������Ķ�ʱ����ת��ΪTick���󲻴���0xFFFFFFFF��
 */
#define OS_ERRNO_SWTMR_INTERVAL_OVERFLOW                    SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x55)

/**@ingroup sre_timer
 * �����ʱ��������:Tick��ʱ�����Ѵ�����
 *
 * ֵ: 0x02002e56
 *
 * �������:�����ظ�������ʱ���顣
 */
#define OS_ERRNO_TIMER_TICKGROUP_CREATED                    SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x56)

/**@ingroup sre_timer
 * �����ʱ��������:���������ʱ��ʱ���붨ʱ������ŷǷ���
 *
 * ֵ: 0x02002e57
 *
 * �������:ȷ������Ķ�ʱ�������ͨ��ʹ�ö�ʱ���鴴���ӿڵõ���
 */
#define OS_ERRNO_TIMERGROUP_ID_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x57)

/**
 * @ingroup sre_timer
 * �����ʱ�������룺�����ʱ��������ʱ����������0xffff��
 *
 * ֵ: 0x02002e58
 *
 * �������: ȷ�������ʱ��������ʱ������С�ڵ���0xffff��
 */
#define OS_ERRNO_TIMER_NUM_TOO_LARGE                        SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x58)

/*======================================================SHARED HWTMR ERRNO============================================*/
/**@ingroup sre_timer
 * ����Ӳ����ʱ��������:����SD6182ƽ̨����������Ӳ����ʱ��ʱ����Ķ�ʱ��ʱ�������ǿա�
 *
 * ֵ: 0x02002e70
 *
 * �������:��SD6182ƽ̨ȷ������Ĺ���Ӳ����ʱ����ʱ������Ϊ�ա�
 */
#define OS_ERRNO_SHARED_TIMER_FUNC_NO_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x70)

/**@ingroup sre_timer
 * ����Ӳ����ʱ��������:����Ĺ���Ӳ����ʱ��ID�����á�
 *
 * ֵ: 0x02002e72
 *
 * �������:ȷ������Ĺ���Ӳ����ʱ��ID��Χ[0,7]��
 */
#define OS_ERRNO_SHARED_TIMER_ID_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x72)

/**@ingroup sre_timer
 * ����Ӳ����ʱ��������:����Ӳ����ʱ��ʱδ������
 *
 * ֵ: 0x02002e73
 *
 * �������:��Ҫ�ȴ�������Ӳ����ʱ����ʹ�á�
 */
#define OS_ERRNO_SHARED_TIMER_NOT_CREATED                   SRE_ERRNO_OS_ERROR(OS_MID_TIMER,0x73)

/**
 * @ingroup sre_timer
 * ����Ӳ����ʱ�������룺����Ӳ����ʱ����ʱδ������
 *
 * ֵ: 0x02002e74
 *
 * �������: ��鹲��Ӳ����ʱ���Ƿ�������
 */
#define OS_ERRNO_SHARED_TIMER_NOT_START                     SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x74)

/**
 * @ingroup sre_timer
 * ����Ӳ����ʱ�������룺����Ӳ����ʱ����ʱ�����á�
 *
 * ֵ: 0x02002e75
 *
 * �������: ��鹲��Ӳ����ʱ���Ƿ����𻵡�
 */
#define OS_ERRNO_SHARED_TIMER_IS_BAD                        SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x75)

/**
 * @ingroup sre_timer
 * ����Ӳ����ʱ�������룺����Ӳ����ʱ����ʱ����usת��cycle��Ϊ0��
 *
 * ֵ: 0x02002e76
 *
 * �������: Ӳ����ʱ����ʱ����usתcycleΪ0,���������usֵ��
 */
#define OS_ERRNO_SHARED_TIMER_US2CYCLE_IS_ZERO              SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x76)

/**
 * @ingroup sre_timer
 * ����Ӳ����ʱ�������룺����Ӳ����ʱ����ʱ����usת��cycle�����
 *
 * ֵ: 0x02002e77
 *
 * �������: Ӳ����ʱ����ʱ����usתcycle���,��С�����usֵ��
 */
#define OS_ERRNO_SHARED_TIMER_US2CYCLE_OVERFLOW             SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x77)

/**
 * @ingroup sre_timer
 * ����Ӳ����ʱ�������룺����Ӳ����ʱ�����õ�ʱ��Ƶ��Ϊ0��
 *
 * ֵ: 0x02002e79
 *
 * �������: ��config.h�����õ�ʱ��Ƶ�ʲ���Ϊ0��
 */
#define OS_ERRNO_SHARED_TIMER_CLOCK_IS_ZERO                 SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x79)

/**
 * @ingroup sre_timer
 * ����Ӳ����ʱ�������룺����Ӳ����ʱ������ʹ�ã������Լ졣
 *
 * ֵ: 0x02002e80
 *
 * �������: ��ʱ��ʹ����ɺ������Լ죬������ʹ��֮ǰ�Լ졣
 */
#define OS_ERRNO_SHARED_TIMER_IN_USING                      SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x80)

/**
 * @ingroup sre_timer
 * ����Ӳ����ʱ�������룺SD6183ƽ̨����Ӳ����ʱ��ͨ����VMID����ʱ�����ͨ����ID�Ƿ���
 *
 * ֵ: 0x02002e81
 *
 * �������: SD6183ƽ̨����Ӳ����ʱ��ͨ����ID������0~3��
 */
#define OS_ERRNO_SHARE_TIMER_CHG_IDX_ILLEGAL                SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x81)

/**
 * @ingroup sre_timer
 * ����Ӳ����ʱ�������룺SD6183ƽ̨����Ӳ����ʱ��ͨ����VMID����ʱ�����VMID�Ƿ���
 *
 * ֵ: 0x02002e82
 *
 * �������: SD6183ƽ̨����Ӳ����ʱ��ͨ����VMID������0~7��
 */
#define OS_ERRNO_SHARE_TIMER_VMID_VALUE_ILLEGAL             SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x82)

/**
 * @ingroup sre_timer
 * ����Ӳ����ʱ�������룺SD6183ƽ̨����Ӳ����ʱ��ͨ����VMID����ʱ�������Դ��̫��(����0xff)��
 *
 * ֵ: 0x02002e83
 *
 * �������: SD6183ƽ̨����Ӳ����ʱ��ͨ����VMID����ʱ�������Դ��Bit0~Bit7��Ч������Bit��������Ϊ0��
 */
#define OS_ERRNO_SHARE_TIMER_MAP_VALUE_TOO_LARGE            SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x83)

/**
 * @ingroup sre_timer
 * ����Ӳ����ʱ�������룺SD6183ƽ̨����Ӳ����ʱ��ͨ����VMID����ʱ�������Դ��ֵΪ0��
 *
 * ֵ: 0x02002e84
 *
 * �������: SD6183ƽ̨����Ӳ����ʱ��ͨ����VMID����ʱ�������Դ��ֵ����Ϊ0��
 */
#define OS_ERRNO_SHARE_TIMER_MAP_VALUE_ZERO                 SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x84)

/**
 * @ingroup  sre_timer
 * @brief ������ʱ����
 *
 * @par ����:
 * ����һ������ΪpstCreatePara�Ķ�ʱ�������ض�ʱ���߼�ID puwTmrHandle��
 *
 * @attention
 * <ul>
 * <li>DSP220/RISC220/HACCC/RISC170/SD6183ƽ̨����ʹ��2��Ӳ����ʱ����Դ,DSP170ƽ̨����ʹ��3��Ӳ����ʱ����Դ,Cortex_AXƽ̨��֧��Ӳ����ʱ�����ܡ�</li>
 * <li>����û���Tick������ɴ���Ӳ����ʱ��������һ����</li>
 * <li>�жϴ�����pfnHandler�ĵ�һ�������Ǵ����Ķ�ʱ�����߼���š�</li>
 * <li>��ʱ�������ɹ��󲢲�������ʼ����������ʽ����#SRE_TimerStart����#SRE_TimerRestart������</li>
 * <li>�������ڶ�ʱģʽ�Ķ�ʱ���������û���Ҫ�Ѷ�ʱ������õĹ��ͣ�����һֱ������ʱ���Ĵ�������</li>
 * <li>TIMER_CREATE_PARA_S���������uwIntervalԪ�ر�ʾ��ʱ�����ڣ������ʱ����λ��ms������Ӳ����ʱ����ȫ��Ӳ����ʱ����λ��us������ʱ������ʱ����ע�����䣬�������������</li>
 * </ul>
 *
 * @param  pstCreatePara [IN] ����#TIMER_CREATE_PARA_S *����ʱ����������
 * @param  puwTmrHandle  [OUT] ����#TIMER_HANDLE_T *����ʱ�����
 *
 * @retval #OS_ERRNO_TIMER_INPUT_PTR_NULL            0x02002e01��ָ�����Ϊ�ա�
 * @retval #OS_ERRNO_TIMER_PROC_FUNC_NULL            0x02002e02����ʱ���ص�����Ϊ�ա�
 * @retval #OS_ERRNO_TIMER_INTERVAL_INVALID          0x02002e04����ʱ�����ڲ����Ƿ���
 * @retval #OS_ERRNO_TIMER_MODE_INVALID              0x02002e05����ʱ������ģʽ�����Ƿ���
 * @retval #OS_ERRNO_TIMER_TYPE_INVALID              0x02002e06����ʱ�����Ͳ����Ƿ���
 * @retval #OS_ERRNO_TIMER_HWTMR_NOT_INIT            0x02002e08��Ӳ����ʱ��û�г�ʼ����
 * @retval #OS_ERRNO_TIMER_GROUP_UNCREATED           0x02002e43����ʱ����δ������
 * @retval #OS_ERRNO_TIMERGROUP_ID_INVALID           0x02002e57�����붨ʱ������ŷǷ���
 * @retval #OS_ERRNO_SWTMR_INTERVAL_NOT_SUITED       0x02002e44����ʱ�����õĶ�ʱ����ת��ΪTick����Ϊ������
 * @retval #OS_ERRNO_SWTMR_INTERVAL_OVERFLOW         0x02002e55�������ʱ����ʱ���ڹ���
 * @retval #OS_ERRNO_SWTMR_MAXSIZE                   0x02002e48�������Ķ�ʱ�������Ѵﵽ���ֵ��
 * @retval #OS_ERRNO_HWTMR_US2CYCLE_OVERFLOW         0x02002e25��Ӳ����ʱ����ʱ����usת��cycle�����SD6183ƽ̨���⡣
 * @retval #OS_ERRNO_SHARED_TIMER_US2CYCLE_IS_ZERO   0x02002e76��ȫ��Ӳ����ʱ����ʱ����usת��cycle��Ϊ0��
 * @retval #OS_ERRNO_SHARED_TIMER_US2CYCLE_OVERFLOW  0x02002e77��ȫ��Ӳ����ʱ����ʱ����usת��cycle�����
 * @retval #OS_ERRNO_HWTMR_UNAVAILABLE               0x02002e21��û�пɷ����Ӳ����ʱ����
 * @retval #OS_ERRNO_SHARED_TIMER_ID_INVALID         0x02002e72�������ȫ��Ӳ����ʱ��ID�����á�
 * @retval #OS_ERRNO_SHARED_TIMER_FUNC_NO_NULL       0x02002e70������ȫ��Ӳ����ʱ��ʱ����Ķ�ʱ��ʱ�������ǿա�
 * @retval #SRE_OK                                   0x00000000����ʱ�������ɹ���
 * @par ����:
 * <ul><li>sre_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TimerDelete
 */
extern UINT32 SRE_TimerCreate(TIMER_CREATE_PARA_S *pstCreatePara, TIMER_HANDLE_T *puwTmrHandle);

/**
 * @ingroup  sre_timer
 * @brief ɾ����ʱ����
 *
 * @par ����:
 * �ͷ�һ����ʱ���߼�IDΪuwTmrHandle�Ķ�ʱ����Դ��
 *
 * @attention
 * <ul>
 * <li>Ӳ����ʱ��ɾ����ֹͣ������</li>
 * <li>ɾ�����ڳ�ʱ״̬�µ������ʱ��ʱ��OS������ʱɾ���ķ�ʽ����ϸ˵������ֲ�ע�����</li>
 * </ul>
 *
 * @param  uwMid [IN] ����#UINT32��ģ��ţ���ǰδʹ�ã�����
 * @param  uwTmrHandle [IN] ����#TIMER_HANDLE_T����ʱ������� ͨ��SRE_TimerCreate�ӿڻ�ȡ
 *
 * @retval #OS_ERRNO_TIMER_GROUP_UNCREATED                   0x02002e43����ʱ����δ������
 * @retval #OS_ERRNO_TIMER_HWTMR_NOT_INIT                    0x02002e08��Ӳ����ʱ��û�г�ʼ����
 * @retval #OS_ERRNO_TIMER_HANDLE_INVALID                    0x02002e03����ʱ������Ƿ���
 * @retval #OS_ERRNO_SWTMR_NOT_CREATED                       0x02002e4a�������ʱ��δ������
 * @retval #OS_ERRNO_HWTMR_NOT_CREATED                       0x02002e24��Ӳ����ʱ��δ������
 * @retval #OS_ERRNO_SHARED_TIMER_NOT_CREATED                0x02002e73��ȫ�ֹ���Ӳ����ʱ��δ������
 * @retval #SRE_OK                                           0x00000000����ʱ��ɾ���ɹ���
 * @par ����:
 * <ul><li>sre_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TimerCreate
 */
extern UINT32 SRE_TimerDelete(UINT32 uwMid, TIMER_HANDLE_T uwTmrHandle);

/**
 * @ingroup  sre_timer
 * @brief ������ʱ����
 *
 * @par ����:
 * ����ʱ���߼�IDΪuwTmrHandle�Ķ�ʱ���ɴ���״̬�������״̬��
 *
 * @attention
 * <ul>
 * <li>���������������ʱ��ʱ�������õ�ֵ��ʼ����������ظ���������������ֹͣȻ�������������ظ����������ֹͣ��ļ���ֵ��ʼ������</li>
 * <li>����SD6182/SD6157/SD6183ȫ��Ӳ����ʱ���������ǵ�һ�����������ظ���������һ���������ӳ�ʼֵ��ʼ��ʱ��</li>
 * <li>���ڵ��δ���ģʽ������һ�κ󣬿��Ե��������ӿ��ٴ������ö�ʱ����ʱ����Ϊ���õ�ʱ������</li>
 * <li>�������ڳ�ʱ״̬�µ������ʱ��ʱ��OS������ʱ�����ķ�ʽ����ϸ˵������ֲ�ע�����</li>
 * <li>SD6182��SD6157�ĺ���Ӳ����ʱ�������������У����������ʱ������ӳ�һ����ʱ���ڣ����¸���ʱ��������Ӧ�жϡ�</li>
 * <li>���ڹ���Ӳ����ʱ�����ýӿڹ��ܸ�#SRE_TimerRestart������ȫһ�£�����������ʱ�������¼�ʱ��</li>
 * </ul>
 *
 * @param  uwMid [IN] ����#UINT32��ģ��ţ���ǰδʹ�ã�����
 * @param  uwTmrHandle [IN] ����#TIMER_HANDLE_T����ʱ������� ͨ��#SRE_TimerCreate�ӿڻ�ȡ
 *
 * @retval #OS_ERRNO_TIMER_GROUP_UNCREATED                   0x02002e43����ʱ����δ����
 * @retval #OS_ERRNO_TIMER_HWTMR_NOT_INIT                    0x02002e08��Ӳ����ʱ��û�г�ʼ����
 * @retval #OS_ERRNO_SWTMR_NOT_CREATED                       0x02002e4a�������ʱ��δ������
 * @retval #OS_ERRNO_TIMER_HANDLE_INVALID                    0x02002e03����ʱ������Ƿ���
 * @retval #OS_ERRNO_HWTMR_NOT_CREATED                       0x02002e24��Ӳ����ʱ��δ������
 * @retval #OS_ERRNO_SHARED_TIMER_NOT_CREATED                0x02002e73��ȫ�ֹ���Ӳ����ʱ��δ������
 * @retval #SRE_OK                                           0x00000000����ʱ�������ɹ���
 * @par ����:
 * <ul><li>sre_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TimerStop
 */
extern UINT32 SRE_TimerStart(UINT32 uwMid, TIMER_HANDLE_T uwTmrHandle);

/**
 * @ingroup  sre_timer
 * @brief ֹͣ��ʱ����
 *
 * @par ����:
 * ֹͣ��ʱ���߼�IDΪuwTmrHandle�Ķ�ʱ��������ʹ��ʱ���ɼ�ʱ״̬��ɴ���״̬��
 *
 * @attention
 * <ul>
 * <li>��ʱ��ֹͣ����һ�����������´�ֹͣ��ļ���ֵ��ʼ���������Ƕ���SD6182/SD6157/SD6183ȫ��Ӳ����ʱ������һ�������ӳ�ʼֵ��ʼ��ʱ��</li>
 * <li>����ֹͣδ�����Ķ�ʱ����</li>
 * <li>ֹͣ���ڳ�ʱ״̬�µ������ʱ��ʱ��OS������ʱֹͣ�ķ�ʽ����ϸ˵������ֲ�ע�����</li>
 * <li>SD6182��SD6157��SD6183�ĺ���Ӳ����ʱ����ֹͣ���������������ʱ����ʣ��ʱ��Ϊ0����������Ӧ��ʱ����������</li>
 * </ul>
 *
 * @param  uwMid [IN] ����#UINT32��ģ��ţ���ǰδʹ�ã�����
 * @param  uwTmrHandle [IN] ����#TIMER_HANDLE_T����ʱ������� ͨ��#SRE_TimerCreate�ӿڻ�ȡ
 *
 * @retval #OS_ERRNO_TIMER_GROUP_UNCREATED                   0x02002e43����ʱ����δ������
 * @retval #OS_ERRNO_TIMER_HWTMR_NOT_INIT                    0x02002e08��Ӳ����ʱ��û�г�ʼ����
 * @retval #OS_ERRNO_SWTMR_NOT_CREATED                       0x02002e4a�������ʱ��δ������
 * @retval #OS_ERRNO_TIMER_HANDLE_INVALID                    0x02002e03����ʱ������Ƿ���
 * @retval #OS_ERRNO_HWTMR_NOT_CREATED                       0x02002e24��Ӳ����ʱ��δ������
 * @retval #OS_ERRNO_HWTMR_NOT_START                         0x02002e27��Ӳ����ʱ����ʱδ������
 * @retval #OS_ERRNO_SWTMR_UNSTART                           0x02002e4d����ʱ���Ѿ�����δ����״̬��
 * @retval #OS_ERRNO_SHARED_TIMER_NOT_CREATED                0x02002e73��ȫ�ֹ���Ӳ����ʱ��δ������
 * @retval #OS_ERRNO_SHARED_TIMER_NOT_START                  0x02002e74��ȫ�ֹ���Ӳ����ʱ��δ������
 * @retval #SRE_OK                                           0x00000000����ʱ��ֹͣ�ɹ���

 * @par ����:
 * <ul><li>sre_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TimerStart
 */
extern UINT32  SRE_TimerStop(UINT32 uwMid, TIMER_HANDLE_T uwTmrHandle);

/**
 * @ingroup  sre_timer
 * @brief ������ʱ��
 *
 * @par ����:
 * ������ʱ���߼�IDΪuwTmrHandle�Ķ�ʱ������������ֹͣ���Ķ�ʱ�����൱�ڻָ����մ���ʱ�Ķ�ʱʱ����ʼ��ʱ��
 *
 * @attention
 * <ul>
 * <li>�������ڳ�ʱ״̬�µ������ʱ��ʱ��OS������ʱ�����ķ�ʽ����ϸ˵������ֲ�ע�����</li>
 * </ul>
 *
 * @param  uwMid [IN] ����#UINT32��ģ��ţ���ǰδʹ�ã�����
 * @param  uwTmrHandle [IN] ����#TIMER_HANDLE_T����ʱ������� ͨ��#SRE_TimerCreate�ӿڻ�ȡ
 *
 * @retval #OS_ERRNO_TIMER_GROUP_UNCREATED                   0x02002e43����ʱ����δ������
 * @retval #OS_ERRNO_SWTMR_NOT_CREATED                       0x02002e4a�������ʱ��δ������
 * @retval #OS_ERRNO_TIMER_HWTMR_NOT_INIT                    0x02002e08��Ӳ����ʱ��û�г�ʼ����
 * @retval #OS_ERRNO_TIMER_HANDLE_INVALID                    0x02002e03����ʱ������Ƿ���
 * @retval #OS_ERRNO_HWTMR_NOT_CREATED                       0x02002e24��Ӳ����ʱ��δ������
 * @retval #OS_ERRNO_SHARED_TIMER_NOT_CREATED                0x02002e73��ȫ�ֹ���Ӳ����ʱ��δ������
 * @retval #SRE_OK                                           0x00000000����ʱ�������ɹ���
 * @par ����:
 * <ul><li>sre_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TimerStop
 */
extern UINT32 SRE_TimerRestart(UINT32 uwMid, TIMER_HANDLE_T uwTmrHandle);

/**
 * @ingroup  sre_timer
 * @brief ��ʱ��ʣ�೬ʱʱ���ѯ
 *
 * @par ����:
 * ���붨ʱ�����uwTmrHandle����ö�Ӧ��ʱ����ʱʣ��ʱ��puwExpireTime��
 *
 * @attention
 * <ul>
 * <li>�����ʱ����λ���룬���ں�ȫ��Ӳ����ʱ����λ΢�롣</li>
 * <li>����OS�ڲ������ʱ������Tick��Ϊ��ʱ��λ��Ӳ����ʱ������Cycle��Ϊ��ʱ��λ������ʣ��ʱ��ת����ms��us��һ������������ת�����ms��us����Ϊ����ʱ�����ص�ʣ��ʱ���Ǹ�ms��us��ȡ����+1;
       ����ת����ms��Ϊ4.2���������û��õ���ʣ��ʱ����5ms��</li>
 * </ul>
 *
 * @param  uwMid [IN] ����#UINT32��ģ��ţ���ǰδʹ�ã�����
 * @param  uwTmrHandle [IN] ����#TIMER_HANDLE_T����ʱ������� ͨ��#SRE_TimerCreate�ӿڻ�ȡ
 * @param  puwExpireTime [OUT] ����#UINT32*����ʱ����ʣ��ĳ�ʱʱ�䣬�����˽��Ӳ����ʱ����λus�������ʱ����λms
 *
 * @retval #OS_ERRNO_TIMER_HANDLE_INVALID                    0x02002e03��Ӳ����ʱ����������á�
 * @retval #OS_ERRNO_TIMER_HWTMR_NOT_INIT                    0x02002e08��Ӳ����ʱ��û�г�ʼ����
 * @retval #OS_ERRNO_SWTMR_NOT_CREATED                       0x02002e4a�������ʱ��δ������
 * @retval #OS_ERRNO_HWTMR_NOT_CREATED                       0x02002e24��Ӳ����ʱ��δ������
 * @retval #OS_ERRNO_SHARED_TIMER_ID_INVALID                 0x02002e72��ȫ�ֹ���Ӳ����ʱ����������á�
 * @retval #OS_ERRNO_TIMER_SHARED_HWTMR_NOT_INIT             0x02002e09��ȫ�ֹ���Ӳ����ʱ��û�г�ʼ����
 * @retval #OS_ERRNO_SHARED_TIMER_NOT_CREATED                0x02002e73��ȫ�ֹ���Ӳ����ʱ��δ������
 * @retval #SRE_OK                                           0x00000000����ʱ��ʣ�೬ʱʱ���ѯ�ɹ���
 * @par ����:
 * <ul><li>sre_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_TimerCreate
 */
extern UINT32 SRE_TimerQuery(UINT32 uwMid, TIMER_HANDLE_T uwTmrHandle, UINT32 *puwExpireTime);

/**
 * @ingroup  sre_timer
 * @brief ����Ӳ����ʱ��ʱ������
 *
 * @par ����:
 * ���ö�ʱ��IDΪuwTmrHandle��Ӳ����ʱ��ʱ����uwInterVal��Ӳ����ʱ�����������õ�ʱ������ʱ��
 *
 * @attention
 * <ul>
 * <li>�����ʱ������ʹ�øýӿڡ�</li>
 * <li>�����˽��Ӳ����ʱ����λus��</li>
 * </ul>
 *
 * @param  uwMid       [IN] ����#UINT32��ģ��ţ���ǰδʹ�ú��ԡ�
 * @param  uwTmrHandle [IN] ����#TIMER_HANDLE_T����ʱ������� ͨ��#SRE_TimerCreate�ӿڻ�ȡ��
 * @param  uwInterVal  [IN] ����#UINT32�����ں�ȫ��Ӳ����ʱ����λ΢�롣
 *
 * @retval #OS_ERRNO_TIMER_HANDLE_INVALID                    0x02002e03��Ӳ����ʱ����������á�
 * @retval #OS_ERRNO_TIMER_HWTMR_NOT_INIT                    0x02002e08��Ӳ����ʱ��û�г�ʼ����
 * @retval #OS_ERRNO_TIMER_INTERVAL_INVALID                  0x02002e04����ʱ�����ڲ����Ƿ���
 * @retval #OS_ERRNO_HWTMR_NOT_CREATED                       0x02002e24��Ӳ����ʱ��δ������
 * @retval #OS_ERRNO_HWTMR_US2CYCLE_OVERFLOW                 0x02002e25��Ӳ����ʱ����ʱ����usת��cycle�����
 * @retval #OS_ERRNO_SHARED_TIMER_ID_INVALID                 0x02002e03��ȫ�ֹ���Ӳ����ʱ����������á�
 * @retval #OS_ERRNO_TIMER_SHARED_HWTMR_NOT_INIT             0x02002e09��ȫ�ֹ���Ӳ����ʱ��û�г�ʼ����
 * @retval #OS_ERRNO_SHARED_TIMER_NOT_CREATED                0x02002e73��ȫ�ֹ���Ӳ����ʱ��δ������
 * @retval #OS_ERRNO_SHARED_TIMER_US2CYCLE_IS_ZERO           0x02002e76��ȫ�ֹ���Ӳ����ʱ����ʱ����usת��cycle��Ϊ0��
 * @retval #OS_ERRNO_SHARED_TIMER_US2CYCLE_OVERFLOW          0x02002e77��ȫ�ֹ���Ӳ����ʱ����ʱ����usת��cycle�����
 * @retval #SRE_OK                                           0x00000000����ʱ��ʱ�������óɹ���
 * @par ����:
 * <ul><li>sre_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TimerCreate
 */
extern UINT32  SRE_HwTmrSetInterval(UINT32 uwMid, TIMER_HANDLE_T uwTmrHandle, UINT32 uwInterVal);

/**
 * @ingroup  sre_timer
 * @brief ��ȡ�����ʱ����ͳ����Ϣ��
 *
 * @par ����:
 * ��ȡϵͳ�������ʱ����ʹ��״̬pstStatInfo(ʹ��������������������)��
 *
 * @attention
 * <ul>
 * <li>��ѯ���Ķ�ʱ��ʹ�����������ڴ���̬����ʱ̬�ͳ�ʱ����̬�Ķ�ʱ��������</li>
 * <li>��ѯ���Ķ�ʱ���������������ڼ�ʱ̬�ͳ�ʱ����̬�Ķ�ʱ��������</li>
 * </ul>
 *
 * @param  pstStatInfo [OUT] ����#SWTMR_STAT_INFO_S *��ͳ����Ϣ��
 *
 * @retval #OS_ERRNO_TIMER_GROUP_UNCREATED      0x02002e43����ʱ����δ������
 * @retval #OS_ERRNO_SWTMR_RET_PTR_NULL         0x02002e47����Ϣ���ص�ַ����Ϊ�ա�
 * @retval #SRE_OK                              0x00000000����ȡ��ʱ��ͳ����Ϣ�ɹ���
 * @par ����:
 * <ul><li>SRE_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C02
 * @see SRE_SwTmrInfoGet
 */
extern UINT32 SRE_SwTmrStatInfoGet(SWTMR_STAT_INFO_S *pstStatInfo);

/**
 * @ingroup  sre_timer
 * @brief ��ȡָ����ʱ������Ϣ��
 *
 * @par ����:
 * ����ָ���Ķ�ʱ��ID����ȡ��ʱ��IDΪuwTmrHandle�Ķ�ʱ������ϢpstInfo��
 *
 * @attention
 * <ul>
 * <li>����OS�ڲ�����Tick��Ϊ�����ʱ����ʱ��Դ������ʣ��ʱ��ת����ms��һ������������ת����ĺ�������Ϊ����ʱ�����ص�ʣ��ʱ���Ǹú�����ȡ����+1;
       ����ת���������Ϊ4.2���������û��õ���ʣ��ʱ����5ms��</li>
 * </ul>
 *
 * @param  uwTmrHandle [IN] ����#TIMER_HANDLE_T����ʱ�������
 * @param  pstInfo   [OUT] ����#SWTMR_INFO_S *����Ŷ�ʱ����Ϣ�ṹ��ָ�롣
 *
 * @retval #OS_ERRNO_TIMER_GROUP_UNCREATED      0x02002e43����ʱ����δ������
 * @retval #OS_ERRNO_TIMER_HANDLE_INVALID       0x02002e03�������ʱ������Ƿ���
 * @retval #OS_ERRNO_SWTMR_NOT_CREATED          0x02002e4a����ʱ��δ������
 * @retval #OS_ERRNO_SWTMR_RET_PTR_NULL         0x02002e47����Ϣ���ص�ַ����Ϊ�ա�
 * @retval #SRE_OK                              0x00000000����ȡָ����ʱ������Ϣ�ɹ���
 * @par ����:
 * <ul><li>sre_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C02
 * @see SRE_SwTmrStatInfoGet
 */
extern UINT32 SRE_SwTmrInfoGet(TIMER_HANDLE_T uwTmrHandle, SWTMR_INFO_S *pstInfo);

/**
 * @ingroup  sre_timer
 * @brief ���������ʱ���顣
 *
 * @par ����:
 * ����һ������ΪpstConfig�������ʱ���飬���������ʱ�����puwGroupID��
 *
 * @attention
 * <ul>
 * <li>�����ʱ����ʱ��Դֻ��ָ��ΪSRE_TIMER_GRP_SRC_TICK��</li>
 * </ul>
 *
 * @param pstConfig  [IN] ����#SRE_TMR_GRP_USER_CFG_S*����ʱ���鴴���ṹ��
 * @param puwGroupID [IN] ����#TIMER_GROUPID_T *�����سɹ�������������ʱ�����
 *
 * @retval #OS_ERRNO_TIMERGROUP_INPUT_PTR_NULL     0x02002e54�������ʱ�������ָ��Ϊ�ա�
 * @retval #OS_ERRNO_TIMER_SOURCE_NOT_TICK         0x02002e40�������ʱ�����ʱ��Դ���Ͳ�ΪTICK���͡�
 * @retval #OS_ERRNO_TICK_NOT_INIT                 0x02002e53��TICKû�г�ʼ����
 * @retval #OS_ERRNO_TIMER_NUM_ZERO                0x02002e41�������ʱ��������ʱ������Ϊ�㡣
 * @retval #OS_ERRNO_TIMER_NUM_TOO_LARGE           0x02002e58�������ʱ��������ʱ����������0xffff��
 * @retval #OS_ERRNO_SWTMR_NO_MEMORY               0x02002e50����ʼ���ڴ治�㡣
 * @retval #OS_ERRNO_TIMER_TICKGROUP_CREATED       0x02002e56��Tick��ʱ�����Ѵ�����
 * @retval #SRE_OK                                 0x00000000����ʱ���鴴���ɹ���
 * @par ����:
 * <ul><li>sre_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see��
 */
extern UINT32  SRE_SwTimerGroupCreate(SRE_TMR_GRP_USER_CFG_S *pstConfig, TIMER_GROUPID_T *puwGroupID);

#if (OS_CPU_TYPE == OS_SD6182 || OS_CPU_TYPE == OS_SD6157 || OS_CPU_TYPE == OS_SD6183)
/**
 * @ingroup  sre_timer
 * @brief ����Ӳ����ʱ���Լ�ӿڡ�
 *
 * @par ����:
 * ���빲��Ӳ����ʱ����ţ���鹲��Ӳ����ʱ���Ƿ���á�
 *
 * @attention
 * <ul>
 * <li>�ýӿ�ֻ��SD6182��SD6157��SD6183����Ӳ����ʱ��ʹ�ã�������ʱ������ʹ�á�</li>
 * <li>�ýӿڲ���ȫ�ֶ�ʱ�����ܺ���ƣ��޷��ü��˹��ܡ�</li>
 * </ul>
 *
 * @param  uwTmrIdex [IN] ����UINT32��ȫ��Ӳ����ʱ�����[0,7]��
 *
 * @retval #OS_ERRNO_SHARED_TIMER_ID_INVALID    0x02002e72������Ӳ����ʱ��ID�����á�
 * @retval #OS_ERRNO_SHARED_TIMER_IS_BAD        0x02002e43������Ӳ����ʱ�������á�
 * @retval #OS_ERRNO_SHARED_TIMER_IN_USING      0x02002e80������Ӳ����ʱ������ʹ�ã������Լ졣
 * @retval #SRE_OK                              0x00000000������Ӳ����ʱ���Լ�ɹ���
 * @par ����:
 * SRE_timer.h���ýӿ��������ڵ�ͷ�ļ���
 * @since  RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_McHwTmrSelfCheck(UINT32 uwTmrIdex);
#endif

#if (OS_CPU_TYPE == OS_SD6183)

#if (OS_OPTION_USR_PROCESS == NO) 

/**
 * @ingroup  sre_timer
 * @brief ����Ӳ����ʱ��ͨ����VMID���á�
 *
 * @par ����:
 * ���ù���Ӳ����ʱ��ͨ����VMID���Ա���ͨ����Դ���е�ȫ�ֶ�ʱ����Դ��
 *
 * @attention
 * <ul>
 * <li>�ýӿ�ֻ��SD6183����Ӳ����ʱ��ʹ�ã�������ʱ������ʹ�á�</li>
 * <li>��MCPU���ã�����Ӳ�����ϱ������жϡ�</li>
 * </ul>
 *
 * @param  uwChgId   [IN] ����UINT32��ͨ����ID��ȡֵ��ΧΪ[0,3]��
 * @param  uwChgMap  [IN] ����UINT32��ͨ��������Դ��ȡֵ��ΧΪ[1,0xff]��
 * @param  uwChgVmid [IN] ����UINT32��ͨ����VMIDֵ��ȡֵ��ΧΪ[0,7]��
 *
 * @retval #OS_ERRNO_SHARE_TIMER_CHG_IDX_ILLEGAL      0x02002e81������Ӳ����ʱ��ID�����á�
 * @retval #OS_ERRNO_SHARE_TIMER_VMID_VALUE_ILLEGAL   0x02002e82������Ӳ����ʱ�������á�
 * @retval #OS_ERRNO_SHARE_TIMER_MAP_VALUE_TOO_LARGE  0x02002e83������Ӳ����ʱ������ʹ�ã������Լ졣
 * @retval #OS_ERRNO_SHARE_TIMER_MAP_VALUE_ZERO       0x02002e84������Ӳ����ʱ������ʹ�ã������Լ졣
 * @retval #SRE_OK                                    0x00000000������Ӳ����ʱ��ͨ����vmid���óɹ���
 * @par ����:
 * SRE_timer.h���ýӿ��������ڵ�ͷ�ļ���
 * @since  RTOSck V100R003C00
 * @see ��
 */
extern UINT32 SRE_McHwTmrChgCfg(UINT32 uwChgId, UINT32 uwChgMap, UINT32 uwChgVmid);

#endif

/**
 * @ingroup  sre_timer
 * @brief ǿ��ɾ������Ӳ����ʱ����Դ��
 *
 * @par ����:
 * ǿ��ɾ������IDΪuwMcHwTmrId��ȫ�ֶ�ʱ����Դ��
 *
 * @attention
 * <ul>
 * <li>�ýӿ�ֻ��SD6183����Ӳ����ʱ��ʹ�ã�������ʱ������ʹ�á�</li>
 * <li>VMIDȨ�����û���֤(�ýӿڻ����Timer��Ĵ���)����Υ��VMIDȨ�ޣ����ϱ������жϡ�</li>
 * </ul>
 *
 * @param  uwMcHwTmrId [IN] ����UINT32��ȫ�ֶ�ʱ������ID��ȡֵ��ΧΪ[0,7]��
 *
 * @retval #OS_ERRNO_SHARED_TIMER_ID_INVALID       0x02002e72������Ӳ����ʱ������ID�Ƿ���
 * @retval #SRE_OK                                 0x00000000��ǿ��ɾ������Ӳ����ʱ����Դ�ɹ���
 * @par ����:
 * SRE_timer.h���ýӿ��������ڵ�ͷ�ļ���
 * @since  RTOSck V100R003C00
 * @see ��
 */
extern UINT32 SRE_McHwTmrForceDelete(UINT32 uwMcHwTmrId);
#endif

#ifdef __cplusplus
#if __cplusplus
 }
#endif
#endif

#endif /* _SRE_TIMER_H */

