

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#ifndef __PWRCTRL_POWER_STATE_MANGER_H__
#define __PWRCTRL_POWER_STATE_MANGER_H__

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/string.h>


#include "io.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define PWRCTRL_MAGIC_OFFSET 24
#define PWRCTRL_STATE_OFFSET 16
#define PWRCTRL_MODULE_ID_OFFSET 0
	
#define PWRCTRL_STATE_MAGIC 0xBD

#define PWRCTRL_POWER_STAT_INVALID_ID          (-1)

#define bool_t  unsigned int
#define void_t  void

#define s8_t    char
#define s16_t   short
#define s32_t   int

#define u8_t    unsigned char
#define u16_t   unsigned short
#define u32_t   unsigned int
#define u64_t   unsigned long long



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum tagPWRCTRL_SLEEP_STATE_CLIENT_ID_E
{
	PWRCTRL_SLEEP_USB,
	PWRCTRL_SLEEP_EMMC,
	PWRCTRL_SLEEP_SDCARD,
	PWRCTRL_SLEEP_EDMAC,
	PWRCTRL_SLEEP_SDIO,
	PWRCTRL_SLEEP_ADE,
	PWRCTRL_SLEEP_CLIENT_BUTT
}PWRCTRL_SLEEP_STATE_CLIENT_ID_E;

typedef enum tagPWCTRL_SLEEP_STATE_ID_E
{
	PWRCTRL_SYS_STAT_S1,
	PWRCTRL_SYS_STAT_S2,
	PWRCTRL_SYS_STAT_S3,
	PWRCTRL_SYS_STAT_BUTT
}PWRCTRL_SLEEP_STATE_ID_E;
typedef enum
{
    RET_ERR_PARAM_NULL = -0xF000,
    RET_ERR_PARAM_INVALID,
    RET_ERR_OVERFLOW,
    RET_ERR_INSUFFICIENT,
    RET_ERR_LIMITED,
    RET_ERR_NOT_FOUND,
    RET_ERR_NOT_OPEN,
    RET_ERR_DUPLICATE,
    RET_ERR_CONNECT_FAIL,
    RET_ERR_TIME_OUT,
    RET_ERR_UNKNOWN,
    RET_ERR = -1,
    RET_OK = 0
} EM_PWC_RET;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
typedef struct PWRCTRL_POWER_STAT_QOS_ID_S
{
	int pwrctrl_power_stater_usb_qos_id;
	int pwrctrl_power_stater_emmc_qos_id;
	int pwrctrl_power_stater_sdcard_qos_id;
	int pwrctrl_power_stater_edmac_qos_id;
	int pwrctrl_power_stater_ade_qos_id;
}PWRCTRL_POWER_STAT_QOS_ID;

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/
extern unsigned int  *g_pwrctrl_sleep_state_votemap ;






/*****************************************************************************
  10 ��������
*****************************************************************************/

extern s32_t  pwrctrl_request_power_state( s32_t module_id, s32_t state, s32_t *req_id);


extern s32_t  pwrctrl_release_power_state( s32_t req_id);








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


