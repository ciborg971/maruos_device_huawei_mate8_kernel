/*************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              acl6_def.h
 *
 *  Project Code: VISP1.8
 *   Module Name: ACL6
 *  Date Created: 
 *        Author: 
 *   Description: �궨��
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *
 ************************************************************************/
#ifndef _ACL6_DEF_H_
#define _ACL6_DEF_H_

#ifdef  __cplusplus
extern "C" 
{
#endif

#include "acl6/include/acl6_cbb_api.h"


/**********************************************************
*   ���������غ궨��
***********************************************************/
/* ��������IDȡֵ��Χ */
#define ACL6_MIN_TYPEID  1
#define ACL6_MAX_TYPEID  3

/**********************************************************
*   �������غ궨��
***********************************************************/
/* ������������ܺ� */
#define ACL6_MAX_GROUPNUM_SUM  9999

/* ȱʡ�������͵Ĺ��������ȱʡֵ */
#define ACL6_BAS_DEFAULT_MIN     2000
#define ACL6_BAS_DEFAULT_MAX     2999

#define ACL6_ADV_DEFAULT_MIN     3000
#define ACL6_ADV_DEFAULT_MAX     3999

#define ACL6_IF_DEFAULT_MIN      1000
#define ACL6_IF_DEFAULT_MAX      1999

/* �����鲽����Χ */
#define ACL6_MIN_STEP    1
#define ACL6_MAX_STEP    20

/* ��Ʒ��Ҫʹ��Ĭ�ϲ���,������API�ж���һ��,ע��ú궨�������acl6_cbb_api.h�е�ACL6_DEFAULT_STEP���屣��һ�� */
/* ������Ĭ�ϲ��� */
#ifndef ACL6_DEFAULT_STEP
#define ACL6_DEFAULT_STEP 5
#endif

/**********************************************************
*   �����غ궨��
***********************************************************/
/* ȫ���������� */
#define ACL6_MAX_ALLRULE_SUM   10000

/* һ������������������ */
#define ACL6_MAX_GROUPRULE_SUM   256

/* �˿ں�ȡֵ��Χ */
#define ACL6_MIN_PORTNUM 0
#define ACL6_MAX_PORTNUM 65535

/* Э���ȡֵ��Χ */
#define ACL6_MIN_PROID    0
#define ACL6_MAX_PROID    255

/* Addr Mask Lenȡֵ��Χ */
#define ACL6_MIN_MASK_LEN 0
#define ACL6_MAX_MASK_LEN 128

/* Hop Limitȡֵ��Χ */
#define ACL6_MIN_HOPLM 0
#define ACL6_MAX_HOPLM 255

/* Traffic Classȡֵ��Χ */
#define ACL6_MIN_CLASS 0
#define ACL6_MAX_CLASS 255

/* �������Ƿ���� */
#define ACL6_GROUP_IS_EXIST(pstGroup) ((pstGroup) != NULL)

/* IP6�ײ�Next Header �ֶεĺ궨�� */
#define ACL6_HD_HOP_BY_HOP  0
#define ACL6_HD_DST_HD      60
#define ACL6_HD_ROUTE_HD    43
#define ACL6_HD_FRAGMENT    44    /* IPv6 Fragmentation header */
#define ACL6_HD_AH          51
#define ACL6_HD_ESP         50
#define ACL6_HD_NONE        59    /* IPv6 No next header */
#define ACL6_HD_TCP6        6
#define ACL6_HD_UDP6        17
#define ACL6_HD_ICMP6       58
#define ACL6_HD_SCTP        132

/* ICMP6 Code��ȡֵ��Χ ����Ч��ΧֵΪ:0,1,2,3,4*/
#define ACL6_MIN_ICMP6CODE  0
#define ACL6_MAX_ICMP6CODE  4

/* ICMP6 Type��ȡֵ��Χ */
#define ACL6_MIN_ICMP6TYPE  0
#define ACL6_MAX_ICMP6TYPE  255

/* Դ��Ŀ��ͨ�õ��ڲ������� */
#define ACL6_PORT_TYPE_ERR    1   /* �˿�ƥ�����ͷǷ� */
#define ACL6_PORT_RANGE_ERR   2   /* �˿ں����÷Ƿ� */


/* x must be a array that have 4 ULONG element */
#define ACL6_ADDRESS_HTON(x) \
{\
    (x)[0] = VOS_HTONL((x)[0]);\
    (x)[1] = VOS_HTONL((x)[1]);\
    (x)[2] = VOS_HTONL((x)[2]);\
    (x)[3] = VOS_HTONL((x)[3]);\
}

/* x must be a array that have 4 ULONG element */
#define ACL6_ADDRESS_NTOH(x) \
{\
    (x)[0] = VOS_NTOHL((x)[0]);\
    (x)[1] = VOS_NTOHL((x)[1]);\
    (x)[2] = VOS_NTOHL((x)[2]);\
    (x)[3] = VOS_NTOHL((x)[3]);\
}


/**********************************************************
*   ����λ��غ궨�壬�ڱ���ƥ��ʱ�ɶ�ָ���ֶβ���Ƚ�
***********************************************************/
/* ��ȡ����λ��־ */
#define ACL6_ING_SIP(ulByte)         (ACL6_SIPByte & (ulByte))
#define ACL6_ING_DIP(ulByte)         (ACL6_DIPByte & (ulByte))
#define ACL6_ING_PRO(ulByte)         (ACL6_PROByte & (ulByte))
#define ACL6_ING_HLM(ulByte)         (ACL6_HLMByte & (ulByte))
#define ACL6_ING_CLS(ulByte)         (ACL6_CLSByte & (ulByte))
#define ACL6_ING_SPORT(ulByte)       (ACL6_SPORTByte & (ulByte))
#define ACL6_ING_DPORT(ulByte)       (ACL6_DPORTByte & (ulByte))
#define ACL6_ING_VRF(ulByte)         (ACL6_VRFByte & (ulByte))


#define ACL6_IS_IPADDRANY(pAddr,lRetResult)\
{\
    CHAR szAddrZero[ACL6_IPV6_ADDR_LEN];\
    (VOID)TCPIP_Mem_Set(szAddrZero,0,ACL6_IPV6_ADDR_LEN);\
    (VOID)VOS_Mem_Cmp((CHAR *)pAddr,szAddrZero,ACL6_IPV6_ADDR_LEN,&lRetResult);\
}

#define ACL6_FILL_GROUP_OUT_INFO(pstGroup,pstGroupInfo)\
{\
    pstGroupInfo->ulTypeID = pstGroup->ulTypeID;\
    pstGroupInfo->ulGroupIndex = pstGroup->ulGroupIndex;\
    pstGroupInfo->ulMatchOrder = pstGroup->ulMatchOrder;\
    pstGroupInfo->ulStep = pstGroup->ulIndexStep;\
    if (NULL != pstGroup->pACL6Description)\
    {\
        (VOID)TCPIP_strncpy(pstGroupInfo->szDescription, ACL6_DESCRIPTIONSTR_LEN + 1, pstGroup->pACL6Description, ACL6_DESCRIPTIONSTR_LEN);\
        pstGroupInfo->szDescription[ACL6_DESCRIPTIONSTR_LEN] = 0;\
    }\
    else\
    {\
        (VOID)TCPIP_Mem_Set(pstGroupInfo->szDescription, 0, (ACL6_DESCRIPTIONSTR_LEN + 1));\
    }\
    pstGroupInfo->ulRuleNum = pstGroup->ulRuleNum;\
}

#define ACL6_SUBADDR_BUILD(pAddr,ulMaskLen,pSubAddr)\
{\
    CHAR szMask[ACL6_IPV6_ADDR_LEN];\
    UCHAR k,ucLastByte = 0xFF;\
    CHAR *pDst,*pSrc;\
    ULONG ulTemp = ACL6_IPV6_ADDR_LEN/2;\
    (VOID)TCPIP_Mem_Set((CHAR*)pSubAddr, 0,ACL6_IPV6_ADDR_LEN);\
    (VOID)TCPIP_Mem_Set(szMask, 0,ACL6_IPV6_ADDR_LEN);\
    (VOID)TCPIP_Mem_Set(szMask, ucLastByte, (ulMaskLen / ulTemp));\
    if ((ulMaskLen) % ulTemp)\
    {\
        ucLastByte = (CHAR)(ucLastByte << (ulTemp - ((ulMaskLen) % ulTemp)));\
        szMask[(ulMaskLen / ulTemp)] = ucLastByte;\
    }\
    for (k = 0; k < ACL6_IPV6_ADDR_LEN; k++)\
    {\
        pSrc = ((CHAR*)(pAddr)+k);\
        pDst = ((CHAR*)(pSubAddr)+k);\
        *pDst = (CHAR)(*pSrc & szMask[k]);\
    }\
}

#define ACL6_GET_TRAFFICCLASS(ulTclassFlow) ((VOS_NTOHL(ulTclassFlow) & 0x0ff00000)>> 20)
#define ACL6_GET_FRAGMENTOFF(usOffFlag) (VOS_NTOHS(usOffFlag) & 0xfff8)

#ifdef  __cplusplus
}
#endif
   
#endif
