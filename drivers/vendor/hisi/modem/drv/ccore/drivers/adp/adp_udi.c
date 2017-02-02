/*lint -e715 -e785*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
#ifdef __OS_VXWORKS__
#include <vxWorks.h>
#include <logLib.h>
#include <usrLib.h>
#include <ioLib.h>
#endif
#include <string.h>
#include <stdio.h>
#include <mdrv.h>
#include <bsp_icc.h>
#include <bsp_om.h>
#include <product_config.h>
#include "udi_balong.h"
#include <osl_malloc.h>
#include "securec.h"

#ifdef __OS_RTOSCK__
#define LOCAL static
#define O_RDWR 2
#endif

LOCAL BSP_S32 udiAdpIccInit(VOID);
LOCAL BSP_S32 udiAdpUartInit(VOID);

/* ��ģ������ֵ���� */
#define UDI_USB_ACM_CAPA                (UDI_CAPA_BLOCK_READ | UDI_CAPA_BLOCK_WRITE | UDI_CAPA_READ_CB | UDI_CAPA_WRITE_CB)
#define UDI_USB_NCM_NDIS_CAPA           (UDI_CAPA_READ_CB | UDI_CAPA_BUFFER_LIST)
#define UDI_USB_NCM_CTRL_CAPA           (UDI_CAPA_READ_CB | UDI_CAPA_CTRL_OPT)
#define UDI_ICC_CAPA                    (UDI_CAPA_BLOCK_READ | UDI_CAPA_BLOCK_WRITE | UDI_CAPA_READ_CB | UDI_CAPA_WRITE_CB)
#define UDI_UART_CAPA                   (UDI_CAPA_BLOCK_READ | UDI_CAPA_BLOCK_WRITE)


/* ��ģ���ʼ���������� */
VOID* g_udiInitFuncTable[(BSP_U32)UDI_DEV_MAX+1] =
{
    /* ICC Init */
    udiAdpIccInit,

    /* UART Init */
    udiAdpUartInit,

    /* Must Be END */
    NULL
};

#if 0
/**************************************************************************
  UART ����ʵ��
**************************************************************************/
LOCAL BSP_CHAR* sg_UartNameTbl[]=
{
    "/tyCo/0",
    "/tyCo/1",
    NULL
};
#define UDI_GET_UART_NUM() (sizeof(sg_UartNameTbl)/sizeof(BSP_U8*)-1)
LOCAL BSP_S32 udiUartAdpOpen(UDI_OPEN_PARAM_S *param, UDI_HANDLE handle)
{

    BSP_U8* pstrName;
    BSP_U32 u32Type;
    BSP_S32 s32Fd;

    UDI_UNUSED_PARAM(handle);

    u32Type = UDI_GET_DEV_TYPE(param->devid);
    if (u32Type > UDI_GET_UART_NUM()-1)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UDI, "Invalid UART Num:%d, line:%d\n",
                  u32Type, __LINE__, 0,0,0,0);
        return (-1);
    }

    pstrName = (BSP_U8*)sg_UartNameTbl[u32Type];

    s32Fd = open((char*)pstrName, O_RDWR, 0);/* [false alarm]:Disable fortify false alarm */
    /* coverity[off_by_one] */
    if (s32Fd <= 0)
    {
        /* coverity[noescape] */
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UDI, "open %s fail, ret:%d line:%d\n",
                  pstrName, s32Fd, __LINE__, 0,0,0);
        return (-1);
    }

    /* coverity[leaked_handle] */
    (BSP_VOID)BSP_UDI_SetPrivate(param->devid, (VOID*)s32Fd);/* [false alarm]:Disable fortify false alarm */
    return 0;
}
#endif
LOCAL BSP_S32 udiAdpUartInit(VOID)
{
    /* pDrvInterface' (line 287) has not been freed or returned */
    return 0;/*lint !e429 */
}
/**************************************************************************
  ICC ����ʵ��
**************************************************************************/
LOCAL BSP_U32 sg_chnHandleTbl[ICC_CHAN_NUM_MAX] = {0};

UDI_HANDLE BSP_UDI_ICC_ChnToHandle(BSP_U32 u32Chn)
{
    return (UDI_HANDLE)sg_chnHandleTbl[u32Chn];
}

/*lint -save -e527*/
LOCAL BSP_S32 udiIccAdpOpen(UDI_OPEN_PARAM_S *param, UDI_HANDLE handle)
{
    BSP_U32 u32ChanId;
    ICC_CHAN_ATTR_S *pstOpenParam;

    u32ChanId = UDI_GET_DEV_TYPE(param->devid);
    (BSP_VOID)BSP_UDI_SetPrivate(param->devid, (VOID*)u32ChanId);

    /* ��param �н������������� */
    pstOpenParam = (ICC_CHAN_ATTR_S *)param->pPrivate;
    sg_chnHandleTbl[u32ChanId] = (BSP_U32)handle;
    return BSP_ICC_Open(u32ChanId, pstOpenParam);
    return 0;
}
/*lint -restore*/

/*lint -save -e830 -e539*/
LOCAL BSP_S32 udiAdpIccInit(VOID)
{
    UDI_DRV_INTEFACE_TABLE* pDrvInterface = NULL;
    BSP_U32 u32Cnt;

    /* ����ص�����ָ���б� */
    pDrvInterface = (UDI_DRV_INTEFACE_TABLE*)osl_malloc(sizeof(UDI_DRV_INTEFACE_TABLE));
    /* coverity[dead_error_condition] */
    if (NULL == pDrvInterface)
    {
        /* coverity[dead_error_condition] */
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UDI, "NO Mem, line:%d\n", __LINE__, 0,0,0,0,0);/* [false alarm]:Disable fortify false alarm */

        /* coverity[dead_error_condition] */
        return (-1);/* [false alarm]:Disable fortify false alarm */
    }
	(void)memset_s((VOID*)pDrvInterface, sizeof(UDI_DRV_INTEFACE_TABLE), 0, sizeof(UDI_DRV_INTEFACE_TABLE));

    /* ֻ������Ҫʵ�ֵļ����ӿ� */
    pDrvInterface->udi_open_cb = (UDI_OPEN_CB_T)udiIccAdpOpen;
    pDrvInterface->udi_close_cb = (UDI_CLOSE_CB_T)BSP_ICC_Close;
    pDrvInterface->udi_write_cb = (UDI_WRITE_CB_T)BSP_ICC_Write;
    pDrvInterface->udi_read_cb = (UDI_READ_CB_T)BSP_ICC_Read;
    pDrvInterface->udi_ioctl_cb = (UDI_IOCTL_CB_T)BSP_ICC_Ioctl;

    /* ���� ICC ��ʹ��ͬһ����������ָ�� */
    for (u32Cnt = 0; u32Cnt < ICC_CHAN_NUM_MAX; u32Cnt++)
    {
        (BSP_VOID)BSP_UDI_SetCapability((UDI_DEVICE_ID_E)UDI_BUILD_DEV_ID(UDI_DEV_ICC, u32Cnt), UDI_ICC_CAPA);
        (BSP_VOID)BSP_UDI_SetInterfaceTable((UDI_DEVICE_ID_E)UDI_BUILD_DEV_ID(UDI_DEV_ICC, u32Cnt), pDrvInterface);
    }

    /*Custodial pointer 'pDrvInterface' (line 342) has not been freed or returned */
    return 0; /*lint !e429 */
}
/*lint -restore*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*lint +e715 +e785*/


