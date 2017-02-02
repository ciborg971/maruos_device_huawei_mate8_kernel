

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/

/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

#ifndef __OM_OM_DEF_H__
#define __OM_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum __LPHY_REQ_MSGID_OM__
{
    LPHY_REQ_OM_ENA_RPT_RESERVED  =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, 0                  ),
    LPHY_REQ_OM_ENA_RPT_RFE       =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_RFE_MID       ),
    LPHY_REQ_OM_ENA_RPT_RFD       =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_RFD_MID       ),
    LPHY_REQ_OM_ENA_RPT_AGC       =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_AGC_MID       ),
    LPHY_REQ_OM_ENA_RPT_DCOC      =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_DCOC_MID      ),
    LPHY_REQ_OM_ENA_RPT_RXIQ      =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_RXIQ_MID      ),
    LPHY_REQ_OM_ENA_RPT_AFC       =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_AFC_MID       ),
    LPHY_REQ_OM_ENA_RPT_CS        =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_CSU_MID       ),
    LPHY_REQ_OM_ENA_RPT_CMU       =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_CMU_MID       ),
    LPHY_REQ_OM_ENA_RPT_EMU       =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_EMU_MID       ),
    LPHY_REQ_OM_ENA_RPT_CHE       =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_CHE_MID       ),
    LPHY_REQ_OM_ENA_RPT_DEM       =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_DEM_MID       ),
    LPHY_REQ_OM_ENA_RPT_CQI       =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_CQI_MID       ),
    LPHY_REQ_OM_ENA_RPT_CORR      =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_CORR_MID      ),
    LPHY_REQ_OM_ENA_RPT_SYNC      =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_SYNC_MID      ),
    LPHY_REQ_OM_ENA_RPT_TIMING    =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_TIMING_MID    ),
    LPHY_REQ_OM_ENA_RPT_DRX       =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_DRX_MID       ),
    LPHY_REQ_OM_ENA_RPT_SERV      =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_SERV_MID      ),
    LPHY_REQ_OM_ENA_RPT_UL        =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_UL_MID        ),
    LPHY_REQ_OM_ENA_RPT_CHANCTRL  =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_CHANCTRL_MID  ),
    LPHY_REQ_OM_ENA_RPT_OM        =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_OM_MID        ),
    LPHY_REQ_OM_ENA_RPT_DMA       =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_DMA_MID       ),
    LPHY_REQ_OM_ENA_RPT_VITERBI   =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_VITERBI_MID   ),
    LPHY_REQ_OM_ENA_RPT_TURBO     =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_TURBO_MID     ),
    LPHY_REQ_OM_ENA_RPT_SCHED     =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_SCHED_MID     ),
    LPHY_REQ_OM_ENA_RPT_INTERRUPT =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_INTERRUPT_MID ),
    LPHY_REQ_OM_ENA_RPT_EQUIP     =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, LPHY_BT_MID        ),
    LPHY_REQ_OM_ENA_RPT_ALL       =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, 0x99               ),
    LPHY_REQ_OM_ENA_RPT_LEVEL     =  OM_CMD_ID(LPHY_OM_MID, OM_TYPE_REQ, 0x100              ),

    TPHY_REQ_OM_ENA_RPT_RESERVED  =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, 0                  ),
    TPHY_REQ_OM_ENA_RPT_RFE       =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_RFDRV_MID     ),
    TPHY_REQ_OM_ENA_RPT_AGC       =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_AGC_MID       ),
    TPHY_REQ_OM_ENA_RPT_AFC       =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_AFC_MID       ),
    TPHY_REQ_OM_ENA_RPT_CS        =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_CS_MID        ),
    TPHY_REQ_OM_ENA_RPT_CMU       =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_CMU_MID       ),
    TPHY_REQ_OM_ENA_RPT_EMU       =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_MEAS_MID      ),
    TPHY_REQ_OM_ENA_RPT_CHE       =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_CHE_MID       ),

    TPHY_REQ_OM_ENA_RPT_DATA      =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_DATA_MID      ),
    TPHY_REQ_OM_ENA_RPT_CORR      =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_CORR_MID      ),
    TPHY_REQ_OM_ENA_RPT_CQI       =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_CQI_MID       ),
    LPHY_REQ_OM_ENA_RPT_PC        =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_PC_MID        ),
    TPHY_REQ_OM_ENA_RPT_SYNC      =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_SYNC_MID      ),
    TPHY_REQ_OM_ENA_RPT_TIMING    =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_TIMING_MID    ),
    TPHY_REQ_OM_ENA_RPT_DRX       =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_DRX_MID       ),
    TPHY_REQ_OM_ENA_RPT_SERV      =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_SERV_MID      ),
    TPHY_REQ_OM_ENA_RPT_UL        =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_UL_MID        ),

    TPHY_REQ_OM_ENA_RPT_CHANCTRL  =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_CHANCTRL_MID  ),
    TPHY_REQ_OM_ENA_RPT_OM        =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_OM_MID        ),
    TPHY_REQ_OM_ENA_RPT_DMA       =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_DMA_MID       ),
    TPHY_REQ_OM_ENA_RPT_CD        =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_CD_MID        ),
    TPHY_REQ_OM_ENA_RPT_VIT_TURBO =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_VIT_TURBO_MID ),
    TPHY_REQ_OM_ENA_RPT_SCHED     =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_SCHED_MID     ),
    TPHY_REQ_OM_ENA_RPT_INTERRUPT =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_INT_MID       ),
    TPHY_REQ_OM_ENA_RPT_JD        =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_JD_MID        ),

    TPHY_REQ_OM_ENA_RPT_DCOC      =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_DCOC_MID      ),
    TPHY_REQ_OM_ENA_RPT_RXIQ      =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_RXIQ_MID      ),
    TPHY_REQ_OM_ENA_RPT_CT        =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_CT_MID        ),
    TPHY_REQ_OM_ENA_RPT_BT        =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_BT_MID        ),
    TPHY_REQ_OM_ENA_RPT_NCIT      =  OM_CMD_ID(TPHY_OM_MID, OM_TYPE_REQ, TPHY_NCIT_MID      )

}LPHY_REQ_MSGID_OM_ENUM;

typedef struct __LPHY_REQ_OM_ENA_RPT_ALL_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16  enEna;           /*OM�ϱ��ܿ���*/
}LPHY_REQ_OM_ENA_RPT_ALL_STRU;

typedef struct __LPHY_REQ_OM_ENA_RPT_SUB_MODULE_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16  enEna;           /*REQ������Ҫ�Ŀ�����*/
    OM_REQ_ENABLE_ENUM_UINT16  enRptDT;
    OM_REQ_ENABLE_ENUM_UINT16  enRptSG;
    OM_REQ_ENABLE_ENUM_UINT16  enRptTrace;
    OM_REQ_ENABLE_ENUM_UINT16  enRptDBG;
    OM_REQ_ENABLE_ENUM_UINT16  enRptERR;
    OM_REQ_ENABLE_ENUM_UINT16  enRptIND;
}LPHY_REQ_OM_ENA_RPT_SUB_MODULE_STRU;

typedef struct __LPHY_REQ_OM_ENA_RPT_LEVEL_STRU__
{
    OM_REQ_TYPE_ENUM_UINT16  enType;           /*REQ������Ҫ�Ŀ�����*/
    OM_REQ_ENABLE_ENUM_UINT16  enTrace;         /*�Ƿ�ʹ��trace�����ϱ�*/
    OM_REQ_ENABLE_ENUM_UINT16  enInfo;          /*�Ƿ�ʹ����Ϣ�����ϱ�*/
    OM_REQ_ENABLE_ENUM_UINT16  enWarning;       /*�Ƿ�ʹ�ܾ��漶���ϱ�*/
    OM_REQ_ENABLE_ENUM_UINT16  enError;         /*�Ƿ�ʹ�ܴ��󼶱��ϱ�*/
    OM_REQ_ENABLE_ENUM_UINT16  enDebug;          /*�Ƿ�ʹ�ܵ��Լ����ϱ�*/
}LPHY_REQ_OM_ENA_RPT_LEVEL_STRU;

/************************************************************
                           2. CNF���ݽṹ����
************************************************************/
typedef enum __LPHY_CNF_MSGID_OM__
{
    LPHY_CNF_OM_RESERVED            = OM_CMD_ID(LPHY_OM_MID, OM_TYPE_CNF, 0x0),
}LPHY_CNF_MSGID_OM_ENUM;


/************************************************************
                           3. Ind���ݽṹ����
************************************************************/
typedef enum __LPHY_IND_MSGID_OM__
{
    LPHY_IND_OM_RESERVED            = OM_CMD_ID(LPHY_OM_MID, OM_TYPE_IND, 0x0),
}LPHY_IND_MSGID_OM_ENUM;


/************************************************************
                           4. SG ���ݽṹ����, �㷨��Ҫ��ͼ��
************************************************************/

/************************************************************
                           5. TRACE���ݽṹ����
************************************************************/
typedef enum __LPHY_TRACE_OM_ENUM__
{
    LPHY_TRACE_OM_RESERVED              = OM_LCMD_ID(LPHY_OM_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_OM_STRING                = OM_PRNT_ID(LPHY_OM_MID, OM_TYPE_TRACE, 0x1) /*��ӡ�ַ�����, û�ж�Ӧ�Ľṹ��*/
}LPHY_TRACE_OM_ENUM;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __OM_OM_DEF_H__ */
