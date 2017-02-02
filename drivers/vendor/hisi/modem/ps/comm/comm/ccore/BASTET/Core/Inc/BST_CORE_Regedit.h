

#ifndef __BST_CORE_Regedit_H__
#define __BST_CORE_Regedit_H__
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_CORE_RegistryDefine.h"
#include "BST_CORE_RegistryTblMng.h"
#include "BST_CORE_Task.h"
#include "BST_OS_Thread.h"
#include "BST_LIB_List.h"
#include "BST_SRV_ChnlCtrl.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_CORE_INVALID_INQUIRED_LEN   ( 0xFFFFU )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/

class BST_CORE_CAPACallBack
{
BST_PUBLIC:
    virtual BST_UINT16              Inquired(
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_UINT16                  usDataSize,
        BST_VOID                   *const pData ){ return 0; };

    virtual BST_ERR_ENUM_UINT8      Configed(
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_UINT16                  usLen,
        const BST_VOID             *const pData,
        BST_UINT8                 **pucNewAddr ){ return BST_NO_ERROR_MSG; };
};

class BST_CORE_CAPCCallBack
{
BST_PUBLIC:
    virtual BST_VOID ChnlCtrlSend(
        BST_SRV_CHNL_HEAD_STRU     *pstPktItem ){};

    virtual BST_VOID ChnlCtrlClose( BST_VOID ){};

    virtual BST_VOID ChnlCtrlClear( BST_VOID ){};
};

typedef struct
{
    NODE                            node;
    BST_CTask                      *pTask;
    BST_CORE_CAPACallBack          *pcApAItf;
    BST_CORE_CAPCCallBack          *pcApCItf;
    LIST                            RegParamList;
} BST_CORE_REGNODE_STRU;

typedef struct
{
    NODE                            node;
    BST_CORE_PID_STRU               stParamInfo;
    BST_UINT32                      ulNotice;
}BST_CORE_PIDNODE_STRU;

class BST_CORE_CRegedit
{
BST_PUBLIC:
    static BST_CORE_CRegedit       *GetInstance ( BST_VOID );

    BST_UINT16                      GetLen(
        BST_OBJT_ADDR_T             usObjtAddr,
        BST_OFST_ADDR_T             usOfstAddr,
        BST_CORE_PID_ENUM_UINT16    enParamId );

    BST_UINT16                      Inquire(
        BST_OBJT_ADDR_T             usObjtAddr,
        BST_OFST_ADDR_T             usOfstAddr,
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_UINT16                  usDataSize,
        BST_VOID                   *const pData );

    BST_ERR_ENUM_UINT8              Config(
        BST_OBJT_ADDR_T             usObjtAddr,
        BST_OFST_ADDR_T             usOfstAddr,
        const BST_CORE_PID_STRU    *pstRegParam );

    BST_ERR_ENUM_UINT8              Config(
        BST_OBJT_ADDR_T             usObjtAddr,
        BST_OFST_ADDR_T             usOfstAddr,
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_UINT16                  usDataLen,
        BST_VOID                   *pData );

    BST_ERR_ENUM_UINT8              Update(
        BST_OBJT_ADDR_T             usObjtAddr,
        BST_OFST_ADDR_T             usOfstAddr,
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_UINT16                  usDataLen,
        BST_VOID                   *pData );

    BST_ERR_ENUM_UINT8              Regist(
        BST_CTask                  *pTask, 
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_CORE_PID_LEN_T          usLen,
        const void *const           pValue );

    BST_ERR_ENUM_UINT8              Regist(
        BST_CTask                  *pTask,
        const BST_UINT32            ulNoticeFlag,
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_CORE_PID_LEN_T          usLen,
        const void                 *const pValue );

    BST_ERR_ENUM_UINT8              Regist(
        BST_CTask                  *pTask, 
        BST_VOID                   *pAPInf,
        BST_UINT32                  ulAPVersion );

    BST_ERR_ENUM_UINT8              unRegist(
        const BST_CTask            *pTask,
        BST_CORE_PID_ENUM_UINT16    enParamId );

    BST_ERR_ENUM_UINT8              unRegist(
        const BST_CTask            *pTask );

    BST_ERR_ENUM_UINT8              ChnlCtrl(
        BST_OBJT_ADDR_T             usObjtAddr,
        BST_OFST_ADDR_T             usOfstAddr,
        BST_SRV_CHNL_HEAD_STRU     *pstChnHead );
    
BST_PRIVATE:
    BST_CORE_PIDNODE_STRU          *Select(
        BST_OBJT_ADDR_T             usObjtAddr,
        BST_OFST_ADDR_T             usOfstAddr,
        BST_CORE_PID_ENUM_UINT16    enParamId );

    BST_CORE_REGNODE_STRU          *Select(
        BST_OBJT_ADDR_T             usObjtAddr,
        BST_OFST_ADDR_T             usOfstAddr);

    BST_BOOL                        InputCheck(
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_UINT16                  usDataLen,
        const BST_VOID             *const pData ) const;

    BST_ERR_ENUM_UINT8              Save(
        BST_CORE_CAPACallBack      *pCallBack,
        BST_CORE_PIDNODE_STRU      *pstPid,
        BST_UINT16                  usDataLen,
        BST_VOID                   *pData );

    LIST                            m_RegistryList;
                                    BST_CORE_CRegedit( BST_VOID );
                                   ~BST_CORE_CRegedit( BST_VOID );
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

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
