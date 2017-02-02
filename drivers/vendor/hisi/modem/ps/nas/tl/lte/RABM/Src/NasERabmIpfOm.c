/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasERabmIpfOm.c
  �� �� ��   : ����
  ��    ��   : L62099
  ��������   : 2011��3��23��
  ����޸�   :
  ��������   : IPFģ���OM�����ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��3��23��
    ��    ��   : L62099
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmPublic.h"
#include  "NasERabmIpfOm.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMIPFOM_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMIPFOM_C
/*lint +e767*/


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
NAS_ERABM_IPF_STATICS_INFO g_stNasERabmIpfOmInfo = {0};

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_ERABM_IpfOmInit
 ��������  : NAS RABM IPF OM���ݳ�ʼ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��23��
    ��    ��   : L62099
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_ERABM_IpfOmInit( VOS_VOID )
{
    PS_MEM_SET(NAS_ERABM_IPF_OM_INFO_PTR(), 0x0, sizeof(NAS_ERABM_IPF_STATICS_INFO));
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_ERABM_IpfDebug
 ��������  : ��ӡRABM IPFͳ����Ϣ������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��12��
    ��    ��   : L62099
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_ERABM_IpfDebug()
{
    (VOS_VOID)vos_printf("\n------------NAS RABM IPF STATICS-----------\n");
    (VOS_VOID)vos_printf("\nNAS ERABM UL RCV PACKET NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_UL_RCV_NUM());
    (VOS_VOID)vos_printf("\nNAS ERABM UL RCV PACKET BYTES: \t\t\t%d",NAS_ERABM_IPF_OM_GET_UL_RCV_BYTES());
    (VOS_VOID)vos_printf("\nNAS ERABM UL RCV PACKET ERR NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_UL_ERR_CNT());
    (VOS_VOID)vos_printf("\nNAS ERABM UL RCV FRAGMENT PACKET NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_UL_FRAG_CNT());
    (VOS_VOID)vos_printf("\nNAS ERABM UL DISCARD PACKET NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_UL_DISCARD_CNT());
    (VOS_VOID)vos_printf("\nNAS ERABM UL PRCS PACKET NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_UL_PRCS_BYTES());
    (VOS_VOID)vos_printf("\n");
    (VOS_VOID)vos_printf("\nNAS ERABM DL RCV PACKET NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_DL_RCV_NUM());
    (VOS_VOID)vos_printf("\nNAS ERABM DL RCV PACKET BYTES: \t\t\t%d",NAS_ERABM_IPF_OM_GET_DL_RCV_BYTES());
    (VOS_VOID)vos_printf("\nNAS ERABM DL RCV PACKET ERR NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_DL_ERR_CNT());
    (VOS_VOID)vos_printf("\nNAS ERABM DL RCV FRAGMENT PACKET NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_DL_FRAG_CNT());
    (VOS_VOID)vos_printf("\nNAS ERABM DL DISCARD PACKET NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_DL_DISCARD_CNT());
    (VOS_VOID)vos_printf("\nNAS ERABM DL PRCS PACKET NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_DL_PRCS_BYTES());
    (VOS_VOID)vos_printf("\n");
    (VOS_VOID)vos_printf("\nNAS ERABM DL NON USER DATA NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_DL_NON_USRDATA_CNT());
    (VOS_VOID)vos_printf("\nNAS ERABM DL USER DATA NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_DL_USRDATA_CNT());
    (VOS_VOID)vos_printf("\nNAS ERABM UL FILTER ERR NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_UL_FILTER_ERR_CNT());
    (VOS_VOID)vos_printf("\nNAS ERABM DL DATA ERR NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_DL_DATA_ERR_CNT());
    (VOS_VOID)vos_printf("\nNAS ERABM IP FILTER FULL NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_FILTER_FULL_CNT());
    (VOS_VOID)vos_printf("\n");
    (VOS_VOID)vos_printf("\nNAS ERABM IPV4 FRAGMENT PACKE NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_PACK_NUM());
    (VOS_VOID)vos_printf("\nNAS ERABM IPV4 NON HEADER FRAGMENT PACKE NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_NON_HEADER_PACK_NUM());
    (VOS_VOID)vos_printf("\nNAS ERABM IPV4 NON HEADER FRAGMENT FIND DEFT FAIL PACKE NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_NON_HEADER_FIND_DEFT_FAIL_PACK_NUM());
    (VOS_VOID)vos_printf("\nNAS ERABM IPV4 HEADER FRAGMENT PACKE NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_HEADER_PACK_NUM());
    (VOS_VOID)vos_printf("\nNAS ERABM IPV4 HEADER FRAGMENT NO UPPER LAYER PACKE NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_HEADER_NO_UPLAYER_PACK_NUM());
    (VOS_VOID)vos_printf("\nNAS ERABM IPV4 DISCARD FRAGMENT PACKE NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_RCV_UL_DISCARD_IPV4_PACK_NUM());
    (VOS_VOID)vos_printf("\n");
    (VOS_VOID)vos_printf("\nNAS ERABM IPV6 FRAGMENT PACKE NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_RCV_UL_IPV6_PACK_NUM());
    (VOS_VOID)vos_printf("\nNAS ERABM IPV6 DISCARD FRAGMENT PACKE NUM: \t\t\t%d",NAS_ERABM_IPF_OM_GET_RCV_UL_DISCARD_IPV6_PACK_NUM());
    (VOS_VOID)vos_printf("\n-------------------END---------------------\n");
}

#ifdef __cplusplus
    #if __cplusplus
         }
    #endif
#endif



