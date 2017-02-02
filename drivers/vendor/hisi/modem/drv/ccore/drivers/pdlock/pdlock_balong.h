/*************************************************************************
*   ��Ȩ����(C) 2008-2013, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  pdlock_balong.h
*
*   ��    �� :  l00312158
*
*   ��    �� :  ���ļ���Ҫ������߷��������ݽṹ����
*
*   �޸ļ�¼ :  2015��5��11��  v1.00  l00312158  ����
*************************************************************************/
#ifndef __PDLOCK_BALONG_H__
#define __PDLOCK_BALONG_H__
    
#ifdef __cplusplus
    extern "C" {
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "bsp_om.h"
#include "bsp_om_enum.h"

#include "osl_types.h"
#include "osl_malloc.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define pdlock_ok (0)
#define pdlock_error (-1)

#define MAX_RECORD (100)
#define FIRST_RECORD (20)

#define PDLOCK_DUMP_SAVE_MOD   DUMP_CP_PDLOCK

#define pdlock_print(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_FATAL, BSP_MODU_PDLOCK, "[pdlock]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

#define pdlock_malloc(size)     osl_malloc(size)
#define pdlock_free(ptr)        osl_free(ptr)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum pdlock_sysctrl_reg
{
    pd_glb = 0,
    modem_glb,
    pcie_glb,
    ao_glb,
    sysctrl_sum
};

enum
{
    magic = 0,      /*dump�ռ�ͷ��Ϣ�е�ħ����*/
    max_log,        /*dump�ռ�ͷ��Ϣ�е�����ܹ������쳣��Ϣ����Ŀ*/
    total,          /*dump�ռ�ͷ��Ϣ�еĵ�ǰ�����������߼����ܴ���*/
    offset          /*dump�ռ�ͷ��Ϣ�еĵ�ǰ�����쳣��Ϣ��λ��*/
};

enum
{
    base_addr = 0,
    addr_offset,
    start_bit,
    end_bit
};

enum
{
    PDLOCK_DISABLE = 0,
    PDLOCK_ENABLE = 1
};

enum
{
    PDLOCK_RESET_DISABLE = 0,
    PDLOCK_RESET_ENABLE = 1
};
/*****************************************************************************
  4 STRUCT����
*****************************************************************************/
struct pdlock_cfg
{
    u8  dump_mst_id;
    u8  dump_operation;
    u8  reserved[2];
    u32 mst_reg_addr[3];     /*����״̬�Ĵ���ƫ�Ƶ�ַ����ʼλ����ֹλ*/
    u32 mst_id_addr[3];      /*mstid ����״̬�Ĵ���ƫ�Ƶ�ַ����ʼλ����ֹλ(ΪV722Ԥ��)*/
    u32 mst_operation[3];    /*mst �������ͼĴ���ƫ�Ƶ�ַ����ʼλ����ֹλ(V722 APB/AHB���У�*/
    char mst_name[32];               /*master���ּ���������*/
    u32 error_address_offset;     /*���ʴ����ַ�Ĵ�����ƫ�Ƶ�ַ*/
};                               

struct pdlock_bus
{
    u8   dump_bus_id;             /*bus_id*/
    u8   reserved[3];
    u32  base_addr;               /*�Ĵ��������ַ*/
    char busname[16];             /*��������*/
    u32  reg_state_sum;           /*����״̬�Ĵ�������*/ 
    struct pdlock_cfg *cfg;       /*����״̬�Ĵ�����¼����Ϣ*/
};                                /*�������ݽṹ*/

struct pdlock_sysctrl
{
    u32 reset_reg_addr[4];        /*��λ����״̬�Ĵ�����ַ��ƫ�ơ���ʼλ����ֹλ*/
    u32 bus_sum;                  /*������Ŀ*/
    struct pdlock_bus *bus;       /*�������ݽṹ*/
};

struct pdlock_state
{
    u32 enable;                   /*��NV��ȡ���ã��ж��Ƿ�ʹ�ܷ������߼���0����ʹ�ܣ�1����ʹ��*/
    u32 reset_enable;             /*��NV��ȡ���ã��������������߼�ʱ���ж��Ƿ�λϵͳ��0������λ��1����λ*/
};

struct pdlock_dump_record
{
    u8 bus_id;                    /*��dump�м�¼�쳣��Ϣ��bus_id*/
    u8 mst_id;                    /*��dump�м�¼�쳣��Ϣ��mst_id*/
    u8 operation;                 /*��dump�м�¼master����Ĳ������ͣ�1����д������2�����������0�����������δ֪*/
    u8 reserved;
    u32 slave_addr;               /*��dump�м�¼�쳣��Ϣ��slave address*/
    u32 slice;                    /*��dump�м�¼�쳣��Ϣ��ʱ���*/
};

/*****************************************************************************
  5 ��������
*****************************************************************************/
s32 bsp_pdlock_init(void);



#ifdef __cplusplus
}
#endif

#endif






