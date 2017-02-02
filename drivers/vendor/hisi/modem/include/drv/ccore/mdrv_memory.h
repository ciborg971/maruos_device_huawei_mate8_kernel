
/*************************************************************************
*   ��Ȩ����(C) 1987-2011, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  mdrv_memory.h
*
*   ��    �� :  yangzhi
*
*   ��    �� :  ���ļ�����Ϊ"mdrv.h", ����V7R1�����Э��ջ֮���API�ӿ�ͳ��
*
*   �޸ļ�¼ :  2011��1��18��  v1.00  yangzhi����
*************************************************************************/

#ifndef __MDRV_CCORE_MEMORY_H__
#define __MDRV_CCORE_MEMORY_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <mdrv_memory_common.h>


typedef enum tagBSP_DDR_SECT_TYPE_E
{
    BSP_DDR_SECT_TYPE_TTF = 0x0,
    BSP_DDR_SECT_TYPE_ARMDSP,
    BSP_DDR_SECT_TYPE_UPA,
    BSP_DDR_SECT_TYPE_CQI,
    BSP_DDR_SECT_TYPE_APT,
    BSP_DDR_SECT_TYPE_ET,
    BSP_DDR_SECT_TYPE_BBPMASTER,
    BSP_DDR_SECT_TYPE_NV,
    BSP_DDR_SECT_TYPE_DICC,
    BSP_DDR_SECT_TYPE_WAN,
    BSP_DDR_SECT_TYPE_SHARE_MEM,
    BSP_DDR_SECT_TYPE_EXCP,
    BSP_DDR_SECT_TYPE_HIFI,
    BSP_DDR_SECT_TYPE_HARQ,
    BSP_DDR_SECT_TYPE_ZSP_UP,
    BSP_DDR_SECT_TYPE_HUTAF,
    BSP_DDR_SECT_TYPE_BBPSAMPLE,
    BSP_DDR_SECT_TYPE_TDS_LH2,
    BSP_DDR_SECT_TYPE_SOCP,
    BSP_DDR_SECT_TYPE_ECS_TEE,
    BSP_DDR_SECT_TYPE_MODEM_SR_STAMP,
    BSP_DDR_SECT_TYPE_BUTTOM
}BSP_DDR_SECT_TYPE_E;

typedef enum tagBSP_DDR_SECT_ATTR_E
{
    BSP_DDR_SECT_ATTR_CACHEABLE = 0x0,
    BSP_DDR_SECT_ATTR_NONCACHEABLE,
    BSP_DDR_SECT_ATTR_BUTTOM
}BSP_DDR_SECT_ATTR_E;

typedef enum tagBSP_DDR_SECT_PVADDR_E
{
    BSP_DDR_SECT_PVADDR_EQU = 0x0,
    BSP_DDR_SECT_PVADDR_NOT_EQU,
    BSP_DDR_SECT_PVADDR_BUTTOM
}BSP_DDR_SECT_PVADDR_E;


typedef struct tagBSP_DDR_SECT_QUERY_S
{
    BSP_DDR_SECT_TYPE_E     enSectType;
    BSP_DDR_SECT_ATTR_E     enSectAttr;
    BSP_DDR_SECT_PVADDR_E   enPVAddr;
    unsigned int                 ulSectSize;
}BSP_DDR_SECT_QUERY_S;

typedef struct tagBSP_DDR_SECT_INFO_S
{
    BSP_DDR_SECT_TYPE_E    enSectType;
    BSP_DDR_SECT_ATTR_E    enSectAttr;
    void *                 pSectVirtAddr;
    void *                 pSectPhysAddr;
    unsigned int           ulSectSize;
}BSP_DDR_SECT_INFO_S;


typedef enum tagBSP_AXI_SECT_TYPE_E
{
    BSP_AXI_SECT_TYPE_ACORE_DEEPSLEEP = 0x0,
    BSP_AXI_SECT_TYPE_FLASH_SEM,
    BSP_AXI_SECT_TYPE_IFC,
    BSP_AXI_SECT_TYPE_ICC,
    BSP_AXI_SECT_TYPE_MEMMGR_FLAG,
    BSP_AXI_SECT_TYPE_DYNAMIC,
    BSP_AXI_SECT_TYPE_SOFT_FLAG,
    BSP_AXI_SECT_TYPE_IPF,
    BSP_AXI_SECT_TYPE_TEMPERATURE,
    BSP_AXI_SECT_TYPE_ONOFF,
    BSP_AXI_SECT_TYPE_DICC,
    BSP_AXI_SECT_TYPE_HIFI,
    BSP_AXI_SECT_TYPE_DDR_CAPACITY,
    BSP_AXI_SECT_TYPE_PTABLE,
    BSP_AXI_SECT_TYPE_RESERVE,
    BSP_AXI_SECT_TYPE_DLOAD_AUTOINSTALL,
    BSP_AXI_SECT_TYPE_DLOAD,
    BSP_AXI_SECT_TYPE_CCORE_DEEPSLEEP ,
    BSP_AXI_SECT_TYPE_TTF_BBP,
    BSP_AXI_SECT_TYPE_BUTTOM
}BSP_AXI_SECT_TYPE_E;

/* ����������Ҫ��ѯ��MEM���� */
typedef enum tagBSP_DDR_TYPE_E
{
    BSP_DDR_TYPE_DDR_GU = 0x0,          /*DDR:GUԤ��*/
    BSP_DDR_TYPE_DDR_TLPHY_IMAGE,       /*DDR:TL DSP ����*/
    BSP_DDR_TYPE_DDR_LPHY_SDR,          /*DDR:SDRС������*/
    BSP_DDR_TYPE_DDR_TLPHY_LCS,         /*DDR:TL DSP LCS*/
    BSP_DDR_TYPE_DDR_TLPHY_BANDNV,      /*DDR:TL DSP BAND*/
    BSP_DDR_TYPE_DDR_TPHY_TABLE,        /*DDR:TL TDS TABLE*/
    BSP_DDR_TYPE_DDR_HIFI,              /*DDR:HIFI*/
#if defined(CHIP_BB_HI6210)
    BSP_DDR_TYPE_DDR_SOCP,              /*DDR:SOCP*/
#endif
    BSP_DDR_TYPE_SRAM_TLPHY,            /*SRAM:TL DSP*/
    BSP_DDR_TYPE_SRAM_RTT_SLEEP_FLAG,   /*SRAM:TL DSP˯�߻��ѱ��*/
    BSP_DDR_TYPE_SHM_TEMPERATURE,       /*�����ڴ�:�±�*/
    BSP_DDR_TYPE_SHM_BBE16_HIFI_HEAD,   /*�����ڴ�:BBE16->HIFI����ͷ*/
    BSP_DDR_TYPE_SHM_HIFI_BBE16_HEAD,   /*�����ڴ�:HIFI->BBE16����ͷ*/
    BSP_DDR_TYPE_SHM_BBE16_HIFI_QUEUE,  /*�����ڴ�:BBE16->HIFI�������*/
    BSP_DDR_TYPE_SHM_HIFI_BBE16_QUEUE,  /*�����ڴ�:HIFI->BBE16�������*/
    BSP_DDR_TYPE_SHM_TIMESTAMP,         /*DDR:LDSP LP*/
    BSP_DDR_TYPE_SHM_AFC_TEMPCOMP,      /*LPHY�±���Ƶƫ*/
    BSP_DDR_TYPE_SRAM_MAILBOX_PROTECT_FLG,   /*LPHY���䱣����־*/
    BSP_DDR_TYPE_SRAM_DSP_MNTN_INFO,    /*SRAM:DSP��ά�ɲ���Ϣ*/
    BSP_DDR_TYPE_SRAM_XMAILBOX_PROTECT_FLG,/*CPHY���䱣����־*/    
    BSP_DDR_TYPE_SRAM_CDSP_MNTN_INFO,    /*SRAM:CDSP��ά�ɲ���Ϣ*/

    BSP_DDR_TYPE_BUTTOM
}BSP_DDR_TYPE_E;


typedef struct tagBSP_AXI_SECT_INFO_S
{
    void *                      pSectVirtAddr;
    void *                      pSectPhysAddr;
    BSP_AXI_SECT_TYPE_E         enSectType;
    unsigned int                ulSectSize;
}BSP_AXI_SECT_INFO_S;

/*tlps use*/
typedef struct BSP_MEMADDR_INFO_S
{
    BSP_DDR_TYPE_E         mem_type;
    unsigned int           mem_base;
    unsigned int           mem_size;
}BSP_MEMADDR_INFO_S;

/*****************************************************************************
* �� �� ��  : mdrv_memcpy
*
* ��������  : ���ݿ����ӿڣ��ײ���ڻ��ʵ�ֵ����Ż��ӿڣ�ֻ������memory��
*             memory�Ŀ���
* Լ������  :
*             ֻ������memory ��memory�Ŀ�������������memory���Ĵ����Ŀ���
*             ��Ҫ4�ֽڶ���
*             ��A�� ARMv8 �ܹ��У���Ҫ8�ֽڶ��������normal memory ���ԣ�
*             ����ioremap_wcӳ��� uncachable ���ڴ� ����cachable���ڴ�
*
* �������  : dest :  ������Ŀ�ĵ�ַ
*             src  :  ������Դ��ַ
*             count:  �������ݵĴ�С
* �������  : ��
* �� �� ֵ  :  ��
****************************************************************************/
void * mdrv_memcpy(void * dest, const void * src, unsigned long count);

/*****************************************************************************
* �� �� ��  : mdrv_cachedmem_alloc
*
* ��������  :ΪDMA�豸������������һ��cache��ȫ���ڴ档
*
* �������  : bytes: ��Ҫ������ֽڵ�����
*
* �������  : ��
* �� �� ֵ  :  NULL :    �����ڴ�ʧ��
*            ��NULLָ��: �����ڴ�ɹ�����ָ��ָ�������ڴ���ָ��
****************************************************************************/
void* mdrv_cachedmem_alloc (unsigned int  bytes);

/*****************************************************************************
* �� �� ��  : mdrv_cachedmem_free
*
* ��������  :�ͷ���mdrv_cachedmem_alloc������ڴ档
*
* �������  : pBuf:ָ��Ҫ�ͷŵ��ڴ���ָ��
*
* �������  : ��
* �� �� ֵ  :  0: �ɹ�
*             -1: ʧ��
****************************************************************************/
int mdrv_cachedmem_free(void*  pBuf);

/*****************************************************************************
* �� �� ��  : mdrv_get_fix_ddr_addr
*
* ��������  :DDR�ڴ�β�ѯ�ӿڡ�
*
* �������  : pstSectQuery: ��Ҫ��ѯ�ڴ�ε����ԣ�����
*             pstSectInfo:  ��ѯ�����ڴ����Ϣ
*
* �������  : ��
* �� �� ֵ  :  ��
****************************************************************************/
int mdrv_get_fix_ddr_addr (BSP_DDR_SECT_QUERY_S *pstSectQuery, BSP_DDR_SECT_INFO_S *pstSectInfo);

/*****************************************************************************
* �� �� ��  : mdrv_get_fix_axi_addr
*
* ��������  :AXI�ڴ�β�ѯ�ӿڡ�
*
* �������  : enSectType: ��Ҫ��ѯ���ڴ������
*            pstSectInfo: ��ѯ�����ڴ����Ϣ
* �������  : ��
* �� �� ֵ  :  ��
****************************************************************************/
int mdrv_get_fix_axi_addr (BSP_AXI_SECT_TYPE_E enSectType,BSP_AXI_SECT_INFO_S *pstSectInfo);

/*****************************************************************************
* �� �� ��  : mdrv_smalloc
*
* ��������  :Ϊ����һ���ڴ档
*
* �������  : size: ��Ҫ������ֽڵ�����
*
* �������  : ��
* �� �� ֵ  :     NULL : �����ڴ�ʧ��
*            ��NULLָ��: �����ڴ�ɹ�����ָ��ָ�������ڴ���ָ��
****************************************************************************/
void* mdrv_smalloc (unsigned int size,MEM_POOL_TYPE flags);

/*****************************************************************************
* �� �� ��  : mdrv_sfree
*
* ��������  :�ͷ���mdrv_smalloc������ڴ档
*
* �������  : pBuf:ָ��Ҫ�ͷŵ��ڴ���ָ��
*
* �������  : ��
* �� �� ֵ  :  0: �ɹ�
*             -1: ʧ��
****************************************************************************/
int mdrv_sfree(void*  pBuf);
/*****************************************************************************
 �� �� ��  : mdrv_getmeminfo
 ��������  : ��ȡmem��ַ�ʹ�С��Ϣ
 �������  : enDdrType: ��Ҫ��ѯ��mem����
 �������  : addr ��ַ
             size ��С
 ����ֵ    ��0    ��ѯ�ɹ�
             -1   ��ѯʧ��
*****************************************************************************/
int mdrv_getmeminfo(BSP_DDR_TYPE_E enDdrType, unsigned int *addr, unsigned int *size);

/*****************************************************************************
 �� �� ��  : mdrv_get_freeblockmem
 ��������  : �ͷ�mem
 �������  : 
 �������  : 

 ����ֵ    ��0    �ɹ�
             -1   ʧ��
*****************************************************************************/
int mdrv_get_freeblockmem(void);

#ifdef __cplusplus
}
#endif
#endif
