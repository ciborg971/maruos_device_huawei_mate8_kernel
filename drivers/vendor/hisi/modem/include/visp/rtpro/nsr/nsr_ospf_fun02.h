/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nsr_ospf_fun02.h
*
*  Project Code: Dopra V3R2
*   Module Name: OSPF NSR�����ṩ��OSPF NSRģ��书�ܺ���
*  Date Created: 2013-10-25
*        Author: guojianjun178934
*   Description: ��ͷ�ļ����ṩ�ĺ�����κͷ���ֵ��Ҫ������OSPF�ڲ���������ݽṹ
*                �������Ҫ�����������ļ�nsr_ospf_fun01.h������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-10-25   guojianjun178934        Create
*
*******************************************************************************/
#ifndef NSR_OSPF_FUN02_INCLUDED
#define NSR_OSPF_FUN02_INCLUDED

NBB_VOID nsr_ospf_check_pre_start_network(QOPM_IF_CB *if_cb  NBB_CCXT_T NBB_CXT);
NBB_VOID nsr_ospf_check_pre_start_router(QOPM_AREA_CB *area_cb  NBB_CCXT_T NBB_CXT);
NBB_VOID nsr_ospf_check_lsa_consistencies(QOPM_AREA_CB *area_cb);
NBB_ULONG nsr_ospf_nbr_activate(QOPM_NBR_CB *nbr_cb);
NBB_VOID nsr_ospf_process_lsa_for_restart(QOPM_LSDB_CB *db_entry_ptr
                                                          NBB_CCXT_T NBB_CXT);
NBB_VOID nsr_ospf_check_adj_reestablished(NBB_CXT_T NBB_CXT);                                                          

/*�жϱ��ݵ�RouterIDͬ��ǰ��RouterID�Ƿ�һ��*/
#define NSR_VALID_REPL_ROUTER_ID(REPL_RID, CUR_RID) \
  (!QOPM_IS_RTR_ID_ZERO((REPL_RID), QOPM_ID_LEN) && \
   !NBB_MEMCMP((REPL_RID), (CUR_RID), QOPM_ID_LEN))


#endif

