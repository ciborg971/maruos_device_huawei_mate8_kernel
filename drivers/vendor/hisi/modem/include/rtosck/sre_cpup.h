/**
* @file sre_cpup.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* ������CPUռ����ģ�����ͷ�ļ��� \n
*/

/** @defgroup SRE_cpup CPUռ����
   *@ingroup SRE_kernel
*/

#ifndef _SRE_CPUP_H
#define _SRE_CPUP_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_cpup
 * CPUP�����룺CPUPģʽ���ò���ȷ��
 *
 * ֵ: 0x02000c00
 *
 * �������: CPUPģʽ��������ΪOS_CPUP_MODE_SYS����OS_CPUP_MODE_THREAD��
 */
#define OS_ERRNO_CPUP_MODE_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x00)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺����(CPUP�澯��ֵ)�趨���ڹ涨��Χ(0,10000]��
 *
 * ֵ: 0x02000c01
 *
 * �������: CPUP�澯��ֵ�趨�ڹ涨��Χ(0,10000]�ڡ�
 */
#define OS_ERRNO_CPUP_INTERVAL_NOT_SUITED       SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x01)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺ָ�����ΪNULL��
 *
 * ֵ: 0x02000c02
 *
 * �������: �����0����Ч��ַ��
 */
#define OS_ERRNO_CPUP_PTR_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x02)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺�ָ���ֵ�趨��С�ڸ澯��ֵ��
 *
 * ֵ: 0x02000c03
 *
 * �������: �ָ���ֵС�ڸ澯��ֵ��
 */
#define OS_ERRNO_CPUP_RESUME_NOT_SUITED         SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x03)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺CPUP��ʼ�������ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02000c04
 *
 * �������: ȷ��ȱʡ��̬�ڴ��Ƿ��㹻���Լ���������(�μ����ú�OS_CPUP_SAMPLE_RECORD_NUM)�Ƿ����
 */
#define OS_ERRNO_CPUP_NO_MEMORY                 SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x04)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺��osStart֮ǰ����CPUPģ����ع��ܽӿڡ�
 *
 * ֵ: 0x02000c05
 *
 * �������: ����CPUPģ�鹦�ܽӿ�ʱ����鿴�Ƿ���osStart֮��
 */
#define OS_ERRNO_CPUP_OS_NOT_STARTED            SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x05)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺CPUP����ģʽ����ȷ��
 *
 * ֵ: 0x02000c06
 *
 * �������: CPUPģ������ģʽ����������ȷ��ģʽ�����ܵ������Ӧ�Ľӿڡ�
 */
#define OS_ERRNO_CPUP_MODE_NOT_CORRECT          SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x06)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺CPUP����ʱ����Ϊ0��
 *
 * ֵ: 0x02000c07
 *
 * �������: ϵͳ��CPUP���ò���ʱ�����������0����CPUP�澯���ܴ�ʱ���̼߳�CPUP����ʱ����Ҳ�������0��
 */
#define OS_ERRNO_CPUP_SAMPLE_TIME_ZERO          SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x07)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺ָ���˺ŷǷ���
 *
 * ֵ: 0x02000c08
 *
 * �������: ָ����С����������
 */
#define OS_ERRNO_CPUP_COREID_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x08)

/**
 * @ingroup SRE_cpup
 * �¼������룺��ȡCPUPʱ�������ID�Ƿ���
 *
 * ֵ: 0x02000c09
 *
 * �������: ������Ϸ�����ID��
 */
#define OS_ERRNO_CPUP_TASKID_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_CPUP, 0x09)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺CPUP��������Ϊ�㡣
 *
 * ֵ: 0x02000c0a
 *
 * �������: ���ò����ظ�����(0,30]֮�䡣
 */
#define OS_ERRNO_CPUP_SAMPLE_NUM_ZERO           SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x0A)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺CPUP���ܿ���δ�򿪻���δ��ʼ��ʱ����ȡCPUP�����ø澯��ֵ���߲���IDLE����ִ��ʱ�䡣
 *
 * ֵ: 0x02000c0b
 *
 * �������: �豣֤�ڴ򿪹��ܿ���,��osStart֮����ܻ�ȡCPUP�����ø澯��ֵ���߲���IDLE����ִ��ʱ�䡣
 */
#define OS_ERRNO_CPUP_NOT_INITED                SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x0B)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺ʹ�û�ȡ�̼߳������̵߳�CPUP�ӿ�ʱ��������߳���Ϊ0��
 *
 * ֵ: 0x02000c0c
 *
 * �������: ʹ�û�ȡ�̼߳������̵߳�CPUP�ӿ�ʱ��������߳����������0
 */
#define OS_ERRNO_CPUP_THREAD_INNUM_INVALID      SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x0C)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺��ȡָ������CPUռ����ʱ��������δ��������ɾ����
 *
 * ֵ: 0x02000c0d
 *
 * �������: �豣֤��ȡָ������CPUռ����ʱ���������Ѿ�������δ��ɾ����
 */
#define OS_ERRNO_CPUP_TASK_NO_CREATE            SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x0D)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺����ϵͳ��CPUPʱ������Ĺ���ΪNULL��
 *
 * ֵ: 0x02000c0e
 *
 * �������: ����ϵͳ��CPUPʱ���豣֤����Ĺ���Ϊ��NULL��
 */
#define OS_ERRNO_CPUP_COMPEN_HOOK_NULL          SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x0E)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺����ϵͳ��CPUPʱ������Ĳ���ֵΪ0������ȥ��IDLE���Ӳ���ʱ�������ֵΪ0��
 *
 * ֵ: 0x02000c0f
 *
 * �������: ������ϵͳ��CPUPʱ������Ĳ���ֵ����0����ȥ��IDLE���Ӳ���ʱ�������ֵ���ܵ���0��
 */
#define OS_ERRNO_CPUP_COMPEN_VALUE_ZERO         SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x0F)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺����ϵͳ��CPUPʱ������Ĺ���δע�ᡣ
 *
 * ֵ: 0x02000c10
 *
 * �������: ����ϵͳ��CPUPʱ������Ĺ�����ע�ᡣ
 */
#define OS_ERRNO_CPUP_COMPEN_HOOK_NO_REG        SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x10)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺����ϵͳ��CPUP IDLE����ʱ������Ĳ���ֵ���ڵ��ڲ������ڣ�ȥ��IDLE���Ӳ���ʱ�������ֵ�����Ѿ�����ֵ���ܴ�С��
 *
 * ֵ: 0x02000c11
 *
 * �������: ����ϵͳ��CPUPʱ���豣֤����Ĳ���ֵС�ڲ������ڣ���ȥ��IDLE���Ӳ���ֵʱ�������ȥ��ֵ���ܴ����Ѿ�����ֵ���ܴ�С��
 */
#define OS_ERRNO_CPUP_COMPEN_VALUE_TOO_LARGE    SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x11)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺CPUP�澯�ָ���CPUP�澯��ֵ���ô���
 *
 * ֵ: 0x02000c12
 *
 * �������: CPUP�澯��ֵ�趨Ӧ��С��CPUP�澯�ָ���ֵ��
 */
#define OS_ERRNO_CPUP_RESUME_VALUE_ERROR        SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x12)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺g_ullBaseValue���������ڴ汻�ȡ�
 *
 * ֵ: 0x03000c13
 *
 * �������: ��λg_ullBaseValue������ʱ���ȣ��������ڴ����
 */
#define OS_ERRNO_CPUP_MEM_DAMAGED_ERROR         SRE_ERRNO_OS_FATAL(OS_MID_CPUP,0x13)

/**
 * @ingroup SRE_cpup
 * CPUP�����룺CPUP��������ʧ�ܡ�
 *
 * ֵ: 0x03000c14
 *
 * �������: ���������ֿռ��С��
 */
#define OS_ERRNO_CPUP_NAME_ALLOC_FAILED         SRE_ERRNO_OS_FATAL(OS_MID_CPUP,0x14)

/**
 * @ingroup SRE_cpup
 * CPUռ���ʸ澯��־��
 */
#define CPUP_INFO_TYPE_OVERLOAD                 0x01

/**
 * @ingroup SRE_cpup
 * CPUռ���ʻָ��澯��־��
 */
#define CPUP_INFO_TYPE_RECONVERT                0x02

/**
 *@ingroup SRE_cpup
 *CPUռ����ʹ��ģʽ��ϵͳ��CPUP��
 */
#define  OS_CPUP_MODE_SYS                       0x01

/**
 *@ingroup SRE_cpup
 *CPUռ����ʹ��ģʽ���̼߳�CPUP��
 */
#define  OS_CPUP_MODE_THREAD                    0x02

/**
 * @ingroup  SRE_cpup
 *
 * CPUP�澯��Ϣ��
 */
typedef struct tagCpupWarnInfo
{
    UINT16 usType;            /**< CPUռ���ʸ澯��Ϣ����*/
    UINT16 usReserve;         /**< ����                 */
}CPUP_WARNINFO_S;

/**
*@ingroup SRE_cpup
*@brief CPUP�澯�ص��������Ͷ��塣
*
*@par ����:
*ͨ���ûص����������Ͷ���ص��������ӡ�
*@attention ��
*
*@param  #CPUP_WARNINFO_S*   [IN] ����#CPUP_WARNINFO_S*��CPUP�澯��Ϣ��
*
*@retval �ޡ�
*@par ����:
*<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
*@since RTOSck V100R001C01
*@see �ޡ�
*/
typedef VOID (*CPUP_HOOK_FUNC)(CPUP_WARNINFO_S*);

/**
 * @ingroup SRE_cpup
 * �̼߳�CPUռ���ʽṹ�塣
 */
typedef struct tagCpupThread
{
    UINT32 uwID;            /**< �߳�ID                  */
    UINT16 usUsage;         /**< ռ���ʣ�ȡֵ[0,10000]   */
    UINT16 usResv;          /**< ����                    */
} OS_CPUP_THREAD_S;

/**
* @ingroup  SRE_cpup
* ����cpuռ���ʵ�ע����Ϣ�ṹ�塣
*/
typedef struct tagCpupModInfo
{
    UINT32 uwCpupType;      /**< CPUP����ģʽ            */
    BOOL   bCpupWarnFlag;   /**< CPUP�澯��־            */
    UINT32 uwSampleNum;     /**< ����Ĳ�������          */
    UINT32 uwSampleTime;    /**< �����������λtick      */
    UINT32 uwTickPerSec;    /**< ÿ���tick��            */
    UINT32 uwCyclePerSec;   /**< ÿ���cycle��           */
    UINT32 uwWarn;          /**< CPUռ���ʸ澯��ֵ       */
    UINT32 uwResume;        /**< CPUռ���ʸ澯�ָ���ֵ   */
} CPUP_MOD_INFO_S;


/**
*@ingroup SRE_cpup
*@brief ��ȡ��ǰcpuռ���ʡ�
*
*@par ����:
*ͨ�����ӿڻ�ȡ��ǰcpuռ���ʡ�
*@attention
* <ul>
* <li>�ýӿڱ�����CPUPģ��ü����ش򿪣�����osStart֮����ܵ��ô˽ӿڣ����򷵻�0xffffffff��</li>
* <li>����Ϊ���֮һ��</li>
* <li>Ϊ�˼�СCPUPͳ�ƶ��̵߳��ȵ�����Ӱ�죬OS�����˻���IDLE������ͳ���㷨��ͳ�ƽ������һ�����������ٷ�֮�塣</li>
* </ul>
*
*@param ��
*
*@retval #0xffffffff      ��ȡʧ�ܣ�CPUP�ü�����δ�򿪣���δ��ʼ����������osStart֮ǰ���á�
*@retval #[0,10000]       ���ص�ǰcpuռ���ʡ�
*@par ����:
*<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
*@since RTOSck V100R001C01
*@see SRE_CpupAvg | SRE_CpupThread
*/
extern UINT32 SRE_CpupNow(VOID);

/**
*@ingroup SRE_cpup
*@brief ��ȡָ���˵�ǰ��CPUռ����
*
*@par ����:
*ͨ���û�����ĺ˺�uwCoreId����ȡָ���˵�ǰcpuռ���ʡ�
*@attention
* <ul>
* <li>osStart֮ǰ���ܵ��ô˽ӿڡ�</li>
* <li>����SD6182/SD6157/SD6183ƽ̨��֧��ʵ�����ѯ�����˵ĵ�ǰCPUռ���ʡ�</li>
* <li>��ʹ�øýӿڻ�ȡָ���˵�ǰCPUռ����ʱ�������ʹ���̼߳�CPUPģʽ�����Ҳ�����������Ϊ0���û�ȡ������Ҫ����ָ���˼�����CPUռ����(����#SRE_CpupNow��#SRE_CpupThread)��</li>
* <li>���ô˽ӿ�ʱ�����ָ����δ��CPUռ���ʲü����أ�����δ���У����ߺ˺ŷǷ������ص���0xffffffff��</li>
* </ul>
*
*@param uwCoreId [IN] ����#UINT32��ָ����ID��
*
*@retval #0xffffffff         ָ���˺ŷǷ���ָ����CPUP�ü�����δ�򿪻�δ��ʼ����ָ����δ��������£�����0xffffffff��
*@retval #[0,10000]          ����ָ���˵�ǰcpuռ���ʡ�
*@par ����:
*<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
*@since RTOSck V100R001C01
*@see SRE_CpupAvg | SRE_CpupNow
*/
extern UINT32 SRE_CpuUsageGet(UINT32 uwCoreId);


#if (OS_OPTION_CPUP_SYS == YES)
/**
*@ingroup SRE_cpup
*@brief ��ȡƽ��cpuռ���ʽӿڡ�
*
*@par ����:
*ͨ�����ӿڻ�ȡԤ����������OS_CPUP_SAMPLE_RECORD_NUM��ָ���������ƽ��cpuռ���ʡ�
*@attention
* <ul>
* <li>�ýӿڱ�����CPUPģ��ü����ش򿪣�����osStart֮�����ʹ�á�</li>
* <li>��ϵͳCPUPģʽ����Ϊ�̼߳�������osStart֮ǰ���ã�������0xffffffff�������ϱ������롣</li>
* <li>���ҽ���CPUPģʽ����Ϊϵͳ��ʱ���ýӿ���Ч��</li>
* </ul>
*
*@param ��
*
*@retval #0xffffffff      ��ȡʧ�ܡ�
*@retval #[0,10000]       ����ƽ��cpuռ���ʡ�
*@par ����:
*<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
*@since RTOSck V100R001C01
*@see SRE_CpupNow | SRE_CpupPeak
*/
extern UINT32 SRE_CpupAvg(VOID);

/**
*@ingroup SRE_cpup
*@brief ��ȡcpuռ���ʷ�ֵ��
*
*@par ����:
*ͨ�����ӿڻ�ȡcpuռ���ʷ�ֵ��
*@attention
* <ul>
* <li>�ڼ����һ��ϵͳCPUռ����֮ǰ�����ýӿڻ�ȡ����CPUռ���ʷ�ֵΪ0��</li>
* </ul>
*
*@param ��
*
*@retval #[0,10000]          ����ϵͳ��CPUռ���ʷ�ֵ��
*@par ����:
*<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
*@since RTOSck V100R001C01
*@see SRE_CpupAvg | SRE_CpupNow | SRE_CpupPeakClear
*/
extern UINT32  SRE_CpupPeak(VOID);

/**
*@ingroup SRE_cpup
*@brief ���cpuռ���ʷ�ֵ��
*
*@par ����:
*ͨ�����ӿڽ�cpuռ���ʷ�ֵ���㡣
*@attention ��
*
*@param ��
*
*@retval ��
*@par ����:
*<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
*@since RTOSck V100R001C01
*@see SRE_CpupPeak
*/
extern VOID  SRE_CpupPeakClear(VOID);

/**
 *@ingroup SRE_cpup
 *@brief ����IDLE����ִ��ʱ�䡣
 *
 *@par ����:
 *�����û������ָ��IDLE���Ӳ���ʱ�䣬��ָ����IDLE����ִ��ʱ����в�����
 *@attention
 *<ul>
 * <li>�ýӿڱ�����CPUPģ��ü����ش򿪣��������ʼ��֮�����ʹ�á�</li>
 * <li>���ҽ���CPUPģʽ����Ϊϵͳ��ʱ���ýӿ���Ч��</li>
 * <li>����ָ����IDLE����ִ��ʱ����в�������ù���ִ��ʱ�䲻�����ڸ����ڡ�</li>
 * <li>�Ե���IDLE���ӽ��ж�β������Լ�����IDLE���ӵĲ���ֵ������ۼ�,����ֵ�ܴ�С�ĺϷ������û���֤��</li>
 * <li>�û��ڶ�IDLE���ӽ��в���ʱ�����뱣֤����ֵ��׼ȷ��(��Ҫ����IDLE����ִ��ʱCache�Ƿ����е�����)������ᵼ��ϵͳCPUռ����ͳ�Ʋ�׼ȷ��</li>
 * <li>��IDLE����ʱ�䲹��ֵ���󣬿������CPUռ���ʼ����쳣������10000�����0�����������������ϵͳ�Լ���ֵ���ݴ�����CPUռ���ʳ���10000���򽫼���ֵ����Ϊ10000����CPUռ���ʵ���0���򽫼���ֵ����Ϊ0��</li>
 *</ul>
 *
 *@param  pfnHook    [IN] ����#OS_VOID_FUNC�������ILDE���ӡ�
 *@param  uwAddCycle [IN] ����#UINT32�����ָ��IDLE���Ӳ���ֵ��С��
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED             0x02000C0B��CPUP�ü�����δ�򿪣�����δ��ʼ����
 *@retval #OS_ERRNO_CPUP_MODE_NOT_CORRECT       0x02000C06��CPUPģʽ����Ϊ�̼߳���
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED         0x02000C05����osStart֮ǰ���á�
 *@retval #OS_ERRNO_CPUP_COMPEN_HOOK_NULL       0x02000C0E�������IDLE����ΪNULL��
 *@retval #OS_ERRNO_CPUP_COMPEN_VALUE_ZERO      0x02000C0F������Ĳ���ֵ��СΪ0��
 *@retval #OS_ERRNO_CPUP_COMPEN_HOOK_NO_REG     0x02000C10������ĵ�IDLE����δע�ᡣ
 *@retval #OS_ERRNO_CPUP_COMPEN_VALUE_TOO_LARGE 0x02000C11������Ĳ���ֵ��С̫�󣬳����˲������ڡ�
 *@retval #SRE_OK                               0x00000000�������ɹ���
 *@par ����:
 *<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_CpupNow
 */
extern UINT32 SRE_CpupIdleHookLoadAdd(OS_VOID_FUNC pfnHook, UINT32 uwAddCycle);

/**
 *@ingroup SRE_cpup
 *@brief ȥ��IDLE���Ӳ���ʱ�䡣
 *
 *@par ����:
 *�����û������ָ��IDLE���Ӳ���ʱ�䣬��IDLE���Ӳ���ʱ�����ȥ����
 *@attention
 *<ul>
 * <li>�ýӿڱ�����CPUPģ��ü����ش򿪣�����osStart֮�����ʹ�á�</li>
 * <li>���ҽ���CPUPģʽ����Ϊϵͳ��ʱ���ýӿ���Ч��</li>
 * <li>����ָ����IDLE����ִ��ʱ����в�������ù���ִ��ʱ�䲻�����ڸ����ڡ�</li>
 * <li>ȥ��ILDE���ӵĲ���ʱ���С�Ϸ������û���֤��</li>
 *</ul>
 *
 *@param  pfnHook    [IN] ����#OS_VOID_FUNC������ж��̵߳�CPUP��Ϣָ�롣
 *@param  uwSubCycle [IN] ����#UINT32�����ָ��IDLE���Ӳ���ֵ��С��
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED             0x02000C0B��CPUP�ü�����δ�򿪣�����δ��ʼ����
 *@retval #OS_ERRNO_CPUP_MODE_NOT_CORRECT       0x02000C06��CPUPģʽ����Ϊ�̼߳���
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED         0x02000C05����osStart֮ǰ���á�
 *@retval #OS_ERRNO_CPUP_COMPEN_HOOK_NULL       0x02000C0E�������IDLE����ΪNULL��
 *@retval #OS_ERRNO_CPUP_COMPEN_VALUE_ZERO      0x02000C0F�������ȥ������ֵ��СΪ0��
 *@retval #OS_ERRNO_CPUP_COMPEN_HOOK_NO_REG     0x02000C10������ĵ�IDLE����δע�ᡣ
 *@retval #OS_ERRNO_CPUP_COMPEN_VALUE_TOO_LARGE 0x02000C11�������ȥ������ֵ��С̫�󣬳�����IDLE�����Ѳ���ֵ�ܴ�С��
 *@retval #SRE_OK                               0x00000000��ȥ�������ɹ���
 *@par ����:
 *<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_CpupNow
 */
extern UINT32 SRE_CpupIdleHookLoadSub(OS_VOID_FUNC pfnHook, UINT32 uwSubCycle);
#endif

#if (OS_OPTION_CPUP_THREAD == YES)
/**
 *@ingroup SRE_cpup
 *@brief ��ȡָ���������̵߳�CPUռ���ʡ�
 *
 *@par ����:
 *�����û�������̸߳�������ȡָ���������߳�CPUռ���ʡ�
 *@attention
 *<ul>
 * <li>���ҽ���CPUPģʽ����Ϊ�̼߳�ʱ���ýӿ���Ч��</li>
 * <li>���������еĲ�������ֵ����0ʱ���̼߳�CPUP��������Ϊ���ε��øýӿڻ���SRE_CpupNow֮��
   �ļ���������̼߳�CPUP��������Ϊ�������е�OS_CPUP_SAMPLE_INTERVAL��С��</li>
 * <li>�����ʵ���̸߳���������ϵͳ��ʵ�ʵ��̸߳���(���������һ���ж��߳�)��</li>
 * <li>��������̸߳���Ϊ1���������ж��߳�(�������߳�������߳�ͳ��)��CPUP��Ϣ��</li>
 * <li>����һ������������������ɾ������ͳ�Ƶ������̺߳��ж��߳�CPUP�ܺ�С��10000��</li>
 *</ul>
 *
 *@param  uwInNum   [IN]  ����#UINT32��������̸߳�����
 *@param  pstCpup   [OUT] ����#OS_CPUP_THREAD_S *�������������������������д��������̵߳�CPUP��Ϣ��
 *@param  puwOutNum [OUT] ����#UINT32 *�����������ʵ���̸߳���ָ�롣
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED           0x02000C0B��CPUP�ü�����δ�򿪣�����δ��ʼ����
 *@retval #OS_ERRNO_CPUP_MODE_NOT_CORRECT     0x02000C06��CPUPģʽ����Ϊ�̼߳���
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED       0x02000C05����osStart֮ǰ���á�
 *@retval #OS_ERRNO_CPUP_PTR_NULL             0x02000C02������ָ��ΪNULL��
 *@retval #OS_ERRNO_CPUP_THREAD_INNUM_INVALID 0x02000C0C��������̸߳���Ϊ0��
 *@retval #SRE_OK                             0x00000000����ȡ�ɹ���
 *@par ����:
 *<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_CpupNow
 */
extern UINT32 SRE_CpupThread(UINT32 uwInNum, OS_CPUP_THREAD_S *pstCpup, UINT32 *puwOutNum);

/**
 *@ingroup SRE_cpup
 *@brief ��ȡָ�������CPUռ���ʡ�
 *
 *@par ����:
 *�����û����������ID����ȡָ�������CPUռ���ʡ�
 *@attention
 *<ul>
 * <li>���ҽ���CPUPģʽ����Ϊ�̼߳�ʱ���ýӿ���Ч��</li>
 * <li>��������������Ϊ0���ô˽ӿ�ʱ����ȡ�����ǣ���һ�������ڽ��������ô˽ӿ�ʱ����ָ�������CPUռ���ʡ�</li>
 * <li>�������������ò�Ϊ0ʱ����ȡ�����ǣ���һ����������ָ�������CPUռ���ʡ�</li>
 *</ul>
 *
 *@param  uwTaskId    [IN]  ����#UINT32�����������ID��
 *@param  puwTaskRate [OUT] ����#UINT32 *�����ָ�������̵߳�CPUP��Ϣָ�롣
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED           0x02000C0B��CPUP�ü�����δ�򿪣�����δ��ʼ����
 *@retval #OS_ERRNO_CPUP_MODE_NOT_CORRECT     0x02000C06��CPUPģʽ���ò�Ϊ�̼߳���
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED       0x02000C05����osStart֮ǰ���á�
 *@retval #OS_ERRNO_CPUP_PTR_NULL             0x02000C02������ָ��ΪNULL��
 *@retval #OS_ERRNO_CPUP_TASKID_INVALID       0x02000C09�����������ID�Ƿ���
 *@retval #OS_ERRNO_CPUP_TASK_NO_CREATE       0x02000C0D�����������δ���������ѱ�ɾ����
 *@retval #SRE_OK                             0x00000000����ȡ�ɹ���
 *@par ����:
 *<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R001C00
 *@see SRE_CpupThread
 */
extern UINT32 SRE_CpupTaskGetById(UINT32 uwTaskId, UINT32 *puwTaskRate);

/**
 *@ingroup SRE_cpup
 *@brief ��ȡ�ж��̵߳�CPUռ���ʡ�
 *
 *@par ����:
 *��ȡ�ж��̵߳�CPUռ���ʡ�
 *@attention
 *<ul>
 * <li>���ҽ���CPUPģʽ����Ϊ�̼߳�ʱ���ýӿ���Ч��</li>
 * <li>��������������Ϊ0���ô˽ӿ�ʱ����ȡ�����ǣ���һ�������ڽ��������ô˽ӿ�ʱ�����ж��̵߳�CPUռ���ʡ�</li>
 * <li>�������������ò�Ϊ0ʱ����ȡ�����ǣ���һ�����������ж��̵߳�CPUռ���ʡ�</li>
 *</ul>
 *
 *@param  puwIntRate [OUT] ����#UINT32 *������ж��̵߳�CPUP��Ϣָ�롣
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED           0x02000C0B��CPUP�ü�����δ�򿪣�����δ��ʼ����
 *@retval #OS_ERRNO_CPUP_MODE_NOT_CORRECT     0x02000C06��CPUPģʽ���ò�Ϊ�̼߳���
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED       0x02000C05����osStart֮ǰ���á�
 *@retval #OS_ERRNO_CPUP_PTR_NULL             0x02000C02������ָ��ΪNULL��
 *@retval #SRE_OK                             0x00000000����ȡ�ɹ���
 *@par ����:
 *<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_CpupTaskGetById
 */
extern UINT32 SRE_CpupIntGet(UINT32 *puwIntRate);
#endif

#if (OS_OPTION_CPUP_WARN == YES)
/**
 *@ingroup SRE_cpup
 *@brief ����CPUռ���ʸ澯��ֵ��
 *
 *@par ����:
 *�����û����õ�CPUռ���ʸ澯��ֵuwWarn�͸澯�ָ���ֵuwResume�����ø澯�ͻָ���ֵ��
 *@attention
 *<ul>
 * <li>osStart֮ǰ���ܵ��ô˽ӿڡ�</li>
 *</ul>
 *
 *@param  uwWarn   [IN] ����#UINT32��CPUP�澯��ֵ��
 *@param  uwResume [IN] ����#UINT32��CPUP�ָ���ֵ��
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED            0x02000C0B��CPUP�ü�����δ�򿪣�����δ��ʼ����
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED        0x02000C05����osStart֮ǰ���á�
 *@retval #OS_ERRNO_CPUP_INTERVAL_NOT_SUITED   0x02000C01����ֵ�趨���ڹ涨��Χ(0,10000]�ڡ�
 *@retval #OS_ERRNO_CPUP_RESUME_NOT_SUITED     0x02000C03, �ָ���ֵ�趨��С�ڸ澯��ֵ��
 *@retval #SRE_OK                              0x00000000����ֵ�趨�趨�ɹ���
 *@par ����:
 *<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R001C01
 *@see SRE_CpupWarnValueGet
 */
extern UINT32 SRE_CpupWarnValueSet(UINT32  uwWarn, UINT32 uwResume);

/**
 *@ingroup SRE_cpup
 *@brief ��ѯCPUP�澯��ֵ�͸澯�ָ���ֵ
 *
 *@par ����:
 *�����û����õĸ澯��ֵָ��puwWarn�͸澯�ָ���ֵָ��puwResume����ѯ�澯��ֵ�͸澯�ָ���ֵ
 *@attention
 *<ul>
 * <li>osStart֮ǰ���ܵ��ô˽ӿڡ�</li>
 *</ul>
 *
 *@param  puwWarn   [OUT] ����#UINT32 *��CPUP�澯��ֵ��
 *@param  puwResume [OUT] ����#UINT32 *��CPUP�ָ���ֵ��
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED           0x02000C0B��CPUP�ü�����δ�򿪣�����δ��ʼ����
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED       0x02000C05����osStart֮ǰ���á�
 *@retval #OS_ERRNO_CPUP_PTR_NULL             0x02000C02������ָ��ΪNULL��
 *@retval #SRE_OK                             0x00000000����ȡ�ɹ���
 *@par ����:
 *<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R001C01
 *@see SRE_CpupWarnValueSet
 */
extern UINT32 SRE_CpupWarnValueGet(UINT32 * puwWarn, UINT32 * puwResume);


/**
 * @ingroup SRE_cpup
 * @brief ע��CPUP�澯�ص�����
 *
 * @par ����:
 * �����û����õĻص�����pfnHook��ע��CPUP�澯�ص�����
 * @attention
 *<ul>
 * <li>�������ظ��򸲸�ע�ṳ�ӡ�</li>
 * <li>pfnHookΪNULLʱ����ʾɾ���ù��ӡ�</li>
 *</ul>
 *
 * @param  pfnHook  [IN] ����#CPUP_HOOK_FUNC��CPU�澯�ص�������
 *
 *@retval #OS_ERRNO_HOOK_FULL              0x02001604���ظ�ע��CPU�澯���ӡ�
 *@retval #SRE_OK                          0x00000000��ע��ɹ���
 *@par ����:
 *<ul><li>sre_cpup.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R001C01
 *@see �ޡ�
 */
extern UINT32 SRE_CpupWarnHookReg(CPUP_HOOK_FUNC pfnHook);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_CPUP_H */

