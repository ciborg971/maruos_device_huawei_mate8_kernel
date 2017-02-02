/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_ipc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:21:48
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_IPC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_IPC_INTERFACE_H__
#define __SOC_ISP_IPC_INTERFACE_H__

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
/* �Ĵ���˵����Դ���������üĴ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_SOURCE_UNION */
#define SOC_ISP_IPC_MBX_SOURCE_ADDR(base, i)          ((base) + (0x000+(i)*64))

/* �Ĵ���˵����Ŀ�Ĵ��������üĴ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_DSET_UNION */
#define SOC_ISP_IPC_MBX_DSET_ADDR(base, i)            ((base) + (0x004+(i)*64))

/* �Ĵ���˵����Ŀ�Ĵ���������Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_DCLEAR_UNION */
#define SOC_ISP_IPC_MBX_DCLEAR_ADDR(base, i)          ((base) + (0x008+(i)*64))

/* �Ĵ���˵����Ŀ�Ĵ�����״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_DSTATUS_UNION */
#define SOC_ISP_IPC_MBX_DSTATUS_ADDR(base, i)         ((base) + (0x00C+(i)*64))

/* �Ĵ���˵��������ͨ��ģʽ״̬��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_MODE_UNION */
#define SOC_ISP_IPC_MBX_MODE_ADDR(base, i)            ((base) + (0x010+(i)*64))

/* �Ĵ���˵�����������ж����μĴ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_IMASK_UNION */
#define SOC_ISP_IPC_MBX_IMASK_ADDR(base, i)           ((base) + (0x014+(i)*64))

/* �Ĵ���˵�����������ж�״̬����Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_ICLR_UNION */
#define SOC_ISP_IPC_MBX_ICLR_ADDR(base, i)            ((base) + (0x018+(i)*64))

/* �Ĵ���˵�������ͼĴ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_SEND_UNION */
#define SOC_ISP_IPC_MBX_SEND_ADDR(base, i)            ((base) + (0x01C+(i)*64))

/* �Ĵ���˵��������0�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_DATA0_UNION */
#define SOC_ISP_IPC_MBX_DATA0_ADDR(base, i)           ((base) + (0x020+(i)*64))

/* �Ĵ���˵��������1�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_DATA1_UNION */
#define SOC_ISP_IPC_MBX_DATA1_ADDR(base, i)           ((base) + (0x024+(i)*64))

/* �Ĵ���˵��������2�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_DATA2_UNION */
#define SOC_ISP_IPC_MBX_DATA2_ADDR(base, i)           ((base) + (0x028+(i)*64))

/* �Ĵ���˵��������3�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_DATA3_UNION */
#define SOC_ISP_IPC_MBX_DATA3_ADDR(base, i)           ((base) + (0x02C+(i)*64))

/* �Ĵ���˵��������4�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_DATA4_UNION */
#define SOC_ISP_IPC_MBX_DATA4_ADDR(base, i)           ((base) + (0x030+(i)*64))

/* �Ĵ���˵��������5�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_DATA5_UNION */
#define SOC_ISP_IPC_MBX_DATA5_ADDR(base, i)           ((base) + (0x034+(i)*64))

/* �Ĵ���˵��������6�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_DATA6_UNION */
#define SOC_ISP_IPC_MBX_DATA6_ADDR(base, i)           ((base) + (0x038+(i)*64))

/* �Ĵ���˵��������7�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_MBX_DATA7_UNION */
#define SOC_ISP_IPC_MBX_DATA7_ADDR(base, i)           ((base) + (0x03C+(i)*64))

/* �Ĵ���˵�����ж�����״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_CPU_IMST_UNION */
#define SOC_ISP_IPC_CPU_IMST_ADDR(base, j)            ((base) + (0x800+(j)*8))

/* �Ĵ���˵�����ж�ԭʼ״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_CPU_IRST_UNION */
#define SOC_ISP_IPC_CPU_IRST_ADDR(base, j)            ((base) + (0x804+(j)*8))

/* �Ĵ���˵������Чͨ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_IPC_MBX_ACTIVE_UNION */
#define SOC_ISP_IPC_IPC_MBX_ACTIVE_ADDR(base)         ((base) + (0x900))

/* �Ĵ���˵�����͹���״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_IPC_LP_STATE_UNION */
#define SOC_ISP_IPC_IPC_LP_STATE_ADDR(base)           ((base) + (0x904))

/* �Ĵ���˵����IPC lock�Ĵ�����
   λ����UNION�ṹ:  SOC_ISP_IPC_IPC_LOCK_UNION */
#define SOC_ISP_IPC_IPC_LOCK_ADDR(base)               ((base) + (0xA00))





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
 �ṹ��    : SOC_ISP_IPC_MBX_SOURCE_UNION
 �ṹ˵��  : MBX_SOURCE �Ĵ����ṹ���塣��ַƫ����:0x000+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: Դ���������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  source   : 3;  /* bit[0-2] : ����ͨ��ռ��Դ���������ã������ö����������ͬռ�ô�����ͨ����ÿһbit��Ӧһ��ռ��ͨ���Ĵ�������
                                                   ���ú�д��ֵͬ�ͷŸ�ͨ�����䣬����������ݼĴ�����ģʽ�Ĵ���֮��ļĴ�������0�����ú�д����ֵ�����塣
                                                   λ����궨��IPC_CPU_NUMһ�¡�(SDRV200Ϊ3)
                                                   ��MBX_SOURCE�Ĵ���Ϊ��0ֵʱ����MBX_DCLEAR�Ĵ�����MBX_DSET�Ĵ�����MBX_MODE�Ĵ�����MBX_IMASK�Ĵ�����MBX_SEND�Ĵ������Խ�����Чд�����������޷�д�롣�����Ĵ������ܴ����ơ� */
        unsigned int  reserved : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_ISP_IPC_MBX_SOURCE_UNION;
#endif
#define SOC_ISP_IPC_MBX_SOURCE_source_START    (0)
#define SOC_ISP_IPC_MBX_SOURCE_source_END      (2)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_DSET_UNION
 �ṹ˵��  : MBX_DSET �Ĵ����ṹ���塣��ַƫ����:0x004+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ŀ�Ĵ��������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dset     : 3;  /* bit[0-2] : ����ͨ��Ŀ�Ĵ��������üĴ�������ͨ���жϵĽ��մ��������ã������ö��������ͬʱ�����жϣ�ÿһbit��Ӧһ����������
                                                   0����Ӱ�죻
                                                   1������ΪĿ�Ĵ�������
                                                   λ����궨��IPC_CPU_NUMһ�¡�(SDRV200Ϊ3) */
        unsigned int  reserved : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_ISP_IPC_MBX_DSET_UNION;
#endif
#define SOC_ISP_IPC_MBX_DSET_dset_START      (0)
#define SOC_ISP_IPC_MBX_DSET_dset_END        (2)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_DCLEAR_UNION
 �ṹ˵��  : MBX_DCLEAR �Ĵ����ṹ���塣��ַƫ����:0x008+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ŀ�Ĵ���������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dclear   : 3;  /* bit[0-2] : ����ͨ��Ŀ�Ĵ���������Ĵ�����ÿһbit��Ӧһ����������
                                                   0����Ӱ�죻
                                                   1�������
                                                   λ����궨��IPC_CPU_NUMһ�¡�(SDRV200Ϊ3) */
        unsigned int  reserved : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_ISP_IPC_MBX_DCLEAR_UNION;
#endif
#define SOC_ISP_IPC_MBX_DCLEAR_dclear_START    (0)
#define SOC_ISP_IPC_MBX_DCLEAR_dclear_END      (2)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_DSTATUS_UNION
 �ṹ˵��  : MBX_DSTATUS �Ĵ����ṹ���塣��ַƫ����:0x00C+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ŀ�Ĵ�����״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dstatus  : 3;  /* bit[0-2] : ����ͨ��Ŀ�Ĵ�����״̬�Ĵ�����ÿһbit��Ӧһ���������� λ����궨��IPC_CPU_NUMһ�¡�(SDRV200Ϊ3) */
        unsigned int  reserved : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_ISP_IPC_MBX_DSTATUS_UNION;
#endif
#define SOC_ISP_IPC_MBX_DSTATUS_dstatus_START   (0)
#define SOC_ISP_IPC_MBX_DSTATUS_dstatus_END     (2)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_MODE_UNION
 �ṹ˵��  : MBX_MODE �Ĵ����ṹ���塣��ַƫ����:0x010+(i)*64����ֵ:0x00000010�����:32
 �Ĵ���˵��: ����ͨ��ģʽ״̬��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  auto_answer  : 1;  /* bit[0]   : Mailbox�Զ�Ӧ��ʹ�ܡ�
                                                       �Զ�Ӧ�𣬼���Ŀ�Ĵ������жϱ����0��mailbox�Զ�����һ���ظ��жϸ�Դ��������
                                                       0����ֹ��
                                                       1��ʹ�ܡ� */
        unsigned int  auto_link    : 1;  /* bit[1]   : Mailbox�Զ�����ʹ�ܡ�
                                                       �Զ����ӣ��������ٽ���Mailboxes������һ�𣬴Ӷ����Խ������Ϣ�����ķ��ͳ�ȥ��������Ҫ����Ϣ����Ϣ֮�䷢���жϸ�Դ����������������Ϣ���Ѿ�������ϣ�Ӧ���жϿ�����һ��Ŀ�Ĵ��������ò�����Ҳ����ͨ���Զ�Ӧ��ģʽ������������˳���ǹ̶��ģ�Mailbox 0 ���ӵ� Mailbox 1 ��������ߵ����һ�����䣬���һ��������Զ����ӹ���������Ч��
                                                       0����ֹ��
                                                       1��ʹ�ܡ� */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : reserved */
        unsigned int  state_status : 4;  /* bit[4-7] : ״̬��״̬��
                                                       4'b0001 ����״̬��������У�
                                                       4'b0010 Դ״̬����״̬�£�����ͨ����ռ�ã���δ���жϸ�Ŀ�Ĵ�������
                                                       4'b0100 Ŀ��״̬����״̬�£�Ŀ�Ĵ������յ�Դ���жϣ�δȫ������򷵻�Ӧ���жϡ�
                                                       4'b1000 Ӧ��״̬����״̬�£�Դ�յ�Ӧ���ж�δ�����ϡ�
                                                       �������쳣ֵ */
        unsigned int  reserved_1   : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_ISP_IPC_MBX_MODE_UNION;
#endif
#define SOC_ISP_IPC_MBX_MODE_auto_answer_START   (0)
#define SOC_ISP_IPC_MBX_MODE_auto_answer_END     (0)
#define SOC_ISP_IPC_MBX_MODE_auto_link_START     (1)
#define SOC_ISP_IPC_MBX_MODE_auto_link_END       (1)
#define SOC_ISP_IPC_MBX_MODE_state_status_START  (4)
#define SOC_ISP_IPC_MBX_MODE_state_status_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_IMASK_UNION
 �ṹ˵��  : MBX_IMASK �Ĵ����ṹ���塣��ַƫ����:0x014+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_mask : 3;  /* bit[0-2] : ����ͨ�������������ж��������ã�ÿһbit��Ӧһ����������
                                                   0�������Σ�
                                                   1�����Ρ�
                                                   λ����궨��IPC_CPU_NUMһ�¡�(SDRV200Ϊ3) */
        unsigned int  reserved : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_ISP_IPC_MBX_IMASK_UNION;
#endif
#define SOC_ISP_IPC_MBX_IMASK_int_mask_START  (0)
#define SOC_ISP_IPC_MBX_IMASK_int_mask_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_ICLR_UNION
 �ṹ˵��  : MBX_ICLR �Ĵ����ṹ���塣��ַƫ����:0x018+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ж�״̬����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_clear : 3;  /* bit[0-2] : ����ͨ�������������κ��ж�״̬��ÿһbit��Ӧһ����������д1�����
                                                    0�����жϣ�
                                                    1�����жϡ�
                                                    λ����궨��IPC_CPU_NUMһ�¡�(SDRV200Ϊ3) */
        unsigned int  reserved  : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_ISP_IPC_MBX_ICLR_UNION;
#endif
#define SOC_ISP_IPC_MBX_ICLR_int_clear_START  (0)
#define SOC_ISP_IPC_MBX_ICLR_int_clear_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_SEND_UNION
 �ṹ˵��  : MBX_SEND �Ĵ����ṹ���塣��ַƫ����:0x01C+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ͼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  send     : 3;  /* bit[0-2] : �жϷ��ͼĴ�����ÿһbit��Ӧһ����������ͨ�Ź����У����ô˼Ĵ�����ֻ��λbit��Ч��
                                                   ��Դ���жϸ�Ŀ��ʱ��send�Ĵ�������ֵ��Դ�Ĵ���ֵ���ʱ���жϸ�Ŀ�Ĵ���������Ŀ�ķ�Ӧ���жϸ�Դʱ��send�Ĵ�������ֵ��Ŀ�����ʱ��Ӧ���жϸ�Դ���Զ�����ʱ������������˼Ĵ����������ã��Զ�Ӧ��ʱ��Ŀ������жϺ󣬴˼Ĵ����Զ���λ���������á�
                                                   λ����궨��IPC_CPU_NUMһ�¡�(SDRV200Ϊ3) */
        unsigned int  reserved : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_ISP_IPC_MBX_SEND_UNION;
#endif
#define SOC_ISP_IPC_MBX_SEND_send_START      (0)
#define SOC_ISP_IPC_MBX_SEND_send_END        (2)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_DATA0_UNION
 �ṹ˵��  : MBX_DATA0 �Ĵ����ṹ���塣��ַƫ����:0x020+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data0 : 32; /* bit[0-31]: ����ͨ�����ݼĴ���0 */
    } reg;
} SOC_ISP_IPC_MBX_DATA0_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA0_data0_START  (0)
#define SOC_ISP_IPC_MBX_DATA0_data0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_DATA1_UNION
 �ṹ˵��  : MBX_DATA1 �Ĵ����ṹ���塣��ַƫ����:0x024+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data1 : 32; /* bit[0-31]: ����ͨ�����ݼĴ���1 */
    } reg;
} SOC_ISP_IPC_MBX_DATA1_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA1_data1_START  (0)
#define SOC_ISP_IPC_MBX_DATA1_data1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_DATA2_UNION
 �ṹ˵��  : MBX_DATA2 �Ĵ����ṹ���塣��ַƫ����:0x028+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data2 : 32; /* bit[0-31]: ����ͨ�����ݼĴ���2 */
    } reg;
} SOC_ISP_IPC_MBX_DATA2_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA2_data2_START  (0)
#define SOC_ISP_IPC_MBX_DATA2_data2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_DATA3_UNION
 �ṹ˵��  : MBX_DATA3 �Ĵ����ṹ���塣��ַƫ����:0x02C+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����3�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data3 : 32; /* bit[0-31]: ����ͨ�����ݼĴ���3 */
    } reg;
} SOC_ISP_IPC_MBX_DATA3_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA3_data3_START  (0)
#define SOC_ISP_IPC_MBX_DATA3_data3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_DATA4_UNION
 �ṹ˵��  : MBX_DATA4 �Ĵ����ṹ���塣��ַƫ����:0x030+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����4�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data4 : 32; /* bit[0-31]: ����ͨ�����ݼĴ���4 */
    } reg;
} SOC_ISP_IPC_MBX_DATA4_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA4_data4_START  (0)
#define SOC_ISP_IPC_MBX_DATA4_data4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_DATA5_UNION
 �ṹ˵��  : MBX_DATA5 �Ĵ����ṹ���塣��ַƫ����:0x034+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����5�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data5 : 32; /* bit[0-31]: ����ͨ�����ݼĴ���5 */
    } reg;
} SOC_ISP_IPC_MBX_DATA5_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA5_data5_START  (0)
#define SOC_ISP_IPC_MBX_DATA5_data5_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_DATA6_UNION
 �ṹ˵��  : MBX_DATA6 �Ĵ����ṹ���塣��ַƫ����:0x038+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����6�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data6 : 32; /* bit[0-31]: ����ͨ�����ݼĴ���6 */
    } reg;
} SOC_ISP_IPC_MBX_DATA6_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA6_data6_START  (0)
#define SOC_ISP_IPC_MBX_DATA6_data6_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_MBX_DATA7_UNION
 �ṹ˵��  : MBX_DATA7 �Ĵ����ṹ���塣��ַƫ����:0x03C+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����7�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data7 : 32; /* bit[0-31]: ����ͨ�����ݼĴ���7 */
    } reg;
} SOC_ISP_IPC_MBX_DATA7_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA7_data7_START  (0)
#define SOC_ISP_IPC_MBX_DATA7_data7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_CPU_IMST_UNION
 �ṹ˵��  : CPU_IMST �Ĵ����ṹ���塣��ַƫ����:0x800+(j)*8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_mask_status : 16; /* bit[0-15] : ������j���κ���ж�״̬�Ĵ�����ÿ��bit��Ӧһ������ͨ����
                                                           0�����жϣ�
                                                           1�����жϡ�
                                                           λ����궨��IPC_MBX_NUMһ��(SDRV200Ϊ16) */
        unsigned int  reserved        : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_ISP_IPC_CPU_IMST_UNION;
#endif
#define SOC_ISP_IPC_CPU_IMST_int_mask_status_START  (0)
#define SOC_ISP_IPC_CPU_IMST_int_mask_status_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_CPU_IRST_UNION
 �ṹ˵��  : CPU_IRST �Ĵ����ṹ���塣��ַƫ����:0x804+(j)*8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�ԭʼ״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_raw_status : 16; /* bit[0-15] : ������jԭʼ�ж�״̬�Ĵ�����ÿ��bit��Ӧһ������ͨ����
                                                          0�����жϣ�
                                                          1�����жϡ�
                                                          λ����궨��IPC_MBX_NUMһ��(SDRV200Ϊ16) */
        unsigned int  reserved       : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_ISP_IPC_CPU_IRST_UNION;
#endif
#define SOC_ISP_IPC_CPU_IRST_int_raw_status_START  (0)
#define SOC_ISP_IPC_CPU_IRST_int_raw_status_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_IPC_MBX_ACTIVE_UNION
 �ṹ˵��  : IPC_MBX_ACTIVE �Ĵ����ṹ���塣��ַƫ����:0x900����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Чͨ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mbx_active_status : 16; /* bit[0-15] : ����ͨ����Ч״̬��ÿ��bit��Ӧһ������ͨ����
                                                             0�����У�
                                                             1����Ч��
                                                             λ����궨��IPC_MBX_NUMһ��(SDRV200Ϊ16) */
        unsigned int  reserved          : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_ISP_IPC_IPC_MBX_ACTIVE_UNION;
#endif
#define SOC_ISP_IPC_IPC_MBX_ACTIVE_mbx_active_status_START  (0)
#define SOC_ISP_IPC_IPC_MBX_ACTIVE_mbx_active_status_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_IPC_LP_STATE_UNION
 �ṹ˵��  : IPC_LP_STATE �Ĵ����ṹ���塣��ַƫ����:0x904����ֵ:0x00000000�����:32
 �Ĵ���˵��: �͹���״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lp_state : 3;  /* bit[0-2] : �͹���״̬��״̬��
                                                   000������״̬��ģ�鸴λ״̬��
                                                   001������״̬����״̬��������ģ�鴦�ڹ���״̬��
                                                   010���͹�������״̬����״̬�����ⲿ�е͹�������ģ����Ҫ������͹���ǰ��׼��������
                                                   011���͹���ȷ��״̬����״̬��������ģ�鴦�ڿ��У����Խ���͹��ģ�
                                                   100���͹��ľܾ�״̬����״̬��������ģ����æ�޷�����͹��ģ�
                                                   101���ȴ��˳��͹���״̬����״̬�ȴ��ⲿ����͹����˳�����csysreq_syncΪ�ߣ���
                                                   110���ȴ�ȷ���˳��͹���״̬����״̬�ȴ�����ģ������˳��͹�����Ӧ��exit_ack���źš� */
        unsigned int  reserved : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_ISP_IPC_IPC_LP_STATE_UNION;
#endif
#define SOC_ISP_IPC_IPC_LP_STATE_lp_state_START  (0)
#define SOC_ISP_IPC_IPC_LP_STATE_lp_state_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_ISP_IPC_IPC_LOCK_UNION
 �ṹ˵��  : IPC_LOCK �Ĵ����ṹ���塣��ַƫ����:0xA00����ֵ:0x00000000�����:32
 �Ĵ���˵��: IPC lock�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_lock : 32; /* bit[0-31]: дlock�Ĵ�����
                                                   ��Lock�Ĵ���д32bits��Կ����Կ�궨�����ã���鿴�궨���ļ����������Ĵ�������ʾ���мĴ�����д����Lock�Ĵ���д��������ֵ�������Ĵ�����Lock������Χ�ڵļĴ�������д��Lock������Χ��ļĴ�������д��
                                                   ���κμĴ�������Lock�Ĵ�����Ӱ�죬�κ�ʱ�̶����Զ���
                                                   ��lock�Ĵ�����
                                                   Lock�Ĵ�������ֵ��ʾ�Ĵ���������״̬��
                                                   32��h0000_0000��ʾ�Ĵ������ڽ���״̬;
                                                   32��h0000_0001��ʾ�Ĵ�����������״̬��
                                                   Lock�Ĵ���������Χ�ο�IP LRS��
                                                   lock�Ĵ�����λֵ�궨�����ã���鿴�궨���ļ��� */
    } reg;
} SOC_ISP_IPC_IPC_LOCK_UNION;
#endif
#define SOC_ISP_IPC_IPC_LOCK_ipc_lock_START  (0)
#define SOC_ISP_IPC_IPC_LOCK_ipc_lock_END    (31)






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

#endif /* end of soc_isp_ipc_interface.h */
