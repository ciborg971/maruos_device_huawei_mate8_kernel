#ifndef __MDRV_CCORE_STUB_V8_H__
#define __MDRV_CCORE_STUB_V8_H__
#ifdef __cplusplus
extern "C"
{
#endif

static inline unsigned int DRV_PWRCTRL_STANDBYSTATECCPU(unsigned int ulStandbyTime, unsigned int ulSwitchtime)
{
    return 0;
}

static inline unsigned int DRV_ABB_WRX_CTRL(unsigned char ucStatus)
{
    return 0;
}

static inline void DRV_RF_LDODOWN(unsigned int enRfID)
{
    return;
}

static inline unsigned long DRV_GET_WCDMA_PLL_STATUS(void)
{
    return 1;
}

static inline unsigned long DRV_GET_GSM_PLL_STATUS(void)
{
    return 0;
}

static inline unsigned long DRV_GET_DSP_PLL_STATUS(void)
{
    return 0;
}
static inline int DRV_GET_ARM_PLL_STATUS(void)
{
    return 0;
}

/*one track �ӿڹ�һ��Ŀ����nv���ݻָ��ӿڣ�����om NV��һ����*/
#if 1
/* Begin: DRVΪOAMʵ��NV���ݻָ����̶��ṩ�Ľӿ� */


extern int DRV_UPGRADE_NV_SET_RESULT(int status);


extern int DRV_NV_FILE_SEC_CHECK(char * pnvFilePath);


extern int BSP_DLOAD_NVBackupRead(unsigned char *pRamAddr, unsigned int len);
#define DRV_NVBACKUP_READ(pRamAddr,len)    BSP_DLOAD_NVBackupRead(pRamAddr, len)


extern int BSP_DLOAD_NVBackupWrite(unsigned char *pRamAddr, unsigned int len);
#define DRV_NVBACKUP_WRITE(pRamAddr, len)   BSP_DLOAD_NVBackupWrite(pRamAddr, len)


extern int DRV_NVBACKUP_EXT_READ(unsigned char *pRamAddr, unsigned int len);


extern int DRV_NVBACKUP_EXT_WRITE(unsigned char *pRamAddr, unsigned int len);
/* End: DRVΪOAMʵ��NV���ݻָ����̶��ṩ�Ľӿ� */

extern int NVBackupFlashDataExtWrite(unsigned char* pRamAddr, unsigned int offset,unsigned int len);
#define DRV_NV_FLASH_EXT_WRITE(pRamAddr, offset,len) NVBackupFlashDataExtWrite(pRamAddr, offset,len)


extern int NVBackupFlashDataWrite(unsigned char* pRamAddr, unsigned int offset,unsigned int len);
#define DRV_NV_FLASH_WRITE(pRamAddr, offset,len) NVBackupFlashDataWrite(pRamAddr, offset,len)


/*sd*/
/*SD���豸����*/
typedef struct _sd_dev_type_str
{
    unsigned int   devNameLen;
    char            devName[16];
}SD_DEV_TYPE_STR;

static inline SD_DEV_TYPE_STR * DRV_GET_SD_PATH(void)
{
    return 0;
}

/*****************************************************************************
 * �� �� ��  : DRV_GET_CDROM_VERSION
 *
 * ��������  : ��ȡ��̨�汾���ַ���
 *
 * �������  : s8 *str   :�ַ���������
 *             int len   :�ַ�������
 * �������  : s8 *str   :�ַ���������
 *
 * �� �� ֵ  : DLOAD_ERROR   :��������Ƿ�
 *             ����          :�����ַ�������
 *
 * ����˵��  : ATģ�����
 *             ����ģʽ֧��
 *             ����ģʽ֧��
 *****************************************************************************/
static inline int DRV_GET_CDROM_VERSION(char *pVersionInfo,unsigned int ulLength)
{
        return 0;
}


#endif

/* ����ģʽö�� */
typedef enum tagDLOAD_MODE_E
{
    DLOAD_MODE_DOWNLOAD = 0,
    DLOAD_MODE_NORMAL,
    DLOAD_MODE_DATA,
    DLOAD_MODE_MAX
}DLOAD_MODE_E;

static inline int DRV_GET_DLOAD_INFO(unsigned char atCmdBuf[], unsigned int dloadType)
{
    return 0;
}

static inline int DRV_SET_UPDATA_FLAG(int flag)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : DRV_GET_DLOAD_VERSION
 ��������  : Get dload version
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
static inline int DRV_GET_DLOAD_VERSION(unsigned char *str, int len)
{
    return 0;
}

static inline int DRV_GET_AUTHORITY_VERSION(unsigned char *str, unsigned int len)
{
    return 0;
}

static inline int DRV_GET_AUTHORITY_ID(unsigned char *buf, unsigned int len)
{
    return 0;
}

static inline unsigned int DRV_SDMMC_USB_STATUS(void)
{
    return 0;
}

#if 1  /*ԭdrv_wifi.h*/
/*****************************************************************************
 �� �� ��  : DRV_AT_GET_USER_EXIST_FLAG
 ��������  : ���ص�ǰ�Ƿ���USB���ӻ���WIFI�û�����(C�˵���)
 �������  : ��
 �������  : ��
 �� �� ֵ  : 1 : ��
             0 : ��
*****************************************************************************/
extern unsigned int  DRV_AT_GET_USER_EXIST_FLAG(void);


unsigned int USB_ETH_DrvSetHostAssembleParam(unsigned int ulHostOUtTimeout);
unsigned int USB_ETH_DrvSetDeviceAssembleParam(unsigned int ulEthTxMinNum,
                                                unsigned int ulEthTxTimeout,
                                                unsigned int ulEthRxMinNum,
                                                unsigned int ulEthRxTimeout);
#endif

/*****************************************************************************
* �� �� ��  : BSP_HwIsSupportWifi
* ��������  : ��ӡӲ���汾��Ϣ,��׮
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
* ����˵��  : ��
*****************************************************************************/
int BSP_HwIsSupportWifi(void);

/*************************************************
 �� �� ��   : BSP_MNTN_ProductTypeGet
 ��������   : ���ص�ǰ��Ʒ����
 �������   : ��
 �������   : ��
 �� �� ֵ   :0:STICK
             1:MOD
             2:E5
             3:CPE
*************************************************/
extern unsigned int BSP_MNTN_ProductTypeGet(void);
#define DRV_PRODUCT_TYPE_GET()   BSP_MNTN_ProductTypeGet()

#if 1 /*drv_usb.h*/
/* MODEM �ܽ��źŽṹ�嶨��*/
typedef struct tagMODEM_MSC_STRU
{
    unsigned int OP_Dtr     :    1;          /*DTR CHANGE FLAG*/
    unsigned int OP_Dsr     :    1;          /*DSR CHANGE FLAG*/
    unsigned int OP_Cts     :    1;          /*CTSCHANGE FLAG*/
    unsigned int OP_Rts     :    1;          /*RTS CHANGE FLAG*/
    unsigned int OP_Ri      :    1;          /*RI CHANGE FLAG*/
    unsigned int OP_Dcd     :    1;          /*DCD CHANGE FLAG*/
    unsigned int OP_Fc      :    1;          /*FC CHANGE FLAG*/
    unsigned int OP_Brk     :    1;          /*BRK CHANGE FLAG*/
    unsigned int OP_Spare   :    24;         /*reserve*/
    unsigned char   ucDtr;                     /*DTR  VALUE*/
    unsigned char   ucDsr;                     /*DSR  VALUE*/
    unsigned char   ucCts;                     /*DTS VALUE*/
    unsigned char   ucRts;                     /*RTS  VALUE*/
    unsigned char   ucRi;                      /*RI VALUE*/
    unsigned char   ucDcd;                     /*DCD  VALUE*/
    unsigned char   ucFc;                      /*FC  VALUE*/
    unsigned char   ucBrk;                     /*BRK  VALUE*/
    unsigned char   ucBrkLen;                  /*BRKLEN VALUE*/
} MODEM_MSC_STRU, *PMODEM_MSC_STRU,AT_DCE_MSC_STRU;


typedef unsigned int (*MNTN_ERRLOGREGFUN)(char * cFileName,unsigned int ulFileId, unsigned int ulLine,
                unsigned int ulErrNo, void * pBuf, unsigned int ulLen);

/*****************************************************************************
 �� �� ��  : BSP_USB_GetDiagModeValue
 ��������  : ����豸���͡�
 �������  : �ޡ�
 �������  : ucDialmode:  0 - ʹ��Modem����; 1 - ʹ��NDIS����; 2 - Modem��NDIS����
              ucCdcSpec:   0 - Modem/NDIS������CDC�淶; 1 - Modem����CDC�淶;
                           2 - NDIS����CDC�淶;         3 - Modem/NDIS������CDC�淶
 �� �� ֵ  : VOS_OK/VOS_ERR
*****************************************************************************/
extern int BSP_USB_GetDiagModeValue(unsigned char *pucDialmode,
                             unsigned char *pucCdcSpec);
#define DRV_GET_DIAG_MODE_VALUE(pucDialmode, pucCdcSpec)    \
                             BSP_USB_GetDiagModeValue(pucDialmode, pucCdcSpec)

/*****************************************************************************
 �� �� ��  : BSP_USB_GetU2diagDefaultValue
 ��������  : ��ö˿�Ĭ��u2diagֵ
 �������  : �ޡ�
 �������  : �ޡ�
 ����ֵ��   u2diagֵ

*****************************************************************************/
extern unsigned int BSP_USB_GetU2diagDefaultValue(void);
#define DRV_GET_U2DIAG_DEFVALUE()    BSP_USB_GetU2diagDefaultValue()


/*extern void ErrlogRegFunc(MNTN_ERRLOGREGFUN pRegFunc);
 */
extern void MNTN_ERRLOG_REG_FUNC(MNTN_ERRLOGREGFUN pRegFunc);

/*****************************************************************************
* �� �� ��  : DRV_DSP_AHB_RESET_CANCEL
* ��������  : ZSP AHB���߽⸴λ
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
* ����˵��  : ��
*****************************************************************************/
extern void DRV_DSP_AHB_RESET_CANCEL(void);

/*****************************************************************************
 �� �� ��  : BSP_USB_UdiagValueCheck
 ��������  : ���ӿ����ڼ��NV����USB��ֵ̬�ĺϷ���.
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0��OK��
            -1��ERROR
*****************************************************************************/
extern int BSP_USB_UdiagValueCheck(unsigned int DiagValue);
#define DRV_UDIAG_VALUE_CHECK(DiagValue)     BSP_USB_UdiagValueCheck(DiagValue)
#define DRV_U2DIAG_VALUE_CHECK(DiagValue)     BSP_USB_UdiagValueCheck(DiagValue)

/********************************************************
����˵���� ���ص�ǰ�豸�б���֧��(sel=1)���߲�֧��(sel=0)PCSC���豸��ֵ̬
��������:
���������sel
          0: ͨ������dev_type���ص�ǰ����PCSC���豸��ֵ̬
          1��ͨ������dev_type���ص�ǰ��PCSC���豸��ֵ̬
���������dev_type д����Ҫ���豸��ֵ̬�����û����д��ֵ��
          NV�д洢���豸��ֵ̬
���������pulDevType ��ulCurDevType��Ӧ���豸��ֵ̬�����û�з���ֵ1��
����ֵ��
          0����ѯ����Ӧ���豸��ֵ̬��
          1��û�в�ѯ����Ӧ���豸��ֵ̬��
********************************************************/
int BSP_USB_PcscInfoSet(unsigned int  ulSel, unsigned int  ulCurDevType, unsigned int *pulDevType);
#define DRV_USB_PCSC_INFO_SET(ulSel, ulCurDevType, pulDevType)    BSP_USB_PcscInfoSet(ulSel, ulCurDevType, pulDevType)

/********************************************************
����˵����Э��ջע��HSICʹ��֪ͨ�ص�����
��������:
���������pFunc: HSICʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
typedef void (*HSIC_UDI_ENABLE_CB_T)(void);
extern unsigned int BSP_HSIC_RegUdiEnableCB(HSIC_UDI_ENABLE_CB_T pFunc);
#define DRV_HSIC_REGUDI_ENABLECB(x) BSP_HSIC_RegUdiEnableCB(x)

/********************************************************
����˵����Э��ջע��HSICȥʹ��֪ͨ�ص�����
��������:
���������pFunc: HSICȥʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
typedef void (*HSIC_UDI_DISABLE_CB_T)(void);
extern unsigned int BSP_HSIC_RegUdiDisableCB(HSIC_UDI_DISABLE_CB_T pFunc);
#define DRV_HSIC_REGUDI_DISABLECB(x) BSP_HSIC_RegUdiDisableCB(x)
/********************************************************
����˵����Э��ջ��ѯHSICö��״̬
��������:
�����������
�����������
�����������
����ֵ��  1��ö�����
          0��ö��δ���
********************************************************/
extern unsigned int BSP_GetHsicEnumStatus(void);
#define DRV_GET_HSIC_ENUM_STATUS() BSP_GetHsicEnumStatus()

/*****************************************************************************
* �� �� ��  : BSP_NCM_Write_Ready
* ��������  : ׼����������
* �������  : void
* �������  :
* �� �� ֵ  : void
* �޸ļ�¼  :
*****************************************************************************/
void BSP_NCM_Write_Ready(void);

/********************************************************
����˵���� ���ص�ǰNV���е��豸��ֵ̬���Ƿ�֧��PCSC
��������:
��������� dev_type���豸��ֵ̬��OAM��NV�ж�����

��������� �ޡ�
����ֵ��
          0: dev_type��֧��PCSC�豸��
          1��dev_type֧��PCSC�豸
********************************************************/
/*unsigned int pcsc_info_quiry(unsigned int ulDevType);*/
#define DRV_USB_PCSC_INFO_QUIRY(a)            MDRV_OK

typedef unsigned int (*pFunAPDUProcess)(unsigned int CmdType, unsigned char *pApdu, unsigned int ApduLen);
typedef unsigned int (*GetCardStatus)(void);

typedef struct
{
    pFunAPDUProcess   pFuncApdu;
    GetCardStatus  pFuncGetCardStatus;
}BSP_CCID_REGFUNC;

/*****************************************************************************
 �� �� ��  : pcsc_usim_int
 ��������  : ע��PCSC������պ���
 �������  :
 �������  : None
 �� �� ֵ  : void
*****************************************************************************/
extern void pcsc_usim_int(pFunAPDUProcess pFun1, GetCardStatus pFun2);
#define DRV_PCSC_REG_CALLBACK(pFun1, pFun2) pcsc_usim_int((pFun1), (pFun2))


/*****************************************************************************
 �� �� ��  : pcsc_usim_ctrl_cmd
 ��������  : PCSC����ظ�����
 �������  :
 �������  : None
 �� �� ֵ  : void
*****************************************************************************/
extern unsigned int pcsc_usim_ctrl_cmd(unsigned int CmdTpye, unsigned int Result,
                                        unsigned char *Buf, unsigned int Length);
#define DRV_PCSC_SEND_DATA(CmdType, Result, Buffer, Length) pcsc_usim_ctrl_cmd(CmdType, Result, Buffer, Length)

/* Porting���࣬��ʱ����Ϊ�� */
#define DRV_COM_RCV_CALLBACK_REGI(uPortNo,pCallback)    MDRV_OK


/************************************************************************
 * FUNCTION
 *       rndis_app_event_dispatch
 * DESCRIPTION
 *       ���翨�汾����Ӧ�ý��в��Ż�Ͽ���������
 * INPUTS
 *       ���в��Ż�Ͽ�����ָʾ
 * OUTPUTS
 *       NONE
 *************************************************************************/
extern void DRV_AT_SETAPPDAILMODE(unsigned int ulStatus);


/************************************************************************
 * FUNCTION
 *       PDP_ACT_DRV_CALLBACK
 * DESCRIPTION
 *       PDP�������õ���Ļص�������ԭ�������翨���������ط��ű���Ϣ�����ڴ�׮
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
extern int PDP_ACT_DRV_CALLBACK(void);

typedef void(* USB_NET_DEV_SWITCH_GATEWAY)
(
    void
);

/************************************����궨��Ϊ�յĺ���******************************************/
/*****************************************************************************
 �� �� ��  : UsbStatusCallbackRegister
 ��������  : ��¼pCallBack��ȫ�ֱ����С�SD��������ؽӿڣ�V7�ȴ�׮
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
 /*extern int  UsbStatusCallbackRegister(pUsbState pCallBack);*/
#define DRV_USB_STATUS_CALLBACK_REGI(pCallBack)        MDRV_OK

/********************************************************************************************************
 �� �� ��  : USB_otg_switch_signal_set
 ��������  : ����BALONG��K3�Խ�ʱUSBͨ���л�GPIO���ſ���
 �������  : ��š����źź�ֵ
 �������  : ��

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int USB_otg_switch_signal_set(unsigned char ucGroup, unsigned char ucPin, unsigned char ucValue);
#define DRV_GPIO_SET(group, pin, value) USB_otg_switch_signal_set(group, pin, value)

#define DRV_GPIO_USB_SWITCH     200
#define DRV_GPIO_HIGH           1
#define DRV_GPIO_LOW            0

/********************************************************************************************************
 �� �� ��  : USB_otg_switch_set
 ��������  : ����BALONG��K3�Խ�ʱMODEM�࿪����ر�USB PHY
 �������  : ������ر�
 �������  : ��

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int USB_otg_switch_set(unsigned char ucValue);
#define DRV_USB_PHY_SWITCH_SET(value) USB_otg_switch_set(value)

#define AT_USB_SWITCH_SET_VBUS_VALID            1
#define AT_USB_SWITCH_SET_VBUS_INVALID          2

#define USB_SWITCH_ON       1
#define USB_SWITCH_OFF      0

/********************************************************************************************************
 �� �� ��  : USB_otg_switch_get
 ��������  : ����BALONG��K3�Խ�ʱMODEM��USB PHY״̬��ѯ
 �������  : ��
 �������  : ����USB PHY����״̬

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int USB_otg_switch_get(unsigned char *pucValue);
#define DRV_USB_PHY_SWITCH_GET(value) USB_otg_switch_get(value)

/* IOCTL CMD ���� */
#define ACM_IOCTL_SET_WRITE_CB      0x7F001000
#define ACM_IOCTL_SET_READ_CB       0x7F001001
#define ACM_IOCTL_SET_EVT_CB        0x7F001002
#define ACM_IOCTL_SET_FREE_CB       0x7F001003

#define ACM_IOCTL_WRITE_ASYNC       0x7F001010
#define ACM_IOCTL_GET_RD_BUFF       0x7F001011
#define ACM_IOCTL_RETURN_BUFF       0x7F001012
#define ACM_IOCTL_RELLOC_READ_BUFF  0x7F001013
#define ACM_IOCTL_SEND_BUFF_CAN_DMA 0x7F001014

#define ACM_IOCTL_IS_IMPORT_DONE    0x7F001020
#define ACM_IOCTL_WRITE_DO_COPY     0x7F001021

/* Modem ���������� */
#define ACM_MODEM_IOCTL_SET_MSC_READ_CB 0x7F001030
#define ACM_MODEM_IOCTL_MSC_WRITE_CMD   0x7F001031
#define ACM_MODEM_IOCTL_SET_REL_IND_CB  0x7F001032

/* UDI IOCTL ����ID */
#define UDI_ACM_IOCTL_SET_READ_CB           ACM_IOCTL_SET_READ_CB
#define UDI_ACM_IOCTL_GET_READ_BUFFER_CB    ACM_IOCTL_GET_RD_BUFF
#define UDI_ACM_IOCTL_RETUR_BUFFER_CB       ACM_IOCTL_RETURN_BUFF

#define UART_IOCTL_SET_WRITE_CB      0x7F001000
#define UART_IOCTL_SET_READ_CB       0x7F001001
#define UART_IOCTL_SET_EVT_CB        0x7F001002
#define UART_IOCTL_SET_FREE_CB       0x7F001003
#define UART_IOCTL_WRITE_ASYNC       0x7F001010
#define UART_IOCTL_GET_RD_BUFF       0x7F001011
#define UART_IOCTL_RETURN_BUFF       0x7F001012
#define UART_IOCTL_RELLOC_READ_BUFF  0x7F001013
#define UART_IOCTL_SEND_BUFF_CAN_DMA 0x7F001014
#define UART_IOCTL_SET_WRITE_TIMEOUT 0x7F001015
#define UART_IOCTL_SET_BAUD           0X7F001016
#define UART_IOCTL_SET_WLEN           0X7F001017
#define UART_IOCTL_SET_STP2           0X7F001018
#define UART_IOCTL_SET_EPS            0X7F001019
#define UART_IOCTL_IS_IMPORT_DONE    0x7F001020
#define UDI_UART_IOCTL_SET_READ_CB           UART_IOCTL_SET_READ_CB
#define UDI_UART_IOCTL_GET_READ_BUFFER_CB    UART_IOCTL_GET_RD_BUFF
#define UDI_UART_IOCTL_RETUR_BUFFER_CB       UART_IOCTL_RETURN_BUFF
#define UART_IOCTL_SET_MSC_READ_CB 0x7F001021
#define UART_IOCTL_MSC_WRITE_CMD 0x7F001022
#define UART_IOCTL_SWITCH_MODE_CB 0x7F001023
#define UART_IOCTL_SET_FLOW_CONTROL 0x7F001024
#define UART_IOCTL_SET_AC_SHELL 0x7F001025

/* UART UDI ������*/
#define UART_UDI_ERROR_BASE               0x80000000

#define UART_ERR_MODULE_NOT_INITED      ((int)(BSP_DEF_ERR(BSP_MODU_UART, (int) BSP_ERR_MODULE_NOT_INITED) | UART_UDI_ERROR_BASE))
#define UART_ERR_NULL_PTR      ((int)(BSP_DEF_ERR(BSP_MODU_UART, (int) BSP_ERR_NULL_PTR) | UART_UDI_ERROR_BASE))
#define UART_ERR_INVALID_PARA      ((int)(BSP_DEF_ERR(BSP_MODU_UART, (int) BSP_ERR_INVALID_PARA) | UART_UDI_ERROR_BASE))
#define UART_ERR_RETRY_TIMEOUT      ((int)(BSP_DEF_ERR(BSP_MODU_UART, (int) BSP_ERR_RETRY_TIMEOUT) | UART_UDI_ERROR_BASE))
#define UART_ERR_BUF_ALLOC_FAILED      ((int)(BSP_DEF_ERR(BSP_MODU_UART, (int) BSP_ERR_BUF_ALLOC_FAILED) | UART_UDI_ERROR_BASE))
#define UART_ERR_BUF_FREE_FAILED      ((int)(BSP_DEF_ERR(BSP_MODU_UART, (int) BSP_ERR_BUF_FREE_FAILED) | UART_UDI_ERROR_BASE))

#define UART_A_SHELL  (0x5A5A5A5A)
#define UART_C_SHELL  (0xA5A5A5A5)

/* UART����λ��*/
typedef enum
{
    WLEN_5_BITS,
    WLEN_6_BITS,
    WLEN_7_BITS,
    WLEN_8_BITS,
    WLEN_MAX
}UART_WLEN_ENUM;

/* UARTֹͣλ��*/
typedef enum
{
    STP2_OFF,
    STP2_ON,
    STP2_MAX
}uart_stp2_enum;

/* UARTУ�鷽ʽ*/
typedef enum
{
    PARITY_NO_CHECK,
    PARITY_CHECK_ODD,        /*��У��*/
    PARITY_CHECK_EVEN,        /*żУ��*/
    PARITY_CHECK_MARK,        /*У��λʼ��Ϊ1*/
    PARITY_CHECK_SPACE,       /*У��λʼ��Ϊ0*/
    PARITY_CHECK_MAX
}uart_parity_enum;

/* �첽�����շ��ṹ */
typedef struct tagUART_WR_ASYNC_INFO
{
    char* pBuffer;
    unsigned int u32Size;
    void* pDrvPriv;
}uart_wr_async_info;
/* ��buffer������Ϣ */
typedef struct tagUART_READ_BUFF_INFO
{
    unsigned int u32BuffSize;
    unsigned int u32BuffNum;
}uart_read_buff_info;
/* ���ؿ��ؽṹ */
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved1 : 14;/* bit[0-13] : reversed */
        unsigned int  rtsen         : 1;/* bit[14] : rts enable, up stream flow ctrl  */
        unsigned int  ctsen         : 1;/* bit[15] : cts enable, down stream flow ctrl */
        unsigned int  reserved2 : 16;/* bit[16-31] : reversed */
    } reg;
} uart_flow_ctrl_union;

typedef void (*uart_free_cb_t)(char* pBuff);
typedef void (*uart_read_cb_t)(void);
typedef void (*uart_msc_read_cb_t)(MODEM_MSC_STRU* pModemMsc);
typedef void (*uart_switch_mode_cb_t)(void);

/* �첽�����շ��ṹ */
typedef struct tagACM_WR_ASYNC_INFO
{
    char* pVirAddr;
    char* pPhyAddr;
    unsigned int u32Size;
    void* pDrvPriv;
}ACM_WR_ASYNC_INFO;

/* ACM�豸�¼����� */
typedef enum tagACM_EVT_E
{
    ACM_EVT_DEV_SUSPEND = 0,        /* �豸�����Խ��ж�д(��Ҫ�����¼��ص�������״̬) */
    ACM_EVT_DEV_READY = 1,          /* �豸���Խ��ж�д(��Ҫ�����¼��ص�������״̬) */
    ACM_EVT_DEV_BOTTOM
}ACM_EVT_E;

/* ��buffer��Ϣ */
typedef struct tagACM_READ_BUFF_INFO
{
    unsigned int u32BuffSize;
    unsigned int u32BuffNum;
}ACM_READ_BUFF_INFO;


typedef struct tagNCM_PKT_S
{
    unsigned char *pBuffer;       /* bufferָ��*/
    unsigned int  u32BufLen;      /* buffer���� */
}NCM_PKT_S;

/* NCM�豸����ö��*/
typedef enum tagNCM_DEV_TYPE_E
{
    NCM_DEV_DATA_TYPE,      /* ����ͨ�����ͣ�PSʹ��*/
    NCM_DEV_CTRL_TYPE       /* ����ͨ����MSP����AT����ʹ��*/
}NCM_DEV_TYPE_E;

/* USB IOCTLö�� */
typedef enum tagNCM_IOCTL_CMD_TYPE_E
{
    NCM_IOCTL_NETWORK_CONNECTION_NOTIF,      /* 0x0,NCM�����Ƿ�������*/
    NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF, /* 0x1,NCM�豸Э�̵������ٶ�*/
    NCM_IOCTL_SET_PKT_ENCAP_INFO,            /* 0x2,���ð���װ��ʽ*/
    NCM_IOCTL_REG_UPLINK_RX_FUNC,            /* 0x3,ע�������հ��ص�����*/
    NCM_IOCTL_REG_FREE_PKT_FUNC,             /* 0x4,ע���ͷŰ���װ�ص�����*/
    NCM_IOCTL_FREE_BUFF,                     /* 0x5,�ͷŵ���buffer*/
    NCM_IOCTL_GET_USED_MAX_BUFF_NUM,         /* 0x6,��ȡ�ϲ�������ռ�õ�ncm buffer����*/
    NCM_IOCTL_GET_DEFAULT_TX_MIN_NUM,        /* 0x7,��ȡĬ�Ϸ���������ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_GET_DEFAULT_TX_TIMEOUT,        /* 0x8,��ȡĬ�Ϸ�����ʱʱ�䣬������ʱ�������һ��NCM����*/
    NCM_IOCTL_GET_DEFAULT_TX_MAX_SIZE,       /* 0x9,��ȡĬ�Ϸ����ֽ���ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_SET_TX_MIN_NUM,                /* 0xa,���÷���������ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_SET_TX_TIMEOUT,                /* 0xb,���÷�����ʱʱ�䣬������ʱ�������һ��NCM����*/
    NCM_IOCTL_SET_TX_MAX_SIZE,               /* 0xc,�������ֲ���ʹ�á����÷����ֽ���ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_GET_RX_BUF_SIZE,               /* 0xd,��ȡ�հ�buffer��С*/
    NCM_IOCTL_FLOW_CTRL_NOTIF,               /* 0xe,���ؿ��ƿ���*/
    NCM_IOCTL_REG_AT_PROCESS_FUNC,           /* 0xf,ע��AT�����ص�����*/
    NCM_IOCTL_AT_RESPONSE,                   /* 0x10,AT�����Ӧ*/
    NCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC,     /* 0x11,ע������״̬�ı�֪ͨ�ص�����*/
    NCM_IOCTL_SET_PKT_STATICS,               /* 0x12,����ͳ����Ϣ*/
    NCM_IOCTL_GET_FLOWCTRL_STATUS,           /* 0x13 ��ѯNCM����״̬*/
    /* END:   Modified by liumengcun, 2011-4-21 */

    NCM_IOCTL_GET_CUR_TX_MIN_NUM,              /* 0x14 ��ȡ��ǰ����������ֵ*/
    NCM_IOCTL_GET_CUR_TX_TIMEOUT,               /* 0x15 ��ȡ��ǰ������ʱʱ��*/
    NCM_IOCTL_IPV6_DNS_NOTIF,              /*0x16 IPV6 DNS�����ϱ�*/
    /* END:   Modified by liumengcun, 2011-6-23 */
    /* BEGIN: Modified by liumengcun, 2011-7-20 ֧��IPV6 DNS����*/
    NCM_IOCTL_SET_IPV6_DNS,                     /* 0x16 ����IPV6 DNS*/
    /* END:   Modified by liumengcun, 2011-7-20 */
    /* BEGIN: Modified by liumengcun, 2011-8-10 MSP������*/
    NCM_IOCTL_CLEAR_IPV6_DNS,                     /* 0x17 ���IPV6 DNS�ڰ�˵Ļ���,param�ڴ�������û�����壬�����ָ�뼴��*/
    NCM_IOCTL_GET_NCM_STATUS,                     /* 0x18 ��ȡNCM����״̬ enable:TRUE(1);disable:FALSE(0) */
    /* END:   Modified by liumengcun, 2011-8-10 */

    NCM_IOCTL_SET_ACCUMULATION_TIME,

    /* BEGIN: Modified by baoxianchun, 2012-5-17 GU PS ������*/
    NCM_IOCTL_SET_RX_MIN_NUM,        /*�����հ�������ֵ*/
    NCM_IOCTL_SET_RX_TIMEOUT,        /*�����հ���ʱʱ��*/
    /* END: Modified by baoxianchun, 2012-5-17 GU PS ������*/

    NCM_IOCTL_REG_NDIS_RESP_STATUS_FUNC   /* NDISͨ��AT����״̬����ص����� */
}NCM_IOCTL_CMD_TYPE_E;

/* NCM����״̬ö��,NCM_IOCTL_NETWORK_CONNECTION_NOTIF�����ֶ�Ӧ����ö��*/
typedef enum tagNCM_IOCTL_CONNECTION_STATUS_E
{
    NCM_IOCTL_CONNECTION_LINKDOWN,      /* NCM����Ͽ�����*/
    NCM_IOCTL_CONNECTION_LINKUP         /* NCM��������*/
}NCM_IOCTL_CONNECTION_STATUS_E;

/* NCM�����ٶȽṹ,NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF�����ֶ�Ӧ�����ṹ��*/
typedef struct tagNCM_IOCTL_CONNECTION_SPEED_S
{
    unsigned int u32DownBitRate;
    unsigned int u32UpBitRate;
}NCM_IOCTL_CONNECTION_SPEED_S;

/* ����װ�ṹ��,NCM_IOCTL_SET_PKT_ENCAP_INFO�����ֶ�Ӧ�����ṹ��*/
typedef struct tagNCM_PKT_ENCAP_INFO_S
{
    int s32BufOft;      /* bufƫ���� */
    int s32LenOft;      /* lenƫ���� */
    int s32NextOft;     /* nextƫ���� */
}NCM_PKT_ENCAP_INFO_S;

/* AT����ظ�����ָ�뼰���� NCM_IOCTL_AT_RESPONSE*/
typedef struct tagNCM_AT_RSP_S
{
    unsigned char* pu8AtAnswer;
    unsigned int u32Length;
} NCM_AT_RSP_S;
typedef struct tagNCM_IPV6_DNS_NTF_S
{
    unsigned char* pu8Ipv6DnsNtf;
    unsigned int u32Length;
} NCM_AT_IPV6_DNS_NTF_S;

/* AT������պ���ָ�룬�ú���Ϊͬ���ӿڣ���ӦNCM_IOCTL_REG_AT_PROCESS_FUNC������*/
typedef void (*USBNdisAtRecvFunc)(unsigned char * pu8Buf, unsigned int u32Len);

/* NCM���ؿ���ö��,NCM_IOCTL_NETWORK_CONNECTION_NOTIF�����ֶ�Ӧ����ö��*/
typedef enum tagNCM_IOCTL_FLOW_CTRL_E
{
    NCM_IOCTL_FLOW_CTRL_ENABLE,      /* ������*/
    NCM_IOCTL_FLOW_CTRL_DISABLE      /* �ر�����*/
}NCM_IOCTL_FLOW_CTRL_E;

/* NCM����״̬�ı�֪ͨö��,NCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC�����ֶ�Ӧ����ö��*/
typedef enum tagNCM_IOCTL_CONNECT_STUS_E
{
    NCM_IOCTL_STUS_CONNECT,      /* ����*/
    NCM_IOCTL_STUS_BREAK         /* �����Ͽ�,����*/
}NCM_IOCTL_CONNECT_STUS_E;

/*  �´��ϴ������ذ��ĸ���ͳ����Ϣ��
    �����͸�PC�������ȴ�PC�Ķ�ȡ,NCM_IOCTL_SET_PKT_STATICS�����ֶ�Ӧ�����ṹ*/
typedef struct tagNCM_IOCTL_PKT_STATISTICS_S
{
    unsigned int     u32TxOKCount;         /*���Ͱ���*/
    unsigned int     u32RxOKCount;         /*���հ���*/
    unsigned int     u32TxErrCount;        /*���ʹ���*/
    unsigned int     u32RxErrCount;        /*���մ���*/
    unsigned int     u32TxOverFlowCount;   /*�����������*/
    unsigned int     u32RxOverFlowCount;   /*�����������*/
    unsigned int     u32CurrentTx;         /*��������*/
    unsigned int     u32CurrentRx;         /*��������*/
} NCM_IOCTL_PKT_STATISTICS_S;

/* BEGIN: Modified by liumengcun, 2011-7-20 IPV6 DNS���ýṹ,NCM_IOCTL_SET_IPV6_DNS��Ӧ�����ṹ*/
#define BSP_NCM_IPV6_DNS_LEN     32
 typedef struct tagNCM_IPV6DNS_S  /* 0x16 ����IPV6 DNS*/
 {
     unsigned char * pu8Ipv6DnsInfo;/* 32�ֽڣ���16�ֽڱ�ʾprimaryDNS����16�ֽڱ�ʾSecondaryDNS��*/
     unsigned int u32Length;
 } NCM_IPV6DNS_S;
/* END:   Modified by liumengcun, 2011-7-20 */
typedef struct tagNCM_PKT_INFO_S
{
    unsigned int u32PsRcvPktNum;              /* �հ��͵�PS�İ�����*/
    unsigned int u32RcvUnusedNum;             /* �հ�������PSҪ����������*/
    unsigned int u32NcmSendPktNum;            /* ��������*/
}NCM_PKT_INFO_S;
extern int BSP_Modem_OS_Status_Switch(int enable);
#define DRV_OS_STATUS_SWITCH(enable) BSP_Modem_OS_Status_Switch(enable)

struct sk_buff;
typedef void (*USB_IPS_MNTN_TRACE_CB_T)(struct sk_buff *skb,unsigned short usType);
extern unsigned int BSP_USB_RegIpsTraceCB(USB_IPS_MNTN_TRACE_CB_T pFunc);
#define DRV_USB_REG_IPS_TRACECB(x) BSP_USB_RegIpsTraceCB(x)

#endif

/*audio module*/
#define AUDIO_IOCTL_BASE                    (0x30000000)
#define IOCTL_AUDIO_VOICE_OPEN              (AUDIO_IOCTL_BASE+23)
#define IOCTL_AUDIO_VOICE_CLOSE             (AUDIO_IOCTL_BASE+24)

static inline int DRV_CODEC_OPEN(const char *devname, int flags, int mode)
{
    return 0;
}

static inline int DRV_CODEC_IOCTL(int devid, int cmd, int arg)
{
    return 0;
}

static inline int DRV_GET_CODEC_FUNC_STATUS(void)
{
    /*note: asic return 1,sft need to return 0*/
    return 1;
}

static inline int DRV_FILE_GET_DISKSPACE(const char *path,unsigned int *DskSpc,unsigned int *UsdSpc,  unsigned int *VldSpc)
{
    return 0;
}

/*mntn module*/
typedef int  (*OM_SAVE_FUNC)(int funcType, unsigned char *data, unsigned int* ulLength);

/****************************************************
Function:     BSP_MNTN_ExchOMSaveRegister
Description:  ע��������trace���溯���������ڵ��帴λʱ�����浱ǰ���������־��Ϣ���ȴ�׮�����������쳣�������������
Input:             NA;
Output:       NA;
Return:       0;
Others:       NA;
****************************************************/
static inline int DRV_SAVE_REGISTER(int funcType, OM_SAVE_FUNC *pFunc)
{
    return 0;
}

static inline int DRV_GET_FLASH_INFO(unsigned char * pFlashInfo, unsigned int ulLength)
{
    return 0;
}
static inline int DRV_ABB_SELFCHECK (void)
{
    return 0;
}

static inline int DRV_PMU_SELFCHECK (void)
{
    return 0;
}

static inline int DRV_I2C_SELFCHECK (void)
{
    return 0;
}

static inline int DRV_SPI_SELFCHECK (void)
{
    return 0;
}

/***************************************************************************
 * �� �� ��  : DRV_GET_RF_GLOCKSTATE
 * ��������  : ��ȡGSM RF����״̬��
 * �������  : �ޡ�
 * �������  : Status���������״̬�����ֵ��
 *                  0��TX����RX��������
 *                  1��TX��RX��û�б�������
 * �� �� ֵ  : 0:  �����ɹ���
 *            -1�� ����ʧ�ܡ�
 ****************************************************************************/
static inline int DRV_GET_RF_GLOCKSTATE(unsigned int *Status)
{
    return 0;
}


static inline int DRV_BOOTFLAG_CFG(unsigned int ulBootFlag)
{
    return 0;
}

static inline int DRV_GET_GPIO_INFO(unsigned char * pGpioInfo, unsigned long ulLength)
{
    return 0;
}

static inline int DRV_GET_HEAPINFO(unsigned int *allocSize, unsigned int *totalSize)
{
    return 0;
}

static inline int DRV_BACKUP_SYS_FILE(void)
{
    return 0;
}

static inline int DRV_SDMMC_GET_STATUS(void)
{
    return 0;
}

#define DRV_LOG_INSTALL(fptr, fptr1, fptr2, fptr3, fptr4)     MDRV_OK

static inline int DRV_MNTN_GET_BATT_STATE(void)
{
    return 0;
}

/*VERSIONINFO_I���ݽṹ�а汾�ַ��������Ч�ַ�����*/
#define VER_MAX_LENGTH                  30

typedef struct
{
    unsigned char CompId;              /* ����ţ��μ�COMP_TYPE */
    unsigned char CompVer[VER_MAX_LENGTH+1];         /* ���汾���� 30 �ַ�+ \0 */
}VERSIONINFO_I;

/*lmsp ��diag_common.h ��ʹ�ã���֪��Ϊʲô*/
typedef enum{
     ADDRTYPE8BIT,
     ADDRTYPE16BIT,
     ADDRTYPE32BIT
}ENADDRTYPE;

/*taf used ,don't know why*/
enum SECURE_SUPPORT_STATUS_I
{
    SECURE_NOT_SUPPORT = 0,
    SECURE_SUPPORT = 1
};

/*LPS used,don't konw why begin*/
#ifndef PS_L2_UL_TRACE
#define PS_L2_UL_TRACE 0
#endif

#ifndef PS_L2_DL_TRACE
#define PS_L2_DL_TRACE 1
#endif

#define PROCESS_ENTER(pADDRESS)  do { } while (0)
#define PROCESS_EXIT(pADDRESS)   do { } while (0)


typedef struct tagBSP_OM_NET_S
{
    unsigned int u32NetRxStatOverFlow;       /* ����FIFO���ͳ�Ƽ��� */
    unsigned int u32NetRxStatPktErr;         /* �����ܴ������ */
    unsigned int u32NetRxStatCrcErr;         /* ����CRC������� */
    unsigned int u32NetRxStatLenErr;         /* ������Ч���Ȱ����� */
    unsigned int u32NetRxNoBufInt;           /* ����û��BUFFER�жϼ��� */
    unsigned int u32NetRxStopInt;            /* ����ֹͣ�жϼ��� */
    unsigned int u32NetRxDescErr;            /* �������������� */

    unsigned int u32NetTxStatUnderFlow;      /* ����FIFO����ͳ�Ƽ��� */
    unsigned int u32NetTxUnderFlowInt;       /* ����FIFO�����жϼ��� */
    unsigned int u32NetTxStopInt;            /* ����ֹͣ�жϼ��� */
    unsigned int u32NetTxDescErrPs;          /* ��������������(Ps) */
    unsigned int u32NetTxDescErrOs;          /* ��������������(Os) */
    unsigned int u32NetTxDescErrMsp;         /* ��������������(Msp) */

    unsigned int u32NetFatalBusErrInt;      /* ���ߴ���*/
}BSP_OM_NET_S;

static inline void BSP_OM_NET(BSP_OM_NET_S *pstNetOm)
{
    return ;
}

/*LPS used,don't konw why end*/



/*�ýӿڴ�ɾ��*/
/*****************************************************************************
 �� �� ��  : DRV_MEM_READ
 ��������  : ��32λ��Ȳ�ѯ�ڴ棬���4�ֽ����ݡ���ά�ɲ⣬V7�ȴ�׮
 �������  : ulAddress����ѯ��ַ�ռ��ַ����ַ�����ڴ淶Χ�ڣ����򷵻�-1��
 �������  : pulData��ָ���ѯ���ݵ�ָ�롣
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int DRV_MEM_READ(unsigned int ulAddress, unsigned int* pulData);

#if 1  /*drv_sec.h*/
/*************************************************
 �� �� ��       : DRV_SECURE_SUPPORT
 ��������   : ��ǰ�汾�Ƿ�֧�ְ�ȫ����
 �������   : unsigned char *pData
 �������   : unsigned char *pData
 �� �� ֵ      : OK/ERROR
*************************************************/
extern int DRV_SECURE_SUPPORT(unsigned char *pu8Data);

/*************************************************
 �� �� ��       : DRV_SECURE_ALREADY_USE
 ��������   : ��ѯ��ǰ�汾�Ƿ��Ѿ����ð�ȫ����
 �������   : unsigned char *pData
 �������   : unsigned char *pData
 �� �� ֵ      : OK/ERROR
*************************************************/
extern int DRV_SECURE_ALREADY_USE(unsigned char *pu8Data);

/*************************************************
 �� �� ��       : DRV_START_SECURE
 ��������   : ���ð�ȫ����
 �������   :
 �������   :
 �� �� ֵ      : OK/ERROR
*************************************************/
extern int DRV_START_SECURE(void);
#endif

#if 1  /*drv_pmu.h*/
/*****************************************************************************
 �� �� ��  : DRV_GET_PMU_STATE
 ��������  : ��ȡPMUģ�鿪����ʽ�����״̬����ص����������λ״̬��
 �������  : �ޡ�
 �������  : Pmu_State :������ʽ�����״̬����ص����������λ״̬��
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע��������ýӿڽ���PS��PC������ʹ�ã�Ŀǰû��Ӧ�ã��ݱ�����
*****************************************************************************/
extern unsigned int DRV_GET_PMU_STATE(void*  Pmu_State);
#endif

#if 1  /*drv_oled.h*/

/*****************************************************************************
*  Function:  DRV_OLED_CLEAR_WHOLE_SCREEN
*  Description: oled clear *
*  Called By:AP
*  Table Accessed:
*  Table Updated:
*  Input:
*         N/A
*  Output:
*         N/A
*  Return:
*         N/A
*****************************************************************************/
extern void DRV_OLED_CLEAR_WHOLE_SCREEN(void);

/*****************************************************************************
*  Function:  DRV_OLED_UPDATE_STATE_DISPLAY
*  Description: oled display right or not right  *
*  Called By:AP
*  Table Accessed:
*  Table Updated:
*  Input:
*         N/A
*  Output:
*         N/A
*  Return:
*         N/A
*****************************************************************************/
extern  void DRV_OLED_UPDATE_STATE_DISPLAY(int UpdateStatus);

/*****************************************************************************
 �� �� ��  : DRV_OLED_UPDATE_DISPLAY
 ��������  : SD����Ƭ�汾������OLED��ʾ
 �������  : BOOL UpdateStatus
 �������  : �ޡ�
 ����ֵ��   ��
 ����:  �����ɹ���NV������ɺ���øú�����
        ����ʧ�ܺ���øú������
*****************************************************************************/
extern void DRV_OLED_UPDATE_DISPLAY(int UpdateStatus);

/*****************************************************************************
 �� �� ��  : DRV_OLED_STRING_DISPLAY
 ��������  : oled�ַ�����ʾ����
 �������  :
 *           Ҫ��ʾ�ַ�������ʼ����
 *           Ҫ��ʾ���ַ���
 �������  : none
 �� �� ֵ  : void
*****************************************************************************/
extern void DRV_OLED_STRING_DISPLAY(unsigned char ucX, unsigned char ucY, unsigned char *pucStr);

#endif

#if 1  /*drv_nve.h*/
#define BSP_NVE_NAME_LENGTH          8       /*NV name maximum length*/
#define BSP_NVE_NV_DATA_SIZE        104     /*NV data maximum length*/

#define BSP_NV_READ                 1       /*NV read  operation*/
#define BSP_NV_WRITE                0       /*NV write operation*/

typedef struct nve_info_stru {
	unsigned int nv_operation;              /*0-write,1-read*/
	unsigned int nv_number;                 /*NV number you want to visit*/
	char nv_name[BSP_NVE_NAME_LENGTH];
	unsigned int valid_size;
	unsigned char nv_data[BSP_NVE_NV_DATA_SIZE];
}NVE_INFO_S;

/*****************************************************************************
* �� �� ��  : DRV_NVE_ACCESS
*
* ��������  : ����LINUX NVE
*
* �������  : nve  ID
*
* �������  : ��
*
* �� �� ֵ  : OK& ERROR
*
* �޸ļ�¼ :  2013��6��27��  v1.00  yuanqinshun  ����
*****************************************************************************/
int DRV_NVE_ACCESS(NVE_INFO_S *nve);
#endif

#if 1  /*drv_nv.h*/
/*****************************************************************************
 �� �� ��  : BSP_PROD_GetRecoverNvInfo
 ��������  : �ӵ����õ�ǰ��Ҫ���ǵ�NV��Ϣ
 �������  : N/A

 �������  : ppNvInfo  - ָ��NV��Ϣ�ṹ�������
             pulNvNum  - �������

 �� �� ֵ  : 0����ȷ����0: ʧ��
*****************************************************************************/
extern  int BSP_PROD_GetRecoverNvInfo(void **ppNvInfo, unsigned long *pulNvNum);
#define  DRV_GET_RECOVER_NV_INFO(ppNvInfo, pulNvNum)  \
                BSP_PROD_GetRecoverNvInfo(ppNvInfo, pulNvNum)


extern int DRV_COPY_NVUSE_TO_NVBACKUP ( void );



extern int DRV_COPY_NVUPGRADE_TO_NVUSE( void );
#endif

/*drv_mntn module*/
typedef enum tagMSP_PROC_ID_E
{
    OM_REQUEST_PROC = 0,
    OM_ADDSNTIME_PROC = 1,
    OM_PRINTF_WITH_MODULE = 2,
    OM_PRINTF = 3,

    OM_PRINTF_GET_MODULE_IDLEV = 4,
    OM_READ_NV_PROC = 5,
    OM_WRITE_NV_PROC = 6,
    OM_MNTN_ERRLOG = 7,

    MSP_PROC_REG_ID_MAX
}MSP_PROC_ID_E;

typedef void (*BSP_MspProc)(void);
#define EXCH_CB_NAME_SIZE           (32)
typedef struct
{
    char   aucName[EXCH_CB_NAME_SIZE];
    unsigned char *pucData;
    unsigned int  ulDataLen;
}cb_buf_t;

typedef int  (*exchCBReg)(cb_buf_t *);

/*liuyi++ �ýӿ����ĵ���δ���� ++*/
/*******************************************************************************
 �� �� ��: DRV_EXCH_CUST_FUNC_REG
 ��������: ��������ģ���ṩ����ӿڣ����ϲ�ע��ص������ڸ�λʱ�����ϲ�ָ����Ϣ
 �������: cb �ϲ�ָ���ص��ӿ�
 �������: ��
 �� �� ֵ: 0-��ӳɹ�������-���ʧ��
 ˵��    :  pucData :ָ����¼��Ϣ��ַ����ע�ⲻҪָ��ջ����ʱ���������ѿռ����ݣ�
                     ʹ�����Լ�ά���������ռ�ʹ���꣬�Լ��ͷš�����ȫ�ֱ�����
            aucName :����
            ulDataLen: ���ݳ���

����ֵ�б�:
    CUST_REG_OK = 0,                        ��ӳɹ�
    CUST_REG_PARM_NULL,                     ���Ϊ��
    CUST_REG_EXCH_NOT_READY,                EXCHģ����δ��ʼ��
    CUST_REG_EXCH_REBOOT_CONTEXT,           �Ѿ����븴λ����
    CUST_REG_EXCH_QUEUE_NOT_INIT,           ע�������δ��ʼ��
    CUST_REG_EXCH_QUEUE_FULL,               ��������
    CUST_REG_EXCH_ALREADY_IN_QUEUE,         �ظ�ע��
    CUST_REG_EXCH_MUTEX_REJECT,             MUTEX REJECT
    CUST_REG_EXCH_QUEUE_IN_ERR              �����ʧ��

��ͨ������ֵ��λ�������

*******************************************************************************/
extern int DRV_EXCH_CUST_FUNC_REG(exchCBReg cb);
/*liuyi++ �ýӿ����ĵ���δ���� --*/

/*liuyi++ �ýӿ����ĵ���δ����*/
/*****************************************************************************
* �� �� ��  : DRV_MSP_PROC_REG
*
* ��������  : DRV�ṩ��OM��ע�ắ��
*
* �������  : MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc
* �������  : NA
*
* �� �� ֵ  : NA
*
* ����˵��  : ��ά�ɲ�ӿں���
*
*****************************************************************************/
extern void DRV_MSP_PROC_REG(MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc);
/*liuyi++ �ýӿ����ĵ���δ����--*/

/*drv*/
/*****************************************************************************
 �� �� ��  : BSP_GUDSP_ShareAddrGet
 ��������  : ��ȡ����㹲���ַ�ε���Ϣ��
 �������  : �ޡ�
 �������  : pulAddr���������㹲���ַ����Ϣ�Ļ��档
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern int BSP_GUDSP_ShareAddrGet(unsigned int * pulAddrInTcm, unsigned int * pulAddrInDdr, unsigned int * pulLength);
#define DRV_DSP_SHARE_ADDR_GET(pulAddrInTcm,pulAddrInDdr,pulLength)    BSP_GUDSP_ShareAddrGet(pulAddrInTcm,pulAddrInDdr,pulLength)

static inline int DRV_DSP_DRX_GPIO_VAL_SET(unsigned int  u32Data)
{
    return 0;
}

static inline int  NAND_GET_BAD_BLOCK(unsigned int *pNum, unsigned int **ppBadBlock)
{
    return -1;
}

static inline void  NAND_FREE_BAD_BLOCK_MEM(unsigned int* pBadBlock)
{
    return ;
}

/******************************************************************************
*
  ������:   BSP_Sram_BackupInfoReg
  ��������: ע��SRAM�α��ݻָ���Ϣ
  �������: pucSramAddr ע��Ķ���SRAM�ļ��ص�ַ
            ulSectLen   ע��Ķε��ֽڴ�С�������ڲ�Ĭ�ϲ����κ��ֽڶ��봦��
            ulNeedMulBck�ö��Ƿ���Ҫÿ���µ綼�����ݴ���һ������֮���������
                        ���ĶΣ�����:data����Ҫÿ�ζ������������ݣ���ô�ò���
                        ��дΪ1����text������֮��һֱ���䣬�ʱ���һ�μ��ɣ�����
                        ���߷��ʴ������ò�����дΪ0
            ulNeedCheck �ָ��������Ƿ���ҪУ�飬����У�������Ӱ��ϴ󣬹ʸù���
                        ����Ŀǰ����������չ���ݲ�ʵ�֣�����ֵ��Ч
  �������: None
  ����ֵ:   BSP_OK      ����ɹ�
            BSP_ERROR   ����ʧ��
*******************************************************************************/
extern int BSP_SRAM_BackupInfoReg(unsigned char *pucSramAddr, unsigned long ulSectLen, unsigned long ulNeedMulBak, unsigned long ulNeedCheck);
#define DRV_SRAM_BACKUP_INFO_REG(pucSramAddr, ulSectLen, ulNeedMulBak, ulNeedCheck)  BSP_SRAM_BackupInfoReg(pucSramAddr, ulSectLen, ulNeedMulBak, ulNeedCheck)

#define NAND_MFU_NAME_MAX_LEN    16
#define NAND_DEV_SPEC_MAX_LEN    32

typedef struct
{
    unsigned int           MufId;                                         /* ����ID */
    unsigned char          aucMufName[NAND_MFU_NAME_MAX_LEN];             /* ���������ַ��� */
    unsigned int           DevId;                                         /* �豸ID */
    unsigned char          aucDevSpec[NAND_DEV_SPEC_MAX_LEN];             /* �豸����ַ��� */
}NAND_DEV_INFO_S;

/******************************************************************************
*
  ������:       int nand_get_dev_info (NAND_DEV_INFO_S *pNandDevInfo)
  ��������:     ��ѯNAND�豸�����Ϣ����������ID���������ơ��豸ID���豸���
  �������:     ��
  �������:     pNandDevInfo    �洢NAND�豸�����Ϣ�Ľṹ��
  ����ֵ:       0    : ��ѯ�ɹ�
                ���� : ��ѯʧ��
*******************************************************************************/
static inline int NAND_GET_DEV_INFO(NAND_DEV_INFO_S *pNandDevInfo)
{
    return -1;
}

/*****************************************************************************
* �� �� ��  : BSP_IPM_FreeBspBuf
*
* ��������  : �ͷ��ڴ�ӿ�
*
* �������  : unsigned char *pBuf ��Ҫ�ͷŵ�ָ��
*
* �������  : ��
* �� �� ֵ  : ��
*
* �޸ļ�¼  :2011��1��27��   ³��  ����
*****************************************************************************/
void BSP_IPM_FreeBspBuf(unsigned char *pBuf);

typedef struct
{
    unsigned int ulblockCount;    /*Block����*/
    unsigned int ulpageSize;      /*pageҳ��С*/
    unsigned int ulpgCntPerBlk;   /*һ��Block�е�page����*/
}DLOAD_FLASH_STRU;

static inline int DRV_GET_DLOAD_FLASHINFO(DLOAD_FLASH_STRU* pFlashInfo)
{
	return 0;
}

#ifdef __cplusplus
}
#endif
#endif
