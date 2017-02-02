

/************************************************************
                     ��������ģ�����ļ�
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

#ifndef __EMBMS_OM_DEF_H__
#define __EMBMS_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



/************************************************************
                    1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum
{
    LPHY_REQ_EMBMS_TM_REQUEST           = OM_CMD_ID(LPHY_EMBMS_MID, OM_TYPE_REQ, 0x1),
    LPHY_REQ_EMBMS_CP_REQUEST,
}LPHY_EMBMS_REQ_ENUM;

typedef UINT16 LPHY_EMBMS_REQ_ENUM_UINT16;


typedef struct
{
    OM_REQ_ENABLE_ENUM enOmTmSwitch;
    OM_REQ_ENABLE_ENUM enOmCpSwitch;
}LPHY_OM_REQ_EMBMS_STRU;

/************************************************************
                    2. CNF���ݽṹ����
************************************************************/


/************************************************************
                    3. Ind���ݽṹ����
************************************************************/


/************************************************************
                    4. TRACE���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_TRACE_EMBMS_MCCH_SETUP           = OM_CMD_ID(LPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_EMBMS_PMCH_SETUP,
    LPHY_TRACE_EMBMS_MRNTI_CONFIG,
    LPHY_TRACE_EMBMS_MBSFN_CONFIG,
    LPHY_TRACE_EMBMS_STOP,
    LPHY_TRACE_EMBMS_MAC_STOP
}LPHY_EMBMS_TRACE_ENUM;

typedef UINT16 LPHY_EMBMS_TRACE_ENUM_UINT16;

typedef struct
{
    UINT16      usSysFrmNum;    /*ϵͳ֡��*/
    UINT16      usSubFrmNum;    /*��֡��*/
    UINT16      usSymbNum;      /*��ǰ������*/
    UINT16      usReserved;
    UINT32      ulData1;
    UINT32      ulData2;
    UINT32      ulData3;
    UINT32      ulData4;
}LPHY_OM_TRACE_EMBMS_STRU;




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CHANCTRL_OM_DEF_H__ */


