/**
 * @file sre_sem.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * �������ź���ģ�����ͷ�ļ��� \n
 */

#ifndef _SRE_SEM_H
#define _SRE_SEM_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**@defgroup SRE_sem �ź���
  *@ingroup SRE_comm
  */

/**
 * @ingroup SRE_sem
 * �ź����ȴ�ʱ���趨����ʾ���õȴ���
 */
#define OS_WAIT_FOREVER     0xFFFFFFFF

/**
 * �������ź�������״̬���������ź�����ʼ����ֵ��
 */
#define OS_SEM_FULL         1

/**
 * �������ź���ռ��״̬��ͬ�����ź�����ʼ����ֵ��
 */
#define OS_SEM_EMPTY        0

/**
 * @ingroup SRE_sem
 * �ź��������룺��ʼ���ź����ڴ治�㡣
 *
 * ֵ: 0x02000f00
 *
 * �������: ���Խ�˽�еľ�̬�ڴ�ռ����
 */
#define OS_ERRNO_SEM_NO_MEMORY                      SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x00)

/**
 * @ingroup SRE_sem
 * �ź��������룺�ź�������Ƿ����������ɾ������
 *
 * ֵ: 0x02000f01
 *
 * �������: �鿴������ź������ֵ�Ƿ���Ч��
 */
#define OS_ERRNO_SEM_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x01)

/**
 * @ingroup SRE_sem
 * �ź��������룺����ָ��Ϊ�ա�
 *
 * ֵ: 0x02000f02
 *
 * �������: �鿴ָ���Ƿ�����Ϊ�ա�
 */
#define OS_ERRNO_SEM_PTR_NULL                       SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x02)

/**
 * @ingroup SRE_sem
 * �ź��������룺û�п����ź�����
 *
 * ֵ: 0x02000f03
 *
 * �������: �鿴�ź���ģ���Ƿ�򿪣������ø����ź�����
 */
#define OS_ERRNO_SEM_ALL_BUSY                       SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x03)

/**
 * @ingroup SRE_sem
 * �ź��������룺�ź���û�п�����Դ��Pendʱ��Ϊ���ȴ�(�ȴ�ʱ��Ϊ0)ʱ��ȡ�ź���ʧ�ܡ�
 *
 * ֵ: 0x02000f04
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_SEM_UNAVAILABLE                    SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x04)

/**
 * @ingroup SRE_sem
 * �ź��������룺��ֹ�жϴ������������ź�����
 *
 * ֵ: 0x02000f05
 *
 * �������: �鿴�Ƿ����ж���Pend�ź�����
 */
#define OS_ERRNO_SEM_PEND_INTERR                    SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x05)

/**
 * @ingroup SRE_sem
 * �ź��������룺�����л�����ʱ����ֹ�����������ź�����
 *
 * ֵ: 0x02000f06
 *
 * �������: ��Ҫ��������ʱpendû����Դ���õ��ź�����
 */
#define OS_ERRNO_SEM_PEND_IN_LOCK                   SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x06)

/**
 * @ingroup SRE_sem
 * �ź��������룺�ź����ȴ���ʱ��
 *
 * ֵ: 0x02000f07
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_SEM_TIMEOUT                        SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x07)

/**
 * @ingroup SRE_sem
 * �ź��������룺�ź������������
 *
 * ֵ: 0x02000f08
 *
 * �������: �鿴������ź�������ֵ�Ƿ���Ч��
 */
#define OS_ERRNO_SEM_OVERFLOW                       SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x08)

/**
 * @ingroup SRE_sem
 * �ź��������룺�ź���ɾ�������赱ǰֵʱ���������ź���������
 *
 * ֵ: 0x02000f09
 *
 * �������: �����ǰ�ź������������������ܽ���ɾ�����������ֵ������
 */
#define OS_ERRNO_SEM_PENDED                         SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x09)

/**
 * @ingroup SRE_sem
 * �ź��������룺���ж����ͷŻ������ź�����
 *
 * ֵ: 0x02000f0a
 *
 * �������: ֻ���������жԻ������ź�������PV������
 */
#define OS_ERRNO_SEM_MUTEX_POST_INTERR              SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x0A)

/**
 * @ingroup SRE_sem
 * �ź��������룺�ǵ�ǰ�����ź����ĳ������ͷŸ��ź�����
 *
 * ֵ: 0x02000f0b
 *
 * �������: �����ź���ֻ������������ͷţ��������ź�����PV�����������ʹ�á�
 */
#define OS_ERRNO_SEM_MUTEX_NOT_OWNER_POST           SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x0B)

/**
 * @ingroup SRE_sem
 * �ź��������룺ע������ź�������Ϊ0����ע��ʧ�ܡ�
 *
 * ֵ: 0x02000f10
 *
 * �������: �鿴�ź���ģ�����õ��������Ƿ�Ϊ0��
 */
#define OS_ERRNO_SEM_REG_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x10)

/**
 * @ingroup SRE_sem
 * �ź��������룺����#SRE_SemPendListGetʱ��ָ�����ڴ�ռ䲻�㣬�޷�����ȫ������������PID��
 *
 * ֵ: 0x02000f11
 *
 * �������: ���齫���鳤������Ϊ(#OS_TSK_MAX_SUPPORT_NUM + 1) * 4��
 */
#define OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH           SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x11)

/**
 * @ingroup SRE_sem
 * �ź��������룺����#SRE_SemPendListGetʱ������ָ��Ϊ�ջ���uwBufLenС��4��
 *
 * ֵ: 0x02000f12
 *
 * �������: ���β���ΪNULL��ָ���Ļ��泤�Ȳ���С��4��
 */
#define OS_ERRNO_SEM_INPUT_ERROR                    SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x12)

/*
 * @ingroup SRE_sem
 * �ź��������룺�ź�������ʱָ���Ļ��ѷ�ʽ�Ƿ���
 *
 * ֵ: 0x02000f13
 *
 * �������: ���ѷ�ʽֻ��ΪSEM_MODE_FIFO,SEM_MODE_PRIOR��
 */
#define OS_ERRNO_SEM_MODE_INVALID                   SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x13)

/*
 * @ingroup SRE_sem
 * �ź��������룺�����������ź����ĳ�ʼֵֻ��ΪOS_SEM_FULL����OS_SEM_EMPTY��
 *
 * ֵ: 0x02000f14
 *
 * �������: �������ź�����ʼֵֻ��ΪOS_SEM_FULL(1)����OS_SEM_EMPTY(0)��
 */
#define OS_ERRNO_SEM_BIN_VALUE_ERR                  SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x14)

/*
 * @ingroup SRE_sem
 * �ź��������룺�ź������ü������ֵʱָ�������ֵ�Ƿ���
 *
 * ֵ: 0x02000f15
 *
 * �������: ָ�����ź���������ֵ���ܴ���0xFFFF FFFE��
 */
#define OS_ERRNO_SEM_MAXCOUNT_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x15)

/*
 * @ingroup SRE_sem
 * �ź��������룺�ź������ü������ֵʱָ�������ֵС�ڵ�ǰ����ֵ��
 *
 * ֵ: 0x02000f16
 *
 * �������: ָ�����ź���������ֵ����С�ڵ�ǰ����ֵ��
 */
#define OS_ERRNO_SEM_MAXCOUNT_GREATER_THAN_CURRENT  SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x16)

/*
 * @ingroup SRE_sem
 * �ź��������룺�Զ��������ź����������ֵ��
 *
 * ֵ: 0x02000f17
 *
 * �������: ��Ҫ�Զ��������ź����������ֵ��
 */
#define OS_ERRNO_SEM_BIN_NO_MAXCOUNT                SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x17)

/*
 * @ingroup SRE_sem
 * �ź��������룺�����ź����ĵ�ǰ����ֵ���������õ����ֵ��
 *
 * ֵ: 0x02000f18
 *
 * �������: ���õĵ�ǰ����ֵ���ܴ������õ����ֵ��
 */
#define OS_ERRNO_SEM_OVER_MAXCOUNT                  SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x18)

/*
 * @ingroup SRE_sem
 * �ź��������룺��ȡ�ź�����ϸ��Ϣʱ���νṹ��ָ��ΪNULL��
 *
 * ֵ: 0x02000f19
 *
 * �������: ���������ź�����ϸ��Ϣ�Ľṹ��ָ�벻��ΪNULL��
 */
#define OS_ERRNO_SEM_INFO_NULL                      SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x19)

/*
 * @ingroup SRE_sem
 * �ź��������룺�Զ��������ź������赱ǰ����ֵ��
 *
 * ֵ: 0x02000f1a
 *
 * �������: ��Ҫ�Զ��������ź������赱ǰ����ֵ��
 */
#define OS_ERRNO_SEM_BIN_CANNOT_RESET               SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x1A)

/*
 * @ingroup SRE_sem
 * �ź��������룺�������ź����Ļ��ѷ�ʽ��Ϊ���ȼ���ʽ��
 *
 * ֵ: 0x02000f1c
 *
 * �������: �������ź����Ļ��ѷ�ʽ����ΪFIFO��
 */
#define OS_ERRNO_SEM_MUTEX_SHOULD_PRIO              SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x1C)

/*
 * @ingroup SRE_sem
 * �ź��������룺��ȡ��ǰ�ź�������ʱ����ĳ���ΪNULL��
 *
 * ֵ: 0x02000f1d
 *
 * �������: �������ź����Ļ��ѷ�ʽ����ΪFIFO��
 */
#define OS_ERRNO_SEM_COUNT_GET_PTR_NULL             SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x1D)

/*
 * @ingroup SRE_sem
 * �ź��������κ�������У����ڿ���״̬��
 */
#define OS_INVALID_OWNER_ID                         (0xFFFFFFFE)

/**
 * @ingroup SRE_sem
 * �ź���������Ͷ��塣
 */
typedef UINT16 SEM_HANDLE_T;

/**
 * @ingroup SRE_sem
 * �ź���ģ��������Ϣ�Ľṹ�嶨�塣
 */
typedef struct tagSemModInfo
{
    UINT16 usMaxNum;                            /**< ���֧�ֵ��ź�����  */
    UINT16 usReserved;                          /**< ����                */
}SEM_MOD_INFO_S;

/*
 * @ingroup SRE_sem
 * �ź������͡�
 */
typedef enum
{
    SEM_TYPE_COUNT,                             /**< �������ź���    */
    SEM_TYPE_BIN                                /**< �������ź���    */
}OS_SEM_TYPE_E;

/*
 * @ingroup SRE_sem
 * �ź���ģ�鱻�����̻߳��ѷ�ʽ��
 */
typedef enum
{
    SEM_MODE_FIFO,                              /**< �ź���FIFO����ģʽ    */
    SEM_MODE_PRIOR,                             /**< �ź������ȼ�����ģʽ  */
    SEM_MODE_BUTT                               /**< �ź����Ƿ����ѷ�ʽ  */
}OS_SEM_MODE_E;

/**
 * @ingroup SRE_sem
 * �ź���ģ���ȡ�ź�����ϸ��Ϣʱ����Ϣ�ṹ�塣
 */
typedef struct tagSemInfo
{
    UINT32 uwCount;                             /**< �ź������� */
    UINT32 uwOwner;                             /**< �ź���ռ���ߣ����ڼ������ź�������¼�������һ���ź�������ߣ����û�б������ã���ΪOS_THREAD_ID_INVALID */
    OS_SEM_MODE_E enMode;                       /**< �ź������ѷ�ʽ��ΪSEM_MODE_FIFO��SEM_MODE_PRIOR */
    OS_SEM_TYPE_E enType;                       /**< �ź������ͣ�ΪSEM_TYPE_COUNT�������ͣ���SEM_TYPE_BIN�������ƣ�*/
}SEM_INFO_S;

/**
 * @ingroup SRE_sem
 * @brief ����һ���������ź�����
 *
 * @par ����:
 * �����û�ָ���ļ���ֵ������һ���������ź������趨��ʼ��������ֵ�����ѷ�ʽΪFIFO��
 * @attention
 * <ul><li>�����Ƿ�ɹ����ܵ�"�����ź����ü�����"��"���֧���ź���"����������ơ�</li></ul>
 *
 * @param uwCount [IN] ����Ϊ#UINT32����������ʼֵ��ȡֵ��ΧΪ[0, 0xFFFFFFFE]��
 * @param pusSemHandle [OUT] ����Ϊ#SEM_HANDLE_T *������ź��������
 *
 * @retval #OS_ERRNO_SEM_OVERFLOW 0x02000f08����������ʼֵ������Χ��
 * @retval #OS_ERRNO_SEM_ALL_BUSY 0x02000f03��û�п����ź�������������"���֧���ź���"���á�
 * @retval #OS_ERRNO_SEM_PTR_NULL 0x02000f02�����ָ��Ϊ�ա�
 * @retval #SRE_OK                0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemDelete | SRE_SemCCreate | SRE_SemBCreate
 */
extern  UINT32 SRE_SemCreate(UINT32 uwCount,  SEM_HANDLE_T *pusSemHandle);

/**
 * @ingroup SRE_sem
 * @brief ����һ���������ź�����
 *
 * @par ����:
 * ����һ�������ź������趨��ʼ��������ֵ��
 * @attention
 * <ul><li>�����Ƿ�ɹ����ܵ�"���֧���ź���"����������ơ�</li></ul>
 *
 * @param uwCount [IN]       ����#UINT32����������ʼֵ��ȡֵ��ΧΪ[0, 0xFFFFFFFE]��
 * @param enMode  [IN]       ����#OS_SEM_MODE_E���ź���ģʽ��ȡֵ��ΧΪSEM_MODE_FIFO����SEM_MODE_PRIOR��
 * @param pusSemHandle [OUT] ����#SEM_HANDLE_T *������ź��������
 *
 * @retval #OS_ERRNO_SEM_OVERFLOW     0x02000f08����������ʼֵ������Χ��
 * @retval #OS_ERRNO_SEM_ALL_BUSY     0x02000f03��û�п����ź�������������"���֧���ź���"���á�
 * @retval #OS_ERRNO_SEM_PTR_NULL     0x02000f02�����ָ��Ϊ�ա�
 * @retval #OS_ERRNO_SEM_MODE_INVALID 0x02000f13��ָ���Ļ���ģʽ�Ƿ���
 * @retval #SRE_OK                    0x00000000�������ɹ���
 * @par ����:
 * <ul><li>SRE_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_SemDelete | SRE_SemCreate | SRE_SemBCreate
 */
extern UINT32 SRE_SemCCreate(UINT32 uwCount, SEM_HANDLE_T *pusSemHandle, OS_SEM_MODE_E enMode);

/**
 * @ingroup SRE_sem
 * @brief ����һ���������ź�����
 *
 * @par ����:
 * ����һ���������ź������趨��ʼ��������ֵ��
 * @attention
 * <ul><li>�����Ƿ�ɹ����ܵ�"���֧���ź���"����������ơ�</li></ul>
 *
 * @param uwCount [IN]       ����#UINT32����������ʼֵ��ȡֵ��ΧΪOS_SEM_FULL��OS_SEM_EMPTY��
 * @param enMode  [IN]       ����#OS_SEM_MODE_E���ź���ģʽ��ȡֵ��ΧΪSEM_MODE_FIFO����SEM_MODE_PRIOR��
 * @param pusSemHandle [OUT] ����#SEM_HANDLE_T *������ź��������
 *
 * @retval #OS_ERRNO_SEM_BIN_VALUE_ERR     0x02000f14����������ʼֵ����
 * @retval #OS_ERRNO_SEM_ALL_BUSY          0x02000f03��û�п����ź�������������"���֧���ź���"���á�
 * @retval #OS_ERRNO_SEM_PTR_NULL          0x02000f02�����ָ��Ϊ�ա�
 * @retval #OS_ERRNO_SEM_MODE_INVALID      0x02000f13��ָ���Ļ���ģʽ�Ƿ���
 * @retval #OS_ERRNO_SEM_MUTEX_SHOULD_PRIO 0x02000f1c���������ź����Ļ��ѷ�ʽֻ��Ϊ���ȼ���ʽ��
 * @retval #SRE_OK                         0x00000000�������ɹ���
 * @par ����:
 * <ul><li>SRE_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_SemDelete
 */
extern UINT32 SRE_SemBCreate(UINT32 uwCount, SEM_HANDLE_T *pusSemHandle, OS_SEM_MODE_E enMode);

/**
 * @ingroup SRE_sem
 * @brief ɾ��һ���ź�����
 *
 * @par ����:
 * ɾ���û�������ź������ָ�����ź�������������������ڸ��ź�������ɾ��ʧ�ܡ�
 * @attention  ��
 *
 * @param usSemHandle [IN] ����Ϊ#SEM_HANDLE_T���ź����������Դ���ź��������ɹ������ֵ��
 *
 * @retval #OS_ERRNO_SEM_INVALID 0x02000f01���ź������Ϊ�Ƿ�ֵ�����ѱ�ɾ����
 * @retval #OS_ERRNO_SEM_PENDED  0x02000f09�������������ڸ��ź�������ֹɾ����
 * @retval #SRE_OK               0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemCreate
 */
extern UINT32 SRE_SemDelete(SEM_HANDLE_T usSemHandle);

/**
 * @ingroup SRE_sem
 * @brief ����һ���ź��������ֵ��
 *
 * @par ����:
 * ����һ���ź������������ֵ��
 * @attention  ��
 *
 * @param usSemHandle [IN] ����Ϊ#SEM_HANDLE_T���ź����������Դ���ź��������ɹ������ֵ��
 * @param uwMaxCount  [IN] ����Ϊ#UINT32�������õ�������ֵ������С�ڵ�ǰ����ֵ���Ҳ��ܴ���0xFFFFFFFE��
 *
 * @retval #OS_ERRNO_SEM_INVALID           0x02000f01���ź������Ϊ�Ƿ�ֵ�����ѱ�ɾ����
 * @retval #OS_ERRNO_SEM_MAXCOUNT_INVALID  0x02000f15�����õ����ֵ�Ƿ���
 * @retval #OS_ERRNO_SEM_BIN_NO_MAXCOUNT   0x02000f17���Զ������ź����������ֵ��
 * @retval #OS_ERRNO_SEM_MAXCOUNT_GREATER_THAN_CURRENT 0x02000f16���ź������ü������ֵʱָ�������ֵС�ڵ�ǰ����ֵ��
 * @retval #SRE_OK                         0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_SemCreate | SRE_SemReset
 */
extern UINT32 SRE_SemCMaxCountSet(SEM_HANDLE_T usSemHandle, UINT32 uwMaxCount);

/**
 * @ingroup SRE_sem
 * @brief �����ź�����������ֵ������
 *
 * @par ����:
 * �����û������ź�������ͼ���ֵ�������ź�����������ֵ��
 * @attention
 * <ul><li>��������������ڸ��ź�����������ʧ�ܡ�</li></ul>
 *
 * @param usSemHandle [IN] ����Ϊ#SEM_HANDLE_T���ź����������Դ���ź��������ɹ������ֵ��
 * @param uwCount [IN] ����Ϊ#UINT32���������趨ֵ��ȡֵ��ΧΪ[0, 0xFFFFFFFE]��
 *
 * @retval #OS_ERRNO_SEM_INVALID       0x02000f01���ź������Ϊ�Ƿ�ֵ�����ѱ�ɾ����
 * @retval #OS_ERRNO_SEM_OVERFLOW      0x02000f08���������趨ֵ����OS_SEM_COUNT_MAX��
 * @retval #OS_ERRNO_SEM_BIN_CANNOT_RESET    0x02000f1a���Զ��������ź������赱ǰ����ֵ��
 * @retval #OS_ERRNO_SEM_PENDED        0x02000f09�������������ڸ��ź�������ֹ���衣
 * @retval #OS_ERRNO_SEM_OVER_MAXCOUNT 0x02000f18���������趨ֵ�������õ����ֵ��
 * @retval #SRE_OK                     0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemCreate | SRE_SemCountGet | SRE_SemCMaxCountSet
 */
extern UINT32 SRE_SemReset(SEM_HANDLE_T usSemHandle, UINT32 uwCount);

/**
 * @ingroup SRE_sem
 * @brief ��ȡ�ź�����������ֵ��
 *
 * @par ����:
 * �����û������ź�������ͼ���ֵ����ȡ�ź�����������ֵ��
 * @attention ��
 *
 * @param usSemHandle [IN]  ����Ϊ#SEM_HANDLE_T���ź����������Դ���ź��������ɹ������ֵ��
 * @param puwSemCnt   [OUT] ����Ϊ#UINT32 *�������ź�������ֵָ�롣
 *
 * @retval #OS_ERRNO_SEM_INVALID         0x02000f01���ź������Ϊ�Ƿ�ֵ�����ѱ�ɾ����
 * @retval #OS_ERRNO_SEM_COUNT_GET_PTR_NULL      0x02000f1d����ȡ��ǰ�ź�������ʱ����ĳ���ΪNULL��
 * @retval #SRE_OK                       0x00000000����ȡ�ź���������ֵ�ɹ���
 * @par ����:
 * <ul><li>sre_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemCreate | SRE_SemReset | SRE_SemInfoGet
 */
extern UINT32 SRE_SemCountGet(SEM_HANDLE_T usSemHandle, UINT32 *puwSemCnt);

/**
 * @ingroup SRE_sem
 * @brief �ȴ�һ���ź�����
 *
 * @par ����:
 * �ȴ��û������ź������ָ�����ź��������������ֵ����0����ֱ�Ӽ�1���سɹ�����������������
 * �ȴ������̷߳������ź������ȴ���ʱʱ����趨��
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>�ȴ�ʱ�����ѡ����ȴ����ȴ��ض�ʱ�䡢���õȴ���</li>
 * <li>�ýӿ�ֻ�ܱ�������á�</li>
 * <li>������������£��û�ҪPEND�ź�����Ҫ��֤��ǰ�п����ź�����Դ��</li>
 * </ul>
 *
 * @param usSemHandle [IN] ����Ϊ#SEM_HANDLE_T���ź����������Դ���ź��������ɹ������ֵ��
 * @param uwTimeout [IN] ����Ϊ#UINT32���ȴ�ʱ�����ƣ���λΪtick��ȡֵ��ΧΪ[0, 0xffffffff]��
 * #OS_NO_WAIT��0��ʾ���ȴ���#OS_WAIT_FOREVER��0xffffffff��ʾ���õȴ���
 *
 * @retval #OS_ERRNO_SEM_INVALID      0x02000f01���ź������Ϊ�Ƿ�ֵ�����ѱ�ɾ����
 * @retval #OS_ERRNO_SEM_UNAVAILABLE  0x02000f04���ź�����ȴ�ʱ��ȡʧ�ܡ�
 * @retval #OS_ERRNO_SEM_PEND_INTERR  0x02000f05���жϴ�������ֹ����������
 * @retval #OS_ERRNO_SEM_PEND_IN_LOCK 0x02000f06��ϵͳ������ԴΪ0�������л�����ʱ����ֹ������������
 * @retval #OS_ERRNO_SEM_TIMEOUT      0x02000f07���ź����ȴ���ʱ��
 * @retval #SRE_OK                    0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemPost
 */
extern UINT32 SRE_SemPend(SEM_HANDLE_T usSemHandle, UINT32 uwTimeout);

/**
 * @ingroup SRE_sem
 * @brief ����ָ�����ź�����
 *
 * @par ����:
 * ����ָ�����ź�������û������ȴ����ź�������ֱ�ӽ���������1���ء�
 * ������ݻ��ѷ�ʽ������Ӧ����������FIFO��ʽ���������������������ȼ���ʽ���������ڴ��ź�����������ȼ�����
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>��δ�����������£�������ѵ��������ȼ����ڵ�ǰ����������̷��������л���</li>
 * <li>���������л�ʱ�����֧�����ȼ����ѷ�ʽ���Ҵ����ź���ʱָ�����ѷ�ʽΪ���ȼ������������ڸ��ź����ϵ�������ȼ�����</li>
 * </ul>
 * @param usSemHandle [IN] ����Ϊ#SEM_HANDLE_T���ź����������Դ���ź��������ɹ������ֵ��
 *
 * @retval #OS_ERRNO_SEM_INVALID              0x02000f01���ź������Ϊ�Ƿ�ֵ�����ѱ�ɾ����
 * @retval #OS_ERRNO_SEM_OVERFLOW             0x02000f08���ź����Ӳ����������
 * @retval #OS_ERRNO_SEM_MUTEX_POST_INTERR    0x02000f0a���ж����ͷŻ������ź�����
 * @retval #OS_ERRNO_SEM_MUTEX_NOT_OWNER_POST 0x02000f0b���ǻ����ź����ĳ��������ͷŴ˻����ź�����
 * @retval #SRE_OK                            0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemPend
 */
extern UINT32 SRE_SemPost(SEM_HANDLE_T usSemHandle);

/**
 * @ingroup SRE_sem
 * @brief ��ȡ������ָ�������ź����ϵ�����PID�嵥��
 *
 * @par ����:
 * �����û�ָ���ĺ����ź����������ȡ������ָ�������ź����ϵ�����PID�嵥���������������ڸú����ź������򷵻������ڸú����ź�����������Ŀ���Լ���Ӧ�����PID��
 * ��û�����������ڸú����ź������򷵻������ڸú����ź�����������ĿΪ0��
 * @attention
 * <ul><li>�û�Ӧ��֤�洢����PID�嵥���ڴ�ռ��㹻�󣬽��齫uwBufLen����Ϊ(#OS_TSK_MAX_SUPPORT_NUM + 1) * 4bytes��</li></ul>
 *
 * @param usSemHandle   [IN]  ����Ϊ#SEM_HANDLE_T���ź����������Դ���ź��������ɹ������ֵ��
 * @param puwTskCnt [OUT] ����Ϊ#UINT32 *�������ڸú����ź�������������
 * @param puwPidBuf [OUT] ����Ϊ#UINT32 *�����û�ָ�����ڴ������׵�ַ�����ڴ洢������ָ�������ź���������PID��
 * @param uwBufLen  [IN]  ����Ϊ#UINT32���û�ָ�����ڴ�����ĳ��ȣ���λ���ֽڣ���
 *
 * @retval #OS_ERRNO_SEM_INVALID              0x02000f01���ź������Ϊ�Ƿ�ֵ�����ѱ�ɾ����
 * @retval #OS_ERRNO_SEM_INPUT_ERROR          0x02000f12��ָ��Ϊ�ջ���uwBufLenС��4��
 * @retval #OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH 0x02000f11��ָ�����ڴ�ռ䲻�㣬���ڴ��е�����PID��Ч��
 * @retval #SRE_OK                            0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskPendSemGet | SRE_McSemPendListGet | SRE_SemInfoGet
 */
extern UINT32 SRE_SemPendListGet( SEM_HANDLE_T usSemHandle,
                                 UINT32 *puwTskCnt,
                                 UINT32 *puwPidBuf,
                                 UINT32  uwBufLen );

/**
 * @ingroup SRE_sem
 * @brief ��ȡ�ź�����ϸ��Ϣ:�ź�����ǰ����ֵ���ź���������(���һ��pend�ɹ����߳�ID)���ź������ѷ�ʽ���ź������͡�
 *
 * @par ����:
 * �����û������ź��������ȡ�ź�����ϸ��Ϣ��
 * @attention ��
 *
 * @param usSemHandle [IN]  ����Ϊ#SEM_HANDLE_T���ź����������Դ���ź��������ɹ������ֵ��
 * @param pstSemInfo  [OUT] ����Ϊ#SEM_INFO_S*���ź�����ϸ��Ϣ:uwCount--�ź���������uwOwner--�ź���ռ���ߣ�enMode--�ź������ѷ�ʽ��enType--�ź������͡�
 *
 * @retval #OS_ERRNO_SEM_INFO_NULL       0x02000f19������ĳ��νṹ��ָ��ΪNULL��
 * @retval #OS_ERRNO_SEM_INVALID         0x02000f01���ź�������Ƿ����ѱ�ɾ����
 * @retval #SRE_OK                       0x00000000����ȡ�ź���������ֵ�ɹ���
 * @par ����:
 * <ul><li>sre_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_SemCountGet | SRE_SemPendListGet
 */
extern UINT32 SRE_SemInfoGet(SEM_HANDLE_T usSemHandle, SEM_INFO_S *pstSemInfo);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _SRE_SEM_H */


