/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3DaoJKLOkHnsHop7n+e+dpNEZbcEUANAhREkDhyi9k9JiD8innzTXtzoD3G9IhJgTHUk7k
ETG2NI2nqdzZcPC3BMtcGARKklVHocpE39IMocylCJhLsvboEP3ws+F39pdOlQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
 * @file sre_k_copy.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������Ӳ�����ģ��Ķ���ͷ�ļ��� \n
 */

 /**@defgroup SRE_K_copy �ں˿���
   *@ingroup SRE_kernel
 */

#ifndef _SRE_K_COPY_H
#define _SRE_K_COPY_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_OPTION_KERNEL_PROCESS == YES)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP��Ԫ�ŷǷ���Ϊ0ֵ���߳������������á�
 *
 * ֵ: 0x02003601
 *
 *�������:����LP��Ԫ�źϷ���
 */
#define OS_ERRNO_KCOPY_LEN_ERROR                          SRE_ERRNO_OS_ERROR(OS_MID_K_COPY, 0x01)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP��Ԫ�ŷǷ���Ϊ0ֵ���߳������������á�
 *
 * ֵ: 0x02003602
 *
 *�������:����LP��Ԫ�źϷ���
 */
#define OS_ERRNO_KCOPY_PFROM_ERROR                          SRE_ERRNO_OS_ERROR(OS_MID_K_COPY, 0x02)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP��Ԫ�ŷǷ���Ϊ0ֵ���߳������������á�
 *
 * ֵ: 0x02003603
 *
 *�������:����LP��Ԫ�źϷ���
 */
#define OS_ERRNO_KCOPY_PTO_ERROR                          SRE_ERRNO_OS_ERROR(OS_MID_K_COPY, 0x03)

/*****************************************************************************
 Description : �û��ռ�-->�ں˿ռ�
 Input       : 
                pFrom:Դ��ַ���û��ռ䣩

 Output      : 
                pTo:Ŀ���ַ���ں˿ռ䣩
                
 Return      : �ɹ�����0��ʧ�ܷ��ش�����
 *****************************************************************************/
extern UINT32 SRE_copy_from_usr(void *pTo, const void *pFrom, UINT32 uwLen);



/*****************************************************************************
Description : �ں˿ռ�-->�û��ռ�
Input       : 
                pFrom:Դ��ַ���ں˿ռ䣩

Output      : 
                pTo:Ŀ���ַ���û��ռ䣩
            
Return      : �ɹ�����0��ʧ�ܷ��ش�����
*****************************************************************************/
extern UINT32 SRE_copy_to_usr(void *pTo, const void *pFrom, UINT32 uwLen);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HW_H */


