

#ifndef _NASCOMMBUFFER_H
#define _NASCOMMBUFFER_H




/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "vos.h"
#include    "NasCommPublic.h"

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
#define NAS_COMM_BUFF_ESM_MAX_ITEM_NUM                      (10)
/*modify from 1500 to 2048*/
#define NAS_COMM_BUFF_ESM_ITEM_MAX_SIZE                     (2048)
#define NAS_COMM_BUFF_EMM_MAX_ITEM_NUM                      (16)
#define NAS_COMM_BUFF_EMM_ITEM_MAX_SIZE                     (300)

#define NAS_COMM_BUFF_ITEM_USED                             (1)
#define NAS_COMM_BUFF_ITEM_UNUSED                           (0)
#define NAS_COMM_BUFF_ITEM_ILLEGAL_ID                       (0xff)

#define NAS_COMM_BUFF_SUCCESS                               (0)
#define NAS_COMM_BUFF_CHECK_FAIL                            (1)
#define NAS_COMM_BUFF_FREE_FAIL                             (2)
#define NAS_COMM_BUFF_QUERY_TYPE_TABLE_FAIL                 (3)

#define NAS_COMM_BUFF_NUM                                   (sizeof(g_astNasBuffTypeTable) / sizeof(NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU))
/*lint -e961*/
#define NAS_COMM_BUFF_PROT_CRC                              (0x88668866)
/*lint +e961*/
#define NAS_COMM_BUFF_ITEM_RESERVED_HEAD_LEN                (sizeof(NAS_COMM_BUFFER_ITEM_HEAD_STRU))
#define NAS_COMM_BUFF_ITEM_RESERVED_TAIL_LEN                (sizeof(VOS_UINT32))
#define NAS_COMM_BUFF_ITEM_RESERVED_LEN                     (NAS_COMM_BUFF_ITEM_RESERVED_HEAD_LEN + NAS_COMM_BUFF_ITEM_RESERVED_TAIL_LEN)

#define NAS_GetBufferTypeTable()                            (g_astNasBuffTypeTable)
#define NAS_GetBufferTypeTableItem(ulIndex)                 (&g_astNasBuffTypeTable[ulIndex])
#define NAS_GetBufferCtrlBlock(ulIndex)                     (&g_astNasBuffCtrlBlockTable[ulIndex])


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NAS_COMM_BUFF_TYPE_ENUM
{
    NAS_COMM_BUFF_TYPE_ESM              = 0,                                    /*ESM��������*/
    NAS_COMM_BUFF_TYPE_EMM              = 1,                                    /*EMM��������*/

    NAS_COMM_BUFF_TYPE_BUTT
};
typedef VOS_UINT8  NAS_COMM_BUFF_TYPE_ENUM_UINT8;

enum NAS_COMM_BUFF_STATE_ENUM
{
    NAS_COMM_BUFF_STATE_NOT_INITED      = 0,                                    /*������δ��ʼ��*/
    NAS_COMM_BUFF_STATE_INITED          = 1,                                    /*�������ѳ�ʼ��*/

    NAS_COMM_BUFF_STATE_BUTT
};
typedef VOS_UINT8  NAS_COMM_BUFF_STATE_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : NAS_COMM_BUFFER_ITEM_STRU
 �ṹ˵��  : �����¼�ṹ��
 ***************************************************************************/
typedef struct
{
    VOS_UINT32                          ulProtCrc;                              /* �����¼�洢�ռ䱣����ʶ */
    VOS_UINT8                           ucUsedTag;                              /* ��ʶ��¼�Ƿ��ѷ��� */
    VOS_UINT8                           aucReserved[3];
}NAS_COMM_BUFFER_ITEM_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_COMM_BUFFER_CTRL_BLOCK_STRU
 �ṹ˵��  : ����ṹ��
 ***************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsedNum;                              /* ���ü�¼���� */
    VOS_UINT8                           ucMaxNum;                               /* ����¼�洢���� */
    NAS_COMM_BUFF_STATE_ENUM_UINT8      enState;                                /* �Ƿ��ʼ����ʶ */
    VOS_UINT8                           aucReserved[1];

    VOS_UINT32                          ulMaxItemLen;                           /* ��¼��󳤶� */
}NAS_COMM_BUFFER_CTRL_BLOCK_STRU;

/*****************************************************************************
 �ṹ��    : NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU
 �ṹ˵��  : �������ͱ��¼�ṹ
 ***************************************************************************/
typedef struct
{
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBufferType;                        /* �������� */
    VOS_UINT8                           ucMaxBuffItemNum;                       /* �����¼������ */
    VOS_UINT8                           ucReserved[2];
    VOS_UINT8                          *pucBuff;                                /* �������׵�ַ */
    VOS_UINT32                          ulMaxBuffItemLen;                       /* �����¼��󳤶� */
}NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT8                        g_aucEsmBuff[NAS_COMM_BUFF_ESM_MAX_ITEM_NUM][NAS_COMM_BUFF_ESM_ITEM_MAX_SIZE + NAS_COMM_BUFF_ITEM_RESERVED_LEN];
extern NAS_COMM_BUFFER_CTRL_BLOCK_STRU  g_astNasBuffCtrlBlockTable[];

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID*  NAS_COMM_AllocBuffItem
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType,
    VOS_UINT32                          ulAllocLen
);
extern VOS_UINT32  NAS_COMM_CheckBuff
(
    VOS_UINT8                          *pucBuffItemAddr,
    VOS_UINT32                          ulMaxBuffItemLen
);
extern VOS_VOID  NAS_COMM_ClearBuff
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType
);
extern VOS_VOID  NAS_COMM_ClearBuffItem
(
    VOS_UINT8                          *pucBuffItemAddr,
    VOS_UINT32                          ulMaxBuffItemLen
);
extern VOS_UINT32  NAS_COMM_FreeBuffItem
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType,
    const VOS_VOID                     *pBufferItemStorageAddr
);
extern VOS_VOID  NAS_COMM_InitBuff
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType
);
extern VOS_VOID  NAS_COMM_InitBuffItem
(
    VOS_UINT8                          *pucBuffItemAddr,
    VOS_UINT32                          ulMaxBuffItemLen
);
extern VOS_UINT32 NAS_COMM_QueryBuffTypeTableItem
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType,
    VOS_UINT32                         *pulIndex
);
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

#endif /* end of NasCommBuffer.h*/
