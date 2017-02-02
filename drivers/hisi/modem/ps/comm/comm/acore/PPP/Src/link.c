/*-
 * Copyright (c) 1998 Brian Somers <brian@Awfulhak.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/usr.sbin/ppp/link.c,v 1.19 2002/08/27 20:11:57 brian Exp $
 *
 */
 
/******************************************************************************
   ͷ�ļ�����
******************************************************************************/
#include "PPP/Inc/ppp_public.h"
#include "PPP/Inc/layer.h"
#include "PPP/Inc/ppp_mbuf.h"
#include "PPP/Inc/hdlc.h"
#include "PPP/Inc/acf.h"
#include "PPP/Inc/throughput.h"
#include "PPP/Inc/proto.h"
#include "PPP/Inc/ppp_fsm.h"
#include "PPP/Inc/lcp.h"
#include "PPP/Inc/async.h"
#include "PPP/Inc/auth.h"
#include "PPP/Inc/ipcp.h"
#include "PPP/Inc/pppid.h"
#include "PPP/Inc/link.h"
#include "PPP/Inc/pap.h"
#include "PPP/Inc/ppp_input.h"
#include "AdsDeviceInterface.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

/*****************************************************************************
   1 Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_LINK_C

#if(FEATURE_ON == FEATURE_PPP)
/******************************************************************************
   2 �ⲿ������������
******************************************************************************/
extern struct ppp_mbuf *
proto_LayerPush(/*struct bundle *b, */struct link *l, struct ppp_mbuf *bp,
                VOS_INT32 pri, VOS_UINT16 *proto);
extern struct ppp_mbuf *
acf_LayerPush(/*struct bundle *b, */struct link *l, struct ppp_mbuf *bp,
              VOS_INT32 pri, VOS_UINT16 *proto);
extern struct ppp_mbuf *
async_LayerPush(/*struct bundle *bundle, */struct link *l, struct ppp_mbuf *bp,
                VOS_INT32 pri, VOS_UINT16 *proto);
extern PPP_ZC_STRU *ipv4_Input(/*struct bundle *bundle, */struct link *l, PPP_ZC_STRU *bp);

void ParentLayerStart (void *p, struct fsm *fsm);
void ParentLayerUp (void *p, struct fsm *fsm);
void ParentLayerDown (void *p, struct fsm *fsm);
void ParentLayerFinish (void *p, struct fsm *fsm);

#ifdef PPP_ST_TEST
VOS_VOID   PPP_STUB_ProcDlData(VOS_UINT16 usPppId, PPP_ZC_STRU *pstMem);
VOS_UINT32 PPP_STUB_ProcUlData(IMM_ZC_STRU *pstData, VOS_UINT8 ucRabId);

#endif
/*****************************************************************************
   3 ˽�ж���
*****************************************************************************/
#define PROTO_IN  1                       /* third arg to link_ProtocolRecord */
#define PROTO_OUT 2


/*****************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/
struct link*            pgPppLink = VOS_NULL_PTR;

PPP_HDLC_CONFIG_STRU    g_astHdlcConfig[PPP_MAX_ID_NUM] = {{0, 0, 0, 0}};

PPP_HDLC_CONFIG_STRU    *g_pstHdlcConfig = &g_astHdlcConfig[0];

/*lint -e958 -e830 -e528*/

static const struct {
  VOS_UINT16 proto;
  PPP_ZC_STRU *(*fn)(/*struct bundle *, */struct link *, PPP_ZC_STRU *);
} despatcher[] = {
  { PROTO_IP, ipv4_Input },
#ifndef NOINET6
#ifndef NI_WITHSCOPEID
#define NI_WITHSCOPEID 0
#endif
  /*{ PROTO_IPV6,ipv6_Input },*/
#endif
  /*{ PROTO_MP, mp_Input },*/
  { PROTO_LCP,lcp_Input},
  { PROTO_IPCP, ipcp_Input},
#ifndef NOINET6
#ifndef NI_WITHSCOPEID
#define NI_WITHSCOPEID 0
#endif
  /*{ PROTO_IPV6CP, ipv6cp_Input },*/
#endif
  { PROTO_PAP, pap_Input},
  { PROTO_CHAP, chap_Input }
  /*{ PROTO_CCP, ccp_Input },*/
  /*{ PROTO_LQR, lqr_Input },*/
  /*{ PROTO_CBCP, cbcp_Input }*/
};
/*lint +e958 +e830 -e528*/

#define DSIZE (sizeof despatcher / sizeof despatcher[0])

struct  fsm_parent  parent = {
             ParentLayerStart,
             ParentLayerUp,
             ParentLayerDown,
             ParentLayerFinish,
             VOS_NULL
             };

/******************************************************************************
   5 ����ʵ��
******************************************************************************/
#if 0
static struct protostatheader {
  VOS_UINT16 number;
  const VOS_CHAR *name;
} ProtocolStat[NPROTOSTAT] = {
  { PROTO_IP, "IP" },
  { PROTO_VJUNCOMP, "VJ_UNCOMP" },
  { PROTO_VJCOMP, "VJ_COMP" },
  { PROTO_COMPD, "COMPD" },
  { PROTO_ICOMPD, "ICOMPD" },
  { PROTO_LCP, "LCP" },
  { PROTO_IPCP, "IPCP" },
  { PROTO_CCP, "CCP" },
  { PROTO_PAP, "PAP" },
  { PROTO_LQR, "LQR" },
  { PROTO_CHAP, "CHAP" },
  { PROTO_MP, "MULTILINK" },
  { 0, "Others" }
};

void
link_AddInOctets(struct link *l, VOS_INT32 n)
{
  if (l->stats.gather)
  {
    throughput_addin(&l->stats.total, n);
    if (l->stats.parent)
    {
        throughput_addin(l->stats.parent, n);
    }
  }
}

void
link_AddOutOctets(struct link *l, VOS_INT32 n)
{
  if (l->stats.gather)
  {
    throughput_addout(&l->stats.total, n);
    if (l->stats.parent)
    {
        throughput_addout(l->stats.parent, n);
    }
  }
}

void
link_DeleteQueue(struct link *l)
{
  struct ppp_mqueue *queue, *highest;

  highest = LINK_HIGHQ(l);
  for (queue = l->Queue; queue <= highest; queue++)
  {
    while (queue->top)
    {
      ppp_m_freem(ppp_m_dequeue(queue));
    }
  }
}

VOS_UINT32
link_QueueLen(struct link *l)
{
  VOS_UINT32 i;
  VOS_UINT32 len;

  for (i = 0, len = 0; i < LINK_QUEUES(l); i++)
  {
    len += l->Queue[i].len;
  }

  return len;
}

/*lint -e732*/
VOS_UINT32
link_QueueBytes(struct link *l)
{
  VOS_UINT32 i;
  VOS_UINT32 len, bytes;
  struct ppp_mbuf *m;

  bytes = 0;
  for (i = 0, len = 0; i < LINK_QUEUES(l); i++)
  {
    len = l->Queue[i].len;
    m = l->Queue[i].top;
    while (len--)
    {
      bytes += ppp_m_length(m);
      m = m->m_nextpkt;
    }
  }

  return bytes;
}
/*lint +e732*/

/*lint -e958*/
struct ppp_mbuf *
link_Dequeue(struct link *l)
{
  VOS_INT32 pri;
  struct ppp_mbuf *bp;

  for (bp = VOS_NULL_PTR, pri = LINK_QUEUES(l) - 1; pri >= 0; pri--)
  {
    if (l->Queue[pri].len)
    {
      bp = ppp_m_dequeue(l->Queue + pri);
      PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                    "pri <1>;length <2>\r\n", pri, (VOS_INT32)l->Queue[pri].len);
      break;
    }
  }
  return bp;
}
/*lint +e958*/

/*lint -e661*/
void
link_ProtocolRecord(struct link *l, VOS_UINT16 proto, VOS_INT32 type)
{
    VOS_INT32 i;

    for (i = 0; i < NPROTOSTAT; i++)
    {
        if (ProtocolStat[i].number == proto)
        {
            break;
        }
    }
    if (type == PROTO_IN)
    {
        l->proto_in[i]++;
    }
    else
    {
        l->proto_out[i]++;
    }
}
/*lint +e661*/

void
link_ReportProtocolStatus(struct link *l/*, struct prompt *prompt*/)
{
    VOS_INT32 i;

    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Protocol  in out\r\n");
    for (i = 0; i < NPROTOSTAT; i++)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "   %-9s: %8lu, %8lu\r\n"/*,
            ProtocolStat[i].name, l->proto_in[i], l->proto_out[i]*/);
        if ((i % 2) == 0)
        {
            PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "\n");
        }
    }
    if (!(i % 2))
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "\n");
    }
}

VOS_INT32 link_ShowLayers(struct link *l/*struct cmdargs const *arg*/)
{
    /*  struct link *l = command_ChooseLink(arg);*/
    VOS_INT32 layer;

    for (layer = l->nlayers; layer; layer--)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "%s%s");
    }
    if (l->nlayers)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "\n");
    }

    return 0;
}
#endif

void link_SequenceQueue(struct link *l)
{
  struct ppp_mqueue *queue, *highest;

  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "link_SequenceQueue\r\n");

  highest = LINK_HIGHQ(l);
  for (queue = l->Queue; queue < highest; queue++)
  {
    while (queue->len)
    {
        ppp_m_enqueue(highest, ppp_m_dequeue(queue));
    }
  }
}


VOS_INT32 link_Stack(struct link *l, struct layer *layer)
{
  if (l->nlayers == sizeof l->layer / sizeof l->layer[0]) {
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
        "Oops, cannot stack a layer\r\n");
    return 0;
  }
  l->layer[l->nlayers++] = layer;
  return 1;
}

void link_EmptyStack(struct link *l)
{
  l->nlayers = 0;
}

/*****************************************************************************
 Prototype      : ipv4_Input
 Description    : ����TE�����������ݱ��ģ������Ӧ��link���Ǵ�������׶β���״
                  ̬Ϊopen��ת���˱��ĵ�GGSN��

 Input          : ---
 Output         : ---����ָ��mbuf��ָ��
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : ---
    Modification: Created function
*****************************************************************************/
PPP_ZC_STRU *ipv4_Input(/*struct bundle *bundle, */struct link *l, PPP_ZC_STRU *bp)
{
    if(l->phase == PHASE_NETWORK
        &&l->ipcp.fsm.state == ST_OPENED)
    {
        #if (PPP_FEATURE == PPP_FEATURE_PPP)
        /*���������ݷ���Э��ջ*/
        PPP_SendPulledData((VOS_UINT16)PPP_LINK_TO_ID(l), bp);
        #else
        /*����PPPoE�ķ��ͺ���*/
        PPPoE_PPPSendDataToRABM(PPP_ZC_GET_DATA_PTR(bp), PPP_ZC_GET_DATA_LEN(bp));
        PPP_MemFree(bp);
        #endif
    }
    else
    {
        PPP_MemFree(bp);
    }

    return VOS_NULL_PTR;
}

void ParentLayerStart (void *p, struct fsm *fsm)         /* tls */
{
    return;
}

void ParentLayerUp (void *p, struct fsm *fsm)            /* tlu */
{
    return;
}

void ParentLayerDown (void *p, struct fsm *fsm)          /* tld */
{
    return;
}

void ParentLayerFinish (void *p, struct fsm *fsm)        /* tlf */
{
    return;
}

VOS_VOID link_Init(struct link *l)
{
    l->phase = PHASE_DEAD;
    l->type = PHYSICAL_LINK;
    l->name = VOS_NULL;
    l->len = sizeof(*l);

    /* The sample period is fixed - see physical2iov() & iov2physical() */
    throughput_init(&l->stats.total, SAMPLE_PERIOD);

    #if 0
    p->link.stats.parent = dl->bundle->ncp.mp.active ?
    &dl->bundle->ncp.mp.link.stats.total : VOS_NULL_PTR;
    #endif

    l->stats.gather = 1;
    l->DropedPacketFromGgsn = 0;

    PS_MEM_SET(l->Queue, '\0', sizeof l->Queue);
    PS_MEM_SET(l->proto_in, '\0', sizeof l->proto_in);
    PS_MEM_SET(l->proto_out, '\0', sizeof l->proto_out);
    link_EmptyStack(l);

    /*����ѹ��PPPЭ��ĸ��������*/
    #if (PPP_FEATURE == PPP_FEATURE_PPP)
    link_Stack(l, &asynclayer);
    link_Stack(l, &hdlclayer);
    link_Stack(l, &acflayer);
    #endif

    link_Stack(l, &protolayer);

    async_Init(&(l->async));
    hdlc_Init(&(l->hdlc),&(l->lcp));

    /*����const struct fsm_parent * parent����Ϊ��*/
    lcp_Init(&(l->lcp), l, &parent);
    ipcp_Init(&(l->ipcp), l, &parent);
    pap_Init(&(l->pap));
    chap_Init(&(l->chap));
}

void link_PushPacket(struct link *l, struct ppp_mbuf *bp,/* struct bundle *b, */VOS_INT32 pri,
                VOS_UINT16 proto)
{
    PPP_ID                  usPppId     = (PPP_ID)(PPP_LINK_TO_ID(l));
    PPP_HDLC_CONFIG_STRU   *pstHdlcConfig;


    /* ��PPPЭ�̰���Ϊ��ά�ɲ���Ϣ,IP��������ά�ɲ�ά��*/
    if (PROTO_IP != proto)
    {
        Ppp_MBufFrameMntnInfo(bp, proto, PPP_SEND_OUT_PROTOCOL_FRAME);
    }

    pstHdlcConfig = PPP_CONFIG(usPppId);

    if (VOS_NULL_PTR != pstHdlcConfig->pFunProcProtocolPacket)
    {
        pstHdlcConfig->pFunProcProtocolPacket(l, bp, pri, proto);
    }
    else
    {
        ppp_m_freem(bp);
        bp = VOS_NULL_PTR;

        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                     "PPP, link_PushPacket, WARNING, pFunProcProtocolPacket is NULL!\r\n");
    }

    return;
}
VOS_VOID PPP_HDLC_ProcIpModeUlData
(
    struct link *pstLink,
    PPP_ZC_STRU *pstMem,
    VOS_UINT16  usProto
)
{
    #ifdef PPP_ST_TEST
    PPP_STUB_ProcUlData(pstMem, 5);
    #else
    VOS_UINT32          f;
    struct ppp_mbuf    *bp;

    /* ��PPPЭ�̰���Ϊ��ά�ɲ���Ϣ,IP��������ά�ɲ�ά��*/
    if (PROTO_IP != usProto)
    {
        Ppp_TtfMemFrameMntnInfo(pstMem, usProto, PPP_RECV_IN_PROTOCOL_FRAME);
    }

    for (f = 0; f < DSIZE; f++)
    {
        if (despatcher[f].proto == usProto)
        {
            pstMem = (*despatcher[f].fn)(/*bundle, */pstLink, pstMem);
            break;
        }
    }

    /* ����ǲ�֧�ֵ�Э�飬��Զ˷���REJ֡ */
    if (VOS_NULL_PTR != pstMem)
    {
        bp = ppp_m_get_from_ttfmem(pstMem);

        PPP_MemFree(pstMem);

        if (VOS_NULL_PTR == bp)
        {
            return;
        }

        /*    struct physical *p = link2physical(l);

        log_Printf(LogPHASE, "%s protocol 0x%04x (%s)\n",
        f == DSIZE ? "Unknown" : "Unexpected", proto,
        hdlc_Protocol2Nam(proto));*/

        bp = ppp_m_pullup(proto_Prepend(bp, usProto, 0, 0));

        if (VOS_NULL_PTR == bp)
        {
            return;
        }
        lcp_SendProtoRej(&pstLink->lcp, PPP_MBUF_CTOP(bp), bp->m_len);
        if (pstLink)
        {
            pstLink->hdlc.lqm.SaveInDiscards++;
            pstLink->hdlc.stats.unknownproto++;
        }
        ppp_m_freem(bp);
    }

    return;
    #endif
}


VOS_VOID PPP_HDLC_ProcPppModeUlData
(
    PPP_ID      usPppId,
    PPP_ZC_STRU *pstMem
)
{
    #ifdef PPP_ST_TEST
    PPP_STUB_ProcUlData(pstMem, 5);
    #else
    PPP_SendPulledData(usPppId, pstMem);
    #endif
    return;
}


VOS_VOID PPP_HDLC_ProcDlData(VOS_UINT16 usPppId, PPP_ZC_STRU *pstMem)
{
    #ifdef PPP_ST_TEST
    PPP_STUB_ProcDlData(usPppId, pstMem);
    #else
    /* ����ATģ���������ݽ��սӿ� */
    AT_SendZcDataToModem(usPppId, pstMem);
    #endif

    return;
}

#ifdef WTTF_PC_ST_SWITCH
/******************************************************************************
 Function:       PPP_STUB_TraceDlData
 Description:    ��������GTR����������
 Calls:
 Data Accessed:
 Data Updated:
 Input:
 Output:
 Return:

 Others:
******************************************************************************/
VOS_VOID PPP_STUB_RcvUlData(PPP_STUB_ZC_DATA_MSG_STRU *pstUlStubDataMsg)
{
    PPP_ZC_STRU                        *pstImmZc;

    pstImmZc = PPP_MemAlloc(pstUlStubDataMsg->u.stUlDataReq.usDataLen, 0);

    if ( VOS_NULL_PTR == pstImmZc )
    {
        return;
    }

    PPP_MemWriteData(pstImmZc, &(pstUlStubDataMsg->u.stUlDataReq.aucData[0]),
                     pstUlStubDataMsg->u.stUlDataReq.usDataLen);

    PPP_PullPacketEvent(PppGetAllocedId(), pstImmZc);

    return;
}

/******************************************************************************
 Function:       PPP_STUB_TraceDlData
 Description:    ���������ݷ��͸�GTR
 Calls:
 Data Accessed:
 Data Updated:
 Input:
 Output:
 Return:

 Others:
******************************************************************************/
VOS_VOID PPP_STUB_TraceDlData(PPP_ZC_STRU *pstImmZc)
{
    PPP_STUB_ZC_DATA_MSG_STRU          *pstDlStubMsg;
    VOS_UINT32                          ulLength;


    ulLength = sizeof(PPP_STUB_ZC_DATA_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstDlStubMsg = (PPP_STUB_ZC_DATA_MSG_STRU *) PS_ALLOC_MSG( PS_PID_APP_PPP, ulLength);

    if ( VOS_NULL_PTR == pstDlStubMsg )
    {
        return;
    }

    pstDlStubMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstDlStubMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstDlStubMsg->ulSenderPid     = PS_PID_APP_PPP;
    pstDlStubMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstDlStubMsg->ulLength        = ulLength;

    pstDlStubMsg->ulMsgType       = PPP_AT_DL_DATA_IND;

    pstDlStubMsg->u.stDlDataInd.usDataLen       = PPP_ZC_GET_DATA_LEN(pstImmZc);

    PPP_MemSingleCopy(&(pstDlStubMsg->u.stDlDataInd.aucData[0]), PPP_ZC_GET_DATA_PTR(pstImmZc),
                      pstDlStubMsg->u.stDlDataInd.usDataLen);

    PS_SEND_MSG(PS_PID_APP_PPP, pstDlStubMsg);

#ifdef WTTF_PS_FUSION_PC_ST
    PPP_MemFree(pstImmZc);
#endif

    return;
}
#endif


VOS_UINT32 PPP_SendPulledData(VOS_UINT16 usPppId,  PPP_ZC_STRU *pstImmZc)
{
    VOS_UINT8                          ucRabId = PPP_INVALID_RABID;
    VOS_UINT32                         ulResult;


    #ifdef WTTF_PS_FUSION_PC_ST
    ucRabId = 5;
    #else
    /* ͨ��usPppId��Ѱ�ҵ�usRabId */
    if ( !PPP_PPPID_TO_RAB(usPppId, &ucRabId) )
    {
        g_PppDataQCtrl.stStat.ulUplinkDropCnt++;
        PPP_MemFree(pstImmZc);
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                      "PPP, PPP_PushPacketEvent, WARNING, Can not get PPP Id %d, RabId %d",
                      usPppId, ucRabId);

        return PS_FAIL;
    }
    #endif

    /* ���ݷ��͸�ADS�����ʧ�����ͷ��ڴ� */
    ulResult = ADS_UL_SendPacket(pstImmZc, ucRabId);

    if ( VOS_OK != ulResult )
    {
        g_PppDataQCtrl.stStat.ulUplinkDropCnt++;
        PPP_MemFree(pstImmZc);

        return PS_FAIL;
    }

    g_PppDataQCtrl.stStat.ulUplinkSndDataCnt++;

    return PS_SUCC;
}


VOS_UINT32 PPP_SendPushedData(VOS_UINT16 usPppId, VOS_UINT8 *pucDataBuf, VOS_UINT16 usLen)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT16                          usRemainLen = usLen;
    VOS_UINT8                          *pucRemainDataBuf = pucDataBuf;


    while ( 0 < usRemainLen)
    {
        /* �㿽���ڴ���������ƣ����޷ֶ�η��� */
        if ( PPP_ZC_MAX_DATA_LEN < usRemainLen)
        {
            pstMem       = PPP_MemCopyAlloc(pucRemainDataBuf, PPP_ZC_MAX_DATA_LEN, PPP_ZC_DL_RESERVE_LEN);
            usRemainLen -= PPP_ZC_MAX_DATA_LEN;
            pucRemainDataBuf += PPP_ZC_MAX_DATA_LEN;
        }
        else
        {
            pstMem       = PPP_MemCopyAlloc(pucRemainDataBuf, usRemainLen, PPP_ZC_DL_RESERVE_LEN);
            usRemainLen  = 0;
        }

        if ( VOS_NULL_PTR == pstMem )
        {
            return PS_FAIL;
        }

        #ifdef WTTF_PC_ST_SWITCH
        PPP_STUB_TraceDlData(pstMem);
        #else
        PPP_HDLC_ProcDlData(usPppId, pstMem);
        #endif

        g_PppDataQCtrl.stStat.ulDownlinkSndDataCnt++;
    }

    return PS_SUCC;
}

#endif /*#if(FEATURE_ON == FEATURE_PPP)*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


