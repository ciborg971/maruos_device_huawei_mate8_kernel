/*************************************************************************
 *
 *              Copyright 2007, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              arith_ip.h
 *
 *  Project Code: VISP1.6
 *   Module Name: CBB
 *  Date Created: 2007-07-30
 *        Author: mafeng 59090
 *   Description: �ṩarith cbbģ����Ҫͷ�ļ��İ���
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2007-07-11      mafeng 59090    Create
 *
 ************************************************************************/
#ifndef _ARITH_IP_H_
#define _ARITH_IP_H_

#ifdef __cplusplus
extern "C" {
#endif

struct tagMBuf;

/*
#ifndef VOS_UINT32
#define VOS_UINT32     unsigned long
#endif
*/
#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif

#define MIN_IP_ADDR_CHAR_NUM   7    /* 1.1.1.1 is the lest char num = 7 */
#define MAX_IP_ADDR_CHAR_NUM   15    /*255.255.255.255 is the largest num = 15 */

#ifndef INADDR_ANY
#define INADDR_ANY  (VOS_UINT32)0x00000000L
#endif

#ifndef INADDR_BROADCAST
#define INADDR_BROADCAST    (VOS_UINT32)0xffffffffL /* must be masked */
#endif

#ifndef VRP_IN_CLASSA
#define VRP_IN_CLASSA(i)        (0 == ((long)(i) & 0x80000000L))
#endif

#ifndef VRP_IN_CLASSA_HOST
#define VRP_IN_CLASSA_HOST      0x00ffffffL
#endif

#ifndef VRP_IN_CLASSB
#define VRP_IN_CLASSB(i)        (0x80000000L == ((long)(i) & 0xc0000000L))
#endif

#ifndef VRP_IN_CLASSB_HOST
#define VRP_IN_CLASSB_HOST      0x0000ffffL
#endif

#ifndef VRP_IN_CLASSC
#define VRP_IN_CLASSC(i)        (0xc0000000L == ((long)(i) & 0xe0000000L))
#endif

#ifndef VRP_IN_CLASSC_HOST
#define VRP_IN_CLASSC_HOST      0x000000ffL
#endif

#ifndef ADDCARRY
#define ADDCARRY(x)  (x > 65535L ? x -= 65535L : x)
#endif

#ifndef REDUCE
#define REDUCE \
{ \
    unLUtil.l = lSum;\
    lSum = unLUtil.s[0] + unLUtil.s[1]; \
    ADDCARRY(lSum); \
}
#endif

#ifndef InetAddr
ULONG vrp_InetAddr(CHAR *);
#define InetAddr(a)   vrp_InetAddr(a)
#endif

extern ULONG VOS_strlen(const CHAR *);
extern VOS_INT32  VOS_atol( const VOS_CHAR * pcStr, VOS_INT32 * pnVal );
/* End added */


/*******************************************************************************
*    Func Name: IP_IsInvalidAddr
*  Description: ��Ϊ��ַ�Ϸ����жϵĹ�������
*               �Ƿ���ַ��: ȫ���㲥��0.X.X.X ��D��E���ַ
*        Input: ULONG ulIpAddr: ��ַ(������)
*       Output: 
*       Return: 0: �Ϸ�   1: �Ƿ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-11   mafeng 59090            Create
*
*******************************************************************************/
ULONG IP_IsInvalidAddr(ULONG ulIpAddr);
/*******************************************************************************
*    Func Name: InetAddr
*  Description:�����ʮ������ʽ�ĵ�ַת��Ϊ�����ֽ���Ķ�������ʽ 
*        Input: CHAR *pIpChar:���ʮ���Ƶ�ַ�ַ���
*       Output: 
*       Return: �ɹ�:ת��֮��ĵ�ַ ʧ��:���ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-11-10   wangtao(60012929)       Create
*
*******************************************************************************/
ULONG InetAddr(CHAR *pIpChar);
/*******************************************************************************
*    Func Name: IP_MaskBitLen
*  Description: ��ȡ���볤��
*        Input: ULONG ulMask: ����(������)
*       Output: 
*       Return: 0-32 ���볤��,255,���벻����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-11   mafeng 59090            Create
*
*******************************************************************************/
USHORT IP_MaskBitLen(ULONG ulMask);
/*******************************************************************************
*    Func Name: Ip_Fast_Cksum
*  Description: Checksum routine for Internet Protocol family headers (Portable Version).
*               This routine is very heavily used in the network
*               code and should be modified for each CPU to be as fast as possible.    
*        Input: USHORT * pusWord: IP�ײ�ָ��
*       Output: 
*       Return: IP�ײ�У���
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-11   mafeng 59090            Create
*
*******************************************************************************/
USHORT Ip_Fast_Cksum(USHORT * pusWord);
/*******************************************************************************
*    Func Name: IN_Cksum
*  Description: Checksum routine for Internet Protocol family headers    
*        Input: MBUF_S *pstMBuf: IP����
*               LONG lLen:       IP�ײ�����
*       Output: 
*       Return: IP�ײ�У���
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-11   mafeng 59090            Create
*
*******************************************************************************/
USHORT IN_Cksum(MBUF_S* pstMbuf, LONG lLen);

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of _ARITH_IP_H_ */

