/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_ppi.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD SHELL
*  Date Created: 2006-12-11
*        Author: Wangchengyang
*   Description: NP���Կ�ά���Ժ�������ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-11      Wangchengyang       Create
*
*******************************************************************************/
#ifndef _BFD_PPI_H_
#define _BFD_PPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* PPI�����ķ���ֵ */
enum tagBFDPPIRetValue
{
    BFD_PPI_OK,
    BFD_PPI_ERR
};

/* �궨�� */
#define PPI_BFD                                    0        /* BFD PPI */

extern BFD_PPI_COUNT_S g_stBfdPpiCount;

typedef struct tagBFD_PPI_COM_S
{
    ULONG ulIpver;
    CHAR szCtlPkt[BFD_LEN_AUTH_NONE]; /* �Ự��BFD���Ʊ���,������,ֵΪ�û�����ֵ */

    ULONG ulDetectMode;             /* ����ʵ�ʵļ��ģʽ */
    ULONG ulTxInterval;             /* ����ʵ�ʵķ���ʱ����,ms */
    ULONG ulDetectInterval;         /* ����ʵ�ʵļ����,ms */
    ULONG ulDetectMult;             /* ����ʵ�ʵļ�ⱶ�� */
    ULONG ulMyDiscriminator;        /* ���˱�ʶ�� */
    ULONG ulYourDiscriminator;      /* �Զ˱�ʶ�� */

    ULONG ulDstIPAddress[4];        /* �Զ˵�ַ,Big Endian */
    ULONG ulSrcIPAddress[4];        /* ���˵�ַ,Big Endian */
    ULONG ulTTL;                    /* TTL */
    ULONG ulDstUdpPort;             /* UDPĿ�Ķ˿ں�,����Ϊ3784,����Ϊ4784 */
    ULONG ulSrcUdpPort;             /* UDPԴ�˿ں�,ֵΪ49151+X(X>0) */
    ULONG ulTos;                    /* TOSֵ */
    ULONG ulIfIndex;                /* �Ự�ĳ��ӿ�����(����ʱΪ0) */
    ULONG ulVrfIndex;               /* �Ự���ڵ�VRF */
    ULONG ulIfType;                 /* ���ӿ�����, ȡֵ��enumIFTYPE */
    ULONG ulIfNum;                  /* ���ӿڵ�ͨ���� */
    USHORT usReserved;              /* �������� */
    USHORT usCksum;                 /* ����PPI�ṹ���У��� */
    ULONG ulSessionId;              /* �ỰID */
    ULONG ulDiagnostic;             /* �·���ǰ�Ự����� */
}BFD_PPI_COM_S;

/* �������� */

VOID BFD_PPI_LogMsg(ULONG ulRet, ULONG ulSesssionID, ULONG ulOprType, VOID *pData, ULONG ulVrfIndex,ULONG ulIpVer);
VOID BFD_PPI_Dump(ULONG ulSessionID, BFD_PPI_COM_S *pstPPIInfo);
ULONG BFD_GetComPpi(BFD_PPI_COM_S* pstPpiCom, BFD_PPI_S* pstBfdPpi, BFD6_PPI_S* pstBfd6Ppi);
ULONG BFD_GetPpiFromCom(BFD_PPI_COM_S* pstPpiCom, ULONG *pulIpVer,
                                    BFD_PPI_S* pstBfdPpi, BFD6_PPI_S* pstBfd6Ppi);
#ifdef __cplusplus
}
#endif

#endif /* end of _BFD_PPI_H_ */

