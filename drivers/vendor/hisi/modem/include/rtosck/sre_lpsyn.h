/**
 * @file sre_lpsyn.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ���������ͬ����Ԫģ��h�ļ��� \n
 */

/**
 * @defgroup SRE_lpsyn LPͬ����Ԫ
 * @ingroup v_Patch
 */

#ifndef _SRE_LPSYN_H
#define _SRE_LPSYN_H
#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/**
 * @ingroup SRE_lpsyn
 *
 * ����ͬ����ԪID
 */
#define LP_INNER_GROUP_SYNC_UNIT_ID                         0

/**
 * @ingroup SRE_lpsyn
 *
 * LPͬ��Ĭ�ϳ�ʱʱ��
 */
#define DEFAULT_SYN_OVERTIME                                15000

/**
 * @ingroup SRE_lpsyn
 *
 * LPͬ���׶�ö��
 */
typedef enum tagLPSyncType
{
    LP_SYNC_TYPE_FETCH     = 0,           /**< ���ؽ׶�            */
    LP_SYNC_TYPE_ACTIVE    = 1,           /**< ����׶�            */
    LP_SYNC_TYPE_DEACTIVE  = 2,           /**< ȥ����׶�          */
} LP_SYNC_TYPE;

/**
 * @ingroup SRE_lpsyn
 *
 * LPͬ���׶�ö��
 */
typedef enum tagLPsynRegType
{
    LP_SYNC_TYPE_SP    = 1,               /**< ��̬��������            */
    LP_SYNC_TYPE_DL    = 2,               /**< ��̬��������            */
    LP_SYNC_TYPE_DP    = 4                /**< ��̬��������            */
} LP_SYNC_UINT_TYPE;

/**
 * @ingroup SRE_lpsyn
 *
 * LPͬ����Ϣ�ṹ��
 */
typedef struct taglpsyninfo
{   
    UINT32 uwPatchNo;                     /**< �������ⲿ��Ԫ��           */
    LP_SYNC_UINT_TYPE enUnitType;         /**< ��Ԫ���� DL DP SP          */
    LP_SYNC_TYPE enPhaseType;             /**< ���ؽ׶� ���� ȥ���� ����  */
}LP_SYN_INFO_S;

/**
* @ingroup  SRE_lpsyn
* @brief ����ͬ����Ϣ���ͺ������͡�
*
* @par ����:
* �û�ͨ��ͬ����Ϣ���ͺ������Ͷ�����Ϣ���͹��Ӻ�����LPͬ��ģ����ø����͵Ĺ��Ӻ���������Ϣ����ͬ����
*
* @attention �ޡ�
*
* @param  uwCpuMask  [IN] ����#UINT32������ͬ��CPU��bitMap��
* @param  uwGroupID  [IN] ����#UINT32���ĸ��鷢���ͬ��������Ϣ��Ҫ�����˴��ݸ��Ӻˡ�
* @param  enSyncType [IN] ����#LP_SYNC_TYPE��������Ϣ�Ľ׶Σ����ڽ�����Ϣʱ��Բ�ͬ�׶�����ͬ����
*
* @retval #SRE_OK  0����Ϣ���ͳɹ���
* @retval ��������Ϣ����ʧ�ܡ�
* @par ����:
* <ul><li>sre_lpsyn.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since UniDSP V100R001C02
* @see �ޡ�
*/
typedef UINT32 (* SRE_MCSYNMSGHOOK_FUNCPTR)(UINT32 uwCpuMask, UINT32 uwGroupID, LP_SYNC_TYPE enSyncType);

/**
 * @ingroup SRE_lpsyn
 *
 * ͬ����Ԫ�׶δ������ṹ���塣
 */
typedef struct tagMCSynProFunc
{
    OS_VOID_FUNC               pfnNormalHook;          /**< ͬ���׶εĴ�����     */
    SRE_MCSYNMSGHOOK_FUNCPTR   pfnSendSynMsgHook;      /**< ����ͬ����Ϣ�Ĺ��Ӻ��� */
} MC_SYN_PROFUNC;

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺����ͬ����Ԫ���ڱ�ʹ�á�
 *
 * ֵ: 0x02002c01
 *
 * �������:�ڽ���ͬ������ǰ��ȷ�����е�LPͬ�����Ѿ��˳���
 */
#define OS_ERRNO_LPSYN_STARTSYN_USINGOTHERUNIT             SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x01)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺����ͬ����Ϣʧ�ܡ�
 *
 * ֵ: 0x02002c02
 *
 * �������:��ο��û�ע�����Ϣ���ͽӿ�ʧ��ԭ��Ľ��������
 */
#define OS_ERRNO_LPSYN_STARTSYN_SENDMSGFAIL                SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x02)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺����ͬ��CPU�����ΪNULL��
 *
 * ֵ: 0x02002c03
 *
 * �������:ͬ��ʱCPU���벻��Ϊ�ա�
 */
#define OS_ERRNO_LPSYN_STARTSYN_MASKPTRISNULL              SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x03)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����붨��: ��ǰLP����û����Ч�Ŀ���ͬ���ĺ�
 *
 * ֵ: 0x02002c04
 *
 *�������:ȷ����LP�������õ���Ч���Ƿ��Ѿ����ߣ����߲鿴��Ҫͬ����LP���е���Ч�˷�Χ�Ƿ�����Ϊ0��
 */
#define OS_ERROR_LPSYN_NO_CORE_IN_THIS_IMAGE               SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x04)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺��ʼͬ��ʱ��ʱ��
 *
 * ֵ: 0x02002c05
 *
 * �������:��������ͬ������ʱ�䡣
 */
#define OS_ERRNO_LPSYN_STARTSYN_TIMEOUT                    SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x05)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺û��ע��ͬ����Ϣ���ͺ�����
 *
 * ֵ: 0x02002c06
 *
 * �������:��ע��ͬ����Ϣ���ͺ�����
 */
#define OS_ERRNO_LPSYN_STARTSYN_SENDFUNCISNULL             SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x06)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺�������ͬ����Ԫû�н���ͬ��״̬��
 *
 * ֵ: 0x02002c08
 *
 * �������:ͬ��ʧ�ܣ����·���ͬ�����߼��ͬ����Ϣ����ʱ�û�����Ĺ�����ID�Ƿ�Ϊ��Ҫͬ������Ч������ID��
 */
#define OS_ERRNO_LPSYN_PROCSYN_STATUSINVALID               SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x08)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺ִ��ͬ����Ԫ��ʱ��
 *
 * ֵ: 0x02002c09
 *
 * �������:����ͬ����ʱʱ�䡣
 */
#define OS_ERRNO_LPSYN_PROCSYN_TIMEOUT                     SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x09)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺���øú����ĺ˲��ǿ�ʼͬ���ĺˡ�
 *
 * ֵ: 0x02002c0a
 *
 * �������:���øú����ͷ���ú���������ͬһ���ˡ�
 */
#define OS_ERRNO_LPSYN_PROCSYN_VCPUIDINVALID               SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x0a)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺ͬ����Ԫû�н���ͬ��״̬��
 *
 * ֵ: 0x02002c0c
 *
 * �������:���·���ͬ����
 */
#define OS_ERRNO_LPSYN_ENDSYN_STATUSINVALID                SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x0c)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺����ͬ�����̳�ʱ��
 *
 * ֵ: 0x02002c0d
 *
 * �������:����ͬ����ʱʱ�䡣
 */
#define OS_ERRNO_LPSYN_ENDSYN_TIMEOUT                      SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x0d)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺����ͬ�����̵ĺ˲��ǿ�ʼͬ���ĺˡ�
 *
 * ֵ: 0x02002c0e
 *
 * �������:��ʼ�ͽ���ͬ��������ͬһ���ˡ�
 */
#define OS_ERRNO_LPSYN_ENDSYN_VCPUIDINVALID                SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x0e)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺����ͬ����Ϣ���ͺ���ΪNULL��
 *
 * ֵ: 0x02002c0f
 *
 * �������:ͬ����Ϣ�ĺ����ĵ�ַ����ΪNULL��
 */
#define OS_ERRNO_LPSYN_REGSENDHOOK_HOOKISNULL              SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x0f)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺����ͬ����Ԫ��ID���ڵ���ͬ����Ԫ�������Ŀ��
 *
 * ֵ: 0x02002c10
 *
 * �������:ȷ��ͬ����Ԫ��ID����Ϊ0��
 */
#define OS_ERRNO_LPSYN_SETARGS_SYNIDINVALID                SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x10)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺ͬ����Ԫû�б�ע�ᡣ
 *
 * ֵ: 0x02002c11
 *
 * �������:���ʼ��ͬ����Ԫ��
 */
#define OS_ERRNO_LPSYN_SETARGS_STATUSINVALID               SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x11)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺����ͬ����Ԫ��ID���ڵ���ͬ����Ԫ�������Ŀ��
 *
 * ֵ: 0x02002c12
 *
 * �������:ͬ����ԪID����Ϊ0��
 */
#define OS_ERRNO_LPSYN_GETARGS_SYNIDINVALID                SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x12)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺ͬ����Ԫû�б�ע�ᡣ
 *
 * ֵ: 0x02002c13
 *
 * �������:���ʼ��ͬ����Ԫ��
 */
#define OS_ERRNO_LPSYN_GETARGS_STATUSINVALID               SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x13)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺����Ļ�ȡ������ַ��ָ��ΪNULL��
 *
 * ֵ: 0x02002c14
 *
 * �������:ȷ�������ָ�벻��NULL��
 */
#define OS_ERRNO_LPSYN_GETARGS_INPUTADDRISNULL             SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x14)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺ͬ��ģ���ID�Ƿ���
 *
 * ֵ: 0x02002c15
 *
 * �������:�Ų�ͬ��ģ�������Ϣ�Ƿ񱻲ȡ�
 */
#define OS_ERRNO_LPSYN_UNIT_ERROR                          SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x15)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺���˻�û�з���ͬ����
 *
 * ֵ: 0x02002c16
 *
 * �������:�鿴�����Ƿ���ͬ����
 */
#define OS_ERRNO_LPSYN_UNIT_RUNNING                        SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x16)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺��ǰ�˲���ͬ����ͬ���ķ�Χ��
 *
 * ֵ: 0x02002c17
 *
 * �������:�鿴LP���ʼ���Ƿ�ɹ����߼�鵱ǰ�˴���ͬ����Ϣʱ�����ͬ��������ID�Ƿ�Ϸ���
 */
#define OS_ERRNO_LPSYN_NOT_IN_SYNLIST                      SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x17)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺���˺ʹӺ˵�ͬ������ƥ�䣬����ͬһ��ͬ���С�
 *
 * ֵ: 0x02002c18
 *
 * �������:�鿴���˺ʹӺ�ͬ���Ƿ�ƥ�䡣
 */
#define OS_ERRNO_LPSYN_ALREADY_RESTART                     SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x18)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺ͬ�������д���
 *
 * ֵ: 0x02002c19
 *
 * �������:�鿴����ͬ�������Ƿ��Ѿ���ʱ��
 */
#define OS_ERRNO_LPSYN_HAS_ERROR                           SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x19)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺ͬ����Ϣ��ȡʧ�ܡ�
 *
 * ֵ: 0x02002c1a
 *
 * �������:�鿴��ǰ�Ƿ���ͬ�������У�ֻ��ͬ�����̲��ܻ�ȡͬ����Ϣ��
 */
#define OS_ERRNO_LPSYN_INFO_GET_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x1a)

/**
 * @ingroup SRE_lpsyn
 * ͬ����Ԫ�����룺ͬ����Ϣ��ȡ�ӿ����ΪNULL��
 *
 * ֵ: 0x02002c1b
 *
 * �������:�鿴����洢ͬ����Ϣ�Ľṹ��ָ���Ƿ�ΪNULL��
 */
#define OS_ERRNO_LPSYN_INFO_PARA_IS_NULL                   SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x1b)

/**
 * @ingroup  SRE_lpsyn
 * @brief ͬ����Ϣ��������
 *
 * @par ����:
 * ���øýӿڽ���ͬ����Ϣ�����û����յ�ͬ����Ϣ����øýӿڽ���ͬ����Ϣ����
 ��ͬ����Ϣ�ķ��ͺ���Ϊ�û��ṩ��ͨ��#SRE_LPRegSynMsgSendHook�ӿ�ע�ᵽϵͳ�У����ýӿ��ڲ�����ͬ��ִ�н׶κ�����
 *
 * @attention
 * <ul>
 * <li>ʹ�øýӿ���Ҫ��������� </li>
 * </ul>
 *
 * @param uwGroupID [IN] ����#UINT32 ����̬���ؼ�����������Ϣ��ID����Ҫ�û���֤����ȷ�ԡ�
 * 
 * @retval #OS_ERRNO_LPSYN_UNIT_ERROR                              0x02002c19��ͬ��ģ���ID�Ƿ���
 * @retval #OS_ERRNO_LPSYN_UNIT_RUNNING                            0x02002c1a�����˻�û�з���ͬ����
 * @retval #OS_ERRNO_LPSYN_NOT_IN_SYNLIST                          0x02002c1b����ǰ�˲���ͬ����ͬ���ķ�Χ��
 * @retval #OS_ERRNO_LPSYN_ALREADY_RESTART                         0x02002c1c�����˺ʹӺ˵�ͬ������ƥ�䣬����ͬһ��ͬ���С�
 * @retval #OS_ERRNO_LPSYN_HAS_ERROR                               0x02002c1d��ͬ�������д���
 * @retval #OS_ERRNO_LPSYN_ALREADY_ENDSYN                          0x02002c1e�������˷���ͬ��ʱ���Ӻ��Ѿ��������ͬ����״̬��
 * @retval #OS_ERRNO_LPSYN_PROCSYN_STATUSINVALID                   0x02002c0c, �������ͬ����Ԫû�н���ͬ��״̬��
 * @retval #SRE_OK                                                 0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_lpsyn.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_LPRegSynMsgSendHook
 */
extern UINT32 SRE_MCSynProcess(UINT32 uwGroupID);

/**
 * @ingroup  SRE_lpsyn
 * @brief ע��ͬ����Ϣ���͹��Ӻ����Ľӿڡ�
 *
 * @par ����:
 * ע��ͬ����Ϣ���ͺ����Ľӿڣ�ͬ����Ϣ���ͺ������û������Լ���ҵ����ж��塣
 *
 * @attention
 * <ul>
 * <li>���һ��������Ҫ����ͬ����������ʹ�øýӿ�ע��ͬ����Ϣ���ͺ�����</li>
 * <li>��֧����LP����������ע���޸�ͬ����Ϣ���ͺ�����</li>
 * <li>����ͬ����Ϣ���Ӿ�����Ψһ�������ڸ���ʹ��ͬһ���ӡ�</li>
 * </ul>
 *
 * @param  pfnHook [IN] ����#SRE_MCSYNMSGHOOK_FUNCPTR��ͬ����Ϣ���ͺ���ָ�롣
 *
 * @retval #OS_ERRNO_LPSYN_REGSENDHOOK_HOOKISNULL                  0x02002c13������ͬ����Ϣ���ͺ���ΪNULL��
 * @retval #SRE_OK                                                 0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_lpsyn.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MCSynProcess
 */
extern UINT32 SRE_LPRegSynMsgSendHook(SRE_MCSYNMSGHOOK_FUNCPTR pfnHook);

#if (OS_OPTION_LP_SYN_INFO_GET == YES)

/**
 * @ingroup  SRE_lpsyn
 * @brief ��ȡͬ����Ϣ�ӿڡ�
 *
 * @par ����:
 * ���û����յ�ͬ����Ϣ�󣬵��øýӿڻ�ȡ��ǰͬ��״̬��
 *
 * @attention
 * <ul>
 * <li>�ýӿڱ�����ͬ����ʱ����ã�����᷵�ش����롣</li>
 * <li>�Ľӿڽ����ڽ��յ�ͬ����Ϣ����á�</li>
 * </ul>
 *
 * @param uwGroupID  [IN] ����#UINT32 ����̬���ؼ�����������Ϣ��ID����Ҫ�û���֤����ȷ�ԡ�
 * @param pstSynInfo [OUT] ����#LP_SYN_INFO_S ��ͬ������Ϣ�ṹ�塣
 *
 * @retval #OS_ERRNO_LPSYN_INFO_GET_ERROR                          0x02002c1a��ͬ����Ϣ��ȡʧ�ܡ�
 * @retval #OS_ERRNO_LPSYN_INFO_PARA_IS_NULL                       0x02002c1b��ͬ����Ϣ��ȡ�ӿ����ΪNULL��
 * @retval #SRE_OK                                                 0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_lpsyn.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MCSynProcess
 */
extern UINT32 SRE_LpSynInfoGet(UINT32 uwGroupID, LP_SYN_INFO_S *pstSynInfo);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_LPSYN_H */

/*
 * History: \n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

