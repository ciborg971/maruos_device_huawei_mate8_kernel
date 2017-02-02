

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#include "bsp_shared_ddr.h"
#include "drv_mailbox_cfg.h"
#include "drv_mailbox_gut.h"

#if defined(_DRV_LLT_)
#include "drv_mailbox_stub.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    ��ά�ɲ���Ϣ�а�����C�ļ���ź궨��
*****************************************************************************/
#undef  _MAILBOX_FILE_
#define _MAILBOX_FILE_   "table"
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*���������Ѵ��ڵĹ����ڴ�ͨ���������ڴ漰Ӳ����Դ���ã�ȫ�ֶ���*/
MAILBOX_EXTERN struct mb_cfg g_mailbox_global_cfg_tbl[10] =
{
#if 0
    /*CCPU�������˵�ͨ��*/
    MAILBOX_CHANNEL_COMPOSE(CCPU, MCU,  MSG),
//    MAILBOX_CHANNEL_COMPOSE(CCPU, MCU,  IFC),
    MAILBOX_CHANNEL_COMPOSE(CCPU, HIFI, MSG),
//    MAILBOX_CHANNEL_COMPOSE(CCPU, ACPU, IFC),
//    MAILBOX_CHANNEL_COMPOSE(CCPU, ACPU, MSG),

    /*ACPU�������˵�ͨ��*/
    MAILBOX_CHANNEL_COMPOSE(ACPU, MCU,  MSG),
//    MAILBOX_CHANNEL_COMPOSE(ACPU, MCU,  IFC),
    MAILBOX_CHANNEL_COMPOSE(ACPU, HIFI, MSG),
//    MAILBOX_CHANNEL_COMPOSE(ACPU, CCPU, IFC),
//    MAILBOX_CHANNEL_COMPOSE(ACPU, CCPU, MSG),

    /*MCU�������˵�ͨ��*/
    MAILBOX_CHANNEL_COMPOSE(MCU, CCPU,  MSG),
//    MAILBOX_CHANNEL_COMPOSE(MCU, CCPU,  IFC),
    MAILBOX_CHANNEL_COMPOSE(MCU, ACPU,  MSG),
//    MAILBOX_CHANNEL_COMPOSE(MCU, ACPU,  IFC),

    /*HIFI�������˵�ͨ��*/
    MAILBOX_CHANNEL_COMPOSE(HIFI, CCPU, MSG),
    MAILBOX_CHANNEL_COMPOSE(HIFI, ACPU, MSG),
#else
    MAILBOX_CHANNEL_COMPOSE(ACPU, HIFI, MSG),
    MAILBOX_CHANNEL_COMPOSE(HIFI, ACPU, MSG),
    MAILBOX_CHANNEL_COMPOSE(CCPU, HIFI, MSG),
    MAILBOX_CHANNEL_COMPOSE(HIFI, CCPU, MSG),
#endif

    /*������־*/
    {MAILBOX_MAILCODE_INVALID,  0,  0, 0}

};

/*ƽ̨����ͨ��������ڴ�ؿռ�*/
MAILBOX_EXTERN struct mb_buff     g_mailbox_channel_handle_pool[MAILBOX_CHANNEL_NUM];

/*ƽ̨�����û��ص�������ڴ�ؿռ�*/
MAILBOX_EXTERN struct mb_cb    g_mailbox_user_cb_pool[MAILBOX_USER_NUM];

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

