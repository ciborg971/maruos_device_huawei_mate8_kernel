
/*lint -save -e534 -e586 -e801*/

#include <string.h>
#include <stdlib.h>
#include <securec.h>
#include <osl_types.h>
#include <osl_sem.h>
#include <drv_comm.h>
#include <sre_typedef.h>
#include <sre_err.h>
#include <sre_lp.h>
#include <sre_shell.h>
#include <sre_symbol_api.h>
#include <osl_malloc.h>
#include <bsp_rfile.h>
#include <bsp_nvim.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define MAX_LENGTH 64

typedef s32 (*FUNC_ADDR)(void);

UINT32 g_dload_group_id = 0;
static osl_sem_id dload_mutex;
static s32 status = 0;

s32 get_data_ptr_size( s8* path, s32* fp, long* szp )
{
    s32 ret = 0;

    ret = bsp_access ( path, 0 );
    if ( BSP_OK != ret )
    {
        SRE_Printf ( "bsp_access ERROR, %s not exist, ret = 0x%x!\n", path , ret );
        return -1;
    }

    *fp = bsp_open ( path, RFILE_RDONLY, 0755 );
    if ( *fp < 0 )
    {
        SRE_Printf ( "bsp_open %s ERROR!\n", path );
        return -1;
    }

    *szp = bsp_lseek ( (u32)(*fp), 0, SEEK_END );
    if ( 0 >= *szp )
    {
        SRE_Printf ( "bsp_lseek to SEEK_END ERROR, ret = 0x%x\n", *szp );
        bsp_close ( (u32)(*fp) );
        return -1;
    }

    ret = bsp_lseek ( (u32)(*fp), 0, SEEK_SET );
    if ( 0 > ret )
    {
        SRE_Printf ( "bsp_lseek to 0 ERROR, ret = 0x%x\n", ret );
        bsp_close ( (u32)(*fp) );
        return -1;
    }

    return BSP_OK;
}

s32 bsp_dload_rmmod ( void )
{
    osl_sem_down ( &dload_mutex );
    s32 ret = SRE_OK;
    u32       func_addr      = 0;
    FUNC_ADDR func           = 0;

    if ( !status )
    {
        SRE_Printf ( "There is not a patch to remove!\n" );
        ret = -1;
        goto rmmod_sem_up;
    }

    ret = (s32)SRE_SymFindAddrByName("pan_rpc_ccore_exit", &func_addr);
    if(SRE_OK != ret)
    {
        SRE_Printf("SRE_SymFindAddrByName failed to find FUNC: pan_rpc_ccore_exit!\n");
        goto UnitRemove;
    }
    func = (FUNC_ADDR)func_addr;
    ret = func();

    SRE_Printf ( "pan_rpc exit ok\n" );

UnitRemove:
    ret = (s32)SRE_LPUnitRemove ( g_dload_group_id, 1 );
    if ( SRE_OK != ret )
    {
        SRE_Printf ( "dload_obj_insmod return 0x%x\n", ret );
        goto rmmod_sem_up;
    }
    status = 0;

rmmod_sem_up:
    osl_sem_up ( &dload_mutex );

    return ret;
}

s32 bsp_dload_insmod ( void )
{
    osl_sem_down ( &dload_mutex );

    s32 ret = 0;
    s32 fp0, fp1;
    long size0, rsize0, size1, rsize1;
    s8 * pbuf = NULL;
    s8* uinput = ( s8* )("/etc/patch_path");
    s8 filepath[MAX_LENGTH] = {0};
    u32       func_addr      = 0;
    FUNC_ADDR func           = 0;
    LP_GROUP_REG_INFO stimage_info;

    ret = get_data_ptr_size ( uinput, &fp0, &size0 );
    if ( BSP_OK != ret )
    {
        goto sem_up;
    }
    else if ( size0 >= MAX_LENGTH )
    {
        goto close0;
    }

    rsize0 = bsp_read ( (u32)fp0, filepath, (u32)size0 );
    if ( rsize0 != size0 )
    {
        SRE_Printf ( "bsp_read ERROR!\n" );
        ret = -1;
        goto close0;
    }
    filepath[size0 - 1] = 0;

    ret = get_data_ptr_size ( filepath, &fp1, &size1 );
    if ( BSP_OK != ret )
    {
        goto close0;
    }

    pbuf = ( s8* ) osl_malloc ((unsigned int)size1);
    if ( NULL == pbuf )
    {
        SRE_Printf ( "malloc ERROR!\n" );
        ret = -1;
        goto close1;
    }

    (void)memset_s (pbuf, (unsigned long)size1, 0, (unsigned long)size1);

    rsize1 = bsp_read ( (u32)fp1, pbuf, (u32)size1 );
    if ( rsize1 != size1 )
    {
        SRE_Printf ( "bsp_read ERROR!\n" );
        ret = -1;
        goto free;
    }

    (void)memset_s ( &stimage_info, sizeof ( stimage_info ), 0, sizeof ( stimage_info ) );
    stimage_info.enLPType = LP_TYPE_DP;
    stimage_info.uwPatMaxFuncNum = 100;

    ret = (s32)SRE_LPGroupInfoReg( 0, 0, &stimage_info, &g_dload_group_id );
    if ( SRE_OK != ret )
    {
        SRE_Printf ( "SRE_LPGroupInfoReg return 0x%x\n", ret );
        ret = -1;
        goto free;
    }

    ret = (s32)SRE_LPUnitFetch ( g_dload_group_id, ( UINT8* ) pbuf, (UINT32)size1 );
    if ( SRE_OK != ret )
    {
        SRE_Printf ( "SRE_LPUnitFetch return 0x%x\n", ret );
        (void) SRE_LPGroupInfoUnReg ( g_dload_group_id );
        goto free;
    }
    status = 1;
    SRE_Printf ( "dynamic load ok\n" );

    ret = (s32)SRE_SymFindAddrByName("pan_rpc_ccore_init", &func_addr);
    if(SRE_OK != ret)
    {
        SRE_Printf("SRE_SymFindAddrByName failed to find FUNC: pan_rpc_ccore_init!\n");
        goto free;
    }
    func = (FUNC_ADDR)func_addr;
    ret = func();
    SRE_Printf ( "pan_rpc init ok\n" );

free:
    osl_free ( pbuf );
close1:
    bsp_close ( (u32)fp1 );
close0:
    bsp_close ( (u32)fp0 );
sem_up:
    osl_sem_up ( &dload_mutex );

    return ret;
}

VOID bsp_dload_errhook(CHAR *pcFileName, UINT32 uwLineNo, UINT32 uwErrorNo, UINT32 uwParaLen, VOID *pPara)
{
     SRE_Printf("error function: %s\n", pcFileName);
}

u32 bsp_dload_reghook(void)
{
    return SRE_ErrRegHook(bsp_dload_errhook);
}

void bsp_dload_init ( void )
{
    osl_sem_init (1, &dload_mutex);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

/*lint -restore*/

