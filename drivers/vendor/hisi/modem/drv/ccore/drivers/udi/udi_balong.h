
#ifndef    _BSP_UDI_DRV_H_
#define    _BSP_UDI_DRV_H_

#include "product_config.h"
#include "bsp_om.h"
#include <bsp_udi.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define UDI_GET_MAIN_DEV_ID(id) (((id) & 0xff00) >> 8 )
#define UDI_GET_DEV_TYPE(id) (((id) & 0x00ff))
#define UDI_UNUSED_PARAM(param) //(param=param)

#define BSP_ASSERT(expr) \
{\
    if (!(expr)) { \
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UDI,\
			"Memory Malloc Error, line:%d\n", __LINE__, 0, 0, 0, 0, 0);\
        return BSP_ERROR;\
    } \
}


UDI_HANDLE BSP_UDI_ICC_ChnToHandle(BSP_U32 u32Chn);
BSP_S32 BSP_UDI_SetPrivate(UDI_DEVICE_ID_E devId, VOID* pPrivate);
BSP_S32 BSP_UDI_SetCapability(UDI_DEVICE_ID_E devId, BSP_U32 u32Capability);
BSP_S32 BSP_UDI_SetInterfaceTable(UDI_DEVICE_ID_E devId, UDI_DRV_INTEFACE_TABLE *pDrvInterface);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BSP_UDI_DRV_H_ */


