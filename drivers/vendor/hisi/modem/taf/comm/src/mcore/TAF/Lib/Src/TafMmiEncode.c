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

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "v_typdef.h"
#include "TafTypeDef.h"
#include "TafAppSsa.h"
#include "MnMsgTs.h"
#include "Taf_MmiStrParse.h"
#include "TafMmiEncode.h"
#include "TafStdlib.h"
#include "NasStkInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
  2 ��������
*****************************************************************************/
#define THIS_FILE_ID                PS_FILE_ID_TAF_MMIENCODE_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
 ������    : g_stTafSsaEncodeProcFunc
 �ṹ˵��  : ��Ϣ���Ӧ��������ӳ���
             usMsgType                       - ���������Ϣ���ͣ�
             TAF_MmiEncodeRegisterMmiString  - ���봦����

  1.��    ��   : 2013��05��06��
    ��    ��   : ��ӳ��/62575
    �޸�����   : SS FDN&Call Control
*****************************************************************************/
TAF_MMI_ENCODE_PROC_FUNC_STRU           g_astTafMmiEncodeSsProcFunc[] = {
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_REGISTERSS_MSG),         TAF_MmiEncodeRegisterMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ERASESS_MSG),            TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ACTIVATESS_MSG),         TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_DEACTIVATESS_MSG),       TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_INTERROGATESS_MSG),      TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_REGPWD_MSG),             TAF_MmiEncodeRegisterPwdMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ERASECCENTRY_MSG),       TAF_MmiEncodeEraseCcEntryMmiString},

    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_REGISTERSS_REQ),          TAF_MmiEncodeRegisterMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_ERASESS_REQ),             TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_ACTIVATESS_REQ),          TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_DEACTIVATESS_REQ),        TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_INTERROGATESS_REQ),       TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_REGPWD_REQ),              TAF_MmiEncodeRegisterPwdMmiString},
};

TAF_MMI_OPERATION_TABLE_STRU            g_astTafMmiEventOperationTypeTbl[] = {
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_REGISTERSS_MSG),         TAF_MMI_REGISTER_SS,    {0, 0, 0}},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ERASESS_MSG),            TAF_MMI_ERASE_SS,       {0, 0, 0}},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ACTIVATESS_MSG),         TAF_MMI_ACTIVATE_SS,    {0, 0, 0}},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_DEACTIVATESS_MSG),       TAF_MMI_DEACTIVATE_SS,  {0, 0, 0}},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_INTERROGATESS_MSG),      TAF_MMI_INTERROGATE_SS, {0, 0, 0}},

    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_REGISTERSS_REQ),          TAF_MMI_REGISTER_SS,    {0, 0, 0}},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_ERASESS_REQ),             TAF_MMI_ERASE_SS,       {0, 0, 0}},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_ACTIVATESS_REQ),          TAF_MMI_ACTIVATE_SS,    {0, 0, 0}},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_DEACTIVATESS_REQ),        TAF_MMI_DEACTIVATE_SS,  {0, 0, 0}},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_INTERROGATESS_REQ),       TAF_MMI_INTERROGATE_SS, {0, 0, 0}},
};

/* ASCII to ��ѹ��GSM 7bitת����(��8bit����Ϊ0)��UE�����USSD Request����ת����ѹ��*/
LOCAL VOS_UINT8 g_aucTafMmiDefAsciiToAlphaTbl[] =
{
0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x0A,0x2E,0x2E,0x0D,0x2E,0x2E,
0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
0x20,0x21,0x22,0x23,0x02,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
0x00,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x28,0x2F,0x29,0x2E,0x2D,
0x2F,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x21,0x2F,0x29,0x2D,0x2E
};

/*lint -save -e958 */

/*****************************************************************************
  5 ����ʵ��
*****************************************************************************/



VOS_UINT32 TAF_MmiGetEventOperationTypeTblSize(VOS_VOID)
{
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astTafMmiEventOperationTypeTbl) / sizeof(g_astTafMmiEventOperationTypeTbl[0]);

    return ulTblSize;
}


TAF_MMI_OPERATION_TABLE_STRU *TAF_MmiGetEventOperationTypeTblAddr(VOS_VOID)
{
    return g_astTafMmiEventOperationTypeTbl;
}


VOS_UINT8*   TAF_MmiGetCurrAsciiToAlphaTableAddr(VOS_VOID)
{
    return g_aucTafMmiDefAsciiToAlphaTbl;
}


VOS_UINT32 TAF_MmiGetOperationType(
    VOS_UINT32                          ulEventType,
    MN_MMI_OPERATION_TYPE_ENUM_U8      *penSsOpType
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    TAF_MMI_OPERATION_TABLE_STRU       *pstEventOperationType = VOS_NULL_PTR;

    /* ��ȡ�¼���Ӧ�Ĳ������� */
    ulTableSize           = TAF_MmiGetEventOperationTypeTblSize();
    pstEventOperationType = TAF_MmiGetEventOperationTypeTblAddr();

    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if (ulEventType == pstEventOperationType->ulEventType)
        {
            *penSsOpType = pstEventOperationType->enSsOpType;
            return VOS_TRUE;
        }

        pstEventOperationType++;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_MmiEncodeOperationTypeString(
    VOS_UINT32                          ulEventType,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enSsOpType;
    MN_MMI_SS_OP_Tbl_STRU              *pstOperationType      = VOS_NULL_PTR;

    /* ��ȡ�¼���Ӧ�Ĳ������� */
    ulRet = TAF_MmiGetOperationType(ulEventType, &enSsOpType);

    /* ��ȡҵ���������ʧ�ܣ����ر���ʧ�� */
    if (VOS_FALSE == ulRet)
    {

        return VOS_FALSE;
    }


    /* ��ȡ����ҵ����������ַ��� */
    ulTableSize       = MMI_GetOporationTypeTblSize();
    pstOperationType  = MMI_GetOporationTypeTblAddr();
    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if (enSsOpType == pstOperationType->enSsOpType)
        {
            *pulLength = VOS_StrLen((VOS_CHAR *)pstOperationType->pcSsOpStr);
            (VOS_VOID)VOS_StrNCpy((VOS_CHAR *)pcOutMmiStr,
                        (VOS_CHAR *)pstOperationType->pcSsOpStr,
                        *pulLength);
            return VOS_TRUE;
        }

        pstOperationType++;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_MmiEncodeBS(
    TAF_SS_BASIC_SERVICE_STRU          *pstBsService,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulBSLength
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    MN_MMI_BS_TABLE_STRU               *pstBsType = VOS_NULL_PTR;

    /* ��ȡBS�ַ��� */
    ulTableSize = MMI_GetBSTblSize();
    pstBsType   = MMI_GetBSTblAddr();

    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if ((pstBsType->ucNetBsCode == pstBsService->BsServiceCode)
         && (pstBsType->ucNetBsType == pstBsService->BsType))
        {
            *pulBSLength = VOS_StrLen((VOS_CHAR *)pstBsType->pcMmiBs);
            (VOS_VOID)VOS_StrNCpy(pcOutMmiStr, pstBsType->pcMmiBs, *pulBSLength);
            return VOS_TRUE;
        }

        pstBsType++;
    }

    /* �����BS����û���ҵ���Ӧ�����Ȼ���سɹ���call control��� */
    *pulBSLength    = 0;
    *pcOutMmiStr    = VOS_NULL_PTR;

    return VOS_TRUE;
}
VOS_UINT32 TAF_MmiEncodeSC(
    TAF_SS_CODE                         ucSsCode,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulScLength
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    MN_MMI_SC_TABLE_STRU               *pstSCType;

    /* ��ȡSC�ַ��� */
    ulTableSize = MMI_GetSCTblSize();
    pstSCType   = MMI_GetSCTblAddr();

    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if (pstSCType->ucNetSc == ucSsCode)
        {
            *pulScLength = VOS_StrLen((VOS_CHAR *)pstSCType->pcMmiSc);
            (VOS_VOID)VOS_StrNCpy(pcOutMmiStr, pstSCType->pcMmiSc, *pulScLength);
            return VOS_TRUE;
        }

        pstSCType++;
    }

    return VOS_FALSE;
}
VOS_VOID TAF_MmiEncodeDN(
    TAF_SS_REGISTERSS_REQ_STRU         *pstRegisterInfo,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulDNLength
)
{
    VOS_UINT32                          ulNumberLength;

    ulNumberLength = VOS_StrLen((VOS_CHAR *)pstRegisterInfo->aucFwdToNum);
    if (ulNumberLength > TAF_SS_MAX_FORWARDED_TO_NUM_LEN)
    {
        ulNumberLength = TAF_SS_MAX_FORWARDED_TO_NUM_LEN;
    }

    (VOS_VOID)VOS_StrNCpy(pcOutMmiStr, (VOS_CHAR *)pstRegisterInfo->aucFwdToNum, ulNumberLength);

    /* ����Ŀ�ĺ�����Ӻ����ַ������*DN�ͳ��� */
    *pulDNLength = ulNumberLength;

    return;
}
VOS_VOID TAF_MmiEncodePW(
    VOS_UINT8                          *pucPassword,
    VOS_UINT32                          ulPasswordLength,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulPWLength
)
{

    /* ���������ַ��� */
    PS_MEM_CPY(pcOutMmiStr, pucPassword, ulPasswordLength);

    *pulPWLength = ulPasswordLength;

    return;
}
VOS_UINT32 TAF_MmiEncodeCfnrTimerLen(
    VOS_UINT8                           ucTime,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulLength
)
{
    return TAF_STD_Itoa(ucTime, pcOutMmiStr, pulLength);
}


VOS_UINT32 TAF_MmiEncodeCcbsIndex(
    VOS_UINT8                           ucCallIndex,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulLength
)
{
    return TAF_STD_Itoa(ucCallIndex, pcOutMmiStr, pulLength);

}


VOS_UINT32 TAF_MmiEncodeRegisterMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pcOutMmiStr
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulStrLength;
    TAF_SS_REGISTERSS_REQ_STRU         *pstRegisterInfo = VOS_NULL_PTR;

    /*
    ֻ�к���ת����Ҫע��������漰����^CMMI,+CCFC
        Supplementary   Service     Service Code    SIA     SIB SIC
    22.082
            CFU                     21              DN      BS   -
            CF Busy                 67              DN      BS   -
            CF No Reply             61              DN      BS   T
            CF Not Reachable        62              DN      BS   -

            all CF                  002             DN      BS   T
            all conditional CF      004             DN      BS   T

    */
    ulPos           = 0;
    pstRegisterInfo = (TAF_SS_REGISTERSS_REQ_STRU *)pPara;

    /* ���ͨ��ע�����ǰ׺: ** */
    ulRet = TAF_MmiEncodeOperationTypeString(ulEventType, pcOutMmiStr, &ulPos);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeRegisterMmiString: invalid usMsgType.");
        return ulRet;
    }

    /* ׷��SC�ַ���: */
    ulRet = TAF_MmiEncodeSC(pstRegisterInfo->SsCode,
                            (pcOutMmiStr + ulPos),
                            &ulStrLength);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeRegisterMmiString: invalid SsCode.");
        return ulRet;
    }
    ulPos += ulStrLength;

    /* ׷��DN�ַ���: *����ת����������Ӻ���    */
    /* �������ҵ���ַ��������* */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    if ((VOS_TRUE == pstRegisterInfo->OP_NumType)
     && (VOS_TRUE == pstRegisterInfo->OP_FwdToNum))
    {
        TAF_MmiEncodeDN(pstRegisterInfo, (pcOutMmiStr + ulPos), &ulStrLength);
        ulPos += ulStrLength;
    }
    else
    {
        return VOS_FALSE;
    }

    /* �����Ӻ����ַ��������뺯��û���ӵ�ַ��Э��Ҳû����ȷ���ӵ�ַ��ʽ��
    ���ṩ */

    /* ������ת�ƻ���æת��û��BS����ʱֱ��׷��#����������û��BSҲҪ���* */
    if ((VOS_FALSE == pstRegisterInfo->OP_BsService)
     && (VOS_FALSE == pstRegisterInfo->OP_NoRepCondTime))
    {
        /* ׷��#  */
        *(pcOutMmiStr + ulPos) = '#';

        return VOS_TRUE;
    }

    /* ׷��BS�ַ���: *BS     */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    if (VOS_TRUE == pstRegisterInfo->OP_BsService)
    {
        ulRet = TAF_MmiEncodeBS(&(pstRegisterInfo->BsService),
                                (pcOutMmiStr + ulPos),
                                &ulStrLength);
        if (VOS_TRUE != ulRet)
        {
            MN_WARN_LOG("TAF_MmiEncodeRegisterMmiString: invalid BS parameter.");
            return ulRet;
        }
        ulPos += ulStrLength;
    }

    /*
    ����ת�ƣ���������ת���Լ���Ӧ��ת����Ҫ�ж�ʱ�������û���Ӧ��ת��
    ׷��T�ַ���: *T */
    if ((TAF_ALL_FORWARDING_SS_CODE == pstRegisterInfo->SsCode)
     || (TAF_ALL_COND_FORWARDING_SS_CODE == pstRegisterInfo->SsCode)
     || (TAF_CFNRY_SS_CODE == pstRegisterInfo->SsCode))
    {
        if (VOS_TRUE != pstRegisterInfo->OP_NoRepCondTime)
        {
            return VOS_FALSE;
        }

        TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

        ulRet = TAF_MmiEncodeCfnrTimerLen(pstRegisterInfo->NoRepCondTime,
                                          (pcOutMmiStr + ulPos),
                                          &ulStrLength);
        if (VOS_TRUE != ulRet)
        {
            MN_WARN_LOG("TAF_MmiEncodeRegisterMmiString: invalid T parameter.");
            return ulRet;
        }

        ulPos += ulStrLength;
    }

    /* ׷��#  */
    *(pcOutMmiStr + ulPos) = '#';

    return VOS_TRUE;
}

/*lint -e438 -e830*/


VOS_UINT32 TAF_MmiEncodeActiveMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pMsg,
    VOS_CHAR                           *pcOutMmiStr
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulStrLength;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enSsOpType;
    TAF_SS_ACTIVATESS_REQ_STRU         *pstActiveInfo = VOS_NULL_PTR;

    /*
    �漰����^CMMI,+CCFC,+CCWA,
    +CLIR,+CLIP,+COLP
    1)����ת�Ƽ��ȥ����Ͳ�ѯ��ɾ��������������ҪDN��T����
      �������BS��������ҪΪDN��������*�����򣬲���д*
    2)��������ҵ�񼤻��ȥ�����ʽ���£���ѯ��������Ҫ����
    22.088
        Supplementary   Service     Service Code    SIA     SIB SIC
            BAOC                    33              PW      BS  -
            BAOIC                   331             PW      BS  -
            BAOIC exc home          332             PW      BS  -
            BAIC                    35              PW      BS  -
            BAIC roaming            351             PW      BS  -

            all Barring Serv.       330             PW      BS  -
            Outg. Barr. Serv.       333             PW      BS
            Inc. Barr. Serv.        353             PW      BS
    3)CCBS��ѯ��������Ҫn����
    22.093
            CCBS                    37              n   See Section 4.5.5               where n=1-5
    4)���еȴ��ļ��ȥ����Ͳ�ѯ
    22.083
            WAIT                    43              BS      -   -
    */
    /* ���ͨ�ü���(*)��ȥ����(#)����ѯ����ǰ׺(*#)��ɾ������ǰ׺(##):  */
    ulPos = 0;
    ulRet = TAF_MmiEncodeOperationTypeString(ulEventType, pcOutMmiStr, &ulPos);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeActiveMmiString: invalid usMsgType.");
        return ulRet;
    }

    pstActiveInfo = (TAF_SS_ACTIVATESS_REQ_STRU *)pMsg;

    /* ׷��SC�ַ���: SC */
    ulRet = TAF_MmiEncodeSC(pstActiveInfo->SsCode,
                            (pcOutMmiStr + ulPos),
                            &ulStrLength);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeActiveMmiString: invalid SC parameter.");
        return ulRet;
    }
    ulPos += ulStrLength;

    if ((VOS_FALSE == pstActiveInfo->OP_Password)
     && (VOS_FALSE == pstActiveInfo->OP_BsService))
    {
        /* ׷��#  */
        *(pcOutMmiStr + ulPos) = '#';
        ulPos                  += sizeof('#');

        return ulRet;
    }

    ulRet = TAF_MmiGetOperationType(ulEventType, &enSsOpType);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeActiveMmiString: operation type.");
        return ulRet;
    }

    /* ׷��PW�ַ���: *PW */
    if ((TAF_ALL_BARRING_SS_CODE == (TAF_SS_CODE_MASK & (pstActiveInfo->SsCode)))
      && ((TAF_MMI_ACTIVATE_SS == enSsOpType)
       || (TAF_MMI_DEACTIVATE_SS == enSsOpType)))
    {
        TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

        if (VOS_TRUE == pstActiveInfo->OP_Password)
        {
            TAF_MmiEncodePW(pstActiveInfo->aucPassword,
                            TAF_SS_MAX_PASSWORD_LEN,
                            (pcOutMmiStr + ulPos),
                            &ulStrLength);

            ulPos += ulStrLength;
        }
    }

    /* ����ת�ƴ���BS����ʱ����ҪΪDN��������* */
    if (TAF_ALL_FORWARDING_SS_CODE == (TAF_SS_CODE_MASK & (pstActiveInfo->SsCode)))
    {
        TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);
    }

    /* ׷��BS�ַ���: *BS     */
    /*  3GPP 22030 6.5.2 Structure of the MMI:
        Where SI is not applicable according to the definition of the supplementary service, then *SI is omitted.
        Where its use is optional, but not selected for a particular call set-up, it may be omitted or entered as an extra *
        if this is necessary to avoid ambiguity of interpretation.
    */
    if (VOS_TRUE == pstActiveInfo->OP_BsService)
    {
        TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

        ulRet = TAF_MmiEncodeBS(&(pstActiveInfo->BsService),
                                (pcOutMmiStr + ulPos),
                                &ulStrLength);

        if (VOS_TRUE != ulRet)
        {
            MN_WARN_LOG("TAF_MmiEncodeActiveMmiString: invalid BS parameter!");

            return ulRet;
        }

        ulPos += ulStrLength;
    }

    /* ׷��#  */
    *(pcOutMmiStr + ulPos) = '#';

    return ulRet;
}
/*lint +e438 +e830*/


VOS_UINT32 TAF_MmiEncodeRegisterPwdMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pMsg,
    VOS_CHAR                           *pcOutMmiStr
)
{
    VOS_UINT32                          ulRet;
    TAF_SS_REGPWD_REQ_STRU             *pstRegisterPwdInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulSCLength;

    /*
       �漰����^CMMI,+CPWD
       ���ע�����������ǰ׺: **03���˴���SsCode��ʾ�������ͣ�
       �����������������ע����Ϣ������ֱ�Ӹ�ֵ**03

    22030 6.5.4 Registration of new password
        * 03 * ZZ * OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
        The UE shall also support the alternative procedure:
        ** 03 * ZZ * OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
        where, for Barring Services, ZZ = 330;
        for a common password for all appropriate services, delete the ZZ, entering:
        * 03 ** OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
        The UE shall also support the alternative procedure:
        ** 03 ** OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
    */
    (VOS_VOID)VOS_StrCpy(pcOutMmiStr, TAF_MMI_REGISTER_PASSWORD);
    ulPos              = VOS_StrLen(TAF_MMI_REGISTER_PASSWORD);

    pstRegisterPwdInfo = (TAF_SS_REGPWD_REQ_STRU *)pMsg;

    /* ׷��SC�ַ���: *SC */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    ulRet = TAF_MmiEncodeSC(pstRegisterPwdInfo->SsCode,
                            (pcOutMmiStr + ulPos),
                            &ulSCLength);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeRegisterPwdMmiString: invalid SC parameter.");
        return ulRet;
    }
    ulPos += ulSCLength;


    /* ׷�Ӿ�PW�ַ���: *OLDPASSWORD    */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    (VOS_VOID)VOS_StrNCpy((VOS_CHAR *)(pcOutMmiStr + ulPos), (VOS_CHAR *)pstRegisterPwdInfo->aucOldPwdStr, TAF_SS_MAX_PASSWORD_LEN);
    ulPos += TAF_SS_MAX_PASSWORD_LEN;

    /* ׷����PW�ַ���: *NEWPASSWORD     */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    (VOS_VOID)VOS_StrNCpy((VOS_CHAR *)(pcOutMmiStr + ulPos), (VOS_CHAR *)pstRegisterPwdInfo->aucNewPwdStr, TAF_SS_MAX_PASSWORD_LEN);
    ulPos += TAF_SS_MAX_PASSWORD_LEN;

    /* ׷����PWȷ���ַ���: *NEWPASSWORD     */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    (VOS_VOID)VOS_StrNCpy((VOS_CHAR *)(pcOutMmiStr + ulPos), (VOS_CHAR *)pstRegisterPwdInfo->aucNewPwdStrCnf, TAF_SS_MAX_PASSWORD_LEN);
    ulPos += TAF_SS_MAX_PASSWORD_LEN;

    /* ׷��#  */
    *(pcOutMmiStr + ulPos) = '#';

    return ulRet;
}
VOS_UINT32 TAF_MmiEncodeEraseCcEntryMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pcOutMmiStr
)
{
    TAF_SS_ERASECC_ENTRY_REQ_STRU      *pstEraseCcEntryInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSCLength;
    VOS_UINT32                          ulIndexLength;

    /*
       �漰����^CMMI
    CCBSȥ����ָ��INDEX��CCBS������ʽ#37*n#
    CCBSȥ����CCBS������ʽ#37#
        Supplementary   Service     Service Code    SIA     SIB SIC
    22.093
            CCBS                    37              n   See Section 4.5.5               where n=1-5
            ��Ϊ����ͨ�õ�ע�ᣬɾ���������ȥ������Ϣ�У����Բ�����ͨ�ýӿڻ�ȡ������
    */
    (VOS_VOID)VOS_StrCpy(pcOutMmiStr, "#");
    ulPos               = VOS_StrLen("#");

    pstEraseCcEntryInfo = (TAF_SS_ERASECC_ENTRY_REQ_STRU *)pPara;

    /* ׷��SC�ַ���: */
    ulRet = TAF_MmiEncodeSC(pstEraseCcEntryInfo->SsCode,
                            (pcOutMmiStr + ulPos),
                            &ulSCLength);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeEraseCcEntryMmiString: invalid SC parameter.");
        return ulRet;
    }
    ulPos += ulSCLength;

    /* ����OP_CcbsIndex��CcbsIndex����*n    */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);
    if (VOS_TRUE == pstEraseCcEntryInfo->OP_CcbsIndex)
    {

        /* ת���������͵�INDEXΪ�ַ����� */
        ulRet = TAF_MmiEncodeCcbsIndex(pstEraseCcEntryInfo->CcbsIndex,
                               (pcOutMmiStr + ulPos),
                               &ulIndexLength);
        if (VOS_TRUE != ulRet)
        {
            MN_WARN_LOG("TAF_MmiEncodeEraseCcEntryMmiString: invalid CcbsIndex.");
            return ulRet;
        }
        ulPos += ulIndexLength;

    }

    /* ׷��#  */
    *(pcOutMmiStr + ulPos) = '#';

    return VOS_TRUE;
}


TAF_MMI_ENCODE_PROC_FUNC_STRU *TAF_MmiEncodeSsProcFuncTblAddr(VOS_VOID)
{
    return g_astTafMmiEncodeSsProcFunc;
}


VOS_UINT32 TAF_MmiEncodeSsProcFuncTblSize(VOS_VOID)
{
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astTafMmiEncodeSsProcFunc) / sizeof(g_astTafMmiEncodeSsProcFunc[0]);

    return ulTblSize;
}


VOS_UINT32 TAF_MmiEncodeMmiString(
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pcOutMmiStr
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulEventType;
    TAF_MMI_ENCODE_PROC_FUNC            pMsgProcFunc = VOS_NULL_PTR;
    TAF_MMI_ENCODE_PROC_FUNC_STRU      *pstMapTbl    = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppReq    = VOS_NULL_PTR;

    /* ��ȡָ����Ϣ����Ϣ������ */
    pstAppReq   = (MN_APP_REQ_MSG_STRU *)pPara;
    ulEventType = TAF_MMI_BuildEventType(pstAppReq->ulSenderPid, pstAppReq->usMsgName);

    /* ��ȡ����������ȡ��LOOPֵ���жϺ���ָ���Ƿ�Ϊ�� */
    ulTableSize = TAF_MmiEncodeSsProcFuncTblSize();
    pstMapTbl   = TAF_MmiEncodeSsProcFuncTblAddr();

    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if (pstMapTbl->ulEventType == ulEventType)
        {
            pMsgProcFunc = pstMapTbl->pMsgProcFunc;
            break;
        }

        pstMapTbl++;
    }

    if (VOS_NULL_PTR == pMsgProcFunc)
    {
        return VOS_FALSE;
    }

    ulRet = pMsgProcFunc(ulEventType, pstAppReq->aucContent, pcOutMmiStr);

    return ulRet;

}



VOS_UINT32 TAF_MmiEncodeUssdMessage (
    TAF_SS_USSD_STRING_STRU            *pstPara
)
{
    VOS_UINT8                           aucTmp[TAF_SS_MAX_UNPARSE_PARA_LEN];
    VOS_UINT32                          ulEncodeLen;
    VOS_UINT8                           aucTemp_buffer[TAF_SS_MAX_UNPARSE_PARA_LEN];
    VOS_UINT32                          i;
    VOS_UINT8                          *pucCurTransTbl = VOS_NULL_PTR;

    PS_MEM_SET(aucTmp, 0 , TAF_SS_MAX_UNPARSE_PARA_LEN);
    PS_MEM_SET(aucTemp_buffer, 0 , TAF_SS_MAX_UNPARSE_PARA_LEN);
    ulEncodeLen = 0;

    /* �ж�������ַ����Ƿ񳬳�,7bit����ʱ�182���ַ� */
    if (pstPara->usCnt > TAF_SS_MAX_USSDSTRING_LEN)
    {
        MN_WARN_LOG("TAF_MmiEncodeUssdMessage: string is too long");
        return VOS_FALSE;
    }

    /* convert from ascii coding into GSM default-alphabet
       coding with 1 char per byte  */
    pucCurTransTbl      = TAF_MmiGetCurrAsciiToAlphaTableAddr();
    for (i = 0; i < pstPara->usCnt; i++)
    {
        aucTemp_buffer[i]   = pucCurTransTbl[pstPara->aucUssdStr[i]];
    }

    /* ѭ���ṹ,ת����7bit���뷽ʽ */
    if (VOS_OK != TAF_STD_Pack7Bit(aucTemp_buffer, pstPara->usCnt, 0, aucTmp, &ulEncodeLen))
    {
        MN_WARN_LOG("TAF_MmiEncodeUssdMessage: TAF_STD_Pack7Bit Error");
    }

    /* �ж��Ƿ���7��λ�Ŀ���,����ж����7��λ�����'0001101' */
    if (TAF_MMI_BITS_PER_SEPTET == (pstPara->usCnt % TAF_MMI_BITS_PER_OCTET))
    {
       aucTmp[ulEncodeLen - 1] = aucTmp[ulEncodeLen - 1] | TAF_MMI_USSD_7BIT_PAD;
    }

    pstPara->usCnt = (VOS_UINT16)ulEncodeLen;
    PS_MEM_CPY(pstPara->aucUssdStr, aucTmp, pstPara->usCnt);

    return VOS_TRUE;
}
/*lint -restore */

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

