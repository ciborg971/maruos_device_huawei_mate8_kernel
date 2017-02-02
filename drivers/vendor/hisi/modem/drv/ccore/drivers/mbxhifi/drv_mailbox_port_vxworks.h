
#ifndef _DRV_MAILBOX_PORT_VXWORKS_H_
#define _DRV_MAILBOX_PORT_VXWORKS_H_


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include <stdio.h>
#include "bsp_om.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*��ʵ��ַת���ӿڶ���*/
/*CCPUʵ��ַ�������ַӳ���ת���ӿ�*/
#define MEM_CORE_SHARE_PHY2VIRT(phy)                (phy)

#define MEM_CORE_SHARE_VIRT2PHY(virt)               (virt)

/*����ͨ�������ܣ��˵�������ýӿڶ���*/
/*������CPU��ID*/
#define MAILBOX_LOCAL_CPUID                         MAILBOX_CPUID_CCPU
 
/*����C��ƽ̨��ص� ����ͨ�� �����������շ�ͨ�� */
#define MAILBOX_CHANNEL_NUM \
    ( MAILBOX_CHANNEL_BUTT(CCPU, HIFI)   \
    + MAILBOX_CHANNEL_BUTT(HIFI, CCPU))

/*����C��ƽ̨��ص� �ʼ� ���� , ֻ���Ľ���ͨ��*/
#define MAILBOX_USER_NUM    \
    ( MAILBOX_USER_BUTT(HIFI, CCPU, MSG)) 

/*��ӡ���������ö���*/

/*����̨��ӡ����ӿ�*/
#ifdef _DRV_LLT_
#define mailbox_out(p)                             (printf p)
#else
#define mailbox_out(p)                             (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX, (void*)p))
#endif
/*���������Ƿ��ӡ����*/
#define _MAILBOX_LINE_                              __LINE__

/*���������Ƿ��ӡ�ļ���,(����ӡ�ļ����ɽ�ʡ����ռ�)*/
#define _MAILBOX_FILE_                              (void*)(0) /*__FILE__*/   

#define MAILBOX_LOG_LEVEL                           MAILBOX_LOG_INFO                     

/*������Թ���������ö���*/
/*�����ڴ�CPU�ϴ򿪿�ά�ɲ⹦��*/
#ifndef MAILBOX_OPEN_MNTN
#define MAILBOX_OPEN_MNTN
#endif

/*��ά�ɲ��¼�������ID��*/
#define MAILBOX_RECORD_USEID_NUM                    (64)

#define RT  "\n"   /*��ӡ�س�����*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /*_DRV_MAILBOX_VXWORKS_H_*/

