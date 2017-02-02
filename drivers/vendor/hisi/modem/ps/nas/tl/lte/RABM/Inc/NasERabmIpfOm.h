/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasERabmIpfOm.h
  �� �� ��   : ����
  ��    ��   : L62099
  ��������   : 2011��3��23��
  ����޸�   :
  ��������   : NAS  RABM IPF��OM����ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��3��23��
    ��    ��   : L62099
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __NASRABMIPFOM_H__
#define __NASRABMIPFOM_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasERabmPublic.h"

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
#define NAS_ERABM_IPF_OM_INFO_PTR()          (&g_stNasERabmIpfOmInfo)

/* ���������յ���IP������ */
#define NAS_ERABM_IPF_OM_ADD_UL_RCV_NUM()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlRcvDataCnt += 1)

#define NAS_ERABM_IPF_OM_GET_UL_RCV_NUM()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlRcvDataCnt)

/* ���������յ����ֽ��� */
#define NAS_ERABM_IPF_OM_ADD_UL_RCV_BYTES(bytes)\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlRcvDataBytes += (bytes))

#define NAS_ERABM_IPF_OM_GET_UL_RCV_BYTES()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlRcvDataBytes)

/* ��������IPF���˴����� */
#define NAS_ERABM_IPF_OM_ADD_UL_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlErrorCnt += 1)

#define NAS_ERABM_IPF_OM_GET_UL_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlErrorCnt)

/* ���������յ���IP��Ƭ�� */
#define NAS_ERABM_IPF_OM_ADD_UL_FRAG_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlFragCnt += 1)

#define NAS_ERABM_IPF_OM_GET_UL_FRAG_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlFragCnt)

/* �������ж�����IP������ */
#define NAS_ERABM_IPF_OM_ADD_UL_DISCARD_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlDiscardCnt += 1)

#define NAS_ERABM_IPF_OM_GET_UL_DISCARD_CNT()\
                    (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlDiscardCnt)

/* ��������IPF�Ѵ�����ֽ��� */
#define NAS_ERABM_IPF_OM_ADD_UL_PRCS_BYTES(bytes)\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlProcBytes += (bytes))

#define NAS_ERABM_IPF_OM_GET_UL_PRCS_BYTES()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlProcBytes)

/* ���������յ���IP������ */
#define NAS_ERABM_IPF_OM_ADD_DL_RCV_NUM()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlRcvDataCnt += 1)

#define NAS_ERABM_IPF_OM_GET_DL_RCV_NUM()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlRcvDataCnt)

/* ���������յ����ֽ��� */
#define NAS_ERABM_IPF_OM_ADD_DL_RCV_BYTES(bytes)\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlRcvDataBytes += (bytes))

#define NAS_ERABM_IPF_OM_GET_DL_RCV_BYTES()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlRcvDataBytes)

/* ��������IPF���˴����� */
#define NAS_ERABM_IPF_OM_ADD_DL_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlErrorCnt += 1)

#define NAS_ERABM_IPF_OM_GET_DL_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlErrorCnt)

/* ���������յ���IP��Ƭ�� */
#define NAS_ERABM_IPF_OM_ADD_DL_FRAG_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlFragCnt += 1)

#define NAS_ERABM_IPF_OM_GET_DL_FRAG_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlFragCnt)

/* ��������IPF �����İ����� */
#define NAS_ERABM_IPF_OM_ADD_DL_DISCARD_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlDiscardCnt += 1)

#define NAS_ERABM_IPF_OM_GET_DL_DISCARD_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlDiscardCnt)

/* ��������IPF�������ֽ��� */
#define NAS_ERABM_IPF_OM_ADD_DL_PRCS_BYTES(bytes)\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlProcBytes += (bytes))

#define NAS_ERABM_IPF_OM_GET_DL_PRCS_BYTES()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlProcBytes)

/* �������з��û�������IP������ */
#define NAS_ERABM_IPF_OM_ADD_DL_NON_USRDATA_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulDlNonUsrDataCnt += 1)

#define NAS_ERABM_IPF_OM_GET_DL_NON_USRDATA_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulDlNonUsrDataCnt)

/* ���������û�������IP������ */
#define NAS_ERABM_IPF_OM_ADD_DL_USRDATA_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulDlUsrDataCnt += 1)

#define NAS_ERABM_IPF_OM_GET_DL_USRDATA_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulDlUsrDataCnt)

/* ���в���TFT Filter���� */
#define NAS_ERABM_IPF_OM_ADD_UL_FILTER_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfTftFilterErr += 1)

#define NAS_ERABM_IPF_OM_GET_UL_FILTER_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfTftFilterErr)

/* ����������ӵ�IPF������� */
#define NAS_ERABM_IPF_OM_ADD_DL_DATA_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlFilterErr += 1)

#define NAS_ERABM_IPF_OM_GET_DL_DATA_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlFilterErr)

/* ����IPF FIlter��������� */
#define NAS_ERABM_IPF_OM_ADD_FILTER_FULL_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfFilterFull += 1)

#define NAS_ERABM_IPF_OM_GET_FILTER_FULL_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfFilterFull)


/* ��ȡ���з�Ƭ���ݰ���������Ϣ��ַ */
#define NAS_ERABM_IPF_OM_GET_UL_TRANS_INFO_ADDR()\
                (&((NAS_ERABM_IPF_OM_INFO_PTR())->stUlIpFfragmentTransInfo))

/* ��ȡ����IPV4��Ƭ���ݰ���������Ϣ��ַ */
#define NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR()\
                (&((NAS_ERABM_IPF_OM_GET_UL_TRANS_INFO_ADDR())->stUlIpv4FragmentTransInfo))

/* ��ȡ����IPV6��Ƭ���ݰ���������Ϣ��ַ */
#define NAS_ERABM_IPF_OM_GET_UL_IPV6_TRANS_INFO_ADDR()\
                (&((NAS_ERABM_IPF_OM_GET_UL_TRANS_INFO_ADDR())->stUlIpv6FragmentTransInfo))


/* ��ȡ�����ܵķ�Ƭ���ݰ���Ŀ������IPV4 �� IPV6 ��Ƭ�� */


/* ��ȡ���� IPV4 ��Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4FragmentPackageNum)

/* ��ȡ���� IPV4 ͷ����Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_HEADER_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4HeaderFragmentPackageNum)

/* ��ȡ���ж��� IPV4 ��Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_DISCARD_IPV4_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4DiscardFragmentPackageNum)

/* ��ȡ���� IPV4 ��Ƭ���з�ͷ����Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_NON_HEADER_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4NonHeaderFragmentPackageNum)

/* ��ȡ���� IPV4 ��Ƭ���з�ͷ����Ƭ����ȱʡ����ʧ�ܰ���Ŀ */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_NON_HEADER_FIND_DEFT_FAIL_PACK_NUM()\
                    ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4NonHeaderFragmentFindDeftFailedPackageNum)


/* ��ȡ���� IPV4 ͷ����Ƭƥ����Ϣ�������ķ�Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_HEADER_NO_UPLAYER_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4HeaderFragmentNoUpperLayerPackageNum)

/* �������� IPV4 ��Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4FragmentPackageNum ++)

/* �������ж��� IPV4 ��Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_DISCARD_IPV4_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4DiscardFragmentPackageNum ++)

/* �������� IPV4 ͷ����Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_HEADER_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4HeaderFragmentPackageNum ++)

/* �������� IPV4 ��Ƭ���з�ͷ����Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_NON_HEADER_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4NonHeaderFragmentPackageNum ++)

/* �������� IPV4 ��Ƭ���з�ͷ����Ƭ����ȱʡ����ʧ�ܰ���Ŀ */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_NON_HEADER_FIND_DEFT_FAIL_PACK_NUM()\
                    ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4NonHeaderFragmentFindDeftFailedPackageNum ++)


/* �������� IPV4 ͷ����Ƭƥ����Ϣ�������ķ�Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_HEADER_NO_UPLAYER_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4HeaderFragmentNoUpperLayerPackageNum ++)

/* ��ȡ���� IPV6 ��Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_IPV6_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV6_TRANS_INFO_ADDR())->ulIpv6FragmentPackageNum)

/* ��ȡ���ж��� IPV6 ��Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_DISCARD_IPV6_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV6_TRANS_INFO_ADDR())->ulIpv6DiscardFragmentPackageNum)

/* �������� IPV6 ��Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV6_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV6_TRANS_INFO_ADDR())->ulIpv6FragmentPackageNum ++)

/* �������ж��� IPV6 ��Ƭ����Ŀ */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_DISCARD_IPV6_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV6_TRANS_INFO_ADDR())->ulIpv6DiscardFragmentPackageNum ++)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : NAS_ERABM_UL_IPV4_IP_FRAGMENT_DATA_TRANS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����IPV4��Ƭ��������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIpv4FragmentPackageNum;                           /* IPV4��Ƭ���� */
    VOS_UINT32                          ulIpv4DiscardFragmentPackageNum;                    /* IPV4������Ƭ���� */
    VOS_UINT32                          ulIpv4HeaderFragmentPackageNum;                     /* IPV4ͷ����Ƭ���� */
    VOS_UINT32                          ulIpv4NonHeaderFragmentPackageNum;                  /* IPV4��ͷ����Ƭ���� */
    VOS_UINT32                          ulIpv4NonHeaderFragmentFindDeftFailedPackageNum;    /* IPV4��ͷ����Ƭ������ȱʡ����ʧ�ܰ��� */
    VOS_UINT32                          ulIpv4HeaderFragmentNoUpperLayerPackageNum;         /* IPV4ͷ����Ƭƥ����Ϣ�������ķ�Ƭ���� */
}NAS_ERABM_UL_IPV4_IP_FRAGMENT_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERABM_UL_IPV6_IP_FRAGMENT_DATA_TRANS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����IPV6��Ƭ��������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIpv6FragmentPackageNum;                        /* IPV6��Ƭ���� */
    VOS_UINT32                          ulIpv6DiscardFragmentPackageNum;                  /* IPV6������Ƭ���� */
}NAS_ERABM_UL_IPV6_IP_FRAGMENT_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERABM_UL_IP_FRAGMENT_DATA_TRANS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���з�Ƭ��������Ϣ
*****************************************************************************/
typedef struct
{
    /* �ܵķ�Ƭ���ݰ��� IPV4 + IPV6��Ƭ�� */
    /*VOS_UINT32                                              ulIpFragmentPackageNum;
 */

    NAS_ERABM_UL_IPV4_IP_FRAGMENT_DATA_TRANS_INFO_STRU      stUlIpv4FragmentTransInfo;
    NAS_ERABM_UL_IPV6_IP_FRAGMENT_DATA_TRANS_INFO_STRU      stUlIpv6FragmentTransInfo;
}NAS_ERABM_UL_IP_FRAGMENT_DATA_TRANS_INFO_STRU;
/*****************************************************************************
 �ṹ��    : NAS_ERABM_IPF_STATICS_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPF OM ͳ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulIpfUlRcvDataCnt;          /*�����յ������ݸ���
 */
    VOS_UINT32              ulIpfUlRcvDataBytes;        /*�����յ����ֽ���
 */
    VOS_UINT32              ulIpfUlErrorCnt;            /*����IPF�����������
 */
    VOS_UINT32              ulIpfUlFragCnt;             /*�����յ�IP��Ƭ����
 */
    VOS_UINT32              ulIpfUlDiscardCnt;          /*���ж������ݰ�����
 */
    VOS_UINT32              ulIpfUlProcBytes;           /*����IPF������ֽ���,������
 */

    VOS_UINT32              ulIpfDlRcvDataCnt;          /*�����յ������ݰ�����
 */
    VOS_UINT32              ulIpfDlRcvDataBytes;        /*�����յ������ݰ��ֽ���
 */
    VOS_UINT32              ulIpfDlErrorCnt;            /*����IPF�����������
 */
    VOS_UINT32              ulIpfDlFragCnt;             /*�����յ�IP��Ƭ����
 */
    VOS_UINT32              ulIpfDlDiscardCnt;          /*���ж������ݰ���ʽ
 */
    VOS_UINT32              ulIpfDlProcBytes;           /*����IPF������ֽ���
 */

    VOS_UINT32              ulDlNonUsrDataCnt;          /*���д�����û����ݸ���
 */
    VOS_UINT32              ulDlUsrDataCnt;             /*���д����û����ݸ���
 */

    VOS_UINT32              ulIpfTftFilterErr;          /*����TFT����ת������ͳ��
 */
    VOS_UINT32              ulIpfDlFilterErr;           /*�������ݷ��ʹ���ͳ��
 */

    VOS_UINT32              ulIpfFilterFull;          /*����FILTERͳ��
 */
    NAS_ERABM_UL_IP_FRAGMENT_DATA_TRANS_INFO_STRU stUlIpFfragmentTransInfo; /* ���з�Ƭ��������Ϣ */
}NAS_ERABM_IPF_STATICS_INFO;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_ERABM_IPF_STATICS_INFO g_stNasERabmIpfOmInfo;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern  VOS_VOID NAS_ERABM_IpfOmInit( VOS_VOID );


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

#endif

