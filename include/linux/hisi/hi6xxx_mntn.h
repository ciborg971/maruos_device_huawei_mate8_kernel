/****************************************************************************
  �� �� ��   : hi6xxx_mntn.h
  �� �� ��   : ����
  ��    ��   : liuyi
  ��������   : 2014��11��1��
  ����޸�   :
  ��������   : ������ά�ɲ�ģ��ͷ�ļ�
  ע������   ��������������������������
               ���ļ�ΪBSP.h �ı���
			   �޸ĸ��ļ�ʱע��ͬ���޸�
			   ������������������������
*****************************************************************************/

/*�޸Ĵ��ļ�Ҫͬʱ�޸� BSP.h*/

/*liuyi++ temp*/
#ifndef __HI6XXX_MNTN_H__
#define __HI6XXX_MNTN_H__
/*liuyi-- temp*/
#ifdef __cplusplus
extern "C"
{
#endif

/*BSP_MODULE_E��BSP.h��һ��copy����ע��ͬ���޸� begin*/
/* ����ģ��ö�ٶ��� */
typedef enum tagBSP_MODULE_E
{
    BSP_MODU_NANDF = 0x0, /* 0x0 */
    BSP_MODU_TIMER, /* 0x1 */
    BSP_MODU_VIC,   /* 0x2 */
    BSP_MODU_UART,  /* 0x3 */
    BSP_MODU_YAFFS, /* 0x4 */
    BSP_MODU_ETH,   /* 0x5 */
    BSP_MODU_DMAC,  /* 0x6 */
    BSP_MODU_SPI,   /* 0x7 */
    BSP_MODU_GPIO,  /* 0x8 */
    BSP_MODU_WDT,   /* 0x9 */
    BSP_MODU_SCI,   /* 0xA */
    BSP_MODU_USB,   /* 0xB */
    BSP_MODU_DRX,   /* 0xC */
    BSP_MODU_SDIO,  /* 0xD */
    BSP_MODU_FTP,   /* 0xE */
    BSP_MODU_GMAC,      /* 0xF */
    BSP_MODU_SEEKER,    /* 0x10 */
    BSP_MODU_UPGRADE,   /* 0x11 */
    BSP_MODU_AXI,       /* 0x12 */
    BSP_MODU_NET,       /* 0x13 */
    BSP_MODU_USB_ACM,   /* 0x14 */
    BSP_MODU_USB_NCM,   /* 0x15 */
    BSP_MODU_AXI_MONITOR,
    BSP_MODU_IFC,
    BSP_MODU_ICC,
    BSP_MODU_IPF,
    BSP_MODU_ACC,       /* 0x1A */
    BSP_MODU_BBP,
    BSP_MODU_MEM,
    BSP_MODU_UDI,
    BSP_MODU_DLOAD,
    BSP_MODU_SOCP,
    BSP_MODU_IFCP,      /* 0x20 */
    BSP_MODU_PWRCTRL,
    BSP_MODU_SERIAL_UPGRADE,
    BSP_MODU_SYNC,
    BSP_MODU_IPC,
    BSP_MODU_MNTN,
    BSP_MODU_SSI,
    BSP_MODU_HKADC,
    BSP_MODU_PMU,
    BSP_MODU_HIFI,      /*0x29*/
    BSP_MODU_AUDIO,
    BSP_MODU_CHGC,
    BSP_MODU_MAILBOX,
    BSP_MODU_SLAVE,
    BSP_MODU_MIPI,
    BSP_MODU_SKU,
    BSP_MODU_THERMAL,   /*�±�ģ��*/
    BSP_MODU_MBX,
    BSP_MODU_DORESET,
    BSP_MODU_EDMA,      /*0x33*/
	BSP_MODU_WM8990,	/*wm8990ģ��*/
    BSP_MODU_LED,		/*LEDģ��*/
    BSP_MODU_ABB,		/*ABBģ��*/
	BSP_MODU_RFILE,
	BSP_MODU_SSDMA,     /*��ȫģ��*/
	BSP_MODU_OSAL,
	BSP_MODU_TUNER,
	BSP_MODU_BBE,
    BSP_MODU_CIPHER,
	BSP_MODU_RST,
	BSP_MODU_EMMC,
	/*�¼�ģ�����β�˿�ʼ��ͬʱ����ı��ϱ߸�ģ���λ��*/
    BSP_MODU_ALL,       /* �������е�ģ�� */
    BSP_MODU_MAX        /* �߽�ֵ */
} BSP_MODULE_E;

#define  BSP_MNTN_CACHE_FLUSH   0x8765abcd
/*BSP_MODULE_E��BSP.h��һ��copy����ע��ͬ���޸� end*/

#ifdef __cplusplus
}
#endif

#endif
