

/*----includes-----------------------------------------------------------------------*/

#include <stdarg.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include <linux/uaccess.h>
#include <linux/ioport.h>
#include <linux/highmem.h>

#include <linux/version.h>
#include <net/addrconf.h>

#include <asm/page.h>        /* for PAGE_SIZE */
#include <asm/div64.h>
#include <asm/sections.h>    /* for dereference_function_descriptor() */

#include "../include/srecorder_snprintf.h"


/*----local macroes------------------------------------------------------------------*/


/*----local prototypes----------------------------------------------------------------*/


/*----local variables------------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/


/*----function definitions--------------------------------------------------------------*/

/**
    @function: int srecorder_snprintf(char *buf, size_t size, const char *fmt, ...)
    @brief: ��ָ����ʽ����ַ�����ָ�������С�

    @param: buf ����
    @param: size ����ռ��С
    @param: fmt �ַ�����ʽ

    @return: д�뻺����ֽ���

    @note: 
*/
int srecorder_snprintf(char *buf, size_t size, const char *fmt, ...)
{
    va_list args;
    int i = 0;

    va_start(args, fmt);
    i = vscnprintf(buf, size, fmt, args);
    va_end(args);

    return i;
}


/**
    @function: int srecorder_init_snprintf(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ����ʽ�����ģ��

    @param: pinit_params ģ���ʼ������

    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_snprintf(srecorder_module_init_params_t *pinit_params)
{
    return 0;
}


/**
    @function: void srecorder_exit_snprintf(void)
    @brief: �˳���ʽ�����ģ��

    @param: none

    @return: none

    @note: 
*/
void srecorder_exit_snprintf(void)
{
}

