

/******************************************************************************
 PROJECT   :
 SUBSYSTEM :
 MODULE    :
 OWNER     :
******************************************************************************/
#include <msp_errno.h>
#include <osm.h>
#include <gen_msg.h>
#include <ftm.h>
#include "LMspLPhyInterface.h"
#include "ftm_ct.h"
#include "msp_nvim.h"
#include "msp_nv_def.h"
#include "msp_nv_id.h"
/*lint -e767*/
#define    THIS_FILE_ID        MSP_FILE_ID_FTM_TDS_CMD_C
/*lint -e767*/

/*lint --e{830,539,525}*/


#if(FEATURE_ON == FEATURE_UE_MODE_TDS)

/* ȫ�ֱ���������У׼�����Ϣ */
FTM_SCALIB_SYSTEM_SETTING_STRU * gst_systemSetting = NULL;
/* ȫ�ֱ���������APCУ׼״̬���� */
FTM_SCALIB_APCOFFSET_SETTING_STRU * g_pstApcoffsetFlag = NULL;
/*lint -save -e762*/
extern VOS_VOID tgl00_99getCurrentCellInfo(FTM_SCELLINFO_STRU * currentCellInfo);
/*lint -restore*/

VOS_UINT32 DHI_getCurrentCellInfo(FTM_SCELLINFO_STRU * currentCellInfo)
{
    if(NULL == currentCellInfo)
    {
        return ERR_MSP_FAILURE;
    }

	tgl00_99getCurrentCellInfo(currentCellInfo);

	return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : atr05_51transAsciiCharIntoHex
 ��������  : ��ASCII���ַ�ת��Ϊ16�������ݣ�ֻʶ����������ĸ��
			 �����ַ������滻Ϊ0xFF
 �������  : VOS_CHAR
 �������  : ��
 �� �� ֵ  : VOS_UINT8
*****************************************************************************/
VOS_UINT8 atr05_51transAsciiCharIntoHex(VOS_CHAR asciiChar)
{
	VOS_UINT8 v_returnVal;

	/*lint -save -e732*/
	if((asciiChar >= '0') && (asciiChar <= '9'))
	{
		v_returnVal = asciiChar - '0';
	}
	else if((asciiChar >= 'a') && (asciiChar <= 'f'))
	{
		v_returnVal = asciiChar - 'W'; /* decimal interger is 87. */
	}
	else if((asciiChar >= 'A') && (asciiChar <= 'F'))
	{
		v_returnVal = asciiChar - '7'; /* decimal interger is 55. */
	}
	/*lint -restore*/
	else
	{
		v_returnVal = 0xFF;
	}

	return v_returnVal;
}

/*****************************************************************************
 �� �� ��  : atr05_72translateAsciiCharIntoTpdu
 ��������  : ��ASCII���ַ�����ת��ΪTPDU����
 �������  : asciiChar        --- ��ת������
			 tpduResult       --- Ŀ������
			 asciiCharLength  --- ASCII���ַ����г���
			 maxOutputDataLen --- ���ת������
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID atr05_72translateAsciiCharIntoTpdu(VOS_CHAR * asciiChar, VOS_UINT8 * tpduResult,
                                           VOS_UINT16 asciiCharLength, VOS_UINT16 maxOutputDataLen)
{
	VOS_UINT16 indexOfAsciiChar = 0;
	VOS_UINT16 indexOfResult = 0;
	VOS_UINT8  v_tempVal1 = 0;
	VOS_UINT8  v_tempVal2 = 0;

	if(asciiCharLength % 2 != 0)
	{
	    asciiCharLength -= 1;
	}

	for(indexOfAsciiChar = 0, indexOfResult = 0;\
		(indexOfAsciiChar < asciiCharLength) && (indexOfResult < maxOutputDataLen);\
		indexOfAsciiChar += 2, indexOfResult++)
	{
	    v_tempVal1 = ATR_MC_ASCII_TO_HEX(asciiChar[indexOfAsciiChar]);
	    v_tempVal2 = ATR_MC_ASCII_TO_HEX(asciiChar[indexOfAsciiChar + 1]);
		/* the TPDU octet content. */
        tpduResult[indexOfResult] = (VOS_UINT8)((VOS_UINT8)((v_tempVal1 & 0x0F) << 4) | (VOS_UINT8)(v_tempVal2 & 0x0F));
    }
}

/*****************************************************************************
 �� �� ��  : SystemDataTdRead
 ��������  : ��ȡTDS���NV��
 �������  : FTM_SCALIB_SYSTEM_SETTING_STRU
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 SystemDataTdRead(FTM_SCALIB_SYSTEM_SETTING_STRU * pstSystemInfo)
{
	VOS_UINT32 ret = ERR_MSP_SUCCESS;
    TDS_NV_PA_POWER_STRU maxPower;

    if(NULL == pstSystemInfo)
    {
        return ERR_MSP_FAILURE;
    }

    (VOS_VOID)MSP_MEMSET(&maxPower, 0x00, sizeof(TDS_NV_PA_POWER_STRU));

    /* band A */
    ret = NVM_Read(NV_ID_TDS_TX_PA_POWER_BAND_A, &maxPower, AT_CALIB_PARAM_APCOFF_MAX);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }
    (VOS_VOID)MSP_MEMCPY((pstSystemInfo->tdsTxPaPowerBand_A), (maxPower.asTxMaxPower), AT_CALIB_PARAM_APCOFF);

    ret = NVM_Read(NV_ID_TDS_TX_APC_COMP_BAND_A, pstSystemInfo->tdsTxApcCompBand_A, AT_CALIB_PARAM_APC);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Read(NV_ID_TDS_TX_APC_FREQ_COMP_BAND_A, pstSystemInfo->tdsTxApcFreqCompBand_A, AT_CALIB_PARAM_APCFREQ);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Read(NV_ID_TDS_RX_AGC_COMP_BAND_A, pstSystemInfo->tdsRxAgcCompBand_A, AT_CALIB_PARAM_AGC);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Read(NV_ID_TDS_RX_AGC_FREQ_COMP_BAND_A, pstSystemInfo->tdsRxAgcFreqCompBand_A, AT_CALIB_PARAM_AGCFREQ);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    /* band E */
    ret = NVM_Read(NV_ID_TDS_TX_PA_POWER_BAND_E, &maxPower, AT_CALIB_PARAM_APCOFF_MAX);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }
    (VOS_VOID)MSP_MEMCPY((pstSystemInfo->tdsTxPaPowerBand_E), (maxPower.asTxMaxPower), AT_CALIB_PARAM_APCOFF);

    ret = NVM_Read(NV_ID_TDS_TX_APC_COMP_BAND_E, pstSystemInfo->tdsTxApcCompBand_E, AT_CALIB_PARAM_APC);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Read(NV_ID_TDS_TX_APC_FREQ_COMP_BAND_E, pstSystemInfo->tdsTxApcFreqCompBand_E, AT_CALIB_PARAM_APCFREQ);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Read(NV_ID_TDS_RX_AGC_COMP_BAND_E, pstSystemInfo->tdsRxAgcCompBand_E, AT_CALIB_PARAM_AGC);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Read(NV_ID_TDS_RX_AGC_FREQ_COMP_BAND_E, pstSystemInfo->tdsRxAgcFreqCompBand_E, AT_CALIB_PARAM_AGCFREQ);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    /* band F */
    ret = NVM_Read(NV_ID_TDS_TX_PA_POWER_BAND_F, &maxPower, AT_CALIB_PARAM_APCOFF_MAX);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }
    (VOS_VOID)MSP_MEMCPY((pstSystemInfo->tdsTxPaPowerBand_F), (maxPower.asTxMaxPower), AT_CALIB_PARAM_APCOFF);

    ret = NVM_Read(NV_ID_TDS_TX_APC_COMP_BAND_F, pstSystemInfo->tdsTxApcCompBand_F, AT_CALIB_PARAM_APC);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Read(NV_ID_TDS_TX_APC_FREQ_COMP_BAND_F, pstSystemInfo->tdsTxApcFreqCompBand_F, AT_CALIB_PARAM_APCFREQ);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Read(NV_ID_TDS_RX_AGC_COMP_BAND_F, pstSystemInfo->tdsRxAgcCompBand_F, AT_CALIB_PARAM_AGC);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Read(NV_ID_TDS_RX_AGC_FREQ_COMP_BAND_F, pstSystemInfo->tdsRxAgcFreqCompBand_F, AT_CALIB_PARAM_AGCFREQ);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    return ret;

}

/*****************************************************************************
 �� �� ��  : SystemDataTdWrite
 ��������  : д��TDS���NV��
 �������  : FTM_SCALIB_SYSTEM_SETTING_STRU
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 SystemDataTdWrite(FTM_SCALIB_SYSTEM_SETTING_STRU * pstSystemInfo)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    TDS_NV_PA_POWER_STRU maxPower;

    if (NULL == pstSystemInfo)
    {
        return ERR_MSP_FAILURE;
    }

    (VOS_VOID)MSP_MEMSET(&maxPower, 0x00, sizeof(TDS_NV_PA_POWER_STRU));

    /* band A */
    (VOS_VOID)MSP_MEMCPY((maxPower.asTxMaxPower), (pstSystemInfo->tdsTxPaPowerBand_A), AT_CALIB_PARAM_APCOFF);
    ret = NVM_Write(NV_ID_TDS_TX_PA_POWER_BAND_A, &maxPower, AT_CALIB_PARAM_APCOFF_MAX);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Write(NV_ID_TDS_TX_APC_COMP_BAND_A, pstSystemInfo->tdsTxApcCompBand_A, AT_CALIB_PARAM_APC);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Write(NV_ID_TDS_TX_APC_FREQ_COMP_BAND_A, pstSystemInfo->tdsTxApcFreqCompBand_A, AT_CALIB_PARAM_APCFREQ);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Write(NV_ID_TDS_RX_AGC_COMP_BAND_A, pstSystemInfo->tdsRxAgcCompBand_A, AT_CALIB_PARAM_AGC);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Write(NV_ID_TDS_RX_AGC_FREQ_COMP_BAND_A, pstSystemInfo->tdsRxAgcFreqCompBand_A, AT_CALIB_PARAM_AGCFREQ);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    /* band E */
    (VOS_VOID)MSP_MEMCPY((maxPower.asTxMaxPower), (pstSystemInfo->tdsTxPaPowerBand_E), AT_CALIB_PARAM_APCOFF);
    ret = NVM_Write(NV_ID_TDS_TX_PA_POWER_BAND_E, &maxPower, AT_CALIB_PARAM_APCOFF_MAX);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Write(NV_ID_TDS_TX_APC_COMP_BAND_E, pstSystemInfo->tdsTxApcCompBand_E, AT_CALIB_PARAM_APC);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Write(NV_ID_TDS_TX_APC_FREQ_COMP_BAND_E, pstSystemInfo->tdsTxApcFreqCompBand_E, AT_CALIB_PARAM_APCFREQ);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Write(NV_ID_TDS_RX_AGC_COMP_BAND_E, pstSystemInfo->tdsRxAgcCompBand_E, AT_CALIB_PARAM_AGC);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Write(NV_ID_TDS_RX_AGC_FREQ_COMP_BAND_E, pstSystemInfo->tdsRxAgcFreqCompBand_E, AT_CALIB_PARAM_AGCFREQ);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    /* band F */
    (VOS_VOID)MSP_MEMCPY((maxPower.asTxMaxPower), (pstSystemInfo->tdsTxPaPowerBand_F), AT_CALIB_PARAM_APCOFF);
    ret = NVM_Write(NV_ID_TDS_TX_PA_POWER_BAND_F, &maxPower, AT_CALIB_PARAM_APCOFF_MAX);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Write(NV_ID_TDS_TX_APC_COMP_BAND_F, pstSystemInfo->tdsTxApcCompBand_F, AT_CALIB_PARAM_APC);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Write(NV_ID_TDS_TX_APC_FREQ_COMP_BAND_F, pstSystemInfo->tdsTxApcFreqCompBand_F, AT_CALIB_PARAM_APCFREQ);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Write(NV_ID_TDS_RX_AGC_COMP_BAND_F, pstSystemInfo->tdsRxAgcCompBand_F, AT_CALIB_PARAM_AGC);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

    ret = NVM_Write(NV_ID_TDS_RX_AGC_FREQ_COMP_BAND_F, pstSystemInfo->tdsRxAgcFreqCompBand_F, AT_CALIB_PARAM_AGCFREQ);
    if(ret != ERR_MSP_SUCCESS)
    {
        return ret;
    }

	return ret;
}
VOS_UINT32 SystemDataTd2Dsp(FTM_SCALIB_SYSTEM_SETTING_STRU * pstSystemInfo)
{
    if(NULL == pstSystemInfo)/* [false alarm]:fortify */
    {
        return ERR_MSP_FAILURE;/* [false alarm]:fortify */
    }

    (VOS_VOID)MSP_MEMCPY((VOS_UINT8 *)(TDS_DHI_BASE_DRR), pstSystemInfo, sizeof(FTM_SCALIB_SYSTEM_SETTING_STRU));/* [false alarm]:fortify */


    return ERR_MSP_SUCCESS;/* [false alarm]:fortify */
}


VOS_UINT32 SetApcflagTd2Dsp(FTM_SCALIB_APCOFFSET_SETTING_STRU * pstSystemInfo)
{
    if(NULL == pstSystemInfo)
    {
        return ERR_MSP_FAILURE;
    }

    /* MSP_MEMCPY((VOS_VOID *)(TDS_DDR_BASE_ADDR + TDS_RFADJUSTPARA_DRR_OFFSET), pstSystemInfo, sizeof(FTM_SCALIB_APCOFFSET_SETTING_STRU));*/

	return ERR_MSP_SUCCESS;
}
VOS_UINT32 SystemDataInit(VOS_UINT32 bandType, VOS_UINT32 dataType)
{
    VOS_UINT32  v_frcId = ERR_MSP_SUCCESS;

    if(NULL == gst_systemSetting)
    {
        gst_systemSetting = (FTM_SCALIB_SYSTEM_SETTING_STRU *)VOS_MemAlloc(MSP_SYS_FTM_PID, (DYNAMIC_MEM_PT), sizeof(FTM_SCALIB_SYSTEM_SETTING_STRU));
        if(NULL == gst_systemSetting)
        {
            return ERR_MSP_NO_MORE_MEMORY;
        }

        (VOS_VOID)MSP_MEMSET(gst_systemSetting, 0x00, sizeof(FTM_SCALIB_SYSTEM_SETTING_STRU));
        v_frcId = SystemDataTdRead(gst_systemSetting);
        if(ERR_MSP_SUCCESS != v_frcId)
        {
            return v_frcId;
        }
    }

    if(NULL == g_pstApcoffsetFlag)
    {
        g_pstApcoffsetFlag = (FTM_SCALIB_APCOFFSET_SETTING_STRU *)VOS_MemAlloc(MSP_SYS_FTM_PID, (DYNAMIC_MEM_PT),sizeof(FTM_SCALIB_APCOFFSET_SETTING_STRU));
        if(NULL == g_pstApcoffsetFlag)
        {
            return ERR_MSP_NO_MORE_MEMORY;
        }

        (VOS_VOID)MSP_MEMSET(g_pstApcoffsetFlag, 0x00, sizeof(FTM_SCALIB_APCOFFSET_SETTING_STRU));
    }

    if(dataType != AT_CALIB_DATA_TYPE_BUTT)
    {
        switch(dataType)
        {
            case AT_CALIB_DATA_TYPE_APCOFFSETFLAG:

                (VOS_VOID)MSP_MEMSET(g_pstApcoffsetFlag, 0x00, sizeof(VOS_UINT16)*2);

                /* set rf tab flag when AFC,AGC,APC */
                gst_systemSetting->tdRfTabFlag1    = 0x5555;
                gst_systemSetting->tdRfTabFlag2    = 0xAAAA;
                gst_systemSetting->tdApcOffsetFlag = 0xDCBA;

                break;

            case AT_CALIB_DATA_TYPE_APCOFFSET:

                if(AT_CALIB_BAND_TYPE_A == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxPaPowerBand_A, 0x00, AT_CALIB_PARAM_APCOFF);
                }
                else if(AT_CALIB_BAND_TYPE_E == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxPaPowerBand_E, 0x00, AT_CALIB_PARAM_APCOFF);
                }
                else if(AT_CALIB_BAND_TYPE_F == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxPaPowerBand_F, 0x00, AT_CALIB_PARAM_APCOFF);
                }
                else
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxPaPowerBand_A, 0x00, AT_CALIB_PARAM_APCOFF);
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxPaPowerBand_E, 0x00, AT_CALIB_PARAM_APCOFF);
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxPaPowerBand_F, 0x00, AT_CALIB_PARAM_APCOFF);
                }

                gst_systemSetting->tdApcOffsetFlag = 0xDCBA;


                break;

            case AT_CALIB_DATA_TYPE_APC:

                if(AT_CALIB_BAND_TYPE_A == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcCompBand_A, 0x00, AT_CALIB_PARAM_APC);
                }
                else if(AT_CALIB_BAND_TYPE_E == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcCompBand_E, 0x00, AT_CALIB_PARAM_APC);
                }
                else if(AT_CALIB_BAND_TYPE_F == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcCompBand_F, 0x00, AT_CALIB_PARAM_APC);
                }
                else
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcCompBand_A, 0x00, AT_CALIB_PARAM_APC);
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcCompBand_E, 0x00, AT_CALIB_PARAM_APC);
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcCompBand_F, 0x00, AT_CALIB_PARAM_APC);
                }

                gst_systemSetting->tdRfTabFlag1 = 0x5555;
                gst_systemSetting->tdRfTabFlag2 = 0xAAAA;

                break;

             case AT_CALIB_DATA_TYPE_APCFREQ:

                if(AT_CALIB_BAND_TYPE_A == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcFreqCompBand_A, 0x00, AT_CALIB_PARAM_APCFREQ);
                }
                else if(AT_CALIB_BAND_TYPE_E == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcFreqCompBand_E, 0x00, AT_CALIB_PARAM_APCFREQ);
                }
                else if(AT_CALIB_BAND_TYPE_F == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcFreqCompBand_F, 0x00, AT_CALIB_PARAM_APCFREQ);
                }
                else
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcFreqCompBand_A, 0x00, AT_CALIB_PARAM_APCFREQ);
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcFreqCompBand_E, 0x00, AT_CALIB_PARAM_APCFREQ);
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcFreqCompBand_F, 0x00, AT_CALIB_PARAM_APCFREQ);
                }

                gst_systemSetting->tdRfTabFlag1 = 0x5555;
                gst_systemSetting->tdRfTabFlag2 = 0xAAAA;

                break;

            case AT_CALIB_DATA_TYPE_AGC:

                if(AT_CALIB_BAND_TYPE_A == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcCompBand_A, 0x00, AT_CALIB_PARAM_AGC);
                }
                else if(AT_CALIB_BAND_TYPE_E == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcCompBand_E, 0x00, AT_CALIB_PARAM_AGC);
                }
                else if(AT_CALIB_BAND_TYPE_F == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcCompBand_F, 0x00, AT_CALIB_PARAM_AGC);
                }
                else
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcCompBand_A, 0x00, AT_CALIB_PARAM_AGC);
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcCompBand_E, 0x00, AT_CALIB_PARAM_AGC);
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcCompBand_F, 0x00, AT_CALIB_PARAM_AGC);
                }

                gst_systemSetting->tdRfTabFlag1 = 0x5555;
                gst_systemSetting->tdRfTabFlag2 = 0xAAAA;
                gst_systemSetting->afcAgcDcFlag = 0xABCD;

                break;

            case AT_CALIB_DATA_TYPE_AGCFREQ:

                if(AT_CALIB_BAND_TYPE_A == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcFreqCompBand_A, 0x00, AT_CALIB_PARAM_AGCFREQ);
                }
                else if(AT_CALIB_BAND_TYPE_E == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcFreqCompBand_E, 0x00, AT_CALIB_PARAM_AGCFREQ);
                }
                else if(AT_CALIB_BAND_TYPE_F == bandType)
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcFreqCompBand_F, 0x00, AT_CALIB_PARAM_AGCFREQ);
                }
                else
                {
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcFreqCompBand_A, 0x00, AT_CALIB_PARAM_AGCFREQ);
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcFreqCompBand_E, 0x00, AT_CALIB_PARAM_AGCFREQ);
                    (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcFreqCompBand_F, 0x00, AT_CALIB_PARAM_AGCFREQ);
                }

                gst_systemSetting->tdRfTabFlag1 = 0x5555;
                gst_systemSetting->tdRfTabFlag2 = 0xAAAA;
                gst_systemSetting->afcAgcDcFlag = 0xABCD;

                break;

            default:

                v_frcId = ERR_MSP_FAILURE;

                break;
        }
    }
    else
    {
        (VOS_VOID)MSP_MEMSET(g_pstApcoffsetFlag,  0x00, sizeof(VOS_UINT16)*2);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxPaPowerBand_A, 0x00, AT_CALIB_PARAM_APCOFF);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxPaPowerBand_E, 0x00, AT_CALIB_PARAM_APCOFF);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxPaPowerBand_F, 0x00, AT_CALIB_PARAM_APCOFF);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcCompBand_A, 0x00, AT_CALIB_PARAM_APC);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcCompBand_E, 0x00, AT_CALIB_PARAM_APC);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcCompBand_F, 0x00, AT_CALIB_PARAM_APC);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcFreqCompBand_A, 0x00, AT_CALIB_PARAM_APCFREQ);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcFreqCompBand_E, 0x00, AT_CALIB_PARAM_APCFREQ);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsTxApcFreqCompBand_F, 0x00, AT_CALIB_PARAM_APCFREQ);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcCompBand_A, 0x00, AT_CALIB_PARAM_AGC);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcCompBand_E, 0x00, AT_CALIB_PARAM_AGC);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcCompBand_F, 0x00, AT_CALIB_PARAM_AGC);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcFreqCompBand_A, 0x00, AT_CALIB_PARAM_AGCFREQ);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcFreqCompBand_E, 0x00, AT_CALIB_PARAM_AGCFREQ);
        (VOS_VOID)MSP_MEMSET(gst_systemSetting->tdsRxAgcFreqCompBand_F, 0x00, AT_CALIB_PARAM_AGCFREQ);
        gst_systemSetting->afcAgcDcFlag     = 0xABCD;
        gst_systemSetting->tdApcOffsetFlag  = 0xDCBA;
        gst_systemSetting->tdRfTabFlag1     = 0x5555;
        gst_systemSetting->tdRfTabFlag2     = 0xAAAA;
    }

    return v_frcId;
}
VOS_VOID StartRFAdjust(VOS_VOID)
{
}


VOS_VOID FinishRFAdjust(VOS_VOID)
{
}


VOS_UINT32 SetApcoffsetFlag(VOS_CHAR * calibData)
{
    VOS_UINT8 a_converArray[sizeof(FTM_SCALIB_APCOFFSET_SETTING_STRU)];

    if(NULL == g_pstApcoffsetFlag || NULL == calibData)
    {
        return ERR_MSP_FAILURE;
    }

    (VOS_VOID)MSP_MEMSET(a_converArray, 0x00, sizeof(FTM_SCALIB_APCOFFSET_SETTING_STRU));

    ATR_MC_ASCII_TO_TPDU(calibData, a_converArray, (VOS_UINT16)VOS_StrLen(calibData), sizeof(FTM_SCALIB_APCOFFSET_SETTING_STRU) * 2 + 1);
    (VOS_VOID)MSP_MEMCPY(g_pstApcoffsetFlag, a_converArray, sizeof(FTM_SCALIB_APCOFFSET_SETTING_STRU));

    return ERR_MSP_SUCCESS;
}


VOS_UINT32 SetCalibParamInBuffer(VOS_UINT32 bandType, VOS_UINT32 dataType, VOS_CHAR * calibData, VOS_UINT16 dataLen)
{
    VOS_UINT8 a_converArray[AT_CALIB_PARAM_APC];

    (VOS_VOID)MSP_MEMSET(a_converArray, 0x00, AT_CALIB_PARAM_APC);

    if(NULL == calibData)
    {
        return ERR_MSP_FAILURE;
    }

    if(dataType == AT_CALIB_DATA_TYPE_BUTT)
    {
        return ERR_MSP_FAILURE;
    }

    switch(dataType)
    {
        case AT_CALIB_DATA_TYPE_APCOFFSETFLAG:

            /* APCOFFSETFLAGֻͨ��SET�������� */
            return ERR_MSP_FAILURE;

        case AT_CALIB_DATA_TYPE_APCOFFSET:

            /* ���ݳ�����󳤶� */
            if(dataLen > AT_CALIB_PARAM_APCOFF*2)
            {
                return ERR_MSP_FAILURE;
            }

            ATR_MC_ASCII_TO_TPDU(calibData, a_converArray, (VOS_UINT16)VOS_StrLen(calibData), AT_CALIB_PARAM_APCOFF * 2 + 1);

            if(AT_CALIB_BAND_TYPE_A == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsTxPaPowerBand_A, a_converArray, AT_CALIB_PARAM_APCOFF);
            }
            else if(AT_CALIB_BAND_TYPE_E == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsTxPaPowerBand_E, a_converArray, AT_CALIB_PARAM_APCOFF);
            }
            else if(AT_CALIB_BAND_TYPE_F == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsTxPaPowerBand_F, a_converArray, AT_CALIB_PARAM_APCOFF);
            }
            else
            {
                return ERR_MSP_FAILURE;
            }

            gst_systemSetting->tdApcOffsetFlag = 0xDCBA;

            break;

        case AT_CALIB_DATA_TYPE_APC:

            /* ���ݳ�����󳤶� */
            if(dataLen > AT_CALIB_PARAM_APC*2)
            {
                return ERR_MSP_FAILURE;
            }

            ATR_MC_ASCII_TO_TPDU(calibData, a_converArray, (VOS_UINT16)VOS_StrLen(calibData), AT_CALIB_PARAM_APC * 2 + 1);

            if(AT_CALIB_BAND_TYPE_A == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsTxApcCompBand_A, a_converArray, AT_CALIB_PARAM_APC);
            }
            else if(AT_CALIB_BAND_TYPE_E == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsTxApcCompBand_E, a_converArray, AT_CALIB_PARAM_APC);
            }
            else if(AT_CALIB_BAND_TYPE_F == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsTxApcCompBand_F, a_converArray, AT_CALIB_PARAM_APC);
            }
            else
            {
                return ERR_MSP_FAILURE;
            }

            gst_systemSetting->tdRfTabFlag1 = 0x5555;
            gst_systemSetting->tdRfTabFlag2 = 0xAAAA;

            break;

         case AT_CALIB_DATA_TYPE_APCFREQ:

            /* ���ݳ�����󳤶� */
            if(dataLen > AT_CALIB_PARAM_APCFREQ*2)
            {
                return ERR_MSP_FAILURE;
            }

            ATR_MC_ASCII_TO_TPDU(calibData, a_converArray, (VOS_UINT16)VOS_StrLen(calibData), AT_CALIB_PARAM_APCFREQ * 2 + 1);

            if(AT_CALIB_BAND_TYPE_A == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsTxApcFreqCompBand_A, a_converArray, AT_CALIB_PARAM_APCFREQ);
            }
            else if(AT_CALIB_BAND_TYPE_E == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsTxApcFreqCompBand_E, a_converArray, AT_CALIB_PARAM_APCFREQ);
            }
            else if(AT_CALIB_BAND_TYPE_F == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsTxApcFreqCompBand_F, a_converArray, AT_CALIB_PARAM_APCFREQ);
            }
            else
            {
                return ERR_MSP_FAILURE;
            }

            gst_systemSetting->tdRfTabFlag1 = 0x5555;
            gst_systemSetting->tdRfTabFlag2 = 0xAAAA;

            break;

        case AT_CALIB_DATA_TYPE_AGC:

            /* ���ݳ�����󳤶� */
            if(dataLen > AT_CALIB_PARAM_AGC*2)
            {
                return ERR_MSP_FAILURE;
            }

            ATR_MC_ASCII_TO_TPDU(calibData, a_converArray, (VOS_UINT16)VOS_StrLen(calibData), AT_CALIB_PARAM_AGC * 2 + 1);

            if(AT_CALIB_BAND_TYPE_A == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsRxAgcCompBand_A, a_converArray, AT_CALIB_PARAM_AGC);
            }
            else if(AT_CALIB_BAND_TYPE_E == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsRxAgcCompBand_E, a_converArray, AT_CALIB_PARAM_AGC);
            }
            else if(AT_CALIB_BAND_TYPE_F == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsRxAgcCompBand_F, a_converArray, AT_CALIB_PARAM_AGC);
            }
            else
            {
                return ERR_MSP_FAILURE;
            }

            gst_systemSetting->tdRfTabFlag1 = 0x5555;
            gst_systemSetting->tdRfTabFlag2 = 0xAAAA;
            gst_systemSetting->afcAgcDcFlag = 0xABCD;

            break;

        case AT_CALIB_DATA_TYPE_AGCFREQ:

            /* ���ݳ�����󳤶� */
            if(dataLen > AT_CALIB_PARAM_AGCFREQ*2)
            {
                return ERR_MSP_FAILURE;
            }

            ATR_MC_ASCII_TO_TPDU(calibData, a_converArray, (VOS_UINT16)VOS_StrLen(calibData), AT_CALIB_PARAM_AGCFREQ * 2 + 1);

            if(AT_CALIB_BAND_TYPE_A == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsRxAgcFreqCompBand_A, a_converArray, AT_CALIB_PARAM_AGCFREQ);
            }
            else if(AT_CALIB_BAND_TYPE_E == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsRxAgcFreqCompBand_E, a_converArray, AT_CALIB_PARAM_AGCFREQ);
            }
            else if(AT_CALIB_BAND_TYPE_F == bandType)
            {
                (VOS_VOID)MSP_MEMCPY(gst_systemSetting->tdsRxAgcFreqCompBand_F, a_converArray, AT_CALIB_PARAM_AGCFREQ);
            }
            else
            {
                return ERR_MSP_FAILURE;
            }

            gst_systemSetting->tdRfTabFlag1 = 0x5555;
            gst_systemSetting->tdRfTabFlag2 = 0xAAAA;
            gst_systemSetting->afcAgcDcFlag = 0xABCD;

            break;

        default:

            return ERR_MSP_FAILURE;

    }

    return ERR_MSP_SUCCESS;
}


VOS_UINT32 SetScalibPara(FTM_SET_SCALIB_REQ_STRU * pstFtmReq, FTM_SET_SCALIB_CNF_STRU * pstCnf)
{
    VOS_UINT32 v_frcId    = ERR_MSP_FAILURE;
    VOS_UINT32 v_opType;
    VOS_UINT32 v_bandType;
    VOS_UINT32 v_dataType;
	/*lint -save -e813*/
    FTM_SCALIB_SYSTEM_SETTING_STRU s_systemSetting;
	/*lint -restore*/
    if(NULL == pstCnf || NULL == pstFtmReq)
    {
        return ERR_MSP_FAILURE;
    }

    v_opType   = pstFtmReq->tds_OpType;
    v_bandType = pstFtmReq->tds_BandType;
    v_dataType = pstFtmReq->tds_DataType;

    /* ������Ϣ�ṹ��ʼ�� */
    pstCnf->tds_OpType   = v_opType;
    pstCnf->tds_BandType = v_bandType;
    pstCnf->tds_DataType = v_dataType;
    (VOS_VOID)MSP_MEMSET(&(pstCnf->systemSetting), 0x00, sizeof(FTM_SCALIB_SYSTEM_SETTING_STRU));
    (VOS_VOID)MSP_MEMSET(&(pstCnf->apcoffsetFlag), 0x00, sizeof(FTM_SCALIB_APCOFFSET_SETTING_STRU));

    switch (v_opType)
	{
        /* ��ʼ������ */
        case AT_CALIB_OP_TYPE_INI:

            v_frcId = SystemDataInit(v_bandType, v_dataType);

			break;

        /* ����д�뻺�� */
        case AT_CALIB_OP_TYPE_CACHE:

            if(gst_systemSetting != NULL)
            {
                if(pstFtmReq->tds_DataLen != 0)
                {
                    v_frcId = SetCalibParamInBuffer(v_bandType, v_dataType, (VOS_CHAR *)pstFtmReq->tds_Data, pstFtmReq->tds_DataLen);
                }
                else
                {
                    /* д��ָ���������ݣ�����Ϊ�� */
                    v_frcId = ERR_MSP_FAILURE;
                }
            }
            else
            {
                /* ��д�뻺��֮ǰ�����ʼ������ */
                return ERR_MSP_FAILURE;
            }

            break;

		/* ���ѻ�������д�빲���ڴ棬��֪ͨDSP��������ʹ�� */
        case AT_CALIB_OP_TYPE_USE:

			if(gst_systemSetting != NULL)
			{
				if(pstFtmReq->tds_DataLen!= 0)
				{
					v_frcId = SetCalibParamInBuffer(v_bandType, v_dataType, (VOS_CHAR *)pstFtmReq->tds_Data, pstFtmReq->tds_DataLen);
				}
                else
                {
                    /* д��ָ���������ݣ�����Ϊ�� */
                    v_frcId = ERR_MSP_FAILURE;
                }

                if(ERR_MSP_SUCCESS != v_frcId)
                {
                    return v_frcId;
                }

				v_frcId = SystemDataTd2Dsp(gst_systemSetting);
			}

			break;

        /* ���ѽ�������д��FLASH���ͷŽ��ջ��� */
        case AT_CALIB_OP_TYPE_SAVE:

            if(gst_systemSetting != NULL)
            {
                /* ���ݲ�Ϊ��ʱ�����Ƚ�����д�뻺�� */
                if(pstFtmReq->tds_DataLen != 0)
                {
                    v_frcId = SetCalibParamInBuffer(v_bandType, v_dataType, (VOS_CHAR *)pstFtmReq->tds_Data, (VOS_UINT16)pstFtmReq->tds_DataLen);
                }

                /* ֻ�в������͵�����£�Ҳ��ѻ�������д��FLASH */
                if((ERR_MSP_SUCCESS != v_frcId) &&
                    ((AT_CALIB_DATA_TYPE_BUTT != v_dataType) || (AT_CALIB_BAND_TYPE_BUTT != v_bandType)))
                {
                    return v_frcId;
                }

                v_frcId = SystemDataTdWrite(gst_systemSetting);
                (VOS_VOID)VOS_MemFree(MSP_SYS_FTM_PID, gst_systemSetting);
                gst_systemSetting = NULL;
                (VOS_VOID)VOS_MemFree(MSP_SYS_FTM_PID, g_pstApcoffsetFlag);
                g_pstApcoffsetFlag = NULL;
            }

            break;

		/* ��ѯ��ǰ������ָ�����͵����� */
        case AT_CALIB_OP_TYPE_GET:

            if(gst_systemSetting != NULL && g_pstApcoffsetFlag != NULL)
            {
				(VOS_VOID)MSP_MEMCPY(&(pstCnf->systemSetting), gst_systemSetting, sizeof(FTM_SCALIB_SYSTEM_SETTING_STRU));
                (VOS_VOID)MSP_MEMCPY(&(pstCnf->apcoffsetFlag), g_pstApcoffsetFlag, sizeof(FTM_SCALIB_APCOFFSET_SETTING_STRU));
                v_frcId = ERR_MSP_SUCCESS;
            }
            else
            {
            }

            break;

		/* ��FLASH�ж�ȡ���� */
		case AT_CALIB_OP_TYPE_READ:

            /* READ�������ܶ�ȡAPCOFFSETFLAG���� */
            if(AT_CALIB_DATA_TYPE_APCOFFSETFLAG == v_dataType)
            {
                return ERR_MSP_FAILURE;
            }

            (VOS_VOID)MSP_MEMSET(&s_systemSetting, 0x00, sizeof(FTM_SCALIB_SYSTEM_SETTING_STRU));
            v_frcId = SystemDataTdRead(&s_systemSetting);

    		if(ERR_MSP_SUCCESS == v_frcId)
			{
                (VOS_VOID)MSP_MEMCPY(&(pstCnf->systemSetting), &s_systemSetting, sizeof(FTM_SCALIB_SYSTEM_SETTING_STRU));
			}
            else
            {
            }

            break;
        /*lint -save -e522 */
        /* ��ʼУ׼ */
        case AT_CALIB_OP_TYPE_BEGIN:

            StartRFAdjust();
            v_frcId = ERR_MSP_SUCCESS;

			break;

        /* ����У׼ */
        case AT_CALIB_OP_TYPE_END:

            FinishRFAdjust();
            v_frcId = ERR_MSP_SUCCESS;

			break;
        /*lint -restore*/

        /* ����DSPУ׼״̬ */
        case AT_CALIB_OP_TYPE_SET:

            /* SET����ֻ֧��APCOFFSETFLAG������ */
            if(AT_CALIB_DATA_TYPE_APCOFFSETFLAG != v_dataType)
            {
                v_frcId = ERR_MSP_INVALID_PARAMETER;
                break;
            }

            /* ���ȼ�� */
            if(0 == pstFtmReq->tds_DataLen || pstFtmReq->tds_DataLen > sizeof(VOS_UINT32)*2)
            {
                v_frcId = ERR_MSP_FAILURE;
                break;
            }

            v_frcId = SetApcoffsetFlag((VOS_CHAR *)pstFtmReq->tds_Data);
            if(ERR_MSP_SUCCESS != v_frcId)
            {
                return v_frcId;
            }

            v_frcId = SetApcflagTd2Dsp(g_pstApcoffsetFlag);

			break;

        default:

            v_frcId = ERR_MSP_FAILURE;

            break;
    }

    return v_frcId;
}



VOS_UINT32 at_ftm_scalibRdFun(VOS_VOID* pParam)
{
    VOS_UINT32 ret                        = ERR_MSP_SUCCESS;
    FTM_RD_SCALIB_CNF_STRU  * pstCnf = NULL;

    pstCnf = (FTM_RD_SCALIB_CNF_STRU *)VOS_MemAlloc(MSP_SYS_FTM_PID, (DYNAMIC_MEM_PT), sizeof(FTM_RD_SCALIB_CNF_STRU));
    
    if (NULL != pstCnf)
    {
        if (NULL == gst_systemSetting)
        {
            pstCnf->ulErrCode = ERR_MSP_FAILURE;
        }
        else
        {
            pstCnf->ulErrCode = ERR_MSP_SUCCESS;
        }
        ret = ftm_SendDataMsg(MSP_SYS_FTM_PID, WUEPS_PID_AT, ID_MSG_FTM_RD_SCALIB_CNF,
            (VOS_UINT32) pstCnf, sizeof(FTM_RD_SCALIB_CNF_STRU));
        (VOS_VOID)VOS_MemFree(MSP_SYS_FTM_PID, pstCnf);
    }
	else
	{
		ret = ERR_MSP_NO_MORE_MEMORY;
	}

    return ret;
}


VOS_UINT32 at_ftm_scalibSetFun(VOS_VOID* pParam)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    FTM_SET_SCALIB_REQ_STRU * pstFtmReq = (FTM_SET_SCALIB_REQ_STRU *)pParam;
	/*lint -save -e813*/
    FTM_SET_SCALIB_CNF_STRU   stCnf     = { 0 };
	/*lint -restore*/

    ret = SetScalibPara(pstFtmReq, &stCnf);
    stCnf.ulErrCode = ret;
    return ftm_SendDataMsg(MSP_SYS_FTM_PID, WUEPS_PID_AT, ID_MSG_FTM_SET_SCALIB_CNF,
                        (VOS_UINT32)&stCnf, sizeof(FTM_SET_SCALIB_CNF_STRU));
}


VOS_UINT32 at_ftm_scellinfoRdFun(VOS_VOID* pParam)
{
    VOS_UINT32 ret                           = ERR_MSP_SUCCESS;
    FTM_RD_SCELLINFO_CNF_STRU  * pstCnf = NULL;

    pstCnf = (FTM_RD_SCELLINFO_CNF_STRU *)VOS_MemAlloc(MSP_SYS_FTM_PID ,(DYNAMIC_MEM_PT), sizeof(FTM_RD_SCELLINFO_CNF_STRU));

    if (NULL != pstCnf)
    {
        (VOS_VOID)MSP_MEMSET(pstCnf, 0x00, sizeof(FTM_RD_SCELLINFO_CNF_STRU));
        ret = DHI_getCurrentCellInfo(&(pstCnf->scellinfoStru));
        pstCnf->ulErrCode = ret;
        ret = ftm_SendDataMsg(MSP_SYS_FTM_PID, WUEPS_PID_AT, ID_MSG_FTM_RD_SCELLINFO_CNF,
            (VOS_UINT32) pstCnf, sizeof(FTM_RD_SCELLINFO_CNF_STRU));
        (VOS_VOID)VOS_MemFree(MSP_SYS_FTM_PID, pstCnf);
    }
	else
	{
		ret = ERR_MSP_NO_MORE_MEMORY;
	}

    return ret;
}
#endif


/*****************************************************************************
 �� �� ��  : at_ftm_cmtm_read
 ��������  : ID_MSG_FTM_RD_TEMPERATURE_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_cmtm_read(VOID* pParam)
{
    VOS_UINT32 ret                           = ERR_MSP_SUCCESS;
    VOS_UINT16 temperature                   =   0;
	/*lint -save -e958 -e550 */
	FTM_RD_TEMPERATURE_CNF_STRU stRdCnf = { 0 };

    ret = (VOS_UINT32)mdrv_hkadc_get_pa_value(&temperature);

    if (ERR_MSP_SUCCESS == ret)
    {
        stRdCnf.ulErrCode     = ERR_MSP_SUCCESS;
        stRdCnf.ulTemperature = (VOS_UINT32)temperature;
    }
    else
    {
        stRdCnf.ulErrCode = ERR_MSP_FAILURE;
    }

    return ftm_comm_send(ID_MSG_FTM_RD_TEMPERATURE_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_TEMPERATURE_CNF_STRU));
    /*lint -restore*/

}

