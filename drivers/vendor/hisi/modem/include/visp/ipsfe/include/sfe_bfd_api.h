

#ifndef _SFE_BFD_API_H_
#define _SFE_BFD_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ������BFDģ������� */
typedef enum enumSfeBfdErrCode
{ 
    SFE_BFD_OK = SFE_OK,                        /* �����ɹ� */
    SFE_BFD_ERR_BEGIN = SFE_BFD_BEGIN_RET_CODE, /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_BFD_GET_SINGLEHOP_PROCMODE_PRECFG_FAIL, /* 1  ��ȡBFD�����Ự����ģʽԤ����ֵʧ�� */
    SFE_BFD_GET_SESS_PRECFG_FAIL,               /* 2  ��ȡ���BFD�ỰԤ����ֵʧ�� */
    SFE_BFD_MALLOC_FAIL_GLOBAL_NODE_NUM,        /* 3  ����ȫ��BFD�����ڵ�˼乲���ڴ�ʱʧ�� */
    SFE_BFD_MALLOC_FAIL_VRF,                    /* 4  ����BFD VRF��Ϣ���鹲���ڴ�ʱʧ�� */
    SFE_BFD_ADD_NAMEDB_VRF,                     /* 5  ��BFD VRF��Ϣ�����ַ��ӵ����ֿ�ʧ�� */
    SFE_BFD_MALLOC_FAIL_SESS_CTRL,              /* 6  ����ÿ��VRF�µ�BFD��Ϣ���ƿ�ʧ�� */
    SFE_BFD_MALLOC_SESSION_POOL,                /* 7  ����BFD�Ự��ϢPOOL��Դ��ʧ�� */
    SFE_BFD_PPI_CMD_INVALID,                    /* 8  BFD PPI�����ֲ��Ϸ� */

    SFE_BFD_GLOBAL_VAR_NULL_POINTER_OPER,       /* 9  ����BFD�Ựʱ, �˼乲�����ΪNULL */
    SFE_BFD_INPUT_NULL_POINTER_OPER,            /* 10 ����BFD�Ựʱ, �������ΪNULL */
    SFE_BFD_VRF_WRONG_OPER,                     /* 11 ����BFD�Ựʱ, VRF�����������Ϸ� */
    SFE_BFD_SESSION_ID_WRONG_OPER,              /* 12 ����BFD�Ựʱ, BFD�ỰID���Ϸ� */
    
    SFE_BFD_NUM_EXCEED_PRECFG,                  /* 13 ���BFD�Ựʱ, ��ǰBFD�Ự�����Ѿ��ﵽ��Ԥ���ù�� */
    SFE_BFD_POOL_ALLOC_UNIT_FAIL_ADD,           /* 14 ���BFD�Ựʱ, ����BFD�ỰPOOL��Դ�ؽڵ�ʧ�� */
    SFE_BFD_GET_POOLNODEADDR_FAIL_ADD,          /* 15 ���BFD�Ựʱ, ����POOL�ڵ�������ȡ�ڵ��ַʧ�� */
    SFE_BFD_CREATE_SEND_TIMER_FAIL_ADD,         /* 16 ���BFD�Ựʱ, ������ʱ���Ͷ�ʱ��ʧ�� */    
    SFE_BFD_CREATE_DETECT_TIMER_FAIL_ADD,       /* 17 ���BFD�Ựʱ, ������ʱ̽�ⶨʱ��ʧ�� */    

    SFE_BFD_DETECT_MODE_INVALID_CHANGE,         /* 18 ����BFD�Ự��Ϣʱ, BFD̽��ģʽ���Ϸ� */
    SFE_BFD_SESSION_NOT_EXIST_CHANGE,           /* 19 ����BFD�Ự��Ϣʱ, BFD�Ự������ */
    SFE_BFD_GET_OLD_POOLNODEADDR_FAIL_CHANGE,   /* 20 ����BFD�Ự��Ϣʱ, �����Ѿ����ڵ�POOL�ڵ�������ȡ�ڵ��ַʧ�� */
    SFE_BFD_POOL_ALLOC_UNIT_FAIL_CHANGE,        /* 21 ����BFD�Ự��Ϣʱ, ����BFD�ỰPOOL��Դ�ؽڵ�ʧ�� */
    SFE_BFD_GET_NEW_POOLNODEADDR_FAIL_CHANGE,   /* 22 ����BFD�Ự��Ϣʱ, �����µ�POOL�ڵ�������ȡ�ڵ��ַʧ�� */

    SFE_BFD_SESSION_NOT_EXIST_DOWN,             /* 23 BFD�ỰDOWNʱ��BFD�Ự������ */
    SFE_BFD_GET_POOLNODEADDR_FAIL_DOWN,         /* 24 BFD�ỰDOWNʱ�������Ѿ����ڵ�POOL�ڵ�������ȡ�ڵ��ַʧ�� */

    SFE_BFD_SESSION_NOT_EXIST_DEL,              /* 25 BFD�ỰDELʱ��BFD�Ự������ */   
    SFE_BFD_GET_POOLNODEADDR_FAIL_FREE,         /* 26 �ͷ�BFD�Ự��Ϣʱ�������Ѿ����ڵ�POOL�ڵ�������ȡ�ڵ��ַʧ�� */
    SFE_BFD_GLOBAL_VAR_NULL_POINTER_DELALL,     /* 27 ɾ������BFD�Ựʱ, �˼乲�����ΪNULL */

    SFE_BFD_GLOBAL_VAR_NULL_POINTER_GETBYID,    /* 28 ָ��ID��ȡBFD�Ựʱ, �˼乲�����ΪNULL */
    SFE_BFD_VRF_WRONG_GETBYID,                  /* 29 ָ��ID��ȡBFD�Ựʱ, VRF�����������Ϸ� */
    SFE_BFD_SESSION_ID_WRONG_GETBYID,           /* 30 ָ��ID��ȡBFD�Ựʱ, BFD�ỰID���Ϸ� */
    SFE_BFD_NOT_FOUND_GETBYID,                  /* 31 ָ��ID��ȡBFD�Ựʱ, BFD�Ự������*/
    SFE_BFD_GET_POOLNODEADDR_FAIL_GETBYID,      /* 32 ָ��ID��ȡBFD�Ựʱ, �����µ�POOL�ڵ�������ȡ�ڵ��ַʧ�� */
    
    SFE_BFD_PKT_VRF_INVALID_INPUT,              /* 33 ����BFD����ʱ, �����е�VRF������Ự�еĲ���ͬ */
    SFE_BFD_PKT_DSTIP_INVALID_INPUT,            /* 34 ����BFD����ʱ, �����е�Ŀ�ĵ�ַIP��Ự�еĲ���ͬ */
    SFE_BFD_PKT_SRCIP_INVALID_INPUT,            /* 35 ����BFD����ʱ, �����е�ԴIP��Ự�еĲ���ͬ */
    SFE_BFD_PKT_TTL_INVALID_INPUT,              /* 36 ����BFD����ʱ, ����BFD�Ự�����е�TTL������255 */
    SFE_BFD_PKT_IFTYPE_INVALID_INPUT,           /* 37 ����BFD����ʱ, �����еĽӿ�������Ự�еĲ���ͬ */
    SFE_BFD_PKT_FRAMID_INVALID_INPUT,           /* 38 ����BFD����ʱ, �����еĿ����Ự�еĲ���ͬ */
    SFE_BFD_PKT_SLOTID_INVALID_INPUT,           /* 39 ����BFD����ʱ, �����еĲۺ���Ự�еĲ���ͬ */
    SFE_BFD_PKT_PORTNO_INVALID_INPUT,           /* 40 ����BFD����ʱ, �����еĶ˿ں���Ự�еĲ���ͬ */
    SFE_BFD_ENCAP_FAIL_UIDRESV_ENLINKHEADER,    /* 41 ��װ��·��ͷʧ��, ��·�㴦�����ڲ��ͷű���,�����߲����ͷű��� */
    SFE_BFD_ENCAP_FAIL_UIDERR_ENLINKHEADER,     /* 42 ��װ��·��ͷʧ��, ��·�㴦�������ͷű���,�����߱����ͷű��� */
    SFE_BFD_IF_TYPE_INVALID_ENLINKHEADER,       /* 43 ��װ��·��ͷʧ��, �ӿ����ʹ��� */
    SFE_BFD_VCPU_NOT_INIT_OPER,                 /* 44 ����BFD�Ựʱ, VCPUû�г�ʼ�� */
    SFE_BFD_SESS_CTRL_NULL_POINTER_OPER,        /* 45 ����BFD�Ựʱ, VRF�µ�BFD�Ự���ƿ�����˼乲���ڴ����ΪNULL */
    SFE_BFD_VCPU_NOT_INIT_DELALL,               /* 46 ɾ������BFD�Ựʱ, VCPUû�г�ʼ�� */
    SFE_BFD_SESS_CTRL_NULL_POINTER_GETBYID,     /* 47 ָ��ID��ȡBFD�Ựʱ, VRF�µ�BFD�Ự���ƿ�����˼乲���ڴ����ΪNULL */

    SFE_BFD_SET_DEBUG_VRF_ERR,                  /* 48 ����BFD�Ự���Կ���ʱ,VRF�������� */
    SFE_BFD_SET_DEBUG_SID_ERR,                  /* 49 ����BFD�Ự���Կ���ʱ,session id���� */
    SFE_BFD_SET_DEBUG_BFDVRF_SHARE_NULL,        /* 50 ����BFD�Ự���Կ���ʱ,����ռ�ΪNULL */
    SFE_BFD_SET_DEBUG_SWITCH_ERR,               /* 51 ����BFD�Ự���Կ���ʱ,���ش��� */
    SFE_BFD_SET_DEBUG_SESSION_NOEXIST,          /* 52 ����BFD�Ự���Կ���ʱ,�Ự������ */

    SFE_BFD_GET_DEBUG_VRF_ERR,                  /* 53 ��ȡBFD�Ự���Կ���ʱ,VRF�������� */
    SFE_BFD_GET_DEBUG_SID_ERR,                  /* 54 ��ȡBFD�Ự���Կ���ʱ,session id���� */
    SFE_BFD_GET_DEBUG_BFDVRF_SHARE_NULL,        /* 55 ��ȡBFD�Ự���Կ���ʱ,����ռ�ΪNULL */
    SFE_BFD_GET_DEBUG_POINT_NULL,               /* 56 ��ȡBFD�Ự���Կ���ʱ,����Ϊ��ָ�� */
    SFE_BFD_GET_DEBUG_SESSION_NOEXIST,          /* 57 ��ȡBFD�Ự���Կ���ʱ,�Ự������ */
    SFE_BFD_MALLOC_FAIL_ALL_SESSION_DEBUG,      /* 58 �����ȫ���Ự�ĵ��Կ��غ˼乲���ڴ�ʱʧ�� */

    SFE_BFD_GET_STAT_BFD_NOT_INIT,              /* 59 ���BFD KEY��Ϣʱ, BFDģ��û�г�ʼ�� */
    SFE_BFD_GET_STAT_VRF_ERR,                   /* 60 ���BFD KEY��Ϣʱ, vrf���Ϸ� */
    SFE_BFD_GET_STAT_SESS_CTRL_NULL,            /* 61 ���BFD KEY��Ϣʱ, VRF�µ�BFD�Ự���ƿ�����˼乲���ڴ����ΪNULL */
    SFE_BFD_GET_STAT_SESSID_ERR,                /* 62 ���BFD KEY��Ϣʱ, �ỰID����ȷ */
    SFE_BFD_GET_STAT_SESSID_NOTEXIST,           /* 63 ���BFD KEY��Ϣʱ, �Ự������ */

}SFE_BFD_ERR_CODE_E;


extern UINT32 SFE_BFD_DelAllBfdSession(VOID);


extern UINT32 SFE_BFD_SetBfdSwitch(UINT32 u32VrfIndex, UINT32 u32SessionId, UINT32 u32IsDebug);


extern UINT32 SFE_BFD_GetBfdSwitch(UINT32 u32VrfIndex, UINT32 u32SessionId, UINT32 *pu32IsDebug);


#ifdef  __cplusplus
}
#endif

#endif


