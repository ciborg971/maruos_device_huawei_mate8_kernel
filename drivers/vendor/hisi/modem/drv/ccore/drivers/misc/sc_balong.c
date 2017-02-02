
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*lint -save -e537 -e732 -e737 -e762 -e774*/
#include <securec.h>
#include "string.h"
#include <osl_bio.h>
#include <bsp_nvim.h>
#include <bsp_misc.h>


sc_status_stru g_sc_stat;

s32 sc_icc_msg_proc(u32 chanid, u32 len, void* pdata);
s32 sc_opt_comm(MISC_SC_OPT_ENUM sc_enum, u8* pRamAddr, u32 len);
void sc_icc_task(void);
s32 bsp_sc_backup(u8* pRamAddr, u32 len);
s32 bsp_sc_restore(u8* pRamAddr,u32 len);

/*
* Function   : bsp_sc_init
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/
s32 bsp_sc_init(void)
{
    u32 ret = 0;

    (void)memset_s((void *)&g_sc_stat, sizeof(sc_status_stru),0,sizeof(sc_status_stru));
    
    /* sem create */
    osl_sem_init(0,&g_sc_stat.sc_api_sem);
    osl_sem_init(0,&g_sc_stat.sc_tsk_sem);

    /* task create */
#ifdef __OS_VXWORKS__
    ret = (u32)osl_task_init("sc_ccore_task",128,4096,(OSL_TASK_FUNC)sc_icc_task,NULL,(void*)&g_sc_stat.sc_taskid);
#elif defined(__OS_RTOSCK__)
    ret = (u32)osl_task_init("sc_ccore_task",57,4096,(OSL_TASK_FUNC)sc_icc_task,NULL,(void*)&g_sc_stat.sc_taskid);
#endif
    if(ret)
    {
        sc_error_printf("init task failed!\n");
        return BSP_ERR_SC_TASK_INIT_FAIL;
    }
    
    /* register icc event */
    if(ICC_OK!=bsp_icc_event_register(SC_ICC_CHAN_ID, sc_icc_msg_proc,NULL,NULL,NULL))
    {
        sc_error_printf("register icc channel failed!\n");
        return BSP_ERR_SC_SEM_INIT_FAIL;
    }

    sc_printf("[SC]: init success.\n");
    
    return SC_OK;
}

/*
* Function   : sc_opt_comm
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/
s32 sc_opt_comm(MISC_SC_OPT_ENUM sc_enum, u8* pRamAddr, u32 len)
{
    s32 write_len   = 0;
    s32 sc_fp       = 0;
    s8* sc_path     = (s8*)SC_PACKET_TRANS_FILE;
    sc_icc_stru     sc_send_msg = {MISC_SC_OPT_BUTT};
    
    /* judge para */
    if(sc_enum >= MISC_SC_OPT_BUTT)
    {
        sc_error_printf("para wrong, sc_enum is %d!\n",sc_enum); /* [false alarm]: fortify ?車㊣“*/
        return BSP_ERR_SC_INVALID_PARAM;
    }

    if((NULL == pRamAddr)||( len >= SC_MTD_PTABLE_OFFSET))
    {
        sc_error_printf("para wrong, addr is 0x%x, len is 0x%x!\n",(unsigned long)pRamAddr,len);
        return BSP_ERR_SC_INVALID_PARAM;
    }
    
    g_sc_stat.sc_ram_addr   = pRamAddr;
    g_sc_stat.sc_ram_len    = len;
    g_sc_stat.sc_opt_type   = sc_enum;

    if(bsp_access(sc_path,0))
    {
        (void)bsp_remove(sc_path);
    }

    if(MISC_SC_OPT_WRITE == sc_enum)
    {
        sc_fp = bsp_open(sc_path, (RFILE_CREAT|RFILE_RDWR), 0660); /* [false alarm]: fortify ?車㊣“*/
        if(sc_fp < 0)
        {
            sc_error_printf("open file %s failed!\n",sc_path);
            return BSP_ERR_SC_NO_FILE;
        }
        
        write_len = bsp_write((u32)sc_fp, (const s8*)pRamAddr, len); /* [false alarm]: fortify ?車㊣“*/
        if(write_len != (s32)len)
        {
            sc_error_printf("write %s fail, write len is 0x%x, given len is 0x%x!\n",sc_path,write_len,len);
            (void)bsp_close((u32)sc_fp);
            return BSP_ERR_SC_WRITE_FILE_FAIL;
        }
        
        (void)bsp_close((u32)sc_fp);
    }

    /* send handshake packet */
    sc_send_msg.sc_opt_type     = sc_enum;
    sc_send_msg.sc_total_len    = len;
    write_len = bsp_icc_send(ICC_CPU_APP, SC_ICC_CHAN_ID, (u8*)&sc_send_msg, sizeof(sc_icc_stru));
    if((u32)write_len != sizeof(sc_icc_stru))
    {
        sc_error_printf("send to app filed, write_len is 0x%x!\n",write_len);
        return BSP_ERR_SC_ICC_SEND;
    }
    else
    {
        sc_debug_printf("send to app ok!\n");
    }
    
    /* wait recv sem */
    if(osl_sem_downtimeout(&g_sc_stat.sc_api_sem, 1000))
    {
        sc_error_printf("get result from acore timeout failed!\n");
        return BSP_ERR_SC_SEM_TIMEOUT;
    }
    else
    {
        if((g_sc_stat.sc_opt_type != sc_enum)||(SC_OK != g_sc_stat.sc_opt_ret) )
        {
            sc_error_printf("recv wrong result,sc_icc_type is %d, sc_ret is %d!\n",g_sc_stat.sc_opt_type,g_sc_stat.sc_opt_ret);
            return BSP_ERR_SC_CNF_ABNORMAL;
        }
    }

    if(bsp_access(sc_path, 0))
    {
        (void)bsp_remove(sc_path);
    }

    sc_debug_printf("api opterate %d success !\n",g_sc_stat.sc_opt_type);
    
    return SC_OK;
}

/*
* Function   : sc_icc_task
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/
void sc_icc_task(void)
{
    s32 read_len    = 0;
    s32 sc_fp       = 0;
    s8* sc_path     = (s8*)SC_PACKET_TRANS_FILE;
    sc_icc_stru     icc_recv = {MISC_SC_OPT_BUTT};

    /* coverity[no_escape] */
    /* coverity[loop_top] */
    for(;;)
    {
        osl_sem_down(&g_sc_stat.sc_tsk_sem);

        sc_debug_printf("get sem ok!\n");
        
        read_len = bsp_icc_read(SC_ICC_CHAN_ID, (u8*)&icc_recv, sizeof(sc_icc_stru));
        if(read_len > (s32)sizeof(sc_icc_stru))
        {
            osl_sem_up(&g_sc_stat.sc_tsk_sem);
            sc_error_printf("bsp icc read error, chanid :0x%x ret :0x%x\n",SC_ICC_CHAN_ID,read_len);
            continue;
        }
        else if(0 >= read_len)
        {
            sc_error_printf("bsp icc read error, length is 0x%x!\n", read_len);
            continue ;
        }

        if( MISC_SC_OPT_READ == icc_recv.sc_opt_type)
        {
            if(SC_OK == icc_recv.sc_cnf_ret)
            {
                sc_fp = bsp_open(sc_path, (RFILE_RDONLY), 0660); /* [false alarm]: fortify ?車㊣“*/
                if(sc_fp < 0)
                {
                    sc_error_printf("open file %s failed!\n",sc_path);
                    g_sc_stat.sc_opt_ret = BSP_ERR_SC_NO_FILE;
                    osl_sem_up(&g_sc_stat.sc_api_sem);
                    continue ;
                }
                
                read_len = bsp_read((u32)sc_fp, (s8 *)(g_sc_stat.sc_ram_addr), g_sc_stat.sc_ram_len); /* [false alarm]: fortify ?車㊣“*/
                if(read_len != (s32)(g_sc_stat.sc_ram_len))
                {
                    sc_error_printf("read %s fail, read len is 0x%x, given len is 0x%x!\n",sc_path,read_len,g_sc_stat.sc_ram_len);
                    (void)bsp_close((u32)sc_fp);
                    g_sc_stat.sc_opt_ret = BSP_ERR_SC_READ_FILE_FAIL;
                    osl_sem_up(&g_sc_stat.sc_api_sem);
                    continue ;
                }
                (void)bsp_close((u32)sc_fp);
            }
        }

        sc_debug_printf("send to api interface\n");
        
        g_sc_stat.sc_opt_ret = icc_recv.sc_cnf_ret;
        osl_sem_up(&g_sc_stat.sc_api_sem);
    }
}

/*
* Function   : sc_icc_msg_proc
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/
s32 sc_icc_msg_proc(u32 chanid, u32 len, void* pdata)
{  
    if(chanid != SC_ICC_CHAN_ID)
    {
        sc_error_printf(" sc icc channel error :0x%x\n",chanid);
        return BSP_ERR_SC_ICC_READ;
    }

    osl_sem_up(&g_sc_stat.sc_tsk_sem);

    sc_debug_printf("recv from acore ok!\n",chanid);

    return SC_OK;
}

/*
* Function   : bsp_sc_backup
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/
s32 bsp_sc_backup(u8* pRamAddr, u32 len)
{
    return sc_opt_comm(MISC_SC_OPT_WRITE, pRamAddr, len);
}

/*
* Function   : bsp_sc_restore
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/

s32 bsp_sc_restore(u8* pRamAddr,u32 len)
{
    return sc_opt_comm(MISC_SC_OPT_READ, pRamAddr, len);
}

/*lint -restore +e537 +e732 +e737 +e762 +e774*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




