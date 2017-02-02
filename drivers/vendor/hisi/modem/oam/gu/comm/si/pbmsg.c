/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmApi.c
  Author       : zhuli
  Version      : V100R002
  Date         : 2008-5-15
  Description  : ��C�ļ�������---�����Ϣ����ģ��ʵ��
  Function List:
  History      :
 ************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#include "si_pb.h"
#include "UsimmApi.h"
#include "AtOamInterface.h"
#include "TafOamInterface.h"
#include "pamom.h"


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_PB_MSG_C
/*lint +e767*/


/*****************************************************************************
    ȫ�ֱ�������
*****************************************************************************/

SI_PB_REQ_UINT_STRU             gstPBReqUnit;

/*˫�˶���Ҫ��ȫ�ֱ�����A �����ͨ����Ϣ�� C ��ͬ��*/
SI_PB_CONTROL_STRU              gstPBCtrlInfo;
SI_PB_CTRL_INFO_ST              gstPBConfigInfo;

SI_PB_CONTENT_STRU              gastPBContent[SI_PB_MAX_NUMBER];
SI_EXT_CONTENT_STRU             gastEXTContent[SI_PB_MAX_NUMBER];
SI_ANR_CONTENT_STRU             gastANRContent[SI_PB_ANRMAX];
SI_EML_CONTENT_STRU             gstEMLContent;
SI_IAP_CONTENT_STRU             gstIAPContent;
SI_PB_INIT_STATE_STRU           gstPBInitState;
VOS_UINT8                       gucPBCStatus = VOS_TRUE;

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
SI_PB_SEARCH_CTRL_STRU          gstPBSearchCtrlInfo;
VOS_UINT32                      gulPBFileCnt;
VOS_UINT32                      gulPBRecordCnt;
VOS_UINT32                      gulPBInitFileNum;
VOS_UINT32                      gulPBInitExtFileNum;
VOS_UINT32                      gulExtRecord;
#endif

extern USIMM_CARD_SERVIC_ENUM_UINT32 g_enAcpuCardStatus;
VOS_UINT32 SI_PB_ErrorProc(VOS_VOID)
{
    USIMM_CARD_SERVIC_ENUM_UINT32       ulCardStatus = USIMM_CARD_SERVIC_BUTT;


#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulCardStatus = (VOS_UINT8)g_enAcpuCardStatus;
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    /*lint -e534*/
    USIMM_GetCardType(gstPBInitState.enCardType, &ulCardStatus);
    /*lint +e534*/
#endif

    if( PB_LOCKED == gstPBReqUnit.enPBLock )
    {
        PB_WARNING_LOG("SI_PB_ErrorProc: The PB is Locked");

        return TAF_ERR_UNSPECIFIED_ERROR;
    }
    else if((USIMM_CARD_SERVIC_UNAVAILABLE == ulCardStatus)
             || (USIMM_CARD_SERVIC_ABSENT == ulCardStatus))
    {
        PB_WARNING_LOG("SI_PB_ErrorProc: The Card Absent");

        return TAF_ERR_SIM_FAIL;
    }
    else if( USIMM_CARD_SERVIC_SIM_PUK == ulCardStatus )
    {
        PB_WARNING_LOG("SI_PB_ErrorProc: PUK NEED");

        return TAF_ERR_NEED_PUK1;
    }
    else if( USIMM_CARD_SERVIC_SIM_PIN == ulCardStatus )
    {
        PB_WARNING_LOG("SI_PB_ErrorProc: PIN NEED");

        return TAF_ERR_NEED_PIN1;
    }
    else
    {
        return TAF_ERR_NO_ERROR;
    }
}

#if ((OSA_CPU_ACPU == VOS_OSA_CPU)||(defined(DMT)))

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID SI_PB_ReadXeccProc(VOS_UINT16 usIndexNum,VOS_UINT16 usIndexStar,SI_PB_EVENT_INFO_STRU *pstCnfData)
{
    VOS_UINT32          ulResult;
    VOS_UINT32          ulValidFlag;
    VOS_UINT8           i;
    VOS_UINT8           *pucContent;

    pucContent = gastPBContent[PB_XECC_CONTENT].pContent + ((usIndexStar-1)*gastPBContent[PB_XECC_CONTENT].ucRecordLen);
    ulValidFlag = VOS_FALSE;

    for(i=0; i<usIndexNum; i++)
    {
        pstCnfData->PBEvent.PBReadCnf.PBRecord.Index = i+usIndexStar;

        ulResult = SI_PB_CheckEccValidity(pucContent);

        if(VOS_ERR == ulResult)
        {
            pstCnfData->PBEvent.PBReadCnf.PBRecord.ValidFlag = SI_PB_CONTENT_INVALID;
        }
        else
        {
            pstCnfData->PBEvent.PBReadCnf.PBRecord.ValidFlag = SI_PB_CONTENT_VALID;
            ulValidFlag = VOS_TRUE;

            SI_PB_BcdToAscii(3, pucContent, pstCnfData->PBEvent.PBReadCnf.PBRecord.Number,
                            &pstCnfData->PBEvent.PBReadCnf.PBRecord.NumberLength);/*Ecc����������ǰ��*/

            pstCnfData->PBEvent.PBReadCnf.PBRecord.NumberType = PB_NUMBER_TYPE_NORMAL;

            if(gastPBContent[PB_XECC_CONTENT].ucNameLen != 0)
            {
                SI_PB_DecodePBName(gastPBContent[PB_XECC_CONTENT].ucNameLen,&pucContent[3],
                                &pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTagType,
                                &pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

                SI_PB_MemSet(sizeof(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag),0xFF,pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag);

                /*lint -e534*/
                VOS_MemCpy(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag, &pucContent[3],
                        pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);
                /*lint +e534*/
            }
            else
            {
                pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength = 0;
            }
        }

        if(i == (usIndexNum-1))
        {
            pstCnfData->PBLastTag = VOS_TRUE;
            pstCnfData->PBError = ((VOS_TRUE == ulValidFlag)?TAF_ERR_NO_ERROR:TAF_ERR_PB_NOT_FOUND);
        }

        /*lint -e534*/
        SI_PBCallback(pstCnfData);
        /*lint +e534*/

        pucContent += gastPBContent[PB_XECC_CONTENT].ucRecordLen;/*����ָ�밴�ռ�¼����ƫ��*/
    }

    return;
}
#endif


VOS_VOID SI_PB_ReadEccProc(VOS_UINT16 usIndexNum,VOS_UINT16 usIndexStar,SI_PB_EVENT_INFO_STRU *pstCnfData)
{
    VOS_UINT32          ulResult;
    VOS_UINT32          ulValidFlag;
    VOS_UINT8           i;
    VOS_UINT8           *pucContent;

    pucContent = gastPBContent[PB_ECC_CONTENT].pContent + ((usIndexStar-1)*gastPBContent[PB_ECC_CONTENT].ucRecordLen);
    ulValidFlag = VOS_FALSE;

    for(i=0; i<usIndexNum; i++)
    {
        pstCnfData->PBEvent.PBReadCnf.PBRecord.Index = i+usIndexStar;

        ulResult = SI_PB_CheckEccValidity(pucContent);

        if(VOS_ERR == ulResult)
        {
            pstCnfData->PBEvent.PBReadCnf.PBRecord.ValidFlag = SI_PB_CONTENT_INVALID;
        }
        else
        {
            pstCnfData->PBEvent.PBReadCnf.PBRecord.ValidFlag = SI_PB_CONTENT_VALID;
            ulValidFlag = VOS_TRUE;

            SI_PB_BcdToAscii(3, pucContent, pstCnfData->PBEvent.PBReadCnf.PBRecord.Number,
                            &pstCnfData->PBEvent.PBReadCnf.PBRecord.NumberLength);/*Ecc����������ǰ��*/

            pstCnfData->PBEvent.PBReadCnf.PBRecord.NumberType = PB_NUMBER_TYPE_NORMAL;

            if(gastPBContent[PB_ECC_CONTENT].ucNameLen != 0)
            {
                SI_PB_DecodePBName(gastPBContent[PB_ECC_CONTENT].ucNameLen,&pucContent[3],
                                &pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTagType,
                                &pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

                SI_PB_MemSet(sizeof(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag),0xFF,pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag);

                /*lint -e534*/
                VOS_MemCpy(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag, &pucContent[3],
                        pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);
                /*lint +e534*/
            }
            else
            {
                pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength = 0;
            }
        }

        if(i == (usIndexNum-1))
        {
            pstCnfData->PBLastTag = VOS_TRUE;
            pstCnfData->PBError = ((VOS_TRUE == ulValidFlag)?TAF_ERR_NO_ERROR:TAF_ERR_PB_NOT_FOUND);
        }

        /*lint -e534*/
        SI_PBCallback(pstCnfData);
        /*lint +e534*/

        pucContent += gastPBContent[PB_ECC_CONTENT].ucRecordLen;/*����ָ�밴�ռ�¼����ƫ��*/
    }

    return;
}


VOS_UINT32 SI_PB_ReadProc(PBMsgBlock *pMsg)
{
    SI_PB_READ_REQ_STRU         *pstMsg;
    SI_PB_EVENT_INFO_STRU       stCnfData;
    VOS_UINT8                   ucPBoffset;
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usIndexNum;
    VOS_UINT16                  i;
    VOS_UINT8                   *pucContent;
    VOS_UINT32                  ulValidFlag = VOS_FALSE;

    /*lint -e534*/
    VOS_MemSet((VOS_UINT8 *)&stCnfData, (VOS_CHAR)0, sizeof(SI_PB_EVENT_INFO_STRU));
    /*lint +e534*/

    pstMsg = (SI_PB_READ_REQ_STRU*)pMsg;

    stCnfData.ClientId    = pstMsg->usClient;

    stCnfData.OpId        =  pstMsg->ucOpID;

    stCnfData.PBEventType = SI_PB_EVENT_READ_CNF;

    stCnfData.Storage     = pstMsg->ulStorage;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((PB_ECC == pstMsg->ulStorage)
     || (PB_XECC == pstMsg->ulStorage))
    {
        stCnfData.PBError = TAF_ERR_NO_ERROR;
    }
#else
    if (PB_ECC == pstMsg->ulStorage)
    {
        stCnfData.PBError = TAF_ERR_NO_ERROR;
    }
#endif

    else
    {
        stCnfData.PBError = SI_PB_ErrorProc();
    }

    if (TAF_ERR_NO_ERROR != stCnfData.PBError)
    {
        PB_WARNING_LOG("SI_PB_ReadProc: Proc Error");

        return SI_PBCallback(&stCnfData);
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->usIndex1, pstMsg->usIndex2, &ucPBoffset);

    if(VOS_OK != ulResult) /*��ǰ�绰������δ�ҵ�*/
    {
        PB_WARNING_LOG("SI_PB_ReadProc: SI_PB_LocateRecord Return Error");

        stCnfData.PBError = ulResult;

        /*lint -e534*/
        SI_PBCallback(&stCnfData);
        /*lint +e534*/

        return VOS_ERR;
    }

    if(0 == pstMsg->usIndex1)
    {
        usIndexNum       = gastPBContent[ucPBoffset].usTotalNum;

        pstMsg->usIndex1 = 1;/*�ӵ�һ����ʼ��ȡ*/

        pstMsg->usIndex2 = gastPBContent[ucPBoffset].usTotalNum;
    }
    else
    {
        usIndexNum = (pstMsg->usIndex2 - pstMsg->usIndex1) + 1;/*������������֮��ļ�¼��*/
    }

    stCnfData.PBEvent.PBReadCnf.RecordNum = 1;

    /*�������к����ڻ�ɽ��Balong���涼�л���*/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((PB_XECC == pstMsg->ulStorage))
    {
        SI_PB_ReadXeccProc(usIndexNum, pstMsg->usIndex1, &stCnfData);

        gstPBReqUnit.enPBLock = PB_UNLOCK;

        return VOS_OK;
    }
#endif

    if (PB_ECC == pstMsg->ulStorage)
    {
        SI_PB_ReadEccProc(usIndexNum, pstMsg->usIndex1, &stCnfData);

        gstPBReqUnit.enPBLock = PB_UNLOCK;

        return VOS_OK;
    }

    pucContent = gastPBContent[ucPBoffset].pContent + ((pstMsg->usIndex1-1) * gastPBContent[ucPBoffset].ucRecordLen);

    stCnfData.PBLastTag = VOS_FALSE;

    for(i=0; i<usIndexNum; i++)     /*���ݶ�ȡ�ĵ绰��������Χѭ��*/
    {
        /*lint -e534*/
        VOS_MemSet((VOS_UINT8 *)&stCnfData.PBEvent.PBReadCnf, 0, sizeof(SI_PB_EVENT_READ_CNF_STRU));
        /*lint +e534*/

        SI_PB_TransPBFromate(&gastPBContent[ucPBoffset], (VOS_UINT16)(pstMsg->usIndex1+i), pucContent, &stCnfData.PBEvent.PBReadCnf.PBRecord);

        pucContent += gastPBContent[ucPBoffset].ucRecordLen;/*����ָ�밴�ռ�¼����ƫ��*/

        if(SI_PB_CONTENT_VALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBoffset].pIndex,pstMsg->usIndex1+i))/*����Index�ж�SI_PB_CONTENT_VALID == stCnfData.PBEvent.PBReadCnf.PBRecord.ValidFlag) */
        {
            ulValidFlag = VOS_TRUE;
        }

        if(i == (usIndexNum-1))
        {
            stCnfData.PBLastTag = VOS_TRUE;
            stCnfData.PBError = ((VOS_TRUE == ulValidFlag)?TAF_ERR_NO_ERROR:TAF_ERR_PB_NOT_FOUND);
        }

        /*lint -e534*/
        SI_PBCallback(&stCnfData); /*����ת�����*/
        /*lint +e534*/
    }

    return VOS_OK;
}



VOS_UINT32 SI_PB_SearchHandle(SI_PB_SEARCH_REQ_STRU *pMsg,
                                      SI_PB_EVENT_INFO_STRU *pstCnfData,
                                      VOS_UINT8 ucOffset)
{
    VOS_UINT16  usMatchRecordNum = 0;
    VOS_UINT16  i;

    pstCnfData->PBError     = TAF_ERR_NO_ERROR;
    pstCnfData->PBLastTag   = VOS_FALSE;
    gstPBReqUnit.enPBLock   = PB_LOCKED;

    for( i = 0 ; i < gastPBContent[ucOffset].usTotalNum ; i++ )
    {
        if(VOS_ERR == SI_PB_CheckContentValidity(&gastPBContent[ucOffset],
                        gastPBContent[ucOffset].pContent + (i * gastPBContent[ucOffset].ucRecordLen)))
        {
            continue;
        }
        else if((VOS_OK == VOS_MemCmp(pMsg->aucContent, gastPBContent[ucOffset].pContent + (i * gastPBContent[ucOffset].ucRecordLen), pMsg->ucLength))
            ||(0 == pMsg->ucLength))
        {
            SI_PB_TransPBFromate(&gastPBContent[ucOffset], (VOS_UINT16)(i+1),
                                    gastPBContent[ucOffset].pContent + (i * gastPBContent[ucOffset].ucRecordLen),
                                    &pstCnfData->PBEvent.PBSearchCnf.PBRecord);

            usMatchRecordNum++;
            /*lint -e534*/
            SI_PBCallback(pstCnfData);
            /*lint +e534*/
        }
        else
        {
            continue;
        }
    }

    if(0 == usMatchRecordNum)
    {
        return TAF_ERR_PB_NOT_FOUND;
    }

    pstCnfData->PBLastTag = VOS_TRUE;
    pstCnfData->PBEvent.PBSearchCnf.PBRecord.ValidFlag = SI_PB_CONTENT_INVALID;

    /*lint -e534*/
    SI_PBCallback(pstCnfData);
    /*lint +e534*/

    return TAF_ERR_NO_ERROR;
}


VOS_UINT32 SI_PB_SearchReq(SI_PB_SEARCH_REQ_STRU *pMsg,
                                   SI_PB_EVENT_INFO_STRU *pstCnfData,
                                   VOS_UINT8 ucOffset)
{
    VOS_UINT8  ucSendReqFlag = PB_REQ_NOT_SEND;
    VOS_UINT8  ucRecord;
    VOS_UINT32 ulResult;
    VOS_UINT16 usFileId;

    if (pMsg->ucLength <= sizeof(gstPBReqUnit.aucXDNContent))
    {
        /*lint -e534*/
        VOS_MemCpy(gstPBReqUnit.aucXDNContent, pMsg->aucContent, pMsg->ucLength);
        /*lint +e534*/
    }
    else
    {
        PB_WARNING_LOG("SI_PB_SearchReq: Text string too long");

        return TAF_ERR_PARA_ERROR;
    }

    gstPBReqUnit.usCurIndex     = 1;

    gstPBReqUnit.usSearchLen    = pMsg->ucLength;

    gstPBReqUnit.usIndex2       = gastPBContent[ucOffset].usTotalNum;

    gstPBReqUnit.enPBEventType  = SI_PB_EVENT_SEARCH_CNF;

    gstPBReqUnit.ucEqualFlag    = VOS_FALSE;

    gstPBReqUnit.enPBStoateType = pMsg->ulStorage;

    while(gstPBReqUnit.usCurIndex <= gstPBReqUnit.usIndex2)
    {
        if (SI_PB_CONTENT_VALID == SI_PB_GetBitFromBuf(gastPBContent[ucOffset].pIndex,
            gstPBReqUnit.usCurIndex))
        {
            ucSendReqFlag = PB_REQ_SEND;
            break;
        }

        gstPBReqUnit.usCurIndex++;
    }

    if (PB_REQ_SEND == ucSendReqFlag)
    {
        if(SI_PB_STORAGE_SM == pMsg->ulStorage)   /*�����ADN��Ҫת��Ϊ��¼��*/
        {
            ulResult = SI_PB_CountADNRecordNum(gstPBReqUnit.usCurIndex, &usFileId, &ucRecord);
        }
        else                                                                    /*���������绰��*/
        {
            ulResult = SI_PB_GetXDNFileID(pMsg->ulStorage, &usFileId);

            ucRecord = (VOS_UINT8)gstPBReqUnit.usCurIndex;
        }

        if(VOS_ERR == ulResult)         /*ת�����ʧ��*/
        {
            PB_WARNING_LOG("SI_PB_SearchReq: Get the XDN File ID and Record Number is Error");

            pstCnfData->PBError = TAF_ERR_PARA_ERROR;

            return TAF_ERR_PARA_ERROR;
        }
    }
    else
    {
        pstCnfData->PBLastTag = VOS_TRUE;

        PB_WARNING_LOG("SI_PB_SearchReq: Content not found!");

        return TAF_ERR_PB_NOT_FOUND;
    }

    return TAF_ERR_NO_ERROR;
}
VOS_UINT32 SI_PB_SearchProc(PBMsgBlock *pMsg)
{
    SI_PB_EVENT_INFO_STRU   stCnfData;
    VOS_UINT32              ulResult;
    VOS_UINT8               ucOffset = 0;

    stCnfData.ClientId              = ((SI_PB_SEARCH_REQ_STRU*)pMsg)->usClient;
    stCnfData.OpId                  = ((SI_PB_SEARCH_REQ_STRU*)pMsg)->ucOpID;
    stCnfData.PBEventType           = SI_PB_EVENT_SEARCH_CNF;
    stCnfData.PBLastTag             = VOS_TRUE;

    if( TAF_ERR_NO_ERROR != (ulResult = SI_PB_ErrorProc()))/*�����λʧ�ܻ��߻������ݲ�����*/
    {
        stCnfData.PBError  = ulResult;
        stCnfData.PBLastTag = VOS_TRUE;
        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    if(VOS_OK != SI_PB_FindPBOffset(((SI_PB_SEARCH_REQ_STRU*)pMsg)->ulStorage, &ucOffset))
    {
        stCnfData.PBError  = TAF_ERR_UNSPECIFIED_ERROR;

        return SI_PBCallback(&stCnfData); /*����ת�����*/
    }

    if( VOS_NULL_PTR == gastPBContent[ucOffset].pContent )
    {
        if(TAF_ERR_NO_ERROR !=
           (ulResult = SI_PB_SearchReq( (SI_PB_SEARCH_REQ_STRU*)pMsg, &stCnfData, ucOffset ) ) )
        {
            stCnfData.PBError  = ulResult;

            /*lint -e534*/
            SI_PBCallback(&stCnfData); /*����ת�����*/
            /*lint +e534*/
        }

        return VOS_OK;
    }

    if(TAF_ERR_NO_ERROR !=
            (ulResult = SI_PB_SearchHandle( (SI_PB_SEARCH_REQ_STRU*)pMsg, &stCnfData, ucOffset ) ) )
    {
        stCnfData.PBError  = ulResult;

        /*lint -e534*/
        SI_PBCallback(&stCnfData); /*����ת�����*/
        /*lint +e534*/
    }

    return VOS_OK;
}
VOS_UINT32 SI_PB_SReadEMLProc(VOS_UINT16 usIndex, VOS_UINT16 usOffset, SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32  ulEMLContentOffset;
    VOS_UINT8 *pucEMLContent;
    VOS_UINT8 ucEMLRecordNum;
    VOS_UINT8 ucType2EMLFileCnt;
    VOS_UINT8   i;

    /*Email,����Type1��2���ȿ��Ƿ���USED, ������ڶ��ڴ�
    Type1 ֱ�Ӹ���Index��
    Type2 ����Index��IAP����ת����ʵ�ʼ�¼�ţ������¼����Ч���˳�*/
    if(0 == gstPBCtrlInfo.ulEMLFileNum)
    {
        PB_WARNING_LOG("SI_PB_SReadEMLProc: No Valid Email Record");
        return VOS_OK;
    }

    if(PB_FILE_TYPE1 == gstPBCtrlInfo.astEMLInfo[0].enEMLType)/*Email�ļ����ͣ�*/
    {
        /* ����TYPE1���͵��ļ���ת��Ĳ���usIndex + usOffset���ܳ���EMAIL���ܼ�¼�� */
        if ((usIndex + usOffset) > gstEMLContent.usTotalNum)
        {
            PB_WARNING_LOG("SI_PB_SReadEMLProc: Email Record Index Large than Total Number.");
            return VOS_OK;
        }

        pucEMLContent = gstEMLContent.pContent
            +((usIndex+(usOffset-1))*gstEMLContent.ucRecordLen);
    }
    else
    {
        if(VOS_NULL_PTR == gstIAPContent.pIAPContent)
        {
            PB_ERROR_LOG("SI_PB_SReadEMLProc: IAP Storage NULL");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        /*Type2 Email�ļ�������gstIAPContent.pIAPContent���ҵ�ADN ��¼��EML��¼��Ӧ��ϵ*/
        ucEMLRecordNum = gstIAPContent.pIAPContent[(((usIndex+usOffset)-1)*gstIAPContent.ucRecordLen)
                                                    +(gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum - 1)];

        if (VOS_OK != SI_PB_GetFileCntFromIndex(usIndex + usOffset, &ucType2EMLFileCnt))
        {
            PB_WARNING_LOG("SI_PB_SReadEMLProc: SI_PB_GetFileCntFromIndex Return Error.");
            return VOS_OK;
        }

        if ((gstPBCtrlInfo.astEMLInfo[ucType2EMLFileCnt - 1].ucRecordNum < ucEMLRecordNum)
            || (0xFF == ucEMLRecordNum)||(0 == ucEMLRecordNum))
        {
            PB_INFO_LOG("SI_PB_SReadEMLProc: No Email Record");
            return VOS_OK;
        }

        ulEMLContentOffset = (ucEMLRecordNum - 1)
                        * gstPBCtrlInfo.astEMLInfo[ucType2EMLFileCnt - 1].ucRecordLen;

        /* ����EMAIL�ļ�ÿ����¼�����ܲ�һ�£���Ҫ����ۼ�������ƫ���� */
        for (i = 0; i < (ucType2EMLFileCnt - 1); i++)
        {
            ulEMLContentOffset += gstPBCtrlInfo.astEMLInfo[i].ucRecordLen
                        * gstPBCtrlInfo.astEMLInfo[i].ucRecordNum;
        }

        pucEMLContent = gstEMLContent.pContent + ulEMLContentOffset;
    }

    SI_PB_TransEMLFromate(gstEMLContent.ucDataLen, pucEMLContent, pstRecord);

    return VOS_OK;
}


VOS_UINT32 SI_PB_SReadANRProc(VOS_UINT16 usIndex, VOS_UINT16 usOffset, SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32 ulAnrContentOffset;
    VOS_UINT16 i,j;
    VOS_UINT8  *pucANRContent;
    VOS_UINT8  ucType2ANRRecord;
    VOS_UINT8  ucType2ANRFileCnt;

    /*ANR,�ȸ��ݻ�������ж��Ƿ����USED��������ڶ��ڴ棬�ڴ�Ϊ�������
    �ڴ����ݶ��������ж�*/
    for(i = 0; i < gstPBCtrlInfo.ulANRStorageNum; i++)
    {
        if(VOS_NULL == gastANRContent[i].pContent)
        {
            PB_ERROR_LOG("SI_PB_SReadANRProc: Storage NULL");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        /*���ΪType2����ANR����Ҫͨ��IAP�ҵ���ʵ��Ҫ��ȡ��*/
        if(PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType)
        {
            if(VOS_NULL == gstIAPContent.pIAPContent)
            {
                PB_ERROR_LOG("SI_PB_SReadANRProc: Storage NULL");
                return TAF_ERR_PB_STORAGE_OP_FAIL;
            }

            ucType2ANRRecord = gstIAPContent.pIAPContent[(((usIndex+usOffset)-1)*gstIAPContent.ucRecordLen)
                                    +(gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1)];

            if (VOS_OK != SI_PB_GetFileCntFromIndex(usIndex + usOffset, &ucType2ANRFileCnt))
            {
                PB_WARNING_LOG("SI_PB_SReadANRProc: SI_PB_GetFileCntFromIndex Return Error.");

                continue;
            }

            /*Index��Ӧ��Type2 ANR��Ч*/
            if ((gstPBCtrlInfo.astANRInfo[ucType2ANRFileCnt - 1][i].ucRecordNum < ucType2ANRRecord)
                ||(0 == ucType2ANRRecord)||(0xFF == ucType2ANRRecord))
            {
                PB_NORMAL_LOG("SI_PB_SReadANRProc: Empty Type2 ANR Or Invalid");

                continue;
            }

            ulAnrContentOffset = (ucType2ANRRecord - 1)*gastANRContent[i].ucRecordLen;

            for (j = 0; j < (ucType2ANRFileCnt - 1); j++)
            {
                ulAnrContentOffset += gstPBCtrlInfo.astANRInfo[j][i].ucRecordNum
                                        * gstPBCtrlInfo.astANRInfo[j][i].ucRecordLen;
            }

            pucANRContent = gastANRContent[i].pContent + ulAnrContentOffset;
        }
        else
        {
            /* ����TYPE1���͵�ANR�ļ���ת��Ĳ���usIndex + usOffset���ܳ���ANR���ܼ�¼�� */
            if ((usIndex + usOffset) > gastANRContent[i].usTotalNum)
            {
                continue;
            }

            pucANRContent = gastANRContent[i].pContent
                            +(((usIndex+usOffset)-1)*gastANRContent[i].ucRecordLen);
        }

        SI_PB_TransANRFromate((VOS_UINT8)i, pucANRContent, pstRecord);
    }

    return VOS_OK;
}
VOS_UINT32 SI_PB_SReadProc(PBMsgBlock *pMsg)
{
    SI_PB_READ_REQ_STRU         *pstMsg;
    SI_PB_EVENT_INFO_STRU       stCnfData;
    VOS_UINT8                   ucPBoffset;
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usIndexNum;
    VOS_UINT16                  i;
    VOS_UINT8                   *pucContent;
    VOS_UINT8                   *pucTempContent;
    VOS_UINT32                  ulValidFlag = VOS_FALSE;

    /*lint -e534*/
    VOS_MemSet((VOS_UINT8 *)&stCnfData, 0, sizeof(SI_PB_EVENT_INFO_STRU));
    /*lint +e534*/

    pstMsg = (SI_PB_READ_REQ_STRU*)pMsg;

    stCnfData.ClientId    = pstMsg->usClient;

    stCnfData.OpId        =  pstMsg->ucOpID;

    stCnfData.PBEventType = SI_PB_EVENT_SREAD_CNF;

    stCnfData.Storage     = pstMsg->ulStorage;

    if((0 == gstPBConfigInfo.ucSPBFlag)||(SI_PB_STORAGE_SM != pstMsg->ulStorage))
    {
        /*��ΪOperation not allowed*/
        stCnfData.PBError = TAF_ERR_CMD_TYPE_ERROR;

        PB_WARNING_LOG("SI_PB_SReadProc: Proc is Not Allow");

        return SI_PBCallback(&stCnfData);
    }

    stCnfData.PBError = SI_PB_ErrorProc();

    if (TAF_ERR_NO_ERROR != stCnfData.PBError)
    {
        PB_WARNING_LOG("SI_PB_SReadProc: Proc Error");

        return SI_PBCallback(&stCnfData);
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->usIndex1, pstMsg->usIndex2, &ucPBoffset);

    if(VOS_OK != ulResult) /*��ǰ�绰������δ�ҵ�*/
    {
        PB_WARNING_LOG("SI_PB_SReadProc: SI_PB_LocateRecord Return Error");

        stCnfData.PBError = ulResult;

        /*lint -e534*/
        SI_PBCallback(&stCnfData);
        /*lint +e534*/

        return VOS_ERR;
    }

    if(0 == pstMsg->usIndex1)
    {
        usIndexNum       = gastPBContent[ucPBoffset].usTotalNum;

        pstMsg->usIndex1 = 1;/*�ӵ�һ����ʼ��ȡ*/

        pstMsg->usIndex2 = gastPBContent[ucPBoffset].usTotalNum;
    }
    else
    {
        usIndexNum = (pstMsg->usIndex2 - pstMsg->usIndex1) + 1;/*������������֮��ļ�¼��*/
    }

    if(VOS_NULL == gastPBContent[ucPBoffset].pContent)/*ADNһ�����ڻ���*/
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;

        PB_WARNING_LOG("SI_PB_SReadProc: The ADN Memory Error");

        return SI_PBCallback(&stCnfData);
    }

    pucContent = gastPBContent[ucPBoffset].pContent + ((pstMsg->usIndex1-1) * gastPBContent[ucPBoffset].ucRecordLen);

    stCnfData.PBLastTag = VOS_FALSE;

    for(i=0; i<usIndexNum; i++)     /*���ݶ�ȡ�ĵ绰��������Χѭ��*/
    {
        stCnfData.PBError = VOS_OK;

        /*lint -e534*/
        VOS_MemSet((VOS_UINT8 *)&stCnfData.PBEvent.PBReadCnf, 0, sizeof(SI_PB_EVENT_READ_CNF_STRU));
        /*lint +e534*/

        stCnfData.PBEvent.PBReadCnf.RecordNum = 1;

        stCnfData.PBEvent.PBReadCnf.PBRecord.Index = (VOS_UINT16)(pstMsg->usIndex1+i);

        /*������¼��Ч���Ҳ������һ��*/
        if(SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBoffset].pIndex,pstMsg->usIndex1+i))/*��Index�л�ȡ��Ч��Ϣ*/
        {
            if(i == (usIndexNum-1))/*���һ����¼��Ч*/
            {
                stCnfData.PBError = ((VOS_TRUE == ulValidFlag)?TAF_ERR_NO_ERROR:TAF_ERR_PB_NOT_FOUND);
                stCnfData.PBLastTag = VOS_TRUE;

                return SI_PBCallback(&stCnfData);
            }
            else
            {
                continue;
            }
        }

        ulValidFlag = VOS_TRUE;

        pucTempContent = pucContent + (i*gastPBContent[ucPBoffset].ucRecordLen);/*����ָ�밴�ռ�¼����ƫ��*/

        SI_PB_TransPBFromate(&gastPBContent[ucPBoffset], (VOS_UINT16)(pstMsg->usIndex1+i), pucTempContent, &stCnfData.PBEvent.PBReadCnf.PBRecord);

        /*ANR,�ȸ��ݻ�������ж��Ƿ����USED��������ڶ��ڴ棬�ڴ�Ϊ�������
        �ڴ����ݶ��������ж�*/
        ulResult = SI_PB_SReadANRProc(pstMsg->usIndex1, i, &stCnfData.PBEvent.PBReadCnf.PBRecord);

        if(VOS_OK != ulResult)
        {
            stCnfData.PBError = ulResult;

            PB_WARNING_LOG("SI_PB_SReadProc: SI_PB_SReadANRProc Return Error");

            return SI_PBCallback(&stCnfData);
        }

        ulResult = SI_PB_SReadEMLProc(pstMsg->usIndex1, i, &stCnfData.PBEvent.PBReadCnf.PBRecord);

        if(VOS_OK != ulResult)
        {
            stCnfData.PBError = ulResult;

            PB_WARNING_LOG("SI_PB_SReadProc: SI_PB_SReadEMLProc Return Error");

            return SI_PBCallback(&stCnfData);
        }

        /*��ȡ���������һ����¼�����ñ�־λΪTrue*/
        if(i == (usIndexNum-1))
        {
            stCnfData.PBLastTag = VOS_TRUE;
        }

        /*lint -e534*/
        SI_PBCallback(&stCnfData); /*����ת�����*/
        /*lint +e534*/
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : SI_PBUpdateGobal
��������  : ���ڴ���Ccpu�绰�����͵�ȫ�ֱ�����ʼ�������Ϣ
�������  : Ccpu���͵���Ϣ����
�������  : ��
�� �� ֵ  : ��
�޶���¼  :
1.  ��    ��   : 2007��10��15��
    ��    ��   :
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 SI_PBUpdateAGlobal(PBMsgBlock *pMsg)
{
    SI_PB_UPDATEGLOBAL_IND_STRU        *pstMsg;

#if (VOS_LINUX == VOS_OS_VER)
    VOS_UINT32                          i;
    VOS_UINT_PTR                        TempAddr;
#endif

    pstMsg = (SI_PB_UPDATEGLOBAL_IND_STRU*)pMsg;

    /*lint -e534*/
    VOS_MemCpy(&gstPBCtrlInfo,  &pstMsg->stPBCtrlInfo,   sizeof(gstPBCtrlInfo));
    VOS_MemCpy(&gstPBConfigInfo,&pstMsg->stPBConfigInfo, sizeof(gstPBConfigInfo));
    VOS_MemCpy(gastPBContent,   pstMsg->astPBContent,   sizeof(gastPBContent));
    VOS_MemCpy(gastEXTContent,  pstMsg->astEXTContent,  sizeof(gastEXTContent));
    VOS_MemCpy(gastANRContent,  pstMsg->astANRContent,  sizeof(gastANRContent));
    VOS_MemCpy(&gstEMLContent,  &pstMsg->stEMLContent,   sizeof(gstEMLContent));
    VOS_MemCpy(&gstIAPContent,  &pstMsg->stIAPContent,   sizeof(gstIAPContent));
    VOS_MemCpy(&gstPBInitState, &pstMsg->stPBInitState,  sizeof(gstPBInitState));
    /*lint +e534*/

#if (VOS_LINUX == VOS_OS_VER)
    for (i=0; i<PB_CONTENT_BUTT; i++)
    {
        gastPBContent[i].pContent   = VOS_NULL_PTR;

        TempAddr = pstMsg->astPBContentAddr[i].ulContentAddr;

        gastPBContent[i].pContent   = (VOS_UINT8 *)TempAddr;

        gastPBContent[i].pIndex     = VOS_NULL_PTR;

        TempAddr = pstMsg->astPBContentAddr[i].ulIndexAddr;

        gastPBContent[i].pIndex     = (VOS_UINT8 *)TempAddr;

        if(VOS_NULL_PTR != gastPBContent[i].pContent)
        {
            gastPBContent[i].pContent   = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gastPBContent[i].pContent);
        }
        if (VOS_NULL_PTR != gastPBContent[i].pIndex)
        {
            gastPBContent[i].pIndex     = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gastPBContent[i].pIndex);
        }
    }

    for (i=0; i<SI_PB_MAX_NUMBER; i++)
    {
        gastEXTContent[i].pExtContent   = VOS_NULL_PTR;

        TempAddr = pstMsg->aulExtContentAddr[i];

        gastEXTContent[i].pExtContent   = (VOS_UINT8 *)TempAddr;

        if(VOS_NULL_PTR != gastEXTContent[i].pExtContent)
        {
            gastEXTContent[i].pExtContent   = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gastEXTContent[i].pExtContent);
        }
    }

    for (i=0; i<SI_PB_ANRMAX; i++)
    {
        gastANRContent[i].pContent   = VOS_NULL_PTR;

        TempAddr = pstMsg->aulANRContentAddr[i];

        gastANRContent[i].pContent   = (VOS_UINT8*)TempAddr;

        if(VOS_NULL_PTR != gastANRContent[i].pContent)
        {
            gastANRContent[i].pContent   = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gastANRContent[i].pContent);
        }
    }

    gstEMLContent.pContent  = VOS_NULL_PTR;

    TempAddr = pstMsg->ulEMLContentAddr;

    gstEMLContent.pContent      = (VOS_UINT8*)TempAddr;

    if(VOS_NULL_PTR != gstEMLContent.pContent)
    {
        gstEMLContent.pContent  = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gstEMLContent.pContent);
    }

    gstIAPContent.pIAPContent   = VOS_NULL_PTR;

    TempAddr = pstMsg->ulIAPContentAddr;

    gstIAPContent.pIAPContent   = (VOS_UINT8*)TempAddr;

    if(VOS_NULL_PTR != gstIAPContent.pIAPContent)
    {
        gstIAPContent.pIAPContent   = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gstIAPContent.pIAPContent);
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : SI_PBUpdateACurPB
��������  : ���ڴ���Ccpu���͵ĸ��µ�ǰ�绰��������Ϣ
�������  : Ccpu���͵ĸ���������Ϣ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2007��10��15��
    ��    ��   :
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 SI_PBUpdateACurPB(PBMsgBlock *pMsg)
{
    SI_PB_SETPB_IND_STRU *pstMsg;

    pstMsg = (SI_PB_SETPB_IND_STRU*)pMsg;

    gstPBCtrlInfo.enPBCurType = pstMsg->enPBCurType;

    return VOS_OK;
}
#endif

#if ((OSA_CPU_CCPU == VOS_OSA_CPU)||(defined(DMT)))
/*****************************************************************************
�� �� ��  : SI_PB_InitStatusInd
��������  : PBģ�鷢�͵绰����ʼ��״ָ̬ʾ��Ϣ
�������  : enPBInitStatus:�绰����ʼ��״̬
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��01��30��
  ��    ��  : h00300778
  �޸�����  : Create
*****************************************************************************/
VOS_VOID SI_PB_InitStatusInd(USIMM_PB_INIT_STATUS_ENUM_UINT16 enPBInitStatus)
{
    USIMM_PBINIT_STATUS_IND_STRU       *pstMsg;

    pstMsg = (USIMM_PBINIT_STATUS_IND_STRU *)VOS_AllocMsg(MAPS_PB_PID,
                                                          sizeof(USIMM_PBINIT_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PB_WARNING_LOG("SI_PB_InitStatusInd: VOS_AllocMsg is Failed");

        return ;
    }

    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_PBINIT_STATUS_IND;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = VOS_NULL;
    pstMsg->enPBInitStatus              = enPBInitStatus;
    pstMsg->usRsv                       = VOS_NULL;

    /*lint -e534*/
    VOS_SendMsg(MAPS_PB_PID, pstMsg);
    /*lint +e534*/

    return ;
}


VOS_UINT8 SI_PB_AlphaTagTruncation(SI_PB_RECORD_STRU *pstRecord, VOS_UINT8 ucOffset)
{
    VOS_UINT8  uctemp;
    VOS_UINT8  ucLen;

    /*�����������Ϊ0���򷵻�Copy����Ϊ0*/
    if (0 == pstRecord->ucAlphaTagLength)
    {
        PB_INFO_LOG("SI_PB_AlphaTagTruncation: The Name Len is 0");
        return 0;
    }

    if (SI_PB_ALPHATAG_TYPE_UCS2_80 == pstRecord->AlphaTagType)
    {
        uctemp = gastPBContent[ucOffset].ucNameLen\
                    - ((gastPBContent[ucOffset].ucNameLen - 1)%2); /* [false alarm]:���  */

        return (pstRecord->ucAlphaTagLength > uctemp)?uctemp:pstRecord->ucAlphaTagLength; /* [false alarm]:���  */
    }
    else if (SI_PB_ALPHATAG_TYPE_GSM == pstRecord->AlphaTagType)
    {
        if(pstRecord->ucAlphaTagLength > gastPBContent[ucOffset].ucNameLen)
        {
            ucLen = gastPBContent[ucOffset].ucNameLen;

            ucLen = (SI_PB_ALPHATAG_TRANSFER_TAG == pstRecord->AlphaTag[ucLen-1]) ? (ucLen-1) : (ucLen);
        }
        else
        {
             ucLen = pstRecord->ucAlphaTagLength;
        }

        return ucLen;
    }
    else/*ʣ��81��82�����������*/
    {
        /*���㱻��ȥ�ĳ���*/
        uctemp = (pstRecord->ucAlphaTagLength > gastPBContent[ucOffset].ucNameLen)?\
                  gastPBContent[ucOffset].ucNameLen:pstRecord->ucAlphaTagLength;

        pstRecord->AlphaTag[1] =  uctemp - ((0x81 == pstRecord->AlphaTag[0])?3:4);

        return uctemp;
    }
}
VOS_UINT32 SI_PB_UpdataXDNFile(VOS_UINT8 ucPBOffset, VOS_UINT16 usFileId, VOS_UINT16 usExtFileId,
                                        VOS_UINT8 ucRecord,SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT8                   ucCopyLen;
    VOS_UINT8                   ucExtRecord;
    VOS_UINT32                  ulResult;
    VOS_UINT32                  ulXDNContentOffset;
    VOS_UINT32                  ulExtInfoNum;
    SI_PB_SETFILE_INFO_STRU     stUpdateReq;

    SI_PB_MemSet(sizeof(gstPBReqUnit.aucXDNContent), 0xFF,gstPBReqUnit.aucXDNContent);
    SI_PB_MemSet(sizeof(gstPBReqUnit.aucEXTContent), 0xFF, gstPBReqUnit.aucEXTContent);

    ucCopyLen = SI_PB_AlphaTagTruncation(pstRecord, ucPBOffset);

    /*lint -e534*/
    VOS_MemCpy(gstPBReqUnit.aucXDNContent, pstRecord->AlphaTag, ucCopyLen);
    /*lint +e534*/

    if(pstRecord->NumberLength != 0)
    {
        gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen+1] = pstRecord->NumberType;
    }

    if( ( pstRecord->NumberLength > SI_PB_NUM_LEN ) && ( 0xFFFF != usExtFileId ) )
    {
        SI_PB_AsciiToBcd(pstRecord->Number, SI_PB_NUM_LEN,
                        &gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen+2],&ucCopyLen);

        gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen] = ucCopyLen + 1;

        ulXDNContentOffset = ( pstRecord->Index - 1 ) * gastPBContent[ucPBOffset].ucRecordLen;

        (ucPBOffset == PB_BDN_CONTENT)?\
                (ulXDNContentOffset += gastPBContent[ucPBOffset].ucRecordLen - 2):
                (ulXDNContentOffset += gastPBContent[ucPBOffset].ucRecordLen - 1);

        /* ��鵱ǰ���µļ�¼�Ƿ��Ѿ�ռ����һ��EXT�ļ���¼ */
        ucExtRecord  = gastPBContent[ucPBOffset].pContent[ulXDNContentOffset];
        ulExtInfoNum = gastPBContent[ucPBOffset].ulExtInfoNum;

        /* ���XDN��¼��Ӧ�Ѿ�������EXT��¼������Ҫȥ���ҿ��е�EXT��¼ */
        if((0xFF == ucExtRecord)||(0 == ucExtRecord))
        {
            /* �ҵõ����е�EXT�ļ���¼ʱ�Ÿ���EXT�ļ����Ҳ����Ͳ����£���������Ҳ������ */
            ulResult = SI_PB_FindUnusedExtRecord( gastEXTContent + ulExtInfoNum, &ucExtRecord, 1);
        }
        else
        {
            ulResult = VOS_OK;
        }

        if ((ucExtRecord <= gastEXTContent[ulExtInfoNum].usExtTotalNum)
            && (VOS_OK == ulResult))
        {
            SI_PB_AsciiToBcd(pstRecord->Number + SI_PB_NUM_LEN, \
                                (VOS_UINT8)(pstRecord->NumberLength - SI_PB_NUM_LEN),\
                                gstPBReqUnit.aucEXTContent+2, &ucCopyLen);

            gstPBReqUnit.aucEXTContent[0] = SI_PB_ADDITIONAL_NUM;
            gstPBReqUnit.aucEXTContent[1] = ucCopyLen;

            stUpdateReq.pucEfContent    = gstPBReqUnit.aucEXTContent;
            stUpdateReq.ucRecordNum     = ucExtRecord;
            stUpdateReq.ulEfLen         = SI_PB_EXT_LEN;
            stUpdateReq.usEfId          = usExtFileId;

            ulResult = SI_PB_SetFileReq(&stUpdateReq);
        }

        /* �ȸ���EXT�ļ��ٸ���ADN�ļ����ݣ��������EXT�ļ�ʧ�ܣ���Ӧ�ı�־λ����ΪFF */
        if(VOS_OK != ulResult)
        {
            gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen+13] = 0xFF;
        }
        else
        {
            gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen+13] = ucExtRecord;
            gstPBReqUnit.usExtIndex = ucExtRecord;
        }

        stUpdateReq.pucEfContent    = gstPBReqUnit.aucXDNContent;
        stUpdateReq.ucRecordNum     = ucRecord;
        stUpdateReq.ulEfLen         = gastPBContent[ucPBOffset].ucRecordLen;
        stUpdateReq.usEfId          = usFileId;

        /* �������XDN�ļ��ɹ�������Ϊ����EXT�ļ�Ҳ�ǳɹ��� */
        return SI_PB_SetFileReq(&stUpdateReq);
    }

    SI_PB_AsciiToBcd(pstRecord->Number,pstRecord->NumberLength,
                        &gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen+2],&ucCopyLen);

    if(0 != pstRecord->NumberLength)
    {
        gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen] = ucCopyLen + 1;
    }

    stUpdateReq.pucEfContent    = gstPBReqUnit.aucXDNContent;
    stUpdateReq.ucRecordNum     = ucRecord;
    stUpdateReq.ulEfLen         = gastPBContent[ucPBOffset].ucRecordLen;
    stUpdateReq.usEfId          = usFileId;

    return SI_PB_SetFileReq(&stUpdateReq);
}
VOS_UINT32 SI_PB_UpdataADN(SI_PB_RECORD_STRU        *pstRecord,
                                   SI_PB_SPBDATA_STRU       *pstSPBReq,
                                   VOS_UINT16               *pusExtUsedNum,
                                   SI_PB_SPB_UPDATE_STRU    *pstPBFid)
{
    VOS_UINT8  ucCopyLen;
    VOS_UINT8  ucNumberLen;
    VOS_UINT8  ucExtRecord;
    VOS_UINT16 *pusFileNum;
    VOS_UINT32 ulEXTContentOffset;
    VOS_UINT32 ulResult = VOS_OK;

    pusFileNum = &pstSPBReq->usFileNum;

    SI_PB_MemSet(sizeof(gstPBReqUnit.aucXDNContent), 0xFF,gstPBReqUnit.aucXDNContent);

    ucCopyLen = SI_PB_AlphaTagTruncation(pstRecord, PB_ADN_CONTENT);

    /*���������µ��������ݵ�����*/
    /*lint -e534*/
    VOS_MemCpy(gstPBReqUnit.aucXDNContent, pstRecord->AlphaTag, ucCopyLen);
    /*lint +e534*/

    /*����ADN����*/
    if(0 != pstRecord->NumberLength)
    {
        gstPBReqUnit.aucXDNContent[gastPBContent[PB_ADN_CONTENT].ucNameLen+1] = pstRecord->NumberType;

        ucNumberLen = (pstRecord->NumberLength > SI_PB_NUM_LEN)?SI_PB_NUM_LEN:pstRecord->NumberLength;

        /*ת�������������º������ݵ�����*/
        SI_PB_AsciiToBcd(pstRecord->Number, ucNumberLen,
                        &gstPBReqUnit.aucXDNContent[gastPBContent[PB_ADN_CONTENT].ucNameLen+2],&ucCopyLen);

        gstPBReqUnit.aucXDNContent[gastPBContent[PB_ADN_CONTENT].ucNameLen] = ucCopyLen + 1;
    }

    ulEXTContentOffset = ( pstRecord->Index - 1 ) * gastPBContent[PB_ADN_CONTENT].ucRecordLen;

    ulEXTContentOffset += gastPBContent[PB_ADN_CONTENT].ucRecordLen - 1;

    /* ��鵱ǰ���µļ�¼�Ƿ��Ѿ�ռ����һ��EXT�ļ���¼ */
    ucExtRecord  = gastPBContent[PB_ADN_CONTENT].pContent[ulEXTContentOffset];
    ucExtRecord = ((ucExtRecord <= gastEXTContent[PB_ADN_CONTENT].usExtTotalNum) ? (ucExtRecord) : 0xFF);

    SI_PB_MemSet(sizeof(gstPBReqUnit.aucEXTContent), 0xFF, gstPBReqUnit.aucEXTContent);

    /*ADN�������봦��*/
    if(pstRecord->NumberLength > SI_PB_NUM_LEN)
    {
        if ( VOS_NULL_PTR == gastEXTContent[PB_ADN_CONTENT].pExtContent)
        {
            /*������*/
            /*Operation not allowed*/
            PB_WARNING_LOG("SI_PB_UpdataADN:Ext Content NULL");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        /*���û�ж�Ӧ��EXT�ļ���¼��ҪѰ�ҿ���EXT��¼*/
        if(0xFF == ucExtRecord)
        {
            /* �ҵõ����е�EXT�ļ���¼ʱ�Ÿ���EXT�ļ����Ҳ����Ͳ����£���������Ҳ������ */
            ulResult = SI_PB_FindUnusedExtRecord( &gastEXTContent[PB_ADN_CONTENT], &ucExtRecord, (VOS_UINT8)*pusExtUsedNum);

            (*pusExtUsedNum)++;
        }

        if(VOS_OK == ulResult)
        {
            SI_PB_AsciiToBcd(pstRecord->Number + SI_PB_NUM_LEN, \
                                (VOS_UINT8)(pstRecord->NumberLength - SI_PB_NUM_LEN),\
                                gstPBReqUnit.aucEXTContent+2, &ucCopyLen);

            gstPBReqUnit.usExtIndex = ucExtRecord;
            gstPBReqUnit.aucEXTContent[0] = SI_PB_ADDITIONAL_NUM;
            gstPBReqUnit.aucEXTContent[1] = ucCopyLen;
            gstPBReqUnit.aucXDNContent[gastPBContent[PB_ADN_CONTENT].ucRecordLen-1] = ucExtRecord;

            /*��¼�����µ�EXT��¼��Ϣ*/
            pstSPBReq->usFileID[*pusFileNum]  = pstPBFid->usExtFileId;
            pstSPBReq->usDataLen[*pusFileNum] = SI_PB_EXT_LEN;
            pstSPBReq->ucRecordNum[*pusFileNum] = ucExtRecord;
            pstSPBReq->pContent[*pusFileNum] = gstPBReqUnit.aucEXTContent;
            (*pusFileNum)++;
        }
        else
        {
            /*Buffer full*/
            PB_WARNING_LOG("SI_PB_UpdataADN:ADN Ext Number Full");
            return TAF_ERR_PB_STORAGE_FULL;
        }
    }
    else
    {
        /*��������ļ�ʱ���볤��С��20��������Ҫ��EXT����ɾ��*/
        if((0xFF != ucExtRecord)&&(0xFFFF != pstPBFid->usExtFileId))
        {
            gstPBReqUnit.aucEXTContent[0] = 0;
            gstPBReqUnit.usExtIndex = ucExtRecord;

            pstSPBReq->usFileID[*pusFileNum]  = pstPBFid->usExtFileId;
            pstSPBReq->usDataLen[*pusFileNum] = SI_PB_EXT_LEN;
            pstSPBReq->ucRecordNum[*pusFileNum] = ucExtRecord;
            pstSPBReq->pContent[*pusFileNum] = gstPBReqUnit.aucEXTContent;
            (*pusFileNum)++;
        }

        gstPBReqUnit.aucXDNContent[gastPBContent[PB_ADN_CONTENT].ucRecordLen-1] = 0xFF;
    }

    /*��¼�����µ�ADN��¼��Ϣ,�ڸ���EXT�ļ�֮��*/
    pstSPBReq->usFileID[*pusFileNum]  = pstPBFid->usADNFileId;
    pstSPBReq->ucRecordNum[*pusFileNum] = pstPBFid->ucRecordNum;
    pstSPBReq->usDataLen[*pusFileNum] = gastPBContent[PB_ADN_CONTENT].ucRecordLen;
    pstSPBReq->pContent[*pusFileNum] = gstPBReqUnit.aucXDNContent;
    (*pusFileNum)++;

    return VOS_OK;
}
VOS_UINT32 SI_PB_UpdataType2ANR(SI_PB_RECORD_STRU       *pstRecord,
                                            SI_PB_SPBDATA_STRU     *pstSPBReq,
                                            SI_PB_SPB_UPDATE_STRU  *pstPBFid,
                                            VOS_UINT32              i,
                                            VOS_UINT8              *pucFreeANRRecord)
{
    VOS_UINT32 ulType2ANROffset;

    if(VOS_NULL_PTR == gstIAPContent.pIAPContent)
    {
        PB_WARNING_LOG("SI_PB_UpdataType2ANR:IAP Content NULL");
        return TAF_ERR_PB_STORAGE_OP_FAIL;
    }

    ulType2ANROffset = ((pstRecord->Index-1)*gstIAPContent.ucRecordLen)
            + (gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum - 1);

    if((0xFF == gstIAPContent.pIAPContent[ulType2ANROffset])
        &&(0 != pstRecord->AdditionNumber[i].NumberLength))
    {
        if(VOS_OK != SI_PB_GetFreeANRRecordNum(pstPBFid->ausANRFileId[i],
                     pucFreeANRRecord,
                     &pstSPBReq->usFileID[pstSPBReq->usFileNum]))
        {
            PB_WARNING_LOG("SI_PB_UpdataType2ANR:No Free ANR Record");
            return TAF_ERR_PB_STORAGE_FULL;
        }


        /*���֧��20��Type2�����ļ�*/
        if(20 < gstIAPContent.ucRecordLen)
        {
            PB_ERROR_LOG("SI_PB_UpdataType2ANR:IAP ucRecordLen too long");

            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        /*lint -e534*/
        VOS_MemCpy(gstPBReqUnit.stSPBReq.aucIAPContent,
                    &gstIAPContent.pIAPContent[(pstRecord->Index-1)*gstIAPContent.ucRecordLen], gstIAPContent.ucRecordLen);
        /*lint +e534*/

        gstPBReqUnit.stSPBReq.aucIAPContent[gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1] =
             *pucFreeANRRecord;

        /*��Ҫ��ʱ�����ڴ���IAP����*/
        gstIAPContent.pIAPContent[ulType2ANROffset] = *pucFreeANRRecord;

        pstSPBReq->ucRecordNum[pstSPBReq->usFileNum] = pstPBFid->ucRecordNum;
        pstSPBReq->usDataLen[pstSPBReq->usFileNum] = gstIAPContent.ucRecordLen;
        pstSPBReq->pContent[pstSPBReq->usFileNum] = gstPBReqUnit.stSPBReq.aucIAPContent;

        pstSPBReq->usFileNum++;
    }
    /*û����Ҫ���µļ�¼*/
    else if((0xFF == gstIAPContent.pIAPContent[ulType2ANROffset])
        &&(0 == pstRecord->AdditionNumber[i].NumberLength))
    {
        PB_INFO_LOG("SI_PB_UpdataType2ANR: The Record is not found");
        return TAF_ERR_PB_NOT_FOUND;
    }
    /*ANR������Ϊ�գ���Ҫɾ��IAP�ж�Ӧ��ϵ*/
    else if((0xFF != gstIAPContent.pIAPContent[ulType2ANROffset])
        &&(0 == pstRecord->AdditionNumber[i].NumberLength))
    {
        *pucFreeANRRecord = gstIAPContent.pIAPContent[ulType2ANROffset];

        /*���֧��20��Type2�����ļ�*/
        if(20 < gstIAPContent.ucRecordLen)
        {
            PB_ERROR_LOG("SI_PB_DeleteHandleEmail:IAP ucRecordLen too long");

            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        if(VOS_OK != SI_PB_GetIAPFidFromANR(pstPBFid->ausANRFileId[i],
                               &pstSPBReq->usFileID[pstSPBReq->usFileNum]))
        {
            PB_WARNING_LOG("SI_PB_UpdataANR:No IAP");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        /*lint -e534*/
        VOS_MemCpy(gstPBReqUnit.stSPBReq.aucIAPContent,
                    &gstIAPContent.pIAPContent[(pstRecord->Index-1)*gstIAPContent.ucRecordLen], gstIAPContent.ucRecordLen);
        /*lint +e534*/

        gstPBReqUnit.stSPBReq.aucIAPContent[gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1] = 0xFF;

        /*��Ҫ��ʱ�����ڴ���IAP����*/
        gstIAPContent.pIAPContent[ulType2ANROffset] = 0xFF;

        pstSPBReq->ucRecordNum[pstSPBReq->usFileNum] = pstPBFid->ucRecordNum;
        pstSPBReq->usDataLen[pstSPBReq->usFileNum] = gstIAPContent.ucRecordLen;
        pstSPBReq->pContent[pstSPBReq->usFileNum] = gstPBReqUnit.stSPBReq.aucIAPContent;

        pstSPBReq->usFileNum++;
    }
    else
    {
        *pucFreeANRRecord = gstIAPContent.pIAPContent[ulType2ANROffset];
    }

    return VOS_OK;
}


VOS_UINT32 SI_PB_UpdataANR(SI_PB_RECORD_STRU        *pstRecord,
                                    SI_PB_SPBDATA_STRU      *pstSPBReq,
                                    VOS_UINT16              *pusExtUsedNum,
                                    SI_PB_SPB_UPDATE_STRU   *pstPBFid)
{
    VOS_UINT32 i;
    VOS_UINT32 ulEXTContentOffset;
    VOS_UINT32 ulANROffset;
    VOS_UINT32 ulFileCnt;
    VOS_UINT32 ulResult = VOS_OK;
    VOS_UINT16 *pusFileId;
    VOS_UINT8  ucADNSfi = 0;
    VOS_UINT8  ucNumberLen;
    VOS_UINT8  ucCopyLen;
    VOS_UINT8  ucExtRecord;
    VOS_UINT8  ucFreeANRRecord;

    pusFileId = &pstSPBReq->usFileNum;

    /*ANR�ļ����µ����ݸ���NV�����*/
    for(i = 0; i < gstPBConfigInfo.ucAnrMaxNum; i++)
    {
        /*��ANR�ڻ����в�����*/
        if(0 == pstPBFid->ausANRFileId[i])
        {
            continue;
        }

        /*���Type2����ANR*/
        if(PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType)
        {

            ulResult = SI_PB_UpdataType2ANR(pstRecord, pstSPBReq, pstPBFid,i,&ucFreeANRRecord);

            if(VOS_OK != ulResult)
            {
                /*����ANR����Ҫ����*/
                if(TAF_ERR_PB_NOT_FOUND == ulResult)
                {
                    continue;
                }

                PB_ERROR_LOG("SI_PB_UpdataANR:UpdataType2ANR Error");
                return ulResult;
            }

            if(VOS_OK != SI_PB_GetADNSfi(&ucADNSfi, pstPBFid->usADNFileId))
            {
                /*������*/
                PB_WARNING_LOG("SI_PB_UpdataANR: The SI_PB_GetADNSfi is not found SFI");
                return TAF_ERR_PB_STORAGE_OP_FAIL;
            }

            /*��ȡ��ǰҪ���µ��ǵڼ���Type2 ANR�ļ�*/
            ulFileCnt = (pstRecord->Index-1)/gstPBCtrlInfo.astADNInfo[0].ucRecordNum;

            /*��ȡ��Ҫ���µ�Type2 ANR��¼�ڻ����е�ƫ��*/
            ulANROffset = (ulFileCnt*(gstPBCtrlInfo.astANRInfo[0][i].ucRecordNum*gstPBCtrlInfo.astANRInfo[0][i].ucRecordLen))
                          + ((ucFreeANRRecord-1)*gstPBCtrlInfo.astANRInfo[0][i].ucRecordLen);

            /*��ȡ��Ҫ���µ�Type2 ANR��¼����չ�������Ϣ�ڻ����е�ƫ��*/
            ulEXTContentOffset = ulANROffset + (gastANRContent[i].ucRecordLen - 3);
        }
        else
        {
            /*��ȡ��ǰҪ���µ��ǵڼ���Type1 ANR�ļ�*/
            ucFreeANRRecord = pstPBFid->ucRecordNum;

            /*��ȡ��Ҫ���µ�Type1 ANR��¼�ڻ����е�ƫ��*/
            ulANROffset = (pstRecord->Index-1)*gastANRContent[i].ucRecordLen;

            /*��ȡ��Ҫ���µ�Type1 ANR��¼����չ�������Ϣ�ڻ����е�ƫ��*/
            ulEXTContentOffset = ulANROffset + (gastANRContent[i].ucRecordLen - 1);
        }

        /*lint -e534*/
        VOS_MemCpy(gstPBReqUnit.stSPBReq.aucANRContent[i],\
                &gastANRContent[i].pContent[ulANROffset],
                gastANRContent[i].ucRecordLen);
        /*lint +e534*/

        /*��ɾ������*/
        if((0 != pstRecord->AdditionNumber[i].NumberLength)
           &&(PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType))
        {
            gstPBReqUnit.stSPBReq.aucANRContent[i][gastANRContent[i].ucRecordLen-2] = ucADNSfi;/*ADN SFI*/
            gstPBReqUnit.stSPBReq.aucANRContent[i][gastANRContent[i].ucRecordLen-1] = pstPBFid->ucRecordNum;
        }

        /*��ANR��¼��2��13��12�ֽڶ�����Ϊ0xFF*/
        /*lint -e534*/
        VOS_MemSet(gstPBReqUnit.stSPBReq.aucANRContent[i]+1, (VOS_CHAR)0xFF, 12);
        /*lint +e534*/

        /*����ANR����*/
        if(0xFF == gstPBReqUnit.stSPBReq.aucANRContent[i][0])
        {
            gstPBReqUnit.stSPBReq.aucANRContent[i][0] = 0;
        }

        gstPBReqUnit.stSPBReq.aucANRContent[i][2] = pstRecord->AdditionNumber[i].NumberType;

        ucNumberLen = (pstRecord->AdditionNumber[i].NumberLength>SI_PB_NUM_LEN)?SI_PB_NUM_LEN:pstRecord->AdditionNumber[i].NumberLength;

        SI_PB_AsciiToBcd(pstRecord->AdditionNumber[i].Number, ucNumberLen,
                        &gstPBReqUnit.stSPBReq.aucANRContent[i][3],&ucCopyLen);

        gstPBReqUnit.stSPBReq.aucANRContent[i][1] = ucCopyLen + 1;

        /* ��鵱ǰ���µļ�¼�Ƿ��Ѿ�ռ����һ��EXT�ļ���¼������EXT�ļ�¼�Ų���Խ�� */

        ucExtRecord  = gastANRContent[i].pContent[ulEXTContentOffset];
        ucExtRecord = ((ucExtRecord <= gastEXTContent[PB_ADN_CONTENT].usExtTotalNum) ? (ucExtRecord) : 0xFF);

        if(pstRecord->AdditionNumber[i].NumberLength > SI_PB_NUM_LEN)
        {
            if ( VOS_NULL_PTR == gastEXTContent[PB_ADN_CONTENT].pExtContent)
            {
                /*������*/
                /*Operation not allowed*/
                PB_WARNING_LOG("SI_PB_UpdataSPBFile:ANR Ext Content NULL");
                return TAF_ERR_PB_STORAGE_OP_FAIL;
            }

            /* ���XDN��¼��Ӧ�Ѿ�������EXT��¼������Ҫȥ���ҿ��е�EXT��¼ */
            if(0xFF == ucExtRecord)
            {
                /* �ҵõ����е�EXT�ļ���¼ʱ�Ÿ���EXT�ļ����Ҳ����Ͳ����£���������Ҳ������ */
                ulResult = SI_PB_FindUnusedExtRecord( &gastEXTContent[PB_ADN_CONTENT], &ucExtRecord, (VOS_UINT8)*pusExtUsedNum);

                (*pusExtUsedNum)++;
            }

            if(VOS_OK == ulResult)
            {
                /*lint -e534*/
                VOS_MemSet(gstPBReqUnit.stSPBReq.aucANRExtContent[i], (VOS_CHAR)0xFF, SI_PB_EXT_LEN);
                /*lint +e534*/

                SI_PB_AsciiToBcd(pstRecord->AdditionNumber[i].Number + SI_PB_NUM_LEN, \
                                    (VOS_UINT8)(pstRecord->AdditionNumber[i].NumberLength - SI_PB_NUM_LEN),\
                                    &gstPBReqUnit.stSPBReq.aucANRExtContent[i][2], &ucCopyLen);

                gstPBReqUnit.stSPBReq.usANRExtIndex[i] = ucExtRecord;
                gstPBReqUnit.stSPBReq.aucANRExtContent[i][0] = SI_PB_ADDITIONAL_NUM;
                gstPBReqUnit.stSPBReq.aucANRExtContent[i][1] = ucCopyLen;
                gstPBReqUnit.stSPBReq.aucANRContent[i][gastANRContent[i].ucRecordLen
                - ((PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType)?3:1)] = ucExtRecord;

                /*��¼�����µ�EXT��¼��Ϣ*/
                pstSPBReq->usFileID[*pusFileId]  = pstPBFid->usExtFileId;
                pstSPBReq->usDataLen[*pusFileId] = SI_PB_EXT_LEN;
                pstSPBReq->ucRecordNum[*pusFileId] = ucExtRecord;
                pstSPBReq->pContent[*pusFileId] = gstPBReqUnit.stSPBReq.aucANRExtContent[i];
                pstSPBReq->usFileNum++;
            }
            else
            {
                PB_WARNING_LOG("SI_PB_UpdataSPBFile:ANR Ext Buffer Full");
                return TAF_ERR_PB_STORAGE_FULL;
            }
        }
        else
        {
            /*��������ļ�ʱ���볤��С��20��������Ҫ��EXT����ɾ��*/
            if((0xFF != ucExtRecord)&&(0xFFFF != pstPBFid->usExtFileId))
            {
                /*lint -e534*/
                VOS_MemSet(gstPBReqUnit.stSPBReq.aucANRExtContent[i], (VOS_CHAR)0xFF, SI_PB_EXT_LEN);
                /*lint +e534*/

                gstPBReqUnit.stSPBReq.aucANRExtContent[i][0] = 0;
                gstPBReqUnit.stSPBReq.usANRExtIndex[i] = ucExtRecord;

                pstSPBReq->usFileID[*pusFileId]  = pstPBFid->usExtFileId;
                pstSPBReq->usDataLen[*pusFileId] = SI_PB_EXT_LEN;
                pstSPBReq->ucRecordNum[*pusFileId] = ucExtRecord;
                pstSPBReq->pContent[*pusFileId] = gstPBReqUnit.stSPBReq.aucANRExtContent[i];
                (*pusFileId)++;
            }

            gstPBReqUnit.stSPBReq.aucANRContent[i][gastANRContent[i].ucRecordLen
                - ((PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType)?3:1)] = 0xFF;
        }

        /*��¼�����µ�ANR��¼��Ϣ*/
        pstSPBReq->usFileID[*pusFileId]  = pstPBFid->ausANRFileId[i];
        pstSPBReq->ucRecordNum[*pusFileId] = ucFreeANRRecord;
        pstSPBReq->usDataLen[*pusFileId] = gastANRContent[i].ucRecordLen;
        pstSPBReq->pContent[*pusFileId] = gstPBReqUnit.stSPBReq.aucANRContent[i];
        (*pusFileId)++;
    }

    return VOS_OK;
}
VOS_UINT32 SI_PB_UpdataEML(SI_PB_RECORD_STRU        *pstRecord,
                                    SI_PB_SPBDATA_STRU       *pstSPBReq,
                                    SI_PB_SPB_UPDATE_STRU    *pstPBFid)
{
    VOS_UINT32 ulType2EMLOffset;
    VOS_UINT16 *pusFileId;
    VOS_UINT8  ucADNSfi;
    VOS_UINT8  ucCopyLen;
    VOS_UINT8  ucFreeEMLRecord;

    /*Email�ļ�����*/
    if(0 == pstPBFid->usEMLFileId)
    {
        if(0 == pstRecord->Email.EmailLen)
        {
            PB_NORMAL_LOG("SI_PB_UpdataEML:Needn't to Update EML");
            return VOS_OK;
        }
        else
        {
            PB_WARNING_LOG("SI_PB_UpdataEML:No Email Storage");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }
    }

    pusFileId = &pstSPBReq->usFileNum;

    if(VOS_NULL_PTR == gstEMLContent.pContent)
    {
        PB_WARNING_LOG("SI_PB_UpdataEML:Email Content NULL");
        return TAF_ERR_PB_STORAGE_OP_FAIL;
    }

    /*lint -e534*/
    VOS_MemSet(gstPBReqUnit.stSPBReq.aucEMLContent, (VOS_CHAR)0xFF, gstEMLContent.ucRecordLen);
    /*lint +e534*/

    if(PB_FILE_TYPE2 == gstPBCtrlInfo.astEMLInfo[0].enEMLType)/*Type2*/
    {
        if(VOS_NULL_PTR == gstIAPContent.pIAPContent)
        {
            PB_WARNING_LOG("SI_PB_UpdataEML:IAP Content NULL");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        ulType2EMLOffset = ((pstRecord->Index-1)*gstIAPContent.ucRecordLen)
                + (gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum - 1);

        /*�����IAP�ļ����ݲ���Э�鵼�µ��쳣*/
        if(0 == gstIAPContent.pIAPContent[ulType2EMLOffset])
        {
            gstIAPContent.pIAPContent[ulType2EMLOffset] = 0xFF;
        }

        if((0xFF == gstIAPContent.pIAPContent[ulType2EMLOffset])
            &&(0 != pstRecord->Email.EmailLen))
        {
            if(VOS_OK != SI_PB_GetFreeEMLRecordNum(pstPBFid->usEMLFileId,
                         &ucFreeEMLRecord,&pstSPBReq->usFileID[*pusFileId]))
            {
                PB_WARNING_LOG("SI_PB_UpdataEML:No Free Email Record");
                return TAF_ERR_PB_STORAGE_OP_FAIL;
            }


            /*�������е�IAP�ļ�*/
            if(20 < gstIAPContent.ucRecordLen)
            {
                PB_ERROR_LOG("SI_PB_UpdataEML:IAP ucRecordLen too long");

                return TAF_ERR_PB_STORAGE_OP_FAIL;
            }

            /*lint -e534*/
            VOS_MemCpy(gstPBReqUnit.stSPBReq.aucIAPContent,
                        &gstIAPContent.pIAPContent[(pstRecord->Index-1)*gstIAPContent.ucRecordLen], gstIAPContent.ucRecordLen);
            /*lint +e534*/

            gstPBReqUnit.stSPBReq.aucIAPContent[gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum-1] =
                 ucFreeEMLRecord;

            /*�������ANRҲΪType2���ͣ����¿�������ʱ���ݲ���ȷ����ʱ����IAP���棬*/
            gstIAPContent.pIAPContent[ulType2EMLOffset] = ucFreeEMLRecord;

            pstSPBReq->ucRecordNum[*pusFileId] = pstPBFid->ucRecordNum;
            pstSPBReq->usDataLen[*pusFileId] = gstIAPContent.ucRecordLen;
            pstSPBReq->pContent[*pusFileId] = gstPBReqUnit.stSPBReq.aucIAPContent;

            (*pusFileId)++;
        }
        else if((0xFF == gstIAPContent.pIAPContent[ulType2EMLOffset])
            &&(0 == pstRecord->Email.EmailLen))
        {
            PB_INFO1_LOG("SI_PB_UpdataEML:The Email is Null or Email Len is %d", (long)pstRecord->Email.EmailLen);
            return VOS_OK;
        }
        /*Email��Ϊ�գ���Ҫɾ��IAP�ж�Ӧ��ϵ*/
        else if((0xFF != gstIAPContent.pIAPContent[ulType2EMLOffset])
            &&(0 == pstRecord->Email.EmailLen))
        {
            ucFreeEMLRecord = gstIAPContent.pIAPContent[ulType2EMLOffset];

            /*�������е�IAP�ļ�*/
            if(20 < gstIAPContent.ucRecordLen)
            {
                PB_ERROR_LOG("SI_PB_UpdataEML:IAP ucRecordLen too long");
                return TAF_ERR_PB_STORAGE_OP_FAIL;
            }

            /*lint -e534*/
            VOS_MemCpy(gstPBReqUnit.stSPBReq.aucIAPContent,
                        &gstIAPContent.pIAPContent[(pstRecord->Index-1)*gstIAPContent.ucRecordLen], gstIAPContent.ucRecordLen);

            SI_PB_GetIAPFidFromEML(pstPBFid->usEMLFileId,&pstSPBReq->usFileID[*pusFileId]);
            /*lint +e534*/

            gstPBReqUnit.stSPBReq.aucIAPContent[gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum-1] = 0xFF;

            /*�������ANRҲΪType2���ͣ����¿�������ʱ���ݲ���ȷ����ʱ����IAP���棬*/
            gstIAPContent.pIAPContent[ulType2EMLOffset] = 0xFF;

            pstSPBReq->ucRecordNum[*pusFileId] = pstPBFid->ucRecordNum;
            pstSPBReq->usDataLen[*pusFileId] = gstIAPContent.ucRecordLen;
            pstSPBReq->pContent[*pusFileId] = gstPBReqUnit.stSPBReq.aucIAPContent;

            (*pusFileId)++;
        }
        else
        {
            ucFreeEMLRecord = gstIAPContent.pIAPContent[ulType2EMLOffset];
        }

        pstSPBReq->ucRecordNum[*pusFileId] = ucFreeEMLRecord;

        if(VOS_OK != SI_PB_GetADNSfi(&ucADNSfi, pstPBFid->usADNFileId))
        {
            /*������*/
            PB_ERROR_LOG("SI_PB_UpdataEML:IAP ucRecordLen too long");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        /*��ɾ������*/
        if(0 != pstRecord->Email.EmailLen)
        {
            gstPBReqUnit.stSPBReq.aucEMLContent[gstEMLContent.ucRecordLen-2] = ucADNSfi;/*ADN SFI*/
            gstPBReqUnit.stSPBReq.aucEMLContent[gstEMLContent.ucRecordLen-1] = pstPBFid->ucRecordNum;
        }
    }
    else
    {
        pstSPBReq->ucRecordNum[*pusFileId] = pstPBFid->ucRecordNum;
    }

    ucCopyLen = ((VOS_UINT8)pstRecord->Email.EmailLen > gstEMLContent.ucDataLen)?gstEMLContent.ucDataLen:(VOS_UINT8)pstRecord->Email.EmailLen;

    if(SI_PB_ALPHATAG_TRANSFER_TAG == pstRecord->Email.Email[ucCopyLen - 1])
    {
        pstRecord->Email.Email[ucCopyLen - 1] = 0xFF;
    }

    /*lint -e534*/
    VOS_MemCpy(gstPBReqUnit.stSPBReq.aucEMLContent, pstRecord->Email.Email, ucCopyLen);
    /*lint +e534*/

    pstSPBReq->usDataLen[*pusFileId] = gstEMLContent.ucRecordLen;
    pstSPBReq->usFileID[*pusFileId] = pstPBFid->usEMLFileId;
    pstSPBReq->pContent[*pusFileId] = gstPBReqUnit.stSPBReq.aucEMLContent;

    (*pusFileId)++;

    return VOS_OK;
}
VOS_UINT32 SI_PB_UpdataSPBFile(SI_PB_SPB_UPDATE_STRU *pstPBFid,
                                        SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32            ulResult = VOS_OK;
    VOS_UINT16            usExtUsedNum = 1;
    SI_PB_SPBDATA_STRU    stSPBReq;/*���Ÿ��ļ�*/

    /*lint -e534*/
    VOS_MemSet((VOS_VOID*)(&stSPBReq), 0, sizeof(SI_PB_SPBDATA_STRU));
    /*lint +e534*/

    /*����Email�ļ�,����NV���ֵΪ�ж��Ƿ���Ը���*/
    if(gstPBConfigInfo.ucEmailFlag)
    {
        ulResult = SI_PB_UpdataEML(pstRecord,&stSPBReq,pstPBFid);

        if(VOS_OK != ulResult)
        {
            PB_WARNING_LOG("SI_PB_UpdataSPBFile:Update Email Fail");
            return ulResult;
        }
    }

    /*����ANR�ļ�*/
    ulResult = SI_PB_UpdataANR(pstRecord,&stSPBReq,&usExtUsedNum,pstPBFid);

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_UpdataSPBFile:Update ANR Fail");
        return ulResult;
    }

    /*����ADN�ļ�*/
    ulResult = SI_PB_UpdataADN(pstRecord,&stSPBReq,&usExtUsedNum,pstPBFid);

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_UpdataSPBFile:Update ADN Fail");
        return ulResult;
    }

    /*����USIMM�ӿڸ����ļ�*/
    if (VOS_OK != SI_PB_SetSPBFileReq(&stSPBReq))
    {
        PB_WARNING_LOG("SI_PB_UpdataSPBFile: SI_PB_SetSPBFileReq Fail");
        return TAF_ERR_USIM_SIM_CARD_NOTEXIST;/*SIM Fail*/
    }

    return VOS_OK;
}



VOS_VOID SI_PB_DeleteHandleAnr(VOS_UINT16          usFileId,
                                        VOS_UINT16          usIndex,
                                        SI_PB_SPBDATA_STRU *pstSPBReq,
                                        VOS_UINT8           ucRecord)
{
    VOS_UINT32            i;
    VOS_UINT8             ucExtRecord;
    VOS_UINT8             ucANRRecord;
    VOS_UINT16            usANRFileId = 0;
    VOS_UINT32            ulRecordOffset;
    VOS_UINT32            ulType2ANRFileCnt;
    VOS_UINT32            ulXDNContentOffset;
    VOS_UINT8             aucContent[20]; /*ɾ����������ȫF*/

    SI_PB_MemSet(sizeof(aucContent), 0xFF, aucContent);/*��ʼ���ֲ�����*/

    for(i = 0; i < SI_PB_ANR_MAX; i++)
    {
        /*����ADN FID��ANR�绰����Ż�ȡ��Ҫɾ����ANR�绰��FID*/
        /*lint -e534*/
        SI_PB_GetANRFidFromADN((VOS_UINT8)i,usFileId,&usANRFileId);
        /*lint +e534*/

        if(0 == usANRFileId)/*��ANR�绰��������*/
        {
            continue;
        }

        /*Type2 ���� ANR����*/
        if(PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType)
        {
            ucANRRecord = gstIAPContent.pIAPContent[((usIndex-1)*gstIAPContent.ucRecordLen)
                            + (gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1)];

            /*����ANR��Ч��ɾ����һ��*/
            if(0xFF == ucANRRecord)
            {
                continue;
            }

            /*lint -e534*/
            VOS_MemCpy(gstPBReqUnit.stSPBReq.aucIAPContent,
            &gstIAPContent.pIAPContent[(usIndex-1)*gstIAPContent.ucRecordLen], gstIAPContent.ucRecordLen);
            /*lint +e534*/

            /*�������е�IAP�ļ�*/
            gstPBReqUnit.stSPBReq.aucIAPContent[gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1] = 0xFF;

            /*��ʱ���»��棬��ֹEmailҲΪType2���ͣ��Ӷ����¿����Ļ������ݲ���ȷ*/
            gstIAPContent.pIAPContent[((usIndex-1)*gstIAPContent.ucRecordLen)
                                + (gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1)] = 0xFF;

            /*lint -e534*/
            SI_PB_GetIAPFidFromANR(usANRFileId,&pstSPBReq->usFileID[pstSPBReq->usFileNum]);
            /*lint +e534*/

            pstSPBReq->ucRecordNum[pstSPBReq->usFileNum] = ucRecord;
            pstSPBReq->usDataLen[pstSPBReq->usFileNum] = gstIAPContent.ucRecordLen;
            pstSPBReq->pContent[pstSPBReq->usFileNum] = gstPBReqUnit.stSPBReq.aucIAPContent;

            pstSPBReq->usFileNum++;

            /*����ANR��EXT����*/
            ulType2ANRFileCnt = (usIndex -1)/gstPBCtrlInfo.astADNInfo[0].ucRecordNum;

            ulRecordOffset =  (ulType2ANRFileCnt*(gstPBCtrlInfo.astANRInfo[0][i].ucRecordNum*gastANRContent[i].ucRecordLen))
                                + ((ucANRRecord-1)*gastANRContent[i].ucRecordLen);

            ulXDNContentOffset = gastANRContent[i].ucRecordLen - 3;
        }
        else
        {
            ucANRRecord = ucRecord;

            /*����ANR��EXT����*/
            ulRecordOffset = (usIndex -1) * gastANRContent[i].ucRecordLen;

            ulXDNContentOffset = gastANRContent[i].ucRecordLen - 1;
        }

        /* �ж�ANR�ļ������Ƿ�Ϊ�� */
        if (VOS_NULL_PTR == gastANRContent[i].pContent)
        {
            continue;
        }

        /*��鵱ǰ���µļ�¼�Ƿ��Ѿ�ռ����һ��EXT�ļ���¼*/
        ucExtRecord  = gastANRContent[i].pContent[ulRecordOffset+ulXDNContentOffset];

        /*�����ɾ����ANR���������չ���룬������Ҫ��EXT����ɾ������EXT�ļ�¼�Ų���Խ�磬����EXT�����ֵ*/
        if ( (ucExtRecord <= gastEXTContent[PB_ADN_CONTENT].usExtTotalNum)
            && (0xFF != ucExtRecord) )
        {
            /*lint -e534*/
            VOS_MemCpy(gstPBReqUnit.stSPBReq.aucANRExtContent[i], aucContent, SI_PB_EXT_LEN);
            /*lint +e534*/

            gstPBReqUnit.stSPBReq.aucANRExtContent[i][0] = 0;

            gstPBReqUnit.stSPBReq.usANRExtIndex[i] = ucExtRecord;

            pstSPBReq->usFileID[pstSPBReq->usFileNum]       = gastEXTContent[PB_ADN_CONTENT].usExtFileId;
            pstSPBReq->usDataLen[pstSPBReq->usFileNum]      = SI_PB_EXT_LEN;
            pstSPBReq->ucRecordNum[pstSPBReq->usFileNum]    = ucExtRecord;
            pstSPBReq->pContent[pstSPBReq->usFileNum]       = gstPBReqUnit.stSPBReq.aucANRExtContent[i];
            pstSPBReq->usFileNum++;
        }

        /*ANR��¼��Ч��������ɾ���б�*/
        if(VOS_OK == SI_PB_CheckANRValidity(gastANRContent[i].pContent+ulRecordOffset))
        {
            /*lint -e534*/
            VOS_MemCpy(gstPBReqUnit.stSPBReq.aucANRContent[i], aucContent, gastANRContent[i].ucRecordLen);
            /*lint +e534*/

            /*��¼��ɾ����ANR��¼��Ϣ*/
            pstSPBReq->usFileID[pstSPBReq->usFileNum]       = usANRFileId;
            pstSPBReq->ucRecordNum[pstSPBReq->usFileNum]    = ucANRRecord;
            pstSPBReq->usDataLen[pstSPBReq->usFileNum]      = gastANRContent[i].ucRecordLen;
            pstSPBReq->pContent[pstSPBReq->usFileNum]       = gstPBReqUnit.stSPBReq.aucANRContent[i];
            pstSPBReq->usFileNum++;
        }
    }
}

VOS_VOID SI_PB_DeleteHandleEmail(VOS_UINT16         usIndex,
                                          SI_PB_SPBDATA_STRU *pstSPBReq,
                                          VOS_UINT8           ucRecord,
                                          VOS_UINT16          usFileId)
{
    VOS_UINT16            usEMLFileId = 0;
    VOS_UINT16            usIAPFileid = 0;
    VOS_UINT32            ulType2EMLIndex;
    VOS_UINT8             ucEMLRecord;
    VOS_UINT8             *pucEMLContent = VOS_NULL_PTR;
    VOS_UINT8             aucContent[64]; /*ɾ����������ȫF*/

    SI_PB_MemSet(sizeof(aucContent), 0xFF, aucContent);/*��ʼ���ֲ�����*/

    /*lint -e534*/
    SI_PB_GetEMLFIdFromADN(&usEMLFileId, usFileId);
    /*lint +e534*/

    if(0 == usEMLFileId)
    {
        PB_NORMAL_LOG("SI_PB_DeleteHandleEmail:No Email");
        return;
    }

    if(PB_FILE_TYPE2 == gstPBCtrlInfo.astEMLInfo[0].enEMLType)
    {
        ulType2EMLIndex = (usIndex-1)*gstIAPContent.ucRecordLen;

        ucEMLRecord = gstIAPContent.pIAPContent[ulType2EMLIndex+(gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum-1)];

        if((0xFF == ucEMLRecord)||(0x00 == ucEMLRecord))
        {
            return;
        }

        /*����Refresh MEM���� */

        /*�������е�IAP�ļ�*/
        if(20 < gstIAPContent.ucRecordLen)
        {
            PB_ERROR_LOG("SI_PB_DeleteHandleEmail:IAP ucRecordLen too long");

            return;
        }

        /*lint -e534*/
        VOS_MemCpy(gstPBReqUnit.stSPBReq.aucIAPContent,
        &gstIAPContent.pIAPContent[ulType2EMLIndex], gstIAPContent.ucRecordLen);
        /*lint +e534*/

        gstPBReqUnit.stSPBReq.aucIAPContent[gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum-1] = 0xFF;

        /*��ʱ���»��棬��ֹEmail��ANRɾ��˳��仯�󣬿����Ļ������ݲ���ȷ*/
        gstIAPContent.pIAPContent[ulType2EMLIndex+(gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum-1)] = 0xFF;

        /*lint -e534*/
        SI_PB_GetIAPFidFromEML(usEMLFileId,&usIAPFileid);
        /*lint +e534*/

        pstSPBReq->ucRecordNum[pstSPBReq->usFileNum] = ucRecord;
        pstSPBReq->usFileID[pstSPBReq->usFileNum]   = usIAPFileid;
        pstSPBReq->usDataLen[pstSPBReq->usFileNum] = gstIAPContent.ucRecordLen;
        pstSPBReq->pContent[pstSPBReq->usFileNum] = gstPBReqUnit.stSPBReq.aucIAPContent;

        pstSPBReq->usFileNum++;
    }
    else
    {
        ucEMLRecord = ucRecord;
    }

    if(VOS_OK != SI_PB_GetEMLRecord(&pucEMLContent, usEMLFileId, ucEMLRecord))
    {
        PB_NORMAL_LOG("SI_PB_DeleteHandleEmail:Search Email Storge Fail");
        return;
    }

    if(0xFF != pucEMLContent[0])/*��ЧEmail*/
    {
        /*lint -e534*/
        VOS_MemCpy(gstPBReqUnit.stSPBReq.aucEMLContent, aucContent, gstEMLContent.ucRecordLen);
        /*lint +e534*/

        /*��¼��ɾ����EML��¼��Ϣ*/
        pstSPBReq->usFileID[pstSPBReq->usFileNum]       = usEMLFileId;
        pstSPBReq->ucRecordNum[pstSPBReq->usFileNum]    = ucEMLRecord;
        pstSPBReq->usDataLen[pstSPBReq->usFileNum]      = gstEMLContent.ucRecordLen;
        pstSPBReq->pContent[pstSPBReq->usFileNum]       = gstPBReqUnit.stSPBReq.aucEMLContent;
        pstSPBReq->usFileNum++;
    }

    return;
}
VOS_UINT32 SI_PB_DeleteHandle(VOS_UINT16 usFileId, VOS_UINT8 ucRecord,
                                      VOS_UINT8 ucOffset,VOS_UINT16 usIndex)
{
    VOS_UINT16            usExtFileId;
    VOS_UINT8             ucExtRecord;
    VOS_UINT32            ulExtInfoNum;
    VOS_UINT8             *pucRecord;
    VOS_UINT8             ucRecordLen;
    VOS_UINT32            ulRecordOffset;
    VOS_UINT32            ulResult = VOS_OK;
    SI_PB_SPBDATA_STRU    stSPBReq;/*���Ÿ��ļ�*/
    VOS_UINT8             aucContent[242]; /*ɾ����������ȫF*/

    SI_PB_MemSet(sizeof(aucContent), 0xFF, aucContent);/*��ʼ���ֲ�����*/

    /*lint -e534*/
    VOS_MemSet((VOS_VOID*)(&stSPBReq), 0, sizeof(SI_PB_SPBDATA_STRU));
    /*lint +e534*/

    /*XDN �� EXT����*/
    ucRecordLen = gastPBContent[ucOffset].ucRecordLen;
    ulRecordOffset = (usIndex -1) * ucRecordLen;
    pucRecord = gastPBContent[ucOffset].pContent + ulRecordOffset;

    /*���ڸ��ϵ绰������£�����ADNΪ��Чֵ*/
    if((1 == gstPBConfigInfo.ucSPBFlag)&&(PB_ADN_CONTENT == ucOffset))
    {
        /*ANR �� EXT����*/
        SI_PB_DeleteHandleAnr(usFileId, usIndex, &stSPBReq, ucRecord);

        /*Email ����*/
        SI_PB_DeleteHandleEmail(usIndex, &stSPBReq, ucRecord, usFileId);

        ulResult = SI_PB_CheckContentValidity(&gastPBContent[ucOffset], pucRecord);
    }

    ucExtRecord  = ((ucOffset == PB_BDN_CONTENT)?pucRecord[ucRecordLen - 2]:pucRecord[ucRecordLen - 1]);
    ulExtInfoNum = gastPBContent[ucOffset].ulExtInfoNum;
    usExtFileId  = gastEXTContent[ulExtInfoNum].usExtFileId;

    if((ucExtRecord <= gastEXTContent[ulExtInfoNum].usExtTotalNum)
        &&(0xFF != ucExtRecord )&&(0 != ucExtRecord)&&(0xFFFF != usExtFileId))
    {
        gstPBReqUnit.usExtIndex = ucExtRecord;
        /*lint -e534*/
        VOS_MemCpy(gstPBReqUnit.aucEXTContent, aucContent, SI_PB_EXT_LEN);
        /*lint +e534*/
        gstPBReqUnit.aucEXTContent[0] = 0;

        stSPBReq.usFileID[stSPBReq.usFileNum]  = usExtFileId;
        stSPBReq.usDataLen[stSPBReq.usFileNum] = SI_PB_EXT_LEN;
        stSPBReq.ucRecordNum[stSPBReq.usFileNum] = ucExtRecord;
        stSPBReq.pContent[stSPBReq.usFileNum] = gstPBReqUnit.aucEXTContent;
        stSPBReq.usFileNum++;
    }

    /*�ڼ�¼��Чʱ�ŷ����ɾ���ļ��б�*/
    if(VOS_OK == ulResult)
    {
        /*lint -e534*/
        VOS_MemCpy(gstPBReqUnit.aucXDNContent, aucContent, ucRecordLen);
        /*lint +e534*/

        stSPBReq.usFileID[stSPBReq.usFileNum]  = usFileId;
        stSPBReq.usDataLen[stSPBReq.usFileNum] = ucRecordLen;
        stSPBReq.ucRecordNum[stSPBReq.usFileNum] = ucRecord;
        stSPBReq.pContent[stSPBReq.usFileNum] = gstPBReqUnit.aucXDNContent;
        stSPBReq.usFileNum++;
    }

    /*����USIMM�ӿڸ����ļ�*/
    if (VOS_OK != SI_PB_SetSPBFileReq(&stSPBReq))
    {
        return TAF_ERR_USIM_SIM_CARD_NOTEXIST;/*SIM Fail*/
    }

    return VOS_OK;
}


VOS_UINT32 SI_PB_QueryProc(PBMsgBlock *pMsg)
{
    SI_PB_QUERY_REQ_STRU *pstMsg;
    SI_PB_EVENT_INFO_STRU stCnfData;
    VOS_UINT32            ulResult;
    VOS_UINT8             ucPBOffset;
    VOS_UINT16            usUsedNum;

    pstMsg = (SI_PB_QUERY_REQ_STRU*)pMsg;

    /*lint -e534*/
    VOS_MemSet(&stCnfData, 0, sizeof(SI_PB_EVENT_INFO_STRU));/*��ʼ����ǰ�ľֲ�����*/
    /*lint +e534*/

    ulResult = SI_PB_FindPBOffset(pstMsg->ulStorage, &ucPBOffset);/*��λ��ǰ�绰��λ��*/

    stCnfData.ClientId          = pstMsg->usClient;        /*������Ϣ�������ظ�����*/
    stCnfData.OpId              = pstMsg->ucOpID;
    stCnfData.PBEventType       = SI_PB_EVENT_QUERY_CNF;
    stCnfData.Storage           = pstMsg->ulStorage;

    if ( TAF_ERR_NO_ERROR != ulResult )
    {
        PB_WARNING_LOG("SI_PB_QUERYProc: Find the PhoneBook Content is Error");

        stCnfData.PBError = TAF_ERR_PB_NOT_FOUND;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    stCnfData.PBError = SI_PB_ErrorProc();

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*�����λʧ�ܻ��߻������ݲ�����*/
    {
        PB_WARNING_LOG("SI_PB_QUERYProc: Proc Error");

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    if( PB_INIT_FINISHED != gstPBInitState.enPBInitStep )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    if(PB_INITIALISED != gastPBContent[ucPBOffset].enInitialState)
    {
        PB_WARNING_LOG("SI_PB_QueryProc: Not Init.");

        stCnfData.PBError = TAF_ERR_SIM_BUSY;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    if(PB_ADN_CONTENT == ucPBOffset)
    {
        usUsedNum = (VOS_UINT16)gstPBCtrlInfo.ulTotalUsed;
    }
    else
    {
        usUsedNum = gastPBContent[ucPBOffset].usUsedNum;
    }

    stCnfData.PBEvent.PBQueryCnf.InUsedNum    = usUsedNum;
    stCnfData.PBEvent.PBQueryCnf.TotalNum     = gastPBContent[ucPBOffset].usTotalNum;
    stCnfData.PBEvent.PBQueryCnf.TextLen      = gastPBContent[ucPBOffset].ucNameLen;
    stCnfData.PBEvent.PBQueryCnf.NumLen       = gastPBContent[ucPBOffset].ucNumberLen;
    stCnfData.PBEvent.PBQueryCnf.EMAILTextLen = gstEMLContent.ucDataLen;
    stCnfData.PBEvent.PBQueryCnf.ANRNumberLen = gastANRContent[0].ucNumberLen;

    return SI_PBCallback(&stCnfData);/*���ûص�����*/
}
VOS_VOID SI_PB_SendSetCurPB(VOS_VOID)
{
    SI_PB_SETPB_IND_STRU *pstMsg;

    pstMsg = (SI_PB_SETPB_IND_STRU*)VOS_AllocMsg(MAPS_PB_PID,
                                sizeof(SI_PB_SETPB_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)  /*�����ڴ�ʧ�ܻ�����*/
    {
        return;
    }

    pstMsg->ulReceiverPid = ACPU_PID_PB;
    pstMsg->ulMsgName     = SI_PB_UPDATE_CURPB;
    pstMsg->enPBCurType   = gstPBCtrlInfo.enPBCurType; /* ��ǰȫ�ֱ��������Ѿ����� */

    if(VOS_OK != VOS_SendMsg(MAPS_PB_PID, pstMsg))
    {
        PB_ERROR_LOG("SI_PB_SendSetCurPB: Send msg Error");
    }

    return;
}


VOS_UINT32 SI_PB_SetProc(PBMsgBlock *pMsg)
{
    SI_PB_SET_REQ_STRU    *pstMsg;
    SI_PB_EVENT_INFO_STRU stCnfData;
    VOS_UINT32            ulResult;
    VOS_UINT8             ucPBOffset;

    pstMsg = (SI_PB_SET_REQ_STRU*)pMsg;

    /*lint -e534*/
    VOS_MemSet(&stCnfData, 0, sizeof(SI_PB_EVENT_INFO_STRU));/*��ʼ���ֲ�����*/
    /*lint +e534*/

    stCnfData.ClientId          = pstMsg->usClient;        /*������Ϣ�������ظ�����*/
    stCnfData.OpId              = pstMsg->ucOpID;
    stCnfData.PBEventType       = SI_PB_EVENT_SET_CNF;
    stCnfData.Storage           = pstMsg->ulStorage;

    ulResult = SI_PB_FindPBOffset(stCnfData.Storage, &ucPBOffset);

    if(VOS_OK != ulResult)
    {
        stCnfData.PBError = TAF_ERR_PARA_ERROR;

        PB_WARNING_LOG("SI_PB_SetProc: Find the PhoneBook Content is Error");

        return SI_PBCallback(&stCnfData);                   /*���ûص�����*/
    }

    stCnfData.PBError = SI_PB_ErrorProc();

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*�����λʧ�ܻ��߻������ݲ�����*/
    {
        PB_WARNING_LOG("SI_PB_SetProc: Proc Error");

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    if( PB_INIT_FINISHED != gstPBInitState.enPBInitStep )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    if(PB_INITIALISED != gastPBContent[ucPBOffset].enInitialState)
    {
        PB_WARNING_LOG("SI_PB_SetProc: Not Init.");

        stCnfData.PBError = TAF_ERR_SIM_BUSY;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    stCnfData.PBEvent.PBSetCnf.InUsedNum      = gastPBContent[ucPBOffset].usUsedNum;
    stCnfData.PBEvent.PBSetCnf.TotalNum       = gastPBContent[ucPBOffset].usTotalNum;
    stCnfData.PBEvent.PBSetCnf.TextLen        = gastPBContent[ucPBOffset].ucNameLen;
    stCnfData.PBEvent.PBSetCnf.NumLen         = gastPBContent[ucPBOffset].ucNumberLen;
    stCnfData.PBEvent.PBSetCnf.ANRNumberLen   = gastANRContent[0].ucNumberLen;
    stCnfData.PBEvent.PBQueryCnf.EMAILTextLen = gstEMLContent.ucDataLen;

    gstPBCtrlInfo.enPBCurType = pstMsg->ulStorage;      /*���õ�ǰȫ�ֱ�������*/

    SI_PB_SendSetCurPB();

    return SI_PBCallback(&stCnfData);                   /*���ûص�����*/
}
VOS_UINT32 SI_PB_FindFreeIndex(VOS_UINT8 ucPBOffset, VOS_UINT16 *pusIndex)
{
    VOS_UINT16 i;

    for(i=1; i<=gastPBContent[ucPBOffset].usTotalNum; i++)/*���ݵ�ǰ����������ѯ�ռ�¼*/
    {
        if(SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBOffset].pIndex, i))
        {
            break;
        }
    }

    if(i > gastPBContent[ucPBOffset].usTotalNum) /*����ȫ��*/
    {
        return TAF_ERR_PB_STORAGE_FULL;/*���ûص�����*/
    }

    *pusIndex = i;

    return VOS_OK;
}
VOS_UINT32 SI_PB_AddProc(PBMsgBlock *pMsg)
{
    SI_PB_ADD_REP_STRU    *pstMsg;
    SI_PB_EVENT_INFO_STRU stCnfData;
    VOS_UINT32            ulResult;
    VOS_UINT16            usFileId;
    VOS_UINT16            usExtFileId = 0xFFFF;
    VOS_UINT8             ucRecord;
    VOS_UINT8             ucPBOffset;
    VOS_UINT16            i;
    VOS_UINT32            ulExtInfoNum;

    pstMsg = (SI_PB_ADD_REP_STRU *)pMsg;

    /*lint -e534*/
    VOS_MemSet(&stCnfData, 0, sizeof(SI_PB_EVENT_INFO_STRU));/*��ʼ���ֲ�����*/
    /*lint +e534*/

    stCnfData.ClientId      = pstMsg->usClient;    /*������Ϣ���ظ�����*/
    stCnfData.OpId          = pstMsg->ucOpID;
    stCnfData.PBEventType   = SI_PB_EVENT_ADD_CNF;
    stCnfData.Storage       = pstMsg->ulStorage;

    stCnfData.PBError = SI_PB_ErrorProc();

    if( ( TAF_ERR_NO_ERROR == stCnfData.PBError )
        && ( PB_INIT_FINISHED != gstPBInitState.enPBInitStep ) )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;
    }

    /*�������к��벻�ܸ���*/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((PB_ECC == pstMsg->ulStorage)
     || (PB_XECC == pstMsg->ulStorage))
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
    }
#else
    if (PB_ECC == pstMsg->ulStorage)
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
    }
#endif

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*�����λʧ�ܻ��߻������ݲ�����*/
    {
        PB_WARNING_LOG("SI_PB_ADDProc: Proc Error");

        return SI_PBCallback(&stCnfData);       /*���ûص�����*/
    }

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->stRecord.Index, pstMsg->stRecord.Index, &ucPBOffset);

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_ADDProc: Find the PhoneBook Content is Error");
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    if(pstMsg->stRecord.NumberLength > gastPBContent[ucPBOffset].ucNumberLen)
    {
        PB_WARNING_LOG("SI_PB_ADDProc: Number Too Long");
        stCnfData.PBError = TAF_ERR_PB_DIAL_STRING_TOO_LONG;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    if(VOS_NULL_PTR == gastPBContent[ucPBOffset].pContent)/*��λ����ʧ��*/
    {
        PB_WARNING_LOG("SI_PB_ADDProc: Content is NULL");
        stCnfData.PBError = TAF_ERR_UNSPECIFIED_ERROR;

        return SI_PBCallback(&stCnfData);       /*���ûص�����*/
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    /*�ҵ����м�¼*/
    ulResult = SI_PB_FindFreeIndex(ucPBOffset, &i);

    if(VOS_OK != ulResult)
    {
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);
    }

    if(SI_PB_STORAGE_SM == pstMsg->ulStorage)   /*�����ADN��Ҫת��Ϊ��¼��*/
    {
        ulResult = SI_PB_CountADNRecordNum(i, &usFileId, &ucRecord);
    }
    else                                                                    /*���������绰��*/
    {
        ulResult = SI_PB_GetXDNFileID(pstMsg->ulStorage, &usFileId);

        ucRecord = (VOS_UINT8)i;
    }

    if(VOS_ERR == ulResult)         /*ת�����ʧ��*/
    {
        PB_WARNING_LOG("SI_PB_ADDProc: Get the XDN File ID and Record Number is Error");

        stCnfData.PBError = TAF_ERR_PARA_ERROR;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    ulExtInfoNum = gastPBContent[ucPBOffset].ulExtInfoNum;
    usExtFileId  = gastEXTContent[ulExtInfoNum].usExtFileId;
    pstMsg->stRecord.Index  = i;

    ulResult = SI_PB_UpdataXDNFile(ucPBOffset, usFileId, usExtFileId,
                                    ucRecord, &pstMsg->stRecord);/*, (VOS_UINT32)SI_PB_ADD_REQ);���ø����ļ�API*/

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_ADDProc: SI_PB_UpdataXDNFile is Error");

        stCnfData.PBError = TAF_ERR_USIM_SIM_CARD_NOTEXIST;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    gstPBReqUnit.enPBEventType     = SI_PB_EVENT_ADD_CNF;    /*��仺��ṹ*/

    gstPBReqUnit.enPBStoateType    = pstMsg->ulStorage;

    gstPBReqUnit.ucOpID            = pstMsg->ucOpID;

    gstPBReqUnit.usClientID        = pstMsg->usClient;

    gstPBReqUnit.usIndex1          = i;

    return VOS_OK;
}
VOS_UINT32 SI_PB_GetANRInfo(SI_PB_ADDITION_NUM_STRU *pstANRNum,
                                    VOS_UINT16 usADNFid,
                                    VOS_UINT16 *pusANRFileId)
{
    VOS_UINT16 i;

    /*�ڶ��绰��������鼰FID��ȡ*/
    for(i = 0; i < gstPBConfigInfo.ucAnrMaxNum; i++)
    {
        if((0 < pstANRNum[i].NumberLength)&&(i >= gstPBCtrlInfo.ulANRStorageNum))
        {
            PB_WARNING_LOG("SI_PB_GetANRInfo:Not Allowed");

            return TAF_ERR_PB_STORAGE_OP_FAIL;/*���ûص�����*/
        }

        if(pstANRNum[i].NumberLength > gastANRContent[i].ucNumberLen)
        {
            PB_WARNING_LOG("SI_PB_GetANRInfo:Para Wrong");

            return TAF_ERR_PB_DIAL_STRING_TOO_LONG;
        }

        pusANRFileId[i] = 0;

        /*lint -e534*/
        SI_PB_GetANRFidFromADN((VOS_UINT8)i, usADNFid, &pusANRFileId[i]);/*����ADN FID��ȡANR FID*/
        /*lint +e534*/

        if((0 == pusANRFileId[i])&&(0 != pstANRNum[i].NumberLength))
        {
            PB_WARNING_LOG("SI_PB_GetANRInfo:No ANR");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }
    }

    return VOS_OK;
}
VOS_UINT32 SI_PB_SAddProc(PBMsgBlock *pMsg)
{
    SI_PB_ADD_REP_STRU    *pstMsg;
    SI_PB_EVENT_INFO_STRU stCnfData;
    VOS_UINT32            ulResult;
    VOS_UINT8             ucRecord;
    VOS_UINT8             ucPBOffset;
    VOS_UINT16            usIndex;
    VOS_UINT32            ulExtInfoNum;
    SI_PB_SPB_UPDATE_STRU stSPBFid;

    /*lint -e534*/
    VOS_MemSet(&stSPBFid, 0, sizeof(stSPBFid));
    /*lint +e534*/

    pstMsg = (SI_PB_ADD_REP_STRU *)pMsg;

    /*lint -e534*/
    VOS_MemSet(&stCnfData, 0, sizeof(SI_PB_EVENT_INFO_STRU));/*��ʼ���ֲ�����*/
    /*lint +e534*/

    stCnfData.ClientId      = pstMsg->usClient;    /*������Ϣ���ظ�����*/
    stCnfData.OpId          = pstMsg->ucOpID;
    stCnfData.PBEventType   = SI_PB_EVENT_SADD_CNF;
    stCnfData.Storage       = pstMsg->ulStorage;

    if((0 == gstPBConfigInfo.ucSPBFlag)||(SI_PB_STORAGE_SM != pstMsg->ulStorage))
    {
        /*��ΪOperation not allowed*/
        stCnfData.PBError = TAF_ERR_CMD_TYPE_ERROR;

        return SI_PBCallback(&stCnfData);
    }

    stCnfData.PBError = SI_PB_ErrorProc();

    if( ( TAF_ERR_NO_ERROR == stCnfData.PBError )
        && ( PB_INIT_FINISHED != gstPBInitState.enPBInitStep ) )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;
    }

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*�����λʧ�ܻ��߻������ݲ�����*/
    {
        PB_WARNING_LOG("SI_PB_SAddProc: Proc Error");

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->stRecord.Index, pstMsg->stRecord.Index, &ucPBOffset);

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_SAddProc: Find the PhoneBook Content is Error");
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);
    }

    if(pstMsg->stRecord.NumberLength > gastPBContent[ucPBOffset].ucNumberLen)
    {
        PB_WARNING_LOG("SI_PB_SAddProc: Number Too Long");
        stCnfData.PBError = TAF_ERR_PB_DIAL_STRING_TOO_LONG;

        return SI_PBCallback(&stCnfData);
    }

    if(VOS_NULL_PTR == gastPBContent[ucPBOffset].pContent)/*��λ����ʧ��*/
    {
        PB_WARNING_LOG("SI_PB_SAddProc: Content is NULL");
        stCnfData.PBError = TAF_ERR_UNSPECIFIED_ERROR;

        return SI_PBCallback(&stCnfData);
    }


    /*�ҵ����м�¼*/
    ulResult = SI_PB_FindFreeIndex(ucPBOffset, &usIndex);

    if(VOS_OK != ulResult)
    {
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);
    }

    /*��¼��Ҫ���µ�Index��*/
    pstMsg->stRecord.Index = usIndex;

    /*ADN�绰��FID����¼�Ż�ȡ*/
    ulResult = SI_PB_CountADNRecordNum(usIndex, &stSPBFid.usADNFileId, &ucRecord);

    if(VOS_ERR == ulResult)/*ת��ʧ��*/
    {
        PB_WARNING_LOG("SI_PB_SAddProc: Get the XDN File ID and Record Number is Error");

        stCnfData.PBError = TAF_ERR_PARA_ERROR;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    /*�ڶ��绰��������鼰ID��ȡ*/
    ulResult = SI_PB_GetANRInfo(pstMsg->stRecord.AdditionNumber,stSPBFid.usADNFileId,stSPBFid.ausANRFileId);

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_SAddProc: Get the ANR Info Fail");

        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    /*Email �ļ�FID��ȡ,����NV���ֵΪ�ж��Ƿ���Ը���*/
    if(gstPBConfigInfo.ucEmailFlag)
    {
        if(0 < pstMsg->stRecord.Email.EmailLen)
        {
            /*lint -e534*/
            SI_PB_GetEMLFIdFromADN(&stSPBFid.usEMLFileId,stSPBFid.usADNFileId);
            /*lint +e534*/

            if (0 == stSPBFid.usEMLFileId)
            {
                PB_WARNING_LOG("SI_PB_SModifyProc:No Email");

                stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;

                return SI_PBCallback(&stCnfData);
            }
        }
    }

    /*EXT �ļ�FID��ȡ*/
    ulExtInfoNum          = gastPBContent[ucPBOffset].ulExtInfoNum;
    stSPBFid.usExtFileId  = gastEXTContent[ulExtInfoNum].usExtFileId;

    gstPBReqUnit.enPBLock = PB_LOCKED;

    stSPBFid.ucRecordNum = ucRecord;

    ulResult = SI_PB_UpdataSPBFile(&stSPBFid,&pstMsg->stRecord);/*���ø����ļ���API*/

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_SAddProc: SI_PB_UpdataXDNFile is Error");

        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    gstPBReqUnit.enPBEventType     = SI_PB_EVENT_ADD_CNF;    /*��仺��ṹ*/

    gstPBReqUnit.enPBStoateType    = pstMsg->ulStorage;

    gstPBReqUnit.ucOpID            = pstMsg->ucOpID;

    gstPBReqUnit.usClientID        = pstMsg->usClient;

    gstPBReqUnit.usIndex1          = usIndex;

    return VOS_OK;
}


VOS_UINT32 SI_PB_ModifyProc(PBMsgBlock *pMsg)
{
    SI_PB_ADD_REP_STRU     *pstMsg;
    SI_PB_EVENT_INFO_STRU  stCnfData;
    VOS_UINT32             ulResult;
    VOS_UINT16             usFileId;
    VOS_UINT16             usExtFileId = 0xFFFF;
    VOS_UINT8              ucRecord;
    VOS_UINT8              ucPBOffset;
    VOS_UINT32             ulExtInfoNum;

    pstMsg = (SI_PB_ADD_REP_STRU *)pMsg;

    /*lint -e534*/
    VOS_MemSet(&stCnfData, 0, sizeof(SI_PB_EVENT_INFO_STRU));/*��ʼ���ֲ�����*/
    /*lint +e534*/

    stCnfData.ClientId     = pstMsg->usClient;    /*������Ϣ���ظ�����*/
    stCnfData.OpId         = pstMsg->ucOpID;
    stCnfData.PBEventType  = SI_PB_EVENT_MODIFY_CNF;
    stCnfData.Storage      = pstMsg->ulStorage;

    stCnfData.PBError = SI_PB_ErrorProc();

    if( ( TAF_ERR_NO_ERROR == stCnfData.PBError )
        && ( PB_INIT_FINISHED != gstPBInitState.enPBInitStep ) )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;
    }

    /*�������к��벻�ܸ���*/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((PB_ECC == pstMsg->ulStorage)
     || (PB_XECC == pstMsg->ulStorage))
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
    }
#else
    if (PB_ECC == pstMsg->ulStorage)
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
    }
#endif

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*�����λʧ�ܻ��߻������ݲ�����*/
    {
        PB_WARNING_LOG("SI_PB_ModifyProc: Proc Error");

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->stRecord.Index, pstMsg->stRecord.Index, &ucPBOffset);

    if(VOS_OK != ulResult)  /*��λ�绰����Ϣʧ��*/
    {
        PB_WARNING_LOG("SI_PB_ModifyProc: Find the PhoneBook Content is Error");
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    if(pstMsg->stRecord.NumberLength > gastPBContent[ucPBOffset].ucNumberLen)
    {
        PB_WARNING_LOG("SI_PB_ModifyProc: Number Too Long");
        stCnfData.PBError = TAF_ERR_PB_DIAL_STRING_TOO_LONG;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    if(SI_PB_STORAGE_SM == pstMsg->ulStorage)/*���ʵ���ADN��Ҫת����¼��*/
    {
        ulResult = SI_PB_CountADNRecordNum(pstMsg->stRecord.Index, &usFileId, &ucRecord);
    }
    else                                                            /*���������绰��*/
    {
        ulResult = SI_PB_GetXDNFileID(pstMsg->ulStorage, &usFileId);

        ucRecord = (VOS_UINT8)pstMsg->stRecord.Index;
    }

    if(VOS_ERR == ulResult)                         /*ת��ʧ��*/
    {
        PB_WARNING_LOG("SI_PB_ModifyProc: Get the XDN File ID and Record Number is Error");

        stCnfData.PBError = TAF_ERR_PARA_ERROR;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    ulExtInfoNum = gastPBContent[ucPBOffset].ulExtInfoNum;
    usExtFileId  = gastEXTContent[ulExtInfoNum].usExtFileId;

    ulResult = SI_PB_UpdataXDNFile(ucPBOffset, usFileId, usExtFileId, ucRecord, &pstMsg->stRecord);/*���ø����ļ���API*/

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_ModifyProc: SI_PB_UpdataXDNFile is Error");

        stCnfData.PBError = TAF_ERR_USIM_SIM_CARD_NOTEXIST;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    gstPBReqUnit.enPBEventType          = SI_PB_EVENT_MODIFY_CNF;/*���������ȫ�ֱ����б���*/

    gstPBReqUnit.enPBStoateType         = pstMsg->ulStorage;

    gstPBReqUnit.ucOpID                 = pstMsg->ucOpID;

    gstPBReqUnit.usClientID             = pstMsg->usClient;

    gstPBReqUnit.usIndex1               = pstMsg->stRecord.Index;

    return VOS_OK;
}
VOS_UINT32 SI_PB_SModifyProc(PBMsgBlock *pMsg)
{
    SI_PB_ADD_REP_STRU     *pstMsg;
    SI_PB_EVENT_INFO_STRU  stCnfData;
    VOS_UINT32             ulResult;
    VOS_UINT8              ucRecord;
    VOS_UINT8              ucPBOffset;
    VOS_UINT32             ulExtInfoNum;
    SI_PB_SPB_UPDATE_STRU  stSPBFid;

    /*lint -e534*/
    VOS_MemSet(&stSPBFid, 0, sizeof(stSPBFid));
    /*lint +e534*/

    pstMsg = (SI_PB_ADD_REP_STRU *)pMsg;

    /*lint -e534*/
    VOS_MemSet(&stCnfData, 0, sizeof(SI_PB_EVENT_INFO_STRU));/*��ʼ���ֲ�����*/
    /*lint +e534*/

    stCnfData.ClientId     = pstMsg->usClient;    /*������Ϣ���ظ�����*/
    stCnfData.OpId         = pstMsg->ucOpID;
    stCnfData.PBEventType  = SI_PB_EVENT_SMODIFY_CNF;
    stCnfData.Storage      = pstMsg->ulStorage;

    if((0 == gstPBConfigInfo.ucSPBFlag)||(SI_PB_STORAGE_SM != pstMsg->ulStorage))
    {
        /*��ΪOperation not allowed*/
        stCnfData.PBError = TAF_ERR_CMD_TYPE_ERROR;

        return SI_PBCallback(&stCnfData);
    }

    stCnfData.PBError = SI_PB_ErrorProc();

    if( ( TAF_ERR_NO_ERROR == stCnfData.PBError )
        && ( PB_INIT_FINISHED != gstPBInitState.enPBInitStep ) )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;
    }

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*�����λʧ�ܻ��߻������ݲ�����*/
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: Proc Error");

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->stRecord.Index, pstMsg->stRecord.Index, &ucPBOffset);

    if(VOS_OK != ulResult)  /*��λ�绰����Ϣʧ��*/
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: Find the PhoneBook Content is Error");
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);
    }

    /*ADN�绰�����볤�ȼ��*/
    if(pstMsg->stRecord.NumberLength > gastPBContent[ucPBOffset].ucNumberLen)
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: Number Too Long");
        stCnfData.PBError = TAF_ERR_PB_DIAL_STRING_TOO_LONG;

        return SI_PBCallback(&stCnfData);
    }

    if(VOS_NULL_PTR == gastPBContent[ucPBOffset].pContent)/*��λ����ʧ��*/
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: Content is NULL");
        stCnfData.PBError = TAF_ERR_UNSPECIFIED_ERROR;

        return SI_PBCallback(&stCnfData);       /*���ûص�����*/
    }

    /*ADN�绰��FID����¼�Ż�ȡ*/
    ulResult = SI_PB_CountADNRecordNum(pstMsg->stRecord.Index, &stSPBFid.usADNFileId, &ucRecord);

    if(VOS_ERR == ulResult)/*ת��ʧ��*/
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: Get the XDN File ID and Record Number is Error");

        stCnfData.PBError = TAF_ERR_PARA_ERROR;

        return SI_PBCallback(&stCnfData);
    }

    /*�ڶ��绰��������鼰FID��ȡ*/
    ulResult = SI_PB_GetANRInfo(pstMsg->stRecord.AdditionNumber,stSPBFid.usADNFileId,stSPBFid.ausANRFileId);

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: Get the ANR Info Fail");

        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);
    }

    /*Email �ļ�FID��ȡ,���Է���ֵ���û����µ�Email�Ƿ���ڷ���SI_PB_UpdataSPBFile���ж�*/
    if(gstPBConfigInfo.ucEmailFlag)
    {
        /*lint -e534*/
        SI_PB_GetEMLFIdFromADN(&stSPBFid.usEMLFileId,stSPBFid.usADNFileId);
        /*lint +e534*/
    }
    else
    {
        stSPBFid.usEMLFileId = 0;
    }

    /*EXT�ļ�FID��ȡ*/
    ulExtInfoNum          = gastPBContent[ucPBOffset].ulExtInfoNum;
    stSPBFid.usExtFileId  = gastEXTContent[ulExtInfoNum].usExtFileId;

    gstPBReqUnit.enPBLock = PB_LOCKED;

    stSPBFid.ucRecordNum = ucRecord;

    ulResult = SI_PB_UpdataSPBFile(&stSPBFid,&pstMsg->stRecord);/*���ø����ļ���API*/

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: SI_PB_UpdataSPBFile is Error");

        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    gstPBReqUnit.enPBEventType          = SI_PB_EVENT_MODIFY_CNF;/*���������ȫ�ֱ����б���*/

    gstPBReqUnit.enPBStoateType         = pstMsg->ulStorage;

    gstPBReqUnit.ucOpID                 = pstMsg->ucOpID;

    gstPBReqUnit.usClientID             = pstMsg->usClient;

    gstPBReqUnit.usIndex1               = pstMsg->stRecord.Index;

    return VOS_OK;
}
VOS_UINT32 SI_PB_DeleteProc(PBMsgBlock *pMsg)
{
    SI_PB_DELETE_REQ_STRU *pstMsg;
    SI_PB_EVENT_INFO_STRU stCnfData;
    VOS_UINT32            ulResult;
    VOS_UINT16            usFileId;
    VOS_UINT8             ucRecord;
    VOS_UINT8             ucPBOffset;
    VOS_UINT8             aucContent[100]; /*ɾ����������ȫF*/

    pstMsg = (SI_PB_DELETE_REQ_STRU *)pMsg;

    SI_PB_MemSet(sizeof(aucContent), 0xFF, aucContent);/*��ʼ���ֲ�����*/

    /*lint -e534*/
    VOS_MemSet(&stCnfData, 0, sizeof(SI_PB_EVENT_INFO_STRU));/*��ʼ���ֲ�����*/
    /*lint +e534*/

    stCnfData.ClientId      = pstMsg->usClient;        /*������Ϣ�������ظ�����*/
    stCnfData.OpId          = pstMsg->ucOpID;
    stCnfData.PBEventType   = SI_PB_EVENT_DELETE_CNF;
    stCnfData.Storage       = pstMsg->ulStorage;

    stCnfData.PBError = SI_PB_ErrorProc();

    if( ( TAF_ERR_NO_ERROR == stCnfData.PBError )
        && ( PB_INIT_FINISHED != gstPBInitState.enPBInitStep ) )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;
    }

    /*�������к��벻��ɾ��*/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((PB_ECC == pstMsg->ulStorage)
     || (PB_XECC == pstMsg->ulStorage))
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
    }
#else
    if (PB_ECC == pstMsg->ulStorage)
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
    }
#endif

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*�����λʧ�ܻ��߻������ݲ�����*/
    {
        PB_WARNING_LOG("SI_PB_DeleteProc: Proc Error");

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->usIndex, pstMsg->usIndex, &ucPBOffset);

    if(VOS_OK != ulResult)     /*��λ������Ϣʧ��*/
    {
        PB_WARNING_LOG("SI_PB_DeleteProc: Find the PhoneBook Content is Error");

        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    if(SI_PB_STORAGE_SM == pstMsg->ulStorage) /*�����ǰ���ʵ���ADN��Ҫת����¼��*/
    {
        ulResult = SI_PB_CountADNRecordNum(pstMsg->usIndex, &usFileId, &ucRecord);
    }
    else                                                        /*��ǰ���ʵ��������绰��*/
    {
        ulResult = SI_PB_GetXDNFileID(pstMsg->ulStorage, &usFileId);

        ucRecord = (VOS_UINT8)pstMsg->usIndex;
    }

    if(VOS_ERR == ulResult)         /*ת������*/
    {
        PB_WARNING_LOG("SI_PB_DeleteProc: Get the XDN File ID and Record Number is Error");

        stCnfData.PBError = TAF_ERR_PARA_ERROR;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }


    if (SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBOffset].pIndex,
                                (VOS_UINT32)pstMsg->usIndex))
    {
        stCnfData.PBError = TAF_ERR_NO_ERROR;

        return SI_PBCallback(&stCnfData);
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    /*���ú���ɾ�����ж����ΪADN����Ҫɾ�����ϵ绰��*/
    ulResult = SI_PB_DeleteHandle(usFileId,ucRecord,ucPBOffset,pstMsg->usIndex);

    if(VOS_OK != ulResult)
    {
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);
    }

    gstPBReqUnit.enPBEventType      = SI_PB_EVENT_DELETE_CNF;/*������ݱ���*/

    gstPBReqUnit.enPBStoateType     = pstMsg->ulStorage;

    gstPBReqUnit.ucOpID             = pstMsg->ucOpID;

    gstPBReqUnit.usClientID         = pstMsg->usClient;

    gstPBReqUnit.usIndex1           = pstMsg->usIndex;

    return VOS_OK;
}
VOS_UINT32 SI_PB_RefreshALLContent(VOS_VOID)
{
    VOS_UINT32             ulResult  = VOS_ERR;

    SI_PB_ClearPBContent(SI_CLEARALL);

    SI_PB_ClearSPBContent(SI_CLEARALL);

    SI_PB_InitGlobeVariable();

    SI_PB_InitStatusInd(USIMM_PB_IDLE);

    gulPBFileCnt = 0;

    if ( VOS_OK != SI_PB_InitPBStatusJudge())/*���ݿ������趨��ʼ������*/
    {
        PB_ERROR_LOG("SI_PB_RefreshProc:Card Status Error");

        return VOS_ERR;
    }

    if ( PB_INIT_EFPBR == gstPBInitState.enPBInitStep )/*USIM��*/
    {
        ulResult = SI_PB_InitEFpbrReq();
    }
    else                                        /*SIM��*/
    {
        ulResult = SI_PB_InitXDNSpaceReq();
    }

    return ulResult;
}
VOS_UINT32 SI_PB_FDNCheckProc(PBMsgBlock *pMsg)
{
    PB_FDN_CHECK_CNF_STRU              *pstFDNCheckCnf;
    SI_PB_FDN_CHECK_REQ_STRU           *pstFDNCheckReq;
    VOS_UINT32                          ulResult1 = VOS_OK;
    VOS_UINT32                          ulResult2 = VOS_OK;
    VOS_UINT32                          ulFdnStatus;

    pstFDNCheckReq = (SI_PB_FDN_CHECK_REQ_STRU *)pMsg;

    pstFDNCheckCnf = (PB_FDN_CHECK_CNF_STRU *)VOS_AllocMsg(MAPS_PB_PID,sizeof(PB_FDN_CHECK_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstFDNCheckCnf)
    {
        PB_ERROR_LOG("SI_PB_FDNCheckProc: alloc msg failed.");

        return VOS_ERR;
    }

    /*���FDNδʹ��ֱ�ӷ���VOS_OK*/
    USIMM_FdnQuery(&ulFdnStatus);

    pstFDNCheckCnf->ulReceiverPid   = pstFDNCheckReq->ulSenderPid;
    pstFDNCheckCnf->ulMsgName       = SI_PB_EVENT_FDNCHECK_CNF;
    pstFDNCheckCnf->enAppType       = pstFDNCheckReq->enAppType;
    pstFDNCheckCnf->ulSendPara      = pstFDNCheckReq->ulSendPara;
    pstFDNCheckCnf->ulContextIndex  = pstFDNCheckReq->ulContextIndex;

    if (USIMM_FDNSTATUS_OFF == ulFdnStatus)
    {
        PB_INFO_LOG("SI_PB_CheckFdn: FDN is disable.");
    }
    else
    {
        /* ����һ������ */
        ulResult1 = SI_PB_CheckFdn(pstFDNCheckReq->stFDNNum.aucNum1, pstFDNCheckReq->stFDNNum.ulNum1Len);

        /* ����ڶ������볤�ȴ���0�����ڶ������� */
        if (pstFDNCheckReq->stFDNNum.ulNum2Len > 0)
        {
            ulResult2 = SI_PB_CheckFdn(pstFDNCheckReq->stFDNNum.aucNum2, pstFDNCheckReq->stFDNNum.ulNum2Len);
        }
    }

    if((VOS_OK != ulResult1)&&(VOS_OK != ulResult2))
    {
        pstFDNCheckCnf->enResult    = PB_FDN_CHECK_BOTH_NUM_FAIL;
    }
    else if(VOS_OK != ulResult1)
    {
        pstFDNCheckCnf->enResult    = PB_FDN_CHECK_NUM1_FAIL;
    }
    else if(VOS_OK != ulResult2)
    {
        pstFDNCheckCnf->enResult    = PB_FDN_CHECK_NUM2_FAIL;
    }
    else
    {
        pstFDNCheckCnf->enResult    = PB_FDN_CHECK_SUCC;
    }

    return VOS_SendMsg(MAPS_PB_PID, pstFDNCheckCnf);
}
VOS_UINT32 SI_PB_EcallNumberQryProc(PBMsgBlock *pMsg)
{
    SI_PB_ECALLQRY_REQ_STRU            *pstEcallQryReq;
    SI_PB_ECALLQRY_CNF_STRU            *pstEcallQryCnf;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulRecordNum;
    VOS_UINT8                           ucPBOffset;

    pstEcallQryReq = (SI_PB_ECALLQRY_REQ_STRU *)pMsg;

    ulRslt = SI_PB_EcallNumberErrProc(pstEcallQryReq->enStorage, pstEcallQryReq->ucListLen, pstEcallQryReq->aucList, &ucPBOffset);

    /* �������������ֻ�н���������ȷ����NASҪ��ļ�¼������FDN/SDN��¼ */
    ulRecordNum = (TAF_ERR_NO_ERROR == ulRslt)?pstEcallQryReq->ucListLen:0;

/*lint -save -e961 */
    pstEcallQryCnf = (SI_PB_ECALLQRY_CNF_STRU *)VOS_AllocMsg(MAPS_PB_PID,
                                                sizeof(SI_PB_ECALLQRY_CNF_STRU)-VOS_MSG_HEAD_LENGTH
                                                + ((sizeof(SI_PB_ECALL_NUM_STRU) * ulRecordNum)));
/*lint -restore */
    if (VOS_NULL_PTR == pstEcallQryCnf)
    {
        PB_ERROR_LOG("SI_PB_EcallNumberQryProc: alloc msg failed.");

        return VOS_ERR;
    }

    pstEcallQryCnf->ulReceiverPid   = pstEcallQryReq->ulSenderPid;
    pstEcallQryCnf->ulMsgName       = SI_PB_EVENT_ECALLQUERY_CNF;
    pstEcallQryCnf->enStorage       = pstEcallQryReq->enStorage;
    pstEcallQryCnf->ulRecordNum     = VOS_NULL;
    pstEcallQryCnf->ulRslt          = ulRslt;
    pstEcallQryCnf->enAppType       = USIMM_GUTL_APP;

    if (TAF_ERR_NO_ERROR == ulRslt)
    {
        pstEcallQryCnf->ulRecordNum     = pstEcallQryReq->ucListLen;

        /*lint -e534*/
        VOS_MemSet(pstEcallQryCnf->astECallNumber, 0, sizeof(SI_PB_ECALL_NUM_STRU) * ulRecordNum);
        /*lint +e534*/

        SI_PB_GetEcallNumber(gastPBContent + ucPBOffset, pstEcallQryCnf->astECallNumber, pstEcallQryReq->ucListLen, pstEcallQryReq->aucList);
    }

    return VOS_SendMsg(MAPS_PB_PID, pstEcallQryCnf);
}
VOS_VOID SI_PB_JudgeTotalUsedNum(VOS_UINT8 ucPBOffset,SI_PB_EVENT_INFO_STRU *pstCnfData)
{
    if ((SI_PB_EVENT_ADD_CNF == gstPBReqUnit.enPBEventType)
        ||(SI_PB_EVENT_SADD_CNF == gstPBReqUnit.enPBEventType))
    {
        if(PB_ADN_CONTENT == ucPBOffset)
        {
            gstPBCtrlInfo.ulTotalUsed++;
        }

        pstCnfData->PBEvent.PBAddCnf.Index = gstPBReqUnit.usIndex1;

        SI_PB_SetBitToBuf(gastPBContent[ucPBOffset].pIndex
            ,gstPBReqUnit.usIndex1,SI_PB_CONTENT_VALID);
    }
    else if (SI_PB_EVENT_DELETE_CNF == gstPBReqUnit.enPBEventType)
    {
        if(PB_ADN_CONTENT == ucPBOffset)
        {
            gstPBCtrlInfo.ulTotalUsed--;
        }

        SI_PB_SetBitToBuf(gastPBContent[ucPBOffset].pIndex,
                          gstPBReqUnit.usIndex1,SI_PB_CONTENT_INVALID);

        SI_PB_MemSet(sizeof(gstPBReqUnit.aucXDNContent), 0xFF,gstPBReqUnit.aucXDNContent);
    }
    else if ((SI_PB_EVENT_MODIFY_CNF == gstPBReqUnit.enPBEventType)
             ||(SI_PB_EVENT_SMODIFY_CNF == gstPBReqUnit.enPBEventType))
    {

        if (SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBOffset].pIndex,
                                                        gstPBReqUnit.usIndex1))
        {
            /*gastPBContent[ucPBOffset].usUsedNum++;
 */

            if(PB_ADN_CONTENT == ucPBOffset)
            {
                gstPBCtrlInfo.ulTotalUsed++;
            }

            SI_PB_SetBitToBuf(gastPBContent[ucPBOffset].pIndex,
                    gstPBReqUnit.usIndex1,SI_PB_CONTENT_VALID);
        }
    }
    else
    {
        /*should not*/
    }

    return;
}
VOS_VOID SI_PB_RefreshADNUsedNum(VOS_UINT8 *pucDstStorage, VOS_UINT8 *pucSrcReq,VOS_UINT8 ucOffset)
{
   /*�õ绰������(���жϻ����Ƿ�Ϊ��)��PBreq�Ƚ�*/
    /*���ԭ����Ч��������Ч������Чֵ����*/
    if(VOS_OK == SI_PB_CheckContentValidity(&gastPBContent[ucOffset],
                                            pucDstStorage))
    {
        if(VOS_OK != SI_PB_CheckContentValidity(&gastPBContent[ucOffset],
                                                pucSrcReq))
        {
            gastPBContent[ucOffset].usUsedNum--;
        }
    }
    /*���ԭ����Ч��������Ч������Чֵ�Ӽ�*/
    else
    {
        if(VOS_OK == SI_PB_CheckContentValidity(&gastPBContent[ucOffset],
                                                pucSrcReq))
        {
            gastPBContent[ucOffset].usUsedNum++;
        }
    }

    return;
}
VOS_VOID SI_PB_RefreshEXTUsedNum(VOS_UINT8 *pucDstStorage, VOS_UINT8 *pucSrcReq, VOS_UINT8 ucOffset)
{
    if((0x0 != pucDstStorage[0])&&(0xFF != pucDstStorage[1]))/*��Ч*/
    {
        if((0x0 == pucSrcReq[0])||(0xFF == pucSrcReq[1]))
        {
            gastEXTContent[ucOffset].usExtUsedNum--;
        }
    }
    else
    {
        if((0x0 != pucSrcReq[0])&&(0xFF != pucSrcReq[1]))
        {
            gastEXTContent[ucOffset].usExtUsedNum++;
        }
    }

    return;
}
VOS_VOID SI_PB_RefreshANRUsedNum(VOS_UINT8 *pucDstStorage, VOS_UINT8 *pucSrcReq, VOS_UINT8 ucOffset)
{
    if(VOS_OK == SI_PB_CheckANRValidity(pucDstStorage))/*��Ч*/
    {
        if(VOS_OK != SI_PB_CheckANRValidity(pucSrcReq))
        {
            gastANRContent[ucOffset].usUsedNum--;
        }
    }
    else
    {
        if(VOS_OK == SI_PB_CheckANRValidity(pucSrcReq))
        {
            gastANRContent[ucOffset].usUsedNum++;
        }
    }

    return;
}
VOS_VOID SI_PB_RefreshEMLUsedNum(VOS_UINT8 *pucDstStorage, VOS_UINT8 *pucSrcReq)
{
    if(0xFF != pucDstStorage[0])/*��Ч*/
    {
        if(0xFF == pucSrcReq[0])
        {
            gstEMLContent.usUsedNum--;
        }
    }
    else
    {
        if(0xFF != pucSrcReq[0])
        {
            gstEMLContent.usUsedNum++;
        }
    }

    return;
}
VOS_UINT32 SI_PB_RefreshMemory(VOS_UINT16 usFileId,VOS_UINT16 usRecordLen,VOS_UINT8 ucOffset,VOS_UINT8 ucRecordNum)
{
    VOS_UINT8  *pucSrcReq;
    VOS_UINT8  *pucDstStorage;
    VOS_UINT16 usMemOffset;
    VOS_UINT8  ucSuffix;
    VOS_UINT8  ucFileCnt;

    /*���������ļ������ĸ��绰��*/
    if(VOS_OK == SI_PB_JudgeADNFid(usFileId))/*ADN*/
    {
        usMemOffset   = (VOS_UINT16)((gstPBReqUnit.usIndex1-1)*gastPBContent[ucOffset].ucRecordLen);
        pucSrcReq     = gstPBReqUnit.aucXDNContent;
        pucDstStorage = &gastPBContent[ucOffset].pContent[usMemOffset];

        SI_PB_RefreshADNUsedNum(pucDstStorage, pucSrcReq, ucOffset);
    }
    else if(VOS_OK == SI_PB_JudgeEXTFid(usFileId, ucOffset))/*EXT*/
    {
        /*����EXT�Ļظ�Record��ȡ��������gstPBReqUnit�еĶ�Ӧλ��*/
        if(VOS_OK != SI_PB_GetEXTContentFromReq(ucRecordNum,&pucSrcReq))
        {
            PB_WARNING_LOG("SI_PB_RefreshMemory:SI_PB_GetEXTContentFromReq ERROR.");
            return VOS_ERR;
        }

        usMemOffset   = (ucRecordNum-1)*SI_PB_EXT_LEN;
        pucDstStorage = &gastEXTContent[ucOffset].pExtContent[usMemOffset];

        SI_PB_RefreshEXTUsedNum(pucDstStorage, pucSrcReq, ucOffset);
    }
    else if(VOS_OK == SI_PB_GetANRSuffix(&ucFileCnt,&ucSuffix,usFileId))/*ANR*/
    {
        pucSrcReq     = gstPBReqUnit.stSPBReq.aucANRContent[ucSuffix];

        usMemOffset   = (VOS_UINT16)(((ucFileCnt*gstPBCtrlInfo.astANRInfo[ucFileCnt][ucSuffix].ucRecordNum)
             +(ucRecordNum - 1))*gastANRContent[ucSuffix].ucRecordLen);

        pucDstStorage = &gastANRContent[ucSuffix].pContent[usMemOffset];

        SI_PB_RefreshANRUsedNum(pucDstStorage, pucSrcReq, ucSuffix);
    }
    else if(VOS_OK == SI_PB_GetEMLRecord(&pucDstStorage , usFileId, ucRecordNum))/*Email*/
    {
        pucSrcReq = gstPBReqUnit.stSPBReq.aucEMLContent;

        SI_PB_RefreshEMLUsedNum(pucDstStorage, pucSrcReq);
    }
    else if(VOS_OK == SI_PB_JudgeIAPFid(usFileId))
    {

        pucSrcReq = gstPBReqUnit.stSPBReq.aucIAPContent;

        pucDstStorage = &gstIAPContent.pIAPContent[(gstPBReqUnit.usIndex1-1)*gstIAPContent.ucRecordLen];

        PB_NORMAL_LOG("SI_PB_RefreshMemory:IAP File.");

    }
    else if( (EFFDN == usFileId) || (EFBDN == usFileId) || (EFMSISDN == usFileId) )
    {
        pucSrcReq = gstPBReqUnit.aucXDNContent;
        pucDstStorage = gastPBContent[ucOffset].pContent + ((gstPBReqUnit.usIndex1-1)* gastPBContent[ucOffset].ucRecordLen);

        if(SI_PB_EVENT_ADD_CNF == gstPBReqUnit.enPBEventType)
        {
            gastPBContent[ucOffset].usUsedNum++;
        }

        if(SI_PB_EVENT_DELETE_CNF == gstPBReqUnit.enPBEventType)
        {
            gastPBContent[ucOffset].usUsedNum--;
            SI_PB_MemSet(sizeof(gstPBReqUnit.aucXDNContent), 0xFF,gstPBReqUnit.aucXDNContent);
        }

        if(SI_PB_EVENT_MODIFY_CNF == gstPBReqUnit.enPBEventType)
        {
            if(VOS_OK != SI_PB_CheckContentValidity(&gastPBContent[ucOffset], pucDstStorage) )
            {
                 gastPBContent[ucOffset].usUsedNum++;
            }
        }
    }
    else
    {
        PB_WARNING_LOG("SI_PB_RefreshMemory:Unknown PB Type.");
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(pucDstStorage, pucSrcReq, usRecordLen);
    /*lint +e534*/

    return VOS_OK;
}


VOS_VOID SI_PB_UsimSetFileProc(USIMM_UPDATEFILE_CNF_STRU    *pstMsg,
                                        VOS_UINT8                   ucPBOffset,
                                        SI_PB_EVENT_INFO_STRU       *pstCnfData)
{
    VOS_UINT16          usEFId;

    SI_PB_GetEFIDFromPath(&pstMsg->stFilePath, &usEFId);

    if(VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        pstCnfData->PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
        PB_WARNING_LOG("SI_PB_UsimSetFileProc:Usimm Cnf ERROR.");
        return;
    }

    SI_PB_JudgeTotalUsedNum(ucPBOffset,pstCnfData);

    if(VOS_NULL_PTR != gastPBContent[ucPBOffset].pContent)
    {
        if(VOS_OK != SI_PB_RefreshMemory(usEFId, pstMsg->usEFLen, ucPBOffset, pstMsg->ucRecordNum))
        {
            pstCnfData->PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
            PB_WARNING_LOG("SI_PB_UsimSetFileProc:SI_PB_RefreshMemory ERROR.");
            return;
        }
    }

    if(VOS_OK == SI_PB_CheckADNFileID(usEFId))
    {
        SI_PB_IncreaceCCValue(1,pstMsg->ucRecordNum);
    }

    return;
}


VOS_VOID SI_PB_UsimSetExtFileProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg, VOS_UINT8 ucPBOffset)
{
    VOS_UINT8   *ptemp;
    VOS_UINT32  ulExtInfoNum;

    ulExtInfoNum = gastPBContent[ucPBOffset].ulExtInfoNum;

    if(VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        ptemp = gastEXTContent[ucPBOffset].pExtContent
                + ( (gstPBReqUnit.usExtIndex - 1) * SI_PB_EXT_LEN);

        if(SI_PB_EVENT_ADD_CNF == gstPBReqUnit.enPBEventType)
        {
            gastEXTContent[ulExtInfoNum].usExtUsedNum++;
        }

        if(SI_PB_EVENT_DELETE_CNF == gstPBReqUnit.enPBEventType)
        {
            gastEXTContent[ulExtInfoNum].usExtUsedNum--;
        }

        if( (SI_PB_EVENT_MODIFY_CNF == gstPBReqUnit.enPBEventType)
            && ( 0xFF == *(ptemp+1)) )
        {
            gastEXTContent[ulExtInfoNum].usExtUsedNum++;
        }

        /*lint -e534*/
        VOS_MemCpy(ptemp, gstPBReqUnit.aucEXTContent, SI_PB_EXT_LEN);
        /*lint +e534*/
    }
    else
    {
        PB_WARNING_LOG("WARNING:SI_PB_UsimSetExtFileProc ERROR.");
    }
}


VOS_VOID SI_PB_RefreshCardIndMsgSnd(VOS_VOID)
{
    VOS_UINT8                           ucCardStatus;
    VOS_UINT8                           ucCardType;
    USIMM_CARDSTATUS_IND_STRU          *pUsimMsg;

    /*lint -e534*/
    USIMM_GetCardTypeByAppType(&ucCardStatus, &ucCardType, USIMM_GUTL_APP);
    /*lint +e534*/

    pUsimMsg = (USIMM_CARDSTATUS_IND_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                               sizeof(USIMM_CARDSTATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pUsimMsg)
    {
        return;
    }

    pUsimMsg->ulMsgName                     = USIMM_CARDSTATUS_IND;    /* ������Ϣ���� */
    pUsimMsg->stUsimSimInfo.enCardType      = ucCardType;
    pUsimMsg->stUsimSimInfo.enCardService   = ucCardStatus;
    pUsimMsg->stCsimUimInfo.enCardType      = USIMM_CARD_NOCARD;
    pUsimMsg->stCsimUimInfo.enCardService   = USIMM_CARD_SERVIC_ABSENT;
    pUsimMsg->stIsimInfo.enCardType         = USIMM_CARD_NOCARD;
    pUsimMsg->stIsimInfo.enCardService      = USIMM_CARD_SERVIC_ABSENT;
    pUsimMsg->ulReceiverPid                 = MAPS_PB_PID;

    (VOS_VOID)VOS_SendMsg(MAPS_PIH_PID, pUsimMsg);

    return;
}

/*****************************************************************************
�� �� ��  :SI_PB_SimRefreshFileCheck
��������  :PBģ���ж��Ƿ���SIM���绰������
�������  :usPathLen:·������
           pcFilePath:·������
�������  :��
�� �� ֵ  :��
�޶���¼  :
1. ��    ��   : 2015��2��2��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_BOOL SI_PB_SimRefreshFileCheck(VOS_UINT16 usPathLen, VOS_UINT8 *pcFilePath)
{
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, usPathLen, (VOS_CHAR *)pcFilePath, &enFileID))
    {
        PB_WARNING_LOG("SI_PB_SimRefreshFileCheck: USIMM_ChangePathToDefFileID is ERROR.");

        return VOS_FALSE;
    }

    if (  (enFileID == USIMM_TELE_EFADN_ID)
        ||(enFileID == USIMM_TELE_EFFDN_ID)
        ||(enFileID == USIMM_TELE_EFBDN_ID)
        ||(enFileID == USIMM_TELE_EFMSISDN_ID))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
�� �� ��  :SI_PB_UsimRefreshFileCheck
��������  :PBģ���ж��Ƿ���SIM���绰������
�������  :usPathLen:·������
           pcFilePath:·������
�������  :��
�� �� ֵ  :��
�޶���¼  :
1. ��    ��   : 2015��2��2��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_BOOL SI_PB_UsimRefreshFileCheck(
    VOS_UINT16                          usPathLen, 
    VOS_UINT8                           *pcFilePath,
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    VOS_CHAR                            aucGlobalPath[] = {'3','F','0','0','7','F','1','0','5','F','3','A'};
    VOS_CHAR                            aucLocallPath[] = {'3','F','0','0','7','F','F','F','5','F','3','A'};
    VOS_INT32                           lRslt1;
    VOS_INT32                           lRslt2;
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID;

    lRslt1 = VOS_MemCmp(aucGlobalPath, pcFilePath, sizeof(aucGlobalPath));
    lRslt2 = VOS_MemCmp(aucLocallPath, pcFilePath, sizeof(aucLocallPath));

    if ((VOS_OK == lRslt1) || (VOS_OK == lRslt2))
    {
        return VOS_TRUE;
    }

    if (VOS_OK != USIMM_ChangePathToDefFileID(enAppType, usPathLen, (VOS_CHAR *)pcFilePath, &enFileID))
    {
        PB_WARNING_LOG("SI_PB_SimRefreshFileCheck: USIMM_ChangePathToDefFileID is ERROR.");

        return VOS_FALSE;
    }

    if ((enFileID == USIMM_TELE_EFFDN_ID)
     || (enFileID == USIMM_TELE_EFBDN_ID)
     || (enFileID == USIMM_TELE_EFMSISDN_ID)
     || (enFileID == USIMM_USIM_EFFDN_ID)
     || (enFileID == USIMM_USIM_EFBDN_ID)
     || (enFileID == USIMM_USIM_EFMSISDN_ID))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
�� �� ��  :SI_PB_RefreshFileCheck
��������  :PBģ��Refresh�����ж��Ƿ���Ҫ����
�������  :pstMsg:REFRESH����ָʾ��Ϣ
�������  :��
�� �� ֵ  :��
�޶���¼  :
1. ��    ��   : 2015��2��2��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_BOOL SI_PB_RefreshFileCheck(USIMM_STKREFRESH_IND_STRU *pstMsg)
{
    VOS_UINT16                          i;

    if (USIMM_CARD_SIM == gstPBInitState.enCardType)
    {
        for (i=0; i<pstMsg->usEfNum; i++)
        {
            if (VOS_TRUE == SI_PB_SimRefreshFileCheck(pstMsg->astEfId[i].usPathLen, pstMsg->astEfId[i].aucPath))
            {
                return VOS_TRUE;
            }
        }
    }
    else
    {
        for (i=0; i<pstMsg->usEfNum; i++)
        {
            if (VOS_TRUE == SI_PB_UsimRefreshFileCheck(pstMsg->astEfId[i].usPathLen, 
                                                        pstMsg->astEfId[i].aucPath,
                                                        pstMsg->astEfId[i].enAppType))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}


VOS_VOID SI_PB_PihRefreshIndProc(USIMM_STKREFRESH_IND_STRU *pstMsg)
{
    VOS_UINT32                          ulPbRefreshFlag;

    if (USIMM_REFRESH_ALL_FILE == pstMsg->enRefreshType)
    {
        ulPbRefreshFlag = VOS_TRUE;
    }
    else if (USIMM_REFRESH_3G_SESSION_RESET == pstMsg->enRefreshType)
    {
        ulPbRefreshFlag = VOS_FALSE;
    }
    else if (USIMM_REFRESH_FILE_LIST == pstMsg->enRefreshType)
    {
        if (VOS_FALSE == SI_PB_RefreshFileCheck(pstMsg))
        {
            ulPbRefreshFlag = VOS_FALSE;
        }
        else
        {
            ulPbRefreshFlag = VOS_TRUE;
        }
    }
    else
    {
        ulPbRefreshFlag = VOS_FALSE;
    }

    if (VOS_TRUE == ulPbRefreshFlag)
    {
        SI_PB_ReleaseAll();

        SI_PB_InitStatusInd(USIMM_PB_IDLE);

        SI_PB_RefreshCardIndMsgSnd();
    }

    return;
}

VOS_VOID SI_PB_UsimSetSPBFileProc(USIMM_SETMUTILFILE_CNF_STRU *pstPBMsg,
                                             SI_PB_EVENT_INFO_STRU       *pstCnfData,
                                             VOS_UINT8                   ucOffset)
{
    VOS_UINT32 i;

    /*���USIMM�ظ�ʧ�ܣ���ֱ���˳��������ڴ���в���*/
    if(VOS_OK != pstPBMsg->stCmdResult.ulResult)
    {
        pstCnfData->PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
        PB_WARNING_LOG("SI_PB_UsimSetSPBFileProc:Usimm Cnf ERROR.");
        return;
    }

    SI_PB_JudgeTotalUsedNum(ucOffset,pstCnfData);

    /*��Ը��ϵ绰���е�ÿ���绰����Ҫ�Ƚϸ���ǰ����ڴ��������ȷ��ʹ��������������ڴ�*/
    for(i = 0; i < pstPBMsg->ucFileNum; i++)
    {
        if(VOS_OK != SI_PB_RefreshMemory(pstPBMsg->ausEfId[i],
                                        pstPBMsg->ausEfLen[i],
                                         ucOffset,
                                         pstPBMsg->aucRecordNum[i]))
        {
            pstCnfData->PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
            PB_WARNING_LOG("SI_PB_UsimSetSPBFileProc:SI_PB_RefreshMemory ERROR.");
            return;
        }

        if(VOS_OK == SI_PB_CheckADNFileID(pstPBMsg->ausEfId[i]))
        {
            SI_PB_IncreaceCCValue(1,pstPBMsg->aucRecordNum[i]);
        }
    }

    return;
}

/*****************************************************************************
�� �� ��  :
��������  :
�������  :
�������  :
�� �� ֵ  :
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2007��10��15��
    ��    ��   :
    �޸�����   : Creat

*****************************************************************************/
VOS_VOID SI_PB_UsimGetFileProc(USIMM_READFILE_CNF_STRU *pstMsg,
                                        VOS_UINT8               ucPBOffset,
                                        SI_PB_EVENT_INFO_STRU   *pstCnfData)
{
    if(VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        pstCnfData->PBError = TAF_ERR_PB_STORAGE_OP_FAIL;

        PB_WARNING_LOG("SI_PB_UsimGetFileProc: USIMM Cnf Error");

        return;
    }

    SI_PB_TransPBFromate(&gastPBContent[ucPBOffset],
                        gstPBReqUnit.usCurIndex,
                        pstMsg->aucEf,
                        &pstCnfData->PBEvent.PBReadCnf.PBRecord);

    pstCnfData->PBEvent.PBReadCnf.RecordNum
            = (gstPBReqUnit.usIndex2 - gstPBReqUnit.usIndex1) + 1;

    if(gstPBReqUnit.usCurIndex == gstPBReqUnit.usIndex2)
    {
        pstCnfData->PBLastTag = VOS_TRUE;
    }
    else
    {
        pstCnfData->PBLastTag = VOS_FALSE;

        gstPBReqUnit.usCurIndex++;
    }

    return ;
}

VOS_VOID SI_PB_UsimSearchFileProc(USIMM_READFILE_CNF_STRU *pstMsg,
                                            VOS_UINT8               ucPBOffset,
                                            SI_PB_EVENT_INFO_STRU   *pstCnfData)
{
    if(VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        pstCnfData->PBError = TAF_ERR_PB_STORAGE_OP_FAIL;

        PB_WARNING_LOG("SI_PB_UsimSearchFileProc: USIMM Cnf Error");

        return;
    }

    pstCnfData->PBEvent.PBSearchCnf.RecordNum
            = (gstPBReqUnit.usIndex2 - gstPBReqUnit.usIndex1) + 1;

    if((VOS_OK == VOS_MemCmp(pstMsg->aucEf, gstPBReqUnit.aucXDNContent, gstPBReqUnit.usSearchLen))
        ||(0 == gstPBReqUnit.usSearchLen))
    {
        SI_PB_TransPBFromate(&gastPBContent[ucPBOffset], gstPBReqUnit.usCurIndex,
                             pstMsg->aucEf, &pstCnfData->PBEvent.PBSearchCnf.PBRecord);

        gstPBReqUnit.ucEqualFlag = VOS_TRUE;
    }
    else
    {
        pstCnfData->PBEvent.PBSearchCnf.PBRecord.ValidFlag = SI_PB_CONTENT_INVALID;
    }

    if(gstPBReqUnit.usCurIndex == gstPBReqUnit.usIndex2)
    {
        pstCnfData->PBLastTag = VOS_TRUE;

        if (VOS_TRUE != gstPBReqUnit.ucEqualFlag)
        {
            pstCnfData->PBError = TAF_ERR_PB_NOT_FOUND;
        }
    }
    else
    {
        pstCnfData->PBLastTag = VOS_FALSE;

        gstPBReqUnit.usCurIndex++;
    }

    return;
}

VOS_VOID SI_PB_UsimGetIndexFile(VOS_UINT8 ucPBOffset, SI_PB_EVENT_INFO_STRU *pstCnfData)
{
    VOS_UINT32                  ulResult;
    VOS_UINT8                   ucSendReqFlag = PB_REQ_NOT_SEND;
    VOS_UINT8                   ucRecord;
    VOS_UINT16                  usFileId;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    /*���м�¼�Ѿ�����,���߳������˳�*/
    if ((VOS_OK != pstCnfData->PBError)||(VOS_TRUE == pstCnfData->PBLastTag))
    {
        return;
    }

    while(gstPBReqUnit.usCurIndex <= gstPBReqUnit.usIndex2)
    {
        if (SI_PB_CONTENT_VALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBOffset].pIndex
            , gstPBReqUnit.usCurIndex))
        {
            ucSendReqFlag = PB_REQ_SEND;
            break;
        }

        gstPBReqUnit.usCurIndex++;
    }

    if (PB_REQ_SEND == ucSendReqFlag)
    {
        if(SI_PB_STORAGE_SM == gstPBReqUnit.enPBStoateType)   /*�����ADN��Ҫת��Ϊ��¼��*/
        {
            ulResult = SI_PB_CountADNRecordNum(gstPBReqUnit.usCurIndex, &usFileId, &ucRecord);
        }
        else                                                                    /*���������绰��*/
        {
            ulResult = SI_PB_GetXDNFileID(gstPBReqUnit.enPBStoateType, &usFileId);

            ucRecord = (VOS_UINT8)gstPBReqUnit.usCurIndex;
        }

        if(VOS_ERR == ulResult)         /*ת�����ʧ��*/
        {
            PB_WARNING_LOG("SI_PB_SearchReq: Get the XDN File ID and Record Number is Error");

            pstCnfData->PBError = TAF_ERR_PARA_ERROR;

            return;
        }

        stGetFileInfo.ucRecordNum   = ucRecord;
        stGetFileInfo.usEfId        = usFileId;

        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        if (VOS_OK != ulResult)
        {
            pstCnfData->PBError = TAF_ERR_USIM_SIM_CARD_NOTEXIST;
        }
    }
    else
    {
        pstCnfData->PBLastTag = VOS_TRUE;

        if ((SI_PB_EVENT_SEARCH_CNF == gstPBReqUnit.enPBEventType)
             &&(VOS_TRUE != gstPBReqUnit.ucEqualFlag))
        {
            pstCnfData->PBError = TAF_ERR_PB_NOT_FOUND;
        }
    }

    return;
}

/*****************************************************************************
�� �� ��  : SI_PBSendGlobalToAcpu
��������  : ����ȫ�ֱ������ݸ�Acpu
�������  : ��
�������  : ��
�� �� ֵ  : ��
�޶���¼  :
1.  ��    ��   : 2011��10��15��
    ��    ��   : z100318
    �޸�����   : Creat

*****************************************************************************/
VOS_VOID SI_PBSendGlobalToAcpu(VOS_VOID)
{
    SI_PB_UPDATEGLOBAL_IND_STRU        *pstMsg;
    VOS_UINT32                          i;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stSystemAppConfig;

    /* ���ANDROID 64λָ������⣬����ָ�뷢��A��ȥ */
    if (VOS_OK != NV_Read(en_NV_Item_System_APP_Config, &stSystemAppConfig, sizeof(NAS_NVIM_SYSTEM_APP_CONFIG_STRU)))
    {
        return;
    }

    if (SYSTEM_APP_ANDROID == stSystemAppConfig.usSysAppConfigType)
    {
        return;
    }

    pstMsg = (SI_PB_UPDATEGLOBAL_IND_STRU*)VOS_AllocMsg(MAPS_PB_PID,
                                sizeof(SI_PB_UPDATEGLOBAL_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverPid = ACPU_PID_PB;
    pstMsg->ulMsgName     = SI_PB_UPDATE_AGOBAL;

    /*����ȫ�� Acpu ��Ҫ��ȫ�ֱ�������*/
    /*lint -e534*/
    VOS_MemCpy(&pstMsg->stPBCtrlInfo,   &gstPBCtrlInfo,  sizeof(gstPBCtrlInfo));
    VOS_MemCpy(&pstMsg->stPBConfigInfo, &gstPBConfigInfo,sizeof(gstPBConfigInfo));
    VOS_MemCpy(pstMsg->astPBContent,    gastPBContent,   sizeof(gastPBContent));
    VOS_MemCpy(pstMsg->astEXTContent,   gastEXTContent,  sizeof(gastEXTContent));
    VOS_MemCpy(pstMsg->astANRContent,   gastANRContent,  sizeof(gastANRContent));
    VOS_MemCpy(&pstMsg->stEMLContent,   &gstEMLContent,  sizeof(gstEMLContent));
    VOS_MemCpy(&pstMsg->stIAPContent,   &gstIAPContent,  sizeof(gstIAPContent));
    VOS_MemCpy(&pstMsg->stPBInitState,  &gstPBInitState, sizeof(gstPBInitState));
    /*lint +e534*/

    for(i=0; i<SI_PB_MAX_NUMBER; i++)
    {
        pstMsg->astPBContentAddr[i].ulIndexAddr     = (VOS_UINT32)gastPBContent[i].pIndex;
        pstMsg->astPBContentAddr[i].ulContentAddr   = (VOS_UINT32)gastPBContent[i].pContent;

        pstMsg->aulExtContentAddr[i] = (VOS_UINT32)gastEXTContent[i].pExtContent;
    }

    for(i=0; i<SI_PB_ANRMAX; i++)
    {
        pstMsg->aulANRContentAddr[i] = (VOS_UINT32)gastANRContent[i].pContent;
    }

    pstMsg->ulEMLContentAddr = (VOS_UINT32)gstEMLContent.pContent;
    pstMsg->ulIAPContentAddr = (VOS_UINT32)gstIAPContent.pIAPContent;

    if(VOS_OK != VOS_SendMsg(MAPS_PB_PID, pstMsg))
    {
        PB_ERROR_LOG("SI_PBSendGobalToAcpu: Send msg Error");
    }

    return;
}


VOS_VOID SI_PB_EcallInitInd(VOS_VOID)
{
    SI_PB_ECALLINIT_IND_STRU           *pstEcallIndMsg;

    pstEcallIndMsg = (SI_PB_ECALLINIT_IND_STRU *)VOS_AllocMsg(MAPS_PB_PID, sizeof(SI_PB_ECALLINIT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstEcallIndMsg)
    {
        PB_ERROR_LOG("SI_PB_EcallInitInd: Alloc Msg Fail");

        return;
    }

    pstEcallIndMsg->ulReceiverPid       = WUEPS_PID_TAF;
    pstEcallIndMsg->ulMsgName           = SI_PB_EVENT_ECALLINIT_IND;
    pstEcallIndMsg->usFdnRecordNum      = gastPBContent[PB_FDN_CONTENT].usTotalNum;
    pstEcallIndMsg->usSdnRecordNum      = gastPBContent[PB_SDN_CONTENT].usTotalNum;

    (VOS_VOID)VOS_SendMsg(MAPS_PB_PID, pstEcallIndMsg);

    return;
}

/*****************************************************************************
�� �� ��  : SI_PB_ReleaseAll
��������  : �ͷŵ绰���ռ估ȫ�ֱ������
�������  :
�������  :
�� �� ֵ  :

�޶���¼  :
1.  ��    ��   : 2012��06��09��
    ��    ��   :
    �޸�����   : Creat

*****************************************************************************/
VOS_VOID SI_PB_ReleaseAll(VOS_VOID)
{
    gstPBInitState.enPBInitStep = PB_INIT_PB_STATUS;

    SI_PB_ClearPBContent(SI_CLEARALL);

    SI_PB_ClearSPBContent(SI_CLEARALL);

    SI_PB_InitGlobeVariable();

    SI_PBSendGlobalToAcpu();
}

/*****************************************************************************
�� �� ��  : SI_PBUsimCnfMsgProc
��������  : ����USIMMģ��ظ���������Ҫ���ݽ���ظ���AT
�������  : ��Ϣ����
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2007��10��15��
    ��    ��   :
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 SI_PBUsimCnfMsgProc(PBMsgBlock *pMsg)
{
    VOS_UINT8                   ucPBOffset;
    SI_PB_EVENT_INFO_STRU       stCnfData;
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usEFId;

    /*lint -e534*/
    VOS_MemSet(&stCnfData, 0, sizeof(stCnfData));
    /*lint +e534*/

    stCnfData.ClientId          = gstPBReqUnit.usClientID;

    stCnfData.OpId              = gstPBReqUnit.ucOpID;

    stCnfData.PBError           = TAF_ERR_NO_ERROR;

    stCnfData.PBEventType       = gstPBReqUnit.enPBEventType;

    stCnfData.Storage           = gstPBReqUnit.enPBStoateType;

    ulResult = SI_PB_FindPBOffset(gstPBReqUnit.enPBStoateType, &ucPBOffset);

    if((VOS_OK != ulResult)&&(USIMM_CARDSTATUS_IND != pMsg->ulMsgName))
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;

        return SI_PBCallback(&stCnfData);/*���ûص�����*/
    }

    switch (pMsg->ulMsgName)
    {
        case USIMM_UPDATEFILE_CNF:
            SI_PB_GetEFIDFromPath(&((USIMM_UPDATEFILE_CNF_STRU *)pMsg)->stFilePath, &usEFId);

            if(VOS_OK == SI_PB_CheckSYNCHFileID(usEFId))
            {
                 return VOS_OK;
            }

            if(VOS_OK == SI_PB_CheckExtFileID(usEFId))
            {
                SI_PB_UsimSetExtFileProc((USIMM_UPDATEFILE_CNF_STRU*)pMsg, ucPBOffset);

                return VOS_OK;
            }

            SI_PB_UsimSetFileProc((USIMM_UPDATEFILE_CNF_STRU*)pMsg,ucPBOffset,&stCnfData);

            break;

        case USIMM_READFILE_CNF:
            if (SI_PB_EVENT_READ_CNF == stCnfData.PBEventType)
            {
                SI_PB_UsimGetFileProc((USIMM_READFILE_CNF_STRU*)pMsg,ucPBOffset,&stCnfData);
            }
            else
            {
                SI_PB_UsimSearchFileProc((USIMM_READFILE_CNF_STRU*)pMsg,ucPBOffset,&stCnfData);
            }

            SI_PB_UsimGetIndexFile(ucPBOffset, &stCnfData);

            break;

        case USIMM_SETMUTILFILE_CNF:
            SI_PB_UsimSetSPBFileProc((USIMM_SETMUTILFILE_CNF_STRU *)pMsg,&stCnfData,ucPBOffset);
            break;

        default:
            PB_WARNING_LOG("SI_PBUsimCnfMsgProc:Msg Name is unknow");
            return VOS_ERR;
    }

    return SI_PBCallback(&stCnfData);/*���ûص�����*/
}

/*****************************************************************************
�� �� ��  : SI_PBUsimMsgProc
��������  : ����ǰUSIMM���غ��ϱ���������Ϣ
�������  : ��Ϣ����
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2007��10��15��
    ��    ��   :
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 SI_PBUsimMsgProc(PBMsgBlock *pMsg)
{
    VOS_UINT32                   ulResult;
    USIMM_CARDSTATUS_IND_STRU   *pStStatusMsg;

    /* ��Refresh��������л����յ�ECC������ϱ�����Ҫ���� */
    if (USIMM_ECCNUMBER_IND == pMsg->ulMsgName)
    {
        /* ���֮ǰ��������ڴ棬�ͷ��ڴ��ֹ�ڴ�й© */
        if(VOS_NULL_PTR != gastPBContent[PB_ECC_CONTENT].pContent)
        {
            /*lint -e534*/
            PB_FREE(gastPBContent[PB_ECC_CONTENT].pContent);
            /*lint +e534*/

            gastPBContent[PB_ECC_CONTENT].pContent = VOS_NULL_PTR;
        }

        ulResult = SI_PB_InitEccProc(pMsg);
    }
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    else if (USIMM_XECCNUMBER_IND == pMsg->ulMsgName)
    {
        /* ���֮ǰ��������ڴ棬�ͷ��ڴ��ֹ�ڴ�й© */
        if(VOS_NULL_PTR != gastPBContent[PB_XECC_CONTENT].pContent)
        {
            /*lint -e534*/
            PB_FREE(gastPBContent[PB_XECC_CONTENT].pContent);
            /*lint +e534*/

            gastPBContent[PB_XECC_CONTENT].pContent = VOS_NULL_PTR;
        }

        ulResult = SI_PB_InitXeccProc(pMsg);
    }
#endif
    else if (USIMM_CARDSTATUS_IND == pMsg->ulMsgName)
    {
        pStStatusMsg = (USIMM_CARDSTATUS_IND_STRU *)pMsg;

        if (USIMM_CARD_NOCARD == pStStatusMsg->stUsimSimInfo.enCardType)
        {
            PB_WARNING_LOG("SI_PBUsimMsgProc:Card Absent");

            SI_PB_ReleaseAll();

            SI_PB_InitStatusInd(USIMM_PB_IDLE);
        }

        ulResult = VOS_OK;
    }
    else if (USIMM_STKREFRESH_IND == pMsg->ulMsgName)
    {
        SI_PB_PihRefreshIndProc((USIMM_STKREFRESH_IND_STRU *)pMsg);

        ulResult = VOS_OK;
    }
    else
    {
        ulResult = SI_PBUsimCnfMsgProc(pMsg);
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��      :
��������  :
�������  :
�������  :
�� �� ֵ      :
���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2007��10��15��
    ��    ��   :
    �޸�����   : Creat

*****************************************************************************/

SI_PB_INIT_LIST_STRU    gastPBInitProc[] =
{
    {PB_INIT_PB_STATUS,     SI_PB_InitPBStatusJudge,    SI_PB_InitPBStatusProc},
    {PB_INIT_EFPBR,         SI_PB_InitEFpbrReq,         SI_PB_InitEFpbrProc},
    {PB_INIT_XDN_SPACE,     SI_PB_InitXDNSpaceReq,      SI_PB_InitXDNSpaceMsgProc},
    {PB_INIT_ANR_SPACE,     SI_PB_InitANRSpaceReq,      SI_PB_InitANRSpaceMsgProc},
    {PB_INIT_EML_SPACE,     SI_PB_InitEMLSpaceReq,      SI_PB_InitEMLSpaceMsgProc},
    {PB_INIT_IAP_SPACE,     SI_PB_InitIAPSpaceReq,      SI_PB_InitIAPSpaceMsgProc},
    {PB_INIT_EXT_SPACE,     SI_PB_InitEXTSpaceReq,      SI_PB_InitEXTSpaceMsgProc},
    {PB_INIT_IAP_CONTENT,   SI_PB_InitIAPContentReq,    SI_PB_InitIAPContentMsgProc},
    {PB_INIT_EML_CONTENT,   SI_PB_InitEMLContentReq,    SI_PB_InitEMLContentMsgProc},
    {PB_INIT_ANR_CONTENT,   SI_PB_InitANRContentReq,    SI_PB_InitANRContentMsgProc},
    {PB_INIT_EXTR_CONTENT,  SI_PB_InitEXTRContentReq,   SI_PB_InitEXTRContentMsgProc},
    {PB_INIT_XDN_CONTENT,   SI_PB_InitXDNContentReq,    SI_PB_InitXDNContentMsgProc},
    {PB_INIT_EXT_CONTENT,   SI_PB_InitEXTContentReq,    SI_PB_InitEXTContentMsgProc},
    {PB_INIT_PBC_CONTENT,   SI_PB_InitPBCContentReq,    SI_PB_InitPBCContentMsgProc},
    {PB_INIT_IAP_SEARCH,    SI_PB_InitIAPSearchReq,     SI_PB_InitIAPSearchMsgProc},
    {PB_INIT_IAP_CONTENT2,  SI_PB_InitIAPContentReq2,   SI_PB_InitIAPContentMsgProc2},
    {PB_INIT_EML_SEARCH,    SI_PB_InitEmailSearchReq,   SI_PB_InitEmailSearchMsgProc},
    {PB_INIT_EML_CONTENT2,  SI_PB_InitEmailContentReq,  SI_PB_InitEmailContentMsgProc},
    {PB_INIT_ANR_SEARCH,    SI_PB_InitANRSearchReq,     SI_PB_InitANRSearchMsgProc},
    {PB_INIT_ANR_CONTENT2,  SI_PB_InitANRContentReq2,   SI_PB_InitANRContentMsgProc2},
    {PB_INIT_XDN_SEARCH,    SI_PB_InitXDNSearchReq,     SI_PB_InitXDNSearchMsgProc},
    {PB_INIT_XDN_CONTENT2,  SI_PB_InitXDNContentReq2,   SI_PB_InitXDNContentMsgProc2},
    {PB_INIT_PBC_SEARCH,    SI_PB_InitPBCSearchReq,     SI_PB_InitPBCSearchMsgProc},
    {PB_INIT_PBC_CONTENT2,  SI_PB_InitPBCContentReq2,   SI_PB_InitPBCContentMsgProc2},
    {PB_INIT_SYNCH,         SI_PB_InitSYNCHReq,         SI_PB_InitSYNCHProc},
    {PB_INIT_INFO_APP,      SI_PB_InitInfoApp,          SI_PB_InitInfoAppDebug}
};

VOS_UINT32 SI_PBInitMsgProc (PBMsgBlock *pMsg)
{
    VOS_UINT32 ulResult = VOS_OK;

    switch (pMsg->ulMsgName)
    {
        case USIMM_CARDSTATUS_IND:/*�ⲿ�ִ����д����ۣ���ʱ��ôд*/
        case USIMM_QUERYFILE_CNF:
        case USIMM_READFILE_CNF:
        case USIMM_UPDATEFILE_CNF:
        case USIMM_SEARCHFILE_CNF:
            if (USIMM_CARDSTATUS_IND == pMsg->ulMsgName)
            {
                gstPBInitState.enPBInitStep = PB_INIT_PB_STATUS;
            }

            gstPBInitState.enReqStatus = PB_REQ_NOT_SEND;

            gastPBInitProc[gstPBInitState.enPBInitStep].pInitProcFun(pMsg);

            SI_PB_InitPBStateProc(gstPBInitState.enPBInitState);

            while( PB_REQ_SEND != gstPBInitState.enReqStatus )
            {
                if ( VOS_OK != gastPBInitProc[gstPBInitState.enPBInitStep].pReqFun())
                {
                    PB_ERROR_LOG("SI_PBInitMsgProc:Send Init Request Error");

                    break;
                }
            }

            break;
        case USIMM_ECCNUMBER_IND:
            ulResult = SI_PB_InitEccProc(pMsg);
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

        case USIMM_XECCNUMBER_IND:

            ulResult = SI_PB_InitXeccProc(pMsg);

            break;
#endif


        case USIMM_STKREFRESH_IND:
            SI_PB_PihRefreshIndProc((USIMM_STKREFRESH_IND_STRU *)pMsg);
            break;

        default:
            break;
    }

    if(VOS_OK !=  ulResult)
    {
        PB_ERROR_LOG("SI_PBInitMsgProc:Process Message Error");
    }

    return ulResult;
}
#endif
VOS_VOID SI_PB_InitGlobeVariable(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&gstPBCtrlInfo,    0, sizeof(gstPBCtrlInfo));

    VOS_MemSet(&gstPBInitState,   0, sizeof(gstPBInitState));
    /*lint +e534*/

#if (OSA_CPU_CCPU == VOS_OSA_CPU)

    if(PB_INITIALISED != gastPBContent[PB_ECC_CONTENT].enInitialState)
    {
        /*lint -e534*/
        VOS_MemSet(&gastPBContent[PB_ECC_CONTENT], 0, sizeof(gastPBContent));
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_MemSet(&gastPBContent[PB_ADN_CONTENT], 0, sizeof(gastPBContent) - sizeof(SI_PB_CONTENT_STRU));
        /*lint +e534*/
    }

    /*lint -e534*/
    VOS_MemSet(&gstPBSearchCtrlInfo, (VOS_CHAR)0xFF, sizeof(SI_PB_SEARCH_CTRL_STRU));
    /*lint +e534*/

    /*��ȡPB������ϢNV��*/
    if(NV_OK != NV_Read(en_NV_Item_Usim_PB_Ctrl_Info,
                        (VOS_VOID*)&gstPBConfigInfo, sizeof(SI_PB_CTRL_INFO_ST)))
    {
        /*��֧�ָ��ϵ绰��*/
        gstPBConfigInfo.ucSPBFlag = 0;

        PB_ERROR_LOG("SI_PB_InitGlobeVariable:Read NV Fail!!");
    }

    if(gstPBConfigInfo.ucAnrMaxNum > SI_PB_ANRMAX)
    {
        gstPBConfigInfo.ucAnrMaxNum = 1;
    }
#endif

    /*lint -e534*/
    VOS_MemSet(&gastEXTContent[0], 0, SI_PB_MAX_NUMBER * sizeof(SI_EXT_CONTENT_STRU));

    VOS_MemSet(&gastANRContent[0], 0, SI_PB_ANRMAX * sizeof(SI_ANR_CONTENT_STRU));

    VOS_MemSet(&gstEMLContent, 0, sizeof(SI_EML_CONTENT_STRU));

    VOS_MemSet(&gstPBReqUnit, 0, sizeof(SI_PB_REQ_UINT_STRU));
    /*lint +e534*/

    SI_PB_MemSet(sizeof(gstPBCtrlInfo.astADNInfo), 0xFF,(VOS_UINT8 *)gstPBCtrlInfo.astADNInfo);

    gstPBCtrlInfo.enPBCurType = SI_PB_STORAGE_SM;

    /*���õ绰�����ͺ����ڻ�����ƫ�ƵĶ�Ӧ��ϵ*/
    gastPBContent[PB_ECC_CONTENT].enPBType         = PB_ECC;

    gastPBContent[PB_ECC_CONTENT].enActiveStatus   = SI_PB_ACTIVE;

    gastPBContent[PB_ADN_CONTENT].enPBType         = PB_ADN;

    gastPBContent[PB_ADN_CONTENT].enActiveStatus   = SI_PB_ACTIVE;

    gastPBContent[PB_FDN_CONTENT].enPBType         = PB_FDN;

    gastPBContent[PB_FDN_CONTENT].enActiveStatus   = SI_PB_ACTIVE;

    gastPBContent[PB_BDN_CONTENT].enPBType         = PB_BDN;

    gastPBContent[PB_BDN_CONTENT].enActiveStatus   = SI_PB_ACTIVE;

    gastPBContent[PB_MSISDN_CONTENT].enPBType       = PB_MISDN;

    gastPBContent[PB_MSISDN_CONTENT].enActiveStatus = SI_PB_ACTIVE;

    gastPBContent[PB_SDN_CONTENT].enPBType          = PB_SDN;

    gastPBContent[PB_SDN_CONTENT].enActiveStatus    = SI_PB_ACTIVE;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    gastPBContent[PB_XECC_CONTENT].enPBType         = PB_XECC;

    gastPBContent[PB_XECC_CONTENT].enActiveStatus   = SI_PB_ACTIVE;
#endif

    return;
}
VOS_UINT32 WuepsPBPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase)
{
    switch (InitPhrase)
    {
        case   VOS_IP_LOAD_CONFIG:
            SI_PB_InitGlobeVariable();
            break;

#if ((OSA_CPU_CCPU == VOS_OSA_CPU)||(VOS_WIN32 == VOS_OS_VER))
		case   VOS_IP_RESTART:
            /*lint -e534*/
            PIH_RegUsimCardStatusIndMsg(MAPS_PB_PID);
            PIH_RegCardRefreshIndMsg(MAPS_PB_PID);
            /*lint +e534*/
            break;
#endif

		default:
            break;
    }
    return VOS_OK;

}



#if (defined(DMT))
SI_PB_PROC_LIST_STRU    gastPBReqProc[] =
{
    {SI_PB_READ_REQ,        SI_PB_ReadProc},        /*��ȡ�绰��*/
    {SI_PB_SEARCH_REQ,      SI_PB_SearchProc},      /*�����绰��*/
    {SI_PB_SREAD_REQ,       SI_PB_SReadProc},       /*��ȡ��չ�绰��*/
    {SI_PB_SET_REQ,         SI_PB_SetProc},         /*���õ�ǰ�绰��*/
    {SI_PB_MODIFY_REQ,      SI_PB_ModifyProc},      /*���ĵ绰��*/
    {SI_PB_DELETE_REQ,      SI_PB_DeleteProc},      /*ɾ���绰��*/
    {SI_PB_QUERY_REQ,       SI_PB_QueryProc},       /*��ѯ��ǰ�绰����Ϣ*/
    {SI_PB_ADD_REQ,         SI_PB_AddProc},         /*��ӵ绰��*/
    {SI_PB_SMODIFY_REQ,     SI_PB_SModifyProc},     /*������չ�绰��*/
    {SI_PB_SADD_REQ,        SI_PB_SAddProc},        /*��ӵ绰��*/
    {SI_PB_FDN_CHECK_REQ,   SI_PB_FDNCheckProc},    /*FDN������*/
    {SI_PB_ECALL_QRY_REQ,   SI_PB_EcallNumberQryProc}, /*ECALL�����ȡ*/
};
#else
#if (OSA_CPU_ACPU == VOS_OSA_CPU)
SI_PB_PROC_LIST_STRU    gastPBReqProc[] =
{
    {SI_PB_READ_REQ,        SI_PB_ReadProc},        /*��ȡ�绰��*/
    {SI_PB_SEARCH_REQ,      SI_PB_SearchProc},      /*�����绰��*/
    {SI_PB_SREAD_REQ,       SI_PB_SReadProc},       /*��ȡ��չ�绰��*/
    {SI_PB_UPDATE_AGOBAL,   SI_PBUpdateAGlobal},    /*ͬ��ȫ�ֱ���*/
    {SI_PB_UPDATE_CURPB,    SI_PBUpdateACurPB},     /*���µ�ǰ�绰������*/
};
#endif    /*(OSA_CPU_ACPU == VOS_OSA_CPU)*/

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
SI_PB_PROC_LIST_STRU    gastPBReqProc[] =
{
    {SI_PB_SET_REQ,         SI_PB_SetProc},         /*���õ�ǰ�绰��*/
    {SI_PB_MODIFY_REQ,      SI_PB_ModifyProc},      /*���ĵ绰��*/
    {SI_PB_DELETE_REQ,      SI_PB_DeleteProc},      /*ɾ���绰��*/
    {SI_PB_QUERY_REQ,       SI_PB_QueryProc},       /*��ѯ��ǰ�绰����Ϣ*/
    {SI_PB_ADD_REQ,         SI_PB_AddProc},         /*��ӵ绰��*/
    {SI_PB_SMODIFY_REQ,     SI_PB_SModifyProc},     /*������չ�绰��*/
    {SI_PB_SADD_REQ,        SI_PB_SAddProc},        /*��ӵ绰��*/
    {SI_PB_FDN_CHECK_REQ,   SI_PB_FDNCheckProc},    /*FDN������*/
    {SI_PB_ECALL_QRY_REQ,   SI_PB_EcallNumberQryProc}, /*ECALL�����ȡ*/
};
#endif    /*(OSA_CPU_CCPU == VOS_OSA_CPU)*/
#endif

VOS_VOID SI_PB_PidMsgProc(struct MsgCB *pstPBMsg)
{
    VOS_UINT32 ulResult = VOS_ERR;
    VOS_UINT32 i;

    /*ֻ��Ccpu�Ŵ����USIMMģ�����Ϣ*/
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    if ((WUEPS_PID_USIM == pstPBMsg->ulSenderPid) || (MAPS_PIH_PID == pstPBMsg->ulSenderPid))
    {
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_2, pstPBMsg->ulSenderPid, MAPS_PB_PID, ((PBMsgBlock*)pstPBMsg)->ulMsgName);

        if(PB_INIT_FINISHED != gstPBInitState.enPBInitStep) /*��ʼ���Ķ��ļ���Ϣ��*/
        {
            ulResult = SI_PBInitMsgProc((PBMsgBlock*)pstPBMsg);
        }
        else
        {
            ulResult = SI_PBUsimMsgProc((PBMsgBlock*)pstPBMsg);
        }

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_2);
    }
    else
#endif
    {
        for(i=0; i<(sizeof(gastPBReqProc)/sizeof(SI_PB_PROC_LIST_STRU)); i++)
        {
            if(gastPBReqProc[i].ulMsgType == ((PBMsgBlock*)pstPBMsg)->ulMsgName)
            {
                ulResult = gastPBReqProc[i].pProcFun((PBMsgBlock*)pstPBMsg); /*�����ⲿ����*/
                break;
            }
        }
    }

    if(VOS_OK !=  ulResult)
    {
        PB_ERROR_LOG("SI_PB_PidMsgProc:Process Message Error");
    }

    return;
}
extern TAF_VOID At_PbCallBackFunc(SI_PB_EVENT_INFO_STRU  *pEvent);

VOS_UINT32 SI_PBCallback(SI_PB_EVENT_INFO_STRU *pstEvent)
{
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    MN_APP_PB_AT_CNF_STRU   *pstMsg; /*���͸�AT����Ϣ*/
#endif

    if(pstEvent->PBError != TAF_ERR_NO_ERROR)
    {
        gstPBReqUnit.enPBLock = PB_UNLOCK;/*����*/
    }
    else if((pstEvent->PBEventType != SI_PB_EVENT_READ_CNF)&&
            (pstEvent->PBEventType != SI_PB_EVENT_SREAD_CNF)&&
            (pstEvent->PBEventType != SI_PB_EVENT_SEARCH_CNF))
    {
        gstPBReqUnit.enPBLock = PB_UNLOCK;/*����*/
    }
    else if(pstEvent->PBLastTag == VOS_TRUE)
    {
        gstPBReqUnit.enPBLock = PB_UNLOCK;/*����*/
    }
    else
    {

    }

#if ((OSA_CPU_ACPU == VOS_OSA_CPU)||(VOS_OS_VER == VOS_WIN32))
    At_PbCallBackFunc(pstEvent);
#endif

#if ((OSA_CPU_CCPU == VOS_OSA_CPU)&&(VOS_OS_VER != VOS_WIN32))
    pstMsg = (MN_APP_PB_AT_CNF_STRU*)VOS_AllocMsg(MAPS_PB_PID,
                                    sizeof(MN_APP_PB_AT_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)  /*ÿ������ʧ�ܻḴλ*/
    {
        return VOS_ERR;
    }

    pstMsg->ulReceiverPid = WUEPS_PID_AT;
    pstMsg->ulMsgId       = PB_AT_EVENT_CNF;

    pstEvent->ClientId = MN_GetRealClientId(pstEvent->ClientId, MAPS_PB_PID);

    /*lint -e534*/
    VOS_MemCpy(&pstMsg->stPBAtEvent, pstEvent, sizeof(SI_PB_EVENT_INFO_STRU));
    /*lint +e534*/

    if(VOS_OK != VOS_SendMsg(MAPS_PB_PID, pstMsg))
    {
        PB_ERROR_LOG("SI_PBCallback:Send AT Msg Error");

        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

#ifdef __cplusplus
  #if __cplusplus
  }
  #endif
#endif

