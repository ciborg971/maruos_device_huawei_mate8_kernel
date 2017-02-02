/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pppc_uim.h
  �� �� ��   : ����
  ��    ��   : w00316385
  ��������   : 2015��08��08��
  ����޸�   :
  ��������   : pppc_uim.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __PPPC_UIM_H__
#define __PPPC_UIM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
****************************************************************************/
#include "ppp_inc.h"
#include "UsimPsInterface.h"
#include "CUeSpec.h"


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define PPPC_HRPD_MEID_LEN                                    (7)               /* MEID�ֽڳ� */
#define PPPC_HRPD_MEID_BIT_LEN                                (56)              /* MEID�̶�Ϊ56��BIT�� */

/* �����ļ��Ĵ�С */
#define PPPC_INIT_USIM_ELEMENT_CST_FILE_SIZE                  (7)
#define PPPC_INIT_USIM_ELEMENT_HRPDUPP_FILE_SIZE              (256)


#define PPPC_MAX_USIM_FILE_NUM                                (5)               /* UIM �е��ļ���� */

/* �ļ�Mask */
#define PPPC_INIT_USIM_ELEMENT_RUIMID_MASK                    (0x01)            /* 6F31 */
#define PPPC_INIT_USIM_ELEMENT_CST_MASK                       (0x02)            /* 6F32 */
#define PPPC_INIT_USIM_ELEMENT_ESNMEIDME_MASK                 (0x04)            /* 6F38 */
#define PPPC_INIT_USIM_ELEMENT_USGIND_MASK                    (0x08)            /* 6F42 */
#define PPPC_INIT_USIM_ELEMENT_HRPDUPP_MASK                   (0x10)            /* 6F57 */

/* ���� AUTH ������ʹ�õ� ProcessCtrl ֵ */
#define PPPC_HRPD_AUTH_PROCESSCTRL_DEFAULT_PROC               (0x00)
#define PPPC_HRPD_AUTH_PROCESSCTRL_SAVE_REGS_ON               (0x10)


/***************************SHA-1�㷨��ض��� BEGIN**********************************************/

#define VOS_TRAN(var, num) (((var) << (num)) | ((var) >> (32 - (num))))

/* ����ʵ���Ͻ�����ulong�任���ֽ���
   ����   | a | b | c | d |
   ת��Ϊ | d | c | b | a |
*/

/* С���� */
#define VOS_NUM1 (0xFF00FF00)
#define VOS_NUM2 (0x00FF00FF)
#define VOS_VAR0(index) (pStr->ulNum[index] = (VOS_TRAN(pStr->ulNum[index],24)&VOS_NUM1) \
    |(VOS_TRAN(pStr->ulNum[index],8)&VOS_NUM2))

#define VOS_VAR(index) (pStr->ulNum[index&15] = VOS_TRAN(pStr->ulNum[(index+13)&15]^pStr->ulNum[(index+8)&15] \
    ^pStr->ulNum[(index+2)&15]^pStr->ulNum[index&15],1))

#define VOS_NUM3 (0x5A827999)
#define VOS_NUM4 (0x6ED9EBA1)
#define VOS_NUM5 (0x8F1BBCDC)
#define VOS_NUM6 (0xCA62C1D6)

#define OPERA0(a,b,c,d,e,f) e+=((b&(c^d))^d)+VOS_VAR0(f)+VOS_NUM3+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA1(a,b,c,d,e,f) e+=((b&(c^d))^d)+VOS_VAR(f)+VOS_NUM3+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA2(a,b,c,d,e,f) e+=(b^c^d)+VOS_VAR(f)+VOS_NUM4+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA3(a,b,c,d,e,f) e+=(((b|c)&d)|(b&c))+VOS_VAR(f)+VOS_NUM5+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA4(a,b,c,d,e,f) e+=(b^c^d)+VOS_VAR(f)+VOS_NUM6+VOS_TRAN(a,5);b=VOS_TRAN(b,30);


/*******************************SHA-1�㷨��ض��� END******************************************/


/*******************************************************************************
                             ��ȡFixedData����ַ
*******************************************************************************/
#define PPPC_HRPD_GetFixedDataAddr()              (pg_stPppcFixedData)

#define PPPC_HRPD_GetUimStatus()                  ((PPPC_HRPD_GetFixedDataAddr())->enUimStatus)         /* ��ȡUIM���ڱ�� */
#define PPPC_HRPD_SetUimStatus(enStatus)          (((PPPC_HRPD_GetFixedDataAddr())->enUimStatus) = (enStatus))    /* ����UIM���ڱ�� */
#define PPPC_HRPD_GetUimDataAddr()                (&((PPPC_HRPD_GetFixedDataAddr())->stUimData))       /* ��ȡUIM���ݵ�ַ */

/* ��ȡNVIM���ݵ�ַ */
#define PPPC_HRPD_GetNvimDataAddr()               (&((PPPC_HRPD_GetFixedDataAddr())->stNvimData))

/* Terminal info */
#define PPPC_HRPD_GetTerminalInfoAddr()           (&((PPPC_HRPD_GetNvimDataAddr())->stTerminalInfo))

/* USIM����ȡ��ʾ */
#define PPPC_HRPD_GetUsimFileMask()               ((PPPC_HRPD_GetFixedDataAddr())->ulUimFileMask)                         /* ��ȡ �Ѷ�USIM���ļ��� */
#define PPPC_HRPD_SetUsimFileMask(ulFileMask)     ((PPPC_HRPD_GetUsimFileMask()) = (ulFileMask))
#define PPPC_HRPD_RmvUsimFileMask(ulFileMask)     ((PPPC_HRPD_GetFixedDataAddr())->ulUimFileMask &= (~(ulFileMask)) )     /* ɾ����ȡUSIM���ļ���־λ */
#define PPPC_HRPD_AddUsimFileMask(ulFileMask)     ((PPPC_HRPD_GetFixedDataAddr())->ulUimFileMask |= (ulFileMask))         /* ��Ӷ�ȡUSIM���ļ���־λ */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*******************************************************************************
* Name        : PPPC_HRPD_MEID_STRU
*
* Description : MEIDһ��56��bit
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMeidLow;                              /* Low 32 bit of MEID */
    VOS_UINT32                          ulMeidHigh;                             /* High 24 bit of MEID */
}PPPC_HRPD_MEID_STRU;

/*******************************************************************************
 * Name        : PPPC_HRPD_UIM_STATUS_ENUM
 *
 * Description : UIM��״̬
 *******************************************************************************/
enum PPPC_HRPD_UIM_STATUS_ENUM
{
    PPPC_HRPD_UIM_STATUS_ABSENT         = 0,
    PPPC_HRPD_CARD_STATUS_UIM_PRESENT   = 1,
    PPPC_HRPD_CARD_STATUS_CSIM_PRESENT  = 2,
    PPPC_HRPD_UIM_STATUS_BUTT
};
typedef VOS_UINT8 PPPC_HRPD_UIM_STATUS_ENUM_UINT8;

/*******************************************************************************
 * Name        : PPPC_HRPD_ESN_MEID_TYPE_ENUM
 *
 * Description : ESN or MEID ����
 *******************************************************************************/
enum PPPC_HRPD_ESN_MEID_TYPE_ENUM
{
    PPPC_HRPD_ESN_MEID_TYPE_ESN      = 0,
    PPPC_HRPD_ESN_MEID_TYPE_MEID        ,

    PPPC_HRPD_ESN_MEID_TYPE_BUTT
};
typedef VOS_UINT8 PPPC_HRPD_ESN_MEID_TYPE_ENUM_UINT8;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*******************************************************************************
* Name        : PPPC_USIMM_AUTH_DATA_STRU
*
* Description : ��Ȩ����
*******************************************************************************/
typedef struct
{
    USIMM_AUTH_TYPE_ENUM_UINT32         enAuthType;
    USIMM_AUTH_DATA_UNION               unAuthPara;
}PPPC_USIMM_AUTH_DATA_STRU;

/*******************************************************************************
* Name        : PPPC_USIM_READ_REQ_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3] ;                        /* ���ֽڶ��룬����        */
    VOS_UINT8                           ucFileNum;                              /* ��Ҫ��ȡ��File��Ŀ      */
    VOS_UINT16                          ausEfId[PPPC_MAX_USIM_FILE_NUM];        /* ��Ҫ��ȡ���ļ����      */
}PPPC_USIM_READ_REQ_STRU;

/*******************************************************************************
* Name        : PPPC_GET_FILE_INFO_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* Ӧ������ */
    VOS_UINT16                  usEfId;         /* �ļ�ID */
    VOS_UINT8                   ucRecordNum;    /* �ļ���¼�ţ��������ļ���0 */
    VOS_UINT8                   ucRsv;          /* ���� */
}PPPC_GET_FILE_INFO_STRU;


/*******************************SHA-1�㷨��ض��� BEGIN******************************************/

/*******************************************************************************
* Name        : PPPC_HRPD_SHA1_STRU
*
* Description : ����Э���㷨������hauwei��̹淶ʵ��
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          aulState[5];
    VOS_UINT32                          aulCount[2];
    VOS_UINT8                           aucBuffer[64];
} PPPC_HRPD_SHA1_STRU;

typedef union
{
    VOS_UINT32 ulNum[16];
} VOS_CHAR64_TO_LONG16;


/*******************************SHA-1�㷨��ض��� END******************************************/

/*******************************************************************************
* Name        : PPPC_HRPD_CST_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCstLen;
    VOS_UINT8                           aucCst[PPPC_INIT_USIM_ELEMENT_CST_FILE_SIZE];
} PPPC_HRPD_CST_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_ESN_MEID_STRU
*
* Description : ������ESN��MEID����ͬʱ����
*******************************************************************************/
typedef struct
{
    PPPC_HRPD_ESN_MEID_TYPE_ENUM_UINT8  enEsnMeidType;                          /* ESN or MEID */
    VOS_UINT8                           aucReserve[3];

    union
    {
        VOS_UINT32                      ulEsn;                                  /* �ӿ������������ESN */
        PPPC_HRPD_MEID_STRU             stMeid;                                 /* �ӿ������������MEID 56��bit */
    }u;
} PPPC_HRPD_ESN_MEID_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_RUIMID_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumbytes;                             /* ��Ч��Bytes���� */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulRUIMIDLow;                            /* Low 32 bit of RUIMID */
    VOS_UINT32                          ulRUIMIDHigh;                           /* High 24 bit of RUIMID */
} PPPC_HRPD_RUIMID_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_USGIND_STRU
*
* Description :
*               Bit 0:
*                  FALSE: ESN_ME is used for CAVE Authentication and MS Identification
*                  TRUE: IDUIMID is used for CAVE Authentication and MS Identification
*
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsgInd;

    VOS_UINT8                           aucReserve[3];
}PPPC_HRPD_USGIND_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_UPP_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHrpdUppLen;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucHrpdUpp[PPPC_INIT_USIM_ELEMENT_HRPDUPP_FILE_SIZE];
} PPPC_HRPD_UPP_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_UIM_INFO_STRU
*
* Description : ��UIM���ж�������Ϣ
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiLen;                              /* IMSI ռ�õĳ��� */
    VOS_UINT8                           aucImsi[PS_CUE_IMSI_MAX_SIZE];          /* MS��IMSI��ʶ */
    PPPC_HRPD_CST_STRU                  stEfCst;                                /* CDMAҵ��� */
    PPPC_HRPD_ESN_MEID_STRU             stEsnMeid;                              /* ESN or MEID */
    PPPC_HRPD_RUIMID_STRU               stRuimid;                               /* RUIMID */
    PPPC_HRPD_USGIND_STRU               stUsgind;                               /* USGIND */
    PPPC_HRPD_UPP_STRU                  stHrpdUpp;                              /* HRPD UPP */
    VOS_UINT8                           aucReserve[4];
} PPPC_HRPD_UIM_INFO_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_NVIM_TERMINAL_INFO_STRU
*
* Description : �ֻ������Ϣ
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEsn;                                  /* ESN */
    PPPC_HRPD_MEID_STRU                 stMeid;                                 /* MEID */

    VOS_UINT8                           ucMobMfgCode;                           /* Manufacturer code */
    VOS_UINT8                           ucMobModel;                             /* Model number */
    VOS_UINT16                          usMobFirmRev;                           /* Firmware revision number */
} PPPC_HRPD_NVIM_TERMINAL_INFO_STRU;


/*******************************************************************************
* Name        : PPPC_HRPD_UIM_INFO_STRU
*
* Description : ��UIM���ж�������Ϣ
*******************************************************************************/
typedef struct
{
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU   stTerminalInfo;                         /* �ֻ������Ϣ */
} PPPC_HRPD_NVIM_INFO_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_FIXED_DATA_STRU
*
* Description : ��һ�ο����󣬱��ֲ�������ݣ�
*               ÿ��Deactiveʱ�����Ըò������ݽ��г�ʼ���������ڹػ�ʱ���ͷ�
*******************************************************************************/
typedef struct
{
    PPPC_HRPD_UIM_INFO_STRU             stUimData;                              /* �� USIM �ж����Ĳ��� */
    PPPC_HRPD_NVIM_INFO_STRU            stNvimData;                             /* �� NVIM �ж����Ĳ��� */
    VOS_UINT32                          ulUimFileMask;                          /* ����������ı��λ */
    PS_BOOL_ENUM_UINT8                  enUimStatus;                            /* UIM���ڱ��,PS_TRUE:����,PS_FALSE:������ */
    VOS_UINT8                           aucReserve[3];
}PPPC_HRPD_FIXED_DATA_STRU;



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID PPPC_UsimmReadFileCnfProc(USIMM_READFILE_CNF_STRU *pstMsg);
VOS_UINT32  PPPC_InitFixedData(VOS_VOID);
PS_BOOL_ENUM_UINT8 PPPC_MD5Active(VOS_VOID);
VOS_UINT32 PPPC_UIM_RunCaveAuthReq(VOS_UINT32 ulRandu);
VOS_UINT32 PPPC_PihUsimStatusIndProc(USIMM_CARDSTATUS_IND_STRU  *pstUsimMsg);




#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of pppc_uim.h */

