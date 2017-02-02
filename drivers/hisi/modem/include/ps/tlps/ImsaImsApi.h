

#ifndef __IMSAIMSAPI_H__
#define __IMSAIMSAPI_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
enum IMSA_VOICE_CODEC_ENUM
{
    IMSA_VOICE_CODEC_AMR_NB = 0,
    IMSA_VOICE_CODEC_EFR,
    IMSA_VOICE_CODEC_FR,
    IMSA_VOICE_CODEC_HR,
    IMSA_VOICE_CODEC_AMR_NB2,
    IMSA_VOICE_CODEC_AMR_WB,
    IMSA_VOICE_CODEC_G711,
    IMSA_VOICE_CODEC_BUTT
};
typedef unsigned short IMSA_VOICE_CODEC_ENUM_UINT16;

enum IMSA_CODEC_AMR_TYPE_TX_ENUM
{
    IMSA_CODEC_AMR_TYPE_TX_SPEECH_GOOD   = 0,
    IMSA_CODEC_AMR_TYPE_TX_SID_FIRST,
    IMSA_CODEC_AMR_TYPE_TX_SID_UPDATE,
    IMSA_CODEC_AMR_TYPE_TX_NO_DATA,
    IMSA_CODEC_AMR_TYPE_TX_SPEECH_DEGRADED,
    IMSA_CODEC_AMR_TYPE_TX_SPEECH_BAD,
    IMSA_CODEC_AMR_TYPE_TX_SID_BAD,
    IMSA_CODEC_AMR_TYPE_TX_ONSET,
    IMSA_CODEC_AMR_TYPE_TX_BUTT
};
typedef unsigned short IMSA_CODEC_AMR_TYPE_TX_ENUM_UINT16;

/* TIMER */
enum IMSA_TIMER_PRECISION_ENUM
{
    IMSA_TIMER_PRECISION_0   = 0,
    IMSA_TIMER_PRECISION_5   = 5,
    IMSA_TIMER_PRECISION_10   = 10,
    IMSA_TIMER_PRECISION_20   = 20,
    IMSA_TIMER_PRECISION_30   = 30,
    IMSA_TIMER_PRECISION_40   = 40,
    IMSA_TIMER_PRECISION_50   = 50,
    IMSA_TIMER_PRECISION_60   = 60,
    IMSA_TIMER_PRECISION_70   = 70,
    IMSA_TIMER_PRECISION_80   = 80,
    IMSA_TIMER_PRECISION_90   = 90,
    IMSA_TIMER_PRECISION_100   = 100,
    IMSA_TIMER_NO_PRECISION,
    IMSA_TIMER_PRECISION_BUTT
};
typedef unsigned int IMSA_TIMER_PRECISION_ENUM_UINT32;


typedef enum
{
    IMSA_IMS_TIMER_NAME_XXX = 500,
    IMSA_IMS_TIMER_NAME_BUTT
}IMSA_IMS_TIMER_NAME_ENUM;

typedef void (*TIMER_FUNC)(unsigned int ulParam, unsigned int ulTimerName);

typedef struct
{
    unsigned int                     ulLen;          /*��ʱ��ʱ������λmillisecond*/
    unsigned int                     ulTimerName;    /*��ʱ��������ʶ��ʱ��������IMSA_IMS_TIMER_NAME_ENUMö��ֵ*/
    unsigned int                     ulParam;        /*��ʱ�����Ӳ���*/
    unsigned char                    ucMode;         /*��ʱ������ģʽ��0���ζ�ʱ��,1ѭ����ʱ������ʱ�Զ�����*/
    unsigned char                    ucRever[3];
    IMSA_TIMER_PRECISION_ENUM_UINT32 enPrecision;    /*��ʱ�����ȣ���ʾ�����̵Ķ�ʱ���ٷֱ�*/
    TIMER_FUNC                       TimeOutRoutine; /*�ص���������ʱ����ʱ����ã��ص������Ĳ���ΪulTimerName��ulTimerName*/
}IMSA_TIMER_PARA_STRU;


typedef struct
{
    IMSA_VOICE_CODEC_ENUM_UINT16  enCodecType;   /*��ǰ����֡��codec����,0��ʾAMR,5��ʾWB AMR,6��ʾG711*/
    unsigned short                usDtxEnable;   /*��֡�ı���DTX�Ƿ����ã�0��ʾ��������1��ʾ����*/
    unsigned short                usRateMode;    /*��֡�ı���������ʣ�ֵΪ0��8��AMR��AMR_WBʱ��Ч*/
    unsigned short                usErrorFlag;   /*��֡�Ƿ���lost packet,0��ʾ��1��ʾ��*/
    unsigned short                usFrameType;   /* ���б�֡��FrameType */
    unsigned short                usQualityIdx;  /* Quality indification */
    unsigned short                usSN;          /* �����к� */
    unsigned short                usReserve;
    unsigned long                 ulTS;          /* ��ʱ��� */
    unsigned long                 ulSsrc;        /* synchronization source */
}IMSA_RX_VOICE_PARA_STRU;


typedef struct
{
    IMSA_CODEC_AMR_TYPE_TX_ENUM_UINT16  usStatus;
    unsigned short                      usFrameType;  /* ���б�֡��FrameType */
}IMSA_TX_VOICE_PARA_STRU;



/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/**
 * \brief ��˼�ṩ��API������IMSЭ��ջ��绰����HIFI�������������ʽ�ı�ʱ���ã�
 *        �ڸ�API�У�IMSA��֪ͨHIFI��������룬��������codec����
 * @param[in]   enCodeType     ��������codec����
 * @retval 0�ɹ���1ʧ��
 */
extern unsigned int IMSA_StartVoiceDsp
(
    IMSA_VOICE_CODEC_ENUM_UINT16    enCodecType,
    unsigned long                   ulPacketTime,
    unsigned long                   ulSendBitrate
);

/**
 * \brief ��˼�ṩ��API������IMSЭ��ջ�ڹҶ����е绰�����
 *        �ڸ�API�У�IMSA��֪ͨHIFI,ֹͣ���������
 * @retval 0�ɹ���1ʧ��
 */
extern unsigned int IMSA_StopVoiceDsp(void);

/**
 * \brief ��˼�ṩ��API������IMSЭ��ջ�յ��������ݺ���ã�
 *        ���������ݷ��͸�HIFI��HIFI�յ����������
 * @param[in]   pstVoicePara   ������Ϣ��ŵ�ַ�������ݿռ��ɵ������ͷ�
 * @param[in]   pusData        �������ݴ�ŵ�ַ���ռ��СΪ160byte�������ݿռ��ɵ������ͷ�
 * @retval 0�ɹ���1ʧ��
 */
extern unsigned int IMSA_Send2HifiRxVoiceData(const IMSA_RX_VOICE_PARA_STRU *pstVoicePara,
                                                        const unsigned short *pusData);
/**
 * \brief IMSЭ��ջ�ṩ����˼��API��
 *        HIFI���������������󣬷���������IMSA��IMSA�յ�����ø�API�������ݷ���IMSЭ��ջ
 * @param[in]   pstVoicePara   ������Ϣ��ŵ�ַ�������ݿռ��ɵ�����(��˼)�ͷ�
 * @param[in]   pusData        �������ݴ�ŵ�ַ���ռ��СΪ160byte�������ݿռ��ɵ�����(��˼)�ͷ�
 * @retval ��
 */
extern void IMSA_Send2ImsTxVoiceData(const IMSA_TX_VOICE_PARA_STRU *pstVoicePara,
                                              const unsigned short *pusData);

/**
 * \brief ��˼�ṩ��API������IMSЭ��ջ��IMSA������Ϣʱ����
 *
 * @param[in]   pstOutputEvent    �¼���ŵ�ַ�������ݿռ��ɵ������ͷţ�����ΪIMSA_IMS_OUTPUT_EVENT_STRU
 * @retval 0�ɹ���1ʧ��
 */
extern unsigned int IMSA_Send2ImsaMsg(void *pstOutputEvent);

/**
 * \brief ��˼�ṩ����API������IMSЭ��ջ������ʱ��
 *
 * @param[in]    pstTimerPara�� ��ʱ��������ŵ�ַ�������ݿռ��ɵ������ͷ�
 * @retval 0�ɹ���1ʧ��
 */
extern unsigned int IMSA_ImsStartTimer(const IMSA_TIMER_PARA_STRU  *pstTimerPara);


/**
 * \brief ��˼�ṩ��API������IMSЭ��ջֹͣ��ʱ��
 *
 * @param[in]    ulTimerName�� ��ʱ������
 * @retval 0�ɹ���1ʧ��
 */
extern unsigned int IMSA_ImsStopTimer(unsigned int  ulTimerName);

/**
 * \brief IMSЭ��ջ�ṩ����˼��API������IMSЭ��ջ�ĳ�ʼ��
 * @retval 0ʧ�ܣ�1�ɹ�
 */
extern unsigned int IMSA_ImsInit(void);


/**
 * \brief IMSЭ��ջ�ṩ����˼��API�����ڸ�IMSЭ��ջ�����¼�
 *
 * @param[in]    pstInputEvent�� INPUT�¼�ָ�� ����ΪIMSA_IMS_INPUT_EVENT_STRU
 * @retval 0ʧ�ܣ�1�ɹ�
 */
extern unsigned int IMSA_WriteImsEvent(void *pstInputEvent);

/**
 * \brief IMSЭ��ջ�ṩ����˼��API������IMSЭ��ջ�ṩSrvcc������ת��CS��ĺ����б�
 *
 * @param[in]    pstSrvccCallList�� ����ΪIMSA_IMS_SRVCC_CALL_LIST_STRU���ڴ��ɺ�˼����
 * @retval 0ʧ�ܣ�1�ɹ�
 */
extern unsigned int IMSA_ImsWriteSrvccCallList(void *pstSrvccCallList);

/*****************************************************************************
  9 OTHERS
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

#endif /* end of ImsaImsApi.h */




