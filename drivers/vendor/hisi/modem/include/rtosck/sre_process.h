/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3Dah1fIWJ0QzaviBugQMTxyfdBxnyOas2YfpGASpq0YvtHfmHX7l8QwPfHpzP7j4EeXHMT
USc3qHiOuJ4gPVgZD1CGUi+Lkp5wZHTl1P4cpX3nmPzE0A11ZIZrF2sLrogADQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
 * @file sre_process.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ����������ģ��Ķ���ͷ�ļ��� \n
 */

 /**@defgroup SRE_process ���̻�������
  *@ingroup SRE_kernel
 */

#ifndef _SRE_PROCESS_H
#define _SRE_PROCESS_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_OPTION_KERNEL_PROCESS == YES) 

/**
 * @ingroup SRE_procss
 * ����PID��
 *
 * ����PID�Ƿ� 
 */
#define OS_PROCESS_NULL_ID                                      0xFFFFFFFF


/**
 * @ingroup SRE_process
 * ����������ȼ�
 *
 * 
 */
#define OS_PROCESS_PRIORITY_LOWEST                              0x0000


/*
 * ����ģ��Ĵ����붨�塣
 */
/**
 * @ingroup SRE_process
 * ���̴����룺�����ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02003000
 *
 * �������: ��������˽��FSC�ڴ����
 *
 */
#define OS_ERRNO_PROCESS_NO_MEMORY                          SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x00)

/**
 * @ingroup SRE_process
 * ���̴����룺���̴�����ɾ��ʱ���ָ�����Ϊ�ջ��ֵַΪ�ա�
 *
 * ֵ: 0x02003001
 *
 * �������: ������ָ����ַ�Ƿ�ΪNULL��
 */
#define OS_ERRNO_PROCESS_PTR_NULL                           SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x01)

/**
 * @ingroup SRE_process
 * ���̴����룺�û�����ջ��Сδ��16�ֽڴ�С���롣
 *
 * ֵ: 0x02003002
 *
 * �������: �������û�����ջ��С�Ƿ�16�ֽڶ��롣
 */
#define OS_ERRNO_PROCESS_STKSZ_NOT_ALIGN                    SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x02)

/**
 * @ingroup SRE_process
 * ���̴����룺�û����õĽ����û�ջ�׵�ַδ16�ֽڶ��롣
 *
 * ֵ: 0x02003003
 *
 * �������: ���ý��������û�ջ�׵�ַ��16�ֽڶ��롣
 */
#define OS_ERRNO_PROCESS_STACKADDR_NOT_ALIGN                SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x03)


/**
 * @ingroup SRE_process
 * ���̴����룺��������ָ��Ϊ�ջ������Ϊ���ַ�����
 *
 * ֵ: 0x02003004
 *
 * �������: ��������ָ��ͽ�������
 */
#define OS_ERRNO_PROCESS_NAME_EMPTY                         SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x04)


/**
 * @ingroup SRE_process
 * ���̴����룺���õĽ�������̫�࣬���15�����������ں˽����Ҳ���Ϊ0��
 *
 * ֵ: 0x02003005
 *
 * �������: �����������н�����û���������ΪС�ڵ���15���Ҵ���0��
 */
#define OS_ERRNO_PROCESS_MAX_NUM_NOT_SUITED                 SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x05)

/**
 * @ingroup SRE_process
 * ���̴����룺���������������õ�ҳ���ַ�򳤶ȷǷ�
 *
 * ֵ: 0x02003006
 *
 * �������: ��ȷ����������ҳ���ַ����Ϊ0������ҳ���Ȳ���Ϊ0��
 */
#define OS_ERRNO_PROCESS_PAGE_TBL_CFG_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x06)

/**
 * @ingroup SRE_process
 * ���̴����룺���ý���ҳ�����ַδ��0x4000�ֽ�(16K)��С���롣
 *
 * ֵ: 0x02003007
 *
 * �������: �����������ҳ�����ַ�Ƿ�0x4000�ֽڴ�С���롣
 */
#define OS_ERRNO_PROCESS_PAGE_TBL_ADDR_NOT_ALIGN            SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x07)

/**
 * @ingroup SRE_process
 * ���̴����룺�������еĽ���ҳ���Сδ��0x400�ֽ�(1K)��С���롣
 *
 * ֵ: 0x02003008
 *
 * �������: ������������ҳ���С���ٰ�0x400�ֽ�(1K)��С���롣
 */
#define OS_ERRNO_PROCESS_PAGE_TBL_ADDR_SIZE_NOT_ALIGN       SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x08)

/**
 * @ingroup SRE_process
 * ���̴����룺�������еĽ���ҳ���С���ù�С��
 *
 * ֵ: 0x02003009
 *
 * �������: ������������ҳ���СOS_PROCESS_PAGE_TABLE_SIZE��С��(1K + OS_PROCESS_MAX_SUPPORT_NUM * 16K)��
 */
#define OS_ERRNO_PROCESS_PAGE_TBL_SIZE_TOO_SMALL            SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x09)

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̴���ʱ�û�����ELF�ļ�ͷ����
 *
 * ֵ: 0x0200300a
 *
 *�������:����û����̵�ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_PROCESS_ELF_HEAD_ERROR                     SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x0a)

/**
 * @ingroup SRE_process
 * ���̴�����: �û�����LP�ļ����ʹ���
 *
 * ֵ: 0x0200300b
 *
 *�������:���SD6183ƽ̨�Ƿ�ʹ����HIDSP������������û����̿�ִ���ļ���
 */
#define OS_ERRNO_PROCESS_ELF_FILETYPE_ERROR                 SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x0b)

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̼���ʱELF�α�ͷ����
 *
 * ֵ: 0x0200300c
 *
 *�������:�����ص��û�����ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_PROCESS_ELF_SEC_HEAD_ERROR                 SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x0c)

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̼���ʱELF�ļ�����ϢУ�����
 *
 * ֵ: 0x0200300d
 *
 *�������:�����ص��û�����ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_PROCESS_ELF_SEC_NUM_ERROR                  SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x0d)

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̼���ʱELF�ļ������������󡣡�
 *
 * ֵ: 0x0200300e
 *
 *�������:ELF�Ķθ�������Ϊ0����ȷ���û����̵Ŀ�ִ���ļ��Ƿ���ȷ�ԡ�
 */
#define OS_ERRNO_PROCESS_SEC_NUM_ADDR_ERROR                 SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x0e)

/**
 * @ingroup SRE_process
 * ���̴�����: �û������ļ���ELF�ζ������
 *
 * ֵ: 0x0200300f
 *
 *�������:�鿴�û�����ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_PROCESS_SEC_ALIGN_ERROR                    SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x0f)

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̿�ִ���ļ������Դ���
 *
 * ֵ: 0x02003010
 *
 *�������:����û�����ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_PROCESS_SECTION_FLAG_ERROR                 SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x10)

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̴���ʱ���õĶ�������Ϊ�ա�
 *
 * ֵ: 0x02003011
 *
 *�������:�û����̴���ʱ���õĶ������ֲ���Ϊ�ա�
 */
#define OS_ERRNO_PROCESS_CFG_SEC_NAME_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x11)

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̼���ʱ����ҳ���ڴ治����
 *
 * ֵ: 0x02003012
 *
 * �������: ���ڽ���������������ҳ��ռ��С��
 */
#define OS_ERRNO_PROCESS_MMU_SIZE_ERROR                     SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x12)

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̴���ʱ���õĽ��̶θ���Ϊ0���߽��̶�����ַΪ�ա�
 *
 * ֵ: 0x02003013
 *
 *�������:�û����̴���ʱ���õĶ���������Ϊ0�����̶�����ַ����Ϊ�ա�
 */
#define OS_ERRNO_PROCESS_SECAREAINFO_IS_NULL                SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x13)

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̴���ʱ���õĽ��̶���������ͬ��
 *
 * ֵ: 0x02003014
 *
 *�������:�޸���ͬ�Ķ���Ϊ��ͬ������
 */
#define OS_ERRNO_PROCESS_SEC_NAME_SAME                      SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x14)

/**
 * @ingroup SRE_process
 *  ���̴����룺�û����̴���ʱ���õĽ��̶��д��������ַ�ص���
 *
 * ֵ: 0x02003015
 *
 * �������: ȷ�����������������ַ���ص���
 */
#define OS_ERRNO_PROCESS_SEC_AREA_OVERLAY_IN_VIR_ADDR       SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x15)

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̴�������ʱ����Ļ�������ַ(uwExeAddr)��4�ֽڶ��롣
 *
 * ֵ: 0x02003016
 *
 *�������:��֤��λ�������ַ(uwExeAddr)4�ֽڶ��롣
 */
#define OS_ERRNO_PROCESS_BUF_ADDR_NOT_ALIGN                 SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x16) 

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̴���ʱ���������Ȳ��������߻���������Ϊ0����������Ƿ���ȷ��
 *
 * ֵ: 0x02003017
 *
 *�������:�鿴����Ļ��������ȡ�
 */
#define OS_ERRNO_PROCESS_BUF_NOT_ENOUGH                     SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x17) 

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̴���ʱ���õĽ����û�ջ��СΪ0��
 *
 * ֵ: 0x02003018
 *
 *�������:�鿴�����û�ջ���ô�С�Ƿ�Ϊ0��
 */
#define OS_ERRNO_PROCESS_STKSZ_IS_ZERO                      SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x18) 

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̴���ʱ���õĽ����û�ջ��ַΪ�ա�
 *
 * ֵ: 0x02003019
 *
 *�������:�鿴�����û�ջ���õ�ַ�Ƿ�ΪNULL��
 */
#define OS_ERRNO_PROCESS_STACKADDR_IS_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x19) 

/**
 * @ingroup SRE_process
 * ���̴�����: �û����̴���ʱ�Ҳ��ܿ��еĽ���ע����Ϣ�顣
 *
 * ֵ: 0x0200301a
 *
 *�������:��鵱ǰ�������û��������Ƿ��Ѿ������û����õ���������(OS_PROCESS_MAX_SUPPORT_NUM)��
 */
#define OS_ERRNO_PROCESS_REG_NOT_FIND_IDLE_BLOCK            SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x1a) 

/**
 * @ingroup SRE_process
 * ��������룺����ID�Ƿ���
 *
 * ֵ: 0x0200301b
 *
 * �������: ��鵱ǰ���н��̵�PID�Ƿ񳬹����õĽ�������������û���ν���PID�Ƿ�Ϸ���
 */
#define OS_ERRNO_PROCESS_ID_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x1b)

/**
 * @ingroup SRE_process
 * ��������룺����û�д�����
 *
 * ֵ: 0x0200301c
 *
 * �������: ��鵱ǰPIDָ���Ľ����Ƿ��Ѿ�����������
 */
#define OS_ERRNO_PROCESS_NOT_CREATED                        SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x1c)


/**
 * @ingroup SRE_process
 * ����ID�����Ͷ��塣
 */
typedef UINT32                                              PROCESS_HANDLE_T;

/**
 * @ingroup SRE_process
 * �������ȼ������Ͷ��塣
 */
typedef UINT16                                              PROCESS_PRIOR_T;


/**
 * @ingroup SRE_process
 * ����ģ��������Ϣ�Ľṹ�嶨�塣
 *
 * �������ģ�����������Ϣ��
 */
typedef struct tagProcessModInfo
{
    UINT32 uwMaxNum;                       /**< ���֧�ֵĽ�����           */
    UINT32 uwPTblAddr;                     /**< �û�����ҳ�����û���ַ(16k����)*/    
    UINT32 uwPTblsize;                     /**< �û�����ҳ�����ô�С(16k����)*/  
} PROCESS_MOD_INFO_S;

/**
 * @ingroup SRE_process
 * ����ģ��������Ϣ�����öεĽṹ�嶨�塣
 *
 * ���̴���ʱ��
 */
typedef struct tagProcessSection
{
    CHAR * pcSecName;                      /**< �û����̵Ķ���         */
    UINT32 uwSecVA;                        /**< �û����̵Ķ������ַ   */
    UINT32 uwSecPA;                        /**< �û����̵Ķ������ַ   */
    UINT32 uwSecSize;                      /**< �û����̵Ķδ�С       */
    UINT32 uwSecAttr;                      /**< �û����̵Ķ�����       */
}PROCESS_SECTION_S; 

/**
 * @ingroup SRE_process
 * ���̴��������Ľṹ�嶨�塣
 *
 * ���ݽ��̴���ʱָ���Ĳ�����Ϣ��
 */
typedef struct tagProcessParam
{
    CHAR * pcProcessName;                   /**< ������                     */
    PROCESS_PRIOR_T usProcessPrio;          /**< �������ȼ�                 */
    UINT16 usPreserved;                     /**< Ԥ��                       */
    UINT32 uwInitCnt;                       /**< ����ʱ��Ƭ��ʼ����ֵ(Tickֵ��������)*/
    UINT32 uwUsrStackAddr;                  /**< �����û�ջ��ַ             */
    UINT32 uwUsrStackSize;                  /**< �����û�ջ��С             */
    UINT32 uwVMID;                          /**< �û����̵�VMID             */
    UINT32 uwSecNum;                        /**< �û����̶�������           */
    PROCESS_SECTION_S *pstProcessSection;   /**< �û����̶�����ַ�ռ�       */
} PROCESS_PARA_S;

/**
 * @ingroup  SRE_process
 * @brief �������̡�
 *
 * @par ����:
 * ����һ�����̡�
 * ϵͳ��ʼ���󴴽��Ľ��̣�������ȼ����ڵ�ǰ������δ�����̣��������������̵��Ȳ������У��������������С�
 *
 * @attention
 * <ul>
 * <li>��������ʱ��Ϣ������Ĭ��Ϊ1��������Ҫ���á�</li>
 * <li>����������󳤶�Ϊ16�ֽڣ�����������</li>
 * <li>ͬһ���ڽ������������ظ����Ҳ���������ж�������</li>
 * <li>����ջ�Ĵ�С���밴16�ֽڴ�С���롣ȷ������ջ��С��ԭ���ǣ����þ��У������˷ѣ����˽���ջ������������ȡ������Ҫ���Ķ��ٵ�ջ�ڴ棬������������������ò��Խ�ջ�ڴ濪��Խ�󣬾ֲ�����Խ�󣬾ֲ�����Խ�࣬ջ�ڴ濪��ҲԽ��</li>
 * <li>�û����õĽ���ջ�ռ������û���֤��Ϸ��ԣ����Կ�cache�ռ�ĵ�ַ�û���Ҫ��֤�����ջ�׵�ַ��ջ��Сcache line���룬ϵͳ�������봦������ʹ�ú������û������ͷš�</li>
 * </ul>
 *
 * @param  puwProcessPID [OUT] ����#UINT32 *���������PID��
 * @param  pstInitParam [IN] ����#PROCESS_PARA_S *�����̴�����������ṹ���еĳ�Ա����uwStackAddr����ʱ������г�ʼ�������������û����õĶ�������ջ����ջ�ռ���䣬�ó�Ա�����ʼ��Ϊ0��
 *
 * @retval #OS_ERRNO_PROCESS_NO_MEMORY              0x02002f00�������ڴ�ʧ�ܡ�
 * @retval #OS_ERRNO_PROCESS_PTR_NULL               0x02002f01��ָ�����Ϊ�ա�
 * @retval #OS_ERRNO_PROCESS_STKSZ_NOT_ALIGN        0x02002f02������ջ��Сδ��16�ֽڴ�С���롣
 * @retval #OS_ERRNO_PROCESS_NAME_EMPTY             0x02002f04����������ָ��Ϊ�ջ������Ϊ���ַ�����
 * @retval #OS_ERRNO_PROCESS_ID_INVALID             0x02002f1b������PID�Ƿ���
 * @retval #OS_ERRNO_PROCESS_STACKADDR_NOT_ALIGN    0x02002f03����������ʱ���û����ý���ջ��ַδ16�ֽڶ��롣
 * @retval #SRE_OK                                  0x00000000�����̴����ɹ���
 * @par ����:
 * <ul><li>sre_process.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ProcessDelete | SRE_ProcessCreateOnly
 */
extern UINT32 SRE_ProcessCreate(PROCESS_HANDLE_T *puwProcessPID, UINT32 uwExeAddr, UINT32 uwSize, PROCESS_PARA_S *pstProcessPara);


/**
 * @ingroup  SRE_process
 * @brief �������̣�����������̡�
 *
 * @par ����:
 * ����һ�����̡��ý��̲�����������У�ֻ���ڹ���״̬���û���Ҫ����ý�����Ҫͨ������SRE_ProcessResume�������伤�
 *
 * @attention
 * <ul>
 * <li>����������󳤶�Ϊ16�ֽڣ�����������</li>
 * <li>��������ʱ��Ϣ������Ĭ��Ϊ1��������Ҫ���á�</li>
 * <li>ͬһ���ڽ������������ظ���</li>
 * <li>����ջ�Ĵ�С���밴16�ֽڴ�С���롣ȷ������ջ��С��ԭ���ǣ����þ��У������˷ѣ����˽���ջ������������ȡ������Ҫ���Ķ��ٵ�ջ�ڴ棬������������������ò��Խ�ջ�ڴ濪��Խ�󣬾ֲ�����Խ�󣬾ֲ�����Խ�࣬ջ�ڴ濪��ҲԽ��</li>
 * <li>�û����õĽ���ջ�׵�ַ��16�ֽڶ��룬�����õĽ���ջ�ռ��У�os��ʹ����Ϣ������*��Ϣ���п��ƿ���ڴ��С��</li>
 * <li>�û����õĽ���ջ�ռ������û���֤��Ϸ��ԣ����Կ�cache�ռ�ĵ�ַ�û���Ҫ��֤�����ջ�׵�ַ��ջ��Сcache line���룬ϵͳ�������봦������ʹ�ú������û������ͷš�</li>
 * </ul>
 *
 * @param  puwProcessPID [OUT] ����#UINT32 *���������PID��
 * @param  pstInitParam [IN] ����#PROCESS_PARA_S *�����̴�����������ṹ���еĳ�Ա����uwStackAddr����ʱ������г�ʼ�������������û����õĶ�������ջ����ջ�ռ���䣬�ó�Ա�����ʼ��Ϊ0��
 *
 * @retval #OS_ERRNO_PROCESS_NO_MEMORY              0x02002f00�������ڴ�ʧ�ܡ�
 * @retval #OS_ERRNO_PROCESS_PTR_NULL               0x02002f01��ָ�����Ϊ�ա�
 * @retval #OS_ERRNO_PROCESS_STKSZ_NOT_ALIGN        0x02002f02������ջ��Сδ��16�ֽڴ�С���롣
 * @retval #OS_ERRNO_PROCESS_NAME_EMPTY             0x02002f04����������ָ��Ϊ�ջ������Ϊ���ַ�����
 * @retval #OS_ERRNO_PROCESS_ID_INVALID             0x02002f1b������PID�Ƿ���
 * @retval #OS_ERRNO_PROCESS_STACKADDR_NOT_ALIGN    0x02002f03����������ʱ���û����ý���ջ��ַδ16�ֽڶ���.
 * @retval #SRE_OK                                  0x00000000�����̴����ɹ���
 * @par ����:
 * <ul><li>sre_process.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ProcessDelete | SRE_ProcessCreate
 */
extern UINT32 SRE_ProcessCreateOnly(PROCESS_HANDLE_T *puwProcessPID, UINT32 uwExeAddr, UINT32 uwSize, PROCESS_PARA_S *pstProcessPara);


/**
 * @ingroup  SRE_process
 * @brief �ָ����̡�
 *
 * @par ����:
 * �ָ�����Ľ��̡�
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>�������Դ�����ʱ������̬����ֻ��ȡ������̬����������������С�</li>
 * </ul>
 *
 * @param  uwProcessPID [IN] ����#UINT32������PID��
 *
 * @retval #OS_ERRNO_PROCESS_ID_INVALID         0x02002f1b������PID�Ƿ���
 * @retval #OS_ERRNO_PROCESS_NOT_CREATED        0x02002f1c������û�б�������
 * @retval #SRE_OK                              0x00000000���ָ����̳ɹ���
 * @par ����:
 * <ul><li>sre_process.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ProcessSuspend
 */
extern UINT32 SRE_ProcessResume(PROCESS_HANDLE_T uwProcessPID);


/**
 * @ingroup  SRE_process
 * @brief ������̡�
 *
 * @par ����:
 * ����ָ���Ľ��̣����̽��Ӿ��������б�ɾ����
 *
 * @attention
 * <ul>
 * <li>��Ϊ��ǰ�������������̣����ܱ�����</li>
 * </ul>
 *
 * @param  uwProcessPID [IN] ����#UINT32������PID��
 *
 * @retval #OS_ERRNO_PROCESS_ID_INVALID             0x02002f1b������PID�Ƿ���
 * @retval #OS_ERRNO_PROCESS_NOT_CREATED            0x02002f1c������û�б�������
 * @retval #SRE_OK                                  0x00000000��������̳ɹ���
 * @par ����:
 * <ul><li>sre_process.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since  RTOSck V100R003C00
 * @see SRE_ProcessResume | SRE_ProcessLock
 */
extern UINT32 SRE_ProcessSuspend(PROCESS_HANDLE_T uwProcessPID);


/**
 * @ingroup  SRE_task
 * @brief ɾ�����̡�
 *
 * @par ����:
 * ɾ��ָ���Ľ��̣��ͷŽ���ջ�ͽ��̿��ƿ���Դ��
 *
 * @attention
 * <ul>
 * <li> </li>
 * </ul>
 *
 * @param  uwProcessPID [IN] ����#UINT32������PID��
 *
 * @retval #OS_ERRNO_PROCESS_ID_INVALID             0x02002f1b������PID�Ƿ���
 * @retval #OS_ERRNO_PROCESS_NOT_CREATED            0x02002f1c������û�б�������
 * @retval #SRE_OK                                  0x00000000��ɾ�����̳ɹ���
 * @par ����:
 * <ul><li>sre_process.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ProcessCreate
 */
//extern UINT32 SRE_ProcessDelete(PROCESS_HANDLE_T uwProcessPID, PROCESS_PARA_S *pstProcessPara);
extern UINT32 SRE_ProcessDelete(PROCESS_HANDLE_T uwProcessPID);

/**
 * @ingroup  SRE_process
 * @brief �����̵��ȡ�
 *
 * @par ����:
 * �����̵��ȡ������̵��ȱ������򲻷��������л���
 *
 * @attention
 * <ul>
 * <li>ֻ�������̵��ȣ��������жϣ���˽����Կɱ��жϴ�ϡ�</li>
 * <li>ִ�д˺�����������ֵ��1��������������ֵ��1����ˣ�������#SRE_processUnlock���ʹ�á�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_process.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ProcessUnlock
 */
extern VOID SRE_ProcessLock(VOID);


/**
 * @ingroup  SRE_process
 * @brief �������̵��ȡ�
 *
 * @par ����:
 * ����������ֵ��1����Ƕ�׼�������ֻ��������ֵ��Ϊ0�������Ľ����˽��̵��ȡ�
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>ִ�д˺�����������ֵ��1��������������ֵ��1����ˣ�������#SRE_processLock���ʹ�á�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_process.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_processLock
 */
extern VOID SRE_ProcessUnlock(VOID);

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_PROCESS_H */


