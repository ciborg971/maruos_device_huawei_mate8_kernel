
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "rand_lcl.h"
#include "e_os.h"
#include "v_lib.h"
#include <openssl/rand.h>
#include "BST_OS_Memory.h"
/******************************************************************************
   2 ����ʵ��
******************************************************************************/

BST_INT32 RAND_poll( BST_VOID )
{
    BST_UINT32      ulRnd;
    BST_UINT32      i;
    ulRnd           = 0;
    BST_UINT8       ucBuf[ENTROPY_NEEDED];
    for ( i = 0; i < BST_OS_SIZEOF(ucBuf); i++ )
    {
        if ( 0 == (i % 4) )
        {
            ulRnd   = VOS_Rand(0xff);/*�˴�����rtosƽ̨����������ɺ���*/
        }
        ucBuf[i]    = ulRnd;
        ulRnd       >>= 8;
    }

    RAND_add( ucBuf, BST_OS_SIZEOF(ucBuf), (double)ENTROPY_NEEDED );
    BST_OS_MEMSET( ucBuf, 0, BST_OS_SIZEOF(ucBuf) );

    return 1;
}

