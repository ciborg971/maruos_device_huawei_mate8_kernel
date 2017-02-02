

#ifndef __TTF_MEMCTRL_H__
#define __TTF_MEMCTRL_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TtfMemoryMap.h"
#include "vos.h"
#include "TtfNvInterface.h"
#include "NVIM_Interface.h"
#include "NasNvInterface.h"
#include "PsCommonDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* TTF�ڴ����ͳ�ʼ����� */
#define TTF_MEMCTRL_TYPE_INIT_FLG                       (1)

/* TTF�ڴ����ʹ��ڲ����ڱ�� */
#define TTF_MEMCTRL_TYPE_EXIST_FLG                      (1)

/* TTF�ڴ����Ϳɼ����ɼ���� */
#define TTF_MEMCTRL_TYPE_VISIBLE_FLG                    (1<<1)

#define TTF_MEMCTRL_INVAILD_SIZE                        (0xFFFFFFFF)

#define TTF_MEMCTRL_SET_ADDR_INIT_FLG(flg)              (g_stTtfMemCtrlAddr.stTtfMemCtrlAddrComm.ucInitFlg = flg)

#define TTF_MEMCTRL_GET_ADDR_INIT_FLG()                 (g_stTtfMemCtrlAddr.stTtfMemCtrlAddrComm.ucInitFlg)

#define TTF_MEMCTRL_SET_TYPE_FLG(type, flg)             (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulAttribute |= flg)

#define TTF_MEMCTRL_GET_TYPE_ATTRIBUTE(type)            (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulAttribute)

#define TTF_MEMCTRL_SET_TYPE_LEN(type, len)             (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulLen = len)

#define TTF_MEMCTRL_GET_TYPE_LEN(type)                  (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulLen)

#define TTF_MEMCTRL_SET_TYPE_OFFSET_BASE_LEN(type, len) (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulOffsetBaseLen = len)

#define TTF_MEMCTRL_GET_TYPE_OFFSET_BASE_LEN(type)      (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulOffsetBaseLen)

/* �ڴ汣��ħ���ֳ��� */
#define TTF_MEM_MAGIC_NUM_LEN                           (32)

/*ħ���ֳ�ʼ��ֵ */
#define TTF_MEM_MAGIC_NUM_VALUE                         (0x5A)

#define TTF_DYNAMIC_MEM_LEN_ZERO                        (0)

#define TTF_MEMCTRL_PID_INVAILD                         (0xFF)

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
/* ��BSP��̬����uncached�ڴ�, ����ɹ�����ʵ�ʵ�ַ������ʧ���򷵻�VOS_NULL_PTR */
#define TTF_UNCACHED_MEM_BSP_ALLOC(ulTtfMemByteSize)   mdrv_cachedmem_alloc(ulTtfMemByteSize)
#else
/* ��ǰ�ڴ涼����C�˵�uncache�ڴ棬A�˱�֤�����lint OK */
#define TTF_UNCACHED_MEM_BSP_ALLOC(ulTtfMemByteSize)   kmalloc(ulTtfMemByteSize, GFP_KERNEL)
#endif
#define TTF_MEM_SET_DYNAMIC_INIT_ADDR_FLAG(ulInitFlag) \
    (g_stTtfMemDynamicCtrlEntity.ulTtfMemDynamicInitAddrFlag = (ulInitFlag))

#define TTF_MEM_GET_DYNAMIC_INIT_ADDR_FLAG() \
    (g_stTtfMemDynamicCtrlEntity.ulTtfMemDynamicInitAddrFlag)

#define TTF_MEM_SET_SUPPORT_WCDMA(Modem, IsSupportWcdma) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupportWcdma = (IsSupportWcdma))

#define TTF_MEM_SET_SUPPORT_GSM(Modem, IsSupportGsm) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupportGsm = (IsSupportGsm))

#define TTF_MEM_GET_DYNAMIC_ADDR_TYPE() \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[0])

#define TTF_MEM_SET_TTF_BASE_ADDR(ulTtfMemBaseAddr) \
    (g_stTtfMemDynamicCtrlEntity.pucTtfMemBaseAddr = (ulTtfMemBaseAddr))

#define TTF_MEM_GET_TTF_BASE_ADDR() \
    (g_stTtfMemDynamicCtrlEntity.pucTtfMemBaseAddr)

#define TTF_MEM_SET_TTF_TOTAL_LEN(ulDynamicTtfMemLen) \
    (g_stTtfMemDynamicCtrlEntity.ulMemTotalLen = (ulDynamicTtfMemLen))

#define TTF_MEM_GET_TTF_TOTAL_LEN() \
    (g_stTtfMemDynamicCtrlEntity.ulMemTotalLen)

#define TTF_DYNAMIC_MEM_SET_OFFSETBASE(type, OffsetBaseLen) \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[type].ulOffsetBaseLen = OffsetBaseLen)

#define TTF_DYNAMIC_MEM_GET_OFFSETBASE(type) \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[type].ulOffsetBaseLen)

#define TTF_DYNAMIC_MEM_SET_LEN(type, len) \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[type].ulLen = len)

#define TTF_DYNAMIC_MEM_GET_LEN(type) \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[type].ulLen)

#define TTF_DYNAMIC_MEM_SET_ATTRIBUTE(type, attribute) \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[type].ulAttribute |= attribute)

#define TTF_DYNAMIC_MEM_GET_ATTRIBUTE(type) \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[type].ulAttribute)

#define WTTF_BBPMST_MAC_TB_HEAD_NUM                 (g_stBbpMstTBHeadInfo.ulTBHeadNum)
#define WTTF_BBPMST_MAC_TB_DATA_NUM                 (g_stBbpMstTBHeadInfo.ulTBHeadNum - g_stBbpMstTBHeadInfo.ulTBHeadReserved)

/* ͷ�������ȣ���λ:�ֽ� */
#define WTTF_BBPMST_MAC_TB_HEAD_BUFF_LEN            ((WTTF_BBPMST_MAC_TB_HEAD_NUM) * (WTTF_MAC_HSDPA_TB_HEAD_SIZE))

/* ���������ȣ���λ:�ֽ� */
#define WTTF_BBPMST_MAC_TB_DATA_BUFF_LEN            ((WTTF_BBPMST_MAC_TB_DATA_NUM) * (WTTF_MAC_HSDPA_TB_DATA_SIZE))

#define TTF_DYNAMIC_MEM_CHECK_PERIOD_COUNTER        (1000)

/*****************************************************************************
 ö����    : TTF_MEM_PLATFORM_SUPPORT_WCDMA_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �Ƿ�֧��wcdma
*****************************************************************************/
enum TTF_MEM_PLATFORM_SUPPORT_WCDMA_ENUM
{
    TTF_MEM_PLATFORM_SUPPORT_WCDMA  = 0,                /* ֧��WCDMA */
    TTF_MEM_PLATFORM_NOT_SUPPORT_WCDMA,                 /* ��֧��WCDMA */
    TTF_MEM_PLATFORM_SUPPORT_BUTT
};
typedef VOS_UINT8 TTF_MEM_PLATFORM_SUPPORT_WCDMA_ENUM8;

/*****************************************************************************
 ö����    : TTF_MEMCTRL_CALLBACK_FUNC_FLAG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �ص�������ʾ
*****************************************************************************/
enum TTF_MEMCTRL_CALLBACK_FUNC_FLAG_ENUM
{
    TTF_MEMCTRL_CALLBACK_FUNC_DRV  = 0,                /* ����ص� */
    TTF_MEMCTRL_CALLBACK_FUNC_TTF,                     /* TTF�ص� */

    TTF_MEMCTRL_CALLBACK_FUNC_BUTT
};
typedef VOS_UINT8 TTF_MEMCTRL_CALLBACK_FUNC_FLAG_ENUM_ENUM8;

/*****************************************************************************
 ö����    : TTF_MEM_MSG_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ��Ϣ�ϱ�ID
*****************************************************************************/
enum TTF_MEM_MSG_ID_ENUM
{
    ID_TRACE_TTF_MEM_LEAK_IND               = 0X0315,   /* _H2ASN_MsgChoice TTF_MEM_LEAK_INFO_IND_MSG */
    ID_TRACE_TTF_MEM_ERR_IND                = 0x0316,   /* _H2ASN_MsgChoice TTF_MEM_ERROR_INFO_IND_STRU */

    ID_TRACE_TTF_MEM_BUTT
};
typedef VOS_UINT16 TTF_MEM_MSG_ID_ENUM_UINT16;

enum TTF_MEM_POOL_BLK_INDEX_ENUM
{
    TTF_MEM_POOL_BLK_INDEX_0    = 0,
    TTF_MEM_POOL_BLK_INDEX_1,
    TTF_MEM_POOL_BLK_INDEX_2,
    TTF_MEM_POOL_BLK_INDEX_3,

    TTF_MEM_POOL_BLK_INDEX_BUTT
};
typedef VOS_UINT32 TTF_MEM_POOL_BLK_INDEX_ENUM_UINT32;

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
�ṹ��    : TTF_MEMCTRL_ADDR_COMM_STRU
Э����  : ��
ASN.1���� : ��
�ṹ˵��  : TTF�ڴ��ַ�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucInitFlg;          /* ��ʼ����� */
    VOS_UINT8                           ucRcv[3];           /* ����λ */
} TTF_MEMCTRL_ADDR_COMM_STRU;

/*****************************************************************************
�ṹ��    : TTF_MEMCTRL_ADDR_TYPE_STRU
Э����  : ��
ASN.1���� : ��
�ṹ˵��  : TTF�ڴ��ַ���ͽṹ
*****************************************************************************/
typedef struct
{
    TTF_MEMCTRL_ADDR_COMM_STRU          stTtfMemCtrlAddrComm;
    TTF_MEMCTRL_ADDR_TYPE_STRU          astTtfMemCtrlAddrType[TTF_MEMCTRL_ADDR_TYPE_BUTT];
} TTF_MEMCTRL_ADDR_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                              usMsgName;
    VOS_UINT8                               aucRsv[2];
    TTF_DYNAMIC_MEM_ADDR_TYPE_ENUM_UINT32   ulMagicNumFlag;
    VOS_UINT32                              aulMagicNum[TTF_MEM_MAGIC_NUM_LEN];
    TTF_MEMCTRL_ADDR_TYPE_STRU              astTtfMemAddrType[TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT];
} TTF_MEM_ERROR_INFO_IND_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern TTF_MEMCTRL_ADDR_STRU                   g_stTtfMemCtrlAddr;

/* BBPMSTͷ��TB����Ϣ */
extern WTTF_MACDL_BBPMST_TB_HEAD_STRU          g_stBbpMstTBHeadInfo;

extern TTF_MEM_SOLUTION_CFG_NV_STRU            g_stTtfMemSolution;
/*****************************************************************************
  5 OTHERS����
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

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of Fc.h */


