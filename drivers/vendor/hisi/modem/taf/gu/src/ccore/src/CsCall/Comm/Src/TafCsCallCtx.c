

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafCsCallCtx.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_CS_CALL_CTX_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID TAF_CSCALL_InitCtx(VOS_VOID)
{

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_XCALL_InitCtx();
#endif

}

/*lint -restore*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */






