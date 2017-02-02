#ifndef NSR_OSPF_API_INCLUDED
#define NSR_OSPF_API_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "nsr_ospf_api_def.h"

/*���ݵ�OSPF������Ϣ��ѯAPI*/
ULONG NSR_Entity_Open(ULONG *pulSessionId, NSR_OSPF_ENTITY_FILTER *pstFilter);
ULONG NSR_Entity_Get_First(ULONG ulSessionId, NSR_OSPF_ENTITY_REPL_SHOW *pstShow);
ULONG NSR_Entity_Get_Next(ULONG ulSessionId, NSR_OSPF_ENTITY_REPL_SHOW *pstShow);
VOID NSR_Show_Entity(USHORT usProcessId);

/*���ݵ�OSPF�ӿڲ�ѯAPI*/
ULONG NSR_If_Open(ULONG *pulSessionId, NSR_OSPF_IF_FILTER *pstFilter);
ULONG NSR_If_Get_First(ULONG ulSessionId, NSR_OSPF_IF_REPL_SHOW *pstShow);
ULONG NSR_If_Get_Next(ULONG ulSessionId, NSR_OSPF_IF_REPL_SHOW *pstShow);
VOID NSR_Show_If(USHORT usProcessId);


/*���ݵ�OSPF�ھӲ�ѯAPI*/
ULONG NSR_Nbr_Open(ULONG *pulSessionId, NSR_OSPF_NBR_FILTER *pstFilter);
ULONG NSR_Nbr_Get_First(ULONG ulSessionId, NSR_OSPF_NBR_REPL_SHOW *pstShow );
ULONG NSR_Nbr_Get_Next(ULONG ulSessionId, NSR_OSPF_NBR_REPL_SHOW *pstShow);
VOID NSR_Show_Nbr(USHORT usProcessId);


/*���ݵ�OSPF�����ѯAPI*/
ULONG NSR_Area_Open(ULONG *pulSessionId, NSR_OSPF_AREA_FILTER *pstFilter);
ULONG NSR_Area_Get_First(ULONG ulSessionId, NSR_OSPF_AREA_REPL_SHOW *pstShow);
ULONG NSR_Area_Get_Next(ULONG ulSessionId, NSR_OSPF_AREA_REPL_SHOW *pstShow);
VOID NSR_Show_Area(USHORT usProcessId);


/*���ݵ�OSPF LSA��ѯAPI*/
ULONG NSR_LSDB_Open(ULONG *pulSessionId, NSR_OSPF_LSDB_FILTER *pstFilter);
ULONG NSR_LSDB_Get_First(ULONG ulSessionId, NSR_OSPF_LSA_HDR_REPL_SHOW_S *pstOSPFLSDBShow);
ULONG NSR_LSDB_Get_Next(ULONG ulSessionId, NSR_OSPF_LSA_HDR_REPL_SHOW_S *pstOSPFLSDBShow);
VOID NSR_Show_LSDB(USHORT usProcessId, UCHAR ucLSAType);


/*�ͷŲ�ѯ�ӿڴ򿪵ĻỰ*/
ULONG NSR_Session_Close(ULONG ulSessionId);

ULONG NSR_Get_NSR_State_Info(NSR_STATE_INFO_SHOW *pstShow);
VOID NSR_Show_NSR_Info();

ULONG NSR_Get_Performance_Stat(NSR_PERFORMANCE_STAT_SHOW *pstShow);
ULONG NSR_Clear_Performance_Stat();
VOID NSR_Show_Performance_Stat();

ULONG NSR_Get_Message_Stat(NSR_MSG_STAT_SHOW *pstShow);
ULONG NSR_Clear_Message_Stat();
VOID NSR_Show_Message_Stat();
VOID NSR_Show_NSR_I3_Info();

/*ҵ��ͳ�Ʋ�ѯapi*/
ULONG NSR_Business_Stat_Open(ULONG *pulSessionId, NSR_BUSINESS_STAT_FILTER *pstFilter);
ULONG NSR_Business_Stat_Get_First(ULONG ulSessionId, NSR_OSPF_BUSINESS_STAT *pstShow);
ULONG NSR_Business_Stat_Get_Next(ULONG ulSessionId, NSR_OSPF_BUSINESS_STAT *pstShow);
VOID NSR_Show_Business_Stat(USHORT usProcessId);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

