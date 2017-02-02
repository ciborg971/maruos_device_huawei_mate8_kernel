
#ifndef __BST_APP_EMALIBASEPROC_H__
#define __BST_APP_EMALIBASEPROC_H__
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_CORE_NPTask.h"
#include "BST_APP_EmailPublic.h"
#include "BST_IP_Socket.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_EMIAL_BASE_CFGED_FLAG       ( BST_CFGFLG_ADDR | BST_CFGFLG_CYCL |  BST_CFGFLG_TYPE )

#define BST_EMAIL_IsBaseCfged( enFlag ) ( ( ( enFlag ) & ( BST_EMIAL_BASE_CFGED_FLAG ) ) \
                                                      == ( BST_EMIAL_BASE_CFGED_FLAG ) )

#define BST_APP_EMAIL_IsErgency(enErr)  ( ( BST_EMAIL_OTHER_EXCEPIONT == (enErr) ) \
                                        ||( BST_EMAIL_NOT_SUPPORT == (enErr) ) )

/*****************************************************************************
  3 ��/�ṹ����
*****************************************************************************/
class BST_APP_CEmailPacketProc : BST_PUBLIC BST_IP_CNetRcver, BST_PUBLIC BST_OS_CTimerCb
{
BST_PUBLIC:
    BST_APP_CEmailPacketProc ( const EMAIL_ACCOUNT_STRU *pstAccountInfo );

    virtual ~BST_APP_CEmailPacketProc( BST_VOID );
    /*��ӿ�*/

    virtual BST_BOOL InitEmailProc  ( BST_CORE_CNPTask *pTaskProp );
    virtual BST_VOID EntryProc      ( BST_VOID );


BST_PROTECTED:

    virtual BST_BOOL IsConfigOk( BST_VOID )
    {
        return BST_TRUE;
    }

    virtual BST_ERR_ENUM_UINT8 ParseResponse( 
        BST_UINT8                  *pucData,
        BST_UINT16                  usLength )
    {
        return BST_NO_ERROR_MSG;
    }
    virtual BST_VOID ResetMachine( BST_VOID ) { m_lServerState = BST_EMAIL_UNCONNECT;};
    virtual BST_ERR_ENUM_UINT8 RunStateMachine( BST_VOID ){ return BST_NO_ERROR_MSG; };
    virtual BST_ERR_ENUM_UINT8 FirstTrsProc   ( BST_VOID ){ return BST_NO_ERROR_MSG; };
    virtual BST_UINT8 *ConfigOtherInfo(
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_UINT16                  usLen,
        const BST_VOID             *const pData )
    {
        return  0;
    }
    /*BST_OS_CTimerCb�ӿ�ʵ��*/
    BST_VOID    TimerExpired(
        BST_OS_TIMERID_T            ulId,
        BST_VOID                   *pvPara );
    /*BST_IP_CNetRcver�ӿ�ʵ��*/  
    BST_IP_ERR_T Connectd( BST_IP_CSocket *pcSocket );
    BST_IP_PKTPROC_MODE_ENUM Received(
        BST_IP_CSocket             *pcSocket,
        const BST_UINT8            *const pucData,
        const BST_UINT16            usLength );
    BST_VOID    IpErr( BST_IP_CSocket *pcSocket, BST_IP_ERR_T InIpErrMsg );
    BST_BOOL    IsBasicConfigOk ( BST_VOID ) const;
    BST_VOID    CloseConnection ( BST_VOID );
    BST_BOOL    CreateConnection( BST_VOID );
    BST_VOID    CloseAndFinish  ( BST_VOID );
    BST_VOID    NewMailProc     ( BST_VOID );
    BST_VOID    FailProc        ( BST_ERR_ENUM_UINT8 enErrType );
    virtual BST_ERR_ENUM_UINT8 SendCommand(
        const BST_UINT8            *pucCmd,
        BST_UINT16                  usLength );
    BST_IP_CSocket                 *m_pSyncSocket;          /* BST_IP_CSocket �� */
    EMAIL_ACCOUNT_STRU             *m_pstAccountInfo;
    BST_CORE_CNPTask               *m_pcHostTask;
    BST_UINT16                      m_usRetryTimes;
    BST_UINT16                      m_usErrSocketTimes;
    BST_UINT32                      m_ulTimerId;
    BST_INT32                       m_lServerState;
    BST_EMAIL_UID_INFO_STRU        *m_pstLastUID;
BST_PRIVATE:
    friend  class BST_APP_CEmailBox;
};
/*****************************************************************************
  4 OTHERS����
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
