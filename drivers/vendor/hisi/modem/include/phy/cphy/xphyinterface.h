
#ifndef __XPHY_INTERFACE_H__
#define __XPHY_INTERFACE_H__

#include "uphy_config.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define XPHY_MAILBOX_BASE_ADDR                      (CPHY_PUB_DTCM_BASE)

/* ���������С����*/
#define XPHY_MAILBOX_SHARE_MEM_SIZE                 (0x00000400UL)  /*1k�ֽڣ�TBD*/
#define XPHY_MAILBOX_HDLC_BUF_SIZE                  (0x00002000UL)  /*8K�ֽ�, TBD*/
#define XPHY_MAILBOX_LHPA_UP_SIZE                   (0x00002000UL)  /*8K�ֽڣ�PS���������С*/
#define XPHY_MAILBOX_LHPA_DOWN_SIZE                 (0x00002000UL)  /*8k�ֽڣ�PS���������С*/
#define XPHY_MAILBOX_OM_DOWN_SIZE                   (0x00000800UL)  /*2k�ֽڣ�OM���������С*/


#define XPHY_MAILBOX_XPHY_WORKING_MODE_ADDR         (XPHY_MAILBOX_BASE_ADDR + 0x0340)
#define XPHY_MAILBOX_LOAD_MEMORY_ADDR               (XPHY_MAILBOX_BASE_ADDR + 0x020C)   /*������ʼ�����ֵ�ַ*/
#define XPHY_MAILBOX_HDLC_BUF_BASE_ADDR             (XPHY_MAILBOX_BASE_ADDR  + XPHY_MAILBOX_SHARE_MEM_SIZE)
#define XPHY_MAILBOX_LHPA_UP_BASE_ADDR              (XPHY_MAILBOX_HDLC_BUF_BASE_ADDR + XPHY_MAILBOX_HDLC_BUF_SIZE)
#define XPHY_MAILBOX_LHPA_DOWN_BASE_ADDR            (XPHY_MAILBOX_LHPA_UP_BASE_ADDR + XPHY_MAILBOX_LHPA_UP_SIZE)
#define XPHY_MAILBOX_OM_DOWN_BASE_ADDR              (XPHY_MAILBOX_LHPA_DOWN_BASE_ADDR + XPHY_MAILBOX_LHPA_DOWN_SIZE)






#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* __MEM_MAP_BASE_H__ */
