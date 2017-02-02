/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_sh_disp.h
*
*  Project Code: VISPV100R005
*   Module Name: PPPMUX
*  Date Created: 2006-5-9
*        Author: ZhouTong(43740)
*   Description: PPPMUX��صĲ�ѯ��������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-5-9  ZhouTong(43740)    Create
*
*******************************************************************************/
#ifndef _PPPMUX_SH_DISP_H_
#define _PPPMUX_SH_DISP_H_

#ifdef  __cplusplus
extern  "C"{
#endif

/* ��ʾָ���ӿ���ص�������Ϣ */
VOID PPPMUX_ShowMuxConfig(ULONG ulIfIndex);

/* ��ʾָ���ӿڵ�PPPMUXCPЭ��Э�̽��*/
VOID PPPMUX_ShowMuxNegoResult(ULONG ulIfIndex);

/* ��ʾָ���ӿڵ�PPPMUXͳ����Ϣ */
VOID PPPMUX_ShowMuxStat(ULONG ulIfIndex);

/* ����ƽ��ֵ */
ULONG PPPMUX_GetAverage(ULONG ulDividend, ULONG ulDivisor, ULONG* pulAvgHigh, ULONG* pulAvgLow);

/*DEBUG��Ϣ���*/
VOID PPPMUX_DebugOutput(CHAR *pszMsg);


#ifdef  __cplusplus
}
#endif

#endif/*# end of _PPPMUX_SH_DISP_H_ */

