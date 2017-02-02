/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasAirMsgHdr.h
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2008��2��19��
  ����޸�   : 2008��2��19��
  ��������   : ����NAS�տ���Ϣ�Ĺ���ͷ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��2��19��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __NASAIRMSGHDR_H__
#define __NASAIRMSGHDR_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"


#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/
/* PD���� (24.007 11.2.3.1.1) */
#define  NAS_PD_GCC                     0x00
#define  NAS_PD_BCC                     0x01
#define  NAS_PD_CC                      0x03
#define  NAS_PD_GTTP                    0x04
#define  NAS_PD_MM                      0x05
#define  NAS_PD_RR                      0x06
#define  NAS_PD_GMM                     0x08
#define  NAS_PD_SMS                     0x09
#define  NAS_PD_SM                      0x0A
#define  NAS_PD_SS                      0x0B
#define  NAS_PD_LS                      0x0C

/* TI flag ���� (24.007 11.2.3.1.3) */
#define  NAS_TI_FLAG_FROM_ORIGINATOR    1
#define  NAS_TI_FLAG_TO_ORIGINATOR      0

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/
/*
   NAS�տ���Ϣͷ��
   ����Ҫʹ��ͳһ����뷽ʽ���б�����NAS��Ϣ�ṹ�����������ͷ��
*/
typedef struct
{
   VOS_UINT8                            bit4PD              :4;
   VOS_UINT8                            bit4TI              :4;
   VOS_UINT8                            ucMsgType;
}NAS_AIR_MSG_HDR_STRU;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __NASAIRMSGHDR_H__ */

