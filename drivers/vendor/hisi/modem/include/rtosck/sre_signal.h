/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3Dah1fIWJ0QzaviBugQMTxyfdBxnyOas2YfpGASpq0YvtHfmHX7l8QwPfHpzP7j4EeXHMT
USc3qHiOuJ4gPVgZD1CGUi+Lkp5wZHTl1P4cpX3nmPzE0A11ZIZrF2sLrogADQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
 * @file sre_signal.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ����������ģ��Ķ���ͷ�ļ��� \n
 */

 /**@defgroup SRE_siganl �����������
  *@ingroup SRE_kernel
 */

#ifndef _SRE_SIGNAL_H
#define _SRE_SIGNAL_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */




/**
 * @ingroup SRE_task
 * ����������󳤶ȡ�
 *
 * ����������󳤶ȣ�������β��'\0'��
 */
//#define OS_TSK_NAME_LEN                                     16



/**
 * @ingroup SRE_signal
 * ��������룺�ź�δ������
 *
 * ֵ: 0x02001a00
 *
 * �������: ����ź��Ƿ񴴽���
 */
#define OS_ERRNO_SIG_NOT_CREATED                            SRE_ERRNO_OS_ERROR(OS_MID_SIG, 0x00)


#if (OS_OPTION_USR_PROCESS == YES) 
/**
 * @ingroup  SRE_signal
 * @brief �����źš�
 *
 * @par ����:
 * 
 *
 * @attention
 * <ul>
 * <li></li>
 * </ul>
 *
 * @param  puwTaskPID [OUT] ����#UINT32 *����������PID��
 * @param  pstInitParam [IN] ����#TSK_INIT_PARAM_S *�����񴴽���������ṹ���еĳ�Ա����uwStackAddr����ʱ������г�ʼ�������������û����õĶ�������ջ����ջ�ռ���䣬�ó�Ա�����ʼ��Ϊ0��
 *

 * @retval #SRE_OK                              0x00000000�����񴴽��ɹ���
 * @par ����:
 * <ul><li>sre_signal.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskDelete | SRE_TaskCreateHookAdd | SRE_TaskCreateOnly
 */
//extern UINT32 UINT32 SRE_SigCreate(UINT32 uwPid, UINT32 uwSigNo, OS_SIG_ENTRY_HOOK pfnhandler);
#define SRE_SigCreate(uwPid, uwSigNo, pfnhandler) \
        (UINT32)SRE_SYSCALL(SRE_SigCreate, 3, (UINT32)uwPid, (UINT32)uwSigNo, (UINT32)pfnhandler)

//extern UINT32 SREK_SigDelete(UINT32 uwPid, UINT32 uwSigNo)  
#define SRE_SigDelete(uwPid, uwSigNo) \
        (UINT32)SRE_SYSCALL(SRE_SigDelete, 2, (UINT32)uwPid, (UINT32)uwSigNo)

//extern UINT32 SREK_SigUsrReg(UINT32 uwPid, UINT32* pUsrData, UINT32 uwSigSp) 
#define SRE_SigUsrReg(uwPid, pUsrData, uwSigSp) \
        (UINT32)SRE_SYSCALL(SRE_SigUsrReg, 3, (UINT32)uwPid, (UINT32)pUsrData, (UINT32)uwSigSp) 

//extern UINT32 SREK_SigSend(UINT32 uwPid, UINT32 uwSigNo)
#define SRE_SigSend(uwPid, uwSigNo) \
        (UINT32)SRE_SYSCALL(SRE_SigSend, 2, (UINT32)uwPid, (UINT32)uwSigNo) 


#endif



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_SIGNAL_H */


