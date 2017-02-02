/**
 * @file sre_shell.h
 *
 * Copyright(C), 2011-2011, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������Shellģ�����ͷ�ļ��� \n
 */

#ifndef __SRE_SHELL_H__
#define __SRE_SHELL_H__

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**@defgroup sre_shell Shell����
  *@ingroup SRE_inspect
  */

/**
 *@ingroup sre_shell
 * Cortex-AXƽ̨���ڴ�ӡ�����������
 */
#define OS_SHELL_END_SIGN        0

 /**
 * @ingroup sre_shell
 * HShell�����룺��������ע��ʱ�ڴ����ʧ�ܡ�
 *
 * ֵ: 0x02002d04
 *
 * �������: ���ԭ������ע��ʱ�ڴ����ռ��Ƿ��ѱ��ͷ��Լ����ڷ����ռ��Ƿ��Ѿ����ꡣ
 *
 */
#define OS_ERRNO_SHELL_CMDREG_MEMALLOC_ERROR                                    SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x04)

/**
 * @ingroup sre_shell
 * HShell�����룺����TRANSIDʱ�����Ϊ�ա�
 *
 * ֵ: 0x02002d05
 *
 * �������: �������TRANSID ���������Ϣ�ĺϷ��ԡ�
 *
 */
#define OS_ERRNO_SHELL_TRANSID_PARA_NULL                                        SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x05)

/**
 * @ingroup sre_shell
 * HShell�����룺����TRANSIDʱ���ڴ�����ʧ��
 *
 * ֵ: 0x02002d06
 *
 * �������:  �������TRANSID ʱ��ԭ��������ڴ��Ƿ��ͷ��Լ������ڴ�����ռ��Ƿ����ꡣ
 *
 */
#define OS_ERRNO_SHELL_TRANSID_MEMALLOC_ERROR                                   SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x06)

/**
 * @ingroup sre_shell
 * HShell�����룺Server��Channel���ص���Ϣ�ַ�ʱ��Ϣָ��Ϊ�ա�
 *
 * ֵ: 0x02002d09
 *
 * �������:  ����������Ϣ�ַ�ʱ�����Ϣָ��ĺϷ��ԡ�
 *
 */
#define OS_ERRNO_SHELL_RES_MSG_NULL                                             SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x09)

/**
 * @ingroup sre_shell
 * HShell�����룺Channel��Server֮�䷢�͵���Ϣ���Ͳ��Ϸ���
 *
 * ֵ: 0x02002d0a
 *
 * �������: ����������Ϣ�ַ�ʱChannel��Server֮�䷢�͵���Ϣ���͵ĺϷ��ԡ�
 *
 */
#define OS_ERRNO_SHELL_RES_TYPE_ERROR                                           SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x0a)

/**
 * @ingroup sre_shell
 * HShell�����룺SVRģ�� �������Ϣ��������ȡ��Ϣ���Ͳ��Ϸ���
 *
 * ֵ: 0x02002d0b
 *
 * �������:  ���SVRģ�� �������Ϣ��������ȡ��Ϣ���͵ĺϷ��ԡ�
 *
 */
#define OS_ERRNO_SHELL_SVR_MSGTYPE_ERROR                                        SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x0b)

/**
 * @ingroup sre_shell
 * HShell�����룺SVRģ��svr ��ͨ������������ʱ�����ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02002d0c
 *
 * �������: ���SVRģ��svr ��ͨ������������ʱԭ���ڴ��Ƿ��ѱ��ͷ��Լ������ڴ�����ռ��Ƿ����ꡣ
 *
 */
#define OS_ERRNO_SHELL_SVR_MEMALLOC_ERROR                                       SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x0c)

/**
 * @ingroup sre_shell
 * HShell�����룺SVRģ��svr ����Ϣ����ʱ������Ϣ������Ϣ�ڴ�ռ�ʧ�ܡ�
 *
 * ֵ: 0x02002d0d
 *
 * �������:  ���SVRģ��svr ����Ϣ����ʱ������Ϣԭ�ȷ�����Ϣ�ڴ�ռ��Ƿ��ѱ��Լ������ڴ�����ռ��Ƿ����ꡣ
 *
 */
#define OS_ERRNO_SHELL_SVR_MSGALLOC_ERROR                                       SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x0d)

/**
 * @ingroup sre_shell
 * HShell�����룺SVRģ��Agent ��Server���صĽ�����Ϣ�ṹָ��Ϊ��,�����˴���������Ϣʱ����Ϣָ��Ϊ�ա�
 *
 * ֵ: 0x02002d0e
 *
 * �������:   ���SVRģ��Agent��Server���صĽ�����Ϣ�ṹָ���Ƿ��Ѿ�����ʼ������
 *
 */
#define OS_ERRNO_SHELL_SVR_POINT_NULL                                           SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x0e)

/**
 * @ingroup sre_shell
 * HShell�����룺SVRģ��������Ϣ�ַ�����ʱ�����Ϣָ��Ϊ�ա�
 *
 * ֵ: 0x02002d0f
 *
 * �������: ���SVRģ��������Ϣ�ַ�����ʱ�����Ϣָ���Ƿ��Ѿ���ʼ����
 *
 */
#define OS_ERRNO_SHELL_SVR_MSGDISPATCH_POINT_NULL                               SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x0f)

/**
 * @ingroup sre_shell
 * HShell�����룺SVRģ��������Ϣ���������Ϣ����ָ��Ϊ�ա�
 * ֵ: 0x02002d10
 *
 * �������:  ���SVRģ��������Ϣ����ʱ�����Ϣ����ָ���Ƿ��Ѿ���ʼ����
 *
 */
#define OS_ERRNO_SHELL_SVR_MSGSUB_MSG_NULL                                      SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x10)

/**
 * @ingroup sre_shell
 * HShell�����룺����TransId��Ϣʱ�������id��Ҫ�Ĳ�����Ϣ�ṹ��ָ��Ϊ�ա�
 *
 * ֵ: 0x02002d11
 *
 * �������:  ������TransId��Ϣʱ�������id��Ҫ�Ĳ�����Ϣ�ṹ��ָ���Ƿ�Ϊ�ա�
 *
 */
#define OS_ERRNO_SHELL_TRAN_POINT_NULL                                          SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x11)

/**
 * @ingroup sre_shell
 * HShell�����룺����TransId��Ϣʱû�з���õ���Ч��TransId ������Ϣ��
 *
 * ֵ: 0x02002d12
 *
 * �������:  ������TransId��Ϣʱ��ЧTransId �Ƿ���ڡ�
 *
 */
#define OS_ERRNO_SHELL_TRANID_FAIL                                              SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x12)

/**
 * @ingroup sre_shell
 * HShell�����룺CHANNEL ģ�����ط��͵���Ϣ�ϱ���ǰ��ʱ������Ϣ�ռ���Ӧ�е��ռ����󲻺Ϸ���
 *
 * ֵ: 0x02002d17
 *
 * �������: ���CHANNEL ģ�����ط��͵���Ϣ�ϱ���ǰ��ʱ������Ϣ�ռ���Ӧ�е��ռ���������ĺϷ��ԡ�
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_COLLECT_OBJ_ERROR                                SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x17)

/**
 * @ingroup sre_shell
 * HShell�����룺CHANNEL ģ��������������ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02002d18
 *
 * �������:  ���CHANNEL ģ���������ԭ��������ڴ��Ƿ��ѱ��ͷ��Լ����ڷ����Ƿ��ѱ����ꡣ
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_MEMALLOC_ERROR                                   SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x18)

/**
 * @ingroup sre_shell
 * HShell�����룺CHANNEL ģ����յ����������ݵ�ָ��Ϊ�ա�
 *
 * ֵ: 0x02002d19
 *
 * �������:  ���CHANNEL ģ����յ����������ݵ�ָ���Ƿ��Ѿ�����ʼ����
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_POINT_NULL                                       SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x19)

/**
 * @ingroup sre_shell
 * HShell�����룺CHANNEL ģ��ACSCOMM����Ĺ�����Ϣ�ռ�����������Ϣ֡�ڴ����ʧ�ܡ�
 *
 * ֵ: 0x02002d1a
 *
 * �������:   CHANNEL ģ��ACSCOMM����Ĺ�����Ϣ�ռ�����������Ϣ֡ԭ���ڴ�����Ƿ��ѱ��ͷ��Լ���ʹ�÷����ռ��Ƿ��ѱ����ꡣ
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_MSGALLOC_ERROR                                   SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x1a)

/**
 * @ingroup sre_shell
 * HShell�����룺CHANNEL ģ�����dbg_acscomm�ṩ�ķ��ͽӿڰѴ���Ϣ�� dbg_server ʱ�����������
 *
 * ֵ: 0x02002d1b
 *
 * �������: ���CHANNEL ģ�����dbg_acscomm�ṩ�ķ��ͽӿڰѴ���Ϣ�� dbg_server ʱ��������ĺϷ��ԡ�
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_CMDTYPE_ERROR                                    SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x1b)

/**
 * @ingroup sre_shell
 * HShell�����룺AGENT ģ��������Ϣ�ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02002d1c
 *
 * �������:  ���AGENT ģ��ԭ��������Ϣ�ڴ�ռ��Ƿ�û�б��ͷ��Լ���ʹ�õķ����ڴ�ռ��Ƿ��ѱ����ꡣ
 *
 */
#define OS_ERRNO_SHELL_AGENT_MSGALLOC_ERROR                                     SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x1c)

/**
 * @ingroup sre_shell
 * HShell�����룺��ʾģ��SRE_Show����SRE_Printf��������ݹ�����
 *
 * ֵ: 0x02002d1d
 *
 * �������:  ��ʾģ����Ҫ����SRE_Show����SRE_Printf�������ݵĳ���Ŀǰ�Ϊ512�ֽڡ�
 *
 */
#define OS_ERRNO_SHELL_SHOW_TOO_LONG                                            SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x1d)

/**
 * @ingroup sre_shell
 * HShell�����룺SHOWģ��SRE_Show����SRE_Printf������������ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02002d1e
 *
 * �������:  ���SHOWģ��SRE_Show����SRE_Printf�������ԭ�ȷ�����ڴ��Ƿ��ѱ��ͷ��Լ���ʹ�÷����Ƿ��ѱ����ꡣ
 *
 */
#define OS_ERRNO_SHELL_SHOW_ALLOC_ERROR                                         SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x1e)

/**
 * @ingroup sre_shell
 * HShell�����룺SHOWģ��SRE_Show���Ӻ���Ϊ�ա�
 *
 * ֵ: 0x02002d1f
 *
 * �������: ���SHOWģ��SRE_Show���Ӻ����Ƿ��ѱ�ע�ᡣ
 *
 */
#define OS_ERRNO_SHELL_SHOW_HOOK_NULL                                           SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x1f)

/**
 * @ingroup sre_shell
 * HShell�����룺SHOWģ��SRE_Show����Ĺ��Ӻ����Ѿ����ڡ�
 *
 * ֵ: 0x02002d20
 *
 * �������: ����Ҫ����ע����ͬ�Ĺ��Ӻ�����ȥ��ע����ͬ�Ĺ��Ӻ�����
 *
 */
#define OS_ERRNO_SHELL_SHOW_HOOK_EXIST                                          SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x20)

/**
 * @ingroup sre_shell
 * HShell�����룺SHOWģ��SRE_Show����Ĺ��Ӻ���ע����࣬һ�� ���SHOW����Ϊ2����
 *
 * ֵ: 0x02002d21
 *
 * �������:  ȥ�������SRE_Show����Ĺ��Ӻ�����
 *
 */
#define OS_ERRNO_SHELL_SHOW_HOOK_TOO_MUCH                                       SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x21)

/**
 * @ingroup sre_shell
 * HShell�����룺CHANNEL ģ��ͨ���������ݵĻ�������С��
 *
 * ֵ: 0x02002d24
 *
 * �������:  CHANNEL ģ��ͨ���������ݵĻ���������������С��ͨ�����͵ı��Ĵ�С��
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_BUFFER_OVERFLOW                                  SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x24)

/**
 * @ingroup sre_shell
 * HShell�����룺CHANNEL ģ��ͨ���������ʽ����
 *
 * ֵ: 0x02002d25
 *
 * �������:CHANNEL ģ�� �鿴Host�˷��͵ı����Ƿ����Э�顣
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_FORMAT_ERROR                                     SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x25)

/**
 * @ingroup sre_shell
 * HShell�����룺CHANNEL ģ�� ͨ�������У�����
 *
 * ֵ: 0x02002d26
 *
 * �������:  ���ͨ����������ı������ݵ���ȷ�ԡ�
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_CHECK_ERROR                                      SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x26)

/**
 * @ingroup sre_shell
 * HShell�����룺CHANNEL ģ��ͨ�������û��û����Ϣ��ͷ����û��@���š�
 *
 * ֵ: 0x02002d27
 *
 * �������: �鿴Host����Ϣ�����Ƿ���ȷ���鿴ͨ���Ƿ���Ϣ�ضϳ����뷢������ȥ����Ϣͷ��
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_NO_MSG_HEAD                                      SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x27)

/**
 * @ingroup sre_shell
 * HShell������:Target shell�ڴ����ʱ��ָ���޸Ļ��ѯ���ڴ��Ȳ��Ϸ���
 *
 * ֵ: 0x02002d30
 *
 * �������: �Ų�Target shell�ڴ��޸Ĳ���ʱ��ָ�����Ϊ1,2��4�ֽڣ��ڴ��ѯʱ����Ȳ��ܳ���256�ֽڡ�
 *
 */
#define OS_ERRNO_SHELL_MEMWR_WIDTH_INVALID                                      SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x30)

/**
 * @ingroup sre_shell
 * HShell������:  �ڴ����ʱ����ʱ�ڴ�����ʧ�ܡ�
 *
 * ֵ: 0x02002d36
 *
 * �������: �Ų���������ڴ�й¶��
 *
 */
#define OS_ERRNO_SHELL_MEMWR_ALLOC                                              SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x36)

/**
 * @ingroup sre_shell
 * HShell������: �ڴ����ʱ��Ŀ�ĵ�ַ��Ч��
 *
 * ֵ: 0x02002d37
 *
 * �������: �Ų�Ŀ�ĵ�ַ�Ƿ���Ч��
 *
 */
#define OS_ERRNO_SHELL_MEMWR_ADDR_INVAIL                                        SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x37)

/**
 * @ingroup sre_shell
 * HShell������: Target shell��ѯ�ڴ����ʱ��������ڴ浥Ԫ�����Ƿ����߱����ԡ�
 *
 * ֵ: 0x02002d38
 *
 * �������: ʹ�ò�ѯ�ڴ��������ʱ�����������ڴ浥Ԫ���������Ѿ������ڴ浥Ԫ���������Ų�������ڴ浥Ԫ������С�Ƿ��ںϷ���Χ[1, 512]�ڡ�
 *
 */
#define OS_ERRNO_SHELL_MEMWR_UNITS_NUM_INVALID                                  SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x38)

/**
 * @ingroup sre_shell
 * HShell������: Target shell��ѯ�����޸��ڴ����ʱ��������ڴ��ַδ����Ҫ����롣
 *
 * ֵ: 0x02002d39
 *
 * �������: �Ų�������ڴ��ַ�Ƿ���Ҫ����룬����������ݿ��Ϊ2����4ʱ��Ҫ������ĵ�ַ��Ϊ2�ֽڻ���4�ֽڶ��롣
 *
 */
#define OS_ERRNO_SHELL_MEMWR_ADDR_NOT_ALIGNED                                   SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x39)

/**
 * @ingroup sre_shell
 * HShell�����룺����SRE_Printfʱ����ĸ�ʽ���ַ���ָ��ΪNULL��
 *
 * ֵ: 0x02002d3a
 *
 * �������: ����SRE_Printfʱ��֤����ĸ�ʽ���ַ���ָ��Ϊ��NULL��
 *
 */
#define OS_ERRNO_SHELL_PTR_NULL                                                 SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x3a)

/**
 * @ingroup sre_shell
 * ��ʾshell�ն��������͡�
 *
 */
#define DBG_TERMINAL_TOOL               1   /**< �ն�ΪTOOL   */
#define DBG_TERMINAL_VRPCLI             2   /**< �ն�ΪVRPCLI */
#define DBG_TERMINAL_MML                3   /**< �ն�ΪMML    */
#define DBG_TERMINAL_UART               4   /**< �ն�ΪUART   */
#define DBG_TERMINAL_SRIO               5   /**< �ն�ΪSRIO   */
#define DBG_TERMINAL_GE                 6   /**< �ն�ΪGE     */


/**
 * @ingroup sre_shell
 * Target shell֧�ֵ�showģ��������š�
 *
 */
typedef enum tagShellShowModCmdNo
{
    OS_SHELL_SHOW_CPUP_CMD_NO = 0,          /**< ��ǰϵͳshowcpup�������*/
    OS_SHELL_SHOW_SEM_CMD_NO,               /**< ��ǰϵͳshowsem�������*/
    OS_SHELL_SHOW_QUEUE_CMD_NO,             /**< ��ǰϵͳshowqueue�������*/
    OS_SHELL_SHOW_MSG_CMD_NO,               /**< ��ǰϵͳshowmsg�������*/
    OS_SHELL_SHOW_EVENT_CMD_NO,             /**< ��ǰϵͳshowevent�������*/
    OS_SHELL_SHOW_TIMER_CMD_NO,             /**< ��ǰϵͳshowetimer�������*/
    OS_SHELL_SHOW_HWI_CMD_NO,               /**< ��ǰϵͳshowhwi�������*/
    OS_SHELL_SHOW_ERROR_CMD_NO,             /**< ��ǰϵͳshowerror�������*/
    OS_SHELL_SHOW_MEMPT_CMD_NO,             /**< ��ǰϵͳshowmempt�������*/
    OS_SHELL_SHOW_CMD_NO_BUTT
} SHELL_SHOW_CMD_NO_E;

/**
 *@defgroup  sre_shell sre_showģ��ӿ�
 *@ingroup sre_shell
 */

/**< ���Show���� */
#define SHOW_MAX_LEN 321

/**
 *@ingroup sre_shell
 *����ض����ʶ
 */
typedef UINT32 TRANSID_T;

/**
 *@ingroup sre_shell
 *SHOW������Ӻ������͡�
 */
typedef UINT32 (*SHOW_HOOK_FUNC)
(
    TRANSID_T   TransId,    /**<�ض����ʶ��*/
    UINT8       ucType,     /**<����       .*/
    UINT32      uwLength,   /**<�����Ϣ���ȣ�������'/0'��*/
    CHAR*       pscOutPut   /**<��ʽ����Ϣ��*/
);

/**
 *@ingroup sre_shell
 *�ȵ㺯��ʹ��tick��timer�ĺ����������͡�
 */
typedef UINT32 (* SHELL_SAM_RP_FUNC)(UINT32* puwPeriod, UINT8 *pucLevel, UINT32 uwDo);

/**
* @ingroup  sre_shell
*
* �����ȵ㺯����������Ϣ��
*/
typedef struct tagShellSamModInfo
{
    UINT32 uwAddr;                  /**<Ĭ��PC�洢����ʼ��ַ, ��4�ֽڶ��� */
    UINT32 uwLen;                   /**<Ĭ��PC�洢������, ��8�ֽڶ���     */
    SHELL_SAM_RP_FUNC pfnRpTick;    /**<����tick�жϵĹ���                */
    SHELL_SAM_RP_FUNC pfnUseTimer;  /**<����timer�Ĺ���                   */
}SHELL_SAM_MOD_INFO_S;

/**
* @ingroup  sre_shell
*
* ����HSHELLģ���������Ϣ��
*/
typedef struct tagHshellModInfo
{
    UINT8 ucServerCoreID;           /**<����Server �˺�                           */
    UINT8 ucSvrPrority;             /**<����Server �����ȼ�                       */
    UINT8 ucAgtPrority;             /**<����Agent  �����ȼ�                       */
    UINT32 uwThreadType;            /**<Shell�߳����ͣ���Ϊ��������ж�           */
    UINT32 uwSvrStackSize;          /**<����Server ��ջ��С                       */
    UINT32 uwAgtStackSize;          /**<����Agent  ��ջ��С                       */
} HSHELL_MOD_INFO_S;

/**
 *@ingroup sre_shell
 *�����Զϵ㹳��ע�ắ����
 *ÿ���������ע��һ��������
 */
typedef VOID (*HSHELL_TRACE_COLLECT_FUNC)(VOID);

/**
 *@ingroup sre_shell
 *Shell agent����Ϣ�����Ӻ�������
 */
typedef UINT32 (*HSHELL_AGENT_MSG_PROC_HOOK_FUNC)(UINT32 uwSendId, VOID *pMsg);


/**
 *@ingroup sre_shell
 *ע����Զ�����ԽӿڵĹ��Ӷ��壬�ù����ṩͳһ�Ĺ������ͣ�ͨ���ù����Ǹ���ģ��ĵ��Խӿڡ�
 */
typedef UINT32 (*CMD_CBK_FUNC)();

/**
* @ingroup  sre_shell
* @brief ��ʽ����Ϣ���������
*
* @par ����:
* ��ʽ����Ϣ���������
*
*
*@param TransId [IN]#TRANSID_T�� �ض����ʶ��
*@param pscFormat [IN]#CHAR *��  �ַ�����Ҫ����ĸ�ʽ����Ϣ���ݡ�
*
* @retval  #OS_ERRNO_SHELL_SHOW_ALLOC_ERROR        0x02002d1e��SHOWģ��������������ڴ�ʧ�ܡ�
* @retval  #OS_ERRNO_SHELL_SHOW_TOO_LONG           0x02002d1d����ʾģ�鴦������ݹ�����
* @retval  #SRE_OK                                 0x00000000���ɹ���
* @par ����:
* <ul><li>sre_shell.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R002C00
* @see ��
*/
extern UINT32 SRE_Show(TRANSID_T TransId, CHAR * pscFormat, ...);

/**
* @ingroup  sre_shell
* @brief ����ͨ�������ַ�������
*
* @par ����:
* �������øýӿڣ���shell�����������յ����ַ���Ϣ��
*
* @attention
* <ul>
* <li>Ŀǰֻ��CORTEX_AXƽ̨֧�ִ��ڽ����ַ�������</li>
* </ul>
*
* @param  ucChar  [IN] ����#UINT8�����ڽ��յ��ַ�ֵ��
*
* @retval  #OS_ERRNO_IO_INTF_SENDCHR2CHL_HOOK_NULL    0x02002d32��ע���ͨ������ַ����Ӻ���Ϊ�ա�
* @retval  #SRE_OK                                  0x00000000���ɹ���
* @par ����:
* <ul><li>sre_shell.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R002C00
* @see ��
*/
extern UINT32 SRE_SendChrToShell(UINT8 ucChar);

/**
* @ingroup  sre_shell
* @brief ��׼�����ӡ��
*
* @par ����:
* ע��ͨ��������Ӻ󣬵��øú�����ʵ�������ӡ��
*
* @attention
* <ul>
* <li>Ŀǰֻ��CORTEX_AXƽ̨֧�ֱ�׼�����ӡ������</li>
* <li>֧��c��d��i��x��s��f��%�������͸�ʽ��ת����</li>
* <li>֧���Ҷ���(��߲�0���߿ո�)�������(�ұ߲��ո�)��</li>
* <li>����Balong��Ʒ���ڳ�ʼ���׶�ϵͳ�����ӡ����ǰ֧����ʱ��ӡ����ϵͳ�����ӡ������(��Ҫ��SRE_HardDrvInit���ȳ�ʼ��UART��������SRE_SendChrToShellע�ᴮ�ڽ����ַ�������)��һ���ӡ������ݡ����֧��4K�ֽڴ�С�Ļ���ռ䡣</li>
* <li>���֧�ִ�ӡ�ַ���ΪSHOW_MAX_LEN(321)��������������</li>
* <li>���ô˺���ʱ����Ҫ�������ĵ�ǰ�߳����ڵ�ջ�ռ���Դ(��ԼΪ343���ֽ�)��</li>
* <li>��ѡ�����ĺϷ������û���֤��������ɴ�ӡ�쳣��</li>
* </ul>
*
* @param  pcFormat  [IN] ����#CHAR *�������ʽ���ַ���ָ�롣
* @param  ...  [IN] ��ѡ������
*
* @retval  #OS_ERROR                               0xFFFFFFFF������ĸ�ʽ���ַ���ָ��ΪNULL�򴮿��������δע�������ʾ�����ݹ���,�ýӿ�֧�ֵ������ʾ����ΪSHOW_MAX_LEN(����������)��
* @retval  #[0,SHOW_MAX_LEN)                       �Ѿ������ӡ���ַ����������ӡ�ɹ���
* @par ����:
* <ul><li>sre_shell.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R002C00
* @see ��
*/
extern UINT32 SRE_Printf (const CHAR *pcFormat, ...);

#ifdef __cplusplus
#if __cplusplus

}
#endif
#endif

#endif    /*__SRE_SHOW_H__*/

