

#ifndef __PPP_CMP_PUBLIC_H__
#define __PPP_CMP_PUBLIC_H__

#define PPPCOMP_LZS1_MAXUSER  5
#define PPPCOMP_LZS0_MAXUSER  5

#if defined(__LINUX_VM__) || defined(__WIN32_PLATFORM__)
#define CMP_MAX_USER_NUM 10                   /* �ͻ�����Ϣ������һ�� */
#define PPPCOMP_MPPC_MAXUSER 10               /* MPPC֧�ֵ��û��� */
#define PPPCOMP_TCPIPCOMP_MAXUSER 10          /* VJ֧�ֵ��û��� */
#define PPPCOMP_LZS_MAXUSER  10
#else
#define CMP_MAX_USER_NUM  (HSGW_PRODUCT_TOTAL_PDN_NUMBER)                   /* ֧�ֵ�����û��� */
#define PPPCOMP_MPPC_MAXUSER (HSGW_PRODUCT_MPPC_PDP_NUMBER * 16 / 10)        /* MPPC֧�ֵ��û��� */
#define PPPCOMP_TCPIPCOMP_MAXUSER (HSGW_PRODUCT_VJ_USER_NUMBER * 16 / 10)    /* VJ֧�ֵ��û��� */
#define PPPCOMP_LZS_MAXUSER  (PPPCOMP_LZS1_MAXUSER + PPPCOMP_LZS0_MAXUSER)
#endif

#ifndef __LINUX_PLATFORM__
#define CMP_MAX_USER_INDEX_NUM (2*CMP_MAX_USER_NUM)
#else
#define CMP_MAX_USER_INDEX_NUM CMP_MAX_USER_NUM
#endif

#endif /* __PPP_CMP_PUBLIC_H__ */
