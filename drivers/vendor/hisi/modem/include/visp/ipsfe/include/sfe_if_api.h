

#ifndef _SFE_IF_API_H_
#define _SFE_IF_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ������IFģ������� */
typedef enum enumSFE_IF_ERRCODE
{
    SFE_IF_OK  = SFE_OK,                /* �����ɹ� */
    SFE_IF_ERR_BEGIN = SFE_IF_BEGIN_RET_CODE,/* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_IF_UPDATE_CMD_INVALID,          /* 1  ���½ӿ���Ϣʱ,�����ֲ�ʶ�� */
    SFE_IF_ERRPORTNO,                   /* 2  ���ӿ���Ŀ */ 
    SFE_IF_ISNOTINIT,                   /* 3  IFģ��δ��ʼ�� */
    SFE_IF_ISEXIST,                     /* 4  �ӿ��Ѿ����� */
    SFE_IF_ISNOTEXIST,                  /* 5  �ӿڲ����� */
    SFE_IF_ISNOTSUSTAINTYPE,            /* 6  ��֧�ָ����ͽӿ� */
    
    SFE_IF_ERRFRAMEORSLOTID,            /* 7  ��Ż�ۺŴ��� */

    SFE_IF_NULL_POINTER_INPUTPARA,      /* 8  �������ָ��Ϊ�� */
    SFE_IF_NULL_POINTER_INTFINFO,       /* 9  ����ӿ���Ϣָ��Ϊ�� */
    SFE_IF_NULL_POINTER_TYPEINFO,       /* 10 �ӿ�������Ϣָ��Ϊ�� */
    SFE_IF_NULL_POINTER_FULLINFO,       /* 11 �ӿ�ȫ����Ϣָ��Ϊ�� */

    SFE_IF_MALLOC_FAIL_FRAMESLOT,       /* 12 �����ۿռ�ʧ�� */
    SFE_IF_MALLOC_FAIL_TYPEINFO,        /* 13 ����ӿ������ڴ�ʧ�� */
    SFE_IF_MALLOC_FAIL_FULLINFO1,       /* 14 ����ӿ�ȫ����Ϣ�ڴ�ʧ�� */
    SFE_IF_MALLOC_FAIL_FULLINFO2,       /* 15 ��һ������ӿ�ȫ����Ϣ�ڴ�ʧ�� */    
    SFE_IF_MALLOC_FAIL_IFPOOL,          /* 16 ����ӿڻ�����Ϣʧ�� */
    SFE_IF_MALLOC_FAIL_IFUNIT,          /* 17 ����Դ��������ӿڵ�Ԫ��Ϣʧ�� */
    
    SFE_IF_ERRPORTTYPE,                 /* 18 �˿����ʹ��� */
    SFE_IF_GETBASEINFOFAIL,             /* 19 ��ȡ�ӿڻ�����Ϣʧ�� */
    SFE_IF_GETBASEINFOFAILFORUPDATE,    /* 20 ��ȡ���½ӿڻ�����Ϣʧ��*/
    SFE_IF_GETLINKINFOFAIL,             /* 21 ��ȡ��·����Ϣʧ�� */

    SFE_IF_ERRORIGIN,                   /* 22 �ӿ���Դ���� */
    SFE_IF_ERRCREATELINK,               /* 23 ������·�����нӿ���Ϣʧ�� */    
    SFE_IF_DELETELINKFAIL,              /* 24 ɾ����·����Ϣʧ�� */
    SFE_IF_UPDATELINKFAIL,              /* 25 ������·����Ϣʧ�� */
    SFE_IF_OVER_MAX_VRF,                /* 26 VRF�����Ƿ� */
    SFE_IF_ERRREDUCETTL,                /* 27 �ӿ�TTL�Ƿ��1ֵ���� */ 

    SFE_IF_ERR_PORTTYPE_CHECK_IFID,     /* 28 ���ӿ�ID��Ч��ʱ,�ӿ����ͷǷ� */
    SFE_IF_ERR_FRAMEID_CHECK_IFID,      /* 29 ���ӿ�ID��Ч��ʱ,�ӿڿ�ŷǷ� */
    SFE_IF_ERR_SLOTID_CHECK_IFID,       /* 30 ���ӿ�ID��Ч��ʱ,�ӿڲۺŷǷ� */
    SFE_IF_ERR_PORTNO_CHECK_IFID,       /* 31 ���ӿ�ID��Ч��ʱ,�ӿڶ˿ںŷǷ� */

    SFE_IF_NULL_IFTYPE_GET_IFINFO_POOLADDR,         /* 32 ��ȡ�ӿ���Ϣʱ,�ӿ����Ϳ��ƿ�Ϊ�� */
    SFE_IF_NULL_IFFULLINFO_GET_IFINFO_POOLADDR,     /* 33 ��ȡ�ӿ���Ϣʱ,�ӿ�ȫ����Ϣ���ƿ�Ϊ�� */
    SFE_IF_IS_NOT_EXIST_GET_IFINFO_POOLADDR,        /* 34 ��ȡ�ӿ���Ϣʱ,�ӿڲ����� */
    SFE_IF_BASEINFO_NULL_GET_IFINFO_POOLADDR,       /* 35 ��ȡ�ӿ���Ϣʱ,�ӿڻ�����Ϣ���ƿ�Ϊ�� */
    SFE_IF_LINKINFO_NULL_GET_IFINFO_POOLADDR,       /* 36 ��ȡ�ӿ���Ϣʱ,�ӿ�������Ϣ���ƿ�Ϊ�� */

    SFE_IF_DISABLE_ARPMISS_SWITCH_INVALID,          /* 37 ������̫�ӿ���Ϣʱ, ָ����ARP MISS�Ƿ�ʹ�ܱ�־�Ƿ� */

    SFE_IF_ERR_PORTTYPE_GETIFINFO,                  /* 38 �����շ�������,��ȡ�ӿ���Ϣ�ĵ�ַʱ,�ӿ����ͷǷ� */
    SFE_IF_ERR_FRAMEID_GETIFINFO,                   /* 39 �����շ�������,��ȡ�ӿ���Ϣ�ĵ�ַʱ,�ӿڿ�ŷǷ� */
    SFE_IF_ERR_SLOTID_GETIFINFO,                    /* 40 �����շ�������,��ȡ�ӿ���Ϣ�ĵ�ַʱ,�ӿڲۺŷǷ� */
    SFE_IF_ERR_PORTNO_GETIFINFO,                    /* 41 �����շ�������,��ȡ�ӿ���Ϣ�ĵ�ַʱ,�ӿڶ˿ںŷǷ� */

    SFE_IF_SWITCH_INVALID_SETTTLSWITCH,             /* 42 ���ýӿ�TTL��һ����ʱ,����ֵ�Ƿ� */
    SFE_IF_VCPU_NOT_INIT_CREATE,                    /* 43 VCPUû�г�ʼ��ʱ���ܽ��д����ӿڲ��� */
    SFE_IF_VCPU_NOT_INIT_DELETE,                    /* 44 VCPUû�г�ʼ��ʱ���ܽ���ɾ���ӿڲ��� */
    SFE_IF_VCPU_NOT_INIT_UPDATE,                    /* 45 VCPUû�г�ʼ��ʱ���ܽ��и��½ӿڲ��� */

    SFE_IF_NULL_POINTER_IFID,                       /* 46 ����IFID��ȡIF����ʱ���ӿ�IDΪNULL*/
    SFE_IF_ERR_GETIFINDEX,                          /* 47 ����IFID��ȡIF����ʱ���ӿڲ�����*/

    SFE_IF_ERRPORTNO_BYIFID,                        /* 48 �ӿڱ�ų����������ֵ */
    SFE_IF_ISNOTINIT_BYID,                          /* 49 IFģ��δ��ʼ�� */
    SFE_IF_ISNOTEXIST_BYID,                         /* 50 �ӿڲ����� */
    SFE_IF_NULL_POINTER_TYPEINFO_BYID,              /* 51 �ӿ�������Ϣָ��Ϊ�� */
    SFE_IF_NULL_POINTER_FULLINFO_BYID,              /* 52 �ӿ�ȫ����Ϣָ��Ϊ�� */
    SFE_IF_MALLOC_FAIL_IFUNIT_UPDATE,               /* 53 ����Դ��������ӿڵ�Ԫ��Ϣʧ�� */
    SFE_IF_ERRPORTTYPE_BYID,                        /* 54 �˿����ʹ��� */
    SFE_IF_GETBASEINFOFAIL_DELETE,                  /* 55 ��ȡ�ӿڻ�����Ϣʧ�� */
    SFE_IF_GETBASEINFOFAIL_UPDATE,                  /* 56 ��ȡ�ӿڻ�����Ϣʧ�� */
    SFE_IF_GETBASEINFOFAIL_IF,                      /* 57 ��ȡ�ӿڻ�����Ϣʧ�� */
    SFE_IF_GETBASEINFOFAIL_ADDR,                    /* 58 ��ȡ�ӿڻ�����Ϣʧ�� */
    SFE_IF_GETLINKINFOFAIL_ADDR,                    /* 59 ��ȡ��·����Ϣʧ�� */
    SFE_IF_ERRORIGIN_DELETE,                        /* 60 �ӿ���Դ���� */
    SFE_IF_ERRORIGIN_UPDATE,                        /* 61 �ӿ���Դ���� */
    
    SFE_IF_MAX
}SFE_IF_ERRCODE_E;

/* �������Ӧ�Ľӿ�����ö�ٶ��� */
typedef enum enumSFE_IF_TYPE
{
    SFE_IF_NULL = 0,
    SFE_IF_INLOOPBACK,
    SFE_IF_LOOPBACK,
    SFE_IF_ETH,
    SFE_IF_PPP,
    
    SFE_IF_TYPEMAX = 8
}SFE_IF_TYPE_E;
VOID SFE_ShowAllIfInfo(VOID);

#ifdef  __cplusplus
}
#endif

#endif


