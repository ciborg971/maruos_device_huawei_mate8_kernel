

#ifndef _BSP_WM8990_H_
#define _BSP_WM8990_H_

#include "drv_audio.h"

#ifdef __cplusplus
extern "C" { /* allow C++ to use these headers */
#endif /* __cplusplus */

typedef enum
{
    PCM_MODE,
    I2S_MODE
}HI6411_MODE;

/*���ֳ���֮����ܻ������ϣ���FM���������ֲ��� */
typedef enum
{
    AUD_SCENE_IDLE=0x00,
    AUD_SCENE_PLAY=0x01,      /*���ֲ��� */
    AUD_SCENE_RECORD=0x02,    /*¼�� */
    AUD_SCENE_CALLBACK=0x03,  /*ý�岥¼�� */
    AUD_SCENE_VOICE=0x04,     /*һ��ͨ����ͨ��¼�� */
    AUD_SCENE_VOICE_RSP=0x08, /*�绰�Զ�Ӧ�� */
    AUD_SCENE_FM_RX=0x10,     /*FM���� */
    AUD_SCENE_FM_TX=0x20,     /*FM���� */

    /*AUD_SCENE_B_PLAY=0x21,    //BT���� */
    /*AUD_SCENE_B_RECORD=0x22, */
    AUD_SCENE_B_VOICE=0x40    /*BTͨ�� BTͨ��¼�� */
}AUDIO_SCENE;

typedef enum
{
    VL_DN_DACL_VOL=0,
    VL_DN_DACR_VOL,
    VL_DN_DAC_BOOST,
    VL_DN_LOPGAVOL,
    VL_DN_ROPGAVOL,
    VL_DN_LROPGAVOL,
    VL_DN_LOUTVOL,
    VL_DN_ROUTVOL,
    VL_DN_LROUTVOL,
    VL_DN_OUT3ATTN,
    VL_DN_OUT4ATTN,
    VL_DN_SPKATTN,
    VL_DN_SPKVOL,
    VL_DN_DCGAIN,
    VL_DN_ACGAIN
}AUDIO_DOWN_AMPLIFIER;

typedef enum
{
    VL_UP_ADCL_VOL=0,
    VL_UP_ADCR_VOL,
    VL_UP_LIN12VOL,
    VL_UP_LIN34VOL,
    VL_UP_RIN12VOL,
    VL_UP_RIN34VOL,
    VL_UP_L12MNBST,
    VL_UP_L34MNBST,
    VL_UP_R12MNBST,
    VL_UP_R34MNBST
}AUDIO_UP_AMPLIFIER;

typedef unsigned int AUDIO_UINT32;
typedef unsigned short AUDIO_UINT16;
typedef unsigned char AUDIO_UINT8;

int wm8990_probe(void);
int wm8990_open(void);
int wm8990_close(void);
int wm8990_samplerate_set(HI6411_MODE mode, AUDIO_SAMPLE_RATE ulSampleRate);
int wm8990_vol_up_set(AUDIO_UP_AMPLIFIER amplifier, AUDIO_UINT16 usVolume);
int wm8990_vol_up_dig_set(AUDIO_UINT16 usVol);
int wm8990_vol_down_set(AUDIO_DOWN_AMPLIFIER amplifier, AUDIO_UINT16 usVolume);
int wm8990_vol_down_dig_set(AUDIO_UINT16 usVol);
int wm8990_indev_sel(AUDIO_DEV_TYPE eAudioDev);
int wm8990_indev_unsel(AUDIO_DEV_TYPE eAudioDev);
int wm8990_outdev_sel(AUDIO_DEV_TYPE eAudioDev);
int wm8990_outdev_unsel(AUDIO_DEV_TYPE eAudioDev);
int wm8990_pcm_down(void);
int wm8990_pcm_up(void);
int wm8990_i2s_down(void);
int wm8990_i2s_up(void);
int wm8990_play_open(void);
int wm8990_play_close(void);
int wm8990_record_open(void);
int wm8990_record_close(void);
int wm8990_playrecord_open(void);
int wm8990_playrecord_close(void);
int wm8990_voice_open(void);
int wm8990_voice_close(void);
int wm8990_fm_rx_open(void);
int wm8990_fm_rx_close(void);
int wm8990_fm_tx_open(void);
int wm8990_fm_tx_close(void);
int wm8990_nv_op(AUDIO_UINT32 Data);

/*****************************************************************
 *  Structure: 
 *		codec_operation
 *	
 *  Description:  
 *		codec�����ӿ�
 *
 *  Member:
 *		init				��ʼ������ָ��
 *		sleep				˯�ߺ���ָ��
 *		scale_dynamic_freq	��̬Ƶ�ʵ��ں���ָ��
 *
 ******************************************************************/
struct codec_operation 
{
    int (*open)(void);
    int (*close)(void);
    int (*samplerate_set)(HI6411_MODE mode, AUDIO_SAMPLE_RATE ulSampleRate);
    int (*indev_sel)(AUDIO_DEV_TYPE eAudioDev);
    int (*indev_unsel)(AUDIO_DEV_TYPE eAudioDev);
    int (*outdev_sel)(AUDIO_DEV_TYPE eAudioDev);
    int (*outdev_unsel)(AUDIO_DEV_TYPE eAudioDev);
    int (*pcm_down)(void);
    int (*pcm_up)(void);
    int (*i2s_down)(void);
    int (*i2s_up)(void);
    int (*vol_up_dig_set)(AUDIO_UINT16 usVolume);
    int (*vol_down_dig_set)(AUDIO_UINT16 usVolume);
    int (*play_open)(void);
    int (*play_close)(void);
    int (*record_open)(void);
    int (*record_close)(void);
    int (*playrecord_open)(void);
    int (*playrecord_close)(void);
    int (*voice_open)(void);
    int (*voice_close)(void);
    int (*fm_rx_open)(void);
    int (*fm_rx_close)(void);
    int (*fm_tx_open)(void);
    int (*fm_tx_close)(void);
};

extern struct codec_operation wm8990_operation;

#ifdef __cplusplus
} /* allow C++ to use these headers */
#endif /* __cplusplus */

#endif

