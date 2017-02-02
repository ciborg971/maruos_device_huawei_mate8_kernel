

#ifndef _SFE_ETH_API_H_
#define _SFE_ETH_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ������ETHģ������� */
typedef enum enumSFE_ETH_ERRCODE
{
    SFE_ETH_OK  = SFE_OK,                           /* �����ɹ� */    
    SFE_ETH_ERR_BEGIN = SFE_ETH_BEGIN_RET_CODE,     /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_ETH_NULL_POINTER_INPUTPARA,                 /* 1  �������Ϊ��ָ�� */    
    SFE_ETH_OPERERR,                                /* 2  ���������ִ��� */

    SFE_ETH_MALLOC_FAIL_ETHPOOL,                    /* 3  ����Eth Pool��Դ��ʧ�� */
    SFE_ETH_MALLOC_FAIL_ETHUNIT,                    /* 4  ��Eth Pool�л�ȡEth��Ԫ��Ϣʧ�� */
    
    SFE_ETH_NULL_ETHINFO,                           /* 5  ��ȡEth��ϢΪ�� */
    SFE_ETH_NULL_POINTER_TYPEINFO,                  /* 6  �ӿ���������Ϊ�� */
    SFE_ETH_NULL_POINTER_FULLINFO,                  /* 7  ��̫ȫ����Ϣ����Ϊ�� */
    SFE_ETH_ISNOTEXIST,                             /* 8  ��̫�ӿ�δ���� */
    SFE_ETH_SWITCH_INVALID_SETARPMISSSWITCH,        /* 9 ����ARP MISS����,���뿪��ֵ�Ƿ� */
    SFE_ETH_PORTTYPE_NOTETH_SETARPMISSSWITCH,       /* 10 ����ARP MISS����,�ӿ����Ͳ�����̫���� */

    SFE_ETH_NULL_POINTER_INPUTPARA_UPDATE,          /* 11 �������Ϊ��ָ�� */
    SFE_ETH_NULL_POINTER_INPUTPARA_GETCFG,          /* 12 �������Ϊ��ָ�� */
    SFE_ETH_NULL_POINTER_INPUTPARA_GETETH,          /* 13 �������Ϊ��ָ�� */

    SFE_ETH_MALLOC_FAIL_ETHUNIT_UPDATE,             /* 14 ��Eth Pool�л�ȡEth��Ԫ��Ϣʧ�� */
    SFE_ETH_NULL_ETHINFO_UPDATE_OLD,                /* 15 ��ȡEth��ϢΪ�� */
    SFE_ETH_NULL_ETHINFO_UPDATE_NEW,                /* 16 ��ȡEth��ϢΪ�� */
    SFE_ETH_NULL_ETHINFO_GET,                       /* 17 ��ȡEth��ϢΪ�� */
    
}SFE_ETH_ERRCODE_E;


#ifdef  __cplusplus
}
#endif

#endif


