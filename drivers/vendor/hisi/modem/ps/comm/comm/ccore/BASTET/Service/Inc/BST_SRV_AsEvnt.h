
#ifndef __BST_SRV_AS_H__
#define __BST_SRV_AS_H__
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_SRV_Define.h"
#include "BST_DRV_Common.h"
#include "BST_OS_Thread.h"
#include "BST_OS_Sync.h"
#include "BST_LIB_List.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_AS_EVT_BIT                  ( 0x01U )
#define BST_SRV_SetAsFlag(ulSet,enEvt)  ( (ulSet) |= (  BST_UINT32 )\
                                        ( BST_AS_EVT_BIT << (enEvt) ) ) 

#define BST_SRV_ClrAsFlag(ulSet,enEvt)  ( (ulSet) &= (~(BST_UINT32 )\
                                        ( BST_AS_EVT_BIT << (enEvt) ) ) )
#define BST_SRV_AsEvntFlagUsed(ulSet,enEvt) ( (ulSet) & ( BST_AS_EVT_BIT <<(enEvt) ) )

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
typedef BST_UINT32          BST_AS_EVT_SET_UINT32;

class BST_SRV_CAsRcver
{
BST_PUBLIC:
    BST_AS_EVT_SET_UINT32   GetEventSet( BST_VOID );

    virtual BST_VOID        AsEventCallback(
        BST_AS_EVT_ENUM_UINT32    enEvent,
        BST_UINT32                ulLength,
        BST_VOID                 *pvData ) = 0;
    const   BST_OS_MBX_T         *m_pstRcvMbox;

BST_PROTECTED:
                BST_SRV_CAsRcver( BST_OS_MBX_T *pstRcverMbx );

    virtual    ~BST_SRV_CAsRcver( BST_VOID );

    BST_VOID    RegAsNotice( BST_AS_EVT_ENUM_UINT32 enEvent );

    BST_VOID    DelEvent( BST_AS_EVT_ENUM_UINT32 enEvent );
BST_PRIVATE:
    BST_AS_EVT_SET_UINT32       m_ulEventFlagSet;
};

typedef struct{
    NODE                node;
    BST_SRV_CAsRcver   *pRcver;
}BST_SRV_ASRCVER_NODE_STRU;

class BST_SRV_CAsEvt
{
BST_PUBLIC:
    static BST_SRV_CAsEvt  *GetInstance( BST_VOID );

    BST_VOID    Receive(
        BST_AS_EVT_ENUM_UINT32  enEvent,
        BST_UINT32              ulLength,
        BST_VOID               *pvData );

    BST_VOID    Forward(
        BST_SRV_CAsRcver       *pcAsRcver,
        BST_AS_EVT_ENUM_UINT32  enEvent,
        BST_UINT32              ulLength,
        BST_VOID               *pvData );

    BST_VOID    Save(
        BST_AS_EVT_ENUM_UINT32  enEvent,
        BST_UINT32              ulBufLen,
        BST_VOID               *pvData );

    BST_BOOL                    Inquire(
        BST_AS_EVT_ENUM_UINT32  enEvent,
        BST_UINT32              ulBufLen,
        BST_VOID               *pvData );

    BST_VOID Attach( BST_SRV_CAsRcver *pcRcver );

    BST_VOID Detach( BST_SRV_CAsRcver *pcRcver );
BST_PRIVATE:
    LIST                m_stAsRcverList;

    BST_VOID            ClearVote( BST_VOID );

                        BST_SRV_CAsEvt( BST_VOID );

    virtual            ~BST_SRV_CAsEvt  ( BST_VOID );
};
/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/
extern "C" BST_UINT32   BST_SRV_RcvAsEvent(
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData );

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
