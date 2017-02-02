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
#include "AtCtx.h"
#include "AtDataProc.h"
#include "AtMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 -e960*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CTX_C
/*lint +e767 +e960*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/***************************AT��ȫ�ֱ����� Begin******************************/
/* AT��������ε�PID��Ӧ��  */
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
AT_MODEM_PID_TAB_STRU                   g_astAtModemPidTab[] =
{
    {I0_WUEPS_PID_USIM,         I1_WUEPS_PID_USIM,          I2_WUEPS_PID_USIM,      0},
    {I0_MAPS_STK_PID,           I1_MAPS_STK_PID,            I2_MAPS_STK_PID,        0},
    {I0_MAPS_PIH_PID,           I1_MAPS_PIH_PID,            I2_MAPS_PIH_PID,        0},
    {I0_MAPS_PB_PID,            I1_MAPS_PB_PID,             I2_MAPS_PB_PID,         0},
    {I0_UEPS_PID_GRM,           I1_UEPS_PID_GRM,            I2_UEPS_PID_GRM,        0},
    {I0_UEPS_PID_DL,            I1_UEPS_PID_DL,             I2_UEPS_PID_DL,         0},
    {I0_UEPS_PID_LL,            I1_UEPS_PID_LL,             I2_UEPS_PID_LL,         0},
    {I0_UEPS_PID_SN,            I1_UEPS_PID_SN,             I2_UEPS_PID_SN,         0},
    {I0_UEPS_PID_GAS,           I1_UEPS_PID_GAS,            I2_UEPS_PID_GAS,        0},
    {I0_WUEPS_PID_MM,           I1_WUEPS_PID_MM,            I2_WUEPS_PID_MM,        0},
    {I0_WUEPS_PID_MMC,          I1_WUEPS_PID_MMC,           I2_WUEPS_PID_MMC,       0},
    {I0_WUEPS_PID_GMM,          I1_WUEPS_PID_GMM,           I2_WUEPS_PID_GMM,       0},
    {I0_WUEPS_PID_MMA,          I1_WUEPS_PID_MMA,           I2_WUEPS_PID_MMA,       0},
    {I0_WUEPS_PID_CC,           I1_WUEPS_PID_CC,            I2_WUEPS_PID_CC,        0},
    {I0_WUEPS_PID_SS,           I1_WUEPS_PID_SS,            I2_WUEPS_PID_SS,        0},
    {I0_WUEPS_PID_TC,           I1_WUEPS_PID_TC,            I2_WUEPS_PID_TC,        0},
    {I0_WUEPS_PID_SMS,          I1_WUEPS_PID_SMS,           I2_WUEPS_PID_SMS,       0},
    {I0_WUEPS_PID_RABM,         I1_WUEPS_PID_RABM,          I2_WUEPS_PID_RABM,      0},
    {I0_WUEPS_PID_SM,           I1_WUEPS_PID_SM,            I2_WUEPS_PID_SM,        0},
    {I0_WUEPS_PID_ADMIN,        I1_WUEPS_PID_ADMIN,         I2_WUEPS_PID_ADMIN,     0},
    {I0_WUEPS_PID_TAF,          I1_WUEPS_PID_TAF,           I2_WUEPS_PID_TAF,       0},
    {I0_WUEPS_PID_VC,           I1_WUEPS_PID_VC,            I2_WUEPS_PID_VC,        0},
    {I0_WUEPS_PID_DRV_AGENT,    I1_WUEPS_PID_DRV_AGENT,     I2_WUEPS_PID_DRV_AGENT, 0},
    {I0_UEPS_PID_MTA,           I1_UEPS_PID_MTA,            I2_UEPS_PID_MTA,        0},
    {I0_DSP_PID_GPHY,           I1_DSP_PID_GPHY,            I2_DSP_PID_GPHY,        0},
    {I0_DSP_PID_SLEEP,          I1_DSP_PID_SLEEP,           I2_DSP_PID_SLEEP,       0},
    {I0_DSP_PID_APM,            I1_DSP_PID_APM,             I2_DSP_PID_APM,         0},
    {I0_WUEPS_PID_SLEEP,        I1_WUEPS_PID_SLEEP,         I2_WUEPS_PID_SLEEP,     0}
};
#endif

/* ATģ�鹫�������� */
AT_COMM_CTX_STRU                        g_stAtCommCtx;

/* ATģ����Modem��ص������� */
AT_MODEM_CTX_STRU                       g_astAtModemCtx[MODEM_ID_BUTT];

/* ATģ����Client��ص������� */
AT_CLIENT_CTX_STRU                      g_astAtClientCtx[AT_MAX_CLIENT_NUM];

/* ATģ�鸴λ��ص������� */
AT_RESET_CTX_STRU                       g_stAtResetCtx;

/***************************AT��ȫ�ֱ����� End******************************/

/*********************************������Ҫ������*************************************/
/* �Ƿ����Ȩ�ޱ�־(����DIAG/SHELL�ڵ�Ȩ��) */
AT_E5_RIGHT_FLAG_ENUM_U32               g_enATE5RightFlag;

/* ���� g_stATDislogPwd �е� DIAG�ڵ�״̬Ҫ���뱸��NV�б�; �����벻�ñ���
   �ʽ� g_stATDislogPwd �е��������, ��ʹ�����е� DIAG ��״̬;
   ���¶���NV��������������  */
VOS_INT8                                g_acATOpwordPwd[AT_OPWORD_PWD_LEN+1];

/* ���ڵ�ǰ�Ƿ���Ȩ�޲���AT�˿� */
AT_RIGHT_OPEN_FLAG_STRU                 g_stAtRightOpenFlg;

/* ʹ�ܽ�ֹSD��ʱ��Ҫ������ */
VOS_INT8                                g_acATE5DissdPwd[AT_DISSD_PWD_LEN+1];

/*���֧����ʾ�ִ�*/
VOS_UINT8                               gaucAtCmdNotSupportStr[AT_NOTSUPPORT_STR_LEN+4];

AT_ABORT_CMD_CTX_STRU                   gstAtAbortCmdCtx;   /* ���ڱ����ϵ���Ϣ */

/*��¼���Ŵ������Ƿ�ʹ�� */
PPP_DIAL_ERR_CODE_ENUM                  gucPppDialErrCodeRpt;

AT_DIAL_CONNECT_DISPLAY_RATE_STRU       g_stDialConnectDisplayRate;

/* UE��������: ����Э��汾������ֵ */
AT_DOWNLINK_RATE_CATEGORY_STRU          g_stAtDlRateCategory;

VOS_UINT8                               ucAtS3          = 13;                   /* <CR> */
VOS_UINT8                               ucAtS4          = 10;                   /* <LF> */
VOS_UINT8                               ucAtS5          = 8;                    /* <DEL> */
VOS_UINT8                               ucAtS6          = 2;                    /* Number of seconds to wait before blind dialling:default value = 2 */
VOS_UINT8                               ucAtS7          = 50;                   /* Number of seconds in which connection must be established or call will be disconnected,
                                                                                   default value = 50(refer to Q)*/

AT_CMEE_TYPE                            gucAtCmeeType;                          /* E5������Ĭ�ϴ����� */

TAF_UINT32                              g_ulSTKFunctionFlag = TAF_FALSE;

/*********************************CC Begin*************************************/
/*********************************CC End*************************************/

/*********************************SMS Begin*************************************/
MN_MSG_CLASS0_TAILOR_U8                 g_enClass0Tailor         = MN_MSG_CLASS0_DEF;
/*********************************SMS End*************************************/

/*********************************NET Begin*************************************/
VOS_UINT16                              g_usReportCregActParaFlg = VOS_FALSE;
CREG_CGREG_CI_RPT_BYTE_ENUM             gucCiRptByte = CREG_CGREG_CI_RPT_TWO_BYTE;

/*********************************NET End*************************************/
#if (FEATURE_ON == FEATURE_LTE)
NVIM_RSRP_CFG_STRU                      g_stRsrpCfg;
NVIM_RSCP_CFG_STRU                      g_stRscpCfg;
NVIM_ECIO_CFG_STRU                      g_stEcioCfg;
#endif

AT_SS_CUSTOMIZE_PARA_STRU               g_stAtSsCustomizePara;

AT_TRACE_MSGID_TAB_STRU                 g_stAtTraceMsgIdTab[AT_CLIENT_ID_BUTT];

AT_CLIENT_CFG_MAP_TAB_STRU              g_astAtClientCfgMapTbl[] =
{
    AT_CLIENT_CFG_ELEMENT(PCUI),
    AT_CLIENT_CFG_ELEMENT(CTRL),
    AT_CLIENT_CFG_ELEMENT(PCUI2),
    AT_CLIENT_CFG_ELEMENT(MODEM),
    AT_CLIENT_CFG_ELEMENT(NDIS),
    AT_CLIENT_CFG_ELEMENT(UART),
#if (FEATURE_ON == FEATURE_AT_HSUART)
    AT_CLIENT_CFG_ELEMENT(HSUART),
#endif
    AT_CLIENT_CFG_ELEMENT(SOCK),
    AT_CLIENT_CFG_ELEMENT(APPSOCK),
#if (FEATURE_ON == FEATURE_AT_HSIC)
    AT_CLIENT_CFG_ELEMENT(HSIC1),
    AT_CLIENT_CFG_ELEMENT(HSIC2),
    AT_CLIENT_CFG_ELEMENT(HSIC3),
    AT_CLIENT_CFG_ELEMENT(HSIC4),
    AT_CLIENT_CFG_ELEMENT(HSIC_MODEM),
    AT_CLIENT_CFG_ELEMENT(MUX1),
    AT_CLIENT_CFG_ELEMENT(MUX2),
    AT_CLIENT_CFG_ELEMENT(MUX3),
    AT_CLIENT_CFG_ELEMENT(MUX4),
    AT_CLIENT_CFG_ELEMENT(MUX5),
    AT_CLIENT_CFG_ELEMENT(MUX6),
    AT_CLIENT_CFG_ELEMENT(MUX7),
    AT_CLIENT_CFG_ELEMENT(MUX8),
#endif
    AT_CLIENT_CFG_ELEMENT(APP),
    AT_CLIENT_CFG_ELEMENT(APP1),
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    AT_CLIENT_CFG_ELEMENT(APP2),
    AT_CLIENT_CFG_ELEMENT(APP3),
    AT_CLIENT_CFG_ELEMENT(APP4),
    AT_CLIENT_CFG_ELEMENT(APP5),
    AT_CLIENT_CFG_ELEMENT(APP6),
    AT_CLIENT_CFG_ELEMENT(APP7),
    AT_CLIENT_CFG_ELEMENT(APP8),
    AT_CLIENT_CFG_ELEMENT(APP9),
    AT_CLIENT_CFG_ELEMENT(APP10),
    AT_CLIENT_CFG_ELEMENT(APP11),
    AT_CLIENT_CFG_ELEMENT(APP12),
    AT_CLIENT_CFG_ELEMENT(APP13),
    AT_CLIENT_CFG_ELEMENT(APP14),
    AT_CLIENT_CFG_ELEMENT(APP15),
    AT_CLIENT_CFG_ELEMENT(APP16),
    AT_CLIENT_CFG_ELEMENT(APP17),
    AT_CLIENT_CFG_ELEMENT(APP18),
    AT_CLIENT_CFG_ELEMENT(APP19),
    AT_CLIENT_CFG_ELEMENT(APP20),
    AT_CLIENT_CFG_ELEMENT(APP21),
    AT_CLIENT_CFG_ELEMENT(APP22),
    AT_CLIENT_CFG_ELEMENT(APP23),
    AT_CLIENT_CFG_ELEMENT(APP24),
    AT_CLIENT_CFG_ELEMENT(APP25),
    AT_CLIENT_CFG_ELEMENT(APP26),
#endif
};

const VOS_UINT8                         g_ucAtClientCfgMapTabLen = AT_ARRAY_SIZE(g_astAtClientCfgMapTbl);

#if ( VOS_WIN32 == VOS_OS_VER )

AT_USIMM_FILE_NUM_TO_ID_STRU g_aenAtSimFileNumToIdTab[]=
{
    {0x6F07, USIMM_GSM_EFIMSI_ID        },
    {0x6F46, USIMM_GSM_EFSPN_ID         },
    {0x6F31, USIMM_GSM_EFHPLMN_ID       },
    {0x6F53, USIMM_GSM_EFLOCIGPRS_ID    },
    {0x6f61, USIMM_GSM_EFOPLMNWACT_ID   },
    {0x6f62, USIMM_GSM_EFHPLMNACT_ID    },
    {0x6F7E, USIMM_GSM_EFLOCI_ID        }
};

VOS_UINT32 g_aenAtSimFileNumToIdTabLen = AT_ARRAY_SIZE(g_aenAtSimFileNumToIdTab);

AT_USIMM_FILE_NUM_TO_ID_STRU g_aenAtUsimFileNumToIdTab[]=
{
    {0x3F00, USIMM_MF_ID                },
    {0x2F00, USIMM_DIR_ID               },
    {0x2FE2, USIMM_ICCID_ID             },
    {0x2F05, USIMM_PL_ID                },
    {0x2F06, USIMM_ARR_ID               },
    {0x7FFF, USIMM_USIM_ID              },
    {0x6F05, USIMM_USIM_EFLI_ID         },
    {0x6F06, USIMM_USIM_EFARR_ID        },
    {0x6F07, USIMM_USIM_EFIMSI_ID       },
    {0x6F08, USIMM_USIM_EFKEYS_ID       },
    {0x6F09, USIMM_USIM_EFKEYSPS_ID     },
    {0x6F2C, USIMM_USIM_EFDCK_ID        },
    {0x6F31, USIMM_USIM_EFHPPLMN_ID     },
    {0x6F32, USIMM_USIM_EFCNL_ID        },
    {0x6F37, USIMM_USIM_EFACMMAX_ID     },
    {0x6F38, USIMM_USIM_EFUST_ID        },
    {0x6F39, USIMM_USIM_EFACM_ID        },
    {0x6F3B, USIMM_USIM_EFFDN_ID        },
    {0x6F3C, USIMM_USIM_EFSMS_ID        },
    {0x6F3E, USIMM_USIM_EFGID1_ID       },
    {0x6F3F, USIMM_USIM_EFGID2_ID       },
    {0x6F40, USIMM_USIM_EFMSISDN_ID     },
    {0x6F41, USIMM_USIM_EFPUCT_ID       },
    {0x6F42, USIMM_USIM_EFSMSP_ID       },
    {0x6F43, USIMM_USIM_EFSMSS_ID       },
    {0x6F45, USIMM_USIM_EFCBMI_ID       },
    {0x6F46, USIMM_USIM_EFSPN_ID        },
    {0x6F47, USIMM_USIM_EFSMSR_ID       },
    {0x6F48, USIMM_USIM_EFCBMID_ID      },
    {0x6F49, USIMM_USIM_EFSDN_ID        },
    {0x6F4B, USIMM_USIM_EFEXT2_ID       },
    {0x6F4C, USIMM_USIM_EFEXT3_ID       },
    {0x6F4D, USIMM_USIM_EFBDN_ID        },
    {0x6F4E, USIMM_USIM_EFEXT5_ID       },
    {0x6F4F, USIMM_USIM_EFCCP2_ID       },
    {0x6F50, USIMM_USIM_EFCBMIR_ID      },
    {0x6F55, USIMM_USIM_EFEXT4_ID       },
    {0x6F56, USIMM_USIM_EFEST_ID        },
    {0x6F57, USIMM_USIM_EFACL_ID        },
    {0x6F58, USIMM_USIM_EFCMI_ID        },
    {0x6F5B, USIMM_USIM_EFSTART_HFN_ID  },
    {0x6F5C, USIMM_USIM_EFTHRESHOL_ID   },
    {0x6F60, USIMM_USIM_EFPLMNWACT_ID   },
    {0x6F61, USIMM_USIM_EFOPLMNWACT_ID  },
    {0x6F62, USIMM_USIM_EFHPLMNwACT_ID  },
    {0x6F73, USIMM_USIM_EFPSLOCI_ID     },
    {0x6F78, USIMM_USIM_EFACC_ID        },
    {0x6F7B, USIMM_USIM_EFFPLMN_ID      },
    {0x6F7E, USIMM_USIM_EFLOCI_ID       },
    {0x6F80, USIMM_USIM_EFICI_ID        },
    {0x6F81, USIMM_USIM_EFOCI_ID        },
    {0x6F82, USIMM_USIM_EFICT_ID        },
    {0x6F83, USIMM_USIM_EFOCT_ID        },
    {0x6FAD, USIMM_USIM_EFAD_ID         },
    {0x6FB1, USIMM_USIM_EFVGCS_ID       },
    {0x6FB2, USIMM_USIM_EFVGCSS_ID      },
    {0x6FB3, USIMM_USIM_EFVBS_ID        },
    {0x6FB4, USIMM_USIM_EFVBSS_ID       },
    {0x6FB5, USIMM_USIM_EFEMLPP_ID      },
    {0x6FB6, USIMM_USIM_EFAAEM_ID       },
    {0x6FB7, USIMM_USIM_EFECC_ID        },
    {0x6FC3, USIMM_USIM_EFHIDDENKEY_ID  },
    {0x6FC4, USIMM_USIM_EFNETPAR_ID     },
    {0x6FC5, USIMM_USIM_EFPNN_ID        },
    {0x6FC6, USIMM_USIM_EFOPL_ID        },
    {0x6FC7, USIMM_USIM_EFMBDN_ID       },
    {0x6FC8, USIMM_USIM_EFEXT6_ID       },
    {0x6FC9, USIMM_USIM_EFMBI_ID        },
    {0x6FCA, USIMM_USIM_EFMWIS_ID       },
    {0x6FCB, USIMM_USIM_EFCFIS_ID       },
    {0x6FCC, USIMM_USIM_EFEXT7_ID       },
    {0x6FCD, USIMM_USIM_EFSPDI_ID       },
    {0x6FCE, USIMM_USIM_EFMMSN_ID       },
    {0x6FCF, USIMM_USIM_EFEXT8_ID       },
    {0x6FD0, USIMM_USIM_EFMMSICP_ID     },
    {0x6FD1, USIMM_USIM_EFMMSUP_ID      },
    {0x6FD2, USIMM_USIM_EFMMSUCP_ID     },
    {0x6FD3, USIMM_USIM_EFNIA_ID        },
    {0x6FD4, USIMM_USIM_EFVGCSCA_ID     },
    {0x6FD5, USIMM_USIM_EFVBSCA_ID      },
    {0x6FD6, USIMM_USIM_EFGBAP_ID       },
    {0x6FD7, USIMM_USIM_EFMSK_ID        },
    {0x6FD8, USIMM_USIM_EFMUK_ID        },
    {0x6FD9, USIMM_USIM_EFEHPLMN_ID     },
    {0x6FDA, USIMM_USIM_EFGBANL_ID      },
    {0x6FDB, USIMM_USIM_EFEHPLMNPI_ID   },
    {0x6FDC, USIMM_USIM_EFLRPLMNSI_ID   },
    {0x6FDD, USIMM_USIM_EFNAFKCA_ID     },
    {0x6FDE, USIMM_USIM_EFSPNI_ID       },
    {0x6FDF, USIMM_USIM_EFPNNI_ID       },
    {0x6FE2, USIMM_USIM_EFNCPIP_ID      },
    {0x6FE3, USIMM_USIM_EFEPSLOCI_ID    },
    {0x6FE4, USIMM_USIM_EFEPSNSC_ID     },
    {0x6FE6, USIMM_USIM_EFUFC_ID        },
    {0x6FE7, USIMM_USIM_EFUICCIARI_ID   },
    {0x6FE8, USIMM_USIM_EFNASCONFIG_ID  },
    {0x6FEC, USIMM_USIM_EFPWS_ID        },
    {0x5F3A, USIMM_USIM_DFPHONEBOOK_ID  },
    {0x4F22, USIMM_USIM_EFPSC_ID        },
    {0x4F23, USIMM_USIM_EFCC_ID         },
    {0x4F24, USIMM_USIM_EFPUID_ID       },
    {0x4F30, USIMM_USIM_EFPBR_ID        },
    {0x5F3B, USIMM_USIM_DFGSM_ACCESS_ID },
    {0x4F20, USIMM_USIM_EFKC_ID         },
    {0x4F52, USIMM_USIM_EFKCGPRS_ID     },
    {0x4F63, USIMM_USIM_EFCPBCCH_ID     },
    {0x4F64, USIMM_USIM_EFINVSCAN_ID    },
    {0x5F3C, USIMM_USIM_DFMEXE_ID       },
    {0x4F40, USIMM_USIM_EFMexE_ST_ID    },
    {0x4F41, USIMM_USIM_EFORPK_ID       },
    {0x4F42, USIMM_USIM_EFARPK_ID       },
    {0x4F43, USIMM_USIM_EFTPRK_ID       },
    {0x5F70, USIMM_USIM_DFSOLSA_ID      },
    {0x4F30, USIMM_USIM_EFSAI_ID        },
    {0x4F31, USIMM_USIM_EFSLL_ID        },
    {0x5F40, USIMM_USIM_DFWLAN_ID       },
    {0x4F41, USIMM_USIM_EFPSEUDO_ID     },
    {0x4F42, USIMM_USIM_EFUPLMNWLAN_ID  },
    {0x4F43, USIMM_USIM_EF0PLMNWLAN_ID  },
    {0x4F44, USIMM_USIM_EFUWSIDL_ID     },
    {0x4F45, USIMM_USIM_EFOWSIDL_ID     },
    {0x4F46, USIMM_USIM_EFWRI_ID        },
    {0x4F47, USIMM_USIM_EFHWSIDL_ID     },
    {0x4F48, USIMM_USIM_EFWEHPLMNPI_ID  },
    {0x4F49, USIMM_USIM_EFWHPI_ID       },
    {0x4F4A, USIMM_USIM_EFWLRPLMN_ID    },
    {0x4F4B, USIMM_USIM_EFHPLMNDAI_ID   },
    {0x5F50, USIMM_USIM_DFHNB_ID        },
    {0x4F81, USIMM_USIM_EFACSGL_ID      },
    {0x4F82, USIMM_USIM_EFCSGT_ID       },
    {0x4F83, USIMM_USIM_EFHNBN_ID       },
    {0x4F84, USIMM_USIM_EFOCSGL_ID      },
    {0x4F85, USIMM_USIM_EFOCSGT_ID      },
    {0x4F86, USIMM_USIM_EFOHNBN_ID      },
    {0X6F30, USIMM_GSM_EFPLMNSEL_ID     },
    {0x6F53, USIMM_GSM_EFLOCIGPRS_ID    },
    {0x6F20, USIMM_GSM_EFKC_ID          },
    {0x6F52, USIMM_GSM_EFKCGPRS_ID      },
    {0x4F34, USIMM_ATTGSM_EFACTINGHPLMN_ID},
    {0x7F66, USIMM_ATTUSIM_ID},
    {0x6FD2, USIMM_ATTUSIM_EFTERMINALTBL_ID},
    {0x4F34, USIMM_ATTUSIM_EFACTINGHPLMN_ID},
    {0x4F36, USIMM_ATTUSIM_EFRATMODE_ID},
    {0x4F40, USIMM_ATTUSIM_EFPRMENABLE_ID},
    {0x4F41, USIMM_ATTUSIM_EFPRMPARA_ID},
    {0x4F42, USIMM_ATTUSIM_EFPRMOMCLR_ID},
    {0x4F43, USIMM_ATTUSIM_EFPRMOMC_ID},
    {0x4F44, USIMM_ATTUSIM_EFPRMVERINFO_ID}
};

VOS_UINT32 g_aenAtUsimFileNumToIdTabLen = AT_ARRAY_SIZE(g_aenAtUsimFileNumToIdTab);
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_VOID AT_InitUsimStatus(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);

    pstUsimInfoCtx->enCardStatus = USIMM_CARD_SERVIC_BUTT;
    pstUsimInfoCtx->enCardType   = USIMM_CARD_TYPE_BUTT;

    pstUsimInfoCtx->ucIMSILen    = 0;
    PS_MEM_SET(pstUsimInfoCtx->aucIMSI, 0, sizeof(pstUsimInfoCtx->aucIMSI));


    return;
}


VOS_VOID AT_InitPlatformRatList(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_SPT_RAT_STRU              *pstSptRat   = VOS_NULL_PTR;

    pstSptRat = AT_GetSptRatFromModemId(enModemId);

    /* Ĭ������µ���ֻ֧��GSM */
    pstSptRat->ucPlatformSptGsm        = VOS_TRUE;
    pstSptRat->ucPlatformSptWcdma      = VOS_FALSE;
    pstSptRat->ucPlatformSptLte        = VOS_FALSE;
    pstSptRat->ucPlatformSptUtralTDD   = VOS_FALSE;

    return;

}
VOS_VOID AT_InitCommPsCtx(VOS_VOID)
{
    AT_COMM_PS_CTX_STRU                *pstPsCtx = VOS_NULL_PTR;

    PS_MEM_SET(&g_stAtNdisDhcpPara, 0, sizeof(g_stAtNdisDhcpPara));
    PS_MEM_SET(&g_stAtAppPdpEntity, 0, sizeof(g_stAtAppPdpEntity));

    pstPsCtx = AT_GetCommPsCtxAddr();

#if (FEATURE_ON == FEATURE_IPV6)
    pstPsCtx->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;

    pstPsCtx->stIpv6BackProcExtCauseTbl.ulCauseNum = 0;

    pstPsCtx->ulIpv6AddrTestModeCfg = 0;
#endif

    pstPsCtx->ucSharePdpFlag = VOS_FALSE;

    pstPsCtx->lSpePort       = AT_INVALID_SPE_PORT;
    pstPsCtx->ulIpfPortFlg   = VOS_FALSE;

    return;
}


VOS_VOID AT_InitCommPbCtx(VOS_VOID)
{
    AT_COMM_PB_CTX_STRU                *pstCommPbCntxt = VOS_NULL_PTR;

    pstCommPbCntxt = AT_GetCommPbCtxAddr();

    pstCommPbCntxt->usCurrIdx       = 0;
    pstCommPbCntxt->usLastIdx       = 0;
    pstCommPbCntxt->ulSingleReadFlg = VOS_FALSE;
    return;
}


VOS_VOID AT_InitModemCcCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstCcCtx = AT_GetModemCcCtxAddrFromModemId(enModemId);

    pstCcCtx->ulCurIsExistCallFlag = VOS_FALSE;
    pstCcCtx->enCsErrCause         = TAF_CS_CAUSE_SUCCESS;

    /* �����Զ�Ӧ�������ʼ�� */
    PS_MEM_SET(&(pstCcCtx->stS0TimeInfo), 0, sizeof(pstCcCtx->stS0TimeInfo));

    PS_MEM_SET(&(pstCcCtx->stEconfInfo), 0, sizeof(pstCcCtx->stEconfInfo));

    for (i = 0; i < TAF_CALL_MAX_ECONF_CALLED_NUM; i++)
    {
        pstCcCtx->stEconfInfo.astCallInfo[i].enCallState = TAF_CALL_ECONF_STATE_BUTT;
        pstCcCtx->stEconfInfo.astCallInfo[i].enCause     = TAF_CS_CAUSE_SUCCESS;
    }


    return;
}
VOS_VOID AT_InitModemSsCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

    pstSsCtx->usUssdTransMode      = AT_USSD_TRAN_MODE;
    pstSsCtx->enCModType           = MN_CALL_MODE_SINGLE;
    pstSsCtx->ucSalsType           = AT_SALS_DISABLE_TYPE;
    pstSsCtx->ucClipType           = AT_CLIP_DISABLE_TYPE;
    pstSsCtx->ucClirType           = AT_CLIR_AS_SUBSCRIPT;
    pstSsCtx->ucColpType           = AT_COLP_DISABLE_TYPE;
    pstSsCtx->ucCrcType            = AT_CRC_DISABLE_TYPE;
    pstSsCtx->ucCcwaType           = AT_CCWA_DISABLE_TYPE;


    pstSsCtx->stCbstDataCfg.enSpeed    = MN_CALL_CSD_SPD_64K_MULTI;
    pstSsCtx->stCbstDataCfg.enName     = MN_CALL_CSD_NAME_SYNC_UDI;
    pstSsCtx->stCbstDataCfg.enConnElem = MN_CALL_CSD_CE_T;

    PS_MEM_SET(&(pstSsCtx->stCcugCfg), 0, sizeof(pstSsCtx->stCcugCfg));

    return;
}


VOS_VOID AT_InitModemSmsCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

    pstSmsCtx->enCmgfMsgFormat      = AT_CMGF_MSG_FORMAT_PDU;
    pstSmsCtx->ucCsdhType           = AT_CSDH_NOT_SHOW_TYPE;
    pstSmsCtx->ucParaCmsr           = VOS_FALSE;
    pstSmsCtx->ucSmsAutoReply       = VOS_FALSE;
    pstSmsCtx->enCsmsMsgVersion     = MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS;

    /* ME�洢״̬��ʼ�� */
    pstSmsCtx->enMsgMeStorageStatus = MN_MSG_ME_STORAGE_DISABLE;
    pstSmsCtx->ucLocalStoreFlg      = VOS_TRUE;

    pstSmsCtx->stCnmiType.CnmiModeType    = AT_CNMI_MODE_BUFFER_TYPE;
    pstSmsCtx->stCnmiType.CnmiMtType      = AT_CNMI_MT_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiBmType      = AT_CNMI_BM_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiDsType      = AT_CNMI_DS_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiBfrType     = AT_CNMI_BFR_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpModeType = AT_CNMI_MODE_BUFFER_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpMtType   = AT_CNMI_MT_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpBmType   = AT_CNMI_BM_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpDsType   = AT_CNMI_DS_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpBfrType  = AT_CNMI_BFR_SEND_TYPE;

    /* �������ʼ�� */
    pstSmsCtx->stCgsmsSendDomain.ucActFlg     = VOS_FALSE;
    pstSmsCtx->stCgsmsSendDomain.enSendDomain = MN_MSG_SEND_DOMAIN_CS_PREFERRED;

    /* �ı�������ز�����ʼ�� */
    /*
    27005 3 Text Mode 3.1 Parameter Definitions
    Message Data Parameters
    <fo> depending on the command or result code: first octet of 3GPP TS 23.040
    [3] SMS-DELIVER, SMS-SUBMIT (default 17), SMS-STATUS-REPORT, or SMS-COMMAND
    (default 2) in integer format
    <vp> depending on SMS-SUBMIT <fo> setting: 3GPP TS 23.040 [3] TP-Validity-
    Period either in integer format (default 167), in time-string format (refer
    <dt>), or if EVPF is supported, in enhanced format (hexadecimal coded string
    with double quotes)
    */
    PS_MEM_SET(&(pstSmsCtx->stCscaCsmpInfo), 0, sizeof(pstSmsCtx->stCscaCsmpInfo));
    pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucParmInd = 0xff;
    pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod     =
    MN_MSG_VALID_PERIOD_RELATIVE;
    pstSmsCtx->stCscaCsmpInfo.stVp.u.ucOtherTime     = AT_CSMP_SUBMIT_VP_DEFAULT_VALUE;

    /* ���ż�״̬�������ɾ����д�����ͻ���մ洢���ʳ�ʼ�� */
    pstSmsCtx->stCpmsInfo.stRcvPath.enStaRptMemStore = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore     = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.enMemReadorDelete          = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.enMemSendorWrite           = MN_MSG_MEM_STORE_SIM;

    /* ���ż�״̬��������ϱ���ʽ��ʼ�� */
    pstSmsCtx->stCpmsInfo.stRcvPath.enRcvSmAct       = MN_MSG_RCVMSG_ACT_STORE;
    pstSmsCtx->stCpmsInfo.stRcvPath.enRcvStaRptAct   = MN_MSG_RCVMSG_ACT_STORE;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmsServVersion = MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS;

    /* ���Ż�״̬���治�洢ֱ���ϱ�PDU�Ļ����ʼ�� */
    PS_MEM_SET(&(pstSmsCtx->stSmtBuffer), 0x00, sizeof(pstSmsCtx->stSmtBuffer));

    /* �����Զ�Ӧ�𻺴�����ָ���ʼ�� */
    PS_MEM_SET(pstSmsCtx->astSmsMtBuffer,
               0x00,
               (sizeof(AT_SMS_MT_BUFFER_STRU) * AT_SMSMT_BUFFER_MAX));

    /* �㲥���ŵ�����ѡ��Ͳ��洢ֱ���ϱ�PDU�Ļ����ʼ�� */
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    PS_MEM_SET(&(pstSmsCtx->stCbsDcssInfo), 0x00, sizeof(pstSmsCtx->stCbsDcssInfo));
    PS_MEM_SET(&(pstSmsCtx->stCbmBuffer), 0x00, sizeof(pstSmsCtx->stCbmBuffer));
#endif

    return;
}
VOS_VOID AT_InitModemNetCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

    pstNetCtx->ucCerssiReportType      = AT_CERSSI_REPORT_TYPE_5DB_CHANGE_REPORT;
    pstNetCtx->ucCregType              = AT_CREG_RESULT_CODE_NOT_REPORT_TYPE;
    pstNetCtx->ucCgregType             = AT_CGREG_RESULT_CODE_NOT_REPORT_TYPE;

    pstNetCtx->ucCopsFormatType         = AT_COPS_LONG_ALPH_TYPE;
    pstNetCtx->enPrefPlmnType           = MN_PH_PREF_PLMN_UPLMN;
    pstNetCtx->ucCpolFormatType         = AT_COPS_NUMERIC_TYPE;
    pstNetCtx->ucRoamFeature            = AT_ROAM_FEATURE_OFF;
    pstNetCtx->ucSpnType                = 0;
    pstNetCtx->ucCerssiMinTimerInterval = 0;
    pstNetCtx->enCalculateAntennaLevel  = AT_CMD_ANTENNA_LEVEL_0;
    PS_MEM_SET(pstNetCtx->aenAntennaLevel, 0, sizeof(pstNetCtx->aenAntennaLevel));
    PS_MEM_SET(&(pstNetCtx->stTimeInfo), 0, sizeof(pstNetCtx->stTimeInfo));

#if(FEATURE_ON == FEATURE_LTE)
    pstNetCtx->ucCeregType           = AT_CEREG_RESULT_CODE_NOT_REPORT_TYPE;
#endif

    return;
}


VOS_VOID AT_InitModemAgpsCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromModemId(enModemId);

    PS_MEM_SET(&(pstAgpsCtx->stXml), 0, sizeof(pstAgpsCtx->stXml));

    pstAgpsCtx->enCposrReport = AT_CPOSR_DISABLE;
    pstAgpsCtx->enXcposrReport = AT_XCPOSR_DISABLE;

    return;
}


VOS_VOID AT_InitModemPsCtx(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstPsCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* ��ʼ��CID�ͺ���ʵ��ӳ��� */
    for (ulCnt = 0; ulCnt <= TAF_MAX_CID; ulCnt++)
    {
        pstPsCtx->aucCidToIndexTbl[ulCnt] = AT_PS_CALL_INVALID_CALLID;
    }

    /* ��ʼ������ʵ�� */
    for (ulCnt = 0; ulCnt < AT_PS_MAX_CALL_NUM; ulCnt++)
    {
        pstPsCtx->astCallEntity[ulCnt].ulUsedFlg   = VOS_FALSE;

        PS_MEM_SET(&pstPsCtx->astCallEntity[ulCnt].stUsrDialParam,
                   0x00, sizeof(AT_DIAL_PARAM_STRU));

        pstPsCtx->astCallEntity[ulCnt].ucIpv4Cid   = AT_PS_CALL_INVALID_CID;
        pstPsCtx->astCallEntity[ulCnt].enIpv4State = AT_PDP_STATE_IDLE;

        PS_MEM_SET(&pstPsCtx->astCallEntity[ulCnt].stIpv4DhcpInfo,
                   0x00, sizeof(AT_IPV4_DHCP_PARAM_STRU));

#if (FEATURE_ON == FEATURE_IPV6)
        pstPsCtx->astCallEntity[ulCnt].ucIpv6Cid   = AT_PS_CALL_INVALID_CID;
        pstPsCtx->astCallEntity[ulCnt].enIpv6State = AT_PDP_STATE_IDLE;

        PS_MEM_SET(&pstPsCtx->astCallEntity[ulCnt].stIpv6RaInfo,
                   0x00, sizeof(AT_IPV6_RA_INFO_STRU));
        PS_MEM_SET(&pstPsCtx->astCallEntity[ulCnt].stIpv6DhcpInfo,
                   0x00, sizeof(AT_IPV6_DHCP_PARAM_STRU));
#endif
    }

    /* ��ʼ��CHDATA CFG */
    for (ulCnt = 0; ulCnt <= TAF_MAX_CID; ulCnt++)
    {
        pstPsCtx->astChannelCfg[ulCnt].ulUsed        = VOS_FALSE;
        pstPsCtx->astChannelCfg[ulCnt].ulRmNetId     = AT_PS_INVALID_RMNET_ID;
        pstPsCtx->astChannelCfg[ulCnt].ulRmNetActFlg = VOS_FALSE;
    }

    /* ��ʼ�������� */
    pstPsCtx->enPsErrCause = TAF_PS_CAUSE_SUCCESS;

    /* ��ʼ��IP��ַ��RABID��ӳ��� */
    PS_MEM_SET(pstPsCtx->aulIpAddrRabIdMap, 0x00, (sizeof(VOS_UINT32) * AT_PS_RABID_MAX_NUM));

    return;
}
VOS_VOID AT_InitClientConfiguration(VOS_VOID)
{
    VOS_UINT8                           i;
    AT_CLIENT_CTX_STRU                 *pstClientCtx = VOS_NULL_PTR;

    for (i = 0; i < AT_CLIENT_BUTT; i++)
    {
        pstClientCtx = AT_GetClientCtxAddr(i);

        pstClientCtx->stClientConfiguration.ucReportFlg = VOS_TRUE;
        pstClientCtx->stClientConfiguration.enModemId   = MODEM_ID_0;
    }

    return;
}


VOS_VOID AT_InitResetCtx(VOS_VOID)
{
    AT_RESET_CTX_STRU                   *pstResetCtx = VOS_NULL_PTR;

    PS_MEM_SET(&g_stAtStatsInfo, 0, sizeof(g_stAtStatsInfo));

    pstResetCtx = AT_GetResetCtxAddr();

    pstResetCtx->hResetSem     = VOS_NULL_PTR;
    pstResetCtx->ulResetingFlag = VOS_FALSE;

    /* ����������ź��� */
    if (VOS_OK != VOS_SmBCreate( "AT", 0, VOS_SEMA4_FIFO, &pstResetCtx->hResetSem))
    {
        vos_printf("Create AT acpu cnf sem failed!\r\n");
        AT_DBG_SET_SEM_INIT_FLAG(VOS_FALSE);
        AT_DBG_CREATE_BINARY_SEM_FAIL_NUM(1);

        return;
    }
    else
    {
        AT_DBG_SAVE_BINARY_SEM_ID(pstResetCtx->hResetSem);
    }

    AT_DBG_SET_SEM_INIT_FLAG(VOS_TRUE);

    return;
}

#if (FEATURE_ON == FEATURE_AT_HSUART)

VOS_VOID AT_InitUartCtx(VOS_VOID)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    pstUartCtx     = AT_GetUartCtxAddr();

    PS_MEM_SET(pstUartCtx, 0, sizeof(AT_UART_CTX_STRU));

    /* ��ʼ��UART��ά�ɲ���Ϣ */
    AT_InitHsUartStats();

    /* ��ʼ��UART�����ʣ�֡��ʽĬ��ֵ */
    pstUartCtx->stPhyConfig.enBaudRate            = AT_UART_DEFAULT_BAUDRATE;
    pstUartCtx->stPhyConfig.stFrame.enFormat      = AT_UART_DEFAULT_FORMAT;
    pstUartCtx->stPhyConfig.stFrame.enParity      = AT_UART_DEFAULT_PARITY;

    /* ��ʼ��UART LINE CTRLĬ��ֵ */
    pstUartCtx->stLineCtrl.enDcdMode              = AT_UART_DEFAULT_DCD_MODE;
    pstUartCtx->stLineCtrl.enDtrMode              = AT_UART_DEFAULT_DTR_MODE;
    pstUartCtx->stLineCtrl.enDsrMode              = AT_UART_DEFAULT_DSR_MODE;

    /* ��ʼ��FLOW CTRLĬ��ֵ */
    pstUartCtx->stFlowCtrl.enDceByDte             = AT_UART_DEFAULT_FC_DCE_BY_DTE;
    pstUartCtx->stFlowCtrl.enDteByDce             = AT_UART_DEFAULT_FC_DTE_BY_DCE;

    /* ��ʼ��RI�źŲ���Ĭ��ֵ */
    pstUartCtx->stRiConfig.ulSmsRiOnInterval      = AT_UART_DEFAULT_SMS_RI_ON_INTERVAL;
    pstUartCtx->stRiConfig.ulSmsRiOffInterval     = AT_UART_DEFAULT_SMS_RI_OFF_INTERVAL;
    pstUartCtx->stRiConfig.ulVoiceRiOnInterval    = AT_UART_DEFAULT_VOICE_RI_ON_INTERVAL;
    pstUartCtx->stRiConfig.ulVoiceRiOffInterval   = AT_UART_DEFAULT_VOICE_RI_OFF_INTERVAL;
    pstUartCtx->stRiConfig.ucVoiceRiCycleTimes    = AT_UART_DEFAULT_VOICE_RI_CYCLE_TIMES;

    /* ��ʼ��RI�ź�״̬ */
    pstUartCtx->stRiStateInfo.ulRunFlg            = VOS_FALSE;
    pstUartCtx->stRiStateInfo.enType              = AT_UART_RI_TYPE_BUTT;

    pstUartCtx->stRiStateInfo.hVoiceRiTmrHdl      = VOS_NULL_PTR;
    pstUartCtx->stRiStateInfo.enVoiceRiTmrStatus  = AT_TIMER_STATUS_STOP;
    pstUartCtx->stRiStateInfo.ulVoiceRiCycleCount = 0;

    for (ucCallId = 0; ucCallId <= MN_CALL_MAX_NUM; ucCallId++)
    {
        pstUartCtx->stRiStateInfo.aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_STOP;
    }

    pstUartCtx->stRiStateInfo.hSmsRiTmrHdl        = VOS_NULL_PTR;
    pstUartCtx->stRiStateInfo.ulSmsRiOutputCount  = 0;
    pstUartCtx->stRiStateInfo.enSmsRiTmrStatus    = AT_TIMER_STATUS_STOP;

    pstUartCtx->ulTxWmHighFlg                     = VOS_FALSE;
    pstUartCtx->pWmLowFunc                        = VOS_NULL_PTR;

    return;
}
#endif
VOS_VOID AT_InitCommCtx(VOS_VOID)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

    pstCommCtx = AT_GetCommCtxAddr();

    /* Ĭ��Ӧ������ΪMP */
    pstCommCtx->ucSystemAppConfigAddr = SYSTEM_APP_MP;

    /* ��ʼ��MUX��ص������� */
    PS_MEM_SET(&(pstCommCtx->stMuxCtx), 0, sizeof(AT_MUX_CTX_STRU));

    /* ��ʼ��PS�򹫹��������� */
    AT_InitCommPsCtx();

    AT_InitCommPbCtx();

    return;
}


VOS_VOID AT_InitClientCtx(VOS_VOID)
{
    AT_InitClientConfiguration();
}


VOS_VOID AT_InitModemCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_InitUsimStatus(enModemId);

    AT_InitPlatformRatList(enModemId);

    AT_InitModemCcCtx(enModemId);

    AT_InitModemSsCtx(enModemId);

    AT_InitModemSmsCtx(enModemId);

    AT_InitModemNetCtx(enModemId);

    AT_InitModemAgpsCtx(enModemId);

    AT_InitModemPsCtx(enModemId);

    return;
}


VOS_VOID AT_InitCtx(VOS_VOID)
{
    MODEM_ID_ENUM_UINT16                enModemId;

    AT_InitCommCtx();

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        AT_InitModemCtx(enModemId);
    }

    AT_InitClientCtx();

    return;
}

/*****************************************************************************
 �� �� ��  : AT_GetModemIDFromPid
 ��������  : ����PID�õ�ModemID
 �������  : VOS_UINT32
 �������  : ��
 �� �� ֵ  : MODEM_ID_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���
*****************************************************************************/
MODEM_ID_ENUM_UINT16 AT_GetModemIDFromPid(VOS_UINT32 ulPid)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                          ulModemPidTabLen;
    VOS_UINT32                          i;

    ulModemPidTabLen    = (sizeof(g_astAtModemPidTab)/sizeof(AT_MODEM_PID_TAB_STRU));

    for (i = 0; i < ulModemPidTabLen; i++)
    {

        if (ulPid == g_astAtModemPidTab[i].ulModem0Pid)
        {
            return MODEM_ID_0;
        }

        if (ulPid == g_astAtModemPidTab[i].ulModem1Pid)
        {
            return MODEM_ID_1;
        }

#if (3 == MULTI_MODEM_NUMBER)
        if (ulPid == g_astAtModemPidTab[i].ulModem2Pid)
        {
            return MODEM_ID_2;
        }
#endif

    }

    return MODEM_ID_BUTT;
#else
    return MODEM_ID_0;
#endif
}



VOS_UINT8* AT_GetSystemAppConfigAddr(VOS_VOID)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

    pstCommCtx = AT_GetCommCtxAddr();

    return &(pstCommCtx->ucSystemAppConfigAddr);
}


AT_RESET_CTX_STRU* AT_GetResetCtxAddr(VOS_VOID)
{
    return &(g_stAtResetCtx);
}


AT_COMM_CTX_STRU* AT_GetCommCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx);
}


AT_COMM_PS_CTX_STRU* AT_GetCommPsCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx.stPsCtx);
}


AT_COMM_PB_CTX_STRU* AT_GetCommPbCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx.stCommPbCtx);
}


AT_MODEM_CTX_STRU* AT_GetModemCtxAddr(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId]);
}


AT_USIM_INFO_CTX_STRU* AT_GetUsimInfoCtxFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stAtUsimInfoCtx);
}


AT_MODEM_SPT_RAT_STRU* AT_GetSptRatFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stPlatformRatList);
}




AT_MODEM_CC_CTX_STRU* AT_GetModemCcCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stCcCtx);
}


AT_MODEM_CC_CTX_STRU* AT_GetModemCcCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemCcCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stCcCtx);
}


AT_MODEM_SS_CTX_STRU* AT_GetModemSsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stSsCtx);
}


AT_MODEM_SS_CTX_STRU* AT_GetModemSsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemSsCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stSsCtx);
}

AT_MODEM_SMS_CTX_STRU* AT_GetModemSmsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stSmsCtx);
}


AT_MODEM_SMS_CTX_STRU* AT_GetModemSmsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemSmsCtxAddrFromClientId: Get modem id fail");
    }

    return &(g_astAtModemCtx[enModemId].stSmsCtx);
}



AT_MODEM_NET_CTX_STRU* AT_GetModemNetCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stNetCtx);
}


AT_MODEM_NET_CTX_STRU* AT_GetModemNetCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemNetCtxAddrFromClientId: Get modem id fail");
    }

    return &(g_astAtModemCtx[enModemId].stNetCtx);
}

AT_MODEM_AGPS_CTX_STRU* AT_GetModemAgpsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stAgpsCtx);
}

AT_MODEM_AGPS_CTX_STRU* AT_GetModemAgpsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemAgpsCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stAgpsCtx);
}


AT_MODEM_PS_CTX_STRU* AT_GetModemPsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stPsCtx);
}


AT_MODEM_PS_CTX_STRU* AT_GetModemPsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemPsCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stPsCtx);
}


AT_CLIENT_CTX_STRU* AT_GetClientCtxAddr(
    AT_CLIENT_ID_ENUM_UINT16            enClientId
)
{
    return &(g_astAtClientCtx[enClientId]);
}


VOS_UINT32 AT_GetModemIdFromClient(
    VOS_UINT16                          usClientId,
    MODEM_ID_ENUM_UINT16               *pModemId
)
{
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    /* �ж��Ƿ���MODEM0�㲥��client index */
    if ((AT_BROADCAST_CLIENT_INDEX_MODEM_0 == usClientId)
     || (AT_BROADCAST_CLIENT_ID_MODEM_0 == usClientId))
    {
        *pModemId = MODEM_ID_0;
    }
    /* �ж��Ƿ���MODEM1�㲥��client index */
    else if ((AT_BROADCAST_CLIENT_INDEX_MODEM_1 == usClientId)
          || (AT_BROADCAST_CLIENT_ID_MODEM_1 == usClientId))
    {
        *pModemId = MODEM_ID_1;
    }
    /* �ж��Ƿ���MODEM2�㲥��client index */
    else if ((AT_BROADCAST_CLIENT_INDEX_MODEM_2 == usClientId)
          || (AT_BROADCAST_CLIENT_ID_MODEM_2 == usClientId))
    {
        *pModemId = MODEM_ID_2;
    }
    /* �ǹ㲥client index */
    else
    {
        /* client index ��Ч��ֱ�ӷ��� */
        if (usClientId >= AT_CLIENT_BUTT)
        {
            return VOS_ERR;
        }

        pstAtClientCtx = AT_GetClientCtxAddr(usClientId);

        *pModemId = pstAtClientCtx->stClientConfiguration.enModemId;
    }

    /* �ڵ�����ʱ��NV���������MODEMIDΪMODEM1ʱ���ᷢ���ڴ�Խ�磬�˴������쳣���� */
    if (*pModemId >= MODEM_ID_BUTT)
    {
        AT_ERR_LOG("AT_GetModemIdFromClient: modem id is invalid");

        *pModemId = MODEM_ID_0;
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_GetDestPid(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulRcvPid
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          i;

    enModemId = MODEM_ID_0;

    /* ��ȡclient id��Ӧ��Modem Id */
    ulRslt = AT_GetModemIdFromClient(usClientId, &enModemId);

    /* modem 1��ulRcvPid��Ӧ��pid */
    if ((VOS_OK == ulRslt)
     && (MODEM_ID_0 != enModemId))
    {
        for (i = 0; i < (sizeof(g_astAtModemPidTab)/sizeof(AT_MODEM_PID_TAB_STRU)); i++)
        {
            if (ulRcvPid != g_astAtModemPidTab[i].ulModem0Pid)
            {
                continue;
            }

            if (MODEM_ID_1 == enModemId)
            {
                return g_astAtModemPidTab[i].ulModem1Pid;
            }

            if (MODEM_ID_2 == enModemId)
            {
                return g_astAtModemPidTab[i].ulModem2Pid;
            }
        }

        /* ��������Ҳ�����Ӧ��PIDӦ��ʱ������ */
        if (i >= (sizeof(g_astAtModemPidTab)/sizeof(AT_MODEM_PID_TAB_STRU)))
        {
            vos_printf("AT_GetDestPid: usClientId is %d, ulRcvPid is %d no modem1 pid. \r\n", usClientId, ulRcvPid);
        }
    }
#endif

    return ulRcvPid;
}
MN_CLIENT_ID_T AT_GetRealClientId(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulPid
)
{
    MODEM_ID_ENUM_UINT16                enModemId;

    /* ����Pid��ֵ��ȡModemId */
    enModemId = AT_GetModemIDFromPid(ulPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
        return usClientId;
    }

    /* ����ModemId��ȡClientId */
    if (MODEM_ID_0 == enModemId)
    {
        return (usClientId & AT_BROADCAST_CLIENT_ID_MODEM_0);
    }
    else if (MODEM_ID_1 == enModemId)
    {
        return (usClientId & AT_BROADCAST_CLIENT_ID_MODEM_1);
    }
    else
    {
        return (usClientId & AT_BROADCAST_CLIENT_ID_MODEM_2);
    }
}


VOS_UINT8 AT_IsModemSupportRat(
    MODEM_ID_ENUM_UINT16                enModemId,
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
)
{
    AT_MODEM_SPT_RAT_STRU              *pstSptRatList = VOS_NULL_PTR;

    pstSptRatList = AT_GetSptRatFromModemId(enModemId);
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    if (TAF_MMA_RAT_LTE == enRat)
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    {
        return pstSptRatList->ucPlatformSptLte;
    }
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    if (TAF_MMA_RAT_WCDMA == enRat)
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    {
        if ((VOS_TRUE == pstSptRatList->ucPlatformSptWcdma)
         || (VOS_TRUE == pstSptRatList->ucPlatformSptUtralTDD))
        {
            return VOS_TRUE;
        }
        else
        {
            return VOS_FALSE;
        }
    }
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    if (TAF_MMA_RAT_GSM == enRat)
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    {
        return pstSptRatList->ucPlatformSptGsm;
    }

    return VOS_FALSE;
}


VOS_UINT8 AT_IsModemSupportUtralTDDRat(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    AT_MODEM_SPT_RAT_STRU              *pstSptRatList = VOS_NULL_PTR;

    pstSptRatList = AT_GetSptRatFromModemId(enModemId);

    return pstSptRatList->ucPlatformSptUtralTDD;
}



VOS_VOID AT_SetCsCallErrCause(
    VOS_UINT16                          usClientId,
    TAF_CS_CAUSE_ENUM_UINT32            enCsErrCause
)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(usClientId);

    pstCcCtx->enCsErrCause = enCsErrCause;

    return;
}


TAF_CS_CAUSE_ENUM_UINT32 AT_GetCsCallErrCause(
    VOS_UINT16                          usClientId
)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(usClientId);

    return pstCcCtx->enCsErrCause;
}



AT_ABORT_CMD_PARA_STRU* AT_GetAbortCmdPara(VOS_VOID)
{
    return &(gstAtAbortCmdCtx.stAtAbortCmdPara);
}


VOS_UINT8* AT_GetAbortRspStr(VOS_VOID)
{
    return (gstAtAbortCmdCtx.stAtAbortCmdPara.aucAbortAtRspStr);
}


VOS_UINT32 AT_GetSsCustomizePara(AT_SS_CUSTOMIZE_TYPE_UINT8 enSsCustomizeType)
{
    VOS_UINT8                           ucMask;

    if (VOS_TRUE != g_stAtSsCustomizePara.ucStatus)
    {
        return VOS_FALSE;
    }

    ucMask = (VOS_UINT8)(AT_SS_CUSTOMIZE_SERVICE_MASK << enSsCustomizeType);
    if (0 != (g_stAtSsCustomizePara.ucSsCmdCustomize & ucMask))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


VOS_SEM AT_GetResetSem(VOS_VOID)
{
    return g_stAtResetCtx.hResetSem;
}


VOS_UINT32 AT_GetResetFlag(VOS_VOID)
{
    return g_stAtResetCtx.ulResetingFlag;
}


VOS_VOID AT_SetResetFlag(VOS_UINT32 ulFlag)
{
    g_stAtResetCtx.ulResetingFlag = ulFlag;
    return;
}



AT_MODEM_MT_INFO_CTX_STRU* AT_GetModemMtInfoCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stMtInfoCtx);
}


VOS_VOID AT_InitTraceMsgTab(VOS_VOID)
{
    PS_MEM_SET(g_stAtTraceMsgIdTab, 0xFF, sizeof(g_stAtTraceMsgIdTab));
}


AT_INTER_MSG_ID_ENUM_UINT32 AT_GetResultMsgID(VOS_UINT8 ucIndex)
{
    AT_INTER_MSG_ID_ENUM_UINT32         enResultMsgID;

    if (AT_BROADCAST_CLIENT_INDEX_MODEM_0 == ucIndex)
    {
        enResultMsgID = ID_AT_MNTN_RESULT_BROADCAST_MODEM_0;
    }
    else if (AT_BROADCAST_CLIENT_INDEX_MODEM_1 == ucIndex)
    {
        enResultMsgID = ID_AT_MNTN_RESULT_BROADCAST_MODEM_1;
    }
    else if (AT_BROADCAST_CLIENT_INDEX_MODEM_2 == ucIndex)
    {
        enResultMsgID = ID_AT_MNTN_RESULT_BROADCAST_MODEM_2;
    }
    else
    {
        enResultMsgID = g_stAtTraceMsgIdTab[ucIndex].enResultMsgID;
    }

    return enResultMsgID;
}


AT_INTER_MSG_ID_ENUM_UINT32 AT_GetCmdMsgID(VOS_UINT8 ucIndex)
{
    return g_stAtTraceMsgIdTab[ucIndex].enCmdMsgID;
}


VOS_VOID AT_ConfigTraceMsg(
    VOS_UINT8                           ucIndex,
    AT_INTER_MSG_ID_ENUM_UINT32         enCmdMsgId,
    AT_INTER_MSG_ID_ENUM_UINT32         enResultMsgId
)
{
    g_stAtTraceMsgIdTab[ucIndex].enCmdMsgID = enCmdMsgId;
    g_stAtTraceMsgIdTab[ucIndex].enResultMsgID = enResultMsgId;

    return;
}


VOS_VOID At_SetAtCmdAbortTickInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulTick
)
{
    gstAtAbortCmdCtx.stCmdAbortTick.ulAtSetTick[ucIndex]    = ulTick;

    return;
}


AT_CMD_ABORT_TICK_INFO* At_GetAtCmdAbortTickInfo(VOS_VOID)
{
    return &(gstAtAbortCmdCtx.stCmdAbortTick);
}


VOS_UINT8 At_GetAtCmdAnyAbortFlg(VOS_VOID)
{
    return (gstAtAbortCmdCtx.stAtAbortCmdPara.ucAnyAbortFlg);
}


VOS_VOID At_SetAtCmdAnyAbortFlg(
    VOS_UINT8                           ucFlg
)
{
    gstAtAbortCmdCtx.stAtAbortCmdPara.ucAnyAbortFlg = ucFlg;

    return;
}


AT_UART_CTX_STRU* AT_GetUartCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx.stUartCtx);
}


AT_UART_PHY_CFG_STRU* AT_GetUartPhyCfgInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stPhyConfig);
}


AT_UART_LINE_CTRL_STRU* AT_GetUartLineCtrlInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stLineCtrl);
}


AT_UART_FLOW_CTRL_STRU* AT_GetUartFlowCtrlInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stFlowCtrl);
}


AT_UART_RI_CFG_STRU* AT_GetUartRiCfgInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stRiConfig);
}


AT_UART_RI_STATE_INFO_STRU* AT_GetUartRiStateInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stRiStateInfo);
}


AT_PORT_BUFF_CFG_STRU* AT_GetPortBuffCfgInfo(VOS_VOID)
{
    return &(AT_GetCommCtxAddr()->stPortBuffCfg);
}


AT_PORT_BUFF_CFG_ENUM_UINT8  AT_GetPortBuffCfg(VOS_VOID)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

    pstCommCtx = AT_GetCommCtxAddr();

    return pstCommCtx->stPortBuffCfg.enSmsBuffCfg;
}


VOS_VOID AT_InitPortBuffCfg(VOS_VOID)
{
    AT_PORT_BUFF_CFG_STRU              *pstUsedClientIdTab = VOS_NULL_PTR;

    pstUsedClientIdTab = AT_GetPortBuffCfgInfo();

    PS_MEM_SET(pstUsedClientIdTab, 0xFF, sizeof(AT_PORT_BUFF_CFG_STRU));

    pstUsedClientIdTab->ucNum = 0;
}


VOS_VOID AT_AddUsedClientId2Tab(VOS_UINT16 usClientId)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    if (usClientId >= AT_MAX_CLIENT_NUM)
    {
        return;
    }

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    /*  �ų��ڲ�ͨ�� */
    if ( (usClientId >= AT_MIN_APP_CLIENT_ID)
      && (usClientId <= AT_MAX_APP_CLIENT_ID))
    {
        return;
    }

#if (VOS_WIN32 == VOS_OS_VER)
    if (AT_CLIENT_ID_SOCK == usClientId)
    {
        return;
    }
#endif

    if (pstPortBuffCfg->ucNum >= AT_MAX_CLIENT_NUM)
    {
        pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM -1;
    }

    /* ѭ�������Ƿ��Ѿ���¼�� */
    for (ucIndex = 0; ucIndex < pstPortBuffCfg->ucNum; ucIndex++)
    {
        if (usClientId == pstPortBuffCfg->ulUsedClientID[ucIndex])
        {
            return;
        }
    }

    /* ���û�м�¼�������¼����� */
    if (ucIndex == pstPortBuffCfg->ucNum)
    {
        pstPortBuffCfg->ulUsedClientID[ucIndex] = (VOS_UINT32)usClientId;
        pstPortBuffCfg->ucNum++;
    }
}
VOS_VOID AT_RmUsedClientIdFromTab(VOS_UINT16 usClientId)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    if (pstPortBuffCfg->ucNum > AT_MAX_CLIENT_NUM)
    {
        pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM;
    }

    /* ѭ�������Ƿ��Ѿ���¼�� */
    for (ulIndex = 0; ulIndex < pstPortBuffCfg->ucNum; ulIndex++)
    {
        if (usClientId == pstPortBuffCfg->ulUsedClientID[ulIndex])
        {
            break;
        }
    }

    /* ���û�м�¼����ֱ���˳� */
    if (ulIndex == pstPortBuffCfg->ucNum)
    {
        return;
    }

    /* ����ҵ���ɾ����Ӧ��client */
    if (ulIndex == pstPortBuffCfg->ucNum - 1)
    {
        pstPortBuffCfg->ucNum--;
        pstPortBuffCfg->ulUsedClientID[ulIndex] = VOS_NULL_DWORD;

    }
    else
    {
        pstPortBuffCfg->ulUsedClientID[ulIndex] =
                    pstPortBuffCfg->ulUsedClientID[pstPortBuffCfg->ucNum - 1];
        pstPortBuffCfg->ulUsedClientID[pstPortBuffCfg->ucNum - 1] = VOS_NULL_DWORD;
        pstPortBuffCfg->ucNum--;
    }
}
AT_CLIENT_CONFIGURATION_STRU* AT_GetClientConfig(
    AT_CLIENT_ID_ENUM_UINT16            enClientId
)
{
    return &(AT_GetClientCtxAddr(enClientId)->stClientConfiguration);
}


AT_CLIENT_CFG_MAP_TAB_STRU* AT_GetClientCfgMapTbl(VOS_UINT8 ucIndex)
{
    return &(g_astAtClientCfgMapTbl[ucIndex]);
}
/* Added by h00313353 for SMS Filter Prj, 2015-9-23, begin */
/*****************************************************************************
 �� �� ��  : AT_GetSmsFilterEnableFlg
 ��������  : ��ȡ����NV����������Ϣ���Ƿ���LOG�ı�ʶ
 �������  : ucIndex    : ClientId
 �������  : VOS_UINT32 : ��ʶ��Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��25��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 AT_GetSmsFilterEnableFlg(
    VOS_UINT8                           ucIndex
)
{
    return AT_GetModemSmsCtxAddrFromClientId(ucIndex)->stSmsFilterCfg.ucSmsFilterEnableFlg;
}
/* Added by h00313353 for SMS Filter Prj, 2015-9-23, end */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
