/*--------------------------------------------------------------------------------------------------------------------------
*���ļ���Ҫ��ʵ��L2CACHE��ɸƬ����
*˵������:��MODEM�������ڵ�1M�ռ����ݰᵽ���Կռ�ĵͶˣ��Ƚ�ԭʼ����͵Ͷ�
*         �ٽ��Ͷ����ݰ��Ƶ��߶ˣ��ȽϸߵͶ˲���
*         �����Կռ�Ͷ�����Ϊֵ0x5A5A5A5A,���Ͷ����ݰ��Ƶ��߶ˣ��ȽϸߵͶ˲���
*         ������Ľ����Ȼ��OK�ģ�A9������ѭ����д��־��
*--------------------------------------------------------------------------------------------------------------------------*/
/**
* @file l2cache_screening.c
*
*
* ������L2CACHEɸƬ���ܡ�
*/
#include <string.h>
#include "l2cache_screening.h"

/* Ϊ�˱�֤flush&incЧ������Ҫ��flush L1,��flush&inv L2,���flush&inv L1*/

void l2cache_screening_case(void)
{
    unsigned int test_count = 0;

    for(test_count = 1; test_count < 6; test_count++)
    {
        memset_s((void*)(L2CACHE_TEST_START_ADDR + MINI_PAGE_SIZE * test_count),(size_t)MINI_PAGE_SIZE,
                       0xa5a5a5a5,(size_t)MINI_PAGE_SIZE);
        memcpy_s((void*)(L2CACHE_TEST_END_ADDR - test_count * MINI_PAGE_SIZE),(size_t)MINI_PAGE_SIZE,
               (void*)(L2CACHE_TEST_START_ADDR + MINI_PAGE_SIZE * test_count),
                        (size_t)MINI_PAGE_SIZE);
        if (memcmp((void*)(L2CACHE_TEST_END_ADDR - test_count * MINI_PAGE_SIZE),
                    (void*)(L2CACHE_TEST_START_ADDR + MINI_PAGE_SIZE * test_count),
                            MINI_PAGE_SIZE))
        {
            while (1)
            {
                ARMA9CTX_REGISTER_WRITE(L2CACHE_TEST_FLAG_ADDR,test_count);
                CACHE_FLUSH_AND_INV_ALL;
            }
        }
    }
    for(test_count = 6; test_count < 11; test_count++)
    {
        memset_s((void*)(L2CACHE_TEST_START_ADDR + MINI_PAGE_SIZE * test_count),(size_t)MINI_PAGE_SIZE,
                       0x5a5a5a5a,(size_t)MINI_PAGE_SIZE);
        memcpy_s((void*)(L2CACHE_TEST_END_ADDR - test_count * MINI_PAGE_SIZE),(size_t)MINI_PAGE_SIZE,
               (void*)(L2CACHE_TEST_START_ADDR + MINI_PAGE_SIZE * test_count),
                        (size_t)MINI_PAGE_SIZE);
        if (memcmp((void*)(L2CACHE_TEST_END_ADDR - test_count * MINI_PAGE_SIZE),
                    (void*)(L2CACHE_TEST_START_ADDR + MINI_PAGE_SIZE * test_count),
                            MINI_PAGE_SIZE))
        {
            while (1)
            {
                ARMA9CTX_REGISTER_WRITE(L2CACHE_TEST_FLAG_ADDR,test_count);
                CACHE_FLUSH_AND_INV_ALL;
            }
        }
    }
    while (1)
    {
        ARMA9CTX_REGISTER_WRITE(L2CACHE_TEST_FLAG_ADDR,0xA5A5A5A5);
        CACHE_FLUSH_AND_INV_ALL;
    }
}

