#ifndef __MDRV_CCORE_STUB_H__
#define __MDRV_CCORE_STUB_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_public.h"
#include "mdrv_memory.h"

#if defined(CHIP_BB_HI6210)
#include "mdrv_stub_v8.h"
#else
#include "mdrv_stub_v7.h"
#endif

#ifdef __cplusplus
}
#endif
#endif
