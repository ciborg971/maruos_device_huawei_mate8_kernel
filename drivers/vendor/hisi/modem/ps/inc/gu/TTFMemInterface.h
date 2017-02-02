

#ifndef __TTFMEMINTERFACE_H__
#define __TTFMEMINTERFACE_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "v_typdef.h"
#include "product_config.h"
#include "TtfDrvInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ת����ԭ�е�����RLC SDU�ص����ݶ�������DATA����ȡ */
#define  TTF_MEM_POOL_ID_UL_RLC_SDU    TTF_MEM_POOL_ID_UL_DATA

/* ת����ԭ�е�����RLC PDU�ص����ݶ�������DATA����ȡ */
#define  TTF_MEM_POOL_ID_UL_RLC_PDU    TTF_MEM_POOL_ID_UL_DATA

/* ת����ԭ�е�����DL�ص����ݶ�������PDU����ȡ */
#define  TTF_MEM_POOL_ID_DL            TTF_MEM_POOL_ID_DL_PDU


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : TTF_MEM_POOL_ID_ENUM_UINT32
 Э����  :
 ASN.1���� :
*****************************************************************************/
enum TTF_MEM_POOL_ID_ENUM
{
    TTF_MEM_POOL_ID_DL_SHARE  = 0,    /* C-CPU ���п�˹����ڴ�أ�Ŀǰֻ����CDS��CSTģ��ʹ�� */
    TTF_MEM_POOL_ID_DL_PDU,           /* C-CPU ����PDU�ڴ�� */
    TTF_MEM_POOL_ID_UL_DATA,          /* C-CPU ���������ڴ�� */
    TTF_MEM_POOL_ID_EXT,              /* A-CPU ����ڴ�� */
    TTF_MEM_POOL_ID_UL_IP_DATA,       /* C-CPU ���� IP�������ڴ��*/

    TTF_MEM_POOL_ID_BUTT
};
typedef VOS_UINT32 TTF_MEM_POOL_ID_ENUM_UINT32;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern TTF_MEM_ST *TTF_MemBlkAlloc_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum, VOS_UINT32 ulPid, VOS_UINT32 ulPoolId, VOS_UINT16 usLen);

extern VOS_VOID TTF_MemFree_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum, VOS_UINT32 ulPid, TTF_MEM_ST **ppMem);

extern TTF_MEM_ST * TTF_DataTransformTtfMem_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum,VOS_UINT8* pucData,VOS_UINT16 usLen, VOS_VOID*  pstIMMZc);



#define TTF_MemBlkAlloc(ulPid, ulPoolId, usLen) \
    TTF_MemBlkAlloc_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, usLen)



#define TTF_MemFree(ulPid, pMem) \
    TTF_MemFree_Debug(THIS_FILE_ID, __LINE__, ulPid, &(pMem))



extern VOS_VOID TTF_ExtMemFree( void **pstExtMem );

#define TTF_RemoteFreeImmMem(pucAddr)  TTF_ExtMemFree((&pucAddr))



#define TTF_DataTransformTtfMem(pucData, usLen, pstIMM)\
    TTF_DataTransformTtfMem_Debug(THIS_FILE_ID, __LINE__, pucData, usLen, pstIMM)



extern VOS_UINT32 TTF_GetDlIpFreeMemCnt (VOS_VOID);



extern VOS_UINT32 TTF_GetUlIpFreeMemCnt (VOS_VOID);



extern VOS_VOID TTF_MemCcpuCheckPoolLeak( VOS_VOID );



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TTFMemInterface.h */

