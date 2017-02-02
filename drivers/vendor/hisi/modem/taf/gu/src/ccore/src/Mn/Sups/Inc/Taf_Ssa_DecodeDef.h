/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SSA_DecodeDef.h
  Author      : ---
  Version     : V200R001
  Date        : 2005-08-16
  Description : ��ͷ�ļ�������SSAģ����뺯���Ľӿ�
  History     :
  1. Date:2005-04-19
     Author: ---
     Modification:Create
  2.��    ��   : 2006��08��09��
    ��    ��   : ����Ƽj60010247
    �޸�����   : ���ⵥA32D03479����PC����ʵ��ʱ��#pragma pack(0)��#pragma pack()�ӱ��뿪��
  3.Date:2007-04-29
    Author: Li Jilin 60827
    Modification: ���ⵥ��:A32D10708

************************************************************************/

#ifndef _SSA_DECODEDEF_H_
#define _SSA_DECODEDEF_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "TafAppSsa.h"
#include "vos.h"
#include "Ssa_Define.h"

#pragma pack(4)

/*�Բ��������Ͳ����Ľ���ĺ궨��*/
/******************************************************************************************/
/**�������ccbs-Index,�μ�24.080��Annex A��ASN.1������*/
#define SSA_DecodeCcbsIndex(value, content, tagmode)                SSA_DecodeInt(value, 5, content, tagmode)
/*�������noReplyConditionTime,�μ�24.080��Annex A��ASN.1������*/

#define SSA_DecodeNoReplyConditionTime(value, content, tagmode)     SSA_DecodeInt(value, 255, content, tagmode)

/*�������defaultPriority,�μ�24.080��Annex A��ASN.1������*/
#define SSA_DecodeDefaultPriority(value, content, tagmode)          SSA_DecodeInt(value, 16, content, tagmode)
/*�������nbrUser,�μ�24.080��Annex A��ASN.1������*/
#define SSA_DecodeNbrUser(value, content, tagmode)                  SSA_DecodeInt(value, 7, content, tagmode)
/*�������nbrSn�μ�24.080��Annex A��ASN.1������*/
#define SSA_DecodeNbrSN(value, content, tagmode)                    SSA_DecodeInt(value, 7, content, tagmode)
/*�������nbrSn�μ�24.080��Annex A��ASN.1������*/
#define SSA_DecodeNbrSB(value, content, tagmode)                    SSA_DecodeInt(value, 7, content, tagmode)
/*�������maximumEntitledPriority,ASN.1�������μ�24.080��Annex A*/
#define SSA_DecodeMaxEntitledPriority(value, content, tagmode)      SSA_DecodeInt(value, 15, content, tagmode)
/*******************************************************************************************/

/*�Բ�����ö�����Ͳ����Ľ���ĺ궨��*/
/********************************************************************************************/
/* �������GuidanceInfo,�μ�24.080��Annex A��ASN.1������**/
#define SSA_DecodeGuidanceInfo(pucDest, pucSrc, TagMode)  SSA_DecodeEnum(pucDest, pucSrc, TagMode)
/*�������cliRestrictionOption,�μ�24.080��Annex A��ASN.1������*/
#define SSA_DecodeCliRestrictionOption(pucDest, pucSrc, TagMode)  SSA_DecodeEnum(pucDest, pucSrc, TagMode)
/********************************************************************************************/

/*�Բ������ַ������Ͳ����Ľ���ĺ궨��*/
/********************************************************************************************/
/*��IA5String���͵��ִ��������ͨ���ַ���*/
#define SSA_DecodeIA5String(pucDest, pucDestLen, pucSrc, ucTagMode)  SSA_DecodeString(pucDest, pucDestLen, pucSrc, ucTagMode);
/*��Numeric String���͵��ִ��������ͨ���ַ���*/
#define SSA_DecodeNumericString(pucDest, pucDestLen, pucSrc, ucTagMode)  SSA_DecodeString(pucDest, pucDestLen, pucSrc, ucTagMode);
/********************************************************************************************/

extern VOS_VOID  SSA_Get7bits( VOS_UINT8 *pucChar,
                               VOS_UINT8 const *pucEncodedMsg,
                               VOS_UINT32 ulBitAddress );
/**����ԭ������**/
VOS_UINT32  SSA_DecodeComponent(TAF_SS_CALL_INDEPENDENT_EVENT_STRU              *pEvent,
                                VOS_UINT8                                       *pucSrc);
VOS_UINT32  SSA_DecodeInvoke(TAF_SS_CALL_INDEPENDENT_EVENT_STRU                 *pEvent,
                             VOS_UINT8                                         **pucSrc);
VOS_UINT32  SSA_DecodeRtrnRslt(TAF_SS_CALL_INDEPENDENT_EVENT_STRU               *pEvent,
                               VOS_UINT8                                       **pucSrc);
VOS_UINT32  SSA_DecodeRtrnErr(TAF_SS_CALL_INDEPENDENT_EVENT_STRU                *pEvent,
                              VOS_UINT8                                        **pucSrc);
VOS_UINT32  SSA_DecodeReject(TAF_SS_CALL_INDEPENDENT_EVENT_STRU                 *pEvent,
                             VOS_UINT8                                         **pucSrc);
VOS_UINT32  SSA_DecodeRegisterSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU          *para,
                                    VOS_UINT8                                  **pucSrc);
VOS_UINT32  SSA_DecodeEraseSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU             *para,
                                 VOS_UINT8                                     **pucSrc);
VOS_UINT32  SSA_DecodeActivateSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU          *para,
                                    VOS_UINT8                                  **pucSrc);
VOS_UINT32  SSA_DecodeDeactivateSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU        *para,
                                      VOS_UINT8                                **pucSrc);
VOS_UINT32  SSA_DecodeInterrogateSsCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU       *para,
                                       VOS_UINT8                               **pucSrc);
VOS_UINT32  SSA_DecodeRegPwdCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU              *para,
                                VOS_UINT8                                      **pucSrc);
VOS_UINT32  SSA_DecodeGetPwdInd(TAF_SS_CALL_INDEPENDENT_EVENT_STRU              *para,
                                VOS_UINT8                                       **pucSrc);
VOS_UINT32  SSA_DecodeProcessUnstructuredSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para,
                                               VOS_UINT8                         **pucSrc);
VOS_UINT32  SSA_DecodeUntructuredSSInd(TAF_SS_CALL_INDEPENDENT_EVENT_STRU       *para,
                                       VOS_UINT8                               **pucSrc);
VOS_UINT32  SSA_DecodeUntructuredSSNotifyInd(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para,
                                             VOS_UINT8                         **pucSrc);
VOS_UINT32  SSA_DecodeEraseCCEntryCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU        *para,
                                      VOS_UINT8                                **pucSrc);
VOS_UINT32  SSA_DecodeProcessUSSDataCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU      *para,
                                        VOS_UINT8                              **pucSrc);
VOS_UINT32  SSA_DecodeSsCode(TAF_SS_CODE                        *pSscode,
                             VOS_UINT8                         **pucSrc,
                             TAG_MODE                            ucTagmode);
VOS_UINT32  SSA_DecodeBasicServiceCode(TAF_BASIC_SERVICE_CODE   *pBsCode,
                                       VOS_UINT8               **pucSrc,
                                       TAG_MODE                  ucTagmode);
VOS_UINT32  SSA_DecodeSsStatus(TAF_SS_STATUS                    *pSsStatus,
                               VOS_UINT8                       **pucSrc,
                               TAG_MODE                          ucTagmode);
VOS_UINT32  SSA_DecodeMsisdn(VOS_UINT8                          *pucMsisdn,
                             VOS_UINT8                         **pucSrc,
                             TAG_MODE                            ucTagmode);
VOS_UINT32  SSA_DecodeAlertingPattern(VOS_UINT8         *pucAlertingPattern,
                                      VOS_UINT8                **pucSrc,
                                      TAG_MODE                   ucTagmode);
VOS_UINT32  SSA_DecodeBasicService(TAF_SS_BASIC_SERVICE_STRU    *pDest,
                                   VOS_UINT8                   **pucSrc,
                                   TAG_MODE                      ucTagMode);
VOS_UINT32  SSA_DecodeForwardedToNumber(TAF_SS_NUMTYPE          *pucNumType,
                                        VOS_UINT8               *pucFwdToNum,
                                        VOS_UINT8              **pucSrc,
                                        TAG_MODE                 ucTagMode);
VOS_UINT32  SSA_DecodeForwardedToSubaddress(TAF_SS_SUBADDRTYPE  *pucSubAddrType,
                                            VOS_UINT8           *pucSubAddr,
                                            VOS_UINT8          **pucSrc,
                                            TAG_MODE             ucTagMode);
VOS_UINT32  SSA_DecodeForwardingInfo(TAF_SS_FORWARDINGINFO_STRU         *pDest,
                                     VOS_UINT8                         **pucSrc,
                                     TAG_MODE                            ucTagMode);
VOS_UINT32  SSA_DecodeForwardingFeatureList(TAF_SS_FWDFEATURELIST_STRU  *pDest,
                                            VOS_UINT8                  **pucSrc,
                                            TAG_MODE                     ucTagMode);
VOS_UINT32  SSA_DecodeForwardingFeature(TAF_SS_FWDFEATURE_STRU          *pDest,
                                        VOS_UINT8                      **pucSrc,
                                        TAG_MODE                         ucTagMode);
VOS_UINT32  SSA_DecodeForwardingOptions(VOS_UINT8                       *pucDest,
                                        VOS_UINT8                      **pucSrc,
                                        TAG_MODE                         ucTagMode);
VOS_UINT32  SSA_DecodeLongForwardedToNumber(TAF_SS_NUMTYPE              *pucLongFwdNumType,
                                            VOS_UINT8                   *pucLongFwdToNum,
                                            VOS_UINT8                  **pucSrc,
                                            TAG_MODE                     ucTagMode);
VOS_UINT32  SSA_DecodeCallBarringInfo(TAF_SS_CALLBRARINGINFO_STRU       *pDest,
                                      VOS_UINT8                        **pucSrc,
                                      TAG_MODE                           ucTagMode);
VOS_UINT32  SSA_DecodeCallBarringFeatureList(TAF_SS_CALLBARFEATURELIST_STRU *pDest,
                                             VOS_UINT8                     **pucSrc,
                                             TAG_MODE                        ucTagMode);
VOS_UINT32  SSA_DecodeCallBarringFeature(TAF_SS_CALLBARRINGFEATURE_STRU     *pDest,
                                         VOS_UINT8                         **pucSrc,
                                         TAG_MODE                            ucTagMode);
VOS_UINT32  SSA_DecodeSSData(TAF_SS_SSDATA_STRU                             *pDest,
                             VOS_UINT8                                     **pucSrc,
                             TAG_MODE                                        ucTagMode);
VOS_UINT32  SSA_DecodeBasicServiceGroupList(TAF_SS_BS_SERV_GROUPLIST_STRU   *pDest,
                                            VOS_UINT8                      **pucSrc,
                                            TAG_MODE                         ucTagMode);
VOS_UINT32  SSA_DecodeGenericServiceInfo(TAF_SS_GENERIC_SERV_INFO_STRU      *pDest,
                                         VOS_UINT8                         **pucSrc,
                                         TAG_MODE                            ucTagMode);
VOS_UINT32  SSA_DecodeCcbsFeatureList(TAF_SS_CCBS_FEATURELIST_STRU          *pDest,
                                      VOS_UINT8                            **pucSrc,
                                      TAG_MODE                               ucTagMode);
VOS_UINT32  SSA_DecodeCcbsFeature(TAF_SS_CCBS_FEATURE_STRU                  *pDest,
                                  VOS_UINT8                                **pucSrc,
                                  TAG_MODE                                   ucTagMode);
VOS_UINT32 SSA_DecodeBSubscriberNum(TAF_SS_NUMTYPE                          *pucNumType,
                                    VOS_UINT8                                   *pucBSubscriberNum,
                                    VOS_UINT8                              **pucSrc,
                                    TAG_MODE                                 ucTagMode);
VOS_UINT32 SSA_DecodeBSubscriberSubAddress(TAF_SS_SUBADDRTYPE               *pucSubAddrType,
                                           VOS_UINT8                        *pucBSubscriberSubAddr,
                                           VOS_UINT8                       **pucSrc,
                                           TAG_MODE                          ucTagMode);
VOS_UINT32  SSA_DecodeUssdDataCodingScheme(TAF_SS_DATA_CODING_SCHEME        *pDest,
                                           VOS_UINT8                       **pucSrc,
                                           TAG_MODE                          ucTagMode);
VOS_UINT32  SSA_DecodeUssdString(TAF_SS_USSD_STRING_STRU                    *pDest,
                                 VOS_UINT8                                 **pucSrc,
                                 TAG_MODE                                    ucTagMode);
VOS_VOID SSA_Decode7bit (TAF_SS_USSD_STRING_STRU   *para, VOS_UINT8  ucCodingScheme);
VOS_UINT32  SSA_DecodeUssdMessage (TAF_SS_USSD_STRING_STRU                  *para,
                                   VOS_UINT8                                 ucCodingScheme);
VOS_UINT32  SSA_DecodeInt(VOS_INT32                                           *piDest,
                          VOS_INT32                                            iMaxNum,
                          VOS_UINT8                                        **pucSrc,
                          TAG_MODE                                           usTagMode);
VOS_UINT32 SSA_DecodeEnum(VOS_UINT8                                         *pucDest,
                          VOS_UINT8                                        **pucSrc,
                          TAG_MODE                                           ucTagMode);
VOS_UINT32  SSA_DecodeString(VOS_UINT8                                      *pucDest,
                             VOS_UINT8                                      *pucDestLen,
                             VOS_UINT8                                     **pucSrc,
                             TAG_MODE                                        ucTagMode);
VOS_UINT32  SSA_Decode_Enum(VOS_UINT8                                       *pucDest,
                            VOS_UINT8                                      **pucSrc,
                            TAG_MODE                                         ucTagMode) ;
VOS_UINT32  SSA_DecodeLength(VOS_UINT8                                     **pucSrc,
                             VOS_UINT8                                      *pucLen);
VOS_UINT32  SSA_DecodeTag(VOS_UINT8                                        **pucSrc ,
                          SSA_TAG_STRU                                      *pTagStru);
VOS_VOID SSA_BcdNumToAsciiNum(VOS_UINT8                                     *pucAsciiNum,
                              VOS_UINT8                                     *pucBcdNum,
                              VOS_UINT8                                      ucBcdNumLen,
                              VOS_UINT8                                      ucNumType); /*A32D10708*/
VOS_UINT32 SSA_DecodeIndefLen(VOS_UINT8 *pucSrc,    VOS_UINT8 *pucLen);

VOS_UINT32 SSA_DecodeTL(VOS_UINT8 **ppucSrc, SSA_TAG_STRU *pstTagStru,VOS_UINT8 *pucLen);
VOS_UINT32 SSA_DecodeSSDataSsCode(TAF_SS_SSDATA_STRU *pDest, VOS_UINT8 **ppucSrc,
                                           VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeSSDataSsStatus(TAF_SS_SSDATA_STRU *pDest, VOS_UINT8 **ppucSrc,
                                           VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeSSDataSsSubScriptionOp(TAF_SS_SSDATA_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                        VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeSSDataBasicServiceGroupList(TAF_SS_SSDATA_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                              VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeSSDataDefaultPriority(TAF_SS_SSDATA_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                   VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeSSDataNbrUser(TAF_SS_SSDATA_STRU *pDest, VOS_UINT8 **ppucSrc,
                                           VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeFwdFeatureBasicService(TAF_SS_FWDFEATURE_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeFwdFeatureSsStatus(TAF_SS_FWDFEATURE_STRU *pDest, VOS_UINT8 **ppucSrc,
                                           VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeFwdFeatureForwardedToNumber(TAF_SS_FWDFEATURE_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                           VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeFwdFeatureForwardedToSubaddress(TAF_SS_FWDFEATURE_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                           VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeFwdFeatureForwardingOptions(TAF_SS_FWDFEATURE_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                         VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeFwdFeatureNoReplyConditionTime(TAF_SS_FWDFEATURE_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                         VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeFwdFeatureLongForwardedToNumber(TAF_SS_FWDFEATURE_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                                  VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeGenericCliRestrictionOption(TAF_SS_GENERIC_SERV_INFO_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                                  VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeGenericMaxEntitledPriority(TAF_SS_GENERIC_SERV_INFO_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                          VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeGenericDefaultPriority(TAF_SS_GENERIC_SERV_INFO_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                          VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeGenericCcbsFeatureList(TAF_SS_GENERIC_SERV_INFO_STRU *pDest, VOS_UINT8 **ppucSrc,
                                                          VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeGenericNbrSB(TAF_SS_GENERIC_SERV_INFO_STRU *pDest, VOS_UINT8 **ppucSrc,
                                               VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeGenericNbrUser(TAF_SS_GENERIC_SERV_INFO_STRU *pDest, VOS_UINT8 **ppucSrc,
                                               VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);
VOS_UINT32 SSA_DecodeGenericNbrSN(TAF_SS_GENERIC_SERV_INFO_STRU *pDest, VOS_UINT8 **ppucSrc,
                                               VOS_UINT8 *pucCurLocation,VOS_UINT8 *pucEndLocation);



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

#endif /* end of SSA_DecodeDef.h*/
