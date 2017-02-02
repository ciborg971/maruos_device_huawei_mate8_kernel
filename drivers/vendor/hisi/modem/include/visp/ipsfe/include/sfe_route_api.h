

#ifndef _SFE_ROUTE_API_H_
#define _SFE_ROUTE_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ������·��ģ������� */
typedef enum enumSfeRouteCode
{
    SFE_RT_SUCCESS = SFE_OK,               /* �����ɹ� */
    SFE_RT_ERR_BEGIN = SFE_ROUTE_BEGIN_RET_CODE,/* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_RT_NOTINIT,                        /* 1  ����û�г��Ի��ɹ� */
    SFE_RT_NULL_PARA_ERR,                  /* 2  ָ��Ϊ�� */
    SFE_RT_OPER_ERR,                       /* 3  �������ͷǷ� */
    SFE_RT_VRF_PRECFG_ERR,                 /* 4  ��ȡVRFԤ���ø���ʧ�� */
    SFE_RT_ROUTE_PRECFG_ERR,               /* 5  ��ȡ��ͨ·�ɽڵ�Ԥ���ø���ʧ�� */
    SFE_RT_ALLOC_ROUTE_ERR,                /* 6  ����·�ɽڵ�ʧ�� */
    SFE_RT_ALLOCBALANCE1_ERR,              /* 7  ����ƽ��·�ɽڵ�ʧ�� */
    SFE_RT_ALLOCBALANCE2_ERR,              /* 8  ����ƽ��·�ɽڵ�ʧ�� */
    SFE_RT_ALLOC_ROUTE_ADD_CURRLAYER1_ERR, /* 9  ����·�ɽڵ�ʧ�� */
    SFE_RT_ALLOC_ROUTE_ADD_CURRLAYER2_ERR, /* 10 ����·�ɽڵ�ʧ�� */
    SFE_RT_ALLOC_ROUTE_ADD_COVERTREE1_ERR, /* 11 ����·�ɽڵ�ʧ�� */
    SFE_RT_ALLOC_ROUTE_ADD_COVERTREE2_ERR, /* 12 ����·�ɽڵ�ʧ�� */
    SFE_RT_MALLOC_L1_TABLE_ERR,            /* 13 ����L1����ʧ�� */
    SFE_RT_ALLOCL2L3INDEX_EXCEED24_ERR,    /* 14 ����L2L3�����ڵ�ʧ�� */
    SFE_RT_ALLOCL2L3INDEX_ERR,             /* 15 ����L2L3�����ڵ�ʧ�� */
    SFE_RT_MASK_ERR,                       /* 16 ���볤�ȷǷ� */
    SFE_RT_OVER_MAX_VRF_ERR,               /* 17 VRF����֧�����ֵ */
    SFE_RT_SAME_ORIGIN_ERR,                /* 18 ����·����ͬ,������Դ��ͬ */
    SFE_RT_SAME_ORIGIN_ADDBALANCE_ERR,     /* 19 ����·����ͬ,������Դ��ͬ */
    SFE_RT_MAX_BALANCE_ERR,                /* 20 ��ͬһ��Ŀ�ĵ�ƽ��·�ɴﵽ���ֵ */
    SFE_RT_OVER_LAYER_ERR,                 /* 21 ���·�ɳ���3��,�����볤�ȴ���32 */
    SFE_RT_POOL_L2L3_ERR,                  /* 22 ��ʼ��POOL L2L3����ʧ�� */
    SFE_RT_POOL_ROUTE_NODE_ERR,            /* 23 ��ʼ��POOL��ͨ·�ɽڵ�ʧ�� */
    SFE_RT_POOL_BLANCE_ROUTE_ERR,          /* 24 ��ʼ��POOLƽ��·�ɽڵ�ʧ�� */
    SFE_RT_BALANCE_ROUTE_PRECFG_ERR,       /* 25 ��ȡƽ��·�ɽڵ�Ԥ���ø���ʧ�� */
    SFE_RT_ADD_COVER_TREE_ERR,             /* 26 ��ӵ�������ʧ�� */
    SFE_RT_DEL_NOROUTE_ERR,                /* 27 ɾ��·��ʧ��,���������·�� */
    SFE_RT_DEL_SAMEROUTE_ERR,              /* 28 ����ɾ����Դ��ͬ��·�ɱ��� */
    SFE_RT_DEL_SAMEBALROUTE_ERR,           /* 29 ����ɾ����Դ��ͬ��ƽ��·�ɱ��� */
    SFE_RT_DEL_OVER_LAYER_ERR,             /* 30 ɾ��·�ɳ���3��,�����볤�ȴ���32 */
    SFE_RT_DEL_CURRLAYER_ERR,              /* 31 �ӵ�ǰ�����ɾ��ʧ�� */
    SFE_RT_DEL_NOROUTE1_ERR,               /* 32 ɾ��·��ʧ��,L1������Ĭ��·�ɲ�����*/
    SFE_RT_DEL_NOROUTE2_ERR,               /* 33 ɾ��·��ʧ��,L2�����µ�ַƫ�Ʋ�����·�� */
    SFE_RT_DEL_NOROUTE3_ERR,               /* 34 ɾ��·��ʧ��,L2������Ĭ��·�ɲ�����*/
    SFE_RT_DEL_NOROUTE4_ERR,               /* 35 ɾ��·��ʧ��,L3�����µ�ַƫ�Ʋ�����·�� */
    SFE_RT_DEL_NOROUTE5_ERR,               /* 36 ɾ��·��ʧ��,L3������Ĭ��·�ɲ�����*/
    SFE_RT_DEL_NOROUTE6_ERR,               /* 37 ɾ��·��ʧ��,�����ڲ��쳣,ָ��Ϊ�� */
    SFE_RT_DEL_NOROUTE7_ERR,               /* 38 ɾ��·��ʧ��,Ĭ��·���²��������·�� */
    SFE_RT_DEL_NOROUTE8_ERR,               /* 39 ɾ��·��ʧ��,ƽ��·���²��������·�� */
    SFE_RT_DEL_NOROUTE9_ERR,               /* 40 ɾ��·��ʧ��,�����������²����ڸ�·�� */
    SFE_RT_DEL_NOROUTE10_ERR,              /* 41 ɾ��·��ʧ��,��ǰ�ڵ��ɾ��·�ɲ�ƥ�� */
    SFE_RT_DEL_SAMEROUTE_COVERTREE_ERR,    /* 42 ����ɾ����Դ��ͬ��·�ɱ��� */
    SFE_RT_SEARCH_UNREACH_VRF_INVALID,     /* 43 ���ڲ���VRF�������ֵ���²���·��ʧ�� */
    SFE_RT_SEARCH_UNREACH_IN_DEFAULT_ROUTE,/* 44 ����Ĭ��·��ʧ�� */
    SFE_RT_SEARCH_UNREACH_L2L3,            /* 45 ·�ɲ���ʧ��*/
    SFE_RT_SEARCH_UNREACH,                 /* 46 ·�ɲ���ʧ��*/
    SFE_RT_SEARCH_UNREACH_IPV4,            /* 47 ·�ɲ���ʧ��*/
    SFE_RT_SEARCH_BLACKHOLE,               /* 48 ·���Ǻڶ�·�� */
    SFE_RT_OPER_INTF_ERR,                  /* 49 ����·�ɽӿڷǷ� */
    SFE_RT_SEARCH_BYIP_VRF_PARA_ERR,       /* 50 ·�ɲ��Ҳ�������*/
    SFE_RT_SEARCH_BYIP_NOT_EXIST,          /* 51 ·�ɲ���δ����*/
    SFE_RT_GET_FIB_VRF_ERR,                /* 52 ��ȡ·��ʱVRF�������� */
}SFE_ROUTE_ERR_CODE;
VOID SFE_ShowAllRouteInfo(VOID);

#ifdef  __cplusplus
}
#endif

#endif


