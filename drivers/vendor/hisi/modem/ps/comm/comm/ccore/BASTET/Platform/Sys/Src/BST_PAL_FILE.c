
#include <stdio.h>
#include "BST_OS_Memory.h"
#include "BST_Platform.h"

#define    THIS_FILE_ID        PS_FILE_ID_BST_PAL_FILE_C

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#if (VOS_RTOSCK == VOS_OS_VER)
size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream)
{
  return 0;
}

int fputs(const char *str, FILE *fp)
{
  return 0;
}

int fputc (int n, FILE *fp)
{
  return 0;
}
/*lint -e48 -e18 -e438 -e516*/
 void *realloc(void *mem_address, unsigned int newsize)
{

  void   * NewPtr;   
  if   ( !mem_address)    
  {     
    return   BST_OS_MALLOC(   newsize   );   
  }    
  else   if   (   newsize   ==   0   )      
  {     
    BST_OS_FREE(   mem_address   );    
  }    
  else   
  {     
    NewPtr   =   BST_OS_MALLOC(newsize);     
    if   (   NewPtr   )       
    {      
      BST_OS_MEMCPY(   NewPtr,   mem_address,   newsize   );     
      BST_OS_FREE(   mem_address   );                  
      return   NewPtr;     
    }    
  }    
  return   BST_NULL_PTR;  
}
/*lint +e48 +e18 +e438 -e516*/

#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

