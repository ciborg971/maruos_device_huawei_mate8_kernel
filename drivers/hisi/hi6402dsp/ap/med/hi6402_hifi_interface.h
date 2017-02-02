

/*****************************************************************************
  1 ����ͷ�ļ�����

  notice:  ��Ҫ�����κ�����ͷ�ļ�!!!
*****************************************************************************/


#ifndef __HI6402_HIFI_INTERFACE_H__
#define __HI6402_HIFI_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* AP��Kernel��Ƶ�����������ݸ�hifiʱ��buff������bufAddrΪ���ߵ�ַ��bufSize��dataSize��λbyte */
#if 0                                                                           /*_H2ASN_Skip*/
#define DRV_SEND_DATA_STRU                                                      \
    VOS_UINT32                              uwBufAddr;                          \
    VOS_UINT32                              uwBufSize;                          \
    VOS_UINT32                              uwDataSize;
#else
#define DRV_SEND_DATA_STRU                                                      \
    unsigned long                           uwBufAddr;                          \
    unsigned long                           uwBufSize;                          \
    unsigned long                           uwDataSize;
#endif

#define HIFI_AUDIO_PCM_COMP_COEF_LEN_MAX    (128)
/*********************************************************
6402��Ϣö��
*********************************************************/
enum DSP_POWER_STATE_ENUM
{
    HIFI_POWER_ON = 0xA0,
    HIFI_POWER_CLK_ON = 0xB0,
    HIFI_POWER_CLK_OFF,
};

enum MLIB_PATH_ENUM
{
    MLIB_PATH_DATA_HOOK     = 0,
    MLIB_PATH_DEFAULT,
    MLIB_PATH_WAKEUP,
    MLIB_PATH_SMARTPA,
    MLIB_PATH_BUTT
};
typedef unsigned int MLIB_PATH_ENUM_UINT32;


enum MLIB_MODULE_ENUM
{
	MLIB_MODULE_DEFAULT     = 0,
	MLIB_MODULE_IVW,		
	MLIB_MODULE_SWU,		
	MLIB_MODULE_DSM,
	MLIB_MODULE_ELVIS,	    
	MLIB_MODULE_TSLICE,	
	MLIB_MODULE_OEM,    
	MLIB_MODULE_GOOGLE,
	MLIB_MODULE_BUTT,

    MLIB_MODULE_BROADCAST   = 0xFFFFFFFF,
};
typedef unsigned int MLIB_MODULE_ENUM_UINT32;

enum APDSP_MSG_ENUM
{
    ID_AP_DSP_IF_OPEN          = 0xDD10,  /*AP ���� DSP���˿ڿ�*/
    ID_AP_DSP_IF_CLOSE         = 0xDD11,  /*AP ���� DSP���˿ڹ�*/
    ID_AP_DSP_PARAMETER_SET    = 0xDD12,  /*AP ���� DSP���㷨set*/
    ID_AP_DSP_PARAMETER_GET    = 0xDD13,  /*AP ���� DSP���㷨get*/
    ID_AP_DSP_OM               = 0xDD14,  /*AP ���� DSP�����ù�ȡPCM��Log����*/
    
    ID_AP_DSP_IF_ST_OPEN       = 0xDD15,  /*AP ���� DSP��Sound Trigger�˿ڿ�*/ 
    ID_AP_DSP_IF_ST_CLOSE      = 0xDD16,  /*AP ���� DSP��Sound Trigger�˿ڹ�*/

    ID_AP_DSP_FASTTRANS_OPEN   = 0XDD17,  /*AP ���� DSP�����������ϱ���*/
    ID_AP_DSP_FASTTRANS_CLOSE  = 0XDD18,  /*AP ���� DSP�����������ϱ���*/
    ID_AP_DSP_WAKEUP_TEST      = 0XDD19,  /*AP ���� DSP��Sound Trigger���Ѳ���*/
    
    ID_DSP_UPDATE_BUF          = 0xDD20,  /*DSP ��Ƶ�������ݸ����ж���Ϣ*/
    ID_DSP_LOG_HOOK            = 0xDD21,  /*DSP ץȡlog����*/
    ID_DSP_UPDATE_FASTBUF      = 0XDD22,  /*DSP �������ѿ����ϱ�ͨ��*/
    ID_DSP_UPDATE_RECORDBUF    = 0XDD23,  /*DSP ����������ͨ¼���ϱ�*/
    ID_AP_DSP_MADTEST_START    = 0xDD31,  /*AP����DSP ���ڲ�����������MAD*/
    ID_AP_DSP_MADTEST_STOP     = 0xDD32,  /*AP����DSP ���ڲ���ֹͣ����MAD*/
    ID_AP_DSP_UARTMODE         = 0xDD33,  /*AP����DSP �����趨��ǰUARTģʽ��ץȡ��*/
    ID_AP_DSP_FASTMODE         = 0xDD34,  /*AP����DSP ���ڴ򿪿���ͨ������Ϣ*/
    ID_AP_IMGAE_DOWNLOAD       = 0xDD40,  /*AP ���� DSP���������*/
};

typedef struct
{
    unsigned short  msgID;           /*�������ѿ���ͨ������*/
    unsigned short  fastTransEnable; /*�������ѿ���ͨ��ʹ�ܱ�־*/
} FAST_TRANS_MSG_STRU;

typedef struct _PCM_IF_MSG_STRU
{
    unsigned int    uwIFId;         /* IF�� id    */
    unsigned int    uwIFDirect;     /* ���ݴ��䷽��,���� ��� ����������� */
    unsigned int    uwSampleRateIn; /* ��������� */
    unsigned int    uwSampleRateOut;/* ��������� */
    unsigned int    uwChannelCount; /* ������, ������ʶ��Ч����, λ��̶�32λ, 26λ��Ч */
    unsigned int    uwDMASetId;     /* ���id, 0 �����  */
    unsigned int    ucResolution;    /* ��Ƶ������Ч������ 16bit/24bit */

} PCM_IF_MSG_STRU;

typedef struct _PCM_PROCESS_DMA_MSG_STRU
{
   unsigned int     uwProcessId;    /* ���� id    */
   unsigned int     uwIFCount;      /* ��Ҫ��IF�ڸ���*/
   unsigned int     uwModuleID;     /* ģ��ID*/
   PCM_IF_MSG_STRU  stIFCfgList[0]; /* if�ڲ����б�,�ɱ䳤��*/
} PCM_PROCESS_DMA_MSG_STRU;
/*****************************************************************************
 ʵ������  : DSP_IF_OPEN_REQ_STRU
 ��������  : ����Ϣ��IFͨ��
*****************************************************************************/
typedef struct
{
    unsigned short                          uhwMsgId;   /*ID_AP_DSP_IF_OPEN 0xDD10*/
    unsigned short                          uhwReserve;
    PCM_PROCESS_DMA_MSG_STRU                stProcessDMA;
} DSP_IF_OPEN_REQ_STRU;

typedef struct
{
    unsigned short                          uhwMsgId;   /*ID_AP_DSP_FASTTRANS_CONFIG 0xDD17*/
    unsigned short                          uhwReserve;
    int                                     swStatus;
} FAST_TRANS_CFG_REQ_STRU;


/* Mlib para control*/
typedef struct
{
    unsigned short  msgID;
    unsigned short  reserve;
    unsigned int    uwProcessID;      /* ���� ID       */
    unsigned int    uwModuleID;       /* ģ��Module ID */
    unsigned int    uwSize;           /* ������С      */
    unsigned char   aucData[0];       /* ������ʼ��ַ  */
} MLIB_PARA_SET_REQ_STRU;

typedef struct
{
    unsigned short  msgID;
    unsigned short  reserve;
    unsigned int    uwProcessID;      /* ���� ID       */
    unsigned int    uwModuleID;       /* ģ��Module ID */
    unsigned int    uwSize;           /* ������С      */
} MLIB_PARA_GET_REQ_STRU;

typedef struct
{
    int result;
    unsigned char para_data[0];
} MLIB_PARA_GET_DATA;

/* OM control */
enum PCM_HOOK_POINT_ENUM{
    TRACK_LOG_NONE                 = 0x00000000,
    TRACK_LOG_MAINMIC              = 0x00000001,  /* ��mic����      */
    TRACK_LOG_SUBMIC               = 0x00000002,  /* ��mic����      */
    TRACK_LOG_THIRDMIC             = 0x00000004,  /* ��mic����      */
    TRACK_LOG_FORTHMIC             = 0x00000008,  /* ��mic����      */
    TRACK_LOG_UPLINK_AFTERPRO      = 0x00000010,  /* ������Ч����� */
    TRACK_LOG_UPLINK_AFTERCODE     = 0x00000020,  /* ���б����     */
    TRACK_LOG_DOWNLINK_AFTERPRO    = 0x00000100,  /* ������Ч����� */
    TRACK_LOG_DOWNLINK_AFTERCODE   = 0x00000200,  /* ���н����     */
    TRACK_LOG_DOWNLINK_BEFORECODE  = 0x00000400,  /* ���н���ǰ     */
    TRACK_LOG_SMARTPA_IN           = 0x00001000,  /* smartpa����    */
    TRACK_LOG_SMARTPA_OUT          = 0x00002000,  /* smartpa���    */
    TRACK_LOG_SMARTPA_I            = 0x00004000,  /* smartpa I�ź�  */
    TRACK_LOG_SMARTPA_V            = 0x00008000,  /* smartpa V�ź�  */
    TRACK_LOG_AEC                  = 0x00010000,  /* AEC�ο��ź�    */
    TRACK_LOG_SOUNDTRIGGER_KEYWORD = 0x00020000,  /* �������ѻ��Ѵ����� */
    TRACK_LOG_UPDATA_LEFT          = 0X00100000,  /* updata���㷨ǰ���������� */
    TRACK_LOG_UPDATA_RIGHT         = 0X00200000,  /* updata���㷨ǰ���������� */
    TRACK_LOG_ALGORITHM_FAILURE    = 0x00400000,  /* �㷨�쳣 */
};

typedef struct
{
    unsigned short  uhwMsgId;         /* OM������ϢID  0xDD14*/
    unsigned short  uhwReserve;
    unsigned int    uwHookType;       /* ץȡ����: 0-HOOK_OFF, 1-HOOK_LOG, 2-HOOK_LOG_PCM*/
    unsigned int    uwOutputMode;     /* ���ģʽ��0-Uart��1-dspif */
    unsigned int    uwPortNum;        /* ���ģʽΪdspifʱ��dsp if�˿ں� */
    unsigned int    uwForceOutPutLog; /* ǿ�����log���ݣ�0-��ǿ�ơ�1-ǿ����� */
    unsigned int    uwHookPoints;     /* ���ݹ�ȡ�� */
    unsigned int    uwLogMode;        /* ����ΪLOG����ʱ��LOG��ӡģʽ��0-ֱͨģʽ��1-����ģʽ */
    unsigned int    uwLogLevel;       /* ��ӡ����0-Error��1-Warning��2-Infor��3-Debug */
} OM_CTRL_BLOCK_STRU;

/*****************************************************************************
 ʵ������  : FW_DOWNLOAD_STRU
 ��������  : �����������ṹ��misc��hal�㹲�ã����漰hifi
*****************************************************************************/
typedef struct
{
    unsigned short                           uhwMsgId;
    unsigned short                           uhwReserve;
    char                                     chwname[50];
} FW_DOWNLOAD_STRU;

typedef struct
{
    unsigned short  uhwMsgId;/*MAD���������ϻ�����*/
    unsigned short  uhwReserve;
} MAD_TEST_STRU;

typedef struct
{
    unsigned short  uhwMsgId;   /*0xDD33,AP����DSP �����趨��ǰUARTģʽ*/
    unsigned short  uhwReserve;
    unsigned int    uwUartMode;
} UARTMODE_STRU;

typedef unsigned short  APDSP_MSG_ENUM_UINT16;
#define AUDIO_PLAY_DEBUG_OPEN_RESERVE (0x0000)

/* OM״̬��Ϣ��Ŀǰץȡ����*/
enum HOOK_TYPE_ENUM
{
    HOOK_OFF = 0,
    HOOK_LOG = 1,
    HOOK_LOG_PCM = 2,
};

/* OM״̬��Ϣ��Ŀǰץȡ����������*/
enum HOOK_FORCE_OUTPUT_LOG_ENUM
{
    HOOK_DEFUALT = 0,
    HOOK_FORCE_OUTPUT_LOG = 1,
};

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hi6402_hifi_interface.h */
