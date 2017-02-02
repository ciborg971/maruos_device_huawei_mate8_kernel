#ifndef __MDRV_CCORE_IPF_H__
#define __MDRV_CCORE_IPF_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_ipf_comm.h"


typedef int (*BSP_IPF_WakeupUlCb)(void);
typedef int (*BSP_IPF_AdqEmptyUlCb)(IPF_ADQ_EMPTY_E eAdqEmpty);

/* BURST��󳤶� */
typedef enum tagIPF_BURST_E
{
    IPF_BURST_16,           /* BURST16 */
    IPF_BURST_8,            /* BURST8 */
    IPF_BURST_4,            /* BURST4 */
    IPF_BURST_MAX,          /* BURST4 ���Ĵ���һ�� */
}IPF_BURST_E;

typedef struct tagIPF_COMMON_PARA_S
{
    int bAdReport;
    int bMultiModeEn;
    int bMultiFilterChainEn;
	int bEspSpiDisable;
	int bAhSpiDisable;
	int bEspAhSel;
    int bIpv6NextHdSel;
    IPF_BURST_E eMaxBurst;
    int bSpWrrModeSel;
    int bSpPriSel;
    int bFltAddrReverse;
    int bFilterSeq;
} IPF_COMMON_PARA_S;

/* ͨ�����ƽṹ�� */
typedef struct tagIPF_CHL_CTRL_S
{
	int bDataChain;
	int bEndian;
	IPF_MODE_E eIpfMode;
    unsigned int u32WrrValue;
} IPF_CHL_CTRL_S;

typedef struct tagIPF_MATCH_INFO_S{
    unsigned char u8SrcAddr[16];
    unsigned char u8DstAddr[16];
    unsigned char u8DstMsk[16];
    union{
        struct{
        	unsigned int u16SrcPortLo:16;
        	unsigned int u16SrcPortHi:16;
        }Bits;
	    unsigned int u32SrcPort;
    } unSrcPort;
    union{
        struct
        {
            unsigned int u16DstPortLo:16;
        	unsigned int u16DstPortHi:16;
        }Bits;
    	unsigned int u32DstPort;
    } unDstPort;
    union{
        struct
        {
            unsigned int u8TrafficClass:8;
        	unsigned int u8TrafficClassMask:8;
        	unsigned int u16Reserve:16;
        }Bits;
    	unsigned int u32TrafficClass;
    }unTrafficClass;
    unsigned int u32LocalAddressMsk;
    union{
    	unsigned int u32NextHeader;
    	unsigned int u32Protocol;
    }unNextHeader;
    unsigned int u32FlowLable;
    union{
        struct{
            unsigned int u16Type:16;
        	unsigned int u16Code:16;
        }Bits;
    	unsigned int u32CodeType;
    } unFltCodeType;
    union{
        struct{
            unsigned int u16NextIndex:16;
        	unsigned int u16FltPri:16;
        }Bits;
    	unsigned int u32FltChain;
    } unFltChain;
    unsigned int u32FltSpi;
    union{
    	struct{
    		unsigned int FltEn:1;
    		unsigned int FltType:1;
    		unsigned int Resv1:2;
            unsigned int FltSpiEn:1;
            unsigned int FltCodeEn:1;
            unsigned int FltTypeEn:1;
            unsigned int FltFlEn:1;
            unsigned int FltNhEn:1;
            unsigned int FltTosEn:1;
            unsigned int FltRPortEn:1;
            unsigned int FltLPortEn:1;
            unsigned int FltRAddrEn:1;
            unsigned int FltLAddrEn:1;
            unsigned int Resv2:2;
            unsigned int FltBid:6;
            unsigned int Resv3:10;
    	}Bits;
    	unsigned int u32FltRuleCtrl;
    }unFltRuleCtrl;
}IPF_MATCH_INFO_S;

typedef struct tagIPF_FILTER_CONFIG_S
{
    unsigned int u32FilterID;
    IPF_MATCH_INFO_S stMatchInfo;
} IPF_FILTER_CONFIG_S;


/*****************************************************************************
* �� �� ��  : mdrv_ipf_init
*
* ��������  : ����IPFӲ����������
*
* �������  : IPF_COMMON_PARA_S *pstCommPara  ���������ṹ��ָ��
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_INVALID_PARA ���������Ч
*             IPF_NOT_INITIALIZED IPFģ��δ��ʼ��
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_init(IPF_COMMON_PARA_S *pstCommPara);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_config_ulchan
*
* ��������  : ����IPF����ͨ�����ƼĴ�������
*
* �������  : IPF_CHL_CTRL_S *pstCtrl ͨ�����ƼĴ������ò���
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_INVALID_PARA ���������Ч
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_config_ulchan(IPF_CHL_CTRL_S *pstCtrl);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_config_dlchan
*
* ��������  : ����IPF����ͨ�����ƼĴ�������
*
* �������  : IPF_CHL_CTRL_S *pstCtrl ͨ�����ƼĴ������ò���
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_INVALID_PARA ���������Ч
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_config_dlchan (IPF_CHL_CTRL_S *pstCtrl);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_set_filter
*
* ��������  : ����IP������
*
* �������  : IPF_FILTER_CHAIN_TYPE_E eFilterChainhead �����õļĴ������׵�ַ
*             IPF_FILTER_CONFIG_S *pstFilterInfo       Filter���ýṹ��ָ��
*             unsigned int u32FilterNum                     Filter����
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_INVALID_PARA ���������Ч
*             IPF_NOT_INITIALIZED IPFģ��δ��ʼ��
*             IPF_FILTER_NOT_ENOUGH IPF��������Ŀ����
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_set_filter (IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, IPF_FILTER_CONFIG_S *pstFilterInfo, unsigned int u32FilterNum);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_get_filter
*
* ��������  : ��ѯFilter����
*
* �������  : IPF_FILTER_CHAIN_TYPE_E eFilterChainhead  �Ĵ������׵�ַ
*             unsigned int u32FilterID                       Filter ID��
*             IPF_FILTER_CONFIG_S *pstFilterInfo        Filter��Ϣ�ṹ��ָ��
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_INVALID_PARA ���������Ч
*             IPF_NOT_INITIALIZED IPFģ��δ��ʼ��
*             IPF_ERROR û�в鵽Filter ID��Ӧ�Ĺ��˹���
* ����˵��  : �˽ӿ�ֻ֧�ֲ�ѯ����Filter����ֵ��u32FilterIDָPS���ù��˹���ʱʹ�õ�ID�ţ���Ӳ���Ĵ�����ID��һһ��Ӧ�����ǲ�һ����ȣ������ά�����Ӧ��ϵ
*
*****************************************************************************/
int mdrv_ipf_get_filter (IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, unsigned int u32FilterID, IPF_FILTER_CONFIG_S *pstFilterInfo);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_config_timeout
*
* ��������  : ����IPFͨ����ʱ����
*
* �������  : unsigned int u32Timeout  �����õ��жϳ�ʱʱ�䣬��λ��256��ʱ�����ڣ���65ԼΪ0.1ms����648ԼΪ1ms
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_INVALID_PARA ���������Ч
* ����˵��  : ��������ķ�Χ��1~ 0xffff�������ö�������ͨ��ͬʱ��Ч
*
*****************************************************************************/
int mdrv_ipf_config_timeout(unsigned int u32Timeout);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_config_dlbd
*
* ��������  : �����������ݰ�
*
* �������  : unsigned int u32Num  ��Ҫ���õ�BD��Ŀ
*             IPF_CONFIG_DLPARA_S* pstDlPara ���ò����ṹ������ָ��
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_ERROR ����ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_config_dlbd(unsigned int u32Num, IPF_CONFIG_DLPARAM_S* pstDlPara);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_enable_chan
*
* ��������  : ʹ�ܻ�λIP������������ͨ��
*
* �������  : IPF_CHANNEL_TYPE_E eChanType ������ͨ����ʶ
*             int bFlag ʹ�ܸ�λ��ʶ��BSP_TRUE��ʹ�ܣ�BSP_FALSE����λ
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_ERROR ����ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_enable_chan (IPF_CHANNEL_TYPE_E eChanType, int bFlag);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_get_dlbd_num
*
* ��������  : ��ȡ���п������õ�BD��CD����Ŀ
*
* �������  : unsigned int* pu32CDNum  ���صĿ������õ�CD����Ŀ
* �������  :
*
* �� �� ֵ  : ���п��е�BD��Ŀ��ΧΪ0 ~ BD_DESC_SIZE������CD��Ŀ��ΧΪ0~1023
*
* ����˵��  :
*
*****************************************************************************/
unsigned int mdrv_ipf_get_dlbd_num (unsigned int* pu32CDNum);
/*****************************************************************************
* �� �� ��  : mdrv_ipf_get_ulrd
*
* ��������  : ��ȡ����RD
*
* �������  : unsigned int* pu32Num  ������Է��ص�����RD��Ŀ/���ʵ�ʷ��ص�RD��Ŀ
*             IPF_RD_DESC_S *pstRd  RD�������ṹ���׵�ַ
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
void mdrv_ipf_get_ulrd (unsigned int* pu32Num, IPF_RD_DESC_S *pstRd);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_config_adthred
*
* ��������  : �ṩ���ֳ��̰��ķֽ緧ֵ
*
* �������  : unsigned int u32UlADThr ����ͨ�����̰��ķֽ緧ֵ
              unsigned int u32DlADThr ����ͨ�����̰��ķֽ緧ֵ
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_INVALID_PARA ���������Ч
*             IPF_NOT_INITIALIZED IPFģ��δ��ʼ��
*
* ����˵��  : ��������øýӿڣ�AD���е�ʹ��404��448Ϊ������ͨ���ĳ��̰���ֵ��Ĭ��ֵ��
*
*****************************************************************************/
int mdrv_ipf_config_adthred (unsigned int u32UlADThr, unsigned int u32DlADThr);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_config_ulad
*
* ��������  : �����е�AD�����µ��ڴ滺����
*
* �������  : IPF_AD_TYPE_E eAdType   AD���кţ�0���̰����У���1���������У�
*             unsigned int u32AdNum    ��Ҫ���õĵ�AD��Ŀ
*             IPF_AD_DESC_S *pstAdDesc ����ռ��Ӧ�����ݽṹ�׵�ַ
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_INVALID_PARA ���������Ч
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_config_ulad(IPF_AD_TYPE_E eAdType, unsigned int u32AdNum, IPF_AD_DESC_S *pstAdDesc);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_get_ulad_num
*
* ��������  : ��ȡ���У�C�ˣ����У�ָ��Ļ������Ѿ���ʹ�ã�AD��Ŀ
*
* �������  : unsigned int* pu32AD0Num  ���ؿ��е�AD0����Ŀ
*             unsigned int* pu32AD1Num  ���ؿ��е�AD1����Ŀ
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_INVALID_PARA ���������Ч
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_get_ulad_num (unsigned int* pu32AD0Num,unsigned int* pu32AD1Num);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_set_pktlen
*
* ��������  : �趨�����������������Сֵ
*
* �������  : unsigned int u32MaxLen  ���ݰ���󳤶�
*             unsigned int u32MinLen  ���ݰ���С����
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_set_pktlen (unsigned int u32MaxLen, unsigned int u32MinLen);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_get_dlstateidle
*
* ��������  : ����ͨ���Ƿ�Ϊ����
*
* �������  :
* �������  :
*
* �� �� ֵ  :IPF_SUCCESS ����
*            IPF_ERROR   �ǿ���
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_get_dlstateidle(void);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_set_dbuf_para
*
* ��������  : ����Դ���ݸ�ʽ��Ϣ
*
* �������  : bufoffset pData��Աƫ��
*             lenoffset usUsed��Աƫ��
*             nextoffset pNext��Աƫ��
* �������  :
*
* �� �� ֵ  : 0 ��ȷ
*             -1 ����
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_set_dbuf_para(unsigned int bufoffset,unsigned int lenoffset, unsigned int nextoffset);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_set_limit_addr
*
* ��������  : ��������ʱGU��ccore������ʵĵ�ַ
*
* �������  : start GU��ccore������ʵĿ�ʼ��ַ
			  end 	GU��ccore������ʵĿ�ʼ��ַ
* �������  :
*
* �� �� ֵ  : 0 ��ȷ
*             -1 ����
* ����˵��  : 
*
*****************************************************************************/
int mdrv_ipf_set_limited_addr(unsigned int start, unsigned int end);


#ifdef __cplusplus
}
#endif
#endif
