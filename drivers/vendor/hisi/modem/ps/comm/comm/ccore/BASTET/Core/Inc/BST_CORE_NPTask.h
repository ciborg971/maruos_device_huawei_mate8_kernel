

#ifndef __BST_CORE_N_P_TASK_H__
#define __BST_CORE_N_P_TASK_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_CORE_PTask.h"
#include "BST_CORE_Regedit.h"
#include "BST_IP_RcverMng.h"
#include "BST_IP_Socket.h"
#include "BST_DRV_Net.h"
#include "BST_DSPP_Report.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_CFGFLG_NONE                 0x00
#define BST_CFGFLG_ADDR                 0x01
#define BST_CFGFLG_CYCL                 0x02
#define BST_CFGFLG_TYPE                 0x04
#define BST_CFGFLG_PRTY                 0x08
#define BST_CFGFLG_CLON                 0x10


#define BST_IsInfoConfiged( enFlag )     ( (enFlag) == ( m_CfgedFlag & (enFlag) ) )
#define BST_SetConfigFlag( enFlag )      ( m_CfgedFlag |= (enFlag) )
#define BST_UnsetConfigFlag( enFlag )    ( m_CfgedFlag &= (~( enFlag) ) )
#define BST_ResetPrptyFlag()             ( m_CfgedFlag &= (~( BST_CFGFLG_PRTY ) ) )
#define BST_IsIpBaseCfged( enFlag )      ( ( ( enFlag ) & ( BST_CFGFLG_ADDR | BST_CFGFLG_TYPE ) ) \
                                          == ( BST_CFGFLG_ADDR | BST_CFGFLG_TYPE ) )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
class BST_IP_CSocket;

class BST_CORE_CNPTask :
    BST_PUBLIC BST_CORE_CPTask, BST_PUBLIC BST_CORE_CAPACallBack
{
BST_PUBLIC:
    BST_CORE_CNPTask(
        BST_PROCID_T              in_usProcId,
        BST_TASKID_T              in_usTaskId );

    virtual ~BST_CORE_CNPTask( BST_VOID );

    BST_ERR_ENUM_UINT8          ReportSocketProperty( BST_VOID );

    BST_ERR_ENUM_UINT8          ReportTrafficFlow( BST_VOID );

    BST_ERR_ENUM_UINT8          Report(
        BST_ERR_ENUM_UINT8        enErrVal );

    virtual BST_UINT16          PidInquired(
        BST_CORE_PID_ENUM_UINT16  enParamId,
        BST_UINT16                usDataSize,
        BST_VOID                 *const pData );

    virtual BST_ERR_ENUM_UINT8  PidConfiged(
        BST_CORE_PID_ENUM_UINT16  enParamId,
        BST_UINT16                usLen,
        const BST_VOID           *const pData,
        BST_UINT32                ulBaseCfged,
        BST_UINT8               **pucNewAddr );

    BST_IP_CSocket             *m_pSocket;
    BST_UINT32                  m_CfgedFlag;

BST_PROTECTED:
    BST_DSPP_CReport           *m_pExptReport;
    BST_PRTC_TYPE_ENUM_UINT32   m_ProtolType;

BST_PRIVATE:
    BST_UINT16          Inquired(
        BST_CORE_PID_ENUM_UINT16  enParamId,
        BST_UINT16                usDataSize,
        BST_VOID                 *const pData );

    BST_UINT16          InquiredSocketProperty(
        BST_UINT16                  usDataSize,
        BST_VOID                   *const pData );

    BST_UINT16          InquiredTrafficFlow(
        BST_UINT16                  usDataSize,
        BST_VOID                   *const pData );

    BST_ERR_ENUM_UINT8  Configed(
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_UINT16                  usLen,
        const BST_VOID             *const pData,
        BST_UINT8                 **pucNewAddr );

    BST_ERR_ENUM_UINT8  ConfigedPriodic(
        BST_UINT16                  usLen,
        const BST_VOID             *const pData,
        BST_UINT8                 **pucNewAddr );

    BST_ERR_ENUM_UINT8  ConfigedSockeInfo(
        BST_UINT16                  usLen,
        const BST_VOID             *const pData,
        BST_UINT8                 **pucNewAddr );

    BST_ERR_ENUM_UINT8  ConfigedSockeProperty(
        BST_UINT16                  usLen,
        const BST_VOID             *const pData,
        BST_UINT8                 **pucNewAddr );
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


