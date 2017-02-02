/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_icmp_api.h
*
*  Project Code: VISPV1R8C02
*   Module Name: ICMP
*  Date Created: 2009-9-11
*        Author: zengshaoyang(62531)/zhangchunyu(62474) 
*   Description: ������ICMP����API�ṹ����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-9-11    zengshaoyang(62531)/zhangchunyu(62474)            Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_ICMP_API_H_
#define _SFE_ICMP_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ������BFDģ������� */
enum enumSfeIcmpErrCode
{ 
    SFE_ICMP_OK = SFE_OK,                         /* �����ɹ� */
    SFE_ICMP_ERR_BEGIN = SFE_ICMP_BEGIN_RET_CODE, /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_ICMP_MALLOC_SWITCH_ERR,                   /* 1 ����ICMP���Կ����ڴ�ʧ�� */
    SFE_ICMP_SETSWITCH_ERR,                       /* 2 ���÷���ICMP���Կ��طǷ� */
    SFE_ICMP_SETSWITCH_NULL_POINT,                /* 3 ����ICMP����ָ��Ϊ�� */
    SFE_ICMP_GETSWITCH_NULL_POINT,                /* 4 ��ȡICMP����ָ��Ϊ�� */
};

#ifdef  __cplusplus
}
#endif

#endif



