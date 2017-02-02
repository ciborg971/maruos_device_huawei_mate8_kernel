/******************************************************************************

                  ��Ȩ���� (C), 2014, ��Ϊ�������޹�˾
*******************************************************************************
  �� �� ��   : BST_APP_LongRRC.c
  �� �� ��   : ����
  ��    ��   : w00346326
  ��������   : 2015��5��19��
  ����޸�   :
  ��������   : �ն˱���RRC����״̬�������߼�ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��23��
    ��    ��   : w00346326
    �޸�����   : �����ļ�
******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_APP_LongRRC.h"

/******************************************************************************
   2 �궨��
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/
BST_VOID               BST_APP_LongRRCTimerCallback( BST_OS_TIMERID_T ulTimerId, BST_VOID *pData );
BST_VOID               BST_APP_LongRRCSendPkt( BST_VOID );

extern BST_OS_MBX_T   *BST_SRV_GetSysMsgHandle( BST_VOID );

/******************************************************************************
   5 ȫ�ֱ�������
******************************************************************************/
BST_APP_LONGRRC_INFO_STRU   g_stLongRRCInfo       = {BST_INVALID_FD, BST_INVALID_FD, BST_FALSE};

BST_UINT8                   g_cBstAppLongRRCPkt[] = {69,0,0,40,0,29,0,0,
                                                     255,6,174,212,202,96,135,183,
                                                     202,96,135,183,172,226,1,187,
                                                     139,176,22,73,38,139,193,202,
                                                     80,16,31,122,74,143,0,0};
/******************************************************************************
   6 ����ʵ��
******************************************************************************/
/*****************************************************************************
 �� �� ��  : BST_APP_LongRRCInit
 ��������  : ��ʼ������RRC����״̬ģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2015��10��24��
      ��    ��   : w00346326
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_APP_LongRRCInit( BST_VOID )
{
    BST_RLS_LOG( "BST_APP_LongRRCInit: enter");
    g_stLongRRCInfo.ulIntervalId  = BST_OS_TimerCreate( BST_APP_LongRRCTimerCallback,
                                                        BST_NULL_PTR,
                                                        BST_SRV_GetSysMsgHandle() );
}

/*****************************************************************************
 �� �� ��  : BST_APP_LongRRCSetNetParm
 ��������  : �����������
 �������  : BST_UINT32 ulIPv4          IPv4��ַ
             BST_BOOL bIsNetStateUp     ����״̬�Ƿ�ΪUP
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2015��10��24��
      ��    ��   : w00346326
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_APP_LongRRCSetNetParm( BST_UINT32 ulIPv4,  BST_BOOL bNetStateUp)
{

    BST_RLS_LOG2( "BST_APP_LongRRCSetNetParm: enter %d, %d" , ulIPv4, bNetStateUp);

    if ( (BST_TRUE == bNetStateUp)&&(BST_INVALID_IP_ADDR != ulIPv4) )
    {
        /* �޸�IP���ݰ���ԴIP��ַ�ֶΣ���ƫ�ư�����ʼλ��12�ֽڵ�λ�� */
        BST_OS_MEMCPY( (BST_UINT8 *)g_cBstAppLongRRCPkt + BST_APP_LONGRRC_PKT_SRC_OFFSET,
                       &ulIPv4, BST_OS_SIZEOF( ulIPv4 ) );
    }
    else
    {
        /* ����Ϊdown��״̬�£���Ҫֹͣ���� */
        if ( BST_OS_IsTimerValid(g_stLongRRCInfo.ulIntervalId) )
        {
            BST_OS_TimerStop( g_stLongRRCInfo.ulIntervalId );
        }
        /* ʣ�෢���������� */
        g_stLongRRCInfo.ulPktsLeft = 0;
    }
}

/*****************************************************************************
 �� �� ��  : BST_APP_LongRRCConfig
 ��������  : ����AP��������Ϣ����������
 �������  : BST_UINT32 ulArgS   AP�·���������Ϣ
 �������  : ��
 �� �� ֵ  : BST_NO_ERROR_MSG   ���óɹ�
             others             ����ʧ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2015��10��24��
      ��    ��   : w00346326
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_LongRRCConfig( BST_UINT32 ulSustainS )
{
    BST_RLS_LOG1( "BST_APP_LongRRCConfig: enter %d", ulSustainS );

    /* �Ƿ���������ֱ�ӷ��� */
    if ( BST_APP_LONGRRC_INVALID_SUSTAIN_S == ulSustainS )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }

    if ( ulSustainS > BST_APP_LONGRRC_SUSTAIN_MAX_S )
    {
        ulSustainS             = BST_APP_LONGRRC_SUSTAIN_MAX_S;
    }

    /* ʣ�෢������             = ���÷�����ʱ�� / ������� */
    g_stLongRRCInfo.ulPktsLeft = ulSustainS / BST_APP_LONGRRC_INTERVAL_S;

    /* ��ֹͣԭ�ȵ�Interval��ʱ�� */
    if ( BST_OS_IsTimerValid(g_stLongRRCInfo.ulIntervalId) )
    {
        BST_OS_TimerStop( g_stLongRRCInfo.ulIntervalId );
    }

    /* ��ʼ�������� */
    BST_RLS_LOG( "BST_APP_LongRRCConfig: start send packets" );
    BST_APP_LongRRCSendPkt();

    /* ����Interval��ʱ�� */
    BST_OS_TimerStart( g_stLongRRCInfo.ulIntervalId, BST_APP_LONGRRC_INTERVAL_S * BST_OS_MS_IN_S );

    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 �� �� ��  : BST_APP_LongRRCTimerCallback
 ��������  : ��ʱ����ʱ�ص�����
 �������  : BST_OS_TIMERID_T ulTimerId         ��ʱ��ID
             BST_VOID *pData                    ��ʱ������������ָ��
 �������  : ��
 �� �� ֵ  : BST_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2015��10��24��
      ��    ��   : w00346326
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_APP_LongRRCTimerCallback( BST_OS_TIMERID_T ulTimerId, BST_VOID *pData )
{
    if ( ulTimerId != g_stLongRRCInfo.ulIntervalId )
    {
        BST_RLS_LOG1( "BST_APP_LongRRCTimerCallback: invalid timer id %d", ulTimerId );
        return;
    }

    /* �������ʣ�෢������,����տڷ������ݰ�,����������Interval��ʱ�� */
    if ( 0 != g_stLongRRCInfo.ulPktsLeft )
    {
        g_stLongRRCInfo.ulPktsLeft--;
        BST_APP_LongRRCSendPkt();
        BST_OS_TimerStart( g_stLongRRCInfo.ulIntervalId, BST_APP_LONGRRC_INTERVAL_S * BST_OS_MS_IN_S );
    }
}

/*****************************************************************************
 �� �� ��  : BST_APP_LongRRCSendPkt
 ��������  : ��տڷ���IP���ݰ�
 �������  : BST_VOID
 �������  : ��
 �� �� ֵ  : BST_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2015��10��24��
      ��    ��   : w00346326
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_APP_LongRRCSendPkt( BST_VOID )
{
    BST_DRV_IP_DATA_STRU                stIPData;
    BST_DRV_STRU                       *pNetDriver;

    stIPData.pucData                    = g_cBstAppLongRRCPkt;
    stIPData.ucDataType                 = BST_IP_BSTT_DATA;

    /* ���������ӿڷ��� */
    pNetDriver = BST_DRV_NetGetDvcHandle();
    if ( BST_NULL_PTR == pNetDriver->pfWrite )
    {
        BST_RLS_LOG( "BST_APP_LongRRCSendPkt: BST_DRV_NetGetDvcHandle()->pfWrite NULL " );
        return;
    }

    pNetDriver->pfWrite( BST_OS_SIZEOF(g_cBstAppLongRRCPkt), (BST_UINT8 *)&stIPData );

    BST_RLS_LOG1( "BST_APP_LongRRCSendPkt: ok. %d", g_stLongRRCInfo.ulPktsLeft );
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
