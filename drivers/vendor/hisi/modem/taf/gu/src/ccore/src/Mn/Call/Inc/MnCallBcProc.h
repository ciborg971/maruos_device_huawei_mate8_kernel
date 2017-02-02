

#ifndef _CCA_CAPABILITY_H_
#define _CCA_CAPABILITY_H_

#include "vos.h"
#include "MnCallApi.h"
#include "NasCcIe.h"
#include "product_config.h"
#include "NasOmInterface.h"
#include "NasOmTrans.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/* +FCLASS�������õ�TAģʽ���� */
enum MN_CALL_TA_MODE_ENUM
{
    MN_CALL_TA_MODE_DATA                = 0,                                    /* ����ģʽ */
    MN_CALL_TA_MODE_FAX_CLASS1          = 1                                     /* Fax Class1 ģʽ */
};
typedef VOS_UINT8 MN_CALL_TA_MODE_ENUM_UINT8;


/* +CSNS�������õĵ����뷽��ģʽ���� */
enum MN_CALL_SNS_MODE_ENUM
{
    MN_CALL_SNS_MODE_VOICE              = 0,
    MN_CALL_SNS_MODE_ALTER_VF_V_FIRST   = 1,
    MN_CALL_SNS_MODE_FAX                = 2,
    MN_CALL_SNS_MODE_DATA               = 4,
    MN_CALL_SNS_MODE_ALTER_VF_F_FIRST   = 5
};
typedef VOS_UINT8 MN_CALL_SNS_MODE_ENUM_UINT8;


/* +CBST�����ʲ������μ�27.007 */
enum MN_CALL_BST_SPEED_ENUM
{
    MN_CALL_BST_SPD_AUTOBAUD            = 0,
    MN_CALL_BST_SPD_300_V21             = 1,
    MN_CALL_BST_SPD_1K2_V22             = 2,
    MN_CALL_BST_SPD_2K4_V22BIS          = 4,
    MN_CALL_BST_SPD_2K4_V26TER          = 5,
    MN_CALL_BST_SPD_4K8_V32             = 6,
    MN_CALL_BST_SPD_9K6_V32             = 7,
    MN_CALL_BST_SPD_9K6_V34             = 12,
    MN_CALL_BST_SPD_14K4_V34            = 14,
    MN_CALL_BST_SPD_19K2_V34            = 15,
    MN_CALL_BST_SPD_28K8_V34            = 16,
    MN_CALL_BST_SPD_33K6_V34            = 17,
    MN_CALL_BST_SPD_1K2_V120            = 34,
    MN_CALL_BST_SPD_2K4_V120            = 36,
    MN_CALL_BST_SPD_4K8_V120            = 38,
    MN_CALL_BST_SPD_9K6_V120            = 39,
    MN_CALL_BST_SPD_14K4_V120           = 43,
    MN_CALL_BST_SPD_19K2_V120           = 47,
    MN_CALL_BST_SPD_28K8_V120           = 48,
    MN_CALL_BST_SPD_38K4_V120           = 49,
    MN_CALL_BST_SPD_48K_V120            = 50,
    MN_CALL_BST_SPD_56K_V120            = 51,
    MN_CALL_BST_SPD_300_V110            = 65,
    MN_CALL_BST_SPD_1K2_V110            = 66,
    MN_CALL_BST_SPD_2K4_V110            = 68,
    MN_CALL_BST_SPD_4K8_V110            = 70,
    MN_CALL_BST_SPD_9K6_V110            = 71,
    MN_CALL_BST_SPD_14K4_V110           = 75,
    MN_CALL_BST_SPD_19K2_V110           = 79,
    MN_CALL_BST_SPD_28K8_V110           = 80,
    MN_CALL_BST_SPD_38K4_V110           = 81,
    MN_CALL_BST_SPD_48K_V110            = 82,
    MN_CALL_BST_SPD_56K_FTM             = 83,
    MN_CALL_BST_SPD_64K_FTM             = 84,
    MN_CALL_BST_SPD_56K_BT              = 115,
    MN_CALL_BST_SPD_64K_BT              = 116,
    MN_CALL_BST_SPD_32K_PIAFS           = 120,
    MN_CALL_BST_SPD_64K_PIAFS           = 121,
    MN_CALL_BST_SPD_64K_MULTI           = 134
};
typedef VOS_UINT8 MN_CALL_BST_SPEED_ENUM_UINT8;



/* +CBST������Ҫ�ز������μ�27.007 */
enum MN_CALL_BST_CE_ENUM
{
    MN_CALL_BST_CE_T                    = 0,
    MN_CALL_BST_CE_NT                   = 1,
    MN_CALL_BST_CE_BOTH_T               = 2,
    MN_CALL_BST_CE_BOTH_NT              = 3
};
typedef VOS_UINT8 MN_CALL_BST_CE_ENUM_UINT8;

/* 24.008 10.5.4.22 �еĶ��� */
enum MN_CALL_REP_IND_ENUM
{
    MN_CALL_REP_IND_NULL              = 0x00,                                   /* regard as invalid value */
    MN_CALL_REP_IND_ALTER             = 0x01,                                   /* mode 1 alternate mode 2 */
    MN_CALL_REP_IND_FALLBACK          = 0x02,                                   /* mode 1 preferred, mode 2 selected */
    MN_CALL_REP_IND_ALTER_1_PRFER     = 0x04
};
typedef VOS_UINT8  MN_CALL_REP_IND_ENUM_U8;

/*******************************************************************************
 �ṹ��    :MN_CALL_SUPPORT_CODEC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ǰ֧�ֵ�codec����,bitλ��1��ʾ��codec��Ч
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          CodecType_GSMFR         :1;
    VOS_UINT16                          CodecType_GSMHR         :1;
    VOS_UINT16                          CodecType_GSMEFR        :1;
    VOS_UINT16                          CodecType_GSMFRAMR      :1;
    VOS_UINT16                          CodecType_GSMHRAMR      :1;
    VOS_UINT16                          CodecType_UMTSAMR       :1;
    VOS_UINT16                          CodecType_UMTSAMR2      :1;
    VOS_UINT16                          CodecType_TDMAEFR       :1;
    VOS_UINT16                          CodecType_PDCEFR        :1;
    VOS_UINT16                          CodecType_GSMFRAMRWB    :1;
    VOS_UINT16                          CodecType_UMTSAMRWB     :1;
    VOS_UINT16                          CodecType_OHR_AMR       :1;
    VOS_UINT16                          CodecType_OFR_AMR_WB    :1;
    VOS_UINT16                          CodecType_OHR_AMR_WB    :1;
    VOS_UINT16                          BandSpare               :2;
}MN_CALL_SUPPORT_CODEC_STRU;

/*******************************************************************************
 �ṹ��    :MN_CALL_SUPPORT_CODEC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ǰ֧�ֵ�codec����,bitλ��1��ʾ��codec��Ч
*******************************************************************************/
typedef union
{
    MN_CALL_SUPPORT_CODEC_STRU          stSupportCodec;
    VOS_UINT16                          usSupportCodec;
}MN_CALL_SUPPORT_CODEC_UNION;




/*****************************************************************************
 �� �� ��  : MN_CALL_CapaProcInit
 ��������  : ��ʼ��Capability Procģ�顣��Ҫ�ǳ�ʼ����������汾�б��
             BC�ֶ���Ϣ�б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ���Ľ����VOS_OK��ʾ��ʼ���ɹ���VOS_ERROR��ʾ��ʼ��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��1��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_CapaProcInit(VOS_VOID);


/******************************************************************************
������  ��MN_CALL_BuildBcOfSetup
��������������SETUP��Ϣ�е�BC����
���������enCallType - ���κ��еĺ������͡��������ģʽ��Ϊsingle����ò���Ϊ
                       ��һ��ҵ������͡�
           enCallMode - ���κ��еĺ���ģʽ
           enTaMode   - ���κ��е�TAģʽ��ֻ�����ݺ�����Ч��
           pstBsType  - ���κ��еĳ���ҵ�����ͣ�ֻ�����ݺ�����Ч��
���������pstBc1 - ��һ��ҵ��ĳ���������
           pstBc2 - �ڶ���ҵ��ĳ���������������ģʽ��Ϊsingleʱ��������ò�����
����ֵ  �������BC�����ĸ��������ܵ�ֵΪ0��1��2��0��ʾ����ʧ�ܡ�
*******************************************************************************/
VOS_UINT32  MN_CALL_BuildBcOfSetup(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstBsType,
    NAS_CC_IE_BC_STRU                   *pstBc1,
    NAS_CC_IE_BC_STRU                   *pstBc2
);


/******************************************************************************
������  ��MN_CALL_BcCompChk
������������BC�������м����Լ�顣
���������pstBc - Ҫ����BC����
�����������
����ֵ  ��VOS_OK - �����Լ��ͨ��
           VOS_ERROR - �����Լ��ʧ��
*******************************************************************************/
VOS_UINT32  MN_CALL_BcCompChk(
    const NAS_CC_IE_BC_STRU             *pstBc
);


/******************************************************************************
������  ��MN_CALL_NegotBcForCallConf
����������Э��SETUP��Ϣ�е�BC�������õ�CALL CONFIRM��Ϣ��Ҫ��BC������
���������pstBsType - ��ǰ���õĳ���ҵ�����ͣ���SETUP��Ϣ�ĺ�������ΪVOICEʱ�ò����������ԡ�
           pstBc     - SETUP��Ϣ�е�BC����
���������pstBc     - Э�̺��BC����
����ֵ  ��VOS_TRUE ��ʾCALL CONF��Ϣ����ҪЯ����BC������
           VOS_FALSE ��ʾCALL CONF��Ϣ�в���ҪЯ����BC������
*******************************************************************************/
VOS_UINT32  MN_CALL_NegotBcForCallConf(
    NAS_CC_IE_BC_STRU                   *pstBc,
    NAS_CC_IE_BC_STRU                   *pstBcOfConf
);


/******************************************************************************
������  ��MN_CALL_BuildBcForSns
�������������쵥���뷽����BC����
���������enSnsMode - ��ǰ���õĵ����뷽��ģʽ
           pstBsType - ���κ��еĳ���ҵ�����ͣ��������뷽��ģʽΪVOICEʱ���Ըò�����
���������pstBc1 - ��һ��ҵ���BC����
           pstBc2 - �ڶ���ҵ���BC����
����ֵ  �������BC�����ĸ��������ܵ�ֵΪ0��1��2��0��ʾ����ʧ�ܡ�
*******************************************************************************/
VOS_UINT32  MN_CALL_BuildBcForSns(
    MN_CALL_SNS_MODE_ENUM_UINT8         enSnsMode,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfg,
    NAS_CC_IE_BC_STRU                   *pstBc1,
    NAS_CC_IE_BC_STRU                   *pstBc2,
    VOS_UINT8                           *pucBcRepInd
);



VOS_UINT32 MN_CALL_ConfigGsmCapaProc(
    NAS_OM_GSM_CODEC_CONFIG_ENUM_U8     enCapaConfig
);

NAS_OM_GSM_CODEC_CONFIG_ENUM_U8  MN_CALL_ConvertSpeechVers(VOS_VOID );

NAS_OM_CURR_CODEC_TYPE_ENUM_U8  MN_CALL_ConvertMnCodecToOmCodec(
    MN_CALL_CODEC_TYPE_ENUM_U8          enCodecType
);


VOS_VOID  MN_CALL_FillGsmSupCodecList(
    MN_CALL_SUPPORT_CODEC_UNION        *punCodecList
);



VOS_VOID  MN_CALL_FillUmtsSupCodecList(
    MN_CALL_SUPPORT_CODEC_UNION        *punCodecList
);




#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* _CCA_CAPABILITY_H_ */

