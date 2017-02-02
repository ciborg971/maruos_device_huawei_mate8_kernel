/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_cmd_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:19:59
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_CMD.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_CMD_INTERFACE_H__
#define __SOC_DSS_CMD_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_CMD
 ****************************************************************************/
/* �Ĵ���˵����CMDLISTͨ�����ƼĴ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_ADDR(base, i)  ((base) + (0x0000+0x40*(i)))

/* �Ĵ���˵����CMDLISTͨ�����ƼĴ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_CH_CTRL_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ADDR(base, i)     ((base) + (0x0004+0x40*(i)))

/* �Ĵ���˵����CMDLISTͨ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_CH_STATUS_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ADDR(base, i)   ((base) + (0x0008+0x40*(i)))

/* �Ĵ���˵����CMDLISTͨ����ʼ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_CH_STAAD_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_STAAD_ADDR(base, i)    ((base) + (0x000C+0x40*(i)))

/* �Ĵ���˵����CMDLISTͨ����ǰ����ڵ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_CH_CURAD_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_CURAD_ADDR(base, i)    ((base) + (0x0010+0x40*(i)))

/* �Ĵ���˵����CMDLISTͨ���ж�ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_CH_INTE_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ADDR(base, i)     ((base) + (0x0014+0x40*(i)))

/* �Ĵ���˵����CMDLISTͨ���ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_CH_INTC_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ADDR(base, i)     ((base) + (0x0018+0x40*(i)))

/* �Ĵ���˵����CMDLISTͨ���ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_CH_INTS_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ADDR(base, i)     ((base) + (0x001C+0x40*(i)))

/* �Ĵ���˵����CMDLISTͨ��debug�����Ĵ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_CH_PERF_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_PERF_ADDR(base, i)     ((base) + (0x0024+0x40*(i)))

/* �Ĵ���˵����DBG�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_CH_DBG_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_DBG_ADDR(base, i)      ((base) + (0x0028+0x40*(i)))

/* �Ĵ���˵����BUF DBGʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_DSS_CMD_BUF_DBG_EN_UNION */
#define SOC_DSS_CMD_BUF_DBG_EN_ADDR(base)             ((base) + (0x03F0))

/* �Ĵ���˵����BUF DBG��������Ĵ���
   λ����UNION�ṹ:  SOC_DSS_CMD_BUF_DBG_CNT_CLR_UNION */
#define SOC_DSS_CMD_BUF_DBG_CNT_CLR_ADDR(base)        ((base) + (0x03F4))

/* �Ĵ���˵����BUF DBG�����Ĵ���
   λ����UNION�ṹ:  SOC_DSS_CMD_BUF_DBG_CNT_UNION */
#define SOC_DSS_CMD_BUF_DBG_CNT_ADDR(base)            ((base) + (0x03F8))

/* �Ĵ���˵����CMDLIST��ʱ��ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_UNION */
#define SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_ADDR(base)     ((base) + (0x03FC))

/* �Ĵ���˵����CMDLISTͨ�������Ĵ���
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_START_UNION */
#define SOC_DSS_CMD_CMDLIST_START_ADDR(base)          ((base) + (0x0400))

/* �Ĵ���˵����CMDLISTͨ����ʼ��ַ���μĴ���
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_UNION */
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_ADDR(base) ((base) + (0x03E8))

/* �Ĵ���˵����CMDLISTͨ����ʼ��ַ���μĴ���
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_UNION */
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_ADDR(base)  ((base) + (0x03EC))

/* �Ĵ���˵����CMDLISTͨ����ʼ��ַ���μĴ���
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_UNION */
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_ADDR(base)   ((base) + (0x0404))

/* �Ĵ���˵����CMDLISTͨ����������Ĵ���
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_UNION */
#define SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_ADDR(base)  ((base) + (0x0408))

/* �Ĵ���˵����CMDLISTͨ������״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_TASK_STATUS_UNION */
#define SOC_DSS_CMD_CMDLIST_TASK_STATUS_ADDR(base)    ((base) + (0x040C))

/* �Ĵ���˵����CMDLIST���ƼĴ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_CTRL_UNION */
#define SOC_DSS_CMD_CMDLIST_CTRL_ADDR(base)           ((base) + (0x0410))

/* �Ĵ���˵����CMDLIST��ȫ���ԼĴ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_SECU_UNION */
#define SOC_DSS_CMD_CMDLIST_SECU_ADDR(base)           ((base) + (0x0414))

/* �Ĵ���˵����CMDLIST�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_INTS_UNION */
#define SOC_DSS_CMD_CMDLIST_INTS_ADDR(base)           ((base) + (0x0418))

/* �Ĵ���˵����CMDLIST�����λ�Ĵ�����
   λ����UNION�ṹ:  SOC_DSS_CMD_CMDLIST_SWRST_UNION */
#define SOC_DSS_CMD_CMDLIST_SWRST_ADDR(base)          ((base) + (0x041C))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ�����TP��
   λ����UNION�ṹ:  SOC_DSS_CMD_CMD_MEM_CTRL_UNION */
#define SOC_DSS_CMD_CMD_MEM_CTRL_ADDR(base)           ((base) + (0x0420))

/* �Ĵ���˵����һ��ģ��ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_CMD_CMD_CLK_SEL_UNION */
#define SOC_DSS_CMD_CMD_CLK_SEL_ADDR(base)            ((base) + (0x0428))

/* �Ĵ���˵����һ��ģ��ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_CMD_CMD_CLK_EN_UNION */
#define SOC_DSS_CMD_CMD_CLK_EN_ADDR(base)             ((base) + (0x042C))





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
                     (1/1) reg_CMD
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_UNION
 �ṹ˵��  : CMDLIST_CH_PENDING_CLR �Ĵ����ṹ���塣��ַƫ����:0x0000+0x40*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ�����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_pending_clr : 1;  /* bit[0]   : 1���˳�pending״̬ */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_ch_pending_clr_START  (0)
#define SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_ch_pending_clr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_CH_CTRL_UNION
 �ṹ˵��  : CMDLIST_CH_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0004+0x40*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ�����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_enable      : 1;  /* bit[0]   : 1��CMDLISTʹ��, 0: CMDLIST��ֹ. CMDLIST��ֹ��, �������ѷ���AXI������غ�,ͨ������IDLE״̬�� */
        unsigned int  ch_auto_single : 1;  /* bit[1]   : 0��Single Frame Updateģʽ
                                                         1�� Auto Refresh ģʽ */
        unsigned int  ch_start_sel   : 1;  /* bit[2]   : ��Auto Refreshģʽ����Ч
                                                         0��ѡ��ldi0������sync�ź���Ϊstart�ź�
                                                         1��ѡ��ldi1������sync�ź���Ϊstart�ź� */
        unsigned int  ch_pause       : 1;  /* bit[3]   : 1����ǰ����ڵ���ɺ���ִͣ�У���������λ�󣬼���ִ����������� */
        unsigned int  reserved       : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_CTRL_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_enable_START       (0)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_enable_END         (0)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_auto_single_START  (1)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_auto_single_END    (1)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_start_sel_START    (2)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_start_sel_END      (2)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_pause_START        (3)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_pause_END          (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_CH_STATUS_UNION
 �ṹ˵��  : CMDLIST_CH_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0008+0x40*(i)����ֵ:0x00000C00�����:32
 �Ĵ���˵��: CMDLISTͨ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_ctl_fsm     : 4;  /* bit[0-3]  : �ڲ�״̬������Ҫ��ע��������״̬��
                                                          0x0:idle״̬��
                                                          0x5:�ȴ�event_list��״̬��
                                                          0x7:pending״̬�� */
        unsigned int  ch_items_fsm   : 4;  /* bit[4-7]  : �ڲ�״̬��,����ʹ�� */
        unsigned int  ch_dma_fsm     : 2;  /* bit[8-9]  : �ڲ�״̬��,����ʹ�� */
        unsigned int  ch_idle        : 1;  /* bit[10]   : CMDLISTͨ����dmaģ��axi_idle */
        unsigned int  oa_idle        : 1;  /* bit[11]   : CMDͨ����ȫidle */
        unsigned int  ch_cmd_done_id : 10; /* bit[12-21]: ��ǰ��ɵ�����ڵ�ID */
        unsigned int  ch_cmd_id      : 10; /* bit[22-31]: ��ǰ����ڵ��ID */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_STATUS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_ctl_fsm_START      (0)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_ctl_fsm_END        (3)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_items_fsm_START    (4)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_items_fsm_END      (7)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_dma_fsm_START      (8)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_dma_fsm_END        (9)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_idle_START         (10)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_idle_END           (10)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_oa_idle_START         (11)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_oa_idle_END           (11)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_cmd_done_id_START  (12)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_cmd_done_id_END    (21)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_cmd_id_START       (22)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_cmd_id_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_CH_STAAD_UNION
 �ṹ˵��  : CMDLIST_CH_STAAD �Ĵ����ṹ���塣��ַƫ����:0x000C+0x40*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ����ʼ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 4;  /* bit[0-3] : ���� */
        unsigned int  ch_start_addr : 28; /* bit[4-31]: CMDLIST�������ʼʼ��ַ,128bit���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_STAAD_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_STAAD_ch_start_addr_START  (4)
#define SOC_DSS_CMD_CMDLIST_CH_STAAD_ch_start_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_CH_CURAD_UNION
 �ṹ˵��  : CMDLIST_CH_CURAD �Ĵ����ṹ���塣��ַƫ����:0x0010+0x40*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ����ǰ����ڵ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved     : 4;  /* bit[0-3] : ���� */
        unsigned int  ch_curr_addr : 28; /* bit[4-31]: CMDLIST��ǰִ������ĵ�ַ,128bit���룬DEBUG�� */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_CURAD_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_CURAD_ch_curr_addr_START  (4)
#define SOC_DSS_CMD_CMDLIST_CH_CURAD_ch_curr_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_CH_INTE_UNION
 �ṹ˵��  : CMDLIST_CH_INTE �Ĵ����ṹ���塣��ַƫ����:0x0014+0x40*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ���ж�ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_onedone_inte  : 1;  /* bit[0]   : 1: һ������ڵ��ж�����ж�ʹ��, 0: �жϽ�ֹ */
        unsigned int  ch_alldone_inte  : 1;  /* bit[1]   : 1: ��������ڵ��ж�����ж�ʹ��, 0: �жϽ�ֹ */
        unsigned int  ch_axi_err_inte  : 1;  /* bit[2]   : 1: AXI���߷��ش����ж�ʹ��, 0: �жϽ�ֹ */
        unsigned int  ch_pending_inte  : 1;  /* bit[3]   : 1: ����Pending״̬�ж�ʹ��, 0: �жϽ�ֹ */
        unsigned int  ch_start_inte    : 1;  /* bit[4]   : 1:��cmdlist��ʼִ��һ������ʱ,�ж�ʹ��, 0: �жϽ�ֹ */
        unsigned int  ch_badcmd_inte   : 1;  /* bit[5]   : 1:���������ʽ�ж�ʹ�� 0: �жϽ�ֹ */
        unsigned int  ch_timeout_inte  : 1;  /* bit[6]   : 1:timeout��ʱ�ж�ʹ�� 0: �жϽ�ֹ */
        unsigned int  ch_taskdone_inte : 1;  /* bit[7]   : 1:������������ж�ʹ�� 0: �жϽ�ֹ */
        unsigned int  reserved         : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_INTE_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_onedone_inte_START   (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_onedone_inte_END     (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_alldone_inte_START   (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_alldone_inte_END     (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_axi_err_inte_START   (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_axi_err_inte_END     (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_pending_inte_START   (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_pending_inte_END     (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_start_inte_START     (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_start_inte_END       (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_badcmd_inte_START    (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_badcmd_inte_END      (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_timeout_inte_START   (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_timeout_inte_END     (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_taskdone_inte_START  (7)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_taskdone_inte_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_CH_INTC_UNION
 �ṹ˵��  : CMDLIST_CH_INTC �Ĵ����ṹ���塣��ַƫ����:0x0018+0x40*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ���ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_onedone_intc  : 1;  /* bit[0]   : 1:�ж���� */
        unsigned int  ch_alldone_intc  : 1;  /* bit[1]   : 1:�ж���� */
        unsigned int  ch_axi_err_intc  : 1;  /* bit[2]   : 1:�ж���� */
        unsigned int  ch_pending_intc  : 1;  /* bit[3]   : 1:�ж���� */
        unsigned int  ch_start_intc    : 1;  /* bit[4]   : 1:�ж���� */
        unsigned int  ch_badcmd_intc   : 1;  /* bit[5]   : 1:�ж���� */
        unsigned int  ch_timeout_intc  : 1;  /* bit[6]   : 1:�ж���� */
        unsigned int  ch_taskdone_intc : 1;  /* bit[7]   : 1:�ж���� */
        unsigned int  reserved         : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_INTC_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_onedone_intc_START   (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_onedone_intc_END     (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_alldone_intc_START   (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_alldone_intc_END     (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_axi_err_intc_START   (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_axi_err_intc_END     (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_pending_intc_START   (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_pending_intc_END     (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_start_intc_START     (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_start_intc_END       (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_badcmd_intc_START    (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_badcmd_intc_END      (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_timeout_intc_START   (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_timeout_intc_END     (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_taskdone_intc_START  (7)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_taskdone_intc_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_CH_INTS_UNION
 �ṹ˵��  : CMDLIST_CH_INTS �Ĵ����ṹ���塣��ַƫ����:0x001C+0x40*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ���ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_onedone_ints  : 1;  /* bit[0]   : 1:�����ж�, 0:û���ж� */
        unsigned int  ch_alldone_ints  : 1;  /* bit[1]   : 1:�����ж�, 0:û���ж� */
        unsigned int  ch_axi_err_ints  : 1;  /* bit[2]   : 1:�����ж�, 0:û���ж� */
        unsigned int  ch_pending_ints  : 1;  /* bit[3]   : 1:�����ж�, 0:û���ж� */
        unsigned int  ch_start_ints    : 1;  /* bit[4]   : 1:�����ж�, 0:û���ж� */
        unsigned int  ch_badcmd_ints   : 1;  /* bit[5]   : 1:�����ж�, 0:û���ж� */
        unsigned int  ch_timeout_ints  : 1;  /* bit[6]   : 1:�����ж�, 0:û���ж� */
        unsigned int  ch_taskdone_ints : 1;  /* bit[7]   : 1:�����ж�, 0:û���ж� */
        unsigned int  reserved         : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_INTS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_onedone_ints_START   (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_onedone_ints_END     (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_alldone_ints_START   (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_alldone_ints_END     (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_axi_err_ints_START   (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_axi_err_ints_END     (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_pending_ints_START   (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_pending_ints_END     (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_start_ints_START     (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_start_ints_END       (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_badcmd_ints_START    (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_badcmd_ints_END      (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_timeout_ints_START   (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_timeout_ints_END     (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_taskdone_ints_START  (7)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_taskdone_ints_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_CH_PERF_UNION
 �ṹ˵��  : CMDLIST_CH_PERF �Ĵ����ṹ���塣��ַƫ����:0x0024+0x40*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ��debug�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_perf_cnt : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_PERF_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_PERF_ch_perf_cnt_START  (0)
#define SOC_DSS_CMD_CMDLIST_CH_PERF_ch_perf_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_CH_DBG_UNION
 �ṹ˵��  : CMDLIST_CH_DBG �Ĵ����ṹ���塣��ַƫ����:0x0028+0x40*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: DBG�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_dbg0 : 1;  /* bit[0]    : ���� */
        unsigned int  cmd_dbg1 : 1;  /* bit[1]    : ���� */
        unsigned int  cmd_dbg2 : 1;  /* bit[2]    : ���� */
        unsigned int  cmd_dbg3 : 1;  /* bit[3]    : ���� */
        unsigned int  cmd_dbg4 : 1;  /* bit[4]    : ���� */
        unsigned int  cmd_dbg5 : 1;  /* bit[5]    : ���� */
        unsigned int  cmd_dbg6 : 1;  /* bit[6]    : ���� */
        unsigned int  cmd_dbg7 : 1;  /* bit[7]    : ���� */
        unsigned int  cmd_dbg8 : 1;  /* bit[8]    : ���� */
        unsigned int  cmd_dbg9 : 1;  /* bit[9]    : ���� */
        unsigned int  reserved : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_DBG_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg0_START  (0)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg0_END    (0)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg1_START  (1)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg1_END    (1)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg2_START  (2)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg2_END    (2)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg3_START  (3)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg3_END    (3)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg4_START  (4)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg4_END    (4)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg5_START  (5)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg5_END    (5)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg6_START  (6)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg6_END    (6)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg7_START  (7)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg7_END    (7)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg8_START  (8)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg8_END    (8)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg9_START  (9)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg9_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_BUF_DBG_EN_UNION
 �ṹ˵��  : BUF_DBG_EN �Ĵ����ṹ���塣��ַƫ����:0x03F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: BUF DBGʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buf_dbg_en : 1;  /* bit[0]   : �����üĴ�����CMDLIST buf dbgʹ���źţ�ʹ��ʱCPU�ɶ���BUF���ݡ�
                                                     0: ��ʹ��
                                                     1: ʹ�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_CMD_BUF_DBG_EN_UNION;
#endif
#define SOC_DSS_CMD_BUF_DBG_EN_buf_dbg_en_START  (0)
#define SOC_DSS_CMD_BUF_DBG_EN_buf_dbg_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_BUF_DBG_CNT_CLR_UNION
 �ṹ˵��  : BUF_DBG_CNT_CLR �Ĵ����ṹ���塣��ַƫ����:0x03F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: BUF DBG��������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buf_dbg_cnt_clr : 1;  /* bit[0]   : �����üĴ�������Ӧtpram200x128
                                                          [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                          [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                          [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                          [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_CMD_BUF_DBG_CNT_CLR_UNION;
#endif
#define SOC_DSS_CMD_BUF_DBG_CNT_CLR_buf_dbg_cnt_clr_START  (0)
#define SOC_DSS_CMD_BUF_DBG_CNT_CLR_buf_dbg_cnt_clr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_BUF_DBG_CNT_UNION
 �ṹ˵��  : BUF_DBG_CNT �Ĵ����ṹ���塣��ַƫ����:0x03F8����ֵ:0x000000C8�����:32
 �Ĵ���˵��: BUF DBG�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buf_dbg_cnt_th : 8;  /* bit[0-7] : �����üĴ�����buf�����Ĵ�����Ĭ��ֵ����ΪMEM��ȡ� */
        unsigned int  reserved       : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_CMD_BUF_DBG_CNT_UNION;
#endif
#define SOC_DSS_CMD_BUF_DBG_CNT_buf_dbg_cnt_th_START  (0)
#define SOC_DSS_CMD_BUF_DBG_CNT_buf_dbg_cnt_th_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_UNION
 �ṹ˵��  : CMDLIST_TIMEOUT_TH �Ĵ����ṹ���塣��ַƫ����:0x03FC����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: CMDLIST��ʱ��ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeout_th : 32; /* bit[0-31]: CMDLISTͨ����ʱ�����Ĵ������������ﵽ������ֵʱtimeout�ж���Ч */
    } reg;
} SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_timeout_th_START  (0)
#define SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_timeout_th_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_START_UNION
 �ṹ˵��  : CMDLIST_START �Ĵ����ṹ���塣��ַƫ����:0x0400����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ�������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start    : 14; /* bit[0-13] : singleģʽ����Ч
                                                    bit0��ch0�������������źţ�
                                                    bit1��ch1�������������źţ�
                                                    bit2��ch2�������������źţ�
                                                    bit3��ch3�������������źţ�
                                                    bit4��ch4�������������źţ�
                                                    bit5��ch5�������������źţ�
                                                    bit6��ch6�������������źţ�
                                                    bit7��ch7�������������źţ�
                                                    bit8��ch8�������������źţ�
                                                    bit9��ch9�������������źţ�
                                                    bit10��ch10�������������źţ�
                                                    bit11��ch11�������������źţ�
                                                    bit12��ch12�������������źţ�
                                                    bit13��ch13�������������źţ� */
        unsigned int  reserved : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_START_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_START_start_START     (0)
#define SOC_DSS_CMD_CMDLIST_START_start_END       (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_UNION
 �ṹ˵��  : CMDLIST_ADDR_MASK_STATUS �Ĵ����ṹ���塣��ַƫ����:0x03E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ����ʼ��ַ���μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mask_status : 14; /* bit[0-13] : 1:��ʾ������ڸ�дstart_addr��Ӳ����ֹʹ��start_addr�Ĵ�����
                                                            0:��ʾ����Ѿ���д��start_addr��Ӳ������ʹ��start_addr��
                                                            bit1��ch1��ʼ��ַ���Σ�
                                                            bit2��ch2��ʼ��ַ���Σ�
                                                            bit3��ch3��ʼ��ַ���Σ�
                                                            bit4��ch4��ʼ��ַ���Σ�
                                                            bit5��ch5��ʼ��ַ���Σ�
                                                            bit6��ch6��ʼ��ַ���Σ�
                                                            bit7��ch7��ʼ��ַ���Σ�
                                                            bit8��ch8��ʼ��ַ���Σ�
                                                            bit9��ch9��ʼ��ַ���Σ�
                                                            bit10��ch10��ʼ��ַ���Σ�
                                                            bit11��ch11��ʼ��ַ���Σ�
                                                            bit12��ch12��ʼ��ַ���Σ�
                                                            bit13��ch13��ʼ��ַ���Σ� */
        unsigned int  reserved         : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_addr_mask_status_START  (0)
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_addr_mask_status_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_UNION
 �ṹ˵��  : CMDLIST_ADDR_MASK_DIS �Ĵ����ṹ���塣��ַƫ����:0x03EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ����ʼ��ַ���μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mask_dis : 14; /* bit[0-13] : ������øüĴ���ʱ������Ҫ�Ȼض���ֱ�����ö�Ӧbit���ɣ�
                                                         1:��ʾ����Ѿ���д��start_addr��Ӳ������ʹ��start_addr�Ĵ�����
                                                         0:��ʾ��bit��Ч�������κ����ã�
                                                         bit0��ch0��ʼ��ַ�����Σ�
                                                         bit1��ch1��ʼ��ַ�����Σ�
                                                         bit2��ch2��ʼ��ַ�����Σ�
                                                         bit3��ch3��ʼ��ַ�����Σ�
                                                         bit4��ch4��ʼ��ַ�����Σ�
                                                         bit5��ch5��ʼ��ַ�����Σ�
                                                         bit6��ch6��ʼ��ַ�����Σ�
                                                         bit7��ch7��ʼ��ַ�����Σ�
                                                         bit8��ch8��ʼ��ַ�����Σ�
                                                         bit9��ch9��ʼ��ַ�����Σ�
                                                         bit10��ch10��ʼ��ַ�����Σ�
                                                         bit11��ch11��ʼ��ַ�����Σ�
                                                         bit12��ch12��ʼ��ַ�����Σ�
                                                         bit13��ch13��ʼ��ַ�����Σ� */
        unsigned int  reserved      : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_addr_mask_dis_START  (0)
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_addr_mask_dis_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_UNION
 �ṹ˵��  : CMDLIST_ADDR_MASK_EN �Ĵ����ṹ���塣��ַƫ����:0x0404����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ����ʼ��ַ���μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mask_en : 14; /* bit[0-13] : ������øüĴ���ʱ������Ҫ�Ȼض���ֱ�����ö�Ӧbit���ɣ�
                                                        1:��ʾ������ڸ�дstart_addr��Ӳ����ֹʹ��start_addr�Ĵ�����
                                                        0:��ʾ��bit��Ч�������κ����ã�
                                                        bit0��ch0��ʼ��ַ���Σ�
                                                        bit1��ch1��ʼ��ַ���Σ�
                                                        bit2��ch2��ʼ��ַ���Σ�
                                                        bit3��ch3��ʼ��ַ���Σ�
                                                        bit4��ch4��ʼ��ַ���Σ�
                                                        bit5��ch5��ʼ��ַ���Σ�
                                                        bit6��ch6��ʼ��ַ���Σ�
                                                        bit7��ch7��ʼ��ַ���Σ�
                                                        bit8��ch8��ʼ��ַ���Σ�
                                                        bit9��ch9��ʼ��ַ���Σ�
                                                        bit10��ch10��ʼ��ַ���Σ�
                                                        bit11��ch11��ʼ��ַ���Σ�
                                                        bit12��ch12��ʼ��ַ���Σ�
                                                        bit13��ch13��ʼ��ַ���Σ� */
        unsigned int  reserved     : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_addr_mask_en_START  (0)
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_addr_mask_en_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_UNION
 �ṹ˵��  : CMDLIST_TASK_CONTINUE �Ĵ����ṹ���塣��ַƫ����:0x0408����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ����������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  task_continue : 14; /* bit[0-13] : ������øüĴ���ʱ������Ҫ�Ȼض���ֱ�����ö�Ӧbit���ɣ�
                                                         1:��ʾ���׼���������񣬿��Լ�����������cmdlist����Ҫ���¿�ʼ������
                                                         0:��ʾ��bit��Ч�������κ����ã�
                                                         bit0��ch0���������־λ��
                                                         bit1��ch1���������־λ��
                                                         bit2��ch2���������־λ��
                                                         bit3��ch3���������־λ��
                                                         bit4��ch4���������־λ��
                                                         bit5��ch5���������־λ��
                                                         bit6��ch6���������־λ��
                                                         bit7��ch7���������־λ��
                                                         bit8��ch8���������־λ��
                                                         bit9��ch9���������־λ��
                                                         bit10��ch10���������־λ��
                                                         bit11��ch11���������־λ��
                                                         bit12��ch12���������־λ��
                                                         bit13��ch13���������־λ�� */
        unsigned int  reserved      : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_task_continue_START  (0)
#define SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_task_continue_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_TASK_STATUS_UNION
 �ṹ˵��  : CMDLIST_TASK_STATUS �Ĵ����ṹ���塣��ַƫ����:0x040C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLISTͨ������״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  task_status : 14; /* bit[0-13] : 1:��ǰ��������û�б�CMDͨ������;
                                                       0:��ǰû����������ҪCMDͨ������;
                                                       bit0��ch0����״̬��־λ��
                                                       bit1��ch1����״̬��־λ��
                                                       bit2��ch2����״̬��־λ��
                                                       bit3��ch3����״̬��־λ��
                                                       bit4��ch4����״̬��־λ��
                                                       bit5��ch5����״̬��־λ��
                                                       bit6��ch6����״̬��־λ��
                                                       bit7��ch7����״̬��־λ��
                                                       bit8��ch8����״̬��־λ��
                                                       bit9��ch9����״̬��־λ��
                                                       bit10��ch10����״̬��־λ��
                                                       bit11��ch11����״̬��־λ��
                                                       bit12��ch12����״̬��־λ��
                                                       bit13��ch13����״̬��־λ�� */
        unsigned int  reserved    : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_TASK_STATUS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_TASK_STATUS_task_status_START  (0)
#define SOC_DSS_CMD_CMDLIST_TASK_STATUS_task_status_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_CTRL_UNION
 �ṹ˵��  : CMDLIST_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0410����ֵ:0x00000400�����:32
 �Ĵ���˵��: CMDLIST���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_mid          : 4;  /* bit[0-3]  : side band signal for priority arbitration */
        unsigned int  axi_qos          : 2;  /* bit[4-5]  : forced qos value, axi_qos[1] = ctl_online, axi_qos[0]=ctl_qos.1��ʾ���ȼ���,0:��ʾ���ȼ��� */
        unsigned int  axi_mainpress    : 2;  /* bit[6-7]  : forced mainpress value, axi_mainpress[1]=ctl_online, axi_mainpress[0]=prirority. 1��ʾ���ȼ���,0:��ʾ���ȼ��� */
        unsigned int  axi_outstd_depth : 4;  /* bit[8-11] : outstanding��ȣ����䷶ΧΪ1~8��Ĭ������Ϊ4 */
        unsigned int  reserved         : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_CTRL_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_mid_START           (0)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_mid_END             (3)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_qos_START           (4)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_qos_END             (5)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_mainpress_START     (6)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_mainpress_END       (7)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_outstd_depth_START  (8)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_outstd_depth_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_SECU_UNION
 �ṹ˵��  : CMDLIST_SECU �Ĵ����ṹ���塣��ַƫ����:0x0414����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLIST��ȫ���ԼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_secu  : 14; /* bit[0-13] : CMDLISTͨ����ʼ��ַ�Ĵ�������ʼ��ַ�Ĵ�����ȫ���ԡ�1: ��ȫ, 0: �ǰ�ȫ
                                                    bit0��ch0��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit1��ch1��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit2��ch2��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit3��ch3��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit4��ch4��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit5��ch5��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit6��ch6��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit7��ch7��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit8��ch8��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit9��ch9��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit10��ch10��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit11��ch11��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit12��ch12��ʼ��ַ�Ĵ�����ȫ���ԣ�
                                                    bit13��ch13��ʼ��ַ�Ĵ�����ȫ���ԣ� */
        unsigned int  reserved : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_SECU_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_SECU_ch_secu_START   (0)
#define SOC_DSS_CMD_CMDLIST_SECU_ch_secu_END     (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_INTS_UNION
 �ṹ˵��  : CMDLIST_INTS �Ĵ����ṹ���塣��ַƫ����:0x0418����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLIST�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_ints  : 14; /* bit[0-13] : CMDLISTͨ���ж�״̬��1:�ж���Ч, 0: �ж���Ч
                                                    bit0��ch0�ж�״̬��
                                                    bit1��ch1�ж�״̬��
                                                    bit2��ch2�ж�״̬��
                                                    bit3��ch3�ж�״̬��
                                                    bit4��ch4�ж�״̬��
                                                    bit5��ch5�ж�״̬��
                                                    bit6��ch6�ж�״̬��
                                                    bit7��ch7�ж�״̬��
                                                    bit8��ch8�ж�״̬��
                                                    bit9��ch9�ж�״̬��
                                                    bit10��ch10�ж�״̬��
                                                    bit11��ch11�ж�״̬��
                                                    bit12��ch12�ж�״̬��
                                                    bit13��ch13�ж�״̬�� */
        unsigned int  reserved : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_INTS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_INTS_ch_ints_START   (0)
#define SOC_DSS_CMD_CMDLIST_INTS_ch_ints_END     (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMDLIST_SWRST_UNION
 �ṹ˵��  : CMDLIST_SWRST �Ĵ����ṹ���塣��ַƫ����:0x041C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDLIST�����λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_swreset : 14; /* bit[0-13] : CMDLISTͨ�������λ�������λ��.�����ѷ���AXI��������ݷ��غ�,ͨ������IDLE״̬��
                                                      bit0��ch0�����λ��
                                                      bit1��ch1�����λ��
                                                      bit2��ch2�����λ��
                                                      bit3��ch3�����λ��
                                                      bit4��ch4�����λ��
                                                      bit5��ch5�����λ��
                                                      bit6��ch6�����λ��
                                                      bit7��ch7�����λ��
                                                      bit8��ch8�����λ��
                                                      bit9��ch9�����λ��
                                                      bit10��ch10�����λ��
                                                      bit11��ch11�����λ��
                                                      bit12��ch12�����λ��
                                                      bit13��ch13�����λ�� */
        unsigned int  reserved   : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMDLIST_SWRST_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_SWRST_ch_swreset_START  (0)
#define SOC_DSS_CMD_CMDLIST_SWRST_ch_swreset_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMD_MEM_CTRL_UNION
 �ṹ˵��  : CMD_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0420����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ�����TP��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_mem_ctrl : 4;  /* bit[0-3] : �����üĴ�������Ӧtpram200x128
                                                       [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                       [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                       [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                       [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved     : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_CMD_CMD_MEM_CTRL_UNION;
#endif
#define SOC_DSS_CMD_CMD_MEM_CTRL_cmd_mem_ctrl_START  (0)
#define SOC_DSS_CMD_CMD_MEM_CTRL_cmd_mem_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMD_CLK_SEL_UNION
 �ṹ˵��  : CMD_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0428����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                      1����ʾǿ�ƴ�ʱ�ӡ�
                                                      0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                      bit0������apb��
                                                      bit1������cmd�߼���
                                                      bit2��reserved��
                                                      bit3������reg��
                                                      bit4������ch0��
                                                      bit5������ch1��
                                                      bit6������ch2��
                                                      bit7������ch3��
                                                      bit8������ch4��
                                                      bit9������ch5��
                                                      bit10������ch6��
                                                      bit11������ch7��
                                                      bit12������ch8��
                                                      bit13������ch9��
                                                      bit14������ch10��
                                                      bit15������ch11��
                                                      bit16������ch12��
                                                      bit17������ch13�� */
    } reg;
} SOC_DSS_CMD_CMD_CLK_SEL_UNION;
#endif
#define SOC_DSS_CMD_CMD_CLK_SEL_cmd_clk_sel_START  (0)
#define SOC_DSS_CMD_CMD_CLK_SEL_cmd_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_CMD_CMD_CLK_EN_UNION
 �ṹ˵��  : CMD_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x042C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                     1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                     0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                     bit0��reserved��
                                                     bit1������cmd�߼���
                                                     bit2��reserved��
                                                     bit3������reg��
                                                     bit4������ch0��
                                                     bit5������ch1��
                                                     bit6������ch2��
                                                     bit7������ch3��
                                                     bit8������ch4��
                                                     bit9������ch5��
                                                     bit10������ch6��
                                                     bit11������ch7��
                                                     bit12������ch8��
                                                     bit13������ch9��
                                                     bit14������ch10��
                                                     bit15������ch11��
                                                     bit16������ch12��
                                                     bit17������ch13�� */
    } reg;
} SOC_DSS_CMD_CMD_CLK_EN_UNION;
#endif
#define SOC_DSS_CMD_CMD_CLK_EN_cmd_clk_en_START  (0)
#define SOC_DSS_CMD_CMD_CLK_EN_cmd_clk_en_END    (31)






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

#endif /* end of soc_dss_cmd_interface.h */
