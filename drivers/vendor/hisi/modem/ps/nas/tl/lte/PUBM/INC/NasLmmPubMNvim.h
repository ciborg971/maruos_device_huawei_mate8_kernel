

#ifndef __NASLMMPUBMNVIM_H__
#define __NASLMMPUBMNVIM_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "vos.h"
#include    "NasLmmPubMNvimOsa.h"
#include    "LPsNvInterface.h"

#include    "NasLmmPubMFsm.h"
#include    "NasLmmCore.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define NAS_NVIM_MAX_BUFFER             1024
#define NAS_NVIM_SEND_COUNTER_NONE      0

#define NAS_NVIM_SECU_CONTEXT_MAX_LEN   150

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

typedef enum
{
    NAS_LMM_USIM_READ_SUCC              = 0x01,
    NAS_LMM_USIM_READ_HARD_IMSI_ERR,
    NAS_LMM_USIM_READ_SOFT_IMSI_ERR,
    NAS_LMM_USIM_READ_UST_ERR ,

    NAS_LMM_USIM_READ_BUTT
}NAS_LMM_USIM_READ_RST_ENUM;
typedef VOS_UINT32  NAS_LMM_USIM_READ_RST_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_LMM_ITEM_TYPE_ENUM
 Э����  : typedef VOS_UINT32     NAS_LMM_ITEM_TYPE_ENUM_UINT32;
 ASN.1���� :
 ö��˵��  : NV_Item������
*****************************************************************************/
typedef VOS_UINT32     NAS_LMM_ITEM_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_LMM_RETURN_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ��������ֵ
*****************************************************************************/

enum  NAS_LMM_RETURN_ENUM
{
    EN_NV_OK                ,
    EN_NV_ITEM_NOTEXIST     ,
    EN_NV_MAXNUM_ERR        ,
    EN_BUFFER_NOT_ENOUGH    ,
    EN_NV_SYS_ERROR
};
typedef VOS_UINT32   NAS_LMM_RETURN_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_USIM_FILE_ID_ENUM
 ö��˵��  : USIM�е�Э���ļ�ID���� 31.102

*****************************************************************************/
enum  NAS_USIM_FILE_ID_ENUM
{
    NAS_USIM_FILE_ID_INVALID            = 0x0000,
    NAS_USIM_FILE_ID_PS_LOC             = 0x6F46,
    NAS_USIM_FILE_ID_SERVICE_TABLE      = 0x6F38,
    NAS_USIM_FILE_ID_IMSI               = 0x6F07,
    NAS_USIM_FILE_ID_MNC_LEN            = 0x6FAD,
    NAS_USIM_FILE_ID_FORB_PLMN_LIST     = 0x6F7B,
    NAS_USIM_FILE_ID_UPLMN              = 0x6F60,
    NAS_USIM_FILE_ID_OPLMN              = 0x6F61,
    NAS_USIM_FILE_ID_PERID_TIMER        = 0x6F31,
    NAS_USIM_FILE_ID_AC_CLASS           = 0x6F78,
    NAS_USIM_FILE_ID_EPS_LOC_INFO       = 0x6FE3,
    NAS_USIM_FILE_ID_SEC_CONTEXT        = 0x6FE4,
    NAS_USIM_FILE_ID_HPLMN_ACT          = 0x6F62,
    NAS_USIM_FILE_ID_LRPLMNSI           = 0x6FDC,
    NAS_USIM_FILE_ID_BUTT
};
typedef VOS_UINT16   NAS_USIM_FILE_ID_ENUM_UINT16;


/*****************************************************************************
 ö����    : NAS_EMMC_LMM_USIM_FILE_ID_ENUM
 ö��˵��  : USIM�е�Э���ļ�ID���� 31.102

*****************************************************************************/
enum  NAS_EMMC_LMM_USIM_FILE_ID_ENUM
{
    NAS_EMMC_LMM_USIM_FILE_ID_INVALID            = 0x0000,
    NAS_EMMC_LMM_USIM_FILE_ID_SERVICE_TABLE      = 0x6F38,
    NAS_EMMC_LMM_USIM_FILE_ID_IMSI               = 0x6F07,
    NAS_EMMC_LMM_USIM_FILE_ID_BUTT
};
typedef VOS_UINT16   NAS_EMMC_LMM_USIM_FILE_ID_ENUM_UINT16;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/* NVIM���������������Ͷ��� */
typedef VOS_UINT32 ( * NAS_LMM_NV_ACTION_FUN )
(

    NAS_NVIM_CTRL_TBL *  /* ��Ϣָ�� */
);

/* NVIM������ṹ */
typedef struct
{
    NAS_LMM_ITEM_TYPE_ENUM_UINT32        ulEventType;        /* �¼����� */
    NAS_LMM_NV_ACTION_FUN                pfDecodeActionFun;  /* �������� */
    NAS_LMM_NV_ACTION_FUN                pfEncodeActionFun;  /* �������� */
}NAS_LMM_NV_ACT_STRU;



/*****************************************************************************
  6 UNION
*****************************************************************************/

/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32  NAS_LMM_NvimWrite( NAS_LMM_ITEM_TYPE_ENUM_UINT32 ulNVItemType,
                                    VOS_VOID *pData,
                                    VOS_UINT16 usDataLen );
extern NAS_LMM_USIM_NV_RESULT  NAS_LMM_NvimRead(  NAS_LMM_ITEM_TYPE_ENUM_UINT32 ulNVItemType,
                                    VOS_VOID *pData,
                                    const VOS_UINT16 *pusDataLen );

extern VOS_VOID NAS_LMM_UsimFileWrite
(
    USIMM_DEF_FILEID_ENUM_UINT32        ulUsimFileId,
    VOS_VOID                           *pData,
    VOS_UINT16                          usDataLen
);
extern VOS_VOID NAS_LMM_UsimFileRead
(
    USIMM_DEF_FILEID_ENUM_UINT32        ulUsimFileId
);

extern VOS_UINT32 NAS_LMM_MatchNvImsi( VOS_VOID );
extern VOS_VOID   NAS_LMM_ProcessNvData( VOS_VOID );
/*extern VOS_VOID   NAS_LMM_ReadUsimFileFailed( MsgBlock * pMsg );*/
extern VOS_UINT32 NAS_LMM_ProcessHardUsimCnf(USIMM_READFILE_CNF_STRU * pstUsimFileCnf);
/*extern VOS_VOID   NAS_LMM_DoAfterReadManOrOptFileOver(VOS_VOID);*/
extern VOS_VOID   NAS_LMM_DoAfterReadOptFileOver( VOS_VOID );

extern NAS_LMM_USIM_READ_RST_ENUM_UINT32  NAS_LMM_ReadUsimFileImsi(VOS_VOID);

extern VOS_VOID   NAS_LMM_ReadLteUsimFile( VOS_VOID );
/*****************************************************************************
  9 OTHERS
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmPubMNvim.h*/

