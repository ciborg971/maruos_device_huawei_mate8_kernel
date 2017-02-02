/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_vcodec_bus_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:23:23
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_VCODEC_BUS.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_VCODEC_BUS_INTERFACE_H__
#define __SOC_VCODEC_BUS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/3) NOC_PERI_VCODEC
 ****************************************************************************/
/* �Ĵ���˵����adapter��ID
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))

/* �Ĵ���˵����Rate Adapter���üĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_ADAPTERRATE_UNION */
#define SOC_VCODEC_BUS_VENC_ADAPTERRATE_ADDR(base)    ((base) + (0x1008))

/* �Ĵ���˵����Rate Adapter bypass�Ĵ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_ADAP_BYPASS_UNION */
#define SOC_VCODEC_BUS_VENC_ADAP_BYPASS_ADDR(base)    ((base) + (0x100C))

/* �Ĵ���˵����adapter��ID
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1080))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1084))

/* �Ĵ���˵����Rate Adapter���üĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VDEC_ADAPTERRATE_UNION */
#define SOC_VCODEC_BUS_VDEC_ADAPTERRATE_ADDR(base)    ((base) + (0x1088))

/* �Ĵ���˵����Rate Adapter bypass�Ĵ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_UNION */
#define SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_ADDR(base)    ((base) + (0x108C))

/* �Ĵ���˵����VCODEC_BUS Err probe��ID
   λ����UNION�ṹ:  SOC_VCODEC_BUS_ERR_ID_COREID_UNION */
#define SOC_VCODEC_BUS_ERR_ID_COREID_ADDR(base)       ((base) + (0x1C00))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_ID_REVISIONID_ADDR(base)       ((base) + (0x1C04))

/* �Ĵ���˵����VCODEC_BUS Err probeʹ��
   λ����UNION�ṹ:  SOC_VCODEC_BUS_FAULTEN_UNION */
#define SOC_VCODEC_BUS_FAULTEN_ADDR(base)             ((base) + (0x1C08))

/* �Ĵ���˵����Error log��Чָʾ�Ĵ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_ERRVLD_UNION */
#define SOC_VCODEC_BUS_ERRVLD_ADDR(base)              ((base) + (0x1C0C))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_ERRCLR_UNION */
#define SOC_VCODEC_BUS_ERRCLR_ADDR(base)              ((base) + (0x1C10))

/* �Ĵ���˵����Error log0
   λ����UNION�ṹ:  SOC_VCODEC_BUS_ERRLOG0_UNION */
#define SOC_VCODEC_BUS_ERRLOG0_ADDR(base)             ((base) + (0x1C14))

/* �Ĵ���˵����Error log1
   λ����UNION�ṹ:  SOC_VCODEC_BUS_ERRLOG1_UNION */
#define SOC_VCODEC_BUS_ERRLOG1_ADDR(base)             ((base) + (0x1C18))

/* �Ĵ���˵����Error log3
   λ����UNION�ṹ:  SOC_VCODEC_BUS_ERRLOG3_UNION */
#define SOC_VCODEC_BUS_ERRLOG3_ADDR(base)             ((base) + (0x1C20))

/* �Ĵ���˵����Error log5
   λ����UNION�ṹ:  SOC_VCODEC_BUS_ERRLOG5_UNION */
#define SOC_VCODEC_BUS_ERRLOG5_ADDR(base)             ((base) + (0x1C28))

/* �Ĵ���˵����Error log7
   λ����UNION�ṹ:  SOC_VCODEC_BUS_ERRLOG7_UNION */
#define SOC_VCODEC_BUS_ERRLOG7_ADDR(base)             ((base) + (0x1C30))



/****************************************************************************
                     (2/3) NOC_VENC
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_QOS_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_ADDR(base)  ((base) + (0x0100))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_QOS_PRIORITY_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_ADDR(base)   ((base) + (0x0108))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_QOS_MODE_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_MODE_ADDR(base)       ((base) + (0x010C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_ADDR(base)  ((base) + (0x0110))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_QOS_SATURATION_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_SATURATION_ADDR(base) ((base) + (0x0114))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))

/* �Ĵ���˵����VENC TransactionStatFilter��ID
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x8000))

/* �Ĵ���˵��������汾
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x8004))

/* �Ĵ���˵����VENC Transaction Probe��Filter����ģʽ���üĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_F_MODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_MODE_ADDR(base)   ((base) + (0x8008))

/* �Ĵ���˵������ַ���˻���ַ
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x800C))

/* �Ĵ���˵������ַ���˻���ַ
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_ADDR(base) ((base) + (0x8010))

/* �Ĵ���˵������ַ���˴���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x8014))

/* �Ĵ���˵����VENC��Transaction Probe��Opcode��������
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_ADDR(base) ((base) + (0x8020))

/* �Ĵ���˵����VENC��Transaction Probe��User��������
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_ADDR(base) ((base) + (0x8024))

/* �Ĵ���˵����VENC��Transaction Probe��User��������Mask
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_ADDR(base) ((base) + (0x8028))

/* �Ĵ���˵����VENC��Transaction Probe�İ�ȫ��������
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x802C))

/* �Ĵ���˵����VENC��Transaction Probe�İ�ȫ��������Mask
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x8030))

/* �Ĵ���˵����VENC TransactionStatProfilter��ID
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x8080))

/* �Ĵ���˵��������汾
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x8084))

/* �Ĵ���˵����transaction Probe��counterʹ������
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_P_EN_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_EN_ADDR(base)     ((base) + (0x8088))

/* �Ĵ���˵����VENC Transaction Probe�Ĺ���ģʽ����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_P_MODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_MODE_ADDR(base)   ((base) + (0x808C))

/* �Ĵ���˵����ͳ�Ƽ��������״̬
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x80EC))

/* �Ĵ���˵����ͳ�Ƽ��������״̬����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x80F0))

/* �Ĵ���˵����outstandingͳ�Ƽ�������ģʽ����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x80F4))

/* �Ĵ���˵����latencyͳ��ϵ������
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x80F8))

/* �Ĵ���˵����VENC Transaction probe��ID
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x8400))

/* �Ĵ���˵�������ߴ���汾�Ĵ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x8404))

/* �Ĵ���˵����Transaction Probeȫ�ֿ��ƼĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x8408))

/* �Ĵ���˵����Packet Probeʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x840C))

/* �Ĵ���˵����ͳ���������üĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x8424))

/* �Ĵ���˵�����ֶ�����ͳ�Ƽ�ʱ��ʼʹ��
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_ADDR(base) ((base) + (0x8428))

/* �Ĵ���˵����ͳ�Ƽ�����С�澯��ֵ
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x842C))

/* �Ĵ���˵����ͳ�Ƽ��������澯��ֵ
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x8430))

/* �Ĵ���˵�����澯״̬�Ĵ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x8434))

/* �Ĵ���˵�����澯״̬����Ĵ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x8438))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x8538))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x853C))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x8540))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x854C))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x8550))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x8554))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x8560))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x8564))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x8568))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x8574))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x8578))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x857C))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x8588))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x858C))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x8590))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x859C))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x85A0))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x85A4))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x85B0))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x85B4))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x85B8))

/* �Ĵ���˵����Counter��ͳ�����Ϳ��ƼĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x85C4))

/* �Ĵ���˵�����澯�жϲ������üĴ���
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x85C8))

/* �Ĵ���˵����ͳ�Ƽ�������ͳ��ֵ
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x85CC))



/****************************************************************************
                     (3/3) NOC_VDEC
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_ADDR(base)  ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_ADDR(base)   ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VDEC_QOS_MODE_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_MODE_ADDR(base)       ((base) + (0x000C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_ADDR(base)  ((base) + (0x0010))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VDEC_QOS_SATURATION_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_SATURATION_ADDR(base) ((base) + (0x0014))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))





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
                     (1/3) NOC_PERI_VCODEC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_UNION
 �ṹ˵��  : VENC_ADAPTER_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0xA247F101�����:32
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
} SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_UNION
 �ṹ˵��  : VENC_ADAPTER_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1004����ֵ:0x012D5300�����:32
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
} SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_ADAPTERRATE_UNION
 �ṹ˵��  : VENC_ADAPTERRATE �Ĵ����ṹ���塣��ַƫ����:0x1008����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_ADAPTERRATE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_ADAPTERRATE_rate_START      (0)
#define SOC_VCODEC_BUS_VENC_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_ADAP_BYPASS_UNION
 �ṹ˵��  : VENC_ADAP_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x100C����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_ADAP_BYPASS_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_ADAP_BYPASS_bypass_START    (0)
#define SOC_VCODEC_BUS_VENC_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_UNION
 �ṹ˵��  : VDEC_ADAPTER_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1080����ֵ:0x6539FD01�����:32
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
} SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_UNION
 �ṹ˵��  : VDEC_ADAPTER_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1084����ֵ:0x012D5300�����:32
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
} SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VDEC_ADAPTERRATE_UNION
 �ṹ˵��  : VDEC_ADAPTERRATE �Ĵ����ṹ���塣��ַƫ����:0x1088����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VDEC_ADAPTERRATE_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_ADAPTERRATE_rate_START      (0)
#define SOC_VCODEC_BUS_VDEC_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_UNION
 �ṹ˵��  : VDEC_ADAP_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x108C����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_bypass_START    (0)
#define SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_ERR_ID_COREID_UNION
 �ṹ˵��  : ERR_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x1C00����ֵ:0xA67A1B0D�����:32
 �Ĵ���˵��: VCODEC_BUS Err probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: SYS_BUS��error probe����ID�� */
    } reg;
} SOC_VCODEC_BUS_ERR_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_VCODEC_BUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_ID_REVISIONID_UNION
 �ṹ˵��  : ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x1C04����ֵ:0x012D5300�����:32
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
} SOC_VCODEC_BUS_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VCODEC_BUS_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_FAULTEN_UNION
 �ṹ˵��  : FAULTEN �Ĵ����ṹ���塣��ַƫ����:0x1C08����ֵ:0x00000000�����:32
 �Ĵ���˵��: VCODEC_BUS Err probeʹ��
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
} SOC_VCODEC_BUS_FAULTEN_UNION;
#endif
#define SOC_VCODEC_BUS_FAULTEN_faulten_START   (0)
#define SOC_VCODEC_BUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_ERRVLD_UNION
 �ṹ˵��  : ERRVLD �Ĵ����ṹ���塣��ַƫ����:0x1C0C����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_ERRVLD_UNION;
#endif
#define SOC_VCODEC_BUS_ERRVLD_errvld_START    (0)
#define SOC_VCODEC_BUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_ERRCLR_UNION
 �ṹ˵��  : ERRCLR �Ĵ����ṹ���塣��ַƫ����:0x1C10����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_ERRCLR_UNION;
#endif
#define SOC_VCODEC_BUS_ERRCLR_errclr_START    (0)
#define SOC_VCODEC_BUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_ERRLOG0_UNION
 �ṹ˵��  : ERRLOG0 �Ĵ����ṹ���塣��ַƫ����:0x1C14����ֵ:0x80000000�����:32
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
} SOC_VCODEC_BUS_ERRLOG0_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG0_lock_START      (0)
#define SOC_VCODEC_BUS_ERRLOG0_lock_END        (0)
#define SOC_VCODEC_BUS_ERRLOG0_opc_START       (1)
#define SOC_VCODEC_BUS_ERRLOG0_opc_END         (4)
#define SOC_VCODEC_BUS_ERRLOG0_errcode_START   (8)
#define SOC_VCODEC_BUS_ERRLOG0_errcode_END     (10)
#define SOC_VCODEC_BUS_ERRLOG0_len1_START      (16)
#define SOC_VCODEC_BUS_ERRLOG0_len1_END        (23)
#define SOC_VCODEC_BUS_ERRLOG0_format_START    (31)
#define SOC_VCODEC_BUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_ERRLOG1_UNION
 �ṹ˵��  : ERRLOG1 �Ĵ����ṹ���塣��ַƫ����:0x1C18����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_ERRLOG1_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG1_errlog1_START   (0)
#define SOC_VCODEC_BUS_ERRLOG1_errlog1_END     (21)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_ERRLOG3_UNION
 �ṹ˵��  : ERRLOG3 �Ĵ����ṹ���塣��ַƫ����:0x1C20����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_ERRLOG3_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG3_errlog3_START   (0)
#define SOC_VCODEC_BUS_ERRLOG3_errlog3_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_ERRLOG5_UNION
 �ṹ˵��  : ERRLOG5 �Ĵ����ṹ���塣��ַƫ����:0x1C28����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_ERRLOG5_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG5_errlog5_START   (0)
#define SOC_VCODEC_BUS_ERRLOG5_errlog5_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_ERRLOG7_UNION
 �ṹ˵��  : ERRLOG7 �Ĵ����ṹ���塣��ַƫ����:0x1C30����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_ERRLOG7_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG7_errlog7_START   (0)
#define SOC_VCODEC_BUS_ERRLOG7_errlog7_END     (0)




/****************************************************************************
                     (2/3) NOC_VENC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_QOS_ID_COREID_UNION
 �ṹ˵��  : VENC_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x3CB8C104�����:32
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
} SOC_VCODEC_BUS_VENC_QOS_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : VENC_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x012D5300�����:32
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
} SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_QOS_PRIORITY_UNION
 �ṹ˵��  : VENC_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x80000003�����:32
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
} SOC_VCODEC_BUS_VENC_QOS_PRIORITY_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_p0_START        (0)
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_p0_END          (1)
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_p1_START        (8)
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_QOS_MODE_UNION
 �ṹ˵��  : VENC_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000003�����:32
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
} SOC_VCODEC_BUS_VENC_QOS_MODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_MODE_mode_START      (0)
#define SOC_VCODEC_BUS_VENC_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_UNION
 �ṹ˵��  : VENC_QOS_BANDWIDTH �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000640�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 13; /* bit[0-12] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_bandwidth_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_QOS_SATURATION_UNION
 �ṹ˵��  : VENC_QOS_SATURATION �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x000003E8�����:32
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
} SOC_VCODEC_BUS_VENC_QOS_SATURATION_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_SATURATION_saturation_START  (0)
#define SOC_VCODEC_BUS_VENC_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_UNION
 �ṹ˵��  : VENC_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_UNION
 �ṹ˵��  : VENC_TRANS_F_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x8000����ֵ:0xBFA61A09�����:32
 �Ĵ���˵��: VENC TransactionStatFilter��ID
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
} SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_UNION
 �ṹ˵��  : VENC_TRANS_F_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x8004����ֵ:0x012D5300�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_F_MODE_UNION
 �ṹ˵��  : VENC_TRANS_F_MODE �Ĵ����ṹ���塣��ַƫ����:0x8008����ֵ:0x00000000�����:32
 �Ĵ���˵��: VENC Transaction Probe��Filter����ģʽ���üĴ���
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
} SOC_VCODEC_BUS_VENC_TRANS_F_MODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_MODE_mode_START      (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_UNION
 �ṹ˵��  : VENC_TRANS_F_ADDRBASE_LOW �Ĵ����ṹ���塣��ַƫ����:0x800C����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_UNION
 �ṹ˵��  : VENC_TRANS_F_ADDRBASE_HIGH �Ĵ����ṹ���塣��ַƫ����:0x8010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ַ���˻���ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_high : 2;  /* bit[0-1] : ��ַ���������Ļ���ַ�� */
        unsigned int  reserved      : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_addrbase_high_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_addrbase_high_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_UNION
 �ṹ˵��  : VENC_TRANS_F_ADDRWINDOWSIZE �Ĵ����ṹ���塣��ַƫ����:0x8014����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_UNION
 �ṹ˵��  : VENC_TRANS_F_OPCODE �Ĵ����ṹ���塣��ַƫ����:0x8020����ֵ:0x00000000�����:32
 �Ĵ���˵��: VENC��Transaction Probe��Opcode��������
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
} SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_rden_START      (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_rden_END        (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_wren_START      (1)
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_UNION
 �ṹ˵��  : VENC_TRANS_F_USERBASE �Ĵ����ṹ���塣��ַƫ����:0x8024����ֵ:0x00000000�����:32
 �Ĵ���˵��: VENC��Transaction Probe��User��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 5;  /* bit[0-4] : User�źŹ������� */
        unsigned int  reserved : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_userbase_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_UNION
 �ṹ˵��  : VENC_TRANS_F_USERMASK �Ĵ����ṹ���塣��ַƫ����:0x8028����ֵ:0x00000000�����:32
 �Ĵ���˵��: VENC��Transaction Probe��User��������Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 5;  /* bit[0-4] : ��UserBase����Mask��ѡ��UserBase�е����⼸bit User�ź���Ϊ����������
                                                   ����������packet.User & UserMask = UserBase & UserMask�� */
        unsigned int  reserved : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_usermask_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_UNION
 �ṹ˵��  : VENC_TRANS_F_SECURITYBASE �Ĵ����ṹ���塣��ַƫ����:0x802C����ֵ:0x00000000�����:32
 �Ĵ���˵��: VENC��Transaction Probe�İ�ȫ��������
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
} SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_UNION
 �ṹ˵��  : VENC_TRANS_F_SECURITYMASK �Ĵ����ṹ���塣��ַƫ����:0x8030����ֵ:0x00000000�����:32
 �Ĵ���˵��: VENC��Transaction Probe�İ�ȫ��������Mask
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
} SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_UNION
 �ṹ˵��  : VENC_TRANS_P_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x8080����ֵ:0xB14C6F0A�����:32
 �Ĵ���˵��: VENC TransactionStatProfilter��ID
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
} SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_UNION
 �ṹ˵��  : VENC_TRANS_P_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x8084����ֵ:0x012D5300�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_P_EN_UNION
 �ṹ˵��  : VENC_TRANS_P_EN �Ĵ����ṹ���塣��ַƫ����:0x8088����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_P_EN_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_EN_en_START        (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_P_MODE_UNION
 �ṹ˵��  : VENC_TRANS_P_MODE �Ĵ����ṹ���塣��ַƫ����:0x808C����ֵ:0x00000000�����:32
 �Ĵ���˵��: VENC Transaction Probe�Ĺ���ģʽ����
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
} SOC_VCODEC_BUS_VENC_TRANS_P_MODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_MODE_mode_START      (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_UNION
 �ṹ˵��  : VENC_TRANS_P_OVERFLOWSTATUS �Ĵ����ṹ���塣��ַƫ����:0x80EC����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_UNION
 �ṹ˵��  : VENC_TRANS_P_OVERFLOWRESET �Ĵ����ṹ���塣��ַƫ����:0x80F0����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_UNION
 �ṹ˵��  : VENC_TRANS_P_PENDINGEVENTMODE �Ĵ����ṹ���塣��ַƫ����:0x80F4����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_UNION
 �ṹ˵��  : VENC_TRANS_P_PRESCALER �Ĵ����ṹ���塣��ַƫ����:0x80F8����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_UNION
 �ṹ˵��  : VENC_TRANS_M_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x8400����ֵ:0x4B15C906�����:32
 �Ĵ���˵��: VENC Transaction probe��ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus��Packet Probe����ID�� */
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_UNION
 �ṹ˵��  : VENC_TRANS_M_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x8404����ֵ:0x012D5300�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_UNION
 �ṹ˵��  : VENC_TRANS_M_MAINCTL �Ĵ����ṹ���塣��ַƫ����:0x8408����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_UNION
 �ṹ˵��  : VENC_TRANS_M_CFGCTL �Ĵ����ṹ���塣��ַƫ����:0x840C����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_active_START    (1)
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_UNION
 �ṹ˵��  : VENC_TRANS_M_STATPERIOD �Ĵ����ṹ���塣��ַƫ����:0x8424����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_UNION
 �ṹ˵��  : VENC_TRANS_M_STATGO �Ĵ����ṹ���塣��ַƫ����:0x8428����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_statgo_START    (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_UNION
 �ṹ˵��  : VENC_TRANS_M_STATALARMMIN �Ĵ����ṹ���塣��ַƫ����:0x842C����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_UNION
 �ṹ˵��  : VENC_TRANS_M_STATALARMMAX �Ĵ����ṹ���塣��ַƫ����:0x8430����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_UNION
 �ṹ˵��  : VENC_TRANS_M_STATALARMSTATUS �Ĵ����ṹ���塣��ַƫ����:0x8434����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_UNION
 �ṹ˵��  : VENC_TRANS_M_STATALARMCLR �Ĵ����ṹ���塣��ַƫ����:0x8438����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_0_SRC �Ĵ����ṹ���塣��ַƫ����:0x8538����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_0_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x853C����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_0_VAL �Ĵ����ṹ���塣��ַƫ����:0x8540����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_1_SRC �Ĵ����ṹ���塣��ַƫ����:0x854C����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_1_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x8550����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_1_VAL �Ĵ����ṹ���塣��ַƫ����:0x8554����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_2_SRC �Ĵ����ṹ���塣��ַƫ����:0x8560����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_2_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x8564����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_2_VAL �Ĵ����ṹ���塣��ַƫ����:0x8568����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_3_SRC �Ĵ����ṹ���塣��ַƫ����:0x8574����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_3_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x8578����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_3_VAL �Ĵ����ṹ���塣��ַƫ����:0x857C����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_4_SRC �Ĵ����ṹ���塣��ַƫ����:0x8588����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_4_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x858C����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_4_VAL �Ĵ����ṹ���塣��ַƫ����:0x8590����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_5_SRC �Ĵ����ṹ���塣��ַƫ����:0x859C����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_5_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x85A0����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_5_VAL �Ĵ����ṹ���塣��ַƫ����:0x85A4����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_6_SRC �Ĵ����ṹ���塣��ַƫ����:0x85B0����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_6_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x85B4����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_6_VAL �Ĵ����ṹ���塣��ַƫ����:0x85B8����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_7_SRC �Ĵ����ṹ���塣��ַƫ����:0x85C4����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_7_ALARMMODE �Ĵ����ṹ���塣��ַƫ����:0x85C8����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_UNION
 �ṹ˵��  : VENC_TRANS_M_COUNTERS_7_VAL �Ĵ����ṹ���塣��ַƫ����:0x85CC����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (11)




/****************************************************************************
                     (3/3) NOC_VDEC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_UNION
 �ṹ˵��  : VDEC_QOS_ID_COREID �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x5A288C04�����:32
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
} SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_UNION
 �ṹ˵��  : VDEC_QOS_ID_REVISIONID �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x012D5300�����:32
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
} SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_UNION
 �ṹ˵��  : VDEC_QOS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x08000003�����:32
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
} SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_p0_START        (0)
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_p0_END          (1)
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_p1_START        (8)
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VDEC_QOS_MODE_UNION
 �ṹ˵��  : VDEC_QOS_MODE �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000003�����:32
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
} SOC_VCODEC_BUS_VDEC_QOS_MODE_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_MODE_mode_START      (0)
#define SOC_VCODEC_BUS_VDEC_QOS_MODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_UNION
 �ṹ˵��  : VDEC_QOS_BANDWIDTH �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x000005D0�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 13; /* bit[0-12] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_bandwidth_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VDEC_QOS_SATURATION_UNION
 �ṹ˵��  : VDEC_QOS_SATURATION �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x000003E8�����:32
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
} SOC_VCODEC_BUS_VDEC_QOS_SATURATION_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_SATURATION_saturation_START  (0)
#define SOC_VCODEC_BUS_VDEC_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_UNION
 �ṹ˵��  : VDEC_QOS_EXTCONTROL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
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
} SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_intclken_END       (2)






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

#endif /* end of soc_vcodec_bus_interface.h */
