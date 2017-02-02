 /******************************************************************************
  �� �� ��   : fwd_ppp.h
  �� �� ��   : ����
  ��    ��   : zhangnan 68158
  ��������   : 2007��07��14��
  ����޸�   :
  ��������   : PPPģ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��07��14��
    ��    ��   : zhangnan 68158
    �޸�����   : �����ļ�
******************************************************************************/

#ifndef __FWD_PPP_H__
#define __FWD_PPP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "TtfDrvInterface.h"

#define FWD_YES                     0
#define FWD_LITTLE_ENDIAN           FWD_YES

/*PPPͷ��������ֵ���� */
#define PPP_PARSE_R_DATA            0       /*��ʾ���ݱ���*/
#define PPP_PARSE_R_LCP_SIG         1       /*��ʾ����*/
#define PPP_PARSE_R_LCP_ECHO_REQ    2       /*��ʾECHO request ����*/
#define PPP_PARSE_R_ASYN            3       /*�첽����*/
#define PPP_PARSE_R_OTHER_SIG       4       /*ppp��������*/
#define PPP_PARSE_R_ERR_SIG         5       /*ppp�Ƿ�����*/
#define PPP_PARSE_R_LCP_ECHO_REPLY  6       /*��ʾECHO reply ����*/
#define PPP_PARSE_R_VSCP_DATA       7       /*��ʾVSCP���ݱ���*/
#define PPP_PARSE_R_VSNP_SIG        10      /*��ʾVSCP�����*/
/*add:by xsm00201057 2012-3-1 PDSN_C6 IPV6��ֲ_pppѹ���޸�*/
#define PPP_PARSE_R_DATA_V4         11      /*ppp IPV4����*/
#define PPP_PARSE_R_DATA_V6         12      /*ppp IPV6����*/
/*end:by xsm00201057 2012-3-1 PDSN_C6 IPV6��ֲ_pppѹ���޸�*/

/*PPP��/���װ����ֵ����*/
#define PPP_R_DATA                   0       /*��ʾ���ݱ�����ת��*/
#define PPP_R_SIG_OK                1       /*��ʾ�������ͳɹ�*/
#define PPP_R_ECHO                   2       /*��ʾECHO����*/
#define PPP_R_ASYN                   3       /*�첽����*/
#define PPP_R_SIG_FAIL            4       /*��ʾ��������ʧ��*/
#define PPP_R_ERROR                 5       /*������*/
#define PPP_R_MAGIC_ERROR     6      /*magicnum������*/


/*���������Ƿ���ֵ*/
#define PPP_TO_CTRL_OK              0       /*���Ϳ�����ɹ�*/
#define PPP_TO_CTRL_FAIL            1       /*���Ϳ�����ʧ��*/

/*PPP ͷ����*/
#define PPP_H_ASYN                  0x7E    /*ͬ�첽��־*/
#define PPP_H_ACF                   0xFF03  /*��ַ������*/
#define PPP_H_PF_LCP                0xC021
#define PPP_H_PF_IPV4               0x0021
#define PPP_H_PF_IPV6               0x0057
#define PPP_H_PFC_IPV6              0x57
#define PPP_H_PFC_IPV4              0x21
#define PPP_H_LCP_ECHOREQ           0x09
#define PPP_H_LCP_ECHOREP           0x0a

#define VAS_PCI_REDIRECT_SIZE   1
#define VAS_PCI_L3STAKE_SIZE    3
#define PF_TRACK_FATAL_ERR_LEVEL        0x04
#define PF_TRACK_ERR_LEVEL              0x03
#define PF_TRACK_WARNING_LEVEL          0x02
#define PF_TRACK_INFO_LEVEL             0x01
#define PF_TRACK_INVALID_LEVEL          0

#define IPV4_VERSION 4

#define PPP_H_PF_VSNP               0x005b
#define PPP_H_PFC_VSNP              0x5b

#define PPP_FLAG_SEQ            0x7e
#define PPP_FLAG_SEQ_NO         0xffffffff

#define PPP_REBUILD_ENABLE      1
#define PPP_REBUILD_DISABLE     0

#define PPP_MAX_PKT_LEN_MULTI_2     3600
/*Mod by tianmin at 2013-3-30 for spuf ������DPI���֧�ַ�Ƭ����2240(����576��datablock)*/

#define PPP_MAX_DATA_BLOCK_LENGTH 2000 /*MBUF��������2368*/


#define FWD_PPP_FRAG_STAT_TYPE_PPP 1    /*ͳ������:һ��ԭʼ���ı���Ϊ���PPP��Ƭ*/
#define FWD_PPP_FRAG_STAT_TYPE_GRE 2    /*ͳ������:���ԭʼ���Ĵ���һ��PPP��Ƭ*/


/*�ж����к�a�Ƿ�����b֮����aû�з�ת֮ǰ��aӦ���Ǵ���b�����a��ת���Ӧ��С��b��*/
/*�˺����кܴ�ľ����ԣ�a�ĺ���ֻ����LINKTCB_S�ṹ�е�seq_late*/
#define AFollowB(a,b)           (((a) > (b)) || ((a) + 0xFFFF > (b) + 0xFFFF))

#define MAX_LINK_ITEM_NUM       (100)
#define PPP_FREELIST_SIZE       (20000)


enum FWD_PKT_TYPE_ENUM
{
    FWD_PKT_TYPE_IPV4 = 0x00,                                                   /* IPV4 */
    FWD_PKT_TYPE_IPV6 = 0x01,                                                   /* IPV6 */
    FWD_PKT_TYPE_PPP  = 0x02,
    FWD_PKT_TYPE_BUTT
};
typedef VOS_UINT8 FWD_PKT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : ICMP_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ICMP Type
*****************************************************************************/
enum ICMP_TYPE_ENUM
{
    ICMP_TYPE_ECHO_REPLY    = 0,
    ICMP_TYPE_ECHO_REQUEST  = 8,

    ICMP_TYPE_BUTT
};
typedef VOS_UINT8 ICMP_TYPE_ENUM_UINT8;


typedef struct tagIN4ADDR
{
    PF_ULONG s_ulAddr;
}IN4ADDR_S;


typedef struct tagIP4
{

#if (FWD_LITTLE_ENDIAN == FWD_YES)
    PF_UCHAR   ip_chHLen:4;        /* header length */
    PF_UCHAR   ip_chVer:4;         /* version */
#else
    PF_UCHAR  ip_chVer:4;         /* version */
    PF_UCHAR  ip_chHLen:4;        /* header length */
#endif
    PF_UCHAR   ip_chTOS;           /* type of service */
    PF_USHORT  ip_usLen;       /* total length */

#define ip_sLen     ip_usLen
    PF_USHORT    ip_usId;        /* identification */
    PF_USHORT    ip_usOff;           /* fragment offset field */

#define ip_sOff    ip_usOff
#define    IP_DF 0x4000        /* dont fragment flag */
#define    IP_MF 0x2000        /* more fragments flag */
#define    IP_OFFMASK 0x1fff       /* mask for fragmenting bits */

    PF_UCHAR   ip_chTTL;       /* time to live */

    PF_UCHAR    ip_chPr;            /* protocol */

    PF_USHORT    ip_usSum;            /* checksum */

    IN4ADDR_S ip_stSrc;
    IN4ADDR_S ip_stDst;/* source and dest address */
} IP4_S;

typedef struct
{
    VOS_UINT16  usSrcPort;
    VOS_UINT16  usDstPort;    /* Source and Dest Port */
    VOS_UINT32  ulSeq;        /* Sequence Number */
    VOS_UINT32  ulAck;        /* Acknowledgement Number */

    /* ��δ��tcp����ͷ������Ԫ�ؾ��г��� */
    VOS_UINT8   aucOthers[4];
} PPP_TRACE_TCP4_STRU;

typedef struct
{
    VOS_UINT16  usSrcPort;
    VOS_UINT16  usDstPort;      /* Source and Dest Port */
    VOS_UINT16  usLen;          /* Length */
    VOS_UINT16  usCheckSum;     /* CRC */

    /* �����Ϊdata */
    VOS_UINT8   aucData[4];
} PPP_TRACE_UDP4_STRU;

typedef struct
{
    VOS_UINT8   ucType;
    VOS_UINT8   ucCode;
    VOS_UINT16  usCheckSum;     /* CRC */
    VOS_UINT32  ulOtherHd;      /* Other Parts of Header */

    /* �����Ϊdata */
    VOS_UINT8   aucData[4];
} PPP_TRACE_ICMP_STRU;


/** ****************************************************************************
* Name        : PPP_REBUILD_MNTN_STATISTIC_STRU
*
* Description : PPP��Ƭ�����ά�ɲ�ͳ��ֵ.
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRebuildStat;                          /* PPP��Ϣ�����д��������Ϣ���� */
    VOS_UINT32                          ulGetPppIdFailStat;                     /* ������ */
    VOS_UINT32                          ulGetLinkItemFailStat;
    VOS_UINT32                          ulGetCurrItemStat;
    VOS_UINT32                          ulGetHeadItemStat;
    VOS_UINT32                          ulGetNextItemStat;
    VOS_UINT32                          ulCalcOffsetStat;
    VOS_UINT32                          ulHeadNotFlagSeqStat;
    VOS_UINT32                          ulFindFlagSeqStat;
    VOS_UINT32                          ulNotFindFlagSeqStat;
    VOS_UINT32                          ulHeadIsFlagSeqStat;
    VOS_UINT32                          ulContinueFlagSeqStat;
    VOS_UINT32                          ulNotAllFlagSeqStat;
    VOS_UINT32                          ulFindFlagSeqStat1;
    VOS_UINT32                          ulNotFindFlagSeqStat1;
    VOS_UINT32                          ulAllAreFlagSeqStat;
    VOS_UINT32                          ulDoRebuildStat;
    VOS_UINT32                          ulPktNumErrStat;
    VOS_UINT32                          ulEnterDoRebuildStat;
    VOS_UINT32                          ulNodeNotNullStat;
    VOS_UINT32                          ulNotStartWithSeqStat;
    VOS_UINT32                          ulNoFlagSeqStat;
    VOS_UINT32                          ulWithValidPktStat;
    VOS_UINT32                          ulContinueFlagSeqStat1;
    VOS_UINT32                          ulTailIsFlagSeqStat;
    VOS_UINT32                          ulValidPktInCurrNodeStat;
    VOS_UINT32                          ulNotFindFlagSeqStat2;
    VOS_UINT32                          ulFindFlagSeqStat2;
    VOS_UINT32                          ulFindFlagSeqStat3;
    VOS_UINT32                          ulAllAreFlagSeqStat1;
    VOS_UINT32                          ulNotAllFlagSeqStat1;
    VOS_UINT32                          ulDeleteJumpedNodeStat;
    VOS_UINT32                          ulDeleteHeadNodeStat;
    VOS_UINT32                          ulNodeNotNullStat1;
    VOS_UINT32                          ulRebuildEndFlagStat;
    VOS_UINT32                          ulTNodeNotNullStat;
    VOS_UINT32                          ulFindFlagSeqStat4;
    VOS_UINT32                          ulTNodeIsNullStat;
    VOS_UINT32                          ulCreateMBufStat;
    VOS_UINT32                          ulMBufIsNullStat;
    VOS_UINT32                          ulIsHeadOrNotStartSeqStat;
    VOS_UINT32                          ulLagerThan3600Stat;
    VOS_UINT32                          ulNodeIsNotHeadStat;
    VOS_UINT32                          ulDataIsNotNullStat;
    VOS_UINT32                          ulLargerThan2000Stat;
    VOS_UINT32                          ulCreateDataBlockFailStat;
    VOS_UINT32                          ulRebuildSuccStat;
    VOS_UINT32                          ulNextProcessSliceStat;
    VOS_UINT32                          ulAllAreFlagSeqStat2;
    VOS_UINT32                          ulNoteTmpNodeStat;
    VOS_UINT32                          ulLastSliceStat;
    VOS_UINT32                          ulNotLastSliceStat;
    VOS_UINT32                          ulContinueFlagSeqStat2;
    VOS_UINT32                          ulPktEndsAtEndStat;
    VOS_UINT32                          ulFindNextNodeStat;
    VOS_UINT32                          ulPktEndsNotAtEndStat;
    VOS_UINT32                          ulNotFindFlagSeqStat3;
    VOS_UINT32                          ulFindFlagSeqStat5;
    VOS_UINT32                          ulReleaseSourceStat;
    VOS_UINT32                          ulReleaseMBufStat;
    VOS_UINT32                          ulReleaseMBufStat1;
    VOS_UINT32                          ulReleaseNodesStat;
    VOS_UINT32                          ulReleaseDataStat;
} PPP_REBUILD_MNTN_STATISTIC_STRU;

/** ****************************************************************************
* Name        : PPP_REBUILD_MNTN_STORE_ITEM_STRU
*
* Description : PPP��Ƭ�����ά�ɲ�洢10������Ľڵ�.
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHndleSeq;
    VOS_UINT16                          usOffset;
    VOS_UINT16                          usCopy;
    VOS_UINT16                          usLitem;
    VOS_UINT16                          usRsvd[3];                              /*��֤�����ָ�밴8�ֽڶ���*/
    PMBUF_S                             stMbuf;                                 /*���ڴ洢MBUF����*/
    VOS_UINT8                           aucData[PPP_MAX_DATA_BLOCK_LENGTH];     /*���ڴ洢MBUF��������*/
} PPP_REBUILD_MNTN_STORE_ITEM_STRU;

/** ****************************************************************************
* Name        : PPP_REBUILD_INCOMPLETE_SLICE_STRU
*
* Description : PPP��Ƭ���鵱ǰ״̬
*******************************************************************************/
typedef struct
{
    VOS_UINT16                           ucHasStartFlag;
    VOS_UINT16                           ucHasEndFlag;
    VOS_UINT32                           ulCurTotalLen;
    VOS_UINT16                           usStartSeq;
    VOS_UINT16                           usEndSeq;
    VOS_UINT32                           ulStartFlagOffset;
    VOS_UINT32                           ulEndFlagOffset;
} PPP_REBUILD_INCOMPLETE_SLICE_STRU;


VOS_VOID FWD_PppFillDataInfo
(
    VOS_UINT8                          *pucPppData,
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo
);

VOS_UINT32 FWD_PppParse
(
    VOS_UINT8                          *pcuPppHead,
    VOS_UINT32                         *pulHdLen,
    FWD_PKT_TYPE_ENUM_UINT8            *enIpVersion
);

VOS_VOID FWD_PppDecap
(
    VOS_UINT16                          usStartSeq,
    VOS_UINT16                          usEndSeq,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode
);

VOS_UINT32 FWD_PppGetHisLcpFcFlag
(
    VOS_UINT8                           ucPppId,
    VOS_UINT32                         *pulPppFcFlag
);

VOS_UINT32 FWD_PppGetHisLcpAcfcFlag
(
    VOS_UINT8                           ucPppId,
    VOS_UINT32                         *pulPppAcfcFlag
);

VOS_UINT32 FWD_PppGetHisAccm
(
    VOS_UINT8                           ucPppId,
    VOS_UINT32                         *pulAccmFlag
);


VOS_UINT32 FWD_PppEncap
(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                          *pucCdsData,
    VOS_UINT16                          usDataLen,
    VOS_UINT32                          ulAccmValue,
    VOS_UINT32                         *pulAsynLen
);

VOS_VOID FWD_PppRebuild
(
    VOS_UINT16                          usSeqNr,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode
);

VOS_VOID FWD_PppHandleCompleteFrame
(
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode
);


#ifdef __cplusplus
}
#endif
#endif    /* end of __FWD_PPP_H__ */
