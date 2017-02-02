

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "PsTypeDef.h"
#include    "NasLppMtaMsgProc.h"
#include    "LppMtaInterface.h"
#include    "NasLppPublic.h"

#define    THIS_FILE_ID            PS_FILE_ID_NASLPPMTAMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPMTAMSGPROC_C

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
#if (FEATURE_LPP == FEATURE_ON)


/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_VOID NAS_LPP_MtaMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_MtaMsgDistr is entered!");

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch(pEmmMsg->ulMsgName)
    {
        case ID_MTA_LPP_GNSS_CAP_CNF:
            //NAS_LPP_RcvMtaLppGnssCapCnf( );
            break;

        default:
            break;
    }
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasLppMtaMsgProc.c */
