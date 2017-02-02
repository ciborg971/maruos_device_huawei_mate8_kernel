/**
 * @file SRE_libc.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������C�⺯��ͷ�ļ��� \n
 */

/**@defgroup SRE_libc libc
 *@ingroup SRE_inspect
*/

#ifndef __SRE_LIBC_H__
#define __SRE_LIBC_H__

#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "sre_base.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_OPTION_LIBC == YES)
#ifndef _TOOL_WIN32
/**
 * @ingroup SRE_libc
 * ��������룺����C�⺯��ʱ������Ĳ������Ϸ���
 *
 * ֵ: 0x02003701
 *
 * �������: ����C�⺯��ʱ���豣֤����Ĳ����Ϸ���
 */
#define OS_ERRNO_LIBC_PARA_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LIBC, 0x01)

/**
 * @ingroup SRE_libc
 * ��������룺����vsnprintf����snprintf����ʱ����ʽ������ַ������Ȳ�С�����볤��size��
 *
 * ֵ: 0x02003702
 *
 * �������: ����vsnprintf����snprintf����ʱ���豣֤��ʽ������ַ�������С�����볤��size��
 */
#define OS_ERRNO_LIBC_LEN_TOO_LONG                         SRE_ERRNO_OS_ERROR(OS_MID_LIBC, 0x02)


/**
* @ingroup  SRE_libc
* @brief ���ɱ������ʽ�������һ���ַ����顣
*
* @par ����:
* ��ap����ʽformat�����һ��ָ����������С���ַ�����str�й��ܡ�
*
* @attention
* <ul>
* <li>Ŀǰֻ��CORTEX_AXƽ̨֧�ֱ�׼�����ӡ������</li>
* <li>֧��c��d��i��x��s��f��%�������͸�ʽ��ת����</li>
* <li>֧���Ҷ���(��߲�0���߿ո�)�������(�ұ߲��ո�)��</li>
* <li>����ʽ������ַ������ȴ���(size-1)ʱ������OS_INVALID�����ǻ��(size-1)���ַ������str�С�</li>
* <li>str�ռ��С���û���֤����������ڴ�Խ�硣</li>
* </ul>
*
* @param  str   [OUT] ����#char *�������ɵĸ�ʽ�����ַ�����������
* @param  size  [IN] ����#size_t��str�ɽ��ܵ�����ֽ���,��ֹ��������Խ�硣
* @param  format[IN] ����#const char *�������ʽ���ַ���ָ�롣
* @param  ap    [IN] ����#va_list��va_list������
*
* @retval  #OS_INVALID                             ��β��Ϸ������߸�ʽ������ַ������ȴ���(size-1)��
* @retval  #[0, size)                              �ɹ�����str�е��ַ��������ڵ���0������С��size��
* @par ����:
* <ul><li>sre_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R003C00
* @see vsprintf
*/
extern int vsnprintf(char *str, size_t size, const char *format, va_list ap);

/**
* @ingroup  SRE_libc
* @brief ���ɱ������ʽ�������һ���ַ����顣
*
* @par ����:
* ��ap����ʽformat������ַ�����str�й��ܡ�
*
* @attention
* <ul>
* <li>Ŀǰֻ��CORTEX_AXƽ̨֧�ֱ�׼�����ӡ������</li>
* <li>֧��c��d��i��x��s��%�������͸�ʽ��ת����</li>
* <li>str�ռ��С���û���֤����������ڴ�Խ�硣</li>
* </ul>
*
* @param  str   [OUT] ����#char *�������ɵĸ�ʽ�����ַ�����������
* <li>֧��c��d��i��x��s��f��%�������͸�ʽ��ת����</li>
* <li>֧���Ҷ���(��߲�0���߿ո�)�������(�ұ߲��ո�)��</li>
* @param  ap    [IN] ����#va_list��va_list������
*
* @retval  #OS_INVALID                             ��β��Ϸ���
* @retval  #��ʽ������ַ���                       �ɹ�����str�е��ַ�����
* @par ����:
* <ul><li>sre_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R003C00
* @see vsnprintf
*/
extern int vsprintf(char *str, const char *format, va_list ap);

/**
* @ingroup  SRE_libc
* @brief ���ɱ����������format��ʽ�����ַ�����Ȼ���临�Ƶ�str�С�
*
* @par ����:
* ���ɱ����������format��ʽ�����ַ�����Ȼ���临�Ƶ�ָ����������Сstr�С�
*
* @attention
* <ul>
* <li>Ŀǰֻ��CORTEX_AXƽ̨֧�ֱ�׼�����ӡ������</li>
* <li>֧��c��d��i��x��s��f��%�������͸�ʽ��ת����</li>
* <li>֧���Ҷ���(��߲�0���߿ո�)�������(�ұ߲��ո�)��</li>
* <li>����ʽ������ַ������ȴ���(size-1)ʱ������OS_INVALID�����ǻ��(size-1)���ַ������str�С�</li>
* <li>str�ռ��С�Ϳ�ѡ�����ĺϷ������û���֤����������ڴ�Խ��������쳣��</li>
* </ul>
*
* @param  str   [OUT] ����#char *�������ɵĸ�ʽ�����ַ�����������
* @param  size  [IN] ����#size_t��str�ɽ��ܵ�����ֽ���,��ֹ��������Խ�硣
* @param  format[IN] ����#const char *�������ʽ���ַ���ָ�롣
* @param  ...   [IN] ��ѡ������
*
* @retval  #OS_INVALID                             ��β��Ϸ������߸�ʽ������ַ������ȴ���(size-1)��
* @retval  #[0, size)                              �ɹ�����str�е��ַ��������ڵ���0������С��size��
* @par ����:
* <ul><li>sre_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R003C00
* @see vsnprintf
*/
extern int snprintf(char *str, size_t size, const char *format, ...);

#if (OS_OPTION_IO_INTF == YES)

/**< ���Show���� */
#define SHOW_MAX_LEN 321

/**
* @ingroup  SRE_libc
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
* <li>��֧�����ж��߳��е��ã����û���֤��</li>
* <li>����Balong��Ʒ��֧�ִ�ӡǰ׺(�߳���)������ISP��Ʒ����֧�ִ�ӡǰ׺��</li>
* <li>���֧�ִ�ӡ�ַ���ΪSHOW_MAX_LEN(321)��������������</li>
* <li>���ô˺���ʱ����Ҫ�������ĵ�ǰ�߳����ڵ�ջ�ռ���Դ(��ԼΪ343���ֽ�)��</li>
* <li>��ѡ�����ĺϷ������û���֤��������ɴ�ӡ�쳣��</li>
* </ul>
*
* @param  pcFormat [IN] ����#CHAR *�������ʽ���ַ���ָ�롣
* @param  ...      [IN] ��ѡ������
*
* @retval  #OS_INVALID                             ��β��Ϸ���
* @retval  #[0,SHOW_MAX_LEN)                       �Ѿ������ӡ���ַ����������ӡ�ɹ���
* @par ����:
* <ul><li>sre_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R003C00
* @see SRE_Printf
*/
extern int printf(const CHAR *pcFormat, ...);
#endif
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif //__SRE_LIBC_H__

