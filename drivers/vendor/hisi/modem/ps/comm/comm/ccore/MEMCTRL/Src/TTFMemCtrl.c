


/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "TTFMemCtrl.h"
#include "mdrv.h"
#include "TTFMemInterface.h"
#include "PhyNvDefine.h"
#include "TTFComm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e534*/
/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TTF_MEMCTRL_C

/******************************************************************************
   2 �궨��
******************************************************************************/


/*****************************************************************************
   ��������
*****************************************************************************/

/*****************************************************************************
   ȫ�ֱ�������
*****************************************************************************/
TTF_MEMCTRL_ADDR_STRU                   g_stTtfMemCtrlAddr =
{
    /* stTtfMemCtrlAddrComm */
    {
        /* ucInitFlg */
        VOS_NULL,
        /* aucRsv[3] */
        {VOS_NULL, VOS_NULL, VOS_NULL}
    },
    /* astTtfMemCtrlAddrType */
    {
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        }
    }
};

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )

/* three modems */
#if ( 3 == MULTI_MODEM_NUMBER )
/*  TTF��̬�ڴ�ά��ʵ�� */
TTF_MEM_DYNAMIC_CTRL_ENTITY_STRU        g_stTtfMemDynamicCtrlEntity =
{
    /* ulTtfMemDynamicInitAddrFlag */
    VOS_NULL,
    /* ulMemTotalLen */
    VOS_NULL,
    /* astModelSupport */
    {
        {
            /* enSupportWcdma */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportGsm */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportLte */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportTds */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupport1X */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportEvdo */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* aucRsv */
            {VOS_NULL, VOS_NULL}
        },
        {
            /* enSupportWcdma */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportGsm */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportLte */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportTds */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupport1X */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportEvdo */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* aucRsv */
            {VOS_NULL, VOS_NULL}
        },
        {
            /* enSupportWcdma */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportGsm */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportLte */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportTds */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupport1X */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportEvdo */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* aucRsv */
            {VOS_NULL, VOS_NULL}
        }
    },
    /* astTtfMemAddrType */
    {
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        }
    },
    /* pucTtfMemBaseAddr */
    VOS_NULL_PTR
};

/* two modems */
#else
/*  TTF��̬�ڴ�ά��ʵ�� */
TTF_MEM_DYNAMIC_CTRL_ENTITY_STRU        g_stTtfMemDynamicCtrlEntity =
{
    /* ulTtfMemDynamicInitAddrFlag */
    VOS_NULL,
    /* ulMemTotalLen */
    VOS_NULL,
    /* astModelSupport */
    {
        {
            /* enSupportWcdma */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportGsm */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportLte */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportTds */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupport1X */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportEvdo */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* aucRsv */
            {VOS_NULL, VOS_NULL}
        },
        {
            /* enSupportWcdma */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportGsm */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportLte */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportTds */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupport1X */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportEvdo */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* aucRsv */
            {VOS_NULL, VOS_NULL}
        }
    },
    /* astTtfMemAddrType */
    {
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        }
    },
    /* pucTtfMemBaseAddr */
    VOS_NULL_PTR
};
#endif

/* only one modem */
#else
/*  TTF��̬�ڴ�ά��ʵ�� */
TTF_MEM_DYNAMIC_CTRL_ENTITY_STRU        g_stTtfMemDynamicCtrlEntity =
{
    /* ulTtfMemDynamicInitAddrFlag */
    VOS_NULL,
    /* ulMemTotalLen */
    VOS_NULL,
    /* astModelSupport */
    {
        {
            /* enSupportWcdma */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportGsm */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportLte */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportTds */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupport1X */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportEvdo */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* aucRsv */
            {VOS_NULL, VOS_NULL}
        }
    },
    /* astTtfMemAddrType */
    {
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        }
    },
    /* pucTtfMemBaseAddr */
    VOS_NULL_PTR
};

#endif

/* BBPMSTͷ��TB����Ϣ */
WTTF_MACDL_BBPMST_TB_HEAD_STRU          g_stBbpMstTBHeadInfo = {440, 40};

TTF_MEM_SOLUTION_CFG_NV_STRU            g_stTtfMemSolution;

/* �Ƿ����RxEvm���ԣ�1Ϊ����ģʽ��0Ϊ����ģʽ */
VOS_UINT32                              g_ulWRfRxEVMTestEn = VOS_NO;

/******************************************************************************
   6 ����ʵ��
******************************************************************************/
/*lint -save -e958 */

VOS_VOID TTF_MEMCTRL_ModelSupport(VOS_UINT32 ulPid)
{
    VOS_UINT32                              ulResult;
    PLATAFORM_RAT_CAPABILITY_STRU           stPlatformRat;
    VOS_UINT32                              ulLoop;
    MODEM_ID_ENUM_UINT16                    enModemId = VOS_GetModemIDFromPid(ulPid);

    if (MODEM_ID_BUTT <= enModemId)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MEMCTRL_ModelSupport: Invalid ModemId ", enModemId);
        enModemId = MODEM_ID_0;
    }

    TTF_MEM_SET_SUPPORT_WCDMA(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_NO);
    TTF_MEM_SET_SUPPORT_GSM(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_NO);

    /* Read the NV Config Value */
    ulResult = NV_ReadEx(   enModemId,
                            en_NV_Item_Platform_RAT_CAP,
                            &stPlatformRat,
                            sizeof(PLATAFORM_RAT_CAPABILITY_STRU) );

    /* Read NV Content is Failed , Configed the Vaule By Default Value */
    if ( VOS_OK != ulResult )
    {
        /* ��ȡNVʧ�ܣ�����Ĭ��֧��wcdma���� */
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "read platform RAT capability fail \n");

        TTF_MEM_SET_SUPPORT_WCDMA(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        TTF_MEM_SET_SUPPORT_GSM(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);

        return;
    }

    /* ��Ч�Լ�飬���ƽ̨֧�ֵĽ��뼼������Ϊ0������usRatNum���ڽ��뼼�����ֵ������֧��WCDMA */
    if ((0 == stPlatformRat.usRatNum) || (stPlatformRat.usRatNum > PLATFORM_MAX_RAT_NUM))
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING, "RatNum error! usRatNum: %d \n", stPlatformRat.usRatNum);

        TTF_MEM_SET_SUPPORT_WCDMA(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        TTF_MEM_SET_SUPPORT_GSM(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);

        return;
    }

    /* ����aenRatList, �鿴�Ƿ�֧�� */
    for ( ulLoop = 0; ulLoop < stPlatformRat.usRatNum; ulLoop++ )
    {
        if ( PLATFORM_RAT_WCDMA == stPlatformRat.aenRatList[ulLoop] )
        {
            TTF_MEM_SET_SUPPORT_WCDMA(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        }
        else if ( PLATFORM_RAT_GSM == stPlatformRat.aenRatList[ulLoop] )
        {
            TTF_MEM_SET_SUPPORT_GSM(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        }
        else
        {
            /* pclint */
        }
    }

    return ;
}


VOS_VOID TTF_MEMCTRL_ReadBBPMemConfig(VOS_UINT32 ulPid)
{
    VOS_UINT32                          ulResult;

    if (TTF_MEMCTRL_MODEL_SUPPORT_NO == TTF_MEM_GET_SUPPORT_WCDMA(MODEM_ID_0))
    {
        return ;
    }

    /*Read the NV Config Value*/
    ulResult = NV_ReadEx(   MODEM_ID_0,
                            en_NV_Item_WTTF_MACDL_BBPMST_TB_HEAD_Config,
                            &g_stBbpMstTBHeadInfo,
                            sizeof(WTTF_MACDL_BBPMST_TB_HEAD_STRU));

    /*Read NV Content is Failed , Configed the Vaule By Default Value*/
    if ( VOS_OK != ulResult )
    {
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "read BBPMaster NV TB head config fail!\n");

#if (FEATURE_ON == FEATURE_MMU_MEDIUM)
        g_stBbpMstTBHeadInfo.ulTBHeadNum            = 440;
        g_stBbpMstTBHeadInfo.ulTBHeadReserved       = 40;
#else
        g_stBbpMstTBHeadInfo.ulTBHeadNum            = 220;
        g_stBbpMstTBHeadInfo.ulTBHeadReserved       = 20;
#endif
    }

    return ;

}


VOS_UINT32 TTF_MEMCTRL_ReadNvCfg(TTF_MEM_SOLUTION_CFG_NV_STRU *pstTtfMemSolution)
{
    VOS_UINT32                     ulRet;
    VOS_UINT8                      ucLoop;
    VOS_UINT8                      ucClusterNum;
    VOS_UINT8                      ucClusterLoop;
    TTF_MEM_POOL_CFG_NV_STRU      *pstPoolCfg;

    /*��ȡTTF�ڴ淽��*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_TTF_MEM_SOLUTION_CFG, pstTtfMemSolution , sizeof(TTF_MEM_SOLUTION_CFG_NV_STRU));
    if (NV_OK != ulRet)
    {
        TTF_LOG1(WUEPS_PID_RLC, 0, PS_PRINT_ERROR, "TTF_MemReadNvCfg Fail, Read NV FAIL, Error Code <1>\n", (VOS_INT32)ulRet);
        return PS_FAIL;
    }

    if (TTF_MEM_POOL_ID_BUTT != pstTtfMemSolution->ucPoolCnt)
    {
        TTF_LOG(WUEPS_PID_RLC, 0, PS_PRINT_ERROR, "TTF_MemReadNvCfg Fail, Pool Num Error \n");
        return PS_FAIL;
    }

    /*�����ڴ�ظ�cluster�Ƿ���ȷ*/
    for (ucLoop = 0; ucLoop < pstTtfMemSolution->ucPoolCnt; ucLoop++)
    {
        pstPoolCfg   = &pstTtfMemSolution->astTtfMemPoolCfgInfo[ucLoop];
        ucClusterNum = pstPoolCfg->ucClusterCnt;

        if (ucClusterNum > TTF_MEM_MAX_CLUSTER_NUM)
        {
            TTF_LOG(WUEPS_PID_RLC, 0, PS_PRINT_ERROR, "TTF_MemReadNvCfg Fail, Cluster Num Error \n");
            return PS_FAIL;
        }

        for(ucClusterLoop = 0 ; ucClusterLoop < ucClusterNum ; ucClusterLoop++)
        {
            if (pstPoolCfg->ausBlkSize[ucClusterLoop] > TTF_MEM_BLK_MAX_BYTE_LEN)
            {
                TTF_LOG(WUEPS_PID_RLC, 0, PS_PRINT_ERROR, "TTF_MemReadNvCfg Fail, Memory Size Error \n");
                return PS_FAIL;
            }
        }
    }

    return PS_SUCC;
}


VOS_UINT32 TTF_MEMCTRL_MemNvCfgTotalLength(TTF_MEM_SOLUTION_CFG_NV_STRU *pstTtfMemSolution)
{
    TTF_MEM_POOL_CFG_NV_STRU      *pstPoolCfg;
    VOS_UINT8                 ucLoop;
    VOS_UINT8                 ucClusterNum;
    VOS_UINT8                 ucClusterLoop;
    VOS_UINT32                ulTotalLength = 0;

    /*�����ڴ�ظ�cluster�Ƿ���ȷ*/
    for (ucLoop = 0; ucLoop < pstTtfMemSolution->ucPoolCnt; ucLoop++)
    {
        pstPoolCfg   = &pstTtfMemSolution->astTtfMemPoolCfgInfo[ucLoop];
        ucClusterNum = pstPoolCfg->ucClusterCnt;

        for(ucClusterLoop = 0 ; ucClusterLoop < ucClusterNum ; ucClusterLoop++)
        {
            ulTotalLength += pstPoolCfg->ausBlkSize[ucClusterLoop] * pstPoolCfg->ausBlkCnt[ucClusterLoop];
        }
    }

    return ulTotalLength;
}
VOS_VOID TTF_MemSetDefaultNvCfg(TTF_MEM_SOLUTION_CFG_NV_STRU *pstTtfMemSolution)
{
    const   VOS_UINT8   ucPoolMask  = 0x16;

    pstTtfMemSolution->ucPoolCnt    = TTF_MEM_MAX_POOL_NUM;
    pstTtfMemSolution->ucPoolMask   = ucPoolMask;

    /*DL SHARE*/
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_SHARE].ucClusterCnt  = 0;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_SHARE].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 0;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_SHARE].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 0;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_SHARE].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 0;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_SHARE].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 0;

    /*DL PDU */
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ucClusterCnt  = 4;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 84;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 2304;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 700;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 824;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_2] = 1560;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_2]  = 1800;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_3] = 8200;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_3]  = 15;

    /*UL DATA*/
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ucClusterCnt  = 4;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 164;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 5430;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 628;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 1748;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_2] = 1652;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_2]  = 270;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_3] = 8200;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_3]  = 10;

    /*UL EXT*/
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_EXT].ucClusterCnt  = 0;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_EXT].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 0;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_EXT].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 0;

    /* UL IP PACKET */
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ucClusterCnt  = 3;
#if (SC_CTRL_MOD_6950_SFT == SC_CTRL_MOD)
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 404;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 2500;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 1560;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 1500;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_2] = 1628;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_2]  = 20;
#else
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 404;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 1000;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 1560;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 1000;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_2] = 1628;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_2]  = 20;
#endif

    return;
}
VOS_UINT32 TTF_MEMCTRL_CalcTotalDynamicMemLen(VOS_UINT32 ulTtfInternalMemLength)
{
    VOS_UINT32                           ulDynamicMemLen;

    /* ��ʽ���£�����ͷβ�Լ�BBPMaster��TTF�ڴ��֮���32byteΪ�����ڴ棬���ڼ��TTF�ڴ��Ƿ񱻲�*/
    /*
    *  ------------------------------------------------------
    * |              ͷ�������ֶ�0byte                       |
    *  ------------------------------------------------------
    * |      BbpMaster Head(���֧��Wģ���������ڴ�)         |
    *  ------------------------------------------------------
    * |      BbpMaster Data(���֧��Wģ���������ڴ�)         |
    *  ------------------------------------------------------
    * |                    TTF pool memory                   |
    *  ------------------------------------------------------
    */

    /* ��ʼ�������ڴ�Ϊ0 */
    ulDynamicMemLen = TTF_DYNAMIC_MEM_LEN_ZERO;

    /* Section 1:ͷ������ħ���ֶ� */
    TTF_DYNAMIC_MEM_SET_OFFSETBASE(TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE, ulDynamicMemLen);
    TTF_DYNAMIC_MEM_SET_LEN(TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE, TTF_DYNAMIC_MEM_LEN_ZERO);
    TTF_DYNAMIC_MEM_SET_ATTRIBUTE(TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE, TTF_MEMCTRL_TYPE_EXIST_FLG);
    ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_DYNAMIC_MEM_GET_LEN(TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE));

    /* ÿһ�ν���������32�ֽ�ħ���ֶ� */
    ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_MEM_MAGIC_NUM_LEN);

    /* �����Ƿ�֧��WCDMA��ȷ���Ƿ����BBPMASTER�ڴ� */
    if (TTF_MEMCTRL_MODEL_SUPPORT_YES == TTF_MEM_GET_SUPPORT_WCDMA(MODEM_ID_0))
    {
        /*
        * BBPMaster data������ʼλ�ñ���8�ֽڶ��룬��ΪBBPӲ��Ҫ��
        * �ʽ�BBPMaster��ͷ��������8btyte����
        * BBP Master����������ɣ�ͷ�������ݲ������£�
        *  --------------------------------------------------------------
        * |  BbpMasterHeadLen = ulTBHeadNum * 128(byte)                   |
        *  --------------------------------------------------------------
        * |  BbpMasterDataLen = (ulTBHeadNum-ulTBHeadReserved)*5408(byte) |
        *  --------------------------------------------------------------
        * BBP Head��data 32byte����
        */

        /* Section 2:BBPMaster head */
        TTF_DYNAMIC_MEM_SET_OFFSETBASE(TTF_DYNAMIC_MEM_BBP_MASTER_HEAD_ADDR_TYPE, ulDynamicMemLen);
        TTF_DYNAMIC_MEM_SET_LEN(TTF_DYNAMIC_MEM_BBP_MASTER_HEAD_ADDR_TYPE, WTTF_BBPMST_MAC_TB_HEAD_BUFF_LEN);
        TTF_DYNAMIC_MEM_SET_ATTRIBUTE(TTF_DYNAMIC_MEM_BBP_MASTER_HEAD_ADDR_TYPE, TTF_MEMCTRL_TYPE_EXIST_FLG);
        ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_DYNAMIC_MEM_GET_LEN(TTF_DYNAMIC_MEM_BBP_MASTER_HEAD_ADDR_TYPE));

        /* ÿһ�ν���������32�ֽ�ħ���ֶ� */
        ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_MEM_MAGIC_NUM_LEN);

        /* Section 3:BBPMaster data */
        TTF_DYNAMIC_MEM_SET_OFFSETBASE(TTF_DYNAMIC_MEM_BBP_MASTER_DATA_ADDR_TYPE, ulDynamicMemLen);
        TTF_DYNAMIC_MEM_SET_LEN(TTF_DYNAMIC_MEM_BBP_MASTER_DATA_ADDR_TYPE, WTTF_BBPMST_MAC_TB_DATA_BUFF_LEN);
        TTF_DYNAMIC_MEM_SET_ATTRIBUTE(TTF_DYNAMIC_MEM_BBP_MASTER_DATA_ADDR_TYPE, TTF_MEMCTRL_TYPE_EXIST_FLG);
        ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_DYNAMIC_MEM_GET_LEN(TTF_DYNAMIC_MEM_BBP_MASTER_DATA_ADDR_TYPE));

        /* ÿһ�ν���������32�ֽ�ħ���ֶ� */
        ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_MEM_MAGIC_NUM_LEN);
    }

    /* Section 4:TTF�ڲ�ʹ�õ��ڴ� */
    TTF_DYNAMIC_MEM_SET_OFFSETBASE(TTF_DYNAMIC_MEM_TTF_INTERNAL_ADDR_TYPE, ulDynamicMemLen);
    TTF_DYNAMIC_MEM_SET_LEN(TTF_DYNAMIC_MEM_TTF_INTERNAL_ADDR_TYPE, ulTtfInternalMemLength);
    TTF_DYNAMIC_MEM_SET_ATTRIBUTE(TTF_DYNAMIC_MEM_TTF_INTERNAL_ADDR_TYPE, TTF_MEMCTRL_TYPE_EXIST_FLG);
    ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_DYNAMIC_MEM_GET_LEN(TTF_DYNAMIC_MEM_TTF_INTERNAL_ADDR_TYPE));

    /* ÿһ�ν���������32�ֽ�ħ���ֶ� */
    ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_MEM_MAGIC_NUM_LEN);

    return ulDynamicMemLen;
}


VOS_UINT32 TTF_MEMCTRL_DynamicAddrInit(VOS_UINT32 ulPid)
{
    VOS_UINT32                          ulDynamicTtfMemLen;
    TTF_MEMCTRL_ADDR_TYPE_STRU         *pstTtfMemDynamicAddr;
    VOS_UINT8                          *pucDynamicTtfMemBaseAddr;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMagicDataAddr;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulTtfInternalMemLength;
    UCOM_NV_W_RF_RX_EVM_TEST_STRU       stWRfRxEvmTestMode;

    /* ��ȡÿ��modem֧��ģʽ */
    TTF_MEMCTRL_ModelSupport(ulPid);

    /* ��ʼ������ֻ�ᱻPID��ʼ������˳����� */
    if ( TTF_MEMCTRL_TYPE_INIT_FLG == TTF_MEM_GET_DYNAMIC_INIT_ADDR_FLAG() )
    {
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_DynamicAddrInit, Warning, Dynamic Memory were already initialized!\n");
        return VOS_OK;
    }

    PS_MEM_SET(&stWRfRxEvmTestMode, 0, sizeof(UCOM_NV_W_RF_RX_EVM_TEST_STRU));

    /* ��ȡNV��ȷ���Ƿ���RF RX EVMģʽ */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_W_RF_RX_EVM_TEST, &stWRfRxEvmTestMode , sizeof(UCOM_NV_W_RF_RX_EVM_TEST_STRU));
    if (NV_OK != ulRet)
    {
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_DynamicAddrInit, Warning, Read NV en_NV_Item_W_RF_RX_EVM_TEST Fail!\n");
        stWRfRxEvmTestMode.enRxEvmTestEn = UCOM_NV_RX_EVM_TEST_DISABLE;
    }

    /* ͨ����ȡ��NVȷ���Ƿ����RxEvm���ԣ�1Ϊ����ģʽ��0Ϊ����ģʽ */
    if (UCOM_NV_RX_EVM_TEST_ENABLE == stWRfRxEvmTestMode.enRxEvmTestEn)
    {
        g_ulWRfRxEVMTestEn = VOS_YES;
        return VOS_OK;
    }

    /* ��ȡ�����ļ� */
    ulRet = TTF_MEMCTRL_ReadNvCfg(&g_stTtfMemSolution);
    if (PS_FAIL == ulRet)
    {
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_DynamicAddrInit, Warning, TTF_MEMCTRL_ReadNvCfg FAIL!\n");
        TTF_MemSetDefaultNvCfg(&g_stTtfMemSolution);
    }

    /* TTF CCORE�ڴ�س��� */
    ulTtfInternalMemLength = TTF_MEMCTRL_MemNvCfgTotalLength(&g_stTtfMemSolution);

    /* TTF�ڲ�ʹ�õ��ڴ棬����HDLC,CICOM,BBPMASTER CIRCLE,ACORE POOL,CCORE POOL */
    ulTtfInternalMemLength += (TTF_HDLC_MASTER_LINK_TOTAL_LEN + TTF_PARA_MEM_TOTAL_LEN + TTF_BBPMST_BUFF_TOTAL_LEN + TTF_ACORE_POOL_MEM_TOTAL_LEN);

    /* 64K���� */
    ulTtfInternalMemLength = (ulTtfInternalMemLength + ((1UL << 16) - 1)) & (~((1UL << 16) - 1));

    /* ��ʼ��BBPMaster������ */
    TTF_MEMCTRL_ReadBBPMemConfig(ulPid);

    pstTtfMemDynamicAddr = &TTF_MEM_GET_DYNAMIC_ADDR_TYPE();
    VOS_MemSet(pstTtfMemDynamicAddr, 0, sizeof(TTF_MEMCTRL_ADDR_TYPE_STRU) * TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT);

    /* ����TTF����Ҫ������ڴ��С */
    ulDynamicTtfMemLen = TTF_MEMCTRL_CalcTotalDynamicMemLen(ulTtfInternalMemLength);

    /* ����drv�ṩ�Ľӿڣ�����uncached�ڴ� */
    pucDynamicTtfMemBaseAddr = (VOS_UINT8 *)TTF_UNCACHED_MEM_BSP_ALLOC(ulDynamicTtfMemLen);
    if (VOS_NULL_PTR == pucDynamicTtfMemBaseAddr)
    {
        TTF_LOG4(ulPid, 0, PS_PRINT_WARNING,
                    "TTF_MEMCTRL_DynamicAddrInit, Memory Alloc Fail!!Length:0x%x, SupporWcdma:%d, BbpMaster Head Num:%d, BbpMaster Data Num:%d \r\n",
                    (VOS_INT32)ulDynamicTtfMemLen,
                    (VOS_INT32)TTF_MEM_GET_SUPPORT_WCDMA(MODEM_ID_0),
                    (VOS_INT32)WTTF_BBPMST_MAC_TB_HEAD_NUM,
                    (VOS_INT32)WTTF_BBPMST_MAC_TB_DATA_NUM);

        return VOS_ERR;
    }

    PS_MEM_SET(pucDynamicTtfMemBaseAddr, 0, ulDynamicTtfMemLen);

    TTF_MEM_SET_TTF_BASE_ADDR(pucDynamicTtfMemBaseAddr);

    TTF_MEM_SET_TTF_TOTAL_LEN(ulDynamicTtfMemLen);

    /*
    * ��ʼ��ͷ��32byte�����������ʼ��ħ���֣����ڼ��TTF�ڴ��Ƿ񱻲�
    * ��ǰ���ý�32byte����Ϊ5A5A......5A5A������32byte����0��1�ͱȽ������
    * һ��32byte�ڴ���������ݱ��ȣ��Ǳ��ⲿ�����ݱض�����5A5A....5A5A
    */
    for (ulLoop = TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE; ulLoop < TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT; ulLoop++)
    {
        ulMagicDataAddr = (VOS_UINT32)((VOS_UINT_PTR)TTF_MEM_GET_TTF_BASE_ADDR() + TTF_DYNAMIC_MEM_GET_OFFSETBASE(ulLoop) + TTF_DYNAMIC_MEM_GET_LEN(ulLoop));
        if (TTF_MEMCTRL_TYPE_EXIST_FLG == TTF_DYNAMIC_MEM_GET_ATTRIBUTE(ulLoop))
        {
            VOS_MemSet((VOS_VOID *)(VOS_UINT_PTR)ulMagicDataAddr, TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_LEN);
        }
    }

    TTF_MEM_SET_DYNAMIC_INIT_ADDR_FLAG(TTF_MEMCTRL_TYPE_INIT_FLG);

    return VOS_OK;
}



VOS_UINT32 TTF_MEMCTRL_ReportMemErrorInd( VOS_UINT32 ulPid,
                                                 TTF_DYNAMIC_MEM_ADDR_TYPE_ENUM_UINT32 ulMagicNumFlag,
                                                 VOS_UINT8 *pucMagicNum,
                                                 TTF_MEMCTRL_ADDR_TYPE_STRU *pststTtfMemAddr)
{
    TTF_MEM_ERROR_INFO_IND_STRU                     stTtfMemErrorInfoInd;

    VOS_MemSet(&stTtfMemErrorInfoInd, 0, sizeof(TTF_MEM_ERROR_INFO_IND_STRU));

    stTtfMemErrorInfoInd.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stTtfMemErrorInfoInd.ulSenderPid                = ulPid;
    stTtfMemErrorInfoInd.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stTtfMemErrorInfoInd.ulReceiverPid              = ulPid;
    stTtfMemErrorInfoInd.ulLength                   = (sizeof(TTF_MEM_ERROR_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    stTtfMemErrorInfoInd.usMsgName                  = ID_TRACE_TTF_MEM_ERR_IND;
    stTtfMemErrorInfoInd.ulMagicNumFlag             = ulMagicNumFlag;

    VOS_MemCpy(stTtfMemErrorInfoInd.aulMagicNum, pucMagicNum, TTF_MEM_MAGIC_NUM_LEN);
    VOS_MemCpy(&stTtfMemErrorInfoInd.astTtfMemAddrType[0], pststTtfMemAddr, sizeof(TTF_MEMCTRL_ADDR_TYPE_STRU) * TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT);

    DIAG_TraceReport((VOS_VOID *)&stTtfMemErrorInfoInd);

    return VOS_OK;
}



VOS_VOID TTF_MEMCTRL_CheckMagicNum(TTF_MEMCTRL_CALLBACK_FUNC_FLAG_ENUM_ENUM8 ucCallbackFlag,
                                            VOS_UINT32 ulPid)
{
    const VOS_UINT8                     aucMagicNumValue[32] = {TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE};
    VOS_UINT32                          ulMagicDataAddr;
    VOS_UINT32                          ulLoop;

    if (VOS_FALSE == TTF_MEM_GET_DYNAMIC_INIT_ADDR_FLAG())
    {
        return;
    }

    for (ulLoop = TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE; ulLoop < TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT; ulLoop++)
    {
        /* ��ȡ��̬�ڴ�ͷ��ħ���ֶε�ַ */
        ulMagicDataAddr = (VOS_UINT32)((VOS_UINT_PTR)TTF_MEM_GET_TTF_BASE_ADDR() + TTF_DYNAMIC_MEM_GET_OFFSETBASE(ulLoop) + TTF_DYNAMIC_MEM_GET_LEN(ulLoop));

        if (TTF_MEMCTRL_TYPE_EXIST_FLG == TTF_DYNAMIC_MEM_GET_ATTRIBUTE(ulLoop))
        {
            if (0 != VOS_MemCmp((VOS_VOID *)(VOS_UINT_PTR)ulMagicDataAddr, aucMagicNumValue, TTF_MEM_MAGIC_NUM_LEN))
            {
                if (TTF_MEMCTRL_CALLBACK_FUNC_DRV == ucCallbackFlag)
                {
                   LogPrint1("Section:%d, Magic number value has been changed \r\n", (VOS_INT)ulLoop);
                }
                else
                {
                    TTF_MEMCTRL_ReportMemErrorInd(  ulPid,
                                                    ulLoop,
                                                    (VOS_UINT8 *)((VOS_UINT_PTR)ulMagicDataAddr),
                                                    &TTF_MEM_GET_DYNAMIC_ADDR_TYPE());
                }
            }
        }
    }

    return;
}
VOS_VOID TTF_MEMCTRL_DRVCallbackFunc(VOS_VOID)
{
    TTF_MEMCTRL_CheckMagicNum(TTF_MEMCTRL_CALLBACK_FUNC_DRV, TTF_MEMCTRL_PID_INVAILD);
}



VOS_VOID TTF_MEMCTRL_EnableAdvanceCheck (VOS_VOID)
{
    /* ���ڴ��⺯���ҹ��������л������ϣ������д�ӡ����,���õ���ӿڣ�OSAL_TaskSwitchHookAdd */
    #if 0
    OSAL_TaskSwitchHookAdd((OSAL_FUNCPTR)TTF_MEMCTRL_DRVCallbackFunc);
    #endif
}
VOS_VOID TTF_MEMCTRL_DisableAdvanceCheck(VOS_VOID)
{
    /*ȥ���Ӻ�����OSAL_TaskSwitchHookDel */
    #if 0
    OSAL_TaskSwitchHookDel((OSAL_FUNCPTR)TTF_MEMCTRL_DRVCallbackFunc);
    #endif
}
VOS_VOID TTF_MEMCTRL_CheckTTFDynamicMem(VOS_UINT32 ulPid)
{
    TTF_MEMCTRL_CheckMagicNum(TTF_MEMCTRL_CALLBACK_FUNC_TTF, ulPid);

    return ;
}

/*****************************************************************************
 �� �� ��  : TTF_MEMCTRL_GetTtfInternalMemBaseAddr
 ��������  : ��ȡTTF�ڲ�ʹ�õĻ���ַ������HDLC,CICOM,BBPMASTER CIRCLE,ACORE POOL,CCORE POOL
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��08��6��
    ��    ��   : gebaizhang
    �޸�����   : Created
*****************************************************************************/
VOS_UINT_PTR TTF_MEMCTRL_GetTtfInternalMemBaseAddr(VOS_VOID)
{
    VOS_UINT_PTR           ulBaseAddr;

#if (VOS_WIN32 == VOS_OS_VER)
    BSP_DDR_SECT_QUERY   stQuery;
    BSP_DDR_SECT_INFO    stInfo;

    stQuery.enSectType = BSP_DDR_SECT_TYPE_TTF;
    DRV_GET_FIX_DDR_ADDR(&stQuery, &stInfo);

    ulBaseAddr = (VOS_UINT_PTR)stInfo.pSectPhysAddr;
#else
    ulBaseAddr = (VOS_UINT_PTR)(TTF_MEM_GET_TTF_BASE_ADDR() + TTF_DYNAMIC_MEM_GET_OFFSETBASE(TTF_DYNAMIC_MEM_TTF_INTERNAL_ADDR_TYPE));
#endif

    return ulBaseAddr;
}


VOS_UINT32   TTF_MEMCTRL_GetMemTotalLen(VOS_VOID)
{
    VOS_UINT32                          ulMemTotalLen;

#if (VOS_WIN32 == VOS_OS_VER)
    BSP_DDR_SECT_QUERY                  stQuery;
    BSP_DDR_SECT_INFO                   stInfo;
    signed int                          lRslt;

    stQuery.enSectType = BSP_DDR_SECT_TYPE_TTF;
    stInfo.ulSectSize  = TTF_MEMCTRL_INVAILD_SIZE;

    lRslt = DRV_GET_FIX_DDR_ADDR(&stQuery, &stInfo);

    if (BSP_OK != lRslt)
    {
        stInfo.ulSectSize = TTF_MEMCTRL_INVAILD_SIZE;
    }

    ulMemTotalLen    = stInfo.ulSectSize;
#else
    ulMemTotalLen    = TTF_DYNAMIC_MEM_GET_LEN(TTF_DYNAMIC_MEM_TTF_INTERNAL_ADDR_TYPE);
#endif

    return ulMemTotalLen;
}


VOS_UINT32   TTF_MEMCTRL_AddrInit(VOS_UINT32 ulPid)
{
    VOS_UINT8                           ucTypeLoop;
    VOS_UINT8                           ucTypeLoopOne   = 0;
    VOS_UINT32                          ulTypeOffestLen = 0;
    VOS_UINT32                          ulCCoreTypeLen  = 0;
    VOS_UINT32                          ulMemTotalLen   = 0;

    if (TTF_MEMCTRL_TYPE_INIT_FLG == TTF_MEMCTRL_GET_ADDR_INIT_FLG())
    {
         TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_AddrInit::Addrs were already initialized!\n");
         return 0;
    }

    memset(&g_stTtfMemCtrlAddr, 0, sizeof(TTF_MEMCTRL_ADDR_STRU));

    /* ����TTF�ڲ��ڴ�������͵��ڴ泤�� */
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE, TTF_HDLC_MASTER_LINK_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_CIPHER_MASTER_ADDR_TYPE, TTF_PARA_MEM_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_BBP_MASTER_ADDR_TYPE, TTF_BBPMST_BUFF_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_ACORE_POOL_ADDR_TYPE, TTF_ACORE_POOL_MEM_TOTAL_LEN);

    ulMemTotalLen   = TTF_MEMCTRL_GetMemTotalLen();

    if (TTF_MEMCTRL_INVAILD_SIZE == ulMemTotalLen)
    {
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_AddrInit:ulMemTotalLen is invalid!\n");
        return 0;
    }

    ulCCoreTypeLen  = (ulMemTotalLen - TTF_HDLC_MASTER_LINK_TOTAL_LEN
                        - TTF_PARA_MEM_TOTAL_LEN - TTF_BBPMST_BUFF_TOTAL_LEN - TTF_ACORE_POOL_MEM_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_CCORE_POOL_ADDR_TYPE, ulCCoreTypeLen);


    for (ucTypeLoop = 0; ucTypeLoop < TTF_MEMCTRL_ADDR_TYPE_BUTT; ucTypeLoop++)
    {
        if (0 != TTF_MEMCTRL_GET_TYPE_LEN(ucTypeLoop))
        {
            TTF_MEMCTRL_SET_TYPE_FLG(ucTypeLoop, TTF_MEMCTRL_TYPE_EXIST_FLG);
        }

        ulTypeOffestLen += TTF_MEMCTRL_GET_TYPE_LEN(ucTypeLoop);
        ucTypeLoopOne   =  ucTypeLoop + 1;
        if (ucTypeLoopOne < TTF_MEMCTRL_ADDR_TYPE_BUTT)
        {
            /* TTF ���������ڴ�����ڻ�ַ��ƫ�Ƴ������� */
            TTF_MEMCTRL_SET_TYPE_OFFSET_BASE_LEN(ucTypeLoopOne, ulTypeOffestLen);
        }
    }

    TTF_MEMCTRL_SET_ADDR_INIT_FLG(TTF_MEMCTRL_TYPE_INIT_FLG);

    return 0;
}



VOS_UINT32   TTF_MEMCTRL_ACORE_AddrInit(VOS_UINT32 ulPid)
{
    if (VOS_YES == g_ulWRfRxEVMTestEn)
    {
        return VOS_OK;
    }

    TTF_MEMCTRL_AddrInit(ulPid);

    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_ACORE_POOL_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);

    return VOS_OK;
}



VOS_UINT32   TTF_MEMCTRL_CCORE_AddrInit(VOS_UINT32 ulPid)
{
    if (VOS_YES == g_ulWRfRxEVMTestEn)
    {
        return VOS_OK;
    }

    TTF_MEMCTRL_AddrInit(ulPid);

    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_CIPHER_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_BBP_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_CCORE_POOL_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
#if(FEATURE_ON == FEATURE_PPP)
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
#endif

    return VOS_OK;
}


VOS_UINT32  TTF_MEMCTRL_GetOffsetBaseLen(VOS_UINT32  ulType)
{
    VOS_UINT32                          ulAttribute;

    if (ulType >= TTF_MEMCTRL_ADDR_TYPE_BUTT)
    {
        TTF_LOG1(WUEPS_PID_RLC, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_GetOffsetBaseLen::ulType:%d is invalid!\n", (VOS_INT32)ulType);
        return 0;
    }

    if (TTF_MEMCTRL_TYPE_INIT_FLG != TTF_MEMCTRL_GET_ADDR_INIT_FLG())
    {
        TTF_LOG(WUEPS_PID_RLC, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_GetOffsetBaseLen::addr is not init!\n");
        return 0;
    }

    ulAttribute = TTF_MEMCTRL_GET_TYPE_ATTRIBUTE(ulType);
    if (   (TTF_MEMCTRL_TYPE_EXIST_FLG == (TTF_MEMCTRL_TYPE_EXIST_FLG & ulAttribute))
        && (TTF_MEMCTRL_TYPE_VISIBLE_FLG == (TTF_MEMCTRL_TYPE_VISIBLE_FLG & ulAttribute)))
    {
        return TTF_MEMCTRL_GET_TYPE_OFFSET_BASE_LEN(ulType);
    }

    TTF_LOG2(WUEPS_PID_RLC, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_GetOffsetBaseLen::ulType:%d, ulAttribute:%d is not exist or not visible!\n",
                    (VOS_INT32)ulType, (VOS_INT32)ulAttribute);

    return 0;
}


VOS_UINT_PTR  TTF_MEMCTRL_GetTypeAddr(VOS_UINT_PTR ulAddr, VOS_UINT32 ulType)
{
    VOS_UINT32                          ulOffsetBaseLen;
    VOS_UINT_PTR                        ulTtfMemCtrlTypeAddr;

    if (ulType >= TTF_MEMCTRL_ADDR_TYPE_BUTT)
    {
        TTF_LOG1(WUEPS_PID_RLC, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_GetTypeAddr::ulType:%d is invalid!\n", (VOS_INT32)ulType);
        return 0;
    }

    ulOffsetBaseLen         = TTF_MEMCTRL_GetOffsetBaseLen(ulType);
    ulTtfMemCtrlTypeAddr    = ulAddr + ulOffsetBaseLen;

    return  ulTtfMemCtrlTypeAddr;
}


VOS_VOID TTF_MEMCTRL_AddrPrint(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT_PTR                        ulBaseAddr;

    /* ��̬�ڴ������Ϣ����̬�����ڴ����ַ�Լ��Ƿ�֧��WCDMA */
    vos_printf("Ttf Dynamic Mem Info: Init Flag:%d \tIsSupportWcdma:%d \tBase Addr:0x%x \tTotalLen:0x%x\n",
                TTF_MEM_GET_DYNAMIC_INIT_ADDR_FLAG(),
                TTF_MEM_GET_SUPPORT_WCDMA(MODEM_ID_0),
                (VOS_UINT32)(VOS_UINT_PTR)TTF_MEM_GET_TTF_BASE_ADDR(),
                TTF_MEM_GET_TTF_TOTAL_LEN());

    vos_printf("\nTtf Dynamic Mem Section Info:\n");
    for (ulLoop = TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE; ulLoop < TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT; ulLoop++)
    {
        vos_printf("[Section]:%d \t[Attribute]:%d \t[StartAddr]:0x%-8x \t[Len]:0x%-8x \t[OffsetBaseLen]:0x%-8x\n",
                    ulLoop,
                    TTF_DYNAMIC_MEM_GET_ATTRIBUTE(ulLoop),
                    TTF_MEM_GET_TTF_BASE_ADDR() + TTF_DYNAMIC_MEM_GET_OFFSETBASE(ulLoop),
                    TTF_DYNAMIC_MEM_GET_LEN(ulLoop),
                    TTF_DYNAMIC_MEM_GET_OFFSETBASE(ulLoop));
    }

    ulBaseAddr      = TTF_MEMCTRL_GetTtfInternalMemBaseAddr();

    vos_printf("\nTTF Internal Mem Base Addr:0x%-8x \tInit Flag:%d\n", ulBaseAddr, TTF_MEMCTRL_GET_ADDR_INIT_FLG());

    for (ulLoop = TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE; ulLoop < TTF_MEMCTRL_ADDR_TYPE_BUTT; ulLoop++)
    {
        vos_printf("[Section]:%d \t[Attribute]:%d \t[StartAddr]:0x%-8x \t[Len]:0x%-8x \t[OffsetBaseLen]:0x%-8x\n",
            ulLoop,
            TTF_MEMCTRL_GET_TYPE_ATTRIBUTE(ulLoop),
            TTF_MEMCTRL_GetTypeAddr((TTF_GET_32BYTE_ALIGN_VALUE(ulBaseAddr)), ulLoop),
            TTF_MEMCTRL_GET_TYPE_LEN(ulLoop),
            TTF_MEMCTRL_GET_TYPE_OFFSET_BASE_LEN(ulLoop));
    }

    return;
}
/*lint -restore */
/*lint +e534*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


