/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         iphc_def.h
 *
 *  Project Code: VISP
 *   Module Name: IPHC
 *  Date Created: 2002/06/25
 *        Author: wangyue
 *   Description: ��ͷ�ļ�����iphcģ��ĺ궨�壻   
 *
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2006-03-30      xiehuaguo       Adjust for D00647
 *
 ************************************************************************/
 
#ifndef _IPHC_DEF_H_
#define _IPHC_DEF_H_


#ifdef  __cplusplus
extern "C"{
#endif

/* Added by Sun Mo 44939 2005-10-04 */
/* ����ѹ�����Ͷ��� */
#define IPHC_COMPRESS_ALL           0   /* ��TCP/non-TCP���Ķ�ѹ�� */
#define IPHC_ONLY_COMPRESS_NON_TCP  1   /* ��ѹ��no-TCP���� */
#define IPHC_ONLY_COMPRESS_TCP      2   /* ��ѹ��TCP����*/
#define IPHC_NOT_COMPRESS_ALL       3   /* ��ֹѹ��TCP��non-TCP���� */

/* �������� */
#define IPHC_IP_TCP_PACKETTYPE      1   /* IP+TCP���� */
#define IPHC_IP_UDP_PACKETTYPE      2   /* IP+UDP���� */
#define IPHC_IP_UDP_RTP_PACKETTYPE  3   /* IP+UDP+RTP���� */

/* TCP_SPACE��������*/
#define IPHC_DEF_TCP_SPACE       15      /* Ĭ��ֵ */
#define IPHC_MIN_TCP_SPACE       3       /* ���� */
#define IPHC_MAX_TCP_SPACE       255     /* ���� */

/* NON_TCP_SPACE�������� */
#define IPHC_DEF_NON_TCP_SPACE   15      /* Ĭ��ֵ */
#define IPHC_MIN_NON_TCP_SPACE   3       /* ���� */
#define IPHC_MAX_NON_TCP_SPACE   999   /* ���� */

#define IPHC_MAX_NON_TCP_SPACE_NP 65535  /*IPHC ��NPģʽ�µ�����*/

/* F_MAX_PERIOD�������� */
#define IPHC_DEF_F_MAX_PERIOD    256     /* Ĭ��ֵ */
#define IPHC_MIN_F_MAX_PERIOD    1       /* ���� */
#define IPHC_MAX_F_MAX_PERIOD    65535   /* ���� */

/* F_MAX_TIME�������� */
#define IPHC_DEF_F_MAX_TIME      5       /* Ĭ��ֵ */
#define IPHC_MIN_F_MAX_TIME      1       /* ���� */
#define IPHC_MAX_F_MAX_TIME      255     /* ���� */

/* MAX_HEADER�������� */
#define IPHC_DEF_MAX_HEADER      168     /* Ĭ��ֵ */
#define IPHC_MIN_MAX_HEADER      60      /* ���� */
#define IPHC_MAX_MAX_HEADER      168     /* ���� */

/* Э��(Enhanced) RTP Compression��ѡ������ */
#define IPHC_NONE_RTP_COMPRESSION       0   /* ��Э��RTP Compression��Enhanced RTP Compression��ѡ�� */
#define IPHC_RTP_COMPRESSION            1   /* Э��RTP Compression��ѡ�� */
#define IPHC_ENHANCED_RTP_COMPRESSION   2   /* Э��Enhanced RTP Compression��ѡ�� */
/* End of add of Sun Mo 44939 2005-09-22 */

/*��ѡ�����Ͷ���*/
#define IPHC_ONLY_COMPRESS_PART         3   /*��ѹ��TCP/��TCP������ѡ��*/

/*��ѡ��ȶ���*/
#define IPHC_LEN_RTP_COMPRESSION     2   /*RTP Compression��ѡ��*/
#define IPHC_LEN_ENHANCED_RTP_COMPRESSION  2   /*Enhanced RTP Compression��ѡ��*/
#define IPHC_LEN_ONLY_COMPRESS_PART       3   /*��ѹ��TCP/��TCP������ѡ��*/

/*���������Ͷ���*/
#define IPHC_CONTEXT_TYPE_ALL       0   /*TCP���ĸ�ʽ�ͷ�TCP���ĸ�ʽ*/
#define IPHC_CONTEXT_TYPE_TCP       1   /*TCP���ĸ�ʽ*/
#define IPHC_CONTEXT_TYPE_NONTCP    2   /*��TCP���ĸ�ʽ*/

/*������λ�ö���*/
#define IPHC_CONTEXT_SIDE_ALL       0   /*ѹ���ͽ�ѹ��������*/
#define IPHC_CONTEXT_SIDE_COMP      1   /*ѹ����������*/
#define IPHC_CONTEXT_SIDE_DECOMP    2   /*��ѹ��������*/

/********************* IPHCģ�����SID��غ�(BEGIN)********************/
#define SID_COMP_IPHC_CONTEXT_S         1
#define SID_COMP_IPHC_MBUF_S            2 
#define SID_COMP_IPHC_COMP_CONTEXT_S    3       
#define SID_COMP_IPHC_DECOMP_CONTEXT_S  4    
/********************* IPHCģ�����SID��غ�(END)**********************/
#ifndef MIN
#define MIN(a, b)       ((a)>(b) ? (b):(a)) 
#endif

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif

