/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_asp_ipc_ns_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:18:14
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ASP_IPC_NS.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ASP_IPC_NS_INTERFACE_H__
#define __SOC_ASP_IPC_NS_INTERFACE_H__

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
/* �Ĵ���˵����Դ���������üĴ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_MBX_SOURCE_UNION */
#define SOC_ASP_IPC_NS_MBX_SOURCE_ADDR(base, i)       ((base) + (0x000+(i)*64))

/* �Ĵ���˵����Ŀ�Ĵ��������üĴ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_MBX_DSET_UNION */
#define SOC_ASP_IPC_NS_MBX_DSET_ADDR(base, i)         ((base) + (0x004+(i)*64))

/* �Ĵ���˵����Ŀ�Ĵ���������Ĵ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_MBX_DCLEAR_UNION */
#define SOC_ASP_IPC_NS_MBX_DCLEAR_ADDR(base, i)       ((base) + (0x008+(i)*64))

/* �Ĵ���˵����Ŀ�Ĵ�����״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_MBX_DSTATUS_UNION */
#define SOC_ASP_IPC_NS_MBX_DSTATUS_ADDR(base, i)      ((base) + (0x00C+(i)*64))

/* �Ĵ���˵��������ͨ��ģʽ״̬��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_MBX_MODE_UNION */
#define SOC_ASP_IPC_NS_MBX_MODE_ADDR(base, i)         ((base) + (0x010+(i)*64))

/* �Ĵ���˵�����������ж����μĴ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_MBX_IMASK_UNION */
#define SOC_ASP_IPC_NS_MBX_IMASK_ADDR(base, i)        ((base) + (0x014+(i)*64))

/* �Ĵ���˵�����������ж�״̬����Ĵ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_MBX_ICLR_UNION */
#define SOC_ASP_IPC_NS_MBX_ICLR_ADDR(base, i)         ((base) + (0x018+(i)*64))

/* �Ĵ���˵�������ͼĴ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_MBX_SEND_UNION */
#define SOC_ASP_IPC_NS_MBX_SEND_ADDR(base, i)         ((base) + (0x01C+(i)*64))

/* �Ĵ���˵��������0�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_MBX_DATA0_UNION */
#define SOC_ASP_IPC_NS_MBX_DATA0_ADDR(base, i)        ((base) + (0x020+(i)*64))

/* �Ĵ���˵��������1�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_MBX_DATA1_UNION */
#define SOC_ASP_IPC_NS_MBX_DATA1_ADDR(base, i)        ((base) + (0x024+(i)*64))

/* �Ĵ���˵�����ж�����״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_CPU_IMST_UNION */
#define SOC_ASP_IPC_NS_CPU_IMST_ADDR(base, j)         ((base) + (0x800+(j)*8))

/* �Ĵ���˵�����ж�ԭʼ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_CPU_IRST_UNION */
#define SOC_ASP_IPC_NS_CPU_IRST_ADDR(base, j)         ((base) + (0x804+(j)*8))

/* �Ĵ���˵������Чͨ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_IPC_MBX_ACTIVE_UNION */
#define SOC_ASP_IPC_NS_IPC_MBX_ACTIVE_ADDR(base)      ((base) + (0x900))

/* �Ĵ���˵����IPC lock�Ĵ�����
   λ����UNION�ṹ:  SOC_ASP_IPC_NS_IPC_LOCK_UNION */
#define SOC_ASP_IPC_NS_IPC_LOCK_ADDR(base)            ((base) + (0xA00))





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
 �ṹ��    : SOC_ASP_IPC_NS_MBX_SOURCE_UNION
 �ṹ˵��  : MBX_SOURCE �Ĵ����ṹ���塣��ַƫ����:0x000+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: Դ���������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  source   : 4;  /* bit[0-3] : ����ͨ��ռ��Դ���������ã������ö����������ͬռ�ô�����ͨ����ÿһbit��Ӧһ��ռ��ͨ���Ĵ�������
                                                   ���ú�д��ֵͬ�ͷŸ�ͨ�����䣬����������ݼĴ�����ģʽ�Ĵ���֮��ļĴ�������0�����ú�д����ֵ�����塣
                                                   ��MBX_SOURCE�Ĵ���Ϊ��0ֵʱ����MBX_DCLEAR�Ĵ�����MBX_DSET�Ĵ�����MBX_MODE�Ĵ�����MBX_IMASK�Ĵ�����MBX_SEND�Ĵ������Խ�����Чд�����������޷�д�롣�����Ĵ������ܴ����ơ� */
        unsigned int  reserved : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_ASP_IPC_NS_MBX_SOURCE_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_SOURCE_source_START    (0)
#define SOC_ASP_IPC_NS_MBX_SOURCE_source_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_MBX_DSET_UNION
 �ṹ˵��  : MBX_DSET �Ĵ����ṹ���塣��ַƫ����:0x004+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ŀ�Ĵ��������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dset     : 4;  /* bit[0-3] : ����ͨ��Ŀ�Ĵ��������üĴ�������ͨ���жϵĽ��մ��������ã������ö��������ͬʱ�����жϣ�ÿһbit��Ӧһ����������
                                                   0����Ӱ�죻
                                                   1������ΪĿ�Ĵ������� */
        unsigned int  reserved : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_ASP_IPC_NS_MBX_DSET_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_DSET_dset_START      (0)
#define SOC_ASP_IPC_NS_MBX_DSET_dset_END        (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_MBX_DCLEAR_UNION
 �ṹ˵��  : MBX_DCLEAR �Ĵ����ṹ���塣��ַƫ����:0x008+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ŀ�Ĵ���������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dclear   : 4;  /* bit[0-3] : ����ͨ��Ŀ�Ĵ���������Ĵ�����ÿһbit��Ӧһ����������
                                                   0����Ӱ�죻
                                                   1������� */
        unsigned int  reserved : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_ASP_IPC_NS_MBX_DCLEAR_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_DCLEAR_dclear_START    (0)
#define SOC_ASP_IPC_NS_MBX_DCLEAR_dclear_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_MBX_DSTATUS_UNION
 �ṹ˵��  : MBX_DSTATUS �Ĵ����ṹ���塣��ַƫ����:0x00C+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ŀ�Ĵ�����״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dstatus  : 4;  /* bit[0-3] : ����ͨ��Ŀ�Ĵ�����״̬�Ĵ�����ÿһbit��Ӧһ���������� */
        unsigned int  reserved : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_ASP_IPC_NS_MBX_DSTATUS_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_DSTATUS_dstatus_START   (0)
#define SOC_ASP_IPC_NS_MBX_DSTATUS_dstatus_END     (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_MBX_MODE_UNION
 �ṹ˵��  : MBX_MODE �Ĵ����ṹ���塣��ַƫ����:0x010+(i)*64����ֵ:0x00000010�����:32
 �Ĵ���˵��: ����ͨ��ģʽ״̬��״̬�Ĵ���
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
} SOC_ASP_IPC_NS_MBX_MODE_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_MODE_auto_answer_START   (0)
#define SOC_ASP_IPC_NS_MBX_MODE_auto_answer_END     (0)
#define SOC_ASP_IPC_NS_MBX_MODE_auto_link_START     (1)
#define SOC_ASP_IPC_NS_MBX_MODE_auto_link_END       (1)
#define SOC_ASP_IPC_NS_MBX_MODE_state_status_START  (4)
#define SOC_ASP_IPC_NS_MBX_MODE_state_status_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_MBX_IMASK_UNION
 �ṹ˵��  : MBX_IMASK �Ĵ����ṹ���塣��ַƫ����:0x014+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_mask : 4;  /* bit[0-3] : ����ͨ�������������ж��������ã�ÿһbit��Ӧһ����������
                                                   0�������Σ�
                                                   1�����Ρ� */
        unsigned int  reserved : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_ASP_IPC_NS_MBX_IMASK_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_IMASK_int_mask_START  (0)
#define SOC_ASP_IPC_NS_MBX_IMASK_int_mask_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_MBX_ICLR_UNION
 �ṹ˵��  : MBX_ICLR �Ĵ����ṹ���塣��ַƫ����:0x018+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ж�״̬����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_clear : 4;  /* bit[0-3] : ����ͨ�������������κ��ж�״̬��ÿһbit��Ӧһ����������д1�����
                                                    0�����жϣ�
                                                    1�����жϡ� */
        unsigned int  reserved  : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_ASP_IPC_NS_MBX_ICLR_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_ICLR_int_clear_START  (0)
#define SOC_ASP_IPC_NS_MBX_ICLR_int_clear_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_MBX_SEND_UNION
 �ṹ˵��  : MBX_SEND �Ĵ����ṹ���塣��ַƫ����:0x01C+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ͼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  send     : 4;  /* bit[0-3] : �жϷ��ͼĴ�����ÿһbit��Ӧһ����������ͨ�Ź����У����ô˼Ĵ�����ֻ��λbit��Ч��
                                                   ��Դ���жϸ�Ŀ��ʱ��send�Ĵ�������ֵ��Դ�Ĵ���ֵ���ʱ���жϸ�Ŀ�Ĵ���������Ŀ�ķ�Ӧ���жϸ�Դʱ��send�Ĵ�������ֵ��Ŀ�����ʱ��Ӧ���жϸ�Դ���Զ�����ʱ������������˼Ĵ����������ã��Զ�Ӧ��ʱ��Ŀ������жϺ󣬴˼Ĵ����Զ���λ���������á� */
        unsigned int  reserved : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_ASP_IPC_NS_MBX_SEND_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_SEND_send_START      (0)
#define SOC_ASP_IPC_NS_MBX_SEND_send_END        (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_MBX_DATA0_UNION
 �ṹ˵��  : MBX_DATA0 �Ĵ����ṹ���塣��ַƫ����:0x020+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����0�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data0 : 32; /* bit[0-31]: ����ͨ�����ݼĴ���0 */
    } reg;
} SOC_ASP_IPC_NS_MBX_DATA0_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_DATA0_data0_START  (0)
#define SOC_ASP_IPC_NS_MBX_DATA0_data0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_MBX_DATA1_UNION
 �ṹ˵��  : MBX_DATA1 �Ĵ����ṹ���塣��ַƫ����:0x024+(i)*64����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����1�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data1 : 32; /* bit[0-31]: ����ͨ�����ݼĴ���1 */
    } reg;
} SOC_ASP_IPC_NS_MBX_DATA1_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_DATA1_data1_START  (0)
#define SOC_ASP_IPC_NS_MBX_DATA1_data1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_CPU_IMST_UNION
 �ṹ˵��  : CPU_IMST �Ĵ����ṹ���塣��ַƫ����:0x800+(j)*8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_mask_status : 4;  /* bit[0-3] : ������j���κ���ж�״̬�Ĵ�����ÿ��bit��Ӧһ������ͨ����
                                                          0�����жϣ�
                                                          1�����жϡ� */
        unsigned int  reserved        : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_ASP_IPC_NS_CPU_IMST_UNION;
#endif
#define SOC_ASP_IPC_NS_CPU_IMST_int_mask_status_START  (0)
#define SOC_ASP_IPC_NS_CPU_IMST_int_mask_status_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_CPU_IRST_UNION
 �ṹ˵��  : CPU_IRST �Ĵ����ṹ���塣��ַƫ����:0x804+(j)*8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�ԭʼ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_raw_status : 4;  /* bit[0-3] : ������jԭʼ�ж�״̬�Ĵ�����ÿ��bit��Ӧһ������ͨ����
                                                         0�����жϣ�
                                                         1�����жϡ� */
        unsigned int  reserved       : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_ASP_IPC_NS_CPU_IRST_UNION;
#endif
#define SOC_ASP_IPC_NS_CPU_IRST_int_raw_status_START  (0)
#define SOC_ASP_IPC_NS_CPU_IRST_int_raw_status_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_IPC_MBX_ACTIVE_UNION
 �ṹ˵��  : IPC_MBX_ACTIVE �Ĵ����ṹ���塣��ַƫ����:0x900����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Чͨ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mbx_active_status : 4;  /* bit[0-3] : ����ͨ����Ч״̬��ÿ��bit��Ӧһ������ͨ����
                                                            0�����У�
                                                            1����Ч�� */
        unsigned int  reserved          : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_ASP_IPC_NS_IPC_MBX_ACTIVE_UNION;
#endif
#define SOC_ASP_IPC_NS_IPC_MBX_ACTIVE_mbx_active_status_START  (0)
#define SOC_ASP_IPC_NS_IPC_MBX_ACTIVE_mbx_active_status_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_IPC_NS_IPC_LOCK_UNION
 �ṹ˵��  : IPC_LOCK �Ĵ����ṹ���塣��ַƫ����:0xA00����ֵ:0x00000001�����:32
 �Ĵ���˵��: IPC lock�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_lock : 32; /* bit[0-31]: дlock�Ĵ�����
                                                   ��Lock�Ĵ���д32bits��Կ��32'h1ACCE551���������Ĵ�������ʾ���мĴ�����д����Lock�Ĵ���д��������ֵ�������Ĵ�����Lock������Χ�ڵļĴ�������д��Lock������Χ��ļĴ�������д��
                                                   ���κμĴ�������Lock�Ĵ�����Ӱ�죬�κ�ʱ�̶����Զ���
                                                   ��lock�Ĵ�����
                                                   Lock�Ĵ�������ֵ��ʾ�Ĵ���������״̬��
                                                   32��h0000_0000��ʾ�Ĵ������ڽ���״̬;
                                                   32��h0000_0001��ʾ�Ĵ�����������״̬��
                                                   Lock�Ĵ���������Χ�ο�IP LRS�� */
    } reg;
} SOC_ASP_IPC_NS_IPC_LOCK_UNION;
#endif
#define SOC_ASP_IPC_NS_IPC_LOCK_ipc_lock_START  (0)
#define SOC_ASP_IPC_NS_IPC_LOCK_ipc_lock_END    (31)






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

#endif /* end of soc_asp_ipc_ns_interface.h */
