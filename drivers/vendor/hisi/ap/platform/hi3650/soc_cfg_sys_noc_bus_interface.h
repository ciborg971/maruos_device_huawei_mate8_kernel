/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_cfg_sys_noc_bus_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:18:56
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_CFG_SYS_NOC_BUS.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_CFG_SYS_NOC_BUS_INTERFACE_H__
#define __SOC_CFG_SYS_NOC_BUS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/9) MODEMBUS
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_ADDR(base) ((base) + (0x000C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* �Ĵ���˵����MODEMBUS Err probe��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* �Ĵ���˵����MODEMBUS Err probeʹ��
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* �Ĵ���˵����Error log��Чָʾ�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_ADDR(base) ((base) + (0x1C10))

/* �Ĵ���˵����Error log0
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* �Ĵ���˵����Error log1
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* �Ĵ���˵����Error log3
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* �Ĵ���˵����Error log5
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* �Ĵ���˵����Error log7
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))

/* �Ĵ���˵����MODEM TransactionStatFilter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x8000))

/* �Ĵ���˵��������汾
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x8004))

/* �Ĵ���˵����MODEM Transaction Probe��Filter����ģʽ���üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_ADDR(base) ((base) + (0x8008))

/* �Ĵ���˵������ַ���˻���ַ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x800C))

/* �Ĵ���˵������ַ���˴���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x8014))

/* �Ĵ���˵����MODEM��Transaction Probe��Opcode��������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_ADDR(base) ((base) + (0x8020))

/* �Ĵ���˵����MODEM��Transaction Probe��User��������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_ADDR(base) ((base) + (0x8024))

/* �Ĵ���˵����MODEM��Transaction Probe��User��������Mask
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_ADDR(base) ((base) + (0x8028))

/* �Ĵ���˵����MODEM��Transaction Probe�İ�ȫ��������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x802C))

/* �Ĵ���˵����MODEM��Transaction Probe�İ�ȫ��������Mask
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x8030))

/* �Ĵ���˵����MODEM TransactionStatProfilter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x8080))

/* �Ĵ���˵��������汾
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x8084))

/* �Ĵ���˵����transaction Probe��counterʹ������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_ADDR(base) ((base) + (0x8088))

/* �Ĵ���˵����MODEM Transaction Probe�Ĺ���ģʽ����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_ADDR(base) ((base) + (0x808C))

/* �Ĵ���˵����MODEM Transaction Probe��bin_0����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_ADDR(base) ((base) + (0x80AC))

/* �Ĵ���˵����MODEM Transaction Probe��bin_0����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_ADDR(base) ((base) + (0x80B0))

/* �Ĵ���˵����ͳ�Ƽ��������״̬
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x80EC))

/* �Ĵ���˵����ͳ�Ƽ��������״̬����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x80F0))

/* �Ĵ���˵����outstandingͳ�Ƽ�������ģʽ����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x80F4))

/* �Ĵ���˵����latencyͳ��ϵ������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x80F8))

/* �Ĵ���˵����MODEM Transaction probe��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x8400))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x8404))

/* �Ĵ���˵����Transaction Probeȫ�ֿ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x8408))

/* �Ĵ���˵����Packet Probeʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x840C))

/* �Ĵ���˵����ͳ���������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x8424))

/* �Ĵ���˵�����ֶ�����ͳ�Ƽ�ʱ��ʼʹ��
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_ADDR(base) ((base) + (0x8428))

/* �Ĵ���˵����ͳ�Ƽ�����С�澯��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x842C))

/* �Ĵ���˵����ͳ�Ƽ��������澯��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x8430))

/* �Ĵ���˵�����澯״̬�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x8434))

/* �Ĵ���˵�����澯״̬����Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x8438))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x8538))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x853C))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x8540))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x854C))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x8550))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x8554))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x8560))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x8564))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x8568))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x8574))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x8578))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x857C))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x8588))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x858C))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x8590))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x859C))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x85A0))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x85A4))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x85B0))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x85B4))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x85B8))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x85C4))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x85C8))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x85CC))



/****************************************************************************
                     (2/9) ASPBUS
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_ADDR(base)   ((base) + (0x000C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0010))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_ADDR(base) ((base) + (0x0014))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* �Ĵ���˵����ASP TransactionStatFilter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x8000))

/* �Ĵ���˵��������汾
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x8004))

/* �Ĵ���˵����ASP Transaction Probe��Filter����ģʽ���üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_ADDR(base) ((base) + (0x8008))

/* �Ĵ���˵������ַ���˻���ַ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x800C))

/* �Ĵ���˵������ַ���˴���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x8014))

/* �Ĵ���˵����ASP��Transaction Probe��Opcode��������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_ADDR(base) ((base) + (0x8020))

/* �Ĵ���˵����ASP��Transaction Probe��User��������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_ADDR(base) ((base) + (0x8024))

/* �Ĵ���˵����ASP��Transaction Probe��User��������Mask
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_ADDR(base) ((base) + (0x8028))

/* �Ĵ���˵����ASP��Transaction Probe�İ�ȫ��������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x802C))

/* �Ĵ���˵����ASP��Transaction Probe�İ�ȫ��������Mask
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x8030))

/* �Ĵ���˵����ASP TransactionStatProfilter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x8080))

/* �Ĵ���˵��������汾
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x8084))

/* �Ĵ���˵����transaction Probe��counterʹ������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_ADDR(base) ((base) + (0x8088))

/* �Ĵ���˵����ASP Transaction Probe�Ĺ���ģʽ����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_ADDR(base) ((base) + (0x808C))

/* �Ĵ���˵����ASP Transaction Probe��bin_0����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_ADDR(base) ((base) + (0x80AC))

/* �Ĵ���˵����ASP Transaction Probe��bin_1����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_ADDR(base) ((base) + (0x80B0))

/* �Ĵ���˵����ASP Transaction Probe��bin_1����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_ADDR(base) ((base) + (0x80B4))

/* �Ĵ���˵����ASP Transaction Probe��bin_1����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_ADDR(base) ((base) + (0x80B8))

/* �Ĵ���˵����ͳ�Ƽ��������״̬
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x80EC))

/* �Ĵ���˵����ͳ�Ƽ��������״̬����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x80F0))

/* �Ĵ���˵����outstandingͳ�Ƽ�������ģʽ����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x80F4))

/* �Ĵ���˵����latencyͳ��ϵ������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x80F8))

/* �Ĵ���˵����ASP Transaction probe��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x8400))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x8404))

/* �Ĵ���˵����Transaction Probeȫ�ֿ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x8408))

/* �Ĵ���˵����Packet Probeʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x840C))

/* �Ĵ���˵����ͳ���������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x8424))

/* �Ĵ���˵�����ֶ�����ͳ�Ƽ�ʱ��ʼʹ��
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_ADDR(base) ((base) + (0x8428))

/* �Ĵ���˵����ͳ�Ƽ�����С�澯��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x842C))

/* �Ĵ���˵����ͳ�Ƽ��������澯��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x8430))

/* �Ĵ���˵�����澯״̬�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x8434))

/* �Ĵ���˵�����澯״̬����Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x8438))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x8538))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x853C))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x8540))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x854C))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x8550))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x8554))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x8560))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x8564))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x8568))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x8574))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x8578))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x857C))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x8588))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x858C))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x8590))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x859C))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x85A0))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x85A4))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x85B0))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x85B4))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x85B8))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x85C4))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x85C8))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x85CC))



/****************************************************************************
                     (3/9) SYSBUS
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_ADDR(base) ((base) + (0x000C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* �Ĵ���˵����adapter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))

/* �Ĵ���˵����Rate Adapter���üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_ADDR(base) ((base) + (0x1008))

/* �Ĵ���˵����Rate Adapter bypass�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))

/* �Ĵ���˵����adapter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1080))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1084))

/* �Ĵ���˵����Rate Adapter���üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_ADDR(base) ((base) + (0x1088))

/* �Ĵ���˵����Rate Adapter bypass�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_ADDR(base) ((base) + (0x108C))

/* �Ĵ���˵����adapter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1100))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1104))

/* �Ĵ���˵����Rate Adapter���üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_ADDR(base) ((base) + (0x1108))

/* �Ĵ���˵����Rate Adapter bypass�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_ADDR(base) ((base) + (0x110C))

/* �Ĵ���˵����adapter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1180))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1184))

/* �Ĵ���˵����Rate Adapter���üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_ADDR(base) ((base) + (0x1188))

/* �Ĵ���˵����Rate Adapter bypass�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_ADDR(base) ((base) + (0x118C))

/* �Ĵ���˵����adapter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1200))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1204))

/* �Ĵ���˵����Rate Adapter���üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_ADDR(base) ((base) + (0x1208))

/* �Ĵ���˵����Rate Adapter bypass�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_ADDR(base) ((base) + (0x120C))

/* �Ĵ���˵����adapter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1280))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1284))

/* �Ĵ���˵����Rate Adapter���üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_ADDR(base) ((base) + (0x1288))

/* �Ĵ���˵����Rate Adapter bypass�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_ADDR(base) ((base) + (0x128C))

/* �Ĵ���˵����adapter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1300))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1304))

/* �Ĵ���˵����Rate Adapter���üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_ADDR(base) ((base) + (0x1308))

/* �Ĵ���˵����Rate Adapter bypass�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_ADDR(base) ((base) + (0x130C))

/* �Ĵ���˵����SYSBUS Err probe��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* �Ĵ���˵����SYSBUS Err probeʹ��
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* �Ĵ���˵����Error log��Чָʾ�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_ADDR(base)  ((base) + (0x1C0C))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_ADDR(base)  ((base) + (0x1C10))

/* �Ĵ���˵����Error log0
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* �Ĵ���˵����Error log1
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* �Ĵ���˵����Error log3
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* �Ĵ���˵����Error log5
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* �Ĵ���˵����Error log7
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))

/* �Ĵ���˵����SYSBUS_DDRC Packet probe��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_ADDR(base) ((base) + (0x2000))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_ADDR(base) ((base) + (0x2004))

/* �Ĵ���˵����Packet Probeȫ�ֿ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_ADDR(base) ((base) + (0x2008))

/* �Ĵ���˵����Packet Probeʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_ADDR(base) ((base) + (0x200C))

/* �Ĵ���˵���������������ұ�
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_ADDR(base) ((base) + (0x2014))

/* �Ĵ���˵����ͳ���������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_ADDR(base) ((base) + (0x2024))

/* �Ĵ���˵�����ֶ�����ͳ�Ƽ�ʱ��ʼʹ��
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_ADDR(base) ((base) + (0x2028))

/* �Ĵ���˵����ͳ�Ƽ�����С�澯��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_ADDR(base) ((base) + (0x202C))

/* �Ĵ���˵����ͳ�Ƽ��������澯��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_ADDR(base) ((base) + (0x2030))

/* �Ĵ���˵�����澯״̬�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_ADDR(base) ((base) + (0x2034))

/* �Ĵ���˵�����澯״̬����Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_ADDR(base) ((base) + (0x2038))

/* �Ĵ���˵����F0��RouteId������������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_ADDR(base) ((base) + (0x2044))

/* �Ĵ���˵����F0��RouteId��������Mask����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_ADDR(base) ((base) + (0x2048))

/* �Ĵ���˵����F0�ĵ�ַ������������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_ADDR(base) ((base) + (0x204C))

/* �Ĵ���˵����F0�ĵ�ַ���˵�Mask��ַ��С����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_ADDR(base) ((base) + (0x2054))

/* �Ĵ���˵����F0�İ�ȫ������������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_ADDR(base) ((base) + (0x2058))

/* �Ĵ���˵����F0�İ�ȫ����������Mask
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_ADDR(base) ((base) + (0x205C))

/* �Ĵ���˵����F0��Opcode������������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_ADDR(base) ((base) + (0x2060))

/* �Ĵ���˵����F0��packet״̬��������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_ADDR(base) ((base) + (0x2064))

/* �Ĵ���˵����F0�İ�����������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_ADDR(base) ((base) + (0x2068))

/* �Ĵ���˵����F0��urgency��������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_ADDR(base) ((base) + (0x206C))

/* �Ĵ���˵����F0��User��������
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_ADDR(base) ((base) + (0x2070))

/* �Ĵ���˵����F0��User��������Mask
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_ADDR(base) ((base) + (0x2074))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_ADDR(base) ((base) + (0x2138))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x213C))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_ADDR(base) ((base) + (0x2140))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_ADDR(base) ((base) + (0x214C))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x2150))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_ADDR(base) ((base) + (0x2154))



/****************************************************************************
                     (4/9) CFGBUS
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_ADDR(base) ((base) + (0x000C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_ADDR(base) ((base) + (0x0088))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_ADDR(base) ((base) + (0x008C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_ADDR(base) ((base) + (0x0100))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_ADDR(base) ((base) + (0x0108))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_ADDR(base) ((base) + (0x010C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))

/* �Ĵ���˵����CFG_BUS Err probe��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* �Ĵ���˵����CFG_BUS Err probeʹ��
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* �Ĵ���˵����Error log��Чָʾ�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_ADDR(base)  ((base) + (0x1C0C))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_ADDR(base)  ((base) + (0x1C10))

/* �Ĵ���˵����Error log0
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* �Ĵ���˵����Error log1
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* �Ĵ���˵����Error log3
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* �Ĵ���˵����Error log5
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* �Ĵ���˵����Error log7
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))



/****************************************************************************
                     (5/9) DMABUS
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_ADDR(base)  ((base) + (0x000C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* �Ĵ���˵����adapter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))

/* �Ĵ���˵����Rate Adapter���üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_ADDR(base) ((base) + (0x1008))

/* �Ĵ���˵����Rate Adapter bypass�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))

/* �Ĵ���˵����DMABUS Err probe��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* �Ĵ���˵����DMABUS Err probeʹ��
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* �Ĵ���˵����Error log��Чָʾ�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_ADDR(base)  ((base) + (0x1C0C))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_ADDR(base)  ((base) + (0x1C10))

/* �Ĵ���˵����Error log0
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* �Ĵ���˵����Error log1
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* �Ĵ���˵����Error log3
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* �Ĵ���˵����Error log5
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* �Ĵ���˵����Error log7
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))



/****************************************************************************
                     (6/9) DBGBUS
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_ADDR(base)  ((base) + (0x000C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0010))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_ADDR(base) ((base) + (0x0014))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_ADDR(base) ((base) + (0x0088))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_ADDR(base) ((base) + (0x008C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_ADDR(base) ((base) + (0x0100))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_ADDR(base) ((base) + (0x0108))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_ADDR(base) ((base) + (0x010C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_ADDR(base) ((base) + (0x0180))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0184))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_ADDR(base) ((base) + (0x0188))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_ADDR(base)  ((base) + (0x018C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0198))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_ADDR(base) ((base) + (0x0200))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0204))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_ADDR(base) ((base) + (0x0208))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_ADDR(base) ((base) + (0x020C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0218))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_ADDR(base) ((base) + (0x0280))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0284))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_ADDR(base) ((base) + (0x0288))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_ADDR(base) ((base) + (0x028C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0298))

/* �Ĵ���˵����adapter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))

/* �Ĵ���˵����Rate Adapter���üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_ADDR(base) ((base) + (0x1008))

/* �Ĵ���˵����Rate Adapter bypass�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))

/* �Ĵ���˵����DBGBUS Err probe��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* �Ĵ���˵����DBGBUS Err probeʹ��
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* �Ĵ���˵����Error log��Чָʾ�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_ADDR(base)  ((base) + (0x1C0C))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_ADDR(base)  ((base) + (0x1C10))

/* �Ĵ���˵����Error log0
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* �Ĵ���˵����Error log1
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* �Ĵ���˵����Error log3
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* �Ĵ���˵����Error log5
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* �Ĵ���˵����Error log7
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))



/****************************************************************************
                     (7/9) MMC1BUS
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_ADDR(base) ((base) + (0x0088))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_ADDR(base) ((base) + (0x008C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))

/* �Ĵ���˵����MMC1BUS Err probe��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* �Ĵ���˵����MMC1BUS Err probeʹ��
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* �Ĵ���˵����Error log��Чָʾ�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_ADDR(base) ((base) + (0x1C10))

/* �Ĵ���˵����Error log0
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* �Ĵ���˵����Error log1
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* �Ĵ���˵����Error log3
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* �Ĵ���˵����Error log5
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* �Ĵ���˵����Error log7
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))



/****************************************************************************
                     (8/9) MMC0BUS 
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_ADDR(base) ((base) + (0x000C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_ADDR(base) ((base) + (0x0088))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_ADDR(base) ((base) + (0x008C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_ADDR(base) ((base) + (0x0100))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_ADDR(base) ((base) + (0x0108))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_ADDR(base) ((base) + (0x010C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))

/* �Ĵ���˵����adapter��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))

/* �Ĵ���˵����Rate Adapter���üĴ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_ADDR(base) ((base) + (0x1008))

/* �Ĵ���˵����Rate Adapter bypass�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))

/* �Ĵ���˵����MMC0BUS Err probe��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* �Ĵ���˵����MMC0BUS Err probeʹ��
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* �Ĵ���˵����Error log��Чָʾ�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_ADDR(base) ((base) + (0x1C10))

/* �Ĵ���˵����Error log0
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* �Ĵ���˵����Error log1
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* �Ĵ���˵����Error log3
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* �Ĵ���˵����Error log5
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* �Ĵ���˵����Error log7
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))



/****************************************************************************
                     (9/9) IVP32BUS
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_ADDR(base) ((base) + (0x000C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* �Ĵ���˵����IVP32 Err probe��ID
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* �Ĵ���˵����IVP32 Err probeʹ��
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_ADDR(base)  ((base) + (0x1C08))

/* �Ĵ���˵����Error log��Чָʾ�Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_ADDR(base)   ((base) + (0x1C0C))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_ADDR(base)   ((base) + (0x1C10))

/* �Ĵ���˵����Error log0
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_ADDR(base)  ((base) + (0x1C14))

/* �Ĵ���˵����Error log1
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_ADDR(base)  ((base) + (0x1C18))

/* �Ĵ���˵����Error log3
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_ADDR(base)  ((base) + (0x1C20))

/* �Ĵ���˵����Error log5
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_ADDR(base)  ((base) + (0x1C28))

/* �Ĵ���˵����Error log7
   λ����UNION�ṹ:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_ADDR(base)  ((base) + (0x1C30))





/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  6 STRUCT����
*****************************************************************************/



/*****************************************************************************
  7 UNION����
*****************************************************************************/

/****************************************************************************
                     (1/9) MODEMBUS
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_UNION
 �ṹ˵��  : MODEM_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x1B101004�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : MODEM_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_UNION
 �ṹ˵��  : MODEM_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_UNION
 �ṹ˵��  : MODEM_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_UNION
 �ṹ˵��  : MODEM_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_UNION
 �ṹ˵��  : MODEMBUS_ERR_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1C00����ֵ:0x08DA560D�����:32
 �Ĵ���˵��: MODEMBUS Err probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: error probe����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_UNION
 �ṹ˵��  : MODEMBUS_ERR_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1C04����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_UNION
 �ṹ˵��  : MODEMBUS_FAULTEN �Ĵ����ṹ���塣��ַƫ����:0x1C08����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEMBUS Err probeʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  faulten  : 1;  /* bit[0]   : ʹ������жϣ�����Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_UNION
 �ṹ˵��  : MODEMBUS_ERRVLD �Ĵ����ṹ���塣��ַƫ����:0x1C0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log��Чָʾ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errvld   : 1;  /* bit[0]   : Error log��Чָʾ״̬�Ĵ���������Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_UNION
 �ṹ˵��  : MODEMBUS_ERRCLR �Ĵ����ṹ���塣��ַƫ����:0x1C10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errclr   : 1;  /* bit[0-0] : 1.д1'b1����ErrVld�Ĵ���������ж�ʹ�ܣ�ͬʱҲ����жϣ���
                                                   2.д1'b1�����ܴ洢��ErrClr�Ĵ����У����üĴ�������������1'b0�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_UNION
 �ṹ˵��  : MODEMBUS_ERRLOG0 �Ĵ����ṹ���塣��ַƫ����:0x1C14����ֵ:0x80000000�����:32
 �Ĵ���˵��: Error log0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lock     : 1;  /* bit[0]    : ֻ��Transaction�Ƿ�ΪLock����������Ч�� */
        unsigned int  opc      : 4;  /* bit[1-4]  : Transaction�������ͣ�
                                                    0-->RD��INCR�Ķ�������
                                                    1-->RDW��WRAP�Ķ�������
                                                    2-->RDL��Exclusive ��������
                                                    3-->RDX��Lock read��
                                                    4-->WR��INCRд������
                                                    5-->WRW��WRAPд������
                                                    6-->WRC��Exclusiveд������
                                                    8-->PRE��FIXED BURST��
                                                    9-->URG��urgency packet��Error Probe�����⵽����packet��
                                                    ����-->Reserveed���Ƿ������� */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : ���� */
        unsigned int  errcode  : 3;  /* bit[8-10] : �������ͣ�
                                                    0-->������slave����Error Response��
                                                    1-->master���������ߵ�Reserve��ַ�ռ䣻
                                                    2-->master������slave��֧�ֵ�Burst���ͣ���ǰ���߲���������ֳ�������
                                                    3-->master�����˵�������
                                                    4-->����Ȩ�ޱ���
                                                    5-->master����ʱ���յ�Firewall��Hide Error Response��
                                                    6-->������slave TimeOut��������Error Response��
                                                    7-->none�� */
        unsigned int  reserved_1: 5;  /* bit[11-15]: ���� */
        unsigned int  len1     : 8;  /* bit[16-23]: ��ʾ����Transaction�İ�������λΪByte */
        unsigned int  reserved_2: 7;  /* bit[24-30]: ���� */
        unsigned int  format   : 1;  /* bit[31]   : ���ڱ�ʾError log0�ĸ�ʽ��FlexNoC2.7�Ժ�汾�̶�Ϊ1'b1�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_UNION
 �ṹ˵��  : MODEMBUS_ERRLOG1 �Ĵ����ṹ���塣��ַƫ����:0x1C18����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog1  : 14; /* bit[0-13] : RouteId��·����Ϣ����bit��������
                                                    [13:10]-->Initiator Flow ID�����ڱ�ʾ������ʵ�master��
                                                    [9:7]-->target Flow ID�����ڱ�ʾ�����ʵ�slave��
                                                    [6:0]-->Seq ID��Transaction��ǣ� */
        unsigned int  reserved : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_UNION
 �ṹ˵��  : MODEMBUS_ERRLOG3 �Ĵ����ṹ���塣��ַƫ����:0x1C20����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog3 : 32; /* bit[0-31]: ���ʵ�ֵַ */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_errlog3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_UNION
 �ṹ˵��  : MODEMBUS_ERRLOG5 �Ĵ����ṹ���塣��ַƫ����:0x1C28����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog5  : 5;  /* bit[0-4] : User�ź�ֵ */
        unsigned int  reserved : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_UNION
 �ṹ˵��  : MODEMBUS_ERRLOG7 �Ĵ����ṹ���塣��ַƫ����:0x1C30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog7  : 1;  /* bit[0]   : ��ȫ�ź�ֵ */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_errlog7_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_UNION
 �ṹ˵��  : MODEM_TRANS_F_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x8000����ֵ:0x0B84FC09�����:32
 �Ĵ���˵��: MODEM TransactionStatFilter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : ����ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: ���ò�����У��� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_UNION
 �ṹ˵��  : MODEM_TRANS_F_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x8004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ����汾
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : �û��Զ���ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC���ɴ��������汾 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_UNION
 �ṹ˵��  : MODEM_TRANS_F_MODE �Ĵ����ṹ���塣��ַƫ����:0x8008����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM Transaction Probe��Filter����ģʽ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0-0] : 0-->handshake��ģʽ��start event=begin request��end event=accept request��
                                                   1-->latencyģʽ��start event=begin request + context ID��end event=begin response + context ID�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_UNION
 �ṹ˵��  : MODEM_TRANS_F_ADDRBASE_LOW �Ĵ����ṹ���塣��ַƫ����:0x800C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ַ���˻���ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_low : 32; /* bit[0-31]: ��ַ���������Ļ���ַ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_UNION
 �ṹ˵��  : MODEM_TRANS_F_ADDRWINDOWSIZE �Ĵ����ṹ���塣��ַƫ����:0x8014����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ַ���˴���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrwindowsize : 6;  /* bit[0-5] : ��ַ���˵�Mask���ڴ�С��
                                                         ���磺��ַ���˵�Mask���ڴ�СΪ64MB��WidowSize=log2(64MB)=26����ʱ��������filter_0_windowsize=0x1A��
                                                         Address Mask=~��2^max(WindowSize,packet.len)-1��=0xFC000000��packet.lenΪNOC�ڲ���ʾһ��packet����������λ����ֵΪ6~7����
                                                         ��������Ϊ��PacketAddress & AddressMask = AddressBase & AddressMask�� */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_UNION
 �ṹ˵��  : MODEM_TRANS_F_OPCODE �Ĵ����ṹ���塣��ַƫ����:0x8020����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM��Transaction Probe��Opcode��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rden     : 1;  /* bit[0-0] : ����Ϊ1ʱ������д���ݰ��� */
        unsigned int  wren     : 1;  /* bit[1-1] : ����Ϊ1ʱ�����˶����ݰ��� */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_rden_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_rden_END        (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_wren_START      (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_UNION
 �ṹ˵��  : MODEM_TRANS_F_USERBASE �Ĵ����ṹ���塣��ַƫ����:0x8024����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM��Transaction Probe��User��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 12; /* bit[0-11] : User�źŹ������� */
        unsigned int  reserved : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_userbase_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_UNION
 �ṹ˵��  : MODEM_TRANS_F_USERMASK �Ĵ����ṹ���塣��ַƫ����:0x8028����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM��Transaction Probe��User��������Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 12; /* bit[0-11] : ��UserBase����Mask��ѡ��UserBase�е����⼸bit User�ź���Ϊ����������
                                                    ����������packet.User & UserMask = UserBase & UserMask�� */
        unsigned int  reserved : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_usermask_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_UNION
 �ṹ˵��  : MODEM_TRANS_F_SECURITYBASE �Ĵ����ṹ���塣��ַƫ����:0x802C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM��Transaction Probe�İ�ȫ��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitybase : 1;  /* bit[0-0] : 0-->��ʾ��ȫ����������
                                                       1-->��ʾ�ǰ�ȫ���������� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_UNION
 �ṹ˵��  : MODEM_TRANS_F_SECURITYMASK �Ĵ����ṹ���塣��ַƫ����:0x8030����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM��Transaction Probe�İ�ȫ��������Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitymask : 1;  /* bit[0-0] : ��ȫ����������packet.Security & SecurityMask = SecurityBase & SecurityMasks��
                                                       Ҳ����˵��Filters_1_SecurityMask=1ʱ��ȫ��������Filters_1_SecurityBase��Ч�����Թ��˰�ȫ��ǰ�ȫpacket�����򣬲���������ã� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_UNION
 �ṹ˵��  : MODEM_TRANS_P_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x8080����ֵ:0xC59E110A�����:32
 �Ĵ���˵��: MODEM TransactionStatProfilter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : ����ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: ���ò�����У��� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_UNION
 �ṹ˵��  : MODEM_TRANS_P_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x8084����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ����汾
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : �û��Զ���ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC���ɴ��������汾 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_UNION
 �ṹ˵��  : MODEM_TRANS_P_EN �Ĵ����ṹ���塣��ַƫ����:0x8088����ֵ:0x00000000�����:32
 �Ĵ���˵��: transaction Probe��counterʹ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0-0] : ������Ϊ1ʱ��ʹ��Transaction Probe��ͳ�Ƽ����� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_en_START        (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_UNION
 �ṹ˵��  : MODEM_TRANS_P_MODE �Ĵ����ṹ���塣��ַƫ����:0x808C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM Transaction Probe�Ĺ���ģʽ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0]   : 0-->ͳ��latency��
                                                   1-->ͳ��outstanding�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_UNION
 �ṹ˵��  : MODEM_TRANS_P_THRESHOLDS_0_0 �Ĵ����ṹ���塣��ַƫ����:0x80AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM Transaction Probe��bin_0����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_0 : 2;  /* bit[0-1] : 0x0-->ѡ��threshold_0��delay��40��outstanding��2����
                                                         0x1-->ѡ��threshold_1��delay��96��outstanding��5����
                                                         0x2-->ѡ��threshold_2��delay��128��-----------------����
                                                         0x3-->ѡ��threshold_3��delay��256��-----------------���� */
        unsigned int  reserved       : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_UNION
 �ṹ˵��  : MODEM_TRANS_P_THRESHOLDS_0_1 �Ĵ����ṹ���塣��ַƫ����:0x80B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM Transaction Probe��bin_0����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_1 : 2;  /* bit[0-1] : 0x0-->ѡ��threshold_0��delay��1~40��outstanding��1~2����
                                                         0x1-->ѡ��threshold_1��delay��41~96��outstanding��3~5����
                                                         0x2-->ѡ��threshold_2��delay��97~128��-----------------����
                                                         0x3-->ѡ��threshold_3��delay��129~256��-----------------���� */
        unsigned int  reserved       : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_UNION
 �ṹ˵��  : MODEM_TRANS_P_OVERFLOWSTATUS �Ĵ����ṹ���塣��ַƫ����:0x80EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ��������״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowstatus : 1;  /* bit[0-0] : 1��ʾͳ�Ƽ�������� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_UNION
 �ṹ˵��  : MODEM_TRANS_P_OVERFLOWRESET �Ĵ����ṹ���塣��ַƫ����:0x80F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ��������״̬����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowreset : 1;  /* bit[0-0] : д1ʱ��OverflowStatus�Ĵ������㣬���üĴ���ʱ�ӷ���0 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_UNION
 �ṹ˵��  : MODEM_TRANS_P_PENDINGEVENTMODE �Ĵ����ṹ���塣��ַƫ����:0x80F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: outstandingͳ�Ƽ�������ģʽ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pendingeventmode : 1;  /* bit[0-0] : 0x0-->��outstanding���� > 0ʱ��ÿ��cycle��ȥ�����������ռ�outstanding������
                                                           0x1-->������1��responseʱ���ʹ����������ռ�outstanding������ */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_UNION
 �ṹ˵��  : MODEM_TRANS_P_PRESCALER �Ĵ����ṹ���塣��ַƫ����:0x80F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: latencyͳ��ϵ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prescaler : 8;  /* bit[0-7] : 0-->handshake��ģʽ��start event=begin request��end event=accept request��
                                                    1-->latencyģʽ��start event=begin request + context ID��end event=begin response + context ID�� */
        unsigned int  reserved  : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_UNION
 �ṹ˵��  : MODEM_TRANS_M_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x8400����ֵ:0xCA501B06�����:32
 �Ĵ���˵��: MODEM Transaction probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus��Packet Probe����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_UNION
 �ṹ˵��  : MODEM_TRANS_M_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x8404����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_UNION
 �ṹ˵��  : MODEM_TRANS_M_MAINCTL �Ĵ����ṹ���塣��ַƫ����:0x8408����ֵ:0x00000000�����:32
 �Ĵ���˵��: Transaction Probeȫ�ֿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  erren                     : 1;  /* bit[0]   : ErrEn��ʹ��Packet Probe����⵽���κδ���״̬��Packet�ϱ���Observer�����ڱ����ߵ�Packet Probe��֧��trace���ܣ��ʴ�λ�����塣 */
        unsigned int  traceen                   : 1;  /* bit[1]   : TraceEn�������߲�֧��Trace���ܣ��ʴ�λ�����塣 */
        unsigned int  payloaden                 : 1;  /* bit[2]   : PayloadEn�������߲�֧��Trace���ܣ��ʴ�λ�����塣 */
        unsigned int  staten                    : 1;  /* bit[3]   : StatEn��ͳ��ģ��ʹ�ܼĴ�������StatEn��0����Ϊ1ʱ��ͳ�Ƽ����������㣻��StatEn����Ϊ0ʱ��ͳ�Ƽ�������disabled�� */
        unsigned int  alarmen                   : 1;  /* bit[4]   : AlarmEn���ж�ʹ�����á�
                                                                    0-->�����жϣ�
                                                                    1-->ʹ���ж������ */
        unsigned int  statconddump              : 1;  /* bit[5]   : 0-->��ʾ������dumpͳ�����ݣ��Ĵ���counters_m_val��ֵ��ʵʱ��ӳͳ�Ƽ�������ֵ��
                                                                    1-->��ʾ������dump���ݣ��ڸ�����ͳ�������ڷ���out of bounds �¼����ŻὫͳ�Ƽ�������ֵdump���Ĵ���counters_m_val�С� */
        unsigned int  intrusivemode             : 1;  /* bit[6]   : IntrusiveMode�� �����߲�֧��Trace���ܣ��ʴ�λ�����塣 */
        unsigned int  filtbytealwayschainableen : 1;  /* bit[7]   : FiltByteAlwaysChainableEn��������ż������������ʹ�ܵ�ȫ�����ã�
                                                                    0-->��ʹ�ܣ���ʱ�����в�statistic counters�����Ա�Map��
                                                                    1-->ʹ�ܣ�ֻ��ż��statistic counters�ſ��Ա�Map�� */
        unsigned int  reserved                  : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_UNION
 �ṹ˵��  : MODEM_TRANS_M_CFGCTL �Ĵ����ṹ���塣��ַƫ����:0x840C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Packet Probeʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  globalen : 1;  /* bit[0]   : GlobalEn��Packet Probeʹ���źţ�����Ч�� */
        unsigned int  active   : 1;  /* bit[1]   : Active��Packet Probe�Ĺ���״ָ̬ʾ�źš�
                                                   0-->��GlobalEn����Ϊ0�ļ���cycle��Active�����ͣ�
                                                   1-->��GlobalEn����Ϊ1ʱ��Active�����ߣ���ʱ�������Packet Probe�������á� */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_active_START    (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_UNION
 �ṹ˵��  : MODEM_TRANS_M_STATPERIOD �Ĵ����ṹ���塣��ַƫ����:0x8424����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ���������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statperiod : 5;  /* bit[0-4] : �Զ�ͳ��ģʽ�µ�ͳ�����ڣ�ͳ������= N_Cycle = 2^min(23,StatPeriod)�����Ϊ8 mega cycles����СΪ2 cycles��������Ϊ0ʱ���Զ�ͳ��ģʽ���رգ���Ҫ�����ֶ�ģʽ��Ҳ��������StatGo�Ĵ�����ʵ�ִ���ͳ�ơ� */
        unsigned int  reserved   : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_UNION
 �ṹ˵��  : MODEM_TRANS_M_STATGO �Ĵ����ṹ���塣��ַƫ����:0x8428����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ֶ�����ͳ�Ƽ�ʱ��ʼʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statgo   : 1;  /* bit[0]   : ��StatPeriod=0ʱ����globalenΪ1����Ĵ���StatGoд1����Ὣcounter_m_val��ֵ��statalarmmax��statalarmmin��ֵ���бȽϣ����üĴ���ʼ�շ���0�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_statgo_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_UNION
 �ṹ˵��  : MODEM_TRANS_M_STATALARMMIN �Ĵ����ṹ���塣��ַƫ����:0x842C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�����С�澯��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmin : 32; /* bit[0-31]: ������һ��ͳ�Ƽ�������ֵС��StatAlarmMin��ֵ���ʹ����澯�Ĵ����� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_UNION
 �ṹ˵��  : MODEM_TRANS_M_STATALARMMAX �Ĵ����ṹ���塣��ַƫ����:0x8430����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ��������澯��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmax : 32; /* bit[0-31]: ������һ��ͳ�Ƽ�������ֵ����StatAlarmMax��ֵ���ʹ����澯�Ĵ����� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_UNION
 �ṹ˵��  : MODEM_TRANS_M_STATALARMSTATUS �Ĵ����ṹ���塣��ַƫ����:0x8434����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmstatus : 1;  /* bit[0]   : ������һ��ͳ�Ƽ�������ֵ����StatAlarmMax��С��StatAlarmMin����üĴ�����λΪ1�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_UNION
 �ṹ˵��  : MODEM_TRANS_M_STATALARMCLR �Ĵ����ṹ���塣��ַƫ����:0x8438����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯״̬����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmclr : 1;  /* bit[0]   : д1������StatAlarmStatus�Ĵ��������˼Ĵ�����������0�� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_0_SRC �Ĵ����ṹ���塣��ַƫ����:0x8538����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_0_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x853C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_0_VAL �Ĵ����ṹ���塣��ַƫ����:0x8540����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 12; /* bit[0-11] : ��Counters_0_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_1_SRC �Ĵ����ṹ���塣��ַƫ����:0x854C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_1_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x8550����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_1_VAL �Ĵ����ṹ���塣��ַƫ����:0x8554����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 12; /* bit[0-11] : ��Counters_1_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_2_SRC �Ĵ����ṹ���塣��ַƫ����:0x8560����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_2_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x8564����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_2_VAL �Ĵ����ṹ���塣��ַƫ����:0x8568����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_val : 12; /* bit[0-11] : ��Counters_2_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_3_SRC �Ĵ����ṹ���塣��ַƫ����:0x8574����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_3_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x8578����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_3_VAL �Ĵ����ṹ���塣��ַƫ����:0x857C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_val : 12; /* bit[0-11] : ��Counters_3_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_4_SRC �Ĵ����ṹ���塣��ַƫ����:0x8588����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_4_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x858C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_4_VAL �Ĵ����ṹ���塣��ַƫ����:0x8590����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_val : 12; /* bit[0-11] : ��Counters_4_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_5_SRC �Ĵ����ṹ���塣��ַƫ����:0x859C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_5_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x85A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_5_VAL �Ĵ����ṹ���塣��ַƫ����:0x85A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_val : 12; /* bit[0-11] : ��Counters_5_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_6_SRC �Ĵ����ṹ���塣��ַƫ����:0x85B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_6_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x85B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_6_VAL �Ĵ����ṹ���塣��ַƫ����:0x85B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_val : 12; /* bit[0-11] : ��Counters_6_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_7_SRC �Ĵ����ṹ���塣��ַƫ����:0x85C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_7_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x85C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_UNION
 �ṹ˵��  : MODEM_TRANS_M_COUNTERS_7_VAL �Ĵ����ṹ���塣��ַƫ����:0x85CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_val : 12; /* bit[0-11] : ��Counters_7_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (11)




/****************************************************************************
                     (2/9) ASPBUS
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_UNION
 �ṹ˵��  : ASP_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0xC364FF04�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : ASP_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_UNION
 �ṹ˵��  : ASP_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_UNION
 �ṹ˵��  : ASP_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_UNION
 �ṹ˵��  : ASP_QOS_BANDWIDTH �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000800�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 12; /* bit[0-11] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_bandwidth_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_UNION
 �ṹ˵��  : ASP_QOS_SATURATION �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x000003E8�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  saturation : 10; /* bit[0-9]  : Defines the size of the bandwidth counter, that is, the measurement window, in 16-byte units. In other words, the desired number of bytes divided by 16. */
        unsigned int  reserved   : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_saturation_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_UNION
 �ṹ˵��  : ASP_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_UNION
 �ṹ˵��  : ASP_TRANS_F_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x8000����ֵ:0x4104DC09�����:32
 �Ĵ���˵��: ASP TransactionStatFilter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : ����ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: ���ò�����У��� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_UNION
 �ṹ˵��  : ASP_TRANS_F_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x8004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ����汾
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : �û��Զ���ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC���ɴ��������汾 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_UNION
 �ṹ˵��  : ASP_TRANS_F_MODE �Ĵ����ṹ���塣��ַƫ����:0x8008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP Transaction Probe��Filter����ģʽ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0-0] : 0-->handshake��ģʽ��start event=begin request��end event=accept request��
                                                   1-->latencyģʽ��start event=begin request + context ID��end event=begin response + context ID�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_UNION
 �ṹ˵��  : ASP_TRANS_F_ADDRBASE_LOW �Ĵ����ṹ���塣��ַƫ����:0x800C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ַ���˻���ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_low : 32; /* bit[0-31]: ��ַ���������Ļ���ַ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_UNION
 �ṹ˵��  : ASP_TRANS_F_ADDRWINDOWSIZE �Ĵ����ṹ���塣��ַƫ����:0x8014����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ַ���˴���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrwindowsize : 6;  /* bit[0-5] : ��ַ���˵�Mask���ڴ�С��
                                                         ���磺��ַ���˵�Mask���ڴ�СΪ64MB��WidowSize=log2(64MB)=26����ʱ��������filter_0_windowsize=0x1A��
                                                         Address Mask=~��2^max(WindowSize,packet.len)-1��=0xFC000000��packet.lenΪNOC�ڲ���ʾһ��packet����������λ����ֵΪ6~7����
                                                         ��������Ϊ��PacketAddress & AddressMask = AddressBase & AddressMask�� */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_UNION
 �ṹ˵��  : ASP_TRANS_F_OPCODE �Ĵ����ṹ���塣��ַƫ����:0x8020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP��Transaction Probe��Opcode��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rden     : 1;  /* bit[0-0] : ����Ϊ1ʱ������д���ݰ��� */
        unsigned int  wren     : 1;  /* bit[1-1] : ����Ϊ1ʱ�����˶����ݰ��� */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_rden_START      (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_rden_END        (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_wren_START      (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_UNION
 �ṹ˵��  : ASP_TRANS_F_USERBASE �Ĵ����ṹ���塣��ַƫ����:0x8024����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP��Transaction Probe��User��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 12; /* bit[0-11] : User�źŹ������� */
        unsigned int  reserved : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_userbase_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_UNION
 �ṹ˵��  : ASP_TRANS_F_USERMASK �Ĵ����ṹ���塣��ַƫ����:0x8028����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP��Transaction Probe��User��������Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 12; /* bit[0-11] : ��UserBase����Mask��ѡ��UserBase�е����⼸bit User�ź���Ϊ����������
                                                    ����������packet.User & UserMask = UserBase & UserMask�� */
        unsigned int  reserved : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_usermask_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_UNION
 �ṹ˵��  : ASP_TRANS_F_SECURITYBASE �Ĵ����ṹ���塣��ַƫ����:0x802C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP��Transaction Probe�İ�ȫ��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitybase : 1;  /* bit[0-0] : 0-->��ʾ��ȫ����������
                                                       1-->��ʾ�ǰ�ȫ���������� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_UNION
 �ṹ˵��  : ASP_TRANS_F_SECURITYMASK �Ĵ����ṹ���塣��ַƫ����:0x8030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP��Transaction Probe�İ�ȫ��������Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitymask : 1;  /* bit[0-0] : ��ȫ����������packet.Security & SecurityMask = SecurityBase & SecurityMasks��
                                                       Ҳ����˵��Filters_1_SecurityMask=1ʱ��ȫ��������Filters_1_SecurityBase��Ч�����Թ��˰�ȫ��ǰ�ȫpacket�����򣬲���������ã� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_UNION
 �ṹ˵��  : ASP_TRANS_P_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x8080����ֵ:0x230D050A�����:32
 �Ĵ���˵��: ASP TransactionStatProfilter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : ����ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: ���ò�����У��� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_UNION
 �ṹ˵��  : ASP_TRANS_P_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x8084����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ����汾
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : �û��Զ���ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC���ɴ��������汾 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_UNION
 �ṹ˵��  : ASP_TRANS_P_EN �Ĵ����ṹ���塣��ַƫ����:0x8088����ֵ:0x00000000�����:32
 �Ĵ���˵��: transaction Probe��counterʹ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0-0] : ������Ϊ1ʱ��ʹ��Transaction Probe��ͳ�Ƽ����� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_en_START        (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_UNION
 �ṹ˵��  : ASP_TRANS_P_MODE �Ĵ����ṹ���塣��ַƫ����:0x808C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP Transaction Probe�Ĺ���ģʽ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0]   : 0-->ͳ��latency��
                                                   1-->ͳ��outstanding�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_UNION
 �ṹ˵��  : ASP_TRANS_P_THRESHOLDS_0_0 �Ĵ����ṹ���塣��ַƫ����:0x80AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP Transaction Probe��bin_0����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_0 : 2;  /* bit[0-1] : 0x0-->ѡ��threshold_0��delay��32��outstanding��2����
                                                         0x1-->ѡ��threshold_1��delay��64��outstanding��4����
                                                         0x2-->ѡ��threshold_2��delay��128��outstanding��6����
                                                         0x3-->ѡ��threshold_3��delay��256��outstanding��10���� */
        unsigned int  reserved       : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_UNION
 �ṹ˵��  : ASP_TRANS_P_THRESHOLDS_0_1 �Ĵ����ṹ���塣��ַƫ����:0x80B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP Transaction Probe��bin_1����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_1 : 2;  /* bit[0-1] : 0x0-->ѡ��threshold_0��delay��32��outstanding��2����
                                                         0x1-->ѡ��threshold_1��delay��64��outstanding��4����
                                                         0x2-->ѡ��threshold_2��delay��128��outstanding��6����
                                                         0x3-->ѡ��threshold_3��delay��256��outstanding��10���� */
        unsigned int  reserved       : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_UNION
 �ṹ˵��  : ASP_TRANS_P_THRESHOLDS_0_2 �Ĵ����ṹ���塣��ַƫ����:0x80B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP Transaction Probe��bin_1����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_2 : 2;  /* bit[0-1] : 0x0-->ѡ��threshold_0��delay��32��outstanding��2����
                                                         0x1-->ѡ��threshold_1��delay��64��outstanding��4����
                                                         0x2-->ѡ��threshold_2��delay��128��outstanding��6����
                                                         0x3-->ѡ��threshold_3��delay��256��outstanding��10���� */
        unsigned int  reserved       : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_thresholds_0_2_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_thresholds_0_2_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_UNION
 �ṹ˵��  : ASP_TRANS_P_THRESHOLDS_0_3 �Ĵ����ṹ���塣��ַƫ����:0x80B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP Transaction Probe��bin_1����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_3 : 2;  /* bit[0-1] : 0x0-->ѡ��threshold_0��delay��32��outstanding��2����
                                                         0x1-->ѡ��threshold_1��delay��64��outstanding��4����
                                                         0x2-->ѡ��threshold_2��delay��128��outstanding��6����
                                                         0x3-->ѡ��threshold_3��delay��256��outstanding��10���� */
        unsigned int  reserved       : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_thresholds_0_3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_thresholds_0_3_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_UNION
 �ṹ˵��  : ASP_TRANS_P_OVERFLOWSTATUS �Ĵ����ṹ���塣��ַƫ����:0x80EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ��������״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowstatus : 1;  /* bit[0-0] : 1��ʾͳ�Ƽ�������� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_UNION
 �ṹ˵��  : ASP_TRANS_P_OVERFLOWRESET �Ĵ����ṹ���塣��ַƫ����:0x80F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ��������״̬����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowreset : 1;  /* bit[0-0] : д1ʱ��OverflowStatus�Ĵ������㣬���üĴ���ʱ�ӷ���0 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_UNION
 �ṹ˵��  : ASP_TRANS_P_PENDINGEVENTMODE �Ĵ����ṹ���塣��ַƫ����:0x80F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: outstandingͳ�Ƽ�������ģʽ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pendingeventmode : 1;  /* bit[0-0] : 0x0-->��outstanding���� > 0ʱ��ÿ��cycle��ȥ�����������ռ�outstanding������
                                                           0x1-->������1��responseʱ���ʹ����������ռ�outstanding������ */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_UNION
 �ṹ˵��  : ASP_TRANS_P_PRESCALER �Ĵ����ṹ���塣��ַƫ����:0x80F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: latencyͳ��ϵ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prescaler : 8;  /* bit[0-7] : ��ͳ��latencyʱ����ͳ��ֵ����PreScaler��ֵ��PreScalerȡֵ��Χ1~255��������Ϊ0ʱ����ʾdisable�ù��ܣ�
                                                    ������PreScaler��ֵʱ����Ҫ������En�Ĵ���Ϊ0����disable Transaction Probe�� */
        unsigned int  reserved  : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_UNION
 �ṹ˵��  : ASP_TRANS_M_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x8400����ֵ:0xDED6C706�����:32
 �Ĵ���˵��: ASP Transaction probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus��Packet Probe����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_UNION
 �ṹ˵��  : ASP_TRANS_M_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x8404����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_UNION
 �ṹ˵��  : ASP_TRANS_M_MAINCTL �Ĵ����ṹ���塣��ַƫ����:0x8408����ֵ:0x00000000�����:32
 �Ĵ���˵��: Transaction Probeȫ�ֿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  erren                     : 1;  /* bit[0]   : ErrEn��ʹ��Packet Probe����⵽���κδ���״̬��Packet�ϱ���Observer�����ڱ����ߵ�Packet Probe��֧��trace���ܣ��ʴ�λ�����塣 */
        unsigned int  traceen                   : 1;  /* bit[1]   : TraceEn�������߲�֧��Trace���ܣ��ʴ�λ�����塣 */
        unsigned int  payloaden                 : 1;  /* bit[2]   : PayloadEn�������߲�֧��Trace���ܣ��ʴ�λ�����塣 */
        unsigned int  staten                    : 1;  /* bit[3]   : StatEn��ͳ��ģ��ʹ�ܼĴ�������StatEn��0����Ϊ1ʱ��ͳ�Ƽ����������㣻��StatEn����Ϊ0ʱ��ͳ�Ƽ�������disabled�� */
        unsigned int  alarmen                   : 1;  /* bit[4]   : AlarmEn���ж�ʹ�����á�
                                                                    0-->�����жϣ�
                                                                    1-->ʹ���ж������ */
        unsigned int  statconddump              : 1;  /* bit[5]   : 0-->��ʾ������dumpͳ�����ݣ��Ĵ���counters_m_val��ֵ��ʵʱ��ӳͳ�Ƽ�������ֵ��
                                                                    1-->��ʾ������dump���ݣ��ڸ�����ͳ�������ڷ���out of bounds �¼����ŻὫͳ�Ƽ�������ֵdump���Ĵ���counters_m_val�С� */
        unsigned int  intrusivemode             : 1;  /* bit[6]   : IntrusiveMode�� �����߲�֧��Trace���ܣ��ʴ�λ�����塣 */
        unsigned int  filtbytealwayschainableen : 1;  /* bit[7]   : FiltByteAlwaysChainableEn��������ż������������ʹ�ܵ�ȫ�����ã�
                                                                    0-->��ʹ�ܣ���ʱ�����в�statistic counters�����Ա�Map��
                                                                    1-->ʹ�ܣ�ֻ��ż��statistic counters�ſ��Ա�Map�� */
        unsigned int  reserved                  : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_UNION
 �ṹ˵��  : ASP_TRANS_M_CFGCTL �Ĵ����ṹ���塣��ַƫ����:0x840C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Packet Probeʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  globalen : 1;  /* bit[0]   : GlobalEn��Packet Probeʹ���źţ�����Ч�� */
        unsigned int  active   : 1;  /* bit[1]   : Active��Packet Probe�Ĺ���״ָ̬ʾ�źš�
                                                   0-->��GlobalEn����Ϊ0�ļ���cycle��Active�����ͣ�
                                                   1-->��GlobalEn����Ϊ1ʱ��Active�����ߣ���ʱ�������Packet Probe�������á� */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_active_START    (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_UNION
 �ṹ˵��  : ASP_TRANS_M_STATPERIOD �Ĵ����ṹ���塣��ַƫ����:0x8424����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ���������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statperiod : 5;  /* bit[0-4] : �Զ�ͳ��ģʽ�µ�ͳ�����ڣ�ͳ������= N_Cycle = 2^min(23,StatPeriod)�����Ϊ8 mega cycles����СΪ2 cycles��������Ϊ0ʱ���Զ�ͳ��ģʽ���رգ���Ҫ�����ֶ�ģʽ��Ҳ��������StatGo�Ĵ�����ʵ�ִ���ͳ�ơ� */
        unsigned int  reserved   : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_UNION
 �ṹ˵��  : ASP_TRANS_M_STATGO �Ĵ����ṹ���塣��ַƫ����:0x8428����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ֶ�����ͳ�Ƽ�ʱ��ʼʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statgo   : 1;  /* bit[0]   : ��StatPeriod=0ʱ����globalenΪ1����Ĵ���StatGoд1����Ὣcounter_m_val��ֵ��statalarmmax��statalarmmin��ֵ���бȽϣ����üĴ���ʼ�շ���0�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_statgo_START    (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_UNION
 �ṹ˵��  : ASP_TRANS_M_STATALARMMIN �Ĵ����ṹ���塣��ַƫ����:0x842C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�����С�澯��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmin : 32; /* bit[0-31]: ������һ��ͳ�Ƽ�������ֵС��StatAlarmMin��ֵ���ʹ����澯�Ĵ����� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_UNION
 �ṹ˵��  : ASP_TRANS_M_STATALARMMAX �Ĵ����ṹ���塣��ַƫ����:0x8430����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ��������澯��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmax : 32; /* bit[0-31]: ������һ��ͳ�Ƽ�������ֵ����StatAlarmMax��ֵ���ʹ����澯�Ĵ����� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_UNION
 �ṹ˵��  : ASP_TRANS_M_STATALARMSTATUS �Ĵ����ṹ���塣��ַƫ����:0x8434����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmstatus : 1;  /* bit[0]   : ������һ��ͳ�Ƽ�������ֵ����StatAlarmMax��С��StatAlarmMin����üĴ�����λΪ1�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_UNION
 �ṹ˵��  : ASP_TRANS_M_STATALARMCLR �Ĵ����ṹ���塣��ַƫ����:0x8438����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯״̬����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmclr : 1;  /* bit[0]   : д1������StatAlarmStatus�Ĵ��������˼Ĵ�����������0�� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_0_SRC �Ĵ����ṹ���塣��ַƫ����:0x8538����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_0_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x853C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_0_VAL �Ĵ����ṹ���塣��ַƫ����:0x8540����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 12; /* bit[0-11] : ��Counters_0_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_1_SRC �Ĵ����ṹ���塣��ַƫ����:0x854C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_1_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x8550����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_1_VAL �Ĵ����ṹ���塣��ַƫ����:0x8554����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 12; /* bit[0-11] : ��Counters_1_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_2_SRC �Ĵ����ṹ���塣��ַƫ����:0x8560����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_2_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x8564����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_2_VAL �Ĵ����ṹ���塣��ַƫ����:0x8568����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_val : 12; /* bit[0-11] : ��Counters_2_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_3_SRC �Ĵ����ṹ���塣��ַƫ����:0x8574����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_3_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x8578����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_3_VAL �Ĵ����ṹ���塣��ַƫ����:0x857C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_val : 12; /* bit[0-11] : ��Counters_3_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_4_SRC �Ĵ����ṹ���塣��ַƫ����:0x8588����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_4_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x858C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_4_VAL �Ĵ����ṹ���塣��ַƫ����:0x8590����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_val : 12; /* bit[0-11] : ��Counters_4_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_5_SRC �Ĵ����ṹ���塣��ַƫ����:0x859C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_5_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x85A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_5_VAL �Ĵ����ṹ���塣��ַƫ����:0x85A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_val : 12; /* bit[0-11] : ��Counters_5_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_6_SRC �Ĵ����ṹ���塣��ַƫ����:0x85B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_6_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x85B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_6_VAL �Ĵ����ṹ���塣��ַƫ����:0x85B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_val : 12; /* bit[0-11] : ��Counters_6_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_7_SRC �Ĵ����ṹ���塣��ַƫ����:0x85C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_src : 6;  /* bit[0-5] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x20-->Bin 0��delay��0~31��outstanding��0~1����
                                                         0x21-->Bin 1��delay��32~63��outstanding��2~3����
                                                         0x22-->Bin 2��delay��64~127��outstanding��4~5����
                                                         0x23-->Bin 3��delay��128~255��outstanding��8~9����
                                                         0x24-->Bin 4��delay��>= 256��outstanding��>= 10����
                                                         ����-->������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_7_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x85C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_UNION
 �ṹ˵��  : ASP_TRANS_M_COUNTERS_7_VAL �Ĵ����ṹ���塣��ַƫ����:0x85CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_val : 12; /* bit[0-11] : ��Counters_7_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (11)




/****************************************************************************
                     (3/9) SYSBUS
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_UNION
 �ṹ˵��  : CCI2SYSBUS_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0xFF81DF04�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : CCI2SYSBUS_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_UNION
 �ṹ˵��  : CCI2SYSBUS_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_UNION
 �ṹ˵��  : CCI2SYSBUS_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_UNION
 �ṹ˵��  : CCI2SYSBUS_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_UNION
 �ṹ˵��  : AOBUS2DDRC_ADAPTER_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0x4995B101�����:32
 �Ĵ���˵��: adapter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_UNION
 �ṹ˵��  : AOBUS2DDRC_ADAPTER_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_UNION
 �ṹ˵��  : AOBUS2DDRC_ADAPTERRATE �Ĵ����ṹ���塣��ַƫ����:0x1008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_UNION
 �ṹ˵��  : AOBUS2DDRC_ADAP_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x100C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter bypass�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_UNION
 �ṹ˵��  : SYS2CFG_ADAPTER_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1080����ֵ:0x13DCBD01�����:32
 �Ĵ���˵��: adapter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_UNION
 �ṹ˵��  : SYS2CFG_ADAPTER_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1084����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_UNION
 �ṹ˵��  : SYS2CFG_ADAPTERRATE �Ĵ����ṹ���塣��ַƫ����:0x1088����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_UNION
 �ṹ˵��  : SYS2CFG_ADAP_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x108C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter bypass�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_UNION
 �ṹ˵��  : PERI2DDRC_ADAPTER_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1100����ֵ:0xB46F5701�����:32
 �Ĵ���˵��: adapter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_UNION
 �ṹ˵��  : PERI2DDRC_ADAPTER_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1104����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_UNION
 �ṹ˵��  : PERI2DDRC_ADAPTERRATE �Ĵ����ṹ���塣��ַƫ����:0x1108����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_UNION
 �ṹ˵��  : PERI2DDRC_ADAP_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x110C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter bypass�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_UNION
 �ṹ˵��  : SYS2PERI_ADAPTER_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1180����ֵ:0xF54FB501�����:32
 �Ĵ���˵��: adapter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_UNION
 �ṹ˵��  : SYS2PERI_ADAPTER_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1184����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_UNION
 �ṹ˵��  : SYS2PERI_ADAPTERRATE �Ĵ����ṹ���塣��ַƫ����:0x1188����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_UNION
 �ṹ˵��  : SYS2PERI_ADAP_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x118C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter bypass�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_UNION
 �ṹ˵��  : MODEM2DDR_ADAPTER_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1200����ֵ:0xF7A25201�����:32
 �Ĵ���˵��: adapter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_UNION
 �ṹ˵��  : MODEM2DDR_ADAPTER_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1204����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_UNION
 �ṹ˵��  : MODEM2DDR_ADAPTERRATE �Ĵ����ṹ���塣��ַƫ����:0x1208����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_UNION
 �ṹ˵��  : MODEM2DDR_ADAP_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x120C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter bypass�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_UNION
 �ṹ˵��  : CFG2SYS_ADAPTER_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1280����ֵ:0x14ADFD01�����:32
 �Ĵ���˵��: adapter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_UNION
 �ṹ˵��  : CFG2SYS_ADAPTER_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1284����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_UNION
 �ṹ˵��  : CFG2SYS_ADAPTERRATE �Ĵ����ṹ���塣��ַƫ����:0x1288����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_UNION
 �ṹ˵��  : CFG2SYS_ADAP_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x128C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter bypass�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_UNION
 �ṹ˵��  : MMC1_ADAPTER_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1300����ֵ:0xE0199F01�����:32
 �Ĵ���˵��: adapter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_UNION
 �ṹ˵��  : MMC1_ADAPTER_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1304����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_UNION
 �ṹ˵��  : MMC1_ADAPTERRATE �Ĵ����ṹ���塣��ַƫ����:0x1308����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_UNION
 �ṹ˵��  : MMC1_ADAP_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x130C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter bypass�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_UNION
 �ṹ˵��  : SYSBUS_ERR_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1C00����ֵ:0x08DA560D�����:32
 �Ĵ���˵��: SYSBUS Err probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: SYS_BUS��error probe����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_UNION
 �ṹ˵��  : SYSBUS_ERR_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1C04����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_UNION
 �ṹ˵��  : SYSBUS_FAULTEN �Ĵ����ṹ���塣��ַƫ����:0x1C08����ֵ:0x00000000�����:32
 �Ĵ���˵��: SYSBUS Err probeʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  faulten  : 1;  /* bit[0]   : ʹ������жϣ�����Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_UNION
 �ṹ˵��  : SYSBUS_ERRVLD �Ĵ����ṹ���塣��ַƫ����:0x1C0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log��Чָʾ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errvld   : 1;  /* bit[0]   : Error log��Чָʾ״̬�Ĵ���������Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_UNION
 �ṹ˵��  : SYSBUS_ERRCLR �Ĵ����ṹ���塣��ַƫ����:0x1C10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errclr   : 1;  /* bit[0-0] : 1.д1'b1����ErrVld�Ĵ���������ж�ʹ�ܣ�ͬʱҲ����жϣ���
                                                   2.д1'b1�����ܴ洢��ErrClr�Ĵ����У����üĴ�������������1'b0�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_UNION
 �ṹ˵��  : SYSBUS_ERRLOG0 �Ĵ����ṹ���塣��ַƫ����:0x1C14����ֵ:0x80000000�����:32
 �Ĵ���˵��: Error log0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lock     : 1;  /* bit[0]    : ֻ��Transaction�Ƿ�ΪLock����������Ч�� */
        unsigned int  opc      : 4;  /* bit[1-4]  : Transaction�������ͣ�
                                                    0-->RD��INCR�Ķ�������
                                                    1-->RDW��WRAP�Ķ�������
                                                    2-->RDL��Exclusive ��������
                                                    3-->RDX��Lock read��
                                                    4-->WR��INCRд������
                                                    5-->WRW��WRAPд������
                                                    6-->WRC��Exclusiveд������
                                                    8-->PRE��FIXED BURST��
                                                    9-->URG��urgency packet��Error Probe�����⵽����packet��
                                                    ����-->Reserveed���Ƿ������� */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : ���� */
        unsigned int  errcode  : 3;  /* bit[8-10] : �������ͣ�
                                                    0-->������slave����Error Response��
                                                    1-->master���������ߵ�Reserve��ַ�ռ䣻
                                                    2-->master������slave��֧�ֵ�Burst���ͣ���ǰ���߲���������ֳ�������
                                                    3-->master�����˵�������
                                                    4-->����Ȩ�ޱ���
                                                    5-->master����ʱ���յ�Firewall��Hide Error Response��
                                                    6-->������slave TimeOut��������Error Response��
                                                    7-->none�� */
        unsigned int  reserved_1: 5;  /* bit[11-15]: ���� */
        unsigned int  len1     : 8;  /* bit[16-23]: ��ʾ����Transaction�İ�������λΪByte */
        unsigned int  reserved_2: 7;  /* bit[24-30]: ���� */
        unsigned int  format   : 1;  /* bit[31]   : ���ڱ�ʾError log0�ĸ�ʽ��FlexNoC2.7�Ժ�汾�̶�Ϊ1'b1�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_UNION
 �ṹ˵��  : SYSBUS_ERRLOG1 �Ĵ����ṹ���塣��ַƫ����:0x1C18����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog1  : 22; /* bit[0-21] : RouteId��·����Ϣ����bit��������
                                                    [21:17]-->Initiator Flow ID�����ڱ�ʾ������ʵ�master��
                                                    [16:12]-->target Flow ID�����ڱ�ʾ�����ʵ�slave��
                                                    [11:9]-->Target NIU SubRange��
                                                    [8:0]-->Seq ID��Transaction��ǣ� */
        unsigned int  reserved : 10; /* bit[22-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_errlog1_END     (21)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_UNION
 �ṹ˵��  : SYSBUS_ERRLOG3 �Ĵ����ṹ���塣��ַƫ����:0x1C20����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog3  : 31; /* bit[0-30] : ���ʵ�ֵַ */
        unsigned int  reserved : 1;  /* bit[31-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_errlog3_START   (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_errlog3_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_UNION
 �ṹ˵��  : SYSBUS_ERRLOG5 �Ĵ����ṹ���塣��ַƫ����:0x1C28����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog5  : 17; /* bit[0-16] : User�ź�ֵ */
        unsigned int  reserved : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_errlog5_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_UNION
 �ṹ˵��  : SYSBUS_ERRLOG7 �Ĵ����ṹ���塣��ַƫ����:0x1C30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog7  : 1;  /* bit[0]   : ��ȫ�ź�ֵ */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_errlog7_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x2000����ֵ:0x3BCD1F06�����:32
 �Ĵ���˵��: SYSBUS_DDRC Packet probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: SYSBUS_DDRC��Packet Probe����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x2004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_MAINCTL �Ĵ����ṹ���塣��ַƫ����:0x2008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Packet Probeȫ�ֿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  erren                     : 1;  /* bit[0]   : ErrEn��ʹ��Packet Probe����⵽���κδ���״̬��Packet�ϱ���Observer�����ڱ����ߵ�Packet Probe��֧��trace���ܣ��ʴ�λ�����塣 */
        unsigned int  traceen                   : 1;  /* bit[1]   : TraceEn�������߲�֧��Trace���ܣ��ʴ�λ�����塣 */
        unsigned int  payloaden                 : 1;  /* bit[2]   : PayloadEn�������߲�֧��Trace���ܣ��ʴ�λ�����塣 */
        unsigned int  staten                    : 1;  /* bit[3]   : StatEn��ͳ��ģ��ʹ�ܼĴ�������StatEn��0����Ϊ1ʱ��ͳ�Ƽ����������㣻��StatEn����Ϊ0ʱ��ͳ�Ƽ�������disabled�� */
        unsigned int  alarmen                   : 1;  /* bit[4]   : AlarmEn���ж�ʹ�����á�
                                                                    0-->�����жϣ�
                                                                    1-->ʹ���ж������ */
        unsigned int  statconddump              : 1;  /* bit[5]   : 0-->��ʾ������dumpͳ�����ݣ��Ĵ���counters_m_val��ֵ��ʵʱ��ӳͳ�Ƽ�������ֵ��
                                                                    1-->��ʾ������dump���ݣ��ڸ�����ͳ�������ڷ���out of bounds �¼����ŻὫͳ�Ƽ�������ֵdump���Ĵ���counters_m_val�С� */
        unsigned int  intrusivemode             : 1;  /* bit[6]   : IntrusiveMode�� �����߲�֧��Trace���ܣ��ʴ�λ�����塣 */
        unsigned int  filtbytealwayschainableen : 1;  /* bit[7]   : FiltByteAlwaysChainableEn��������ż������������ʹ�ܵ�ȫ�����ã�
                                                                    0-->��ʹ�ܣ���ʱ�����в�statistic counters�����Ա�Map��
                                                                    1-->ʹ�ܣ�ֻ��ż��statistic counters�ſ��Ա�Map�� */
        unsigned int  reserved                  : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_erren_START                      (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_erren_END                        (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_traceen_START                    (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_traceen_END                      (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_payloaden_START                  (2)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_payloaden_END                    (2)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_staten_START                     (3)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_staten_END                       (3)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_alarmen_START                    (4)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_alarmen_END                      (4)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_statconddump_START               (5)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_statconddump_END                 (5)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_intrusivemode_START              (6)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_intrusivemode_END                (6)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_CFGCTL �Ĵ����ṹ���塣��ַƫ����:0x200C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Packet Probeʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  globalen : 1;  /* bit[0]   : GlobalEn��Packet Probeʹ���źţ�����Ч�� */
        unsigned int  active   : 1;  /* bit[1]   : Active��Packet Probe�Ĺ���״ָ̬ʾ�źš�
                                                   0-->��GlobalEn����Ϊ0�ļ���cycle��Active�����ͣ�
                                                   1-->��GlobalEn����Ϊ1ʱ��Active�����ߣ���ʱ�������Packet Probe�������á� */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_globalen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_globalen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_active_START    (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_active_END      (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_FILTERLUT �Ĵ����ṹ���塣��ַƫ����:0x2014����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����������ұ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filterlut : 2;  /* bit[0-1] : ѡ�����������
                                                    0x3 reserved
                                                    0x2-->~F0 ��������ΪF0ȡ����
                                                    0x1-->F0 ��������ΪF0��
                                                    0x0 reserved */
        unsigned int  reserved  : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_filterlut_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_filterlut_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_STATPERIOD �Ĵ����ṹ���塣��ַƫ����:0x2024����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ���������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statperiod : 5;  /* bit[0-4] : �Զ�ͳ��ģʽ�µ�ͳ�����ڣ�ͳ������= N_Cycle = 2^min(23,StatPeriod)�����Ϊ8 mega cycles����СΪ2 cycles��������Ϊ0ʱ���Զ�ͳ��ģʽ���رգ���Ҫ�����ֶ�ģʽ��Ҳ��������StatGo�Ĵ�����ʵ�ִ���ͳ�ơ� */
        unsigned int  reserved   : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_statperiod_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_STATGO �Ĵ����ṹ���塣��ַƫ����:0x2028����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ֶ�����ͳ�Ƽ�ʱ��ʼʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statgo   : 1;  /* bit[0]   : ��StatPeriod=0ʱ����globalenΪ1����Ĵ���StatGoд1����Ὣcounter_m_val��ֵ��statalarmmax��statalarmmin��ֵ���бȽϣ����üĴ���ʼ�շ���0�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_statgo_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_statgo_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_STATALARMMIN �Ĵ����ṹ���塣��ַƫ����:0x202C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�����С�澯��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmin : 32; /* bit[0-31]: ������һ��ͳ�Ƽ�������ֵС��StatAlarmMin��ֵ���ʹ����澯�Ĵ����� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_statalarmmin_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_STATALARMMAX �Ĵ����ṹ���塣��ַƫ����:0x2030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ��������澯��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmax : 32; /* bit[0-31]: ������һ��ͳ�Ƽ�������ֵ����StatAlarmMax��ֵ���ʹ����澯�Ĵ����� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_statalarmmax_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_STATALARMSTATUS �Ĵ����ṹ���塣��ַƫ����:0x2034����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmstatus : 1;  /* bit[0]   : ������һ��ͳ�Ƽ�������ֵ����StatAlarmMax��С��StatAlarmMin����üĴ�����λΪ1�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_STATALARMCLR �Ĵ����ṹ���塣��ַƫ����:0x2038����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯״̬����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmclr : 1;  /* bit[0]   : д1������StatAlarmStatus�Ĵ��������˼Ĵ�����������0�� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_statalarmclr_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE �Ĵ����ṹ���塣��ַƫ����:0x2044����ֵ:0x00000000�����:32
 �Ĵ���˵��: F0��RouteId������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_routeidbase : 22; /* bit[0-21] : ͨ������routeId���Թ���master��slave�ķ���ͨ·�ϵ�Packet��
                                                                 [21:17]-->initiator flow�����ڱ�ʾmaster ID��
                                                                 [16:12]-->target flow�����ڱ�ʾslave ID��
                                                                 [11:9]-->Target SubRange�����ڱ�ʾͬһ����slave��ͬ��Mapping��ַ��
                                                                 [8:0]-->SeqIds�����ڱ�ʾͬһ������ͨ·�Ĳ�ͬtransaction��ID�����鲻����4bit��Ϊ���������� */
        unsigned int  reserved              : 10; /* bit[22-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_filters_0_routeidbase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_filters_0_routeidbase_END    (21)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK �Ĵ����ṹ���塣��ַƫ����:0x2048����ֵ:0x00000000�����:32
 �Ĵ���˵��: F0��RouteId��������Mask����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_routeidmask : 22; /* bit[0-21] : ��RouteIdBase����Mask��
                                                                 ���磺��������Ϊinitiator flow + target flow����ô���ô˼Ĵ�����ֵΪ0x3FF000�� */
        unsigned int  reserved              : 10; /* bit[22-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_filters_0_routeidmask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_filters_0_routeidmask_END    (21)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_F0_ADDRBASE �Ĵ����ṹ���塣��ַƫ����:0x204C����ֵ:0x00000000�����:32
 �Ĵ���˵��: F0�ĵ�ַ������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_addrbase_low : 32; /* bit[0-31]: ��ַ���������Ļ���ַ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_filters_0_addrbase_low_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_filters_0_addrbase_low_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_F0_WINDOWSIZE �Ĵ����ṹ���塣��ַƫ����:0x2054����ֵ:0x00000000�����:32
 �Ĵ���˵��: F0�ĵ�ַ���˵�Mask��ַ��С����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_windowsize : 6;  /* bit[0-5] : ��ַ���˵�Mask���ڴ�С��
                                                               ���磺��ַ���˵�Mask���ڴ�СΪ64MB��WidowSize=log2(64MB)=26����ʱ��������filter_0_windowsize=0x1A��
                                                               Address Mask=~��2^max(WindowSize,packet.len)-1��=0xFC000000��packet.lenΪNOC�ڲ���ʾһ��packet����������λ����ֵΪ6~7����
                                                               ��������Ϊ��PacketAddress & AddressMask = AddressBase & AddressMask�� */
        unsigned int  reserved             : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_filters_0_windowsize_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_filters_0_windowsize_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_F0_SECURITYBASE �Ĵ����ṹ���塣��ַƫ����:0x2058����ֵ:0x00000000�����:32
 �Ĵ���˵��: F0�İ�ȫ������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_securitybase : 1;  /* bit[0]   : 0-->��ʾ��ȫ����������
                                                                 1-->��ʾ�ǰ�ȫ���������� */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_filters_0_securitybase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_filters_0_securitybase_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_F0_SECURITYMASK �Ĵ����ṹ���塣��ַƫ����:0x205C����ֵ:0x00000000�����:32
 �Ĵ���˵��: F0�İ�ȫ����������Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_securitymask : 1;  /* bit[0]   : ��ȫ����������packet.Security & SecurityMask = SecurityBase & SecurityMasks��
                                                                 Ҳ����˵��Filters_0_SecurityMask=1ʱ��ȫ��������Filters_0_SecurityBase��Ч�����Թ��˰�ȫ��ǰ�ȫpacket�����򣬲���������ã� */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_filters_0_securitymask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_filters_0_securitymask_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_F0_OPCODE �Ĵ����ṹ���塣��ַƫ����:0x2060����ֵ:0x00000000�����:32
 �Ĵ���˵��: F0��Opcode������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rden     : 1;  /* bit[0]   : 0-->��ѡ��ͳ�ƶ�����packet��
                                                   1-->ѡ��ͳ�ƶ�����packet�� */
        unsigned int  wren     : 1;  /* bit[1]   : 0-->��ѡ��ͳ��д����packet��
                                                   1-->ѡ��ͳ��д����packet�� */
        unsigned int  locken   : 1;  /* bit[2]   : 0-->��ѡ��ͳ��exclusive transaction��
                                                   1-->ѡ��ͳ��exclusive transaction�� */
        unsigned int  urgen    : 1;  /* bit[3]   : 0-->��ѡ��ͳ�ƴ���urgency��packet��
                                                   1-->ѡ��ͳ�ƴ���urgency��packet�� */
        unsigned int  reserved : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_rden_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_rden_END        (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_wren_START      (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_wren_END        (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_locken_START    (2)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_locken_END      (2)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_urgen_START     (3)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_urgen_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_F0_STATUS �Ĵ����ṹ���塣��ַƫ����:0x2064����ֵ:0x00000000�����:32
 �Ĵ���˵��: F0��packet״̬��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reqen    : 1;  /* bit[0]   : 0-->��ѡ��ͳ��request packet��
                                                   1-->ѡ��ͳ��request packet�� */
        unsigned int  rspen    : 1;  /* bit[1]   : 0-->��ѡ��ͳ��response packet��
                                                   1-->ѡ��ͳ��response packet�� */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_reqen_START     (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_reqen_END       (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_rspen_START     (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_rspen_END       (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_F0_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x2068����ֵ:0x00000000�����:32
 �Ĵ���˵��: F0�İ�����������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_length : 4;  /* bit[0-3] : ѡ��ͳ�ư���С�ڵ���2^Filters_0_Length��packet */
        unsigned int  reserved         : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_filters_0_length_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_filters_0_length_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_F0_URGENCY �Ĵ����ṹ���塣��ַƫ����:0x206C����ֵ:0x00000000�����:32
 �Ĵ���˵��: F0��urgency��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_urgency : 2;  /* bit[0-1] : ѡ��ͳ��urgency ���ڵ���Filters_0_Urgency��packet��Eg.����Ϊ0�����������urgency�ȼ���packet�� */
        unsigned int  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_filters_0_urgency_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_filters_0_urgency_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_F0_USERBASE �Ĵ����ṹ���塣��ַƫ����:0x2070����ֵ:0x00000000�����:32
 �Ĵ���˵��: F0��User��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_userbase : 12; /* bit[0-11] : User�źŹ������� */
        unsigned int  reserved           : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_filters_0_userbase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_filters_0_userbase_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_F0_USERMASK �Ĵ����ṹ���塣��ַƫ����:0x2074����ֵ:0x00000000�����:32
 �Ĵ���˵��: F0��User��������Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_usermask : 12; /* bit[0-11] : ��UserBase����Mask��ѡ��UserBase�е����⼸bit User�ź���Ϊ����������
                                                              ����������packet.User & UserMask = UserBase & UserMask�� */
        unsigned int  reserved           : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_filters_0_usermask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_filters_0_usermask_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_COUNTERS_0_SRC �Ĵ����ṹ���塣��ַƫ����:0x2138����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_src : 5;  /* bit[0-4] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x01-->Clock cycles��
                                                         0x02-->IDLE cycles��
                                                         0x03-->Transfer cycles��
                                                         0x04-->Busy cycles��
                                                         0x05-->Wait cycles��
                                                         0x06-->Packets����ͳ�ƣ�
                                                         0x07-->��LUT����ѡ�е�Packet����ͳ�ƣ�
                                                         0x08-->ͳ���ܵ�bytes������
                                                         0x09-->ͳ��Pressure level>0��ʱ�����ڸ�����
                                                         0x0A-->ͳ��Pressure level>1��ʱ�����ڸ�����
                                                         0x0B-->ͳ��Pressure level>2��Press[2]=1����ʱ�����ڸ�����
                                                         0x0C-->��F0��������ѡ�е�Packet������
                                                         0x0D-->��F1��������ѡ�е�Packet������
                                                         0x0E~0x0F-->������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x11-->ͨ��LUT����ͳ��Packet�е���ЧByte������
                                                         0x12-->ͨ��LUT����ͳ��Packet�е�Byte����������ЧByte�������ں�byteenable��д��������
                                                         0x13-->ͨ��filtersx����counters_m_src�е�m������ʱ��filterx��ʾfilter0����counters_m_src�е�m��ż��ʱ��filterx��ʾfilter0������ͳ��Packet�е���ЧByte������
                                                         0x14-->ͨ��filtersx����counters_m_src�е�m������ʱ��filterx��ʾfilter0����counters_m_src�е�m��ż��ʱ��filterx��ʾfilter0������ͳ��Packet�е�Byte����������ЧByte����
                                                         0x15~0x1F-->������
                                                         0x20~0x3F-->������ */
        unsigned int  reserved       : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_counters_0_src_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x213C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_COUNTERS_0_VAL �Ĵ����ṹ���塣��ַƫ����:0x2140����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 15; /* bit[0-14] : ��Counters_0_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 17; /* bit[15-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_counters_0_val_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_COUNTERS_1_SRC �Ĵ����ṹ���塣��ַƫ����:0x214C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter��ͳ�����Ϳ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_src : 5;  /* bit[0-4] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                         0x00-->disabled��������
                                                         0x01-->Clock cycles��
                                                         0x02-->IDLE cycles��
                                                         0x03-->Transfer cycles��
                                                         0x04-->Busy cycles��
                                                         0x05-->Wait cycles��
                                                         0x06-->Packets����ͳ�ƣ�
                                                         0x07-->��LUT����ѡ�е�Packet����ͳ�ƣ�
                                                         0x08-->ͳ���ܵ�bytes������
                                                         0x09-->ͳ��Pressure level>0��ʱ�����ڸ�����
                                                         0x0A-->ͳ��Pressure level>1��ʱ�����ڸ�����
                                                         0x0B-->ͳ��Pressure level>2��Press[2]=1����ʱ�����ڸ�����
                                                         0x0C-->��F0��������ѡ�е�Packet������
                                                         0x0D-->��F1��������ѡ�е�Packet������
                                                         0x0E~0x0F-->������
                                                         0x10-->��counter_2N��counter_2N+1����ͳ�Ƽ��������д�����ֻ�б��Ϊ����ͳ�Ƽ������ɱ���������ֻ�ܽ�����ͳ�Ƽ��������д�����
                                                         0x11-->ͨ��LUT����ͳ��Packet�е���ЧByte������
                                                         0x12-->ͨ��LUT����ͳ��Packet�е�Byte����������ЧByte�������ں�byteenable��д��������
                                                         0x13-->ͨ��filtersx����counters_m_src�е�m������ʱ��filterx��ʾfilter0����counters_m_src�е�m��ż��ʱ��filterx��ʾfilter0������ͳ��Packet�е���ЧByte������
                                                         0x14-->ͨ��filtersx����counters_m_src�е�m������ʱ��filterx��ʾfilter0����counters_m_src�е�m��ż��ʱ��filterx��ʾfilter0������ͳ��Packet�е�Byte����������ЧByte����
                                                         0x15~0x1F-->������
                                                         0x20~0x3F-->������ */
        unsigned int  reserved       : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_counters_1_src_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x2150����ֵ:0x00000000�����:32
 �Ĵ���˵��: �澯�жϲ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_alarmmode : 2;  /* bit[0-1] : ��CfgCtl�Ĵ����е�Active=0ʱ���üĴ��������ã�����ʱ����������ã�
                                                               0x0-->OFF���澯ģʽ����disabled��
                                                               0x1-->MIN����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x2-->MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵ����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1��
                                                               0x3-->MIN_MAX����statperiod���õ�ͳ�����ڽ�����counter��ֵС��StatAlarmMin�Ĵ�����ֵ�����StatAlarmMax�Ĵ�����ֵ����StatAlarmStatusΪ1�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_UNION
 �ṹ˵��  : SYSBUS_DDRC_PACKET_COUNTERS_1_VAL �Ĵ����ṹ���塣��ַƫ����:0x2154����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͳ�Ƽ�������ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 15; /* bit[0-14] : ��Counters_1_Val�ﵽ���֮�󣬻ᱣ�ֲ���ֱ����clear���������������⣩�� */
        unsigned int  reserved       : 17; /* bit[15-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_counters_1_val_END    (14)




/****************************************************************************
                     (4/9) CFGBUS
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_UNION
 �ṹ˵��  : DJTAG_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x84797C04�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : DJTAG_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_UNION
 �ṹ˵��  : DJTAG_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_UNION
 �ṹ˵��  : DJTAG_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_UNION
 �ṹ˵��  : DJTAG_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_UNION
 �ṹ˵��  : A7TOCFG_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x4ADBA804�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : A7TOCFG_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_UNION
 �ṹ˵��  : A7TOCFG_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_UNION
 �ṹ˵��  : A7TOCFG_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_UNION
 �ṹ˵��  : A7TOCFG_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_UNION
 �ṹ˵��  : LPMCU_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x6D480D04�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : LPMCU_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_UNION
 �ṹ˵��  : LPMCU_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_UNION
 �ṹ˵��  : LPMCU_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_UNION
 �ṹ˵��  : LPMCU_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_UNION
 �ṹ˵��  : CFGBUS_ERR_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1C00����ֵ:0x08DA560D�����:32
 �Ĵ���˵��: CFG_BUS Err probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: error probe����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_UNION
 �ṹ˵��  : CFGBUS_ERR_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1C04����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_UNION
 �ṹ˵��  : CFGBUS_FAULTEN �Ĵ����ṹ���塣��ַƫ����:0x1C08����ֵ:0x00000000�����:32
 �Ĵ���˵��: CFG_BUS Err probeʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  faulten  : 1;  /* bit[0]   : ʹ������жϣ�����Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_UNION
 �ṹ˵��  : CFGBUS_ERRVLD �Ĵ����ṹ���塣��ַƫ����:0x1C0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log��Чָʾ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errvld   : 1;  /* bit[0]   : Error log��Чָʾ״̬�Ĵ���������Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_UNION
 �ṹ˵��  : CFGBUS_ERRCLR �Ĵ����ṹ���塣��ַƫ����:0x1C10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errclr   : 1;  /* bit[0-0] : 1.д1'b1����ErrVld�Ĵ���������ж�ʹ�ܣ�ͬʱҲ����жϣ���
                                                   2.д1'b1�����ܴ洢��ErrClr�Ĵ����У����üĴ�������������1'b0�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_UNION
 �ṹ˵��  : CFGBUS_ERRLOG0 �Ĵ����ṹ���塣��ַƫ����:0x1C14����ֵ:0x80000000�����:32
 �Ĵ���˵��: Error log0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lock     : 1;  /* bit[0]    : ֻ��Transaction�Ƿ�ΪLock����������Ч�� */
        unsigned int  opc      : 4;  /* bit[1-4]  : Transaction�������ͣ�
                                                    0-->RD��INCR�Ķ�������
                                                    1-->RDW��WRAP�Ķ�������
                                                    2-->RDL��Exclusive ��������
                                                    3-->RDX��Lock read��
                                                    4-->WR��INCRд������
                                                    5-->WRW��WRAPд������
                                                    6-->WRC��Exclusiveд������
                                                    8-->PRE��FIXED BURST��
                                                    9-->URG��urgency packet��Error Probe�����⵽����packet��
                                                    ����-->Reserveed���Ƿ������� */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : ���� */
        unsigned int  errcode  : 3;  /* bit[8-10] : �������ͣ�
                                                    0-->������slave����Error Response��
                                                    1-->master���������ߵ�Reserve��ַ�ռ䣻
                                                    2-->master������slave��֧�ֵ�Burst���ͣ���ǰ���߲���������ֳ�������
                                                    3-->master�����˵�������
                                                    4-->����Ȩ�ޱ���
                                                    5-->master����ʱ���յ�Firewall��Hide Error Response��
                                                    6-->������slave TimeOut��������Error Response��
                                                    7-->none�� */
        unsigned int  reserved_1: 5;  /* bit[11-15]: ���� */
        unsigned int  len1     : 8;  /* bit[16-23]: ��ʾ����Transaction�İ�������λΪByte */
        unsigned int  reserved_2: 7;  /* bit[24-30]: ���� */
        unsigned int  format   : 1;  /* bit[31]   : ���ڱ�ʾError log0�ĸ�ʽ��FlexNoC2.7�Ժ�汾�̶�Ϊ1'b1�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_UNION
 �ṹ˵��  : CFGBUS_ERRLOG1 �Ĵ����ṹ���塣��ַƫ����:0x1C18����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog1  : 14; /* bit[0-13] : RouteId��·����Ϣ����bit��������
                                                    [13:10]-->Initiator Flow ID�����ڱ�ʾ������ʵ�master��
                                                    [9:7]-->target Flow ID�����ڱ�ʾ�����ʵ�slave��
                                                    [6:0]-->Seq ID��Transaction��ǣ� */
        unsigned int  reserved : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_UNION
 �ṹ˵��  : CFGBUS_ERRLOG3 �Ĵ����ṹ���塣��ַƫ����:0x1C20����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog3 : 32; /* bit[0-31]: ���ʵ�ֵַ */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_errlog3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_UNION
 �ṹ˵��  : CFGBUS_ERRLOG5 �Ĵ����ṹ���塣��ַƫ����:0x1C28����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog5  : 5;  /* bit[0-4] : User�ź�ֵ */
        unsigned int  reserved : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_UNION
 �ṹ˵��  : CFGBUS_ERRLOG7 �Ĵ����ṹ���塣��ַƫ����:0x1C30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog7  : 1;  /* bit[0]   : ��ȫ�ź�ֵ */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_errlog7_END     (0)




/****************************************************************************
                     (5/9) DMABUS
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_UNION
 �ṹ˵��  : DMAC_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0xD08E8504�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : DMAC_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_UNION
 �ṹ˵��  : DMAC_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_UNION
 �ṹ˵��  : DMAC_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_UNION
 �ṹ˵��  : DMAC_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_UNION
 �ṹ˵��  : DMA2SYS_ADAPTER_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0x5B785B01�����:32
 �Ĵ���˵��: adapter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_UNION
 �ṹ˵��  : DMA2SYS_ADAPTER_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_UNION
 �ṹ˵��  : DMA2SYS_ADAPTERRATE �Ĵ����ṹ���塣��ַƫ����:0x1008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_UNION
 �ṹ˵��  : DMA2SYS_ADAP_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x100C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter bypass�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_UNION
 �ṹ˵��  : DMABUS_ERR_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1C00����ֵ:0x08DA560D�����:32
 �Ĵ���˵��: DMABUS Err probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: error probe����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_UNION
 �ṹ˵��  : DMABUS_ERR_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1C04����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_UNION
 �ṹ˵��  : DMABUS_FAULTEN �Ĵ����ṹ���塣��ַƫ����:0x1C08����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMABUS Err probeʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  faulten  : 1;  /* bit[0]   : ʹ������жϣ�����Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_UNION
 �ṹ˵��  : DMABUS_ERRVLD �Ĵ����ṹ���塣��ַƫ����:0x1C0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log��Чָʾ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errvld   : 1;  /* bit[0]   : Error log��Чָʾ״̬�Ĵ���������Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_UNION
 �ṹ˵��  : DMABUS_ERRCLR �Ĵ����ṹ���塣��ַƫ����:0x1C10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errclr   : 1;  /* bit[0-0] : 1.д1'b1����ErrVld�Ĵ���������ж�ʹ�ܣ�ͬʱҲ����жϣ���
                                                   2.д1'b1�����ܴ洢��ErrClr�Ĵ����У����üĴ�������������1'b0�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_UNION
 �ṹ˵��  : DMABUS_ERRLOG0 �Ĵ����ṹ���塣��ַƫ����:0x1C14����ֵ:0x80000000�����:32
 �Ĵ���˵��: Error log0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lock     : 1;  /* bit[0]    : ֻ��Transaction�Ƿ�ΪLock����������Ч�� */
        unsigned int  opc      : 4;  /* bit[1-4]  : Transaction�������ͣ�
                                                    0-->RD��INCR�Ķ�������
                                                    1-->RDW��WRAP�Ķ�������
                                                    2-->RDL��Exclusive ��������
                                                    3-->RDX��Lock read��
                                                    4-->WR��INCRд������
                                                    5-->WRW��WRAPд������
                                                    6-->WRC��Exclusiveд������
                                                    8-->PRE��FIXED BURST��
                                                    9-->URG��urgency packet��Error Probe�����⵽����packet��
                                                    ����-->Reserveed���Ƿ������� */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : ���� */
        unsigned int  errcode  : 3;  /* bit[8-10] : �������ͣ�
                                                    0-->������slave����Error Response��
                                                    1-->master���������ߵ�Reserve��ַ�ռ䣻
                                                    2-->master������slave��֧�ֵ�Burst���ͣ���ǰ���߲���������ֳ�������
                                                    3-->master�����˵�������
                                                    4-->����Ȩ�ޱ���
                                                    5-->master����ʱ���յ�Firewall��Hide Error Response��
                                                    6-->������slave TimeOut��������Error Response��
                                                    7-->none�� */
        unsigned int  reserved_1: 5;  /* bit[11-15]: ���� */
        unsigned int  len1     : 8;  /* bit[16-23]: ��ʾ����Transaction�İ�������λΪByte */
        unsigned int  reserved_2: 7;  /* bit[24-30]: ���� */
        unsigned int  format   : 1;  /* bit[31]   : ���ڱ�ʾError log0�ĸ�ʽ��FlexNoC2.7�Ժ�汾�̶�Ϊ1'b1�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_UNION
 �ṹ˵��  : DMABUS_ERRLOG1 �Ĵ����ṹ���塣��ַƫ����:0x1C18����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog1  : 14; /* bit[0-13] : RouteId��·����Ϣ����bit��������
                                                    [13:10]-->Initiator Flow ID�����ڱ�ʾ������ʵ�master��
                                                    [9:7]-->target Flow ID�����ڱ�ʾ�����ʵ�slave��
                                                    [6:0]-->Seq ID��Transaction��ǣ� */
        unsigned int  reserved : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_UNION
 �ṹ˵��  : DMABUS_ERRLOG3 �Ĵ����ṹ���塣��ַƫ����:0x1C20����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog3 : 32; /* bit[0-31]: ���ʵ�ֵַ */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_errlog3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_UNION
 �ṹ˵��  : DMABUS_ERRLOG5 �Ĵ����ṹ���塣��ַƫ����:0x1C28����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog5  : 5;  /* bit[0-4] : User�ź�ֵ */
        unsigned int  reserved : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_UNION
 �ṹ˵��  : DMABUS_ERRLOG7 �Ĵ����ṹ���塣��ַƫ����:0x1C30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog7  : 1;  /* bit[0]   : ��ȫ�ź�ֵ */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_errlog7_END     (0)




/****************************************************************************
                     (6/9) DBGBUS
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_UNION
 �ṹ˵��  : USB3_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x28DA6D04�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : USB3_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_UNION
 �ṹ˵��  : USB3_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_UNION
 �ṹ˵��  : USB3_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_UNION
 �ṹ˵��  : USB3_QOS_BANDWIDTH �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x0000042A�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 12; /* bit[0-11] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_bandwidth_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_UNION
 �ṹ˵��  : USB3_QOS_SATURATION �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x000003E8�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  saturation : 10; /* bit[0-9]  : Defines the size of the bandwidth counter, that is, the measurement window, in 16-byte units. In other words, the desired number of bytes divided by 16. */
        unsigned int  reserved   : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_saturation_START  (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_UNION
 �ṹ˵��  : USB3_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_UNION
 �ṹ˵��  : SEC_P_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x5F143B04�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : SEC_P_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_UNION
 �ṹ˵��  : SEC_P_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_UNION
 �ṹ˵��  : SEC_P_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_UNION
 �ṹ˵��  : SEC_P_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_UNION
 �ṹ˵��  : SEC_S_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x468FF304�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : SEC_S_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_UNION
 �ṹ˵��  : SEC_S_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_UNION
 �ṹ˵��  : SEC_S_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_UNION
 �ṹ˵��  : SEC_S_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_UNION
 �ṹ˵��  : SOCP_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0180����ֵ:0xB0A55F04�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : SOCP_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0184����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_UNION
 �ṹ˵��  : SOCP_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0188����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_UNION
 �ṹ˵��  : SOCP_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x018C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_UNION
 �ṹ˵��  : SOCP_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0198����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_UNION
 �ṹ˵��  : CSSYS_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0xE7BD1904�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : CSSYS_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0204����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_UNION
 �ṹ˵��  : CSSYS_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0208����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_UNION
 �ṹ˵��  : CSSYS_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x020C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_UNION
 �ṹ˵��  : CSSYS_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0218����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_UNION
 �ṹ˵��  : PERF_STAT_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0280����ֵ:0xA9AEE404�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : PERF_STAT_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0284����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_UNION
 �ṹ˵��  : PERF_STAT_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0288����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_UNION
 �ṹ˵��  : PERF_STAT_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x028C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_UNION
 �ṹ˵��  : PERF_STAT_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0298����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_UNION
 �ṹ˵��  : DBG2SYS_ADAPTER_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0x223E2901�����:32
 �Ĵ���˵��: adapter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_UNION
 �ṹ˵��  : DBG2SYS_ADAPTER_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_UNION
 �ṹ˵��  : DBG2SYS_ADAPTERRATE �Ĵ����ṹ���塣��ַƫ����:0x1008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_UNION
 �ṹ˵��  : DBG2SYS_ADAP_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x100C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter bypass�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_UNION
 �ṹ˵��  : DBGBUS_ERR_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1C00����ֵ:0x08DA560D�����:32
 �Ĵ���˵��: DBGBUS Err probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: error probe����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_UNION
 �ṹ˵��  : DBGBUS_ERR_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1C04����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_UNION
 �ṹ˵��  : DBGBUS_FAULTEN �Ĵ����ṹ���塣��ַƫ����:0x1C08����ֵ:0x00000000�����:32
 �Ĵ���˵��: DBGBUS Err probeʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  faulten  : 1;  /* bit[0]   : ʹ������жϣ�����Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_UNION
 �ṹ˵��  : DBGBUS_ERRVLD �Ĵ����ṹ���塣��ַƫ����:0x1C0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log��Чָʾ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errvld   : 1;  /* bit[0]   : Error log��Чָʾ״̬�Ĵ���������Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_UNION
 �ṹ˵��  : DBGBUS_ERRCLR �Ĵ����ṹ���塣��ַƫ����:0x1C10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errclr   : 1;  /* bit[0-0] : 1.д1'b1����ErrVld�Ĵ���������ж�ʹ�ܣ�ͬʱҲ����жϣ���
                                                   2.д1'b1�����ܴ洢��ErrClr�Ĵ����У����üĴ�������������1'b0�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_UNION
 �ṹ˵��  : DBGBUS_ERRLOG0 �Ĵ����ṹ���塣��ַƫ����:0x1C14����ֵ:0x80000000�����:32
 �Ĵ���˵��: Error log0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lock     : 1;  /* bit[0]    : ֻ��Transaction�Ƿ�ΪLock����������Ч�� */
        unsigned int  opc      : 4;  /* bit[1-4]  : Transaction�������ͣ�
                                                    0-->RD��INCR�Ķ�������
                                                    1-->RDW��WRAP�Ķ�������
                                                    2-->RDL��Exclusive ��������
                                                    3-->RDX��Lock read��
                                                    4-->WR��INCRд������
                                                    5-->WRW��WRAPд������
                                                    6-->WRC��Exclusiveд������
                                                    8-->PRE��FIXED BURST��
                                                    9-->URG��urgency packet��Error Probe�����⵽����packet��
                                                    ����-->Reserveed���Ƿ������� */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : ���� */
        unsigned int  errcode  : 3;  /* bit[8-10] : �������ͣ�
                                                    0-->������slave����Error Response��
                                                    1-->master���������ߵ�Reserve��ַ�ռ䣻
                                                    2-->master������slave��֧�ֵ�Burst���ͣ���ǰ���߲���������ֳ�������
                                                    3-->master�����˵�������
                                                    4-->����Ȩ�ޱ���
                                                    5-->master����ʱ���յ�Firewall��Hide Error Response��
                                                    6-->������slave TimeOut��������Error Response��
                                                    7-->none�� */
        unsigned int  reserved_1: 5;  /* bit[11-15]: ���� */
        unsigned int  len1     : 8;  /* bit[16-23]: ��ʾ����Transaction�İ�������λΪByte */
        unsigned int  reserved_2: 7;  /* bit[24-30]: ���� */
        unsigned int  format   : 1;  /* bit[31]   : ���ڱ�ʾError log0�ĸ�ʽ��FlexNoC2.7�Ժ�汾�̶�Ϊ1'b1�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_UNION
 �ṹ˵��  : DBGBUS_ERRLOG1 �Ĵ����ṹ���塣��ַƫ����:0x1C18����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog1  : 14; /* bit[0-13] : RouteId��·����Ϣ����bit��������
                                                    [13:10]-->Initiator Flow ID�����ڱ�ʾ������ʵ�master��
                                                    [9:7]-->target Flow ID�����ڱ�ʾ�����ʵ�slave��
                                                    [6:0]-->Seq ID��Transaction��ǣ� */
        unsigned int  reserved : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_UNION
 �ṹ˵��  : DBGBUS_ERRLOG3 �Ĵ����ṹ���塣��ַƫ����:0x1C20����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog3 : 32; /* bit[0-31]: ���ʵ�ֵַ */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_errlog3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_UNION
 �ṹ˵��  : DBGBUS_ERRLOG5 �Ĵ����ṹ���塣��ַƫ����:0x1C28����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog5  : 5;  /* bit[0-4] : User�ź�ֵ */
        unsigned int  reserved : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_UNION
 �ṹ˵��  : DBGBUS_ERRLOG7 �Ĵ����ṹ���塣��ַƫ����:0x1C30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog7  : 1;  /* bit[0]   : ��ȫ�ź�ֵ */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_errlog7_END     (0)




/****************************************************************************
                     (7/9) MMC1BUS
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_UNION
 �ṹ˵��  : MMC1BUS_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x6A610C04�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : MMC1BUS_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_UNION
 �ṹ˵��  : MMC1BUS_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_UNION
 �ṹ˵��  : MMC1BUS_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_UNION
 �ṹ˵��  : MMC1BUS_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_UNION
 �ṹ˵��  : MMC1BUS_ERR_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1C00����ֵ:0x08DA560D�����:32
 �Ĵ���˵��: MMC1BUS Err probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: error probe����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_UNION
 �ṹ˵��  : MMC1BUS_ERR_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1C04����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_UNION
 �ṹ˵��  : MMC1BUS_FAULTEN �Ĵ����ṹ���塣��ַƫ����:0x1C08����ֵ:0x00000000�����:32
 �Ĵ���˵��: MMC1BUS Err probeʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  faulten  : 1;  /* bit[0]   : ʹ������жϣ�����Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_UNION
 �ṹ˵��  : MMC1BUS_ERRVLD �Ĵ����ṹ���塣��ַƫ����:0x1C0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log��Чָʾ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errvld   : 1;  /* bit[0]   : Error log��Чָʾ״̬�Ĵ���������Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_UNION
 �ṹ˵��  : MMC1BUS_ERRCLR �Ĵ����ṹ���塣��ַƫ����:0x1C10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errclr   : 1;  /* bit[0-0] : 1.д1'b1����ErrVld�Ĵ���������ж�ʹ�ܣ�ͬʱҲ����жϣ���
                                                   2.д1'b1�����ܴ洢��ErrClr�Ĵ����У����üĴ�������������1'b0�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_UNION
 �ṹ˵��  : MMC1BUS_ERRLOG0 �Ĵ����ṹ���塣��ַƫ����:0x1C14����ֵ:0x80000000�����:32
 �Ĵ���˵��: Error log0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lock     : 1;  /* bit[0]    : ֻ��Transaction�Ƿ�ΪLock����������Ч�� */
        unsigned int  opc      : 4;  /* bit[1-4]  : Transaction�������ͣ�
                                                    0-->RD��INCR�Ķ�������
                                                    1-->RDW��WRAP�Ķ�������
                                                    2-->RDL��Exclusive ��������
                                                    3-->RDX��Lock read��
                                                    4-->WR��INCRд������
                                                    5-->WRW��WRAPд������
                                                    6-->WRC��Exclusiveд������
                                                    8-->PRE��FIXED BURST��
                                                    9-->URG��urgency packet��Error Probe�����⵽����packet��
                                                    ����-->Reserveed���Ƿ������� */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : ���� */
        unsigned int  errcode  : 3;  /* bit[8-10] : �������ͣ�
                                                    0-->������slave����Error Response��
                                                    1-->master���������ߵ�Reserve��ַ�ռ䣻
                                                    2-->master������slave��֧�ֵ�Burst���ͣ���ǰ���߲���������ֳ�������
                                                    3-->master�����˵�������
                                                    4-->����Ȩ�ޱ���
                                                    5-->master����ʱ���յ�Firewall��Hide Error Response��
                                                    6-->������slave TimeOut��������Error Response��
                                                    7-->none�� */
        unsigned int  reserved_1: 5;  /* bit[11-15]: ���� */
        unsigned int  len1     : 8;  /* bit[16-23]: ��ʾ����Transaction�İ�������λΪByte */
        unsigned int  reserved_2: 7;  /* bit[24-30]: ���� */
        unsigned int  format   : 1;  /* bit[31]   : ���ڱ�ʾError log0�ĸ�ʽ��FlexNoC2.7�Ժ�汾�̶�Ϊ1'b1�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_UNION
 �ṹ˵��  : MMC1BUS_ERRLOG1 �Ĵ����ṹ���塣��ַƫ����:0x1C18����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog1  : 14; /* bit[0-13] : RouteId��·����Ϣ����bit��������
                                                    [13:10]-->Initiator Flow ID�����ڱ�ʾ������ʵ�master��
                                                    [9:7]-->target Flow ID�����ڱ�ʾ�����ʵ�slave��
                                                    [6:0]-->Seq ID��Transaction��ǣ� */
        unsigned int  reserved : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_UNION
 �ṹ˵��  : MMC1BUS_ERRLOG3 �Ĵ����ṹ���塣��ַƫ����:0x1C20����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog3 : 32; /* bit[0-31]: ���ʵ�ֵַ */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_errlog3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_UNION
 �ṹ˵��  : MMC1BUS_ERRLOG5 �Ĵ����ṹ���塣��ַƫ����:0x1C28����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog5  : 5;  /* bit[0-4] : User�ź�ֵ */
        unsigned int  reserved : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_UNION
 �ṹ˵��  : MMC1BUS_ERRLOG7 �Ĵ����ṹ���塣��ַƫ����:0x1C30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog7  : 1;  /* bit[0]   : ��ȫ�ź�ֵ */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_errlog7_END     (0)




/****************************************************************************
                     (8/9) MMC0BUS 
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_UNION
 �ṹ˵��  : EMMC0_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0xD7836304�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : EMMC0_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_UNION
 �ṹ˵��  : EMMC0_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_UNION
 �ṹ˵��  : EMMC0_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_UNION
 �ṹ˵��  : EMMC0_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_UNION
 �ṹ˵��  : EMMC1_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x7CA53404�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : EMMC1_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_UNION
 �ṹ˵��  : EMMC1_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_UNION
 �ṹ˵��  : EMMC1_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_UNION
 �ṹ˵��  : EMMC1_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_UNION
 �ṹ˵��  : MMC0BUS_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0xA11D0C04�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : MMC0BUS_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_UNION
 �ṹ˵��  : MMC0BUS_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_UNION
 �ṹ˵��  : MMC0BUS_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_UNION
 �ṹ˵��  : MMC0BUS_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_UNION
 �ṹ˵��  : MMC0BUS_ADAPTER_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0xF33B3F01�����:32
 �Ĵ���˵��: adapter��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_UNION
 �ṹ˵��  : MMC0BUS_ADAPTER_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_UNION
 �ṹ˵��  : MMC0BUS_ADAPTERRATE �Ĵ����ṹ���塣��ַƫ����:0x1008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_UNION
 �ṹ˵��  : MMC0BUS_ADAP_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x100C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rate Adapter bypass�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_UNION
 �ṹ˵��  : MMC0BUS_ERR_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1C00����ֵ:0x08DA560D�����:32
 �Ĵ���˵��: MMC0BUS Err probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: error probe����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_UNION
 �ṹ˵��  : MMC0BUS_ERR_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1C04����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_UNION
 �ṹ˵��  : MMC0BUS_FAULTEN �Ĵ����ṹ���塣��ַƫ����:0x1C08����ֵ:0x00000000�����:32
 �Ĵ���˵��: MMC0BUS Err probeʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  faulten  : 1;  /* bit[0]   : ʹ������жϣ�����Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_UNION
 �ṹ˵��  : MMC0BUS_ERRVLD �Ĵ����ṹ���塣��ַƫ����:0x1C0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log��Чָʾ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errvld   : 1;  /* bit[0]   : Error log��Чָʾ״̬�Ĵ���������Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_UNION
 �ṹ˵��  : MMC0BUS_ERRCLR �Ĵ����ṹ���塣��ַƫ����:0x1C10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errclr   : 1;  /* bit[0-0] : 1.д1'b1����ErrVld�Ĵ���������ж�ʹ�ܣ�ͬʱҲ����жϣ���
                                                   2.д1'b1�����ܴ洢��ErrClr�Ĵ����У����üĴ�������������1'b0�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_UNION
 �ṹ˵��  : MMC0BUS_ERRLOG0 �Ĵ����ṹ���塣��ַƫ����:0x1C14����ֵ:0x80000000�����:32
 �Ĵ���˵��: Error log0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lock     : 1;  /* bit[0]    : ֻ��Transaction�Ƿ�ΪLock����������Ч�� */
        unsigned int  opc      : 4;  /* bit[1-4]  : Transaction�������ͣ�
                                                    0-->RD��INCR�Ķ�������
                                                    1-->RDW��WRAP�Ķ�������
                                                    2-->RDL��Exclusive ��������
                                                    3-->RDX��Lock read��
                                                    4-->WR��INCRд������
                                                    5-->WRW��WRAPд������
                                                    6-->WRC��Exclusiveд������
                                                    8-->PRE��FIXED BURST��
                                                    9-->URG��urgency packet��Error Probe�����⵽����packet��
                                                    ����-->Reserveed���Ƿ������� */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : ���� */
        unsigned int  errcode  : 3;  /* bit[8-10] : �������ͣ�
                                                    0-->������slave����Error Response��
                                                    1-->master���������ߵ�Reserve��ַ�ռ䣻
                                                    2-->master������slave��֧�ֵ�Burst���ͣ���ǰ���߲���������ֳ�������
                                                    3-->master�����˵�������
                                                    4-->����Ȩ�ޱ���
                                                    5-->master����ʱ���յ�Firewall��Hide Error Response��
                                                    6-->������slave TimeOut��������Error Response��
                                                    7-->none�� */
        unsigned int  reserved_1: 5;  /* bit[11-15]: ���� */
        unsigned int  len1     : 8;  /* bit[16-23]: ��ʾ����Transaction�İ�������λΪByte */
        unsigned int  reserved_2: 7;  /* bit[24-30]: ���� */
        unsigned int  format   : 1;  /* bit[31]   : ���ڱ�ʾError log0�ĸ�ʽ��FlexNoC2.7�Ժ�汾�̶�Ϊ1'b1�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_UNION
 �ṹ˵��  : MMC0BUS_ERRLOG1 �Ĵ����ṹ���塣��ַƫ����:0x1C18����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog1  : 14; /* bit[0-13] : RouteId��·����Ϣ����bit��������
                                                    [13:10]-->Initiator Flow ID�����ڱ�ʾ������ʵ�master��
                                                    [9:7]-->target Flow ID�����ڱ�ʾ�����ʵ�slave��
                                                    [6:0]-->Seq ID��Transaction��ǣ� */
        unsigned int  reserved : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_UNION
 �ṹ˵��  : MMC0BUS_ERRLOG3 �Ĵ����ṹ���塣��ַƫ����:0x1C20����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog3 : 32; /* bit[0-31]: ���ʵ�ֵַ */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_errlog3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_UNION
 �ṹ˵��  : MMC0BUS_ERRLOG5 �Ĵ����ṹ���塣��ַƫ����:0x1C28����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog5  : 5;  /* bit[0-4] : User�ź�ֵ */
        unsigned int  reserved : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_UNION
 �ṹ˵��  : MMC0BUS_ERRLOG7 �Ĵ����ṹ���塣��ַƫ����:0x1C30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog7  : 1;  /* bit[0]   : ��ȫ�ź�ֵ */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_errlog7_END     (0)




/****************************************************************************
                     (9/9) IVP32BUS
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_UNION
 �ṹ˵��  : IVP32_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0xD6AAAC04�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : IVP32_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x012D5300�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_UNION
 �ṹ˵��  : IVP32_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ���� */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_UNION
 �ṹ˵��  : IVP32_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_UNION
 �ṹ˵��  : IVP32_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_UNION
 �ṹ˵��  : IVP32_ERR_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1C00����ֵ:0x08DA560D�����:32
 �Ĵ���˵��: IVP32 Err probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: IVP32��error probe����ID�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_UNION
 �ṹ˵��  : IVP32_ERR_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1C04����ֵ:0x012D5300�����:32
 �Ĵ���˵��: ���ߴ���汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: ��8bit�Զ��壬��24bit��NOC������HUSHֵ�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_UNION
 �ṹ˵��  : IVP32_FAULTEN �Ĵ����ṹ���塣��ַƫ����:0x1C08����ֵ:0x00000000�����:32
 �Ĵ���˵��: IVP32 Err probeʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  faulten  : 1;  /* bit[0]   : ʹ������жϣ�����Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_faulten_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_UNION
 �ṹ˵��  : IVP32_ERRVLD �Ĵ����ṹ���塣��ַƫ����:0x1C0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log��Чָʾ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errvld   : 1;  /* bit[0]   : Error log��Чָʾ״̬�Ĵ���������Ч�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_errvld_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_UNION
 �ṹ˵��  : IVP32_ERRCLR �Ĵ����ṹ���塣��ַƫ����:0x1C10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errclr   : 1;  /* bit[0-0] : 1.д1'b1����ErrVld�Ĵ���������ж�ʹ�ܣ�ͬʱҲ����жϣ���
                                                   2.д1'b1�����ܴ洢��ErrClr�Ĵ����У����üĴ�������������1'b0�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_errclr_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_UNION
 �ṹ˵��  : IVP32_ERRLOG0 �Ĵ����ṹ���塣��ַƫ����:0x1C14����ֵ:0x80000000�����:32
 �Ĵ���˵��: Error log0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lock     : 1;  /* bit[0]    : ֻ��Transaction�Ƿ�ΪLock����������Ч�� */
        unsigned int  opc      : 4;  /* bit[1-4]  : Transaction�������ͣ�
                                                    0-->RD��INCR�Ķ�������
                                                    1-->RDW��WRAP�Ķ�������
                                                    2-->RDL��Exclusive ��������
                                                    3-->RDX��Lock read��
                                                    4-->WR��INCRд������
                                                    5-->WRW��WRAPд������
                                                    6-->WRC��Exclusiveд������
                                                    8-->PRE��FIXED BURST��
                                                    9-->URG��urgency packet��Error Probe�����⵽����packet��
                                                    ����-->Reserveed���Ƿ������� */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : ���� */
        unsigned int  errcode  : 3;  /* bit[8-10] : �������ͣ�
                                                    0-->������slave����Error Response��
                                                    1-->master���������ߵ�Reserve��ַ�ռ䣻
                                                    2-->master������slave��֧�ֵ�Burst���ͣ���ǰ���߲���������ֳ�������
                                                    3-->master�����˵�������
                                                    4-->����Ȩ�ޱ���
                                                    5-->master����ʱ���յ�Firewall��Hide Error Response��
                                                    6-->������slave TimeOut��������Error Response��
                                                    7-->none�� */
        unsigned int  reserved_1: 5;  /* bit[11-15]: ���� */
        unsigned int  len1     : 8;  /* bit[16-23]: ��ʾ����Transaction�İ�������λΪByte */
        unsigned int  reserved_2: 7;  /* bit[24-30]: ���� */
        unsigned int  format   : 1;  /* bit[31]   : ���ڱ�ʾError log0�ĸ�ʽ��FlexNoC2.7�Ժ�汾�̶�Ϊ1'b1�� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_format_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_UNION
 �ṹ˵��  : IVP32_ERRLOG1 �Ĵ����ṹ���塣��ַƫ����:0x1C18����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog1  : 22; /* bit[0-21] : RouteId��·����Ϣ����bit��������
                                                    [21:17]-->Initiator Flow ID�����ڱ�ʾ������ʵ�master��
                                                    [16:12]-->target Flow ID�����ڱ�ʾ�����ʵ�slave��
                                                    [11:9]-->Target NIU SubRange��
                                                    [8:0]-->Seq ID��Transaction��ǣ� */
        unsigned int  reserved : 10; /* bit[22-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_errlog1_END     (21)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_UNION
 �ṹ˵��  : IVP32_ERRLOG3 �Ĵ����ṹ���塣��ַƫ����:0x1C20����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog3  : 31; /* bit[0-30] : ���ʵ�ֵַ */
        unsigned int  reserved : 1;  /* bit[31-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_errlog3_START   (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_errlog3_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_UNION
 �ṹ˵��  : IVP32_ERRLOG5 �Ĵ����ṹ���塣��ַƫ����:0x1C28����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog5  : 17; /* bit[0-16] : User�ź�ֵ */
        unsigned int  reserved : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_errlog5_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_UNION
 �ṹ˵��  : IVP32_ERRLOG7 �Ĵ����ṹ���塣��ַƫ����:0x1C30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error log7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog7  : 1;  /* bit[0]   : ��ȫ�ź�ֵ */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_errlog7_END     (0)






/*****************************************************************************
  8 OTHERS����
*****************************************************************************/



/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_cfg_sys_noc_bus_interface.h */
