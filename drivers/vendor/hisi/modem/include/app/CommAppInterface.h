/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CommAppInterface.h
  �� �� ��   : ����
  ��    ��   :     
  ��������   : 2010��9��9��
  ����޸�   :
  ��������   : E5 �������õ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��9��9��
    ��    ��   : 
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __COMM_INTERFACE_H__
#define __COMM_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����                            
*****************************************************************************/



#pragma pack(4)

/*****************************************************************************
  2 �궨�� 
*****************************************************************************/

/*****************************************************************************
  3 STRUCT����
*****************************************************************************/


/**********************************************************************
*
*device event indication
*
*********************************************************************/
#if 0
typedef enum 
{
    DEVICE_ID_NULL_ID =0, /*��id�����ڳ�ʼ��id*/ 
    DEVICE_ID_USB = 1,     /*USB�豸id*/
    DEVICE_ID_KEY = 2,     /*KEY�����豸id*/
    DEVICE_ID_BATTERY = 3,/*����¼��ϱ�ʹ�ô�ID*/
    DEVICE_ID_CHARGER = 4, /*������¼��ϱ�ʹ�ô�ID*/
    DEVICE_ID_SD_CARD = 5,
    DEVICE_ID_GPIO_INTER=6, /*�ǰ�����gpio�ж��ϱ���ʹ�ô�ID*/
    DEVICE_ID_SCREEN=7,
    DEVICE_ID_WLAN=8,
    DEVICE_ID_OM = 9, /* OM�ϱ���Ϣ */
    DEVICE_ID_TEMP=10,/*�¶ȱ���ID*/
    DEVICE_ID_MAX_ID   /*�����߽籣��*/
}DEVICE_ID;
#endif
typedef struct device_event_st
{
    int device_id;   /*�豸ID*/
    int value;         /*��Ϣvalue*/ 
    char * desc;     /*����*/
}device_event_t;

/*****************************************************************************
  4 ��������
*****************************************************************************/
extern unsigned long OM_Printf(char * pcformat, ... );
extern unsigned long OM_PrintfWithModule(unsigned long ulModuleId,
                                   unsigned long ulLevel, char * pcformat, ... );
extern unsigned long OM_PrintfSetModuleIdLev(unsigned long ulModuleId, unsigned long ulLev);
#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __COMM_INTERFACE_H__.h */
