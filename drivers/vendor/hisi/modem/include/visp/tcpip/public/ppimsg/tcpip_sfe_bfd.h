
#ifndef _TCPIP_SFE_BFD_H_
#define _TCPIP_SFE_BFD_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ������̽�⵽BFD DOWN���õĿ�����֪ͨ���� */
extern ULONG (*g_pfSfeBfdDetectDownNotify)(ULONG ulSessionID, ULONG ulVrfIndex);

extern UINT32 TCPIP_SFE_BFD_DetectDownNotify(UINT32 u32VrfIndex, UINT32 u32SessionId);

#ifdef  __cplusplus
}
#endif

#endif

