
#include <osm.h>
#include <gen_msg.h>
#include <ftm.h>
#include <ftm_ct.h>
/*lint -save -e537*/
#include <msp_errno.h>
/*lint -restore*/

/***********************************************************************************
  Prototype       : TDS_PsAppSendMsg
 Description     : PS����APP�Ľӿڣ����ڴ�DSP����TDSά��ԭ��(ATʵ��, PS����)
 Input           : ulLen ��Ϣ���� (�������ݲ�����48�ֽ�)
 Output          : None.
 Return Value    : �ɹ�:0, ʧ��:����ֵ
 History         :
************************************************************************************/

VOS_UINT32 TDS_PsAtSendMsg(VOS_UINT32 ulLen, TDS_AT_PS_MSG_INFO_STRU *pstTdsAppPsMsg)
{
    if((0 == ulLen) || (NULL == pstTdsAppPsMsg))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }
/*  return l1a_CtCnf(&pstTdsAppPsMsg->ulMsgId, 12); */
    return ERR_MSP_UNKNOWN;
}

