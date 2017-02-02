/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              ppp_vj_func.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPP
 *  Date Created: 2002-10-24
 *        Author: LiuKai
 *   Description: VJѹ������ģ�����ݽṹ���弰������
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2002-10-24      LiuKai          Create
 *  2004-07-01      YiAn            Modified for VISP
 *  2006-03-31      ZhuKun          Adjust for D00661
 *  2006-04-21      ZhuKun          Adjust for D00875
 *
 *************************************************************************/

#ifndef _VJ_FUNC_H_
#define _VJ_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_STATES          16              /* must be >2 and <255 */
#define MAX_HDR_VJ          128             /* max TCP+IP hdr length (by protocol def) */

/* packet types */
#define TYPE_IP             PPP_IP
#define TYPE_ERROR          0x0000          /* ����һ��û�г��ֵ�����  this is not a type that ever appears on
                                             * the wire.  The receive framer uses it to
                                             * tell the decompressor there was a packet
                                             * transmission error. 
                                             * Ŀ����������֪ͨ��һ�����Ĵ������
                                             */

/*
 * ѹ������ǰ8�ֽڱ���  Bits in first octet of compressed packet
 */

/* ����ڱ����и��ĵı���  flag bits for what changed in a packet */

#define NEW_C  0x40         /* ���� */
#define NEW_I  0x20         /* ���� */
#define TCP_PUSH_BIT 0x10   /* ���� */

#define NEW_S  0x08         /* ���� */
#define NEW_A  0x04         /* ���� */
#define NEW_W  0x02         /* ���� */
#define NEW_U  0x01         /* ���� */

/* ���ϱ�ʾ���յ����������ֵ  reserved, special-case values of above */
#define SPECIAL_I (NEW_S|NEW_W|NEW_U)        /* ����ʽ�ز��ź�  echoed interactive traffic */
#define SPECIAL_D (NEW_S|NEW_A|NEW_W|NEW_U)  /* ��������  unidirectional data */
#define SPECIALS_MASK (NEW_S|NEW_A|NEW_W|NEW_U)


/*
 * ÿһ�����õ�tcp�滰"state"����
 * "state" data for each active tcp conversation on the wire.  This is
 * �������Ǵ���һ�����ĸ��Ƶ�����TCP/IPͷ
 * basically a copy of the entire IP/TCP header from the last packet together
 * with a small identifier the transmit & receive ends of the line use to
 * locate saved header.
 * ת��&���ս�����������λ�������ײ�
 */

typedef struct tagCState 
{
    struct tagCState *pCSNext;      /* ��һ�����ʹ�õ�cstate  next most recently used cstate (xmit only) */
    USHORT cs_usHdrLen;             /* Ӳ����ַ����(ֻ�н���)  size of hdr (receive only) */
    UCHAR cs_usID;                  /* ���state���  connection # associated with this state */
    UCHAR cs_usFiller;
    union
    {
        CHAR m_chHdr[MAX_HDR_VJ];   /* Not referenced, for keep space only */
        struct tagIP m_stIP;        /* ip/tcp hdr from most recent packet */
    } cs_uIP;
} CState_S;

/* �˴������궨�岻�������ϳ�Աͬ������GCT�»ᵼ�´��� */
#define cs_stIP         cs_uIP.m_stIP
#define cs_chHdr        cs_uIP.m_chHdr

/*
 * all the state data for one serial line (we need one of these per line).
 */
typedef struct tagSLCompress 
{
    struct tagCState *pCSLast;              /* most recently used tstate */
    UCHAR chLastRecv;                       /* last rcvd conn. id */
    UCHAR chLastXmit;                       /* last sent conn. id */
    USHORT usFlags;
    struct tagCState astXState[MAX_STATES]; /* xmit connection states */
    struct tagCState astRState[MAX_STATES]; /* receive connection states */
} SLCompress_S;

/* flag values */
#define SLF_TOSS 1              /* tossing rcvd frames because of input err */

/*
 * The following macros are used to encode and decode numbers.  They all
 * assume that `cp' points to a buffer where the next byte encoded (decoded)
 * is to be stored (retrieved).  Since the decode routines do arithmetic,
 * they have to convert from and to network byte order.
 */

/*
 * ENCODE encodes a number that is known to be non-zero.  ENCODEZ checks for
 * zero (zero has to be encoded in the long, 3 byte form).
 */
 
/*modified by ding delu for XD13388 2002-8-17 */
#define ENCODE(n) { \
     if ((USHORT)(n) >= 256) { \
          *cp = 0; \
          cp++; \
          cp[1] = (UCHAR)(n); \
          cp[0] = (UCHAR)((n) >> 8); \
          cp += 2; \
     } else { \
          *cp = (UCHAR)(n); \
          cp++; \
     } \
}
#define ENCODEZ(n) { \
     if ((USHORT)(n) >= 256 || (USHORT)(n) == 0) { \
          *cp = 0; \
          cp++; \
          cp[1] = (UCHAR)(n); \
          cp[0] = (UCHAR)((n) >> 8); \
          cp += 2; \
     } else { \
          *cp = (UCHAR)(n); \
          cp++; \
     } \
}

/*
 * DECODEL takes the (compressed) change at byte cp and adds it to the
 * current value of packet field 'f' (which must be a 4-byte (long) integer
 * in network byte order).  DECODES does the same for a 2-byte (short) field.
 * DECODEU takes the change at cp and stuffs it into the (short) field f.
 * 'cp' is updated to point to the next field in the compressed header.
 */
#define DECODEL(f) { \
    if (*cp == 0) {\
        ULONG ulTemp = (cp[1] << 8) | cp[2];\
        (f) = VOS_HTONL(VOS_HTONL(f) + ulTemp); \
        cp += 3; \
    } else { \
        ULONG ulTemp = (ULONG)(*cp);\
        (f) = VOS_HTONL(VOS_HTONL(f) + ulTemp); \
        cp++;\
    } \
}
#define DECODES(f) { \
    if (*cp == 0) {\
        USHORT usTemp = (cp[1] << 8) | cp[2];\
        (f) = (USHORT)VOS_HTONS(VOS_NTOHS(f) + usTemp); \
        cp += 3; \
    } else { \
        USHORT usTemp = (USHORT)(*cp);\
        (f) = (USHORT)VOS_HTONS(VOS_NTOHS(f) + usTemp); \
        cp++;\
    } \
}

#define DECODEU(f) { \
    if (*cp == 0) {\
        USHORT usTemp = (cp[1] << 8) | cp[2];\
        (f) = (USHORT)VOS_HTONS(usTemp); \
        cp += 3; \
    } else { \
        USHORT usTemp = (USHORT)(*cp);\
        (f) = (USHORT)VOS_HTONS(usTemp); \
        cp++;\
    } \
}
/*END modified by ding delu for XD13388 2002-8-17 */

extern MBUF_S *  PPP_VJComp_UnCompress(MBUF_S *, USHORT, SLCompress_S *);
extern USHORT    PPP_VJComp_Compress(MBUF_S **, SLCompress_S *, int);
extern void      PPP_VJComp_Init(SLCompress_S *);

#ifdef __cplusplus
}
#endif

#endif /*_VJ_FUNC_H_ */
