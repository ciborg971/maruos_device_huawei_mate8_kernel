

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEmmPlmnPublic.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPLMNPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPLMNPUBLIC_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/


VOS_VOID    NAS_EMM_ClearLocalResource( VOS_VOID )
{
    /*EMM&MMC ȫ�ֱ������ */
    NAS_LMM_EmmAndMmcGlobInfoClear();

    /*��ʼ��EMMȫ�ֱ���*/
    NAS_LMM_EmmInfoInit();

    /* �������ģ��*/
    NAS_LMM_EmmSubModGlobClear();

    /*NAS_LMM_SoftUsimInit();*//*����������*/
    return;
}










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

