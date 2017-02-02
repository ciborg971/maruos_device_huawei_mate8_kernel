/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_modem_ipc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:20
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_MODEM_IPC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_MODEM_IPC_INTERFACE_H__
#define __SOC_MODEM_IPC_INTERFACE_H__

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
/* �Ĵ���˵����ģ��汾�Ĵ���
   λ����UNION�ṹ:  SOC_MODEM_IPC_IPC_VERSION_UNION */
#define SOC_MODEM_IPC_IPC_VERSION_ADDR(base)          ((base) + (0x000))

/* �Ĵ���˵���������ж�ԭʼ�жϼĴ���
   λ����UNION�ṹ:  SOC_MODEM_IPC_IPC_CPU_RAW_INT_UNION */
#define SOC_MODEM_IPC_IPC_CPU_RAW_INT_ADDR(base, i)   ((base) + (0x400+(i)*0x10))

/* �Ĵ���˵���������ж�����Ĵ���
   λ����UNION�ṹ:  SOC_MODEM_IPC_IPC_CPU_INT_MASK_UNION */
#define SOC_MODEM_IPC_IPC_CPU_INT_MASK_ADDR(base, i)  ((base) + (0x404+(i)*0x10))

/* �Ĵ���˵���������ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_MODEM_IPC_IPC_CPU_INT_STAT_UNION */
#define SOC_MODEM_IPC_IPC_CPU_INT_STAT_ADDR(base, i)  ((base) + (0x408+(i)*0x10))

/* �Ĵ���˵���������ж�����Ĵ���
   λ����UNION�ṹ:  SOC_MODEM_IPC_IPC_CPU_INT_CLR_UNION */
#define SOC_MODEM_IPC_IPC_CPU_INT_CLR_ADDR(base, i)   ((base) + (0x40C+(i)*0x10))

/* �Ĵ���˵�����ź����ͷ�ԭʼ�жϼĴ���
   λ����UNION�ṹ:  SOC_MODEM_IPC_IPC_SEM_RAW_INT_UNION */
#define SOC_MODEM_IPC_IPC_SEM_RAW_INT_ADDR(base, j)   ((base) + (0x600+(j)*0x10))

/* �Ĵ���˵�����ź����ͷ��ж�����Ĵ���
   λ����UNION�ṹ:  SOC_MODEM_IPC_IPC_SEM_INT_MASK_UNION */
#define SOC_MODEM_IPC_IPC_SEM_INT_MASK_ADDR(base, j)  ((base) + (0x604+(j)*0x10))

/* �Ĵ���˵�����ź����ͷ��ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_MODEM_IPC_IPC_SEM_INT_STAT_UNION */
#define SOC_MODEM_IPC_IPC_SEM_INT_STAT_ADDR(base, j)  ((base) + (0x608+(j)*0x10))

/* �Ĵ���˵�����ź����ͷ��ж�����Ĵ���
   λ����UNION�ṹ:  SOC_MODEM_IPC_IPC_SEM_INT_CLR_UNION */
#define SOC_MODEM_IPC_IPC_SEM_INT_CLR_ADDR(base, j)   ((base) + (0x60C+(j)*0x10))

/* �Ĵ���˵�����ź�������Ĵ���
   λ����UNION�ṹ:  SOC_MODEM_IPC_IPC_HS_CTRL_UNION */
#define SOC_MODEM_IPC_IPC_HS_CTRL_ADDR(base, j, k)    ((base) + (0x800+(j)*0x100+(k)*0x8))

/* �Ĵ���˵�����ź���״̬�Ĵ���
   λ����UNION�ṹ:  SOC_MODEM_IPC_IPC_HS_STAT_UNION */
#define SOC_MODEM_IPC_IPC_HS_STAT_ADDR(base, j, k)    ((base) + (0x804+(j)*0x100+(k)*0x8))





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
 �ṹ��    : SOC_MODEM_IPC_IPC_VERSION_UNION
 �ṹ˵��  : IPC_VERSION �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x67560100�����:32
 �Ĵ���˵��: ģ��汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_version : 32; /* bit[0-31]: IPC ģ��汾�Ĵ����� */
    } reg;
} SOC_MODEM_IPC_IPC_VERSION_UNION;
#endif
#define SOC_MODEM_IPC_IPC_VERSION_ipc_version_START  (0)
#define SOC_MODEM_IPC_IPC_VERSION_ipc_version_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_IPC_IPC_CPU_RAW_INT_UNION
 �ṹ˵��  : IPC_CPU_RAW_INT �Ĵ����ṹ���塣��ַƫ����:0x400+(i)*0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж�ԭʼ�жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_cpu_raw_int : 32; /* bit[0-31]: �����ж�ԭʼ�жϼĴ�������ַ[7:4]�������ֲ����жϵ��ź��ߡ�
                                                          ÿ1Bit����1��������ԭʼ�жϡ�д1�����жϣ�д0��Ч��
                                                          1'b0: ���жϣ�
                                                          1'b1: ���жϡ� */
    } reg;
} SOC_MODEM_IPC_IPC_CPU_RAW_INT_UNION;
#endif
#define SOC_MODEM_IPC_IPC_CPU_RAW_INT_ipc_cpu_raw_int_START  (0)
#define SOC_MODEM_IPC_IPC_CPU_RAW_INT_ipc_cpu_raw_int_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_IPC_IPC_CPU_INT_MASK_UNION
 �ṹ˵��  : IPC_CPU_INT_MASK �Ĵ����ṹ���塣��ַƫ����:0x404+(i)*0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_cpu_int_mask : 32; /* bit[0-31]: �����ж�����Ĵ����Ĵ�������ַ[7:4]�������ֲ����жϵ��ź��ߡ�
                                                           ÿ1Bit��Ӧ1���������ж����롣
                                                           1'b0: �ж����Σ�
                                                           1'b1: �ж�ʹ�ܡ� */
    } reg;
} SOC_MODEM_IPC_IPC_CPU_INT_MASK_UNION;
#endif
#define SOC_MODEM_IPC_IPC_CPU_INT_MASK_ipc_cpu_int_mask_START  (0)
#define SOC_MODEM_IPC_IPC_CPU_INT_MASK_ipc_cpu_int_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_IPC_IPC_CPU_INT_STAT_UNION
 �ṹ˵��  : IPC_CPU_INT_STAT �Ĵ����ṹ���塣��ַƫ����:0x408+(i)*0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_cpu_int_stat : 32; /* bit[0-31]: ���κ�Ŀ����ж�״̬�Ĵ�������ַ[7:4]�������ֲ����жϵ��ź��ߡ�
                                                           Ϊipc_cpu_raw_int��ipc_cpu_int_mask�İ�λ�롣
                                                           1'b0: ���жϣ�
                                                           1'b1: ���жϡ� */
    } reg;
} SOC_MODEM_IPC_IPC_CPU_INT_STAT_UNION;
#endif
#define SOC_MODEM_IPC_IPC_CPU_INT_STAT_ipc_cpu_int_stat_START  (0)
#define SOC_MODEM_IPC_IPC_CPU_INT_STAT_ipc_cpu_int_stat_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_IPC_IPC_CPU_INT_CLR_UNION
 �ṹ˵��  : IPC_CPU_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x40C+(i)*0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_cpu_int_clr : 32; /* bit[0-31]: �����ж�����Ĵ�������ַ[7:4]�������ֲ����жϵ��ź��ߡ�
                                                          ÿ1Bit��Ӧ1���������ж��������ĳBitд1'b1������ipc_cpu_raw_int�еĶ�ӦBit���㣬д1'b0��Ч�� */
    } reg;
} SOC_MODEM_IPC_IPC_CPU_INT_CLR_UNION;
#endif
#define SOC_MODEM_IPC_IPC_CPU_INT_CLR_ipc_cpu_int_clr_START  (0)
#define SOC_MODEM_IPC_IPC_CPU_INT_CLR_ipc_cpu_int_clr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_IPC_IPC_SEM_RAW_INT_UNION
 �ṹ˵��  : IPC_SEM_RAW_INT �Ĵ����ṹ���塣��ַƫ����:0x600+(j)*0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ź����ͷ�ԭʼ�жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_sem_raw_int : 32; /* bit[0-31]: �ź����ͷ�ԭʼ�жϡ���ַ[6:4]�������ֲ����жϵ��ź��ߡ�
                                                          ÿ1Bit����1��������ԭʼ�жϡ�
                                                          1'b0: ���жϣ�
                                                          1'b1: ���жϡ� */
    } reg;
} SOC_MODEM_IPC_IPC_SEM_RAW_INT_UNION;
#endif
#define SOC_MODEM_IPC_IPC_SEM_RAW_INT_ipc_sem_raw_int_START  (0)
#define SOC_MODEM_IPC_IPC_SEM_RAW_INT_ipc_sem_raw_int_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_IPC_IPC_SEM_INT_MASK_UNION
 �ṹ˵��  : IPC_SEM_INT_MASK �Ĵ����ṹ���塣��ַƫ����:0x604+(j)*0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ź����ͷ��ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_sem_int_mask : 32; /* bit[0-31]: �ź����ͷ��ж�����Ĵ�������ַ[6:4]�������ֲ����жϵ��ź��ߡ�
                                                           ÿ1Bit��Ӧ1���������ж����롣
                                                           1'b0: �ж����Σ�
                                                           1'b1: �ж�ʹ�ܡ� */
    } reg;
} SOC_MODEM_IPC_IPC_SEM_INT_MASK_UNION;
#endif
#define SOC_MODEM_IPC_IPC_SEM_INT_MASK_ipc_sem_int_mask_START  (0)
#define SOC_MODEM_IPC_IPC_SEM_INT_MASK_ipc_sem_int_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_IPC_IPC_SEM_INT_STAT_UNION
 �ṹ˵��  : IPC_SEM_INT_STAT �Ĵ����ṹ���塣��ַƫ����:0x608+(j)*0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ź����ͷ��ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_sem_int_stat : 32; /* bit[0-31]: ���κ���ź����ͷ��ж�״̬�Ĵ�������ַ[6:4]�������ֲ����жϵ��ź��ߡ�
                                                           Ϊipc_sem_raw_int��ipc_sem_int_mask�İ�λ�롣
                                                           1'b0: ���ж�
                                                           1'b1: ���ж� */
    } reg;
} SOC_MODEM_IPC_IPC_SEM_INT_STAT_UNION;
#endif
#define SOC_MODEM_IPC_IPC_SEM_INT_STAT_ipc_sem_int_stat_START  (0)
#define SOC_MODEM_IPC_IPC_SEM_INT_STAT_ipc_sem_int_stat_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_IPC_IPC_SEM_INT_CLR_UNION
 �ṹ˵��  : IPC_SEM_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x60C+(j)*0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ź����ͷ��ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_sem_int_clr : 32; /* bit[0-31]: �ź����ͷ��ж�����Ĵ�������ַ[6:4]�������ֲ����жϵ��ź��ߡ�
                                                          ÿ1Bit��Ӧ1���������ж��������ĳBitд1'b1������ipc_sem_raw_int�еĶ�ӦBit���㣬д1'b0��Ч�� */
    } reg;
} SOC_MODEM_IPC_IPC_SEM_INT_CLR_UNION;
#endif
#define SOC_MODEM_IPC_IPC_SEM_INT_CLR_ipc_sem_int_clr_START  (0)
#define SOC_MODEM_IPC_IPC_SEM_INT_CLR_ipc_sem_int_clr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_IPC_IPC_HS_CTRL_UNION
 �ṹ˵��  : IPC_HS_CTRL �Ĵ����ṹ���塣��ַƫ����:0x800+(j)*0x100+(k)*0x8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ź�������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hs_ctrl_id   : 3;  /* bit[0-2] : �ź���ռ�ô�����ID�Ĵ�������ַ[10:8]�������ֲ�ͬ�Ĵ��������ʡ�
                                                       ��������hs_ctrl_lock��Чʱ��hs_ctrl_id��ʾռ�и��ź����Ĵ�����ID�š� */
        unsigned int  hs_ctrl_lock : 1;  /* bit[3]   : �ź�������ռ�üĴ�������ַ[10:8]�������ֲ�ͬ�Ĵ��������ʡ�
                                                       ���üĴ���������1'b0��ʾ���ź���ռ�óɹ�������1'b1��ʾ���ź�������ռ��ʧ�ܡ�
                                                       д�üĴ�����д1'b0��ʾ�ͷŸ��ź�����д1'b1��Ч�� */
        unsigned int  reserved     : 28; /* bit[4-31]: ����λ�� */
    } reg;
} SOC_MODEM_IPC_IPC_HS_CTRL_UNION;
#endif
#define SOC_MODEM_IPC_IPC_HS_CTRL_hs_ctrl_id_START    (0)
#define SOC_MODEM_IPC_IPC_HS_CTRL_hs_ctrl_id_END      (2)
#define SOC_MODEM_IPC_IPC_HS_CTRL_hs_ctrl_lock_START  (3)
#define SOC_MODEM_IPC_IPC_HS_CTRL_hs_ctrl_lock_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_IPC_IPC_HS_STAT_UNION
 �ṹ˵��  : IPC_HS_STAT �Ĵ����ṹ���塣��ַƫ����:0x804+(j)*0x100+(k)*0x8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ź���״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hs_status_id   : 3;  /* bit[0-2] : �ź���ռ�ô�����ID�Ĵ�������ַ[10:8]�������ֲ�ͬ�Ĵ��������ʡ�
                                                         ��������hs_status_lock��Чʱ��hs_status_id��ʾռ�и��ź����Ĵ�����ID�š� */
        unsigned int  hs_status_lock : 1;  /* bit[3]   : �ź���ռ��״̬�Ĵ�������ַ[10:8]�������ֲ�ͬ�Ĵ��������ʡ�
                                                         ���üĴ���������1'b0��ʾ���ź������У�����1'b1��ʾ���ź����ѱ�ռ�á� */
        unsigned int  reserved       : 28; /* bit[4-31]: ����λ�� */
    } reg;
} SOC_MODEM_IPC_IPC_HS_STAT_UNION;
#endif
#define SOC_MODEM_IPC_IPC_HS_STAT_hs_status_id_START    (0)
#define SOC_MODEM_IPC_IPC_HS_STAT_hs_status_id_END      (2)
#define SOC_MODEM_IPC_IPC_HS_STAT_hs_status_lock_START  (3)
#define SOC_MODEM_IPC_IPC_HS_STAT_hs_status_lock_END    (3)






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

#endif /* end of soc_modem_ipc_interface.h */
