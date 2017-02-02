
#ifndef _SFE_ADDR_API_H_
#define _SFE_ADDR_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ������ADDRģ������� */
typedef enum enumSfeAddrErrCode
{
    SFE_ADDR_OK = SFE_OK,                               /* �����ɹ� */
    SFE_ADDR_ERR_BEGIN = SFE_ADDR_BEGIN_RET_CODE,       /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_ADDR_IFID_INVALID_ADD,                          /* 1  Ҫ��ӵ�ַ�Ľӿ�ָ��Ϊ�� */
    SFE_ADDR_IP_INVALID_ADD,                            /* 2  Ҫ��ӵ�ַ�Ĳ��Ϸ� */
    SFE_ADDR_GETBASEINFOFAIL_ADD,                       /* 3  ��ӵ�ַ,��ȡ�ӿ�base�ڵ�ʧ�� */
    SFE_ADDR_IP_NUM_MAX_ADD,                            /* 4  ��ӵ�ַ,�ӿڵĵ�ַ��Ŀ�Ѿ��ﵽ���ֵ */
    SFE_ADDR_MALLOC_FAIL_ADDIPADDR_ADD,                 /* 5  ��ӵ�ַ,��ȡ��ַ�������ݽṹ����ʧ�� */
    SFE_ADDR_GETBASEINFOFAILFORUPDATE_ADD,              /* 6  ��ӵ�ַ,��ȡ��ַ�������ݽṹ�ڵ�ʧ�� */
    SFE_ADDR_IP_HAS_SETTED_ADD,                         /* 7  ��ӵ�ַ,IP����ͳһ�ӿ����ù� */
    SFE_ADDR_IFID_INVALID_DEL,                          /* 8  Ҫɾ����ַ�Ľӿ�ָ��Ϊ�� */
    SFE_ADDR_IP_INVALID_DEL,                            /* 9  Ҫɾ����ַ�Ľӿ�ָ��Ϊ�� */
    SFE_ADDR_GETBASEINFOFAIL_DEL,                       /* 10 ɾ����ַ,��ȡ�ӿ�base�ڵ�ʧ�� */
    SFE_ADDR_IP_NOT_EXIST_DEL,                          /* 11 ɾ����ַ,Ҫɾ���ĵ�ַ������ */
    SFE_ADDR_FREE_IPADDR_FAIL_DEL,                      /* 12 ɾ����ַ,��Դ���ͷŵ�ַ�ڵ�ʧ�� */
    SFE_ADDR_GET_SFE_IPADDR_MAX_NUM_PRECFG_FAIL,        /* 13 ��ַ�����ʼ��,��ȡ��ַ��Դ��ʼ������ʧ�� */
    SFE_ADDR_GET_SFE_IPADDR_MAX_NUM_PER_IF_PRECFG_FAIL, /* 14 ��ַ�����ʼ��,��ȡÿ���ӿ���������IP ADDR��Ŀʧ�� */
    SFE_ADDR_ALLOC_IP_ADDR_POOL_FAIL,                   /* 15 ��ַ�����ʼ��,��ʼ��IP ADDR��Դ��ʧ�� */

}SFE_ADDR_ERR_CODE_E;


UINT32 SFE_ADDR_AddIpAddr(UINT32 u32IpAddr, UINT32 u32SubnetMask, SFE_MBUF_IFID_S *pstIfId);


UINT32 SFE_ADDR_DelIpAddr(UINT32 u32IpAddr, UINT32 u32SubnetMask, SFE_MBUF_IFID_S *pstIfId);


VOID SFE_ADDR_ShowIpAddr(VOID);


#ifdef  __cplusplus
}
#endif

#endif

