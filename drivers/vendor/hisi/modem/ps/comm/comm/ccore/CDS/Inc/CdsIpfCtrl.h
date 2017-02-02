

#ifndef __CDS_IPFCTRL_H__
#define __CDS_IPFCTRL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "CdsDepend.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define CDS_IPF_MAX_DL_FILTER_NUM                   (12)          /* ����FilterĿǰʹ��8�� */
#define CDS_IPF_MAX_UL_FILTER_NUM                   (128)         /* ����FilterĿǰʹ��128�� */

/*IPF����Դ�ڴ��ͷ�QUEUE������Ϊ����IPF BD��������2��*/
#define CDS_IPF_DL_SRCMEM_FREE_QUE_SIZE             (2*IPF_DLBD_DESC_SIZE)

/*����SDU���д�С*/
#define CDS_IPF_DL_SDU_QUE_SIZE                     (2048)

/*AD0�̰��ڴ泤��*/
#define CDS_IPF_AD_0_PKT_LEN                        (400)

/*AD1�����ڴ泤��*/
#define CDS_IPF_AD_1_PKT_LEN                        (1500)

/*ADQ�ڴ�Ԥ������*/
#define CDS_UL_RESV_LEN_FOR_PDU_HDR                 (4)

/*IPF AD���ȷֽ���ֵ*/
#define CDS_IPF_AD_LEN_THRESHOLD                    ((CDS_IPF_AD_0_PKT_LEN) + 1)

/*IPF BD����жϳ�ʱʱ��*/
#define CDS_IPF_BD_CMP_INT_TIMEOUT                  (648)

/*AD�����������С,ȡAD0��AD1�����ֵ*/
#define CDS_IPF_ULAD_DESC_SIZE                      (IPF_ULAD0_DESC_SIZE)

/*����ADQ�ձ�����ʱ������ֵ����������AD�������ڸ�ֵʱ������������ʱ��*/
#define CDS_IPF_ULAD_START_TMR_THRESHOLD            (CDS_IPF_ULAD_DESC_SIZE - 6)

/*AD�ձ�����ʱ��ʱ�����ݶ�Ϊ10ms*/
#define CDS_IPF_AD_EMPTY_PROTECT_TMR_LEN            (10)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
 ö����    : CDS_IPF_DL_FILTER_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����IP����ID
*****************************************************************************/
typedef enum CDS_IPF_DL_FILTER_ID
{
    CDS_IPF_DL_FITLER_ID_DHCP4 = 0,
    CDS_IPF_DL_FITLER_ID_DHCP6,
    CDS_IPF_DL_FITLER_ID_RS,
    CDS_IPF_DL_FITLER_ID_RA,
    CDS_IPF_DL_FITLER_ID_NS,
    CDS_IPF_DL_FITLER_ID_NA,
    CDS_IPF_DL_FITLER_ID_REDIRECT,
    CDS_IPF_DL_FITLER_ID_LL_PING6,          /*Link Local Ping V6*/
    CDS_IPF_DL_FITLER_ID_LL_FE80,           /*Link Local Addr*/
    CDS_IPF_DL_FITLER_ID_LL_FF,
    CDS_IPF_DL_FITLER_ID_BUTT
}CDS_IPF_DL_FILTER_ID_ENUM;

typedef VOS_UINT32  CDS_IPF_DL_FILTER_ID_ENUM_UINT32;


/*****************************************************************************
 ö����    : CDS_UL_IPF_RSLT_IPSEG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����IPF���˽����IP�ֶ���Ϣ
*****************************************************************************/
typedef enum CDS_UL_IPF_IPSEG_TYPE
{
    CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT   = 0,
    CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_HEAD,
    CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_MID,
    CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_TAIL,
    CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_BUTT
}CDS_UL_IPF_RSLT_IPSEG_TYPE_ENUM;

typedef VOS_UINT16   CDS_UL_IPF_RSLT_IPSEG_TYPE_ENUM_UINT16;


/*****************************************************************************
   5 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : IPF_RESULT
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ӳ��Ip���˵Ľ��
*****************************************************************************/
typedef struct IPF_RESULT
{
    VOS_UINT16                          usBearedId:6;
    VOS_UINT16                          usIpSegInfo:2;
    VOS_UINT16                          usUpperLayer:1;
    VOS_UINT16                          usIpType:1;
    VOS_UINT16                          usVerErr:1;
    VOS_UINT16                          usHdrLenErr:1;
    VOS_UINT16                          usPktLenNotEq:1;
    VOS_UINT16                          usPktLenErr:1;
    VOS_UINT16                          usBdCdNotEq:1;
    VOS_UINT16                          usResv:1;
}IPF_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : CDS_IPF_FILTER_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPF FILTER���нṹ��Ԥ�����й������ýṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulDownLinkUsedNum;
    IPF_FILTER_CONFIG_S             astDlFilter[CDS_IPF_MAX_DL_FILTER_NUM];
}CDS_IPF_FILTER_CFG_STRU;


/*****************************************************************************
 �ṹ��    : CDS_IPF_CTRL_ENTITY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPF����ʵ��
*****************************************************************************/
typedef struct CDS_IPF_CTRL_ENTITY
{
    HTIMER                              pstAdqEmptyProtTmr;                     /*ADQ�ձ�����ʱ��*/

    IPF_RD_DESC_S                       astUlRdBuff[IPF_ULRD_DESC_SIZE];        /*�궨����ڵ���ͷ�ļ��и���*/
    IPF_CONFIG_DLPARAM_S                astDlIpfCfgPara[IPF_DLBD_DESC_SIZE];    /*����IPF��������*/
    CDS_IPF_FILTER_CFG_STRU             stFilterCfgStru;                        /*���������ýṹ*/

    LUP_QUEUE_STRU                     *pstDlSduQue;                            /*����SDU�������*/
    LUP_QUEUE_STRU                     *pstDlSrcMemFreeQue;                     /*����Դ�ڴ��ͷŶ���*/

    IPF_AD_DESC_S                       astUlAdBuff[CDS_IPF_ULAD_DESC_SIZE];        /*����AD����������*/

}CDS_IPF_CTRL_ENTITY_STRU;
/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/
/*lint -e960*/
extern CDS_IPF_CTRL_ENTITY_STRU g_stCdsIpfCtrlEntity;
/*lint +e960*/


/*��ȡCDS IPF����ʵ��*/
#define CDS_GET_IPF_CTRL_ENTITY()          (&g_stCdsIpfCtrlEntity)

/*����RD����*/
#define CDS_GET_UL_RD_BUFF()               (g_stCdsIpfCtrlEntity.astUlRdBuff)

/*���ADQ�ձ�����ʱ��ָ��*/
#define CDS_GET_ADQ_EMPTY_TMR_PTR()        (g_stCdsIpfCtrlEntity.pstAdqEmptyProtTmr)

/*����SDU����*/
#define CDS_GET_IPF_DL_SDU_QUE()               (g_stCdsIpfCtrlEntity.pstDlSduQue)

/*����Դ�ڴ��ͷ�*/
#define CDS_IPF_DL_SRCMEM_FREE_QUE()       (g_stCdsIpfCtrlEntity.pstDlSrcMemFreeQue)

/*�������IPF���ò��������ַ*/
#define CDS_IPF_GET_DL_CFG_PARA_ARRAY()    (g_stCdsIpfCtrlEntity.astDlIpfCfgPara)

/*����IPF���������ַ*/
#define CDS_GET_DL_IPF_FILTER_ARRAY()      (&(g_stCdsIpfCtrlEntity.stFilterCfgStru.astDlFilter[0]))

/*����IPF����������*/
#define CDS_GET_DL_IPF_FILTER_NUM()        (g_stCdsIpfCtrlEntity.stFilterCfgStru.ulDownLinkUsedNum)

/*����IPF������*/
#define CDS_GET_DL_IPF_FILTER_PTR(ulFilterID)  (&(g_stCdsIpfCtrlEntity.stFilterCfgStru.astDlFilter[ulFilterID]))

/*Set IP Type*/
#define CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,Type)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltType = (Type)

/*����IP����һ��Э������*/
#define CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,Protocol) \
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltNhEn = PS_TRUE;\
           (pstFilter)->stMatchInfo.unNextHeader.u32Protocol = (Protocol)

/*Set Hi Port*/
#define CDS_DL_IPF_FILTER_SET_PORT_HI(pstFilter,usHiPort)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltRPortEn = PS_TRUE;\
           (pstFilter)->stMatchInfo.unDstPort.Bits.u16DstPortHi   = (usHiPort)

/*Set Low Port*/
#define CDS_DL_IPF_FILTER_SET_PORT_LOW(pstFilter,usLowPort)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltRPortEn = PS_TRUE;\
           (pstFilter)->stMatchInfo.unDstPort.Bits.u16DstPortLo   = (usLowPort)

/*Set ICMP Type*/
#define CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,Type)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltTypeEn  = PS_TRUE;\
           (pstFilter)->stMatchInfo.unFltCodeType.Bits.u16Type    = (Type)

/*Set ICMP Code*/
#define CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,Code)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltCodeEn  = PS_TRUE;\
           (pstFilter)->stMatchInfo.unFltCodeType.Bits.u16Code    = (Code)

/*Set Filter Priority*/
#define CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,Priority)\
           (pstFilter)->stMatchInfo.unFltChain.Bits.u16FltPri     = (Priority)

/*Set Dest Link Local Addr FE80*/
#define CDS_DL_IPF_FILTER_SET_DST_LL_ADDR_FE80(pstFilter)\
           (pstFilter)->stMatchInfo.u8DstAddr[0]  = 0xFE;\
           (pstFilter)->stMatchInfo.u8DstAddr[1]  = 0x80;\
           (pstFilter)->stMatchInfo.u8DstMsk[0]   = 0xFF;\
           (pstFilter)->stMatchInfo.u8DstMsk[1]   = 0xC0;\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltRAddrEn = PS_TRUE

/*Set Dest Link Local Addr FF*/
#define CDS_DL_IPF_FILTER_SET_DST_LL_ADDR_FF(pstFilter)\
           (pstFilter)->stMatchInfo.u8DstAddr[0]  = 0xFF;\
           (pstFilter)->stMatchInfo.u8DstMsk[0]   = 0xFF;\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltRAddrEn = PS_TRUE

/*Set DL IPF Filter Bearer ID*/
#define CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,BearerID)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltBid  = (BearerID)

/*Set Filter Enable*/
#define CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltEn   = PS_TRUE

/*����DL BD�����е��жϱ�־��λ*/
#define CDS_DL_BD_SET_ATTR_INT_FLG(usAttr)                  ((usAttr) = (usAttr) | 0x1)

/*����DL BD�����й�����ͨ������ͷ*/
#define CDS_DL_BD_SET_ATTR_WITH_FC_HDR(usAttr,ucFcHdr)      ((usAttr) = (ucFcHdr) << 4)

/*�����չ��������־������17bit����Ϊ0*/
#define CDS_DL_IPF_CLR_EX_FILTER_FLG(FilterId)              ((FilterId) = (FilterId) & 0x0000FFFF)

/*������չ��������־������17bit����Ϊ1*/
#define CDS_DL_IPF_SET_EX_FILTER_FLG(FilterId)              ((FilterId) = (FilterId) | 0x00010000)


/*****************************************************************************
  8 ��������
*****************************************************************************/
extern VOS_UINT32   CDS_IpfInit(VOS_VOID );
extern VOS_UINT32   CDS_EnableDlIPFFilter(VOS_UINT16  usModemId);
extern VOS_UINT32   CDS_DisableDlIPFFilter(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID     CDS_ConfigDlIPF(VOS_VOID);
extern TTF_MEM_ST*  CDS_AllocTtfMem(VOS_UINT32 ulLen);
extern VOS_UINT32   CDS_RxDlSdu(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID     CDS_AdqEmptyProctectTimeOutProc(VOS_VOID);
extern TTF_MEM_ST*  CDS_RdTransferTtfMem(const IPF_RD_DESC_S *pstRdDesc);


/*****************************************************************************
  9 OTHERS����
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

