/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasIeUtil.h
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2008��2��18��
  ����޸�   :
  ��������   : 
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��2��18��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __NASIEUTIL_H__
#define __NASIEUTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����                            
*****************************************************************************/
#include "vos.h"
#include "PsLib.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*
����IE���һ���ֽڵ�λ��
    pIe - ָ��IE�ṹ������ָ��
    oct - ���һ����Ч��IE�ֽ�(IE �ṹ�е��ֶ�����)
*/
#define NAS_IE_SET_LAST_OCTET_OFFSET(pIe, oct) \
    ((pIe)->LastOctOffset = (VOS_UINT8)((VOS_UINT32)&(pIe)->oct - (VOS_UINT32)&(pIe)->LastOctOffset))

/*
���ָ����IE�ֽ��Ƿ����
    pIe - ָ��IE�ṹ������ָ��
    oct - ��Ҫ�����ֽ�(IE �ṹ�е��ֶ�����)
*/
#define NAS_IE_OCTET_PRESENT(pIe, oct) \
    (((VOS_UINT32)&(pIe)->oct - (VOS_UINT32)&(pIe)->LastOctOffset <= (pIe)->LastOctOffset) ? \
     VOS_TRUE : VOS_FALSE)

/*
����IE�����ݿ�Ĵ�С��
���IE�����ݿ�(���ֽڵ�Ԫ)����д�����ݣ���Ҫ���øú�������������ݳ��ȡ�
    pIe   - ָ��IE�ṹ������ָ��
    block - ��Ҫ���õ����ݿ�(IE �ṹ�е������ֶ�����)
    size  - �������ݿ��е����ݳ���
*/
#define NAS_IE_SET_BLOCK_SIZE(pIe, block, size) \
    ((pIe)->LastOctOffset = (VOS_UINT8)((((VOS_UINT32)&(pIe)->block[0] - (VOS_UINT32)&(pIe)->LastOctOffset) + size) - 1))

/*
ȡ��IE�����ݿ�����ݳ��ȡ�
    pIe   - ָ��IE�ṹ������ָ��
    block - ��Ҫȡ�����ݳ��ȵ����ݿ�(IE �ṹ�е������ֶ�����)
*/
#define NAS_IE_GET_BLOCK_SIZE(pIe, block) \
    (((((VOS_UINT32)&(pIe)->block[0] - (VOS_UINT32)&(pIe)->LastOctOffset) - 1) <= (pIe)->LastOctOffset) ? \
     (((pIe)->LastOctOffset - ((VOS_UINT32)&(pIe)->block[0] - (VOS_UINT32)&(pIe)->LastOctOffset)) + 1) : 0)

/*
����һ��IE�ֽڵ�ֵ��
����һЩ����Ҫ��λ��ֵ��IE�ֽڣ�����ʹ�øú����������ֽڵ�ֵ��
    pIe - ָ��IE�ṹ������ָ��
    oct - ��Ҫ���õ��ֽ�(IE �ṹ�е��ֶ�����)
    val - �ֽڵ�ֵ
*/
#define NAS_IE_SET_OCTET(pIe, oct, val) \
    (*((VOS_UINT8 *)&(pIe)->oct) = (VOS_UINT8)(val))


/*
ȡ��һ��IE�ֽڵ�ֵ��
    pIe - ָ��IE�ṹ������ָ��
    oct - ��Ҫ��ȡֵ���ֽ�(IE �ṹ�е��ֶ�����)
*/
#define NAS_IE_GET_OCTET(pIe, oct) \
    (*((VOS_UINT8 *)&(pIe)->oct))

/*
����ָ����IE�����ڡ�ֻ�е�IE����Ϣ�б���Ϊ����ʱ���Żᱻ���뵽�տ���Ϣ���С�
    pIe - ָ��IE�ṹ������ָ��
*/
#define NAS_IE_SET_ABSENT(pIe)  ((pIe)->IsExist = 0)


/*
����ָ����IE���ڡ�ֻ�е�IE����Ϣ�б���Ϊ����ʱ���Żᱻ���뵽�տ���Ϣ���С�
    pIe - ָ��IE�ṹ������ָ��
*/
#define NAS_IE_SET_PRESENT(pIe)  ((pIe)->IsExist = 1)


/*
���ָ����IE�Ƿ����
    pIe - ָ��IE�ṹ������ָ��
*/
#define NAS_IE_IS_PRESENT(pIe)   (((pIe)->IsExist != 0) ? VOS_TRUE : VOS_FALSE)


/*****************************************************************************
  3 �ӿں�������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __NASIEUTIL_H__ */

