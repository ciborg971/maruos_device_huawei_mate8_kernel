#ifndef __MDRV_CCORE_SCI_H__
#define __MDRV_CCORE_SCI_H__
#ifdef __cplusplus
extern "C"
{
#endif



#define SCI_RECORD_ATR_LEN      (40)
#define SCI_RECORD_REG_LEN      (36)
#define SCI_RECORD_DATA_CNT     (20)
/*14 = 1(�շ���־)+4(ʱ���)+1(len)+8(����)*/
#define SCI_SIGLE_DATA_LEN      (14)
#define SCI_RECORD_DATA_LEN     (SCI_RECORD_DATA_CNT * SCI_SIGLE_DATA_LEN)
#define SCI_RECORD_EVENT_CNT    (80)
#define SCI_RECORD_EVENT_LEN    (SCI_RECORD_EVENT_CNT * 4 )


typedef void (*OMSCIFUNCPTR)(unsigned int ulVal);

typedef enum
{
    SIM_CARD_OUT = 0,
    SIM_CARD_IN  = 1
} SCI_DETECT_STATE_E;

typedef enum
{
	WARM_RESET = 0,     /* warm reset */
	COLD_RESET = 1,     /* cold reset */
	RESET_MODE_BUTTOM
}RESET_MODE_E;

   
/*for protocol mode*/
typedef enum
{
	T0_PROTOCOL_MODE = 0,          /*T=0*/
	T1_PROTOCOL_MODE = 1,          /*T=1*/
	PROTOCOL_MODE_BUTTOM
}PROTOCOL_MODE_E;

/*for EDC mode*/
typedef enum
{
	T1_ERR_DETECT_MODE_LRC = 0,     /*LRC*/
	T1_ERR_DETECT_MODE_CRC = 1,     /*CRC*/
	T1_ERR_DETECT_MODE_BUTTOM
}T1_ERR_DETECT_MODE_E;	

/*for dsda*/
typedef enum
{
    RF_ID0 = 0,
    RF_ID1 = 1,
    RF_ID2 = 2,
    RF_ID_BUTTOM
}RF_ID_E;

	/*for ATR info*/
typedef struct
{
	PROTOCOL_MODE_E         Tbyte;
	unsigned int            valIFSC;
	unsigned int            valIFSD;
	T1_ERR_DETECT_MODE_E    errDetectMode;
    unsigned int            tckLen;
}SCI_ATRINFO_S;

/*  SIM  Ӳ���쳣*/
typedef enum tagSCI_HW_ABNORMAL_E
{
    SCI_HW_STATE_OK  = 0,                   /*HW  OK*/
    SCI_HW_STATE_ATRSTOUT,                  /*ATR receive start timeout  */
    SCI_HW_STATE_ATRDTOUT,                  /*between ATR TIME OUT*/
    SCI_HW_STATE_TXERR,                     /*TX ERROR*/
    SCI_HW_STATE_CHTOUT,                    /*between char timeout*/
    SCI_HW_STATE_RORI,                      /*receive overrun interrupt*/

    SCI_HW_STATE_BUTT                       /* Butt*/
} SCI_HW_ABNORMAL_E;


/*for sci record info*/
typedef struct stSciRecordInfo{
    unsigned short            cardClass;                          /*����ѹ����:1800��3000*/
    unsigned short            ATRlen;                             /*ATR����ʵ�ʳ���*/
    unsigned char             ATRData[SCI_RECORD_ATR_LEN];        /*ATR���ݼ�¼��������40���ֽ�*/
    SCI_HW_ABNORMAL_E         enSciHwStatus;                      /*��¼sciӲ��״̬*/
    unsigned int              SciRegData[SCI_RECORD_REG_LEN];     /*SCI���мĴ�����¼*/
    unsigned char             SimRecordData[SCI_RECORD_DATA_LEN]; /*�Ϳ����������20�����ݣ�ÿ��������9���ֽڣ�ͬʱ���¼4�ֽ�ʱ���*/
    unsigned int              SciEvent[SCI_RECORD_EVENT_LEN];     /*SCI �ײ��¼����80����¼*/
}SCI_RECORD_INFO_S;


typedef enum
{
	SCI_CLK_STATE_LOW = 0,        /* Э���ָʾͣ��*/
	SCI_CLK_STATE_HIGH = 1,       /*Э���ָʾͣ��*/
	SCI_CLK_STATE_UNSUPPORTED = 2,/*Э���ָʾ��֧��*/
	SCI_CLK_STATE_BUTT
}SCI_CLK_STOP_TYPE_E;

/*  SIM  state*/
typedef enum tagSCI_CARD_STATE_E
{
    SCI_CARD_STATE_READY = 0,               /* Ready */
    SCI_CARD_STATE_NOCARD,                  /* No card */
    SCI_CARD_STATE_BUSY,                    /* In initialization*/
    SCI_CARD_STATE_BUTT                     /* Butt*/
} SCI_CARD_STATE_E;

/*����������������Ƶ�mdrv_sci.h�ļ�*/
typedef enum 
{
    SCI_ID_0 = 0,
    SCI_ID_1 = 1,
    SCI_ID_2 = 2,
    SCI_ID_BUTT
}SCI_SLOT;
    
/*for SCI_LOG  mode*/
typedef enum
{
    SCI_LOG_RESET_FAIL           = 0,     /*��λʧ��*/
    SCI_LOG_PROTECT_RESET_SUCC   = 1,     /*�����Ը�λ�ɹ�*/
    SCI_LOG_PROTECT_RESET_FAIL   = 2,     /*�����Ը�λʧ��*/
    SCI_LOG_NO_DATA              = 3,     /*û�����ݷ���*/
    SCI_LOG_BUF_OVER             = 4,     /*���ݽ������*/
    SCI_LOG_VOL_SWITCH_FAIL      = 5,     /*USIM��ѹ�л�ʧ��*/
    SCI_LOG_BUTT
}SCI_LOG_MODE;


	/********************************************************************************
	 *  �� �� ��  : mdrv_sci_get_cardstatus
	 *  ��������  : ���ӿ����ڻ�ÿ���ǰ��״̬��ĿǰLTE�ṩ�ӿڲ������Ͳ�һ��
	 *  �������  : �ޡ�
	 *  �������  :
	 *  �� �� ֵ  : 0:  ������Ready��
	 *             -1����δ����Ready��
	 *                    ע������  ����Ч����BSP_SCI_Reset()�������ٵ��ô˺�����
	 *********************************************************************************/
     int mdrv_sci_get_cardstatus(void);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_reset
	 *
	 * ��������  : ���ӿ����ڸ�λSCI��Smart Card Interface��������USIM��Universal
	 *           Subscriber Identity Module����
	 *
	 * �������  : void
	 * �������  : ��
	 *
	 * �� �� ֵ  : OK  ��λ�ɹ�
	 *
	 * �޸ļ�¼  : Yangzhi create
	 *
	 *****************************************************************************/
	int mdrv_sci_reset(RESET_MODE_E rstMode);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_send_data
	 *
	 * ��������  : ���ӿ����ڷ���һ�����ݵ�USIM��
	 *
	 * �������  : unsigned int u32DataLength �������ݵ���Ч���ȡ�ȡֵ��Χ1��256����λΪ�ֽ�
	 *             unsigned char *pu8DataBuffer �������������ڴ���׵�ַ�����Ƕ�̬���䣬���ýӿ�
	 *                                   ���������ͷţ�������Ӳ����������
	 * �������  : ��
	 *
	 * �� �� ֵ  : OK
	 *           BSP_ERR_SCI_NOTINIT
	 *           BSP_ERR_SCI_INVALIDPARA
	 *           BSP_ERR_SCI_DISABLED
	 *           BSP_ERR_SCI_NOCARD
	 *           BSP_ERR_SCI_NODATA
	 *
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/
	int mdrv_sci_send_data(unsigned int u32DataLength, unsigned char * pu8DataBuffer);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_recv
	 *
	 * ��������  : ���ӿ�����USIM Manager��ȡ����SCI Driver�Ŀ���������
	 *             �ýӿ�Ϊ�����ӿڣ�ֻ��SCI���յ��㹻����������Ż᷵�أ�
	 *             �ýӿڵĳ�ʱ����Ϊ1s
	 *
	 * �������  : unsigned int u32DataLength USIM Manager����SCI Driver��ȡ�����ݳ��ȡ�
	 * �������  : unsigned char *pu8DataBuffer USIM Managerָ����Buffer��SCI Driver�����ݿ�������Buffer��
	 * �� �� ֵ  : OK
	 *             BSP_ERR_SCI_NOTINIT
	 *             BSP_ERR_SCI_INVALIDPARA
	 *
	 * �޸ļ�¼  : Yangzhi create
	 *
	 *****************************************************************************/
	int mdrv_sci_recv(unsigned int u32DataLength, unsigned char * pu8DataBuffer);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_get_atr
	 *
	 * ��������  : ���ӿ����ڽ�Driver�㻺���ATR���ݺ����ݸ������ظ�USIM Manager��
	 *
	 * �������  : void
	 * �������  : unsigned long *u8DataLength  Driver��ȡ��ATR���ݳ��ȣ����ظ�USIM Manager��
	 *                                   ȡֵ��Χ0��32����λ���ֽ�
	 *           unsigned char *pu8ATR          USIM Managerָ����Buffer��SCI Driver��ATR
	 *                                   ���ݿ�������Buffer��һ��Ϊ����ϵͳ������̬����
	 *                                   ���߾�̬����ĵ�ַ
	 *
	 *
	 * �� �� ֵ  : OK
	 *          BSP_ERR_SCI_NOTINIT
	 *          BSP_ERR_SCI_INVALIDPARA
	 *
	 * �޸ļ�¼  : Yangzhi create
	 *
	 *****************************************************************************/
	int mdrv_sci_get_atr(unsigned long * u32DataLength, unsigned char * pu8ATR,SCI_ATRINFO_S* stSCIATRInfo);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_switch_class
	 *
	 * ��������  : ���ӿ�����֧��PS�Կ��ĵ�ѹ���ͽ����л�����1.8V�л���3V
	 *
	 * �������  : void
	 * �������  : ��
	 *
	 * �� �� ֵ  :  OK    ��ǰ��ѹ������ߵģ����е�ѹ�л�����
	 *           BSP_ERR_SCI_CURRENT_STATE_ERR �л�ʧ�� current SCI driver state is ready/rx/tx
	 *           BSP_ERR_SCI_VLTG_HIGHEST   ��ǰ��ѹ�Ѿ�����ߵ�ѹ��û�н��е�ѹ�л�
	 *           BSP_ERR_SCI_NOTINIT
	 *           BSP_ERR_SCI_CURRENT_VLTG_ERR ��ǰ��ѹֵ�쳣����class B����C��
	 *
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/
	int  mdrv_sci_switch_class(void);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_stop_tm
	 *
	 * ��������  : ���ӿ�����֧��PS�ر�SIM��ʱ��
	 *
	 * �������  :
	 *           SCI_CLK_STOP_TYPE_E enTimeStopCfg ʱ��ֹͣģʽ
	 *
	 * �������  : ��
	 *
	 * �� �� ֵ  : OK - successful completion
	 *               ERROR - failed
	 *               BSP_ERR_SCI_NOTINIT
	 *               BSP_ERR_SCI_INVALIDPARA - invalid mode specified
	 *               BSP_ERR_SCI_UNSUPPORTED - not support such a operation
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/
	int mdrv_sci_stop_tm(SCI_CLK_STOP_TYPE_E enTimeStopCfg);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_deact
	 *
	 * ��������  : ���ӿ����ڶ�SIM����ȥ�������
	 *
	 * �������  : ��
	 *
	 * �������  : ��
	 *
	 * �� �� ֵ  : OK
	 *             BSP_ERR_SCI_NOTINIT
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/
	unsigned int mdrv_sci_deact(void);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_get_clkstat
	 *
	 * ��������  : ���ӿ����ڻ�ȡ��ǰSIM��ʱ��״̬ (v8 ��׮����0)
	 *
	 * �������  : unsigned int *pu32SciClkStatus   ����ָ�룬���ڷ���SIM��ʱ��״̬��
	 *                                       0��ʱ���Ѵ򿪣�
	 *                                       1��ʱ��ֹͣ
	 * �������  : ��
	 *
	 * �� �� ֵ  : OK    �����ɹ�
	 *             BSP_ERR_SCI_INVALIDPARA
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/
	unsigned int mdrv_sci_get_clkstat(unsigned int * pu32SciClkStatus);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_get_clkfreq
	 *
	 * ��������  : ���ӿ����ڻ�ȡ��ǰSIM��ʱ��Ƶ��
	 *
	 * �������  : ��
	 *
	 * �������  : unsigned long *pLen   ʱ��Ƶ�����ݵĳ���
	 *             unsigned char        *pBuf   ʱ��Ƶ������
	 * �� �� ֵ  : OK    �����ɹ�
	 *             BSP_ERR_SCI_INVALIDPARA
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/
	unsigned int mdrv_sci_get_clkfreq(unsigned long * pLen,unsigned char * pBuf);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_get_baudrate
	 *
	 * ��������  : ���ӿ����ڻ�ȡ��ǰSIM��ʱ��Ƶ��
	 *
	 * �������  : ��
	 *
	 * �������  : unsigned long *pLen   ���������ݵĳ���
	 *             unsigned char i      *pBuf   ����������
	 *
	 * �� �� ֵ  : OK    �����ɹ�
	 *             BSP_ERR_SCI_INVALIDPARA
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/
	unsigned int mdrv_sci_get_baudrate(unsigned long * pLen, unsigned char * pBuf);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_get_parameter
	 *
	 * ��������  : ���ӿ����ڻ�ȡ��ǰSIM����PCSC��ز���
	 *
	 * �������  : ��
	 *
	 * �������  : unsigned char *pBuf    PCSC��ز���
	 *
	 * �� �� ֵ  : OK    �����ɹ�
	 *             BSP_ERR_SCI_INVALIDPARA
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/
	unsigned int mdrv_sci_get_parameter(unsigned char * pBuf);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_get_errno
	 *
	 * ��������  : ���ӿڻ�ȡ�ӿڵ��÷��صĴ�����
	 * �������  :  ��
	 * �������  :  ��
	 *
	 * �� �� ֵ  : ������
	 *
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/
	int mdrv_sci_get_errno(void);

	/*****************************************************************************
	 *  �� �� ��  : mdrv_sci_save_recorddata
	 *  ��������  : ���ӿ����ڻ�ȡ��ǰSIM���������ݡ������쳣����ģ�飬V7�ȴ�׮
	 *  �������  : �ޡ�
	 *  �������  : ��
	 *  �� �� ֵ  : na
	 *  ע������  ��
	 ******************************************************************************/
	void mdrv_sci_save_recorddata(void);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_register_callback
	 *
	 * ��������  : ���ӿ�����ע��OAM�Ļص�����
	 *
	 * �������  : omSciFuncPtr
	 * �������  : ��
	 *
	 * �� �� ֵ  : NA
	 *
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/
	void mdrv_sci_register_callback(OMSCIFUNCPTR omSciFuncPtr);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_recv_all
	 *
	 * ��������  : ���ӿ�����USIM Manager�ڶ�����ʱ��ʱ�򣬵��ñ�������
	 *             ��ȡ�������ݻ����е���������
	 *
	 * �������  : ��
	 * �������  : unsigned int *u32DataLength Driver��ȡ�����ݳ��ȣ����ظ�USIM Manager��
	 *                                ȡֵ��Χ1��256����λ���ֽ�
	 *             unsigned char  *pu8DataBuffer USIM Managerָ����Buffer��SCI Driver��
	 *                                ���ݿ�������Buffer
	 *
	 * �� �� ֵ  : OK
	 *          BSP_ERR_SCI_NOTINIT
	 *          BSP_ERR_SCI_INVALIDPARA
	 *
	 * �޸ļ�¼  : Yangzhi create
	 *
	 *****************************************************************************/
	unsigned int mdrv_sci_recv_all(unsigned int *u32DataLength,unsigned char * pu8DataBuffer);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_show_voltage
	 *
	 * ��������  : ���ӿ�������ʾ��ǰSIM���ӿڵ�ѹ
	 *
	 * �������  : ��
	 * �������  :unsigned int * pu32Vltgval ��ǰ��ѹ
	 *
	 * �� �� ֵ  : OK
	 *          BSP_ERR_SCI_NOTINIT
	 *          BSP_ERR_SCI_INVALIDPARA
	 *
	 * �޸ļ�¼  : Yangzhi create
	 *
	 *****************************************************************************/
	unsigned int  mdrv_sci_show_voltage(unsigned int* pu32Vltgval);

	/* T=1 add Begin:*/
	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_set_bwt
	 *
	 * ��������  : ���ӿ��������ÿ�ȴ�ʱ��
	 *
	 * �������  : unsigned int nBWT:  ���ó�ʱʱ��ΪBWT��nBWT��
	 *
	 * �������  : ��
	 *
	 * �� �� ֵ  : OK/ERROR
	 * �޸ļ�¼  : 2013��10��15��   liuyi  creat
	 *
	 *****************************************************************************/
	int mdrv_sci_set_bwt(unsigned int nBWT);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_switch_protocol
	 *
	 * ��������  : ���ӿ�����֪ͨ�������T=0��T=1Э�������л�
	 *
	 * �������  : RESET_MODE_E enSIMProtocolMode:��Ҫ�л�Ϊ��Э������
	 *
	 * �������  : ��
	 *
	 * �� �� ֵ  : OK/ERROR
	 * �޸ļ�¼  : 2013��10��15��   liuyi  creat
	 *
	 *****************************************************************************/
	int mdrv_sci_switch_protocol(PROTOCOL_MODE_E enSIMProtocolMode);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_rcv_blk
	 * ��������  : ���ӿ�������T=1ʱUSIM Manager��ȡ����SCI Driver�Ŀ��������ݣ�
	 *             �������BWT��ʱ�������ݶ�ȡʱ����һ����ʱ��ֵSCI_TIMEOUT
	 *
	 * �������  : ��
	 * �������  : unsigned char  *pu8Data USIM Managerָ����Buffer��SCI Driver�����ݿ�������Buffer��
	 *             unsigned int *pulLength SCI Driver���յ������ݳ��ȡ�
	 *
	 * �� �� ֵ  : OK : 0
	 *             ERROR : -1
	 *             SCI_TIMEOUT : 1
	 *
	 * �޸ļ�¼  : 2013��10��15��   liuyi  creat
	 *
	 *****************************************************************************/
	int mdrv_sci_rcv_blk(unsigned char *pu8Data,unsigned int *pulLength);

	/*****************************************************************************
	 * �� �� ��  : mdrv_sci_read_recordlog
	 *
	 * ��������  : ���ӿڻ�ȡsim���쳣ʱ��λ��Ϣ
	 * �������  : pucDataBuff: ��ȡ��λ��Ϣ��buffer
	 *             ulMaxLength: ���ֵ���ж�ʹ��
	 *
	 * �� �� ֵ  : pulLength: ��ȡ���ݳ���
	 *
	 *
	 * �� �� ֵ  : ��
	 *
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/
	int  mdrv_sci_read_recordlog(unsigned char *pucDataBuff, unsigned int * pulLength, unsigned int ulMaxLength);
	/* T=1 add End */

    /*****************************************************************************
	 * �� �� ��  : mdrv_sci_slot_switch
	 *
	 * ��������  : �л����뿨�۵Ķ�Ӧ��ϵ
	 * �������  : sci_slot0 ����0������״̬
	 *                           sci_slot1 ����1������״̬
	 *
	 * �� �� ֵ  : �л����
	 *
	 *
	 * �� �� ֵ  : ��
	 *
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/
    int mdrv_sci_slot_switch(SCI_SLOT sci_slot0,SCI_SLOT sci_slot1,SCI_SLOT sci_slot2);

    /*****************************************************************************
	 * �� �� ��  : mdrv_sci_get_slot_state
	 *
	 * ��������  : ��ȡ���۵Ķ�Ӧ��ϵ
	 * �������  : sci_slot0 ����0��״̬
	 *                           sci_slot1 ����1��״̬
	 *
	 * �� �� ֵ  : �л����
	 *
	 *
	 * �� �� ֵ  : ��
	 *
	 * �޸ļ�¼  :
	 *
	 *****************************************************************************/

    int mdrv_sci_get_slot_state(SCI_SLOT* sci_slot0,SCI_SLOT* sci_slot1,SCI_SLOT* sci_slot2);

#ifdef __cplusplus
}
#endif

#endif

