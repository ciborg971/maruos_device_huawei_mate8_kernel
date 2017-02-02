

/*----includes-----------------------------------------------------------------------*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <asm/uaccess.h>

#include "../include/srecorder_save_log.h"


/*----local macroes------------------------------------------------------------------*/


/*----local prototypes----------------------------------------------------------------*/

typedef struct
{
    srecorder_info_type_e type;
    char *desciprion;
} srecorder_header_info_type_description_t;


/*----local variables------------------------------------------------------------------*/

static srecorder_header_info_type_description_t s_srecorder_head_info[] = 
{
    {CRASH_REASON_TIME_BIT0, CRASH_REASON_KEYWORD},
    {SYS_INFO_BIT1, SYSINFO_KEYWORD}, 
    {DMESG_BIT2, DMESG_KEYWORD},
    {ALL_CPU_STACK_BIT3, ALL_CPU_CALL_STACK_KEYWORD},
    {ALL_PS_INFO_BIT4, ALL_PS_INFO_KEYWORD},
    {CURRENT_PS_BACKTRACE_BIT5, CURRENT_PS_BACKTRACE_KEYWORD},
    {SLABINFO_BIT6, SLABINFO_KEYWORD},
    {MODEM_ERR_BIT7, MODEM_ERR_KEYWORD},
    {MODEM_ERR_F3_BIT8, MODEM_ERR_F3_KEYWORD},
	{LOGCAT_BIT9, LOGCAT_KEYWORD},
};


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/


/*----function definitions--------------------------------------------------------------*/

/**
    @function: int srecorder_renew_meminfo(srecorder_reserved_mem_info_for_log_t *pmem_info, int bytes_read)
    @brief: ����SRecorder�����ڴ���������Ϣ���ݽṹ

    @param: pmem_info 
    @param: bytes_read 
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_renew_meminfo(srecorder_reserved_mem_info_t *pmem_info, int bytes_read)
{
    pmem_info->bytes_read += bytes_read;
    pmem_info->bytes_per_type += bytes_read;
    pmem_info->bytes_left = pmem_info->mem_size - pmem_info->bytes_read;

    return 0;
}


/**
    @function:int srecorder_write_info_header(srecorder_reserved_mem_info_for_log_t *pmem_info, 
        srecorder_info_type_e type, 
        psrecorder_info_header_t *pinfo_header)
    @brief: ��ʼ��������Ϣ��ͷ�����ݽṹ

    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: type ��Ϣ����
    @param: pinfo_header ��Ϣͷ��У�����ݽṹ
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_write_info_header(srecorder_reserved_mem_info_t *pmem_info, 
    srecorder_info_type_e type, 
    psrecorder_info_header_t *pinfo_header)
{
    int bytes_read = 0;
/* ɾ���˴����� */
#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
    int info_header_size = sizeof(srecorder_info_header_t);
#endif

    if (unlikely(NULL == pmem_info || NULL == pmem_info->start_addr || NULL == pinfo_header 
        || (LOG_TYPE_COUNT <= (int)type || (int)type < 0)))
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -1;
    }

#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
    /*��У����Ϣ��ͷ���ṹ������*/
    /* ɾ���˴� */
    if ((pmem_info->bytes_read + info_header_size) > pmem_info->mem_size)
    {
        return -1;
    }

    *pinfo_header = (psrecorder_info_header_t)(pmem_info->start_addr + pmem_info->bytes_read);
    memset(*pinfo_header, 0, info_header_size);
    ((psrecorder_info_header_t)*pinfo_header)->type = type;
    
    pmem_info->bytes_read += (info_header_size);
#endif

    pmem_info->bytes_per_type = 0;

    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "%s\n", s_srecorder_head_info[type].desciprion);
    srecorder_renew_meminfo(pmem_info, bytes_read);
    
    return 0;
}


/**
    @function: int srecorder_validate_info_header(srecorder_info_header_t *pheader, unsigned long data_len)
    @brief: �Ը��ֶ�λ��Ϣ��ͷ��������У��

    @param: pheader ������Ϣ��У��ͷ
    @param: data_len ÿ����Ϣ�����ݳ��ȣ�������У��ͷ������
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_validate_info_header(srecorder_info_header_t *pheader, unsigned long data_len)
{
#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
    unsigned long buf[2] = {0, 0};

    if (unlikely(NULL == pheader))
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -1;
    }
       
    pheader->data_len = data_len;/* [false alarm]:pheader have protect  */
    buf[0] = (unsigned long)pheader->type;
    buf[1] = (unsigned long)pheader->data_len;
    pheader->crc32 = srecorder_get_crc32((unsigned char *)buf, sizeof(buf));
#endif

    return 0;
}


#if 0 /* ������δ�����Ϊ�ں˶�д�ļ��Ĳο����� */
/**
    @function: int srecorder_save_log(char *file_path, char *pbuf, int data_len)
    @brief: ���ں��н���Ϣ���浽�ļ���

    @param: file_path �ļ�·��
    @param: pbuf �����Ϣ���ڴ���ʼ��ַ
    @param: pbuf Ҫ��������ݳ���
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_save_log(char *file_path, char *pbuf, int data_len)
{
    mm_segment_t old_fs;
    loff_t pos;
    struct file *fp;
    
    if (NULL == file_path || NULL == pbuf || data_len <= 0)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -1;
    }

    /*0644�ļ���дִ��Ȩ�ޣ�������:��д���û���:��������:��*/
    fp = filp_open(file_path, O_WRONLY | O_CREAT, 0644); 
    if (NULL != fp)
    {
        old_fs = get_fs();
        set_fs(KERNEL_DS);
        pos = 0;
        vfs_write(fp, pbuf, data_len, &pos);
        /*
        char buf[1024];        
        memset(buf, 0, sizeof(buf));
        pos = 0;
        vfs_read(fp, buf, sizeof(buf) - 1, &pos);*/
        filp_close(fp, NULL);
        set_fs(old_fs);        
    }

    return 0;
}
#endif

