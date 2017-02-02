/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_asp_hifi3_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:18:12
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ASP_HIFI3.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ASP_HIFI3_INTERFACE_H__
#define __SOC_ASP_HIFI3_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_TRAXID_UNION */
#define SOC_ASP_HIFI3_TRAXID_ADDR(base)               ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_TRAXCTRL_UNION */
#define SOC_ASP_HIFI3_TRAXCTRL_ADDR(base)             ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_TRAXSTAT_UNION */
#define SOC_ASP_HIFI3_TRAXSTAT_ADDR(base)             ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_TRAXDATA_UNION */
#define SOC_ASP_HIFI3_TRAXDATA_ADDR(base)             ((base) + (0x000C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_TRAXADDR_UNION */
#define SOC_ASP_HIFI3_TRAXADDR_ADDR(base)             ((base) + (0x0010))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_TRIGGERPC_UNION */
#define SOC_ASP_HIFI3_TRIGGERPC_ADDR(base)            ((base) + (0x0014))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_PCMATCHCTRL_UNION */
#define SOC_ASP_HIFI3_PCMATCHCTRL_ADDR(base)          ((base) + (0x0018))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_DELAYCNT_UNION */
#define SOC_ASP_HIFI3_DELAYCNT_ADDR(base)             ((base) + (0x001C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_MEMADDRSTART_UNION */
#define SOC_ASP_HIFI3_MEMADDRSTART_ADDR(base)         ((base) + (0x0020))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_MEMADDREND_UNION */
#define SOC_ASP_HIFI3_MEMADDREND_ADDR(base)           ((base) + (0x0024))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_compressparams_UNION */
#define SOC_ASP_HIFI3_compressparams_ADDR(base)       ((base) + (0x006C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_PMG_UNION */
#define SOC_ASP_HIFI3_PMG_ADDR(base)                  ((base) + (0x1000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_INTPC_UNION */
#define SOC_ASP_HIFI3_INTPC_ADDR(base)                ((base) + (0x1010))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_perfcounter0_UNION */
#define SOC_ASP_HIFI3_perfcounter0_ADDR(base)         ((base) + (0x1080))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_perfcounter1_UNION */
#define SOC_ASP_HIFI3_perfcounter1_ADDR(base)         ((base) + (0x1084))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_perfcounter2_UNION */
#define SOC_ASP_HIFI3_perfcounter2_ADDR(base)         ((base) + (0x1088))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_perfcounter3_UNION */
#define SOC_ASP_HIFI3_perfcounter3_ADDR(base)         ((base) + (0x108C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_PMCTRL0_UNION */
#define SOC_ASP_HIFI3_PMCTRL0_ADDR(base)              ((base) + (0x1100))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_PMCTRL1_UNION */
#define SOC_ASP_HIFI3_PMCTRL1_ADDR(base)              ((base) + (0x1104))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_PMCTRL2_UNION */
#define SOC_ASP_HIFI3_PMCTRL2_ADDR(base)              ((base) + (0x1108))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_PMCTRL3_UNION */
#define SOC_ASP_HIFI3_PMCTRL3_ADDR(base)              ((base) + (0x110C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_PMSTA0_UNION */
#define SOC_ASP_HIFI3_PMSTA0_ADDR(base)               ((base) + (0x1180))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_PMSTA1_UNION */
#define SOC_ASP_HIFI3_PMSTA1_ADDR(base)               ((base) + (0x1184))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_PMSTA2_UNION */
#define SOC_ASP_HIFI3_PMSTA2_ADDR(base)               ((base) + (0x1188))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_PMSTA3_UNION */
#define SOC_ASP_HIFI3_PMSTA3_ADDR(base)               ((base) + (0x118C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_OCDID_UNION */
#define SOC_ASP_HIFI3_OCDID_ADDR(base)                ((base) + (0x2000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_DCRCLR_UNION */
#define SOC_ASP_HIFI3_DCRCLR_ADDR(base)               ((base) + (0x2008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_DCRSET_UNION */
#define SOC_ASP_HIFI3_DCRSET_ADDR(base)               ((base) + (0x200C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_DSR_UNION */
#define SOC_ASP_HIFI3_DSR_ADDR(base)                  ((base) + (0x2010))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_DDR_UNION */
#define SOC_ASP_HIFI3_DDR_ADDR(base)                  ((base) + (0x2014))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_DDREXEC_UNION */
#define SOC_ASP_HIFI3_DDREXEC_ADDR(base)              ((base) + (0x2018))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_DIR0EXEC_UNION */
#define SOC_ASP_HIFI3_DIR0EXEC_ADDR(base)             ((base) + (0x201C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_denugInst0_UNION */
#define SOC_ASP_HIFI3_denugInst0_ADDR(base)           ((base) + (0x2020))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_debugInst1_UNION */
#define SOC_ASP_HIFI3_debugInst1_ADDR(base)           ((base) + (0x2024))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_PWRCTL_UNION */
#define SOC_ASP_HIFI3_PWRCTL_ADDR(base)               ((base) + (0x3020))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_PWRSTAT_UNION */
#define SOC_ASP_HIFI3_PWRSTAT_ADDR(base)              ((base) + (0x3024))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_ERISTAT_UNION */
#define SOC_ASP_HIFI3_ERISTAT_ADDR(base)              ((base) + (0x3028))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_undoRegThID1_UNION */
#define SOC_ASP_HIFI3_undoRegThID1_ADDR(base)         ((base) + (0x3034))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_undocRegBuild_UNION */
#define SOC_ASP_HIFI3_undocRegBuild_ADDR(base)        ((base) + (0x3038))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_undocRegBcid_UNION */
#define SOC_ASP_HIFI3_undocRegBcid_ADDR(base)         ((base) + (0x303C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_itCtrl_UNION */
#define SOC_ASP_HIFI3_itCtrl_ADDR(base)               ((base) + (0x3F00))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_claimSet_UNION */
#define SOC_ASP_HIFI3_claimSet_ADDR(base)             ((base) + (0x3FA0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_claimClear_UNION */
#define SOC_ASP_HIFI3_claimClear_ADDR(base)           ((base) + (0x3FA4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_devId_UNION */
#define SOC_ASP_HIFI3_devId_ADDR(base)                ((base) + (0x3FC8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_devType_UNION */
#define SOC_ASP_HIFI3_devType_ADDR(base)              ((base) + (0x3FCC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_peripheralId4_UNION */
#define SOC_ASP_HIFI3_peripheralId4_ADDR(base)        ((base) + (0x3FD0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_peripheralId5_UNION */
#define SOC_ASP_HIFI3_peripheralId5_ADDR(base)        ((base) + (0x3FD4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_peripheralId6_UNION */
#define SOC_ASP_HIFI3_peripheralId6_ADDR(base)        ((base) + (0x3FD8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_peripheralId7_UNION */
#define SOC_ASP_HIFI3_peripheralId7_ADDR(base)        ((base) + (0x3FDC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_peripheralId0_UNION */
#define SOC_ASP_HIFI3_peripheralId0_ADDR(base)        ((base) + (0x3FE0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_peripheralId1_UNION */
#define SOC_ASP_HIFI3_peripheralId1_ADDR(base)        ((base) + (0x3FE4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_peripheralId2_UNION */
#define SOC_ASP_HIFI3_peripheralId2_ADDR(base)        ((base) + (0x3FE8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_peripheralId3_UNION */
#define SOC_ASP_HIFI3_peripheralId3_ADDR(base)        ((base) + (0x3FEC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_componentId0_UNION */
#define SOC_ASP_HIFI3_componentId0_ADDR(base)         ((base) + (0x3FF0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_componentId1_UNION */
#define SOC_ASP_HIFI3_componentId1_ADDR(base)         ((base) + (0x3FF4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_componentId2_UNION */
#define SOC_ASP_HIFI3_componentId2_ADDR(base)         ((base) + (0x3FF8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_HIFI3_componentId3_UNION */
#define SOC_ASP_HIFI3_componentId3_ADDR(base)         ((base) + (0x3FFC))





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
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_TRAXID_UNION
 �ṹ˵��  : TRAXID �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x0D338FF2�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TRAXID : 32; /* bit[0-31]: TRAX ID Register */
    } reg;
} SOC_ASP_HIFI3_TRAXID_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXID_TRAXID_START  (0)
#define SOC_ASP_HIFI3_TRAXID_TRAXID_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_TRAXCTRL_UNION
 �ṹ˵��  : TRAXCTRL �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x80001080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  traceEnabled                        : 1;  /* bit[0]    : traceEnabled */
        unsigned int  traceStop                           : 1;  /* bit[1]    : traceStop */
        unsigned int  pcMatchEn                           : 1;  /* bit[2]    : pcMatchEn */
        unsigned int  reserved_0                          : 1;  /* bit[3]    : reserved */
        unsigned int  processorTriggerInEn                : 1;  /* bit[4]    : processorTriggerInEn */
        unsigned int  crossTriggerInEn                    : 1;  /* bit[5]    : crossTriggerInEn */
        unsigned int  reserved_1                          : 1;  /* bit[6]    : reserved */
        unsigned int  traceMemOutEn                       : 1;  /* bit[7]    : traceMemOutEn */
        unsigned int  reserved_2                          : 1;  /* bit[8]    : reserved */
        unsigned int  CountUnitIsinst                     : 1;  /* bit[9]    : CountUnitIsinst */
        unsigned int  reserved_3                          : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_4                          : 1;  /* bit[11]   : reserved */
        unsigned int  encodeSyncMessageFreq               : 3;  /* bit[12-14]: encodeSyncMessageFreq */
        unsigned int  reserved_5                          : 1;  /* bit[15]   : reserved */
        unsigned int  processorTriggerOutUponPrimeTrigger : 1;  /* bit[16]   : processorTriggerOutUponPrimeTrigger */
        unsigned int  processorTriggerOutUponZeroCount    : 1;  /* bit[17]   : processorTriggerOutUponZeroCount */
        unsigned int  reserved_6                          : 2;  /* bit[18-19]: reserved */
        unsigned int  CrossTriggerOutUponPrimeTrigger     : 1;  /* bit[20]   : CrossTriggerOutUponPrimeTrigger */
        unsigned int  CrossTriggerOutUponZeroCount        : 1;  /* bit[21]   : CrossTriggerOutUponZeroCount */
        unsigned int  CrossTriggerOutTopology             : 1;  /* bit[22]   : CrossTriggerOutTopology */
        unsigned int  CrossTriggerInAckTopology           : 1;  /* bit[23]   : CrossTriggerInAckTopology */
        unsigned int  TRAXCTRL                            : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_ASP_HIFI3_TRAXCTRL_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXCTRL_traceEnabled_START                         (0)
#define SOC_ASP_HIFI3_TRAXCTRL_traceEnabled_END                           (0)
#define SOC_ASP_HIFI3_TRAXCTRL_traceStop_START                            (1)
#define SOC_ASP_HIFI3_TRAXCTRL_traceStop_END                              (1)
#define SOC_ASP_HIFI3_TRAXCTRL_pcMatchEn_START                            (2)
#define SOC_ASP_HIFI3_TRAXCTRL_pcMatchEn_END                              (2)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerInEn_START                 (4)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerInEn_END                   (4)
#define SOC_ASP_HIFI3_TRAXCTRL_crossTriggerInEn_START                     (5)
#define SOC_ASP_HIFI3_TRAXCTRL_crossTriggerInEn_END                       (5)
#define SOC_ASP_HIFI3_TRAXCTRL_traceMemOutEn_START                        (7)
#define SOC_ASP_HIFI3_TRAXCTRL_traceMemOutEn_END                          (7)
#define SOC_ASP_HIFI3_TRAXCTRL_CountUnitIsinst_START                      (9)
#define SOC_ASP_HIFI3_TRAXCTRL_CountUnitIsinst_END                        (9)
#define SOC_ASP_HIFI3_TRAXCTRL_encodeSyncMessageFreq_START                (12)
#define SOC_ASP_HIFI3_TRAXCTRL_encodeSyncMessageFreq_END                  (14)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerOutUponPrimeTrigger_START  (16)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerOutUponPrimeTrigger_END    (16)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerOutUponZeroCount_START     (17)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerOutUponZeroCount_END       (17)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutUponPrimeTrigger_START      (20)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutUponPrimeTrigger_END        (20)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutUponZeroCount_START         (21)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutUponZeroCount_END           (21)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutTopology_START              (22)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutTopology_END                (22)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerInAckTopology_START            (23)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerInAckTopology_END              (23)
#define SOC_ASP_HIFI3_TRAXCTRL_TRAXCTRL_START                             (24)
#define SOC_ASP_HIFI3_TRAXCTRL_TRAXCTRL_END                               (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_TRAXSTAT_UNION
 �ṹ˵��  : TRAXSTAT �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000C00�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  traceActive                : 1;  /* bit[0]    : traceActive */
        unsigned int  primeTrigger               : 1;  /* bit[1]    : primeTrigger */
        unsigned int  pcMatchImputed             : 1;  /* bit[2]    : pcMatchImputed */
        unsigned int  precedingJTAGxsacResult0   : 1;  /* bit[3]    : precedingJTAGxsacResult[0] */
        unsigned int  processTriggerInImputed    : 1;  /* bit[4]    : processTriggerInImputed */
        unsigned int  corssTriggerInImputed      : 1;  /* bit[5]    : corssTriggerInImputed */
        unsigned int  reserved_0                 : 2;  /* bit[6-7]  : reserved */
        unsigned int  reserved_1                 : 5;  /* bit[8-12] : reserved */
        unsigned int  reserved_2                 : 3;  /* bit[13-15]: reserved */
        unsigned int  processorTriggerOut        : 1;  /* bit[16]   : processorTriggerOut */
        unsigned int  crossTriggerOut            : 1;  /* bit[17]   : crossTriggerOut */
        unsigned int  reserved_3                 : 4;  /* bit[18-21]: reserved */
        unsigned int  crossTriggerOutAckTopology : 1;  /* bit[22]   : crossTriggerOutAckTopology */
        unsigned int  crossTriggerInTopology     : 1;  /* bit[23]   : crossTriggerInTopology */
        unsigned int  TRAXSTAT                   : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_ASP_HIFI3_TRAXSTAT_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXSTAT_traceActive_START                 (0)
#define SOC_ASP_HIFI3_TRAXSTAT_traceActive_END                   (0)
#define SOC_ASP_HIFI3_TRAXSTAT_primeTrigger_START                (1)
#define SOC_ASP_HIFI3_TRAXSTAT_primeTrigger_END                  (1)
#define SOC_ASP_HIFI3_TRAXSTAT_pcMatchImputed_START              (2)
#define SOC_ASP_HIFI3_TRAXSTAT_pcMatchImputed_END                (2)
#define SOC_ASP_HIFI3_TRAXSTAT_precedingJTAGxsacResult0_START    (3)
#define SOC_ASP_HIFI3_TRAXSTAT_precedingJTAGxsacResult0_END      (3)
#define SOC_ASP_HIFI3_TRAXSTAT_processTriggerInImputed_START     (4)
#define SOC_ASP_HIFI3_TRAXSTAT_processTriggerInImputed_END       (4)
#define SOC_ASP_HIFI3_TRAXSTAT_corssTriggerInImputed_START       (5)
#define SOC_ASP_HIFI3_TRAXSTAT_corssTriggerInImputed_END         (5)
#define SOC_ASP_HIFI3_TRAXSTAT_processorTriggerOut_START         (16)
#define SOC_ASP_HIFI3_TRAXSTAT_processorTriggerOut_END           (16)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerOut_START             (17)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerOut_END               (17)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerOutAckTopology_START  (22)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerOutAckTopology_END    (22)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerInTopology_START      (23)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerInTopology_END        (23)
#define SOC_ASP_HIFI3_TRAXSTAT_TRAXSTAT_START                    (24)
#define SOC_ASP_HIFI3_TRAXSTAT_TRAXSTAT_END                      (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_TRAXDATA_UNION
 �ṹ˵��  : TRAXDATA �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TRAXDATA : 32; /* bit[0-31]: TRAX Data Register */
    } reg;
} SOC_ASP_HIFI3_TRAXDATA_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXDATA_TRAXDATA_START  (0)
#define SOC_ASP_HIFI3_TRAXDATA_TRAXDATA_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_TRAXADDR_UNION
 �ṹ˵��  : TRAXADDR �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TRAXADDR : 32; /* bit[0-31]: TRAX Address Register */
    } reg;
} SOC_ASP_HIFI3_TRAXADDR_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXADDR_TRAXADDR_START  (0)
#define SOC_ASP_HIFI3_TRAXADDR_TRAXADDR_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_TRIGGERPC_UNION
 �ṹ˵��  : TRIGGERPC �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TRIGGERPC : 32; /* bit[0-31]: TRAX Stop PC */
    } reg;
} SOC_ASP_HIFI3_TRIGGERPC_UNION;
#endif
#define SOC_ASP_HIFI3_TRIGGERPC_TRIGGERPC_START  (0)
#define SOC_ASP_HIFI3_TRIGGERPC_TRIGGERPC_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_PCMATCHCTRL_UNION
 �ṹ˵��  : PCMATCHCTRL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PCMATCHCTRL : 32; /* bit[0-31]: TRAX Stop PC Range */
    } reg;
} SOC_ASP_HIFI3_PCMATCHCTRL_UNION;
#endif
#define SOC_ASP_HIFI3_PCMATCHCTRL_PCMATCHCTRL_START  (0)
#define SOC_ASP_HIFI3_PCMATCHCTRL_PCMATCHCTRL_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_DELAYCNT_UNION
 �ṹ˵��  : DELAYCNT �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DELAYCNT : 32; /* bit[0-31]: TRAX Post Stop Capture Size */
    } reg;
} SOC_ASP_HIFI3_DELAYCNT_UNION;
#endif
#define SOC_ASP_HIFI3_DELAYCNT_DELAYCNT_START  (0)
#define SOC_ASP_HIFI3_DELAYCNT_DELAYCNT_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_MEMADDRSTART_UNION
 �ṹ˵��  : MEMADDRSTART �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MEMADDRSTART : 32; /* bit[0-31]: Trace memory start address */
    } reg;
} SOC_ASP_HIFI3_MEMADDRSTART_UNION;
#endif
#define SOC_ASP_HIFI3_MEMADDRSTART_MEMADDRSTART_START  (0)
#define SOC_ASP_HIFI3_MEMADDRSTART_MEMADDRSTART_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_MEMADDREND_UNION
 �ṹ˵��  : MEMADDREND �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x000003FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MEMADDREND : 32; /* bit[0-31]: Trace memory end address */
    } reg;
} SOC_ASP_HIFI3_MEMADDREND_UNION;
#endif
#define SOC_ASP_HIFI3_MEMADDREND_MEMADDREND_START  (0)
#define SOC_ASP_HIFI3_MEMADDREND_MEMADDREND_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_compressparams_UNION
 �ṹ˵��  : compressparams �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x06710671�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cp2 : 16; /* bit[0-15] : cp2[15:0] */
        unsigned int  cp1 : 16; /* bit[16-31]: cp1[15:0] */
    } reg;
} SOC_ASP_HIFI3_compressparams_UNION;
#endif
#define SOC_ASP_HIFI3_compressparams_cp2_START  (0)
#define SOC_ASP_HIFI3_compressparams_cp2_END    (15)
#define SOC_ASP_HIFI3_compressparams_cp1_START  (16)
#define SOC_ASP_HIFI3_compressparams_cp1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_PMG_UNION
 �ṹ˵��  : PMG �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pergloben : 1;  /* bit[0-0] : overall enable for all performance counting */
        unsigned int  PMG       : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_ASP_HIFI3_PMG_UNION;
#endif
#define SOC_ASP_HIFI3_PMG_pergloben_START  (0)
#define SOC_ASP_HIFI3_PMG_pergloben_END    (0)
#define SOC_ASP_HIFI3_PMG_PMG_START        (1)
#define SOC_ASP_HIFI3_PMG_PMG_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_INTPC_UNION
 �ṹ˵��  : INTPC �Ĵ����ṹ���塣��ַƫ����:0x1010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INTPC : 32; /* bit[0-31]: PC at cycle of last event that cause interrupt */
    } reg;
} SOC_ASP_HIFI3_INTPC_UNION;
#endif
#define SOC_ASP_HIFI3_INTPC_INTPC_START  (0)
#define SOC_ASP_HIFI3_INTPC_INTPC_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_perfcounter0_UNION
 �ṹ˵��  : perfcounter0 �Ĵ����ṹ���塣��ַƫ����:0x1080����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PM0 : 32; /* bit[0-31]: performanc counter0 values */
    } reg;
} SOC_ASP_HIFI3_perfcounter0_UNION;
#endif
#define SOC_ASP_HIFI3_perfcounter0_PM0_START  (0)
#define SOC_ASP_HIFI3_perfcounter0_PM0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_perfcounter1_UNION
 �ṹ˵��  : perfcounter1 �Ĵ����ṹ���塣��ַƫ����:0x1084����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PM1 : 32; /* bit[0-31]: performanc counter1 values */
    } reg;
} SOC_ASP_HIFI3_perfcounter1_UNION;
#endif
#define SOC_ASP_HIFI3_perfcounter1_PM1_START  (0)
#define SOC_ASP_HIFI3_perfcounter1_PM1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_perfcounter2_UNION
 �ṹ˵��  : perfcounter2 �Ĵ����ṹ���塣��ַƫ����:0x1088����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PM2 : 32; /* bit[0-31]: performanc counter2 values */
    } reg;
} SOC_ASP_HIFI3_perfcounter2_UNION;
#endif
#define SOC_ASP_HIFI3_perfcounter2_PM2_START  (0)
#define SOC_ASP_HIFI3_perfcounter2_PM2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_perfcounter3_UNION
 �ṹ˵��  : perfcounter3 �Ĵ����ṹ���塣��ַƫ����:0x108C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PM3 : 32; /* bit[0-31]: performanc counter3 values */
    } reg;
} SOC_ASP_HIFI3_perfcounter3_UNION;
#endif
#define SOC_ASP_HIFI3_perfcounter3_PM3_START  (0)
#define SOC_ASP_HIFI3_perfcounter3_PM3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_PMCTRL0_UNION
 �ṹ˵��  : PMCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x1100����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfIntEn0   : 1;  /* bit[0-0]  : perfIntEn0 */
        unsigned int  reserved_0   : 2;  /* bit[1-2]  : reserved */
        unsigned int  kernelcount0 : 1;  /* bit[3-3]  : kernelcount0 */
        unsigned int  traceLevel0  : 4;  /* bit[4-7]  : traceLevel0 */
        unsigned int  perfSelect0  : 5;  /* bit[8-12] : perfSelect0 */
        unsigned int  reserved_1   : 3;  /* bit[13-15]: reserved */
        unsigned int  perMask0     : 16; /* bit[16-31]: perMask0 */
    } reg;
} SOC_ASP_HIFI3_PMCTRL0_UNION;
#endif
#define SOC_ASP_HIFI3_PMCTRL0_perfIntEn0_START    (0)
#define SOC_ASP_HIFI3_PMCTRL0_perfIntEn0_END      (0)
#define SOC_ASP_HIFI3_PMCTRL0_kernelcount0_START  (3)
#define SOC_ASP_HIFI3_PMCTRL0_kernelcount0_END    (3)
#define SOC_ASP_HIFI3_PMCTRL0_traceLevel0_START   (4)
#define SOC_ASP_HIFI3_PMCTRL0_traceLevel0_END     (7)
#define SOC_ASP_HIFI3_PMCTRL0_perfSelect0_START   (8)
#define SOC_ASP_HIFI3_PMCTRL0_perfSelect0_END     (12)
#define SOC_ASP_HIFI3_PMCTRL0_perMask0_START      (16)
#define SOC_ASP_HIFI3_PMCTRL0_perMask0_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_PMCTRL1_UNION
 �ṹ˵��  : PMCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x1104����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfIntEn1   : 1;  /* bit[0-0]  : perfIntEn1 */
        unsigned int  reserved_0   : 2;  /* bit[1-2]  : reserved */
        unsigned int  kernelcount1 : 1;  /* bit[3-3]  : kernelcount1 */
        unsigned int  traceLevel1  : 4;  /* bit[4-7]  : traceLevel1 */
        unsigned int  perfSelect1  : 5;  /* bit[8-12] : perfSelect1 */
        unsigned int  reserved_1   : 3;  /* bit[13-15]: reserved */
        unsigned int  perMask1     : 16; /* bit[16-31]: perMask1 */
    } reg;
} SOC_ASP_HIFI3_PMCTRL1_UNION;
#endif
#define SOC_ASP_HIFI3_PMCTRL1_perfIntEn1_START    (0)
#define SOC_ASP_HIFI3_PMCTRL1_perfIntEn1_END      (0)
#define SOC_ASP_HIFI3_PMCTRL1_kernelcount1_START  (3)
#define SOC_ASP_HIFI3_PMCTRL1_kernelcount1_END    (3)
#define SOC_ASP_HIFI3_PMCTRL1_traceLevel1_START   (4)
#define SOC_ASP_HIFI3_PMCTRL1_traceLevel1_END     (7)
#define SOC_ASP_HIFI3_PMCTRL1_perfSelect1_START   (8)
#define SOC_ASP_HIFI3_PMCTRL1_perfSelect1_END     (12)
#define SOC_ASP_HIFI3_PMCTRL1_perMask1_START      (16)
#define SOC_ASP_HIFI3_PMCTRL1_perMask1_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_PMCTRL2_UNION
 �ṹ˵��  : PMCTRL2 �Ĵ����ṹ���塣��ַƫ����:0x1108����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfIntEn2   : 1;  /* bit[0-0]  : perfIntEn2 */
        unsigned int  reserved_0   : 2;  /* bit[1-2]  : reserved */
        unsigned int  kernelcount2 : 1;  /* bit[3-3]  : kernelcount2 */
        unsigned int  traceLevel2  : 4;  /* bit[4-7]  : traceLevel2 */
        unsigned int  perfSelect2  : 5;  /* bit[8-12] : perfSelect2 */
        unsigned int  reserved_1   : 3;  /* bit[13-15]: reserved */
        unsigned int  perMask2     : 16; /* bit[16-31]: perMask2 */
    } reg;
} SOC_ASP_HIFI3_PMCTRL2_UNION;
#endif
#define SOC_ASP_HIFI3_PMCTRL2_perfIntEn2_START    (0)
#define SOC_ASP_HIFI3_PMCTRL2_perfIntEn2_END      (0)
#define SOC_ASP_HIFI3_PMCTRL2_kernelcount2_START  (3)
#define SOC_ASP_HIFI3_PMCTRL2_kernelcount2_END    (3)
#define SOC_ASP_HIFI3_PMCTRL2_traceLevel2_START   (4)
#define SOC_ASP_HIFI3_PMCTRL2_traceLevel2_END     (7)
#define SOC_ASP_HIFI3_PMCTRL2_perfSelect2_START   (8)
#define SOC_ASP_HIFI3_PMCTRL2_perfSelect2_END     (12)
#define SOC_ASP_HIFI3_PMCTRL2_perMask2_START      (16)
#define SOC_ASP_HIFI3_PMCTRL2_perMask2_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_PMCTRL3_UNION
 �ṹ˵��  : PMCTRL3 �Ĵ����ṹ���塣��ַƫ����:0x110C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfIntEn3   : 1;  /* bit[0-0]  : perfIntEn3 */
        unsigned int  reserved_0   : 2;  /* bit[1-2]  : reserved */
        unsigned int  kernelcount3 : 1;  /* bit[3-3]  : kernelcount3 */
        unsigned int  traceLevel3  : 4;  /* bit[4-7]  : traceLevel3 */
        unsigned int  perfSelect3  : 5;  /* bit[8-12] : perfSelect3 */
        unsigned int  reserved_1   : 3;  /* bit[13-15]: reserved */
        unsigned int  perMask3     : 16; /* bit[16-31]: perMask3 */
    } reg;
} SOC_ASP_HIFI3_PMCTRL3_UNION;
#endif
#define SOC_ASP_HIFI3_PMCTRL3_perfIntEn3_START    (0)
#define SOC_ASP_HIFI3_PMCTRL3_perfIntEn3_END      (0)
#define SOC_ASP_HIFI3_PMCTRL3_kernelcount3_START  (3)
#define SOC_ASP_HIFI3_PMCTRL3_kernelcount3_END    (3)
#define SOC_ASP_HIFI3_PMCTRL3_traceLevel3_START   (4)
#define SOC_ASP_HIFI3_PMCTRL3_traceLevel3_END     (7)
#define SOC_ASP_HIFI3_PMCTRL3_perfSelect3_START   (8)
#define SOC_ASP_HIFI3_PMCTRL3_perfSelect3_END     (12)
#define SOC_ASP_HIFI3_PMCTRL3_perMask3_START      (16)
#define SOC_ASP_HIFI3_PMCTRL3_perMask3_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_PMSTA0_UNION
 �ṹ˵��  : PMSTA0 �Ĵ����ṹ���塣��ַƫ����:0x1180����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfverflow0     : 1;  /* bit[0-0] : perOverflow0 */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : reserved */
        unsigned int  perfIntAsserted0 : 1;  /* bit[4-4] : perfIntAsserted0 */
        unsigned int  reserved_1       : 27; /* bit[5-31]: performance counter0 status register */
    } reg;
} SOC_ASP_HIFI3_PMSTA0_UNION;
#endif
#define SOC_ASP_HIFI3_PMSTA0_perfverflow0_START      (0)
#define SOC_ASP_HIFI3_PMSTA0_perfverflow0_END        (0)
#define SOC_ASP_HIFI3_PMSTA0_perfIntAsserted0_START  (4)
#define SOC_ASP_HIFI3_PMSTA0_perfIntAsserted0_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_PMSTA1_UNION
 �ṹ˵��  : PMSTA1 �Ĵ����ṹ���塣��ַƫ����:0x1184����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfverflow1     : 1;  /* bit[0-0] : perOverflow1 */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : reserved */
        unsigned int  perfIntAsserted1 : 1;  /* bit[4-4] : perfIntAsserted1 */
        unsigned int  reserved_1       : 27; /* bit[5-31]: performance counter1 status register */
    } reg;
} SOC_ASP_HIFI3_PMSTA1_UNION;
#endif
#define SOC_ASP_HIFI3_PMSTA1_perfverflow1_START      (0)
#define SOC_ASP_HIFI3_PMSTA1_perfverflow1_END        (0)
#define SOC_ASP_HIFI3_PMSTA1_perfIntAsserted1_START  (4)
#define SOC_ASP_HIFI3_PMSTA1_perfIntAsserted1_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_PMSTA2_UNION
 �ṹ˵��  : PMSTA2 �Ĵ����ṹ���塣��ַƫ����:0x1188����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfverflow2     : 1;  /* bit[0-0] : perOverflow2 */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : reserved */
        unsigned int  perfIntAsserted2 : 1;  /* bit[4-4] : perfIntAsserted2 */
        unsigned int  reserved_1       : 27; /* bit[5-31]: performance counter2 status register */
    } reg;
} SOC_ASP_HIFI3_PMSTA2_UNION;
#endif
#define SOC_ASP_HIFI3_PMSTA2_perfverflow2_START      (0)
#define SOC_ASP_HIFI3_PMSTA2_perfverflow2_END        (0)
#define SOC_ASP_HIFI3_PMSTA2_perfIntAsserted2_START  (4)
#define SOC_ASP_HIFI3_PMSTA2_perfIntAsserted2_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_PMSTA3_UNION
 �ṹ˵��  : PMSTA3 �Ĵ����ṹ���塣��ַƫ����:0x118C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfverflow3     : 1;  /* bit[0-0] : perOverflow3 */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : reserved */
        unsigned int  perfIntAsserted3 : 1;  /* bit[4-4] : perfIntAsserted3 */
        unsigned int  reserved_1       : 27; /* bit[5-31]: performance counter3 status register */
    } reg;
} SOC_ASP_HIFI3_PMSTA3_UNION;
#endif
#define SOC_ASP_HIFI3_PMSTA3_perfverflow3_START      (0)
#define SOC_ASP_HIFI3_PMSTA3_perfverflow3_END        (0)
#define SOC_ASP_HIFI3_PMSTA3_perfIntAsserted3_START  (4)
#define SOC_ASP_HIFI3_PMSTA3_perfIntAsserted3_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_OCDID_UNION
 �ṹ˵��  : OCDID �Ĵ����ṹ���塣��ַƫ����:0x2000����ֵ:0x0D338FF2�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  OCDID : 32; /* bit[0-31]: ID register */
    } reg;
} SOC_ASP_HIFI3_OCDID_UNION;
#endif
#define SOC_ASP_HIFI3_OCDID_OCDID_START  (0)
#define SOC_ASP_HIFI3_OCDID_OCDID_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_DCRCLR_UNION
 �ṹ˵��  : DCRCLR �Ĵ����ṹ���塣��ַƫ����:0x2008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enableOCD          : 1;  /* bit[0-0]  : enableOCD */
        unsigned int  hostDebugInterrupt : 1;  /* bit[1-1]  : hostDebugInterrupt */
        unsigned int  induceOCDoverride  : 1;  /* bit[2-2]  : induceOCDoverride */
        unsigned int  reserved_0         : 13; /* bit[3-15] : reserved */
        unsigned int  extDbgIntEn        : 1;  /* bit[16-16]: extDbgIntEn */
        unsigned int  xOCDModePulseEn    : 1;  /* bit[17-17]: xOCDModePulseEn */
        unsigned int  reserved_1         : 6;  /* bit[18-23]: reserved */
        unsigned int  breakOutTopology   : 1;  /* bit[24-24]: breakOutTopology */
        unsigned int  breakInAckTopology : 1;  /* bit[25-25]: breakInAckTopology */
        unsigned int  reserved_2         : 6;  /* bit[26-31]: debug control register,wtite to clear */
    } reg;
} SOC_ASP_HIFI3_DCRCLR_UNION;
#endif
#define SOC_ASP_HIFI3_DCRCLR_enableOCD_START           (0)
#define SOC_ASP_HIFI3_DCRCLR_enableOCD_END             (0)
#define SOC_ASP_HIFI3_DCRCLR_hostDebugInterrupt_START  (1)
#define SOC_ASP_HIFI3_DCRCLR_hostDebugInterrupt_END    (1)
#define SOC_ASP_HIFI3_DCRCLR_induceOCDoverride_START   (2)
#define SOC_ASP_HIFI3_DCRCLR_induceOCDoverride_END     (2)
#define SOC_ASP_HIFI3_DCRCLR_extDbgIntEn_START         (16)
#define SOC_ASP_HIFI3_DCRCLR_extDbgIntEn_END           (16)
#define SOC_ASP_HIFI3_DCRCLR_xOCDModePulseEn_START     (17)
#define SOC_ASP_HIFI3_DCRCLR_xOCDModePulseEn_END       (17)
#define SOC_ASP_HIFI3_DCRCLR_breakOutTopology_START    (24)
#define SOC_ASP_HIFI3_DCRCLR_breakOutTopology_END      (24)
#define SOC_ASP_HIFI3_DCRCLR_breakInAckTopology_START  (25)
#define SOC_ASP_HIFI3_DCRCLR_breakInAckTopology_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_DCRSET_UNION
 �ṹ˵��  : DCRSET �Ĵ����ṹ���塣��ַƫ����:0x200C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enableOCD          : 1;  /* bit[0-0]  : enableOCD */
        unsigned int  hostDebugInterrupt : 1;  /* bit[1-1]  : hostDebugInterrupt */
        unsigned int  induceOCDoverride  : 1;  /* bit[2-2]  : induceOCDoverride */
        unsigned int  reserved_0         : 13; /* bit[3-15] : reserved */
        unsigned int  extDbgIntEn        : 1;  /* bit[16-16]: extDbgIntEn */
        unsigned int  xOCDModePulseEn    : 1;  /* bit[17-17]: xOCDModePulseEn */
        unsigned int  reserved_1         : 6;  /* bit[18-23]: reserved */
        unsigned int  breakOutTopology   : 1;  /* bit[24-24]: breakOutTopology */
        unsigned int  breakInAckTopology : 1;  /* bit[25-25]: breakInAckTopology */
        unsigned int  DCRSET             : 6;  /* bit[26-31]: debug control register,wtite to set */
    } reg;
} SOC_ASP_HIFI3_DCRSET_UNION;
#endif
#define SOC_ASP_HIFI3_DCRSET_enableOCD_START           (0)
#define SOC_ASP_HIFI3_DCRSET_enableOCD_END             (0)
#define SOC_ASP_HIFI3_DCRSET_hostDebugInterrupt_START  (1)
#define SOC_ASP_HIFI3_DCRSET_hostDebugInterrupt_END    (1)
#define SOC_ASP_HIFI3_DCRSET_induceOCDoverride_START   (2)
#define SOC_ASP_HIFI3_DCRSET_induceOCDoverride_END     (2)
#define SOC_ASP_HIFI3_DCRSET_extDbgIntEn_START         (16)
#define SOC_ASP_HIFI3_DCRSET_extDbgIntEn_END           (16)
#define SOC_ASP_HIFI3_DCRSET_xOCDModePulseEn_START     (17)
#define SOC_ASP_HIFI3_DCRSET_xOCDModePulseEn_END       (17)
#define SOC_ASP_HIFI3_DCRSET_breakOutTopology_START    (24)
#define SOC_ASP_HIFI3_DCRSET_breakOutTopology_END      (24)
#define SOC_ASP_HIFI3_DCRSET_breakInAckTopology_START  (25)
#define SOC_ASP_HIFI3_DCRSET_breakInAckTopology_END    (25)
#define SOC_ASP_HIFI3_DCRSET_DCRSET_START              (26)
#define SOC_ASP_HIFI3_DCRSET_DCRSET_END                (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_DSR_UNION
 �ṹ˵��  : DSR �Ĵ����ṹ���塣��ַƫ����:0x2010����ֵ:0x02000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  execDone           : 1;  /* bit[0-0]  : execDone */
        unsigned int  exeException       : 1;  /* bit[1-1]  : exeException */
        unsigned int  exeBusy            : 1;  /* bit[2-2]  : exeBusy */
        unsigned int  execOverrun        : 1;  /* bit[3-3]  : execOverrun */
        unsigned int  ocdDtopped         : 1;  /* bit[4-4]  : ocdDtopped */
        unsigned int  reserved_0         : 5;  /* bit[5-9]  : reserved */
        unsigned int  corewroteDDR       : 1;  /* bit[10-10]: corewroteDDR */
        unsigned int  coreReadDDR        : 1;  /* bit[11-11]: coreReadDDR */
        unsigned int  reserved_1         : 2;  /* bit[12-13]: reserved */
        unsigned int  hostWroteDDR       : 1;  /* bit[14-14]: hostWroteDDR */
        unsigned int  hostReadDDR        : 1;  /* bit[15-15]: hostReadDDR */
        unsigned int  debugPendBreakin   : 1;  /* bit[16-16]: debugPendBreakin */
        unsigned int  debugpendhost      : 1;  /* bit[17-17]: debugpendhost */
        unsigned int  debugpendtrax      : 1;  /* bit[18-18]: debugPendTrax */
        unsigned int  reserved_2         : 1;  /* bit[19-19]: reserved */
        unsigned int  debugIntBreakin    : 1;  /* bit[20-20]: debugIntBreakin */
        unsigned int  debugIntHost       : 1;  /* bit[21-21]: debugIntHost */
        unsigned int  debugIntTrax       : 1;  /* bit[22-22]: debugIntTrax */
        unsigned int  reserved_3         : 2;  /* bit[23-24]: reserved */
        unsigned int  beakOutAckTopology : 1;  /* bit[25-25]: beakOutAckTopology */
        unsigned int  breakInTopology    : 1;  /* bit[26-26]: breakInTopology */
        unsigned int  reserved_4         : 5;  /* bit[27-31]: debug status register */
    } reg;
} SOC_ASP_HIFI3_DSR_UNION;
#endif
#define SOC_ASP_HIFI3_DSR_execDone_START            (0)
#define SOC_ASP_HIFI3_DSR_execDone_END              (0)
#define SOC_ASP_HIFI3_DSR_exeException_START        (1)
#define SOC_ASP_HIFI3_DSR_exeException_END          (1)
#define SOC_ASP_HIFI3_DSR_exeBusy_START             (2)
#define SOC_ASP_HIFI3_DSR_exeBusy_END               (2)
#define SOC_ASP_HIFI3_DSR_execOverrun_START         (3)
#define SOC_ASP_HIFI3_DSR_execOverrun_END           (3)
#define SOC_ASP_HIFI3_DSR_ocdDtopped_START          (4)
#define SOC_ASP_HIFI3_DSR_ocdDtopped_END            (4)
#define SOC_ASP_HIFI3_DSR_corewroteDDR_START        (10)
#define SOC_ASP_HIFI3_DSR_corewroteDDR_END          (10)
#define SOC_ASP_HIFI3_DSR_coreReadDDR_START         (11)
#define SOC_ASP_HIFI3_DSR_coreReadDDR_END           (11)
#define SOC_ASP_HIFI3_DSR_hostWroteDDR_START        (14)
#define SOC_ASP_HIFI3_DSR_hostWroteDDR_END          (14)
#define SOC_ASP_HIFI3_DSR_hostReadDDR_START         (15)
#define SOC_ASP_HIFI3_DSR_hostReadDDR_END           (15)
#define SOC_ASP_HIFI3_DSR_debugPendBreakin_START    (16)
#define SOC_ASP_HIFI3_DSR_debugPendBreakin_END      (16)
#define SOC_ASP_HIFI3_DSR_debugpendhost_START       (17)
#define SOC_ASP_HIFI3_DSR_debugpendhost_END         (17)
#define SOC_ASP_HIFI3_DSR_debugpendtrax_START       (18)
#define SOC_ASP_HIFI3_DSR_debugpendtrax_END         (18)
#define SOC_ASP_HIFI3_DSR_debugIntBreakin_START     (20)
#define SOC_ASP_HIFI3_DSR_debugIntBreakin_END       (20)
#define SOC_ASP_HIFI3_DSR_debugIntHost_START        (21)
#define SOC_ASP_HIFI3_DSR_debugIntHost_END          (21)
#define SOC_ASP_HIFI3_DSR_debugIntTrax_START        (22)
#define SOC_ASP_HIFI3_DSR_debugIntTrax_END          (22)
#define SOC_ASP_HIFI3_DSR_beakOutAckTopology_START  (25)
#define SOC_ASP_HIFI3_DSR_beakOutAckTopology_END    (25)
#define SOC_ASP_HIFI3_DSR_breakInTopology_START     (26)
#define SOC_ASP_HIFI3_DSR_breakInTopology_END       (26)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_DDR_UNION
 �ṹ˵��  : DDR �Ĵ����ṹ���塣��ַƫ����:0x2014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DDR : 32; /* bit[0-31]: debug data register */
    } reg;
} SOC_ASP_HIFI3_DDR_UNION;
#endif
#define SOC_ASP_HIFI3_DDR_DDR_START  (0)
#define SOC_ASP_HIFI3_DDR_DDR_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_DDREXEC_UNION
 �ṹ˵��  : DDREXEC �Ĵ����ṹ���塣��ַƫ����:0x2018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DDREXEC : 32; /* bit[0-31]: alias DDR, execute DIR when accessed  */
    } reg;
} SOC_ASP_HIFI3_DDREXEC_UNION;
#endif
#define SOC_ASP_HIFI3_DDREXEC_DDREXEC_START  (0)
#define SOC_ASP_HIFI3_DDREXEC_DDREXEC_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_DIR0EXEC_UNION
 �ṹ˵��  : DIR0EXEC �Ĵ����ṹ���塣��ַƫ����:0x201C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DIR0EXEC : 32; /* bit[0-31]: alias DIR0, execute instruction when written  */
    } reg;
} SOC_ASP_HIFI3_DIR0EXEC_UNION;
#endif
#define SOC_ASP_HIFI3_DIR0EXEC_DIR0EXEC_START  (0)
#define SOC_ASP_HIFI3_DIR0EXEC_DIR0EXEC_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_denugInst0_UNION
 �ṹ˵��  : denugInst0 �Ĵ����ṹ���塣��ַƫ����:0x2020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  denugInst0 : 32; /* bit[0-31]: denugInst0 */
    } reg;
} SOC_ASP_HIFI3_denugInst0_UNION;
#endif
#define SOC_ASP_HIFI3_denugInst0_denugInst0_START  (0)
#define SOC_ASP_HIFI3_denugInst0_denugInst0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_debugInst1_UNION
 �ṹ˵��  : debugInst1 �Ĵ����ṹ���塣��ַƫ����:0x2024����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debugInst1 : 32; /* bit[0-31]: debugInst1 */
    } reg;
} SOC_ASP_HIFI3_debugInst1_UNION;
#endif
#define SOC_ASP_HIFI3_debugInst1_debugInst1_START  (0)
#define SOC_ASP_HIFI3_debugInst1_debugInst1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_PWRCTL_UNION
 �ṹ˵��  : PWRCTL �Ĵ����ṹ���塣��ַƫ����:0x3020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 16; /* bit[0-15] : reserved */
        unsigned int  apbcorereset  : 1;  /* bit[16-16]: setting to 1 asserts reset to the core */
        unsigned int  reserved_1    : 11; /* bit[17-27]: reserved */
        unsigned int  apbdebugreset : 1;  /* bit[28-28]: setting to 1 assert reset to debug module */
        unsigned int  pwrctl        : 3;  /* bit[29-31]: power and reset control */
    } reg;
} SOC_ASP_HIFI3_PWRCTL_UNION;
#endif
#define SOC_ASP_HIFI3_PWRCTL_apbcorereset_START   (16)
#define SOC_ASP_HIFI3_PWRCTL_apbcorereset_END     (16)
#define SOC_ASP_HIFI3_PWRCTL_apbdebugreset_START  (28)
#define SOC_ASP_HIFI3_PWRCTL_apbdebugreset_END    (28)
#define SOC_ASP_HIFI3_PWRCTL_pwrctl_START         (29)
#define SOC_ASP_HIFI3_PWRCTL_pwrctl_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_PWRSTAT_UNION
 �ṹ˵��  : PWRSTAT �Ĵ����ṹ���塣��ַƫ����:0x3024����ֵ:0x30011111�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0       : 16; /* bit[0-15] : reserved */
        unsigned int  apbcorewasreset  : 1;  /* bit[16-16]: apb core was reset */
        unsigned int  reserved_1       : 11; /* bit[17-27]: reserved */
        unsigned int  apbdebugwasreset : 1;  /* bit[28-28]: apbdebug was reset */
        unsigned int  PWRSTAT          : 3;  /* bit[29-31]: power and reset status */
    } reg;
} SOC_ASP_HIFI3_PWRSTAT_UNION;
#endif
#define SOC_ASP_HIFI3_PWRSTAT_apbcorewasreset_START   (16)
#define SOC_ASP_HIFI3_PWRSTAT_apbcorewasreset_END     (16)
#define SOC_ASP_HIFI3_PWRSTAT_apbdebugwasreset_START  (28)
#define SOC_ASP_HIFI3_PWRSTAT_apbdebugwasreset_END    (28)
#define SOC_ASP_HIFI3_PWRSTAT_PWRSTAT_START           (29)
#define SOC_ASP_HIFI3_PWRSTAT_PWRSTAT_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_ERISTAT_UNION
 �ṹ˵��  : ERISTAT �Ĵ����ṹ���塣��ַƫ����:0x3028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stickyErriWrResult : 1;  /* bit[0-0] : stickyErriWrResult */
        unsigned int  reserved           : 31; /* bit[1-31]: ERI transaction status */
    } reg;
} SOC_ASP_HIFI3_ERISTAT_UNION;
#endif
#define SOC_ASP_HIFI3_ERISTAT_stickyErriWrResult_START  (0)
#define SOC_ASP_HIFI3_ERISTAT_stickyErriWrResult_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_undoRegThID1_UNION
 �ṹ˵��  : undoRegThID1 �Ĵ����ṹ���塣��ַƫ����:0x3034����ֵ:0x19450671�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  undoRegThID1 : 32; /* bit[0-31]: undoRegThID1 */
    } reg;
} SOC_ASP_HIFI3_undoRegThID1_UNION;
#endif
#define SOC_ASP_HIFI3_undoRegThID1_undoRegThID1_START  (0)
#define SOC_ASP_HIFI3_undoRegThID1_undoRegThID1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_undocRegBuild_UNION
 �ṹ˵��  : undocRegBuild �Ĵ����ṹ���塣��ַƫ����:0x3038����ֵ:0x00050671�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  undocRegBuild : 32; /* bit[0-31]: undocRegBuild */
    } reg;
} SOC_ASP_HIFI3_undocRegBuild_UNION;
#endif
#define SOC_ASP_HIFI3_undocRegBuild_undocRegBuild_START  (0)
#define SOC_ASP_HIFI3_undocRegBuild_undocRegBuild_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_undocRegBcid_UNION
 �ṹ˵��  : undocRegBcid �Ĵ����ṹ���塣��ַƫ����:0x303C����ֵ:0x000023B3�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  undocRegBcid : 32; /* bit[0-31]: undocRegBcid */
    } reg;
} SOC_ASP_HIFI3_undocRegBcid_UNION;
#endif
#define SOC_ASP_HIFI3_undocRegBcid_undocRegBcid_START  (0)
#define SOC_ASP_HIFI3_undocRegBcid_undocRegBcid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_itCtrl_UNION
 �ṹ˵��  : itCtrl �Ĵ����ṹ���塣��ַƫ����:0x3F00����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itCtrl   : 1;  /* bit[0-0] : itCtrl */
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_ASP_HIFI3_itCtrl_UNION;
#endif
#define SOC_ASP_HIFI3_itCtrl_itCtrl_START    (0)
#define SOC_ASP_HIFI3_itCtrl_itCtrl_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_claimSet_UNION
 �ṹ˵��  : claimSet �Ĵ����ṹ���塣��ַƫ����:0x3FA0����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  claimSet : 32; /* bit[0-31]: claimSet */
    } reg;
} SOC_ASP_HIFI3_claimSet_UNION;
#endif
#define SOC_ASP_HIFI3_claimSet_claimSet_START  (0)
#define SOC_ASP_HIFI3_claimSet_claimSet_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_claimClear_UNION
 �ṹ˵��  : claimClear �Ĵ����ṹ���塣��ַƫ����:0x3FA4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  claimClear : 32; /* bit[0-31]: claimClear */
    } reg;
} SOC_ASP_HIFI3_claimClear_UNION;
#endif
#define SOC_ASP_HIFI3_claimClear_claimClear_START  (0)
#define SOC_ASP_HIFI3_claimClear_claimClear_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_devId_UNION
 �ṹ˵��  : devId �Ĵ����ṹ���塣��ַƫ����:0x3FC8����ֵ:0x120034E5�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  devId : 32; /* bit[0-31]: devId */
    } reg;
} SOC_ASP_HIFI3_devId_UNION;
#endif
#define SOC_ASP_HIFI3_devId_devId_START  (0)
#define SOC_ASP_HIFI3_devId_devId_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_devType_UNION
 �ṹ˵��  : devType �Ĵ����ṹ���塣��ַƫ����:0x3FCC����ֵ:0x00000013�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  devType : 32; /* bit[0-31]: devType */
    } reg;
} SOC_ASP_HIFI3_devType_UNION;
#endif
#define SOC_ASP_HIFI3_devType_devType_START  (0)
#define SOC_ASP_HIFI3_devType_devType_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_peripheralId4_UNION
 �ṹ˵��  : peripheralId4 �Ĵ����ṹ���塣��ַƫ����:0x3FD0����ֵ:0x00000024�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId4 : 32; /* bit[0-31]: peripheralId4 */
    } reg;
} SOC_ASP_HIFI3_peripheralId4_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId4_peripheralId4_START  (0)
#define SOC_ASP_HIFI3_peripheralId4_peripheralId4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_peripheralId5_UNION
 �ṹ˵��  : peripheralId5 �Ĵ����ṹ���塣��ַƫ����:0x3FD4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId5 : 32; /* bit[0-31]: peripheralId5 */
    } reg;
} SOC_ASP_HIFI3_peripheralId5_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId5_peripheralId5_START  (0)
#define SOC_ASP_HIFI3_peripheralId5_peripheralId5_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_peripheralId6_UNION
 �ṹ˵��  : peripheralId6 �Ĵ����ṹ���塣��ַƫ����:0x3FD8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId6 : 32; /* bit[0-31]: peripheralId6 */
    } reg;
} SOC_ASP_HIFI3_peripheralId6_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId6_peripheralId6_START  (0)
#define SOC_ASP_HIFI3_peripheralId6_peripheralId6_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_peripheralId7_UNION
 �ṹ˵��  : peripheralId7 �Ĵ����ṹ���塣��ַƫ����:0x3FDC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId7 : 32; /* bit[0-31]: peripheralId7 */
    } reg;
} SOC_ASP_HIFI3_peripheralId7_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId7_peripheralId7_START  (0)
#define SOC_ASP_HIFI3_peripheralId7_peripheralId7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_peripheralId0_UNION
 �ṹ˵��  : peripheralId0 �Ĵ����ṹ���塣��ַƫ����:0x3FE0����ֵ:0x00000003�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId0 : 32; /* bit[0-31]: peripheralId0 */
    } reg;
} SOC_ASP_HIFI3_peripheralId0_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId0_peripheralId0_START  (0)
#define SOC_ASP_HIFI3_peripheralId0_peripheralId0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_peripheralId1_UNION
 �ṹ˵��  : peripheralId1 �Ĵ����ṹ���塣��ַƫ����:0x3FE4����ֵ:0x00000021�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId1 : 32; /* bit[0-31]: peripheralId1 */
    } reg;
} SOC_ASP_HIFI3_peripheralId1_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId1_peripheralId1_START  (0)
#define SOC_ASP_HIFI3_peripheralId1_peripheralId1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_peripheralId2_UNION
 �ṹ˵��  : peripheralId2 �Ĵ����ṹ���塣��ַƫ����:0x3FE8����ֵ:0x0000000F�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId2 : 32; /* bit[0-31]: peripheralId2 */
    } reg;
} SOC_ASP_HIFI3_peripheralId2_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId2_peripheralId2_START  (0)
#define SOC_ASP_HIFI3_peripheralId2_peripheralId2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_peripheralId3_UNION
 �ṹ˵��  : peripheralId3 �Ĵ����ṹ���塣��ַƫ����:0x3FEC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId3 : 32; /* bit[0-31]: peripheralId3 */
    } reg;
} SOC_ASP_HIFI3_peripheralId3_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId3_peripheralId3_START  (0)
#define SOC_ASP_HIFI3_peripheralId3_peripheralId3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_componentId0_UNION
 �ṹ˵��  : componentId0 �Ĵ����ṹ���塣��ַƫ����:0x3FF0����ֵ:0x0000000D�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  componentId0 : 32; /* bit[0-31]: componentId0 */
    } reg;
} SOC_ASP_HIFI3_componentId0_UNION;
#endif
#define SOC_ASP_HIFI3_componentId0_componentId0_START  (0)
#define SOC_ASP_HIFI3_componentId0_componentId0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_componentId1_UNION
 �ṹ˵��  : componentId1 �Ĵ����ṹ���塣��ַƫ����:0x3FF4����ֵ:0x00000090�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  componentId1 : 32; /* bit[0-31]: componentId1 */
    } reg;
} SOC_ASP_HIFI3_componentId1_UNION;
#endif
#define SOC_ASP_HIFI3_componentId1_componentId1_START  (0)
#define SOC_ASP_HIFI3_componentId1_componentId1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_componentId2_UNION
 �ṹ˵��  : componentId2 �Ĵ����ṹ���塣��ַƫ����:0x3FF8����ֵ:0x00000005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  componentId2 : 32; /* bit[0-31]: componentId2 */
    } reg;
} SOC_ASP_HIFI3_componentId2_UNION;
#endif
#define SOC_ASP_HIFI3_componentId2_componentId2_START  (0)
#define SOC_ASP_HIFI3_componentId2_componentId2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HIFI3_componentId3_UNION
 �ṹ˵��  : componentId3 �Ĵ����ṹ���塣��ַƫ����:0x3FFC����ֵ:0x000000B1�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  componentId3 : 32; /* bit[0-31]: componentId3 */
    } reg;
} SOC_ASP_HIFI3_componentId3_UNION;
#endif
#define SOC_ASP_HIFI3_componentId3_componentId3_START  (0)
#define SOC_ASP_HIFI3_componentId3_componentId3_END    (31)






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

#endif /* end of soc_asp_hifi3_interface.h */
