
/*************************************************************************
*   ��Ȩ����(C) 1987-2011, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  mdrv_version.h
*
*   ��    �� :  yangzhi
*
*   ��    �� :  ���ļ�����Ϊ"mdrv.h", ����V7R1�����Э��ջ֮���API�ӿ�ͳ��
*
*   �޸ļ�¼ :  2011��1��18��  v1.00  yangzhi����
*************************************************************************/

#ifndef __MDRV_CCORE_VERSION_H__
#define __MDRV_CCORE_VERSION_H__
#ifdef __cplusplus
extern "C"
{
#endif




typedef enum{
     PROTOCOL_TYPE_LTE_ONLY    = 0,
     PROTOCOL_TYPE_GUL
}PROTOCOL_TYPE_E;



typedef enum{
	 BOARD_TYPE_BBIT    = 0,
	 BOARD_TYPE_SFT,
	 BOARD_TYPE_ASIC,
	 BOARD_TYPE_MAX
}BOARD_ACTUAL_TYPE_E;


typedef enum{
     PV500_CHIP             = 0,
     V7R1_CHIP              = 1,
     PV500_PILOT_CHIP,
     V7R1_PILOT_CHIP,
     V7R2_CHIP              =5,
     V8R1_PILOT_CHIP        = 0x8,

}BSP_CHIP_TYPE_E;

typedef struct  tagMPRODUCT_INFO_S
{
	unsigned char *  productname;  /*оƬ���� */ /* BSP*/
	unsigned int   productnamelen;
	BSP_CHIP_TYPE_E echiptype;  /* PV500_CHIP V7R1_CHIP? */
	PROTOCOL_TYPE_E  eprotype;  /* GUL,ONLY LTE ? */
	unsigned int  platforminfo ;     /* FPGA ASIC?*/
	BOARD_ACTUAL_TYPE_E eboardatype;   /*BBIT SFT ASIC FOR */
} MPRODUCT_INFO_S;

#define BUILD_DATE_LEN  12
#define BUILD_TIME_LEN  12

/* оƬModem ������汾��Ϣ*/
typedef  struct  tagMSW_VER_INFO_S
{
	unsigned short  ulVVerNO;
	unsigned short  ulRVerNO;
	unsigned short  ulCVerNO;
	unsigned short  ulBVerNO;
	unsigned short  ulSpcNO;
	unsigned short  ulCustomNOv;
	unsigned int  ulProductNo;
	unsigned char  acBuildDate[BUILD_DATE_LEN];
	unsigned char  acBuildTime[BUILD_TIME_LEN];
} MSW_VER_INFO_S;

typedef  struct  tagMHW_VER_INFO_S
{
	int  hwindex;  /* HKADC��⵽��Ӳ��ID��(�弶��*/
	unsigned int  hwidsub;  /* HKADC��⵽���Ӱ汾��*/
	unsigned char *  hwfullver;  /* Ӳ���汾��Ϣ MBBʹ�� */
	unsigned int  hwfullverlen;
	unsigned char *  hwname;  /* �ⲿ��Ʒ����  MBBʹ�� CPE? */
	unsigned int  hwnamelen;
	unsigned char *  hwinname;  /* �ڲ���Ʒ����  MBBʹ��*/
	unsigned int  hwinnamelen;  
} MHW_VER_INFO_S;


typedef struct  tagMODEM_VER_INFO_S
{
	MPRODUCT_INFO_S  stproductinfo;
	MSW_VER_INFO_S  stswverinfo;
	MHW_VER_INFO_S  sthwverinfo;
} MODEM_VER_INFO_S;


typedef enum
{
	VER_BOOTLOAD = 0,
	VER_BOOTROM = 1,
	VER_NV = 2,
	VER_VXWORKS = 3,
	VER_DSP = 4,
	VER_PRODUCT_ID = 5,
	VER_WBBP = 6,
	VER_PS = 7,
	VER_OAM = 8,
	VER_GBBP = 9,
	VER_SOC = 10,
	VER_HARDWARE = 11,
	VER_SOFTWARE = 12,
	VER_MEDIA = 13,
	VER_APP = 14,
	VER_ASIC = 15,
	VER_RF = 16,
	VER_PMU = 17,
	VER_PDM = 18,
	VER_PRODUCT_INNER_ID = 19,
	VER_INFO_NUM = 20
} COMP_TYPE_E;

/*memVersionCtrl�ӿڲ�������*/
#define VERIONREADMODE                  0
#define VERIONWRITEMODE                 1

/*****************************************************************************
 �� �� ��  : mdrv_ver_get_memberinfo
 ��������  : ��ѯ��������İ汾�š�
 �������  : ppVersionInfo��������İ汾��Ϣ��ַ��
 �������  : ucLength�������ص����ݵ��ֽ�����
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
int mdrv_ver_get_memberinfo(void ** ppVersionInfo, unsigned int * ulLength);


/*****************************************************************************
 �� �� ��  : mdrv_ver_memberctrl
 ��������  : ����汾��д�ӿڡ�
 �������  : pcData����ModeΪ����ʱ��Ϊ�����ߴ����淵�ص�����汾��Ϣ���ڴ��ַ��
                     ��ModeΪд��ʱ��Ϊ������׼��д�������汾��Ϣ�ĵ�ַ��
             ucLength����ModeΪ����ʱ��Ϊ�����ߴ����淵�ص�����汾��Ϣ���ڴ��С��
                       ��ModeΪд��ʱ��Ϊ������׼��д�������汾��Ϣ���ַ�����������'\0'����
             ucType���汾��ϢID��
             ucMode��0����ȡָ��ID������汾��Ϣ��1��д��ָ��ID������汾��Ϣ��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
int mdrv_ver_memberctrl(signed char *pcData, unsigned char ucLength, COMP_TYPE_E ucType, unsigned char ucMode);


/*****************************************************************************
 �� �� ��  : mdrv_ver_get_info
 ��������  : ����modem�汾��Ϣ
 �������  :
 �������  :
 �� �� ֵ  : Modem �汾��Ϣ
****************************************************************************/
const MODEM_VER_INFO_S * mdrv_ver_get_info(void);


/*****************************************************************************
 �� �� ��  : mdrv_ver_init_platform
 ��������  : ��ʼ��оƬ�İ汾��
 �������  : ��
 �������  : none
 �� �� ֵ  : void
*****************************************************************************/
void mdrv_ver_init_platform(void);


#ifdef __cplusplus
}
#endif

#endif
