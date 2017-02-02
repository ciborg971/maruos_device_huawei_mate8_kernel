#ifndef CSDR_BASEADDR_INFO_H
#define CSDR_BASEADDR_INFO_H
#include "stdint.h"

typedef struct
{
    uint32_t uwBbpCdmaBaseAddr;                                    /*  */
    uint32_t uwBbpMasterBaseAddr;                               /*  */
    uint32_t uwEdmaBaseAddr;                                    /*  */
    uint32_t uwIpcmBaseAddr;                                    /*  */
    uint32_t uwSocpBaseAddr;                                    /*  */
    uint32_t uw32kBaseAddr;                                     /*  */
    uint32_t uwSysctrlBaseAddr;                                 /*  */
    uint32_t uwAbbCfgAddr;                                      /*  */
    uint32_t uwBbpcomAddr;                                      /*  */
    uint32_t uwBbpcomOnAddr;                                    /*  */
    uint32_t uwBbpGlbOnAddr;                                    /*  */
    uint32_t uwWbbpBaseAddr;                                    /*  */
    uint32_t uwBbpcom2Addr;                                     /*  */
    uint32_t uwPmuSsiAddr;                                     /*  */
    uint32_t uwDataMailboxAddr;                                 /*  */
}CSDR_PLAT_BASEADDR_STRU;

#endif