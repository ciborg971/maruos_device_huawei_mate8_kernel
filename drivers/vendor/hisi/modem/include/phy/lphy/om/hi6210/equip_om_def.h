

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/
#include "om_base_def.h"
/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

#ifndef __EQUIP_OM_DEF_H__
#define __EQUIP_OM_DEF_H__


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
    LPHY_REQ_EQUIP_BT_REQUEST           = OM_CMD_ID(LPHY_BT_MID, OM_TYPE_REQ, 0x1),
}LPHY_EQUIP_REQ_ENUM;


typedef struct
{
    OM_REQ_ENABLE_ENUM usTxCmpOmSwitch;
    OM_REQ_ENABLE_ENUM usRxCmpOmSwitch;
}LPHY_OM_REQ_EQUIP_STRU;

/************************************************************
                    2. CNF���ݽṹ����
************************************************************/


/************************************************************
                    3. Ind���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_IND_EQUIP_BT_CMP_TX_REPORT = OM_CMD_ID(LPHY_BT_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_EQUIP_BT_CMP_RX_REPORT
}LPHY_EQUIP_BT_CMP_ENUM;



typedef struct
{
    UINT16 usCalMaxPwr;      /*����У׼�����������������*/
    INT16  sPwrCalc;         /*���㹦��*/
    UINT16 usPbVal;          /*AMPR��MPR����ֵ*/
    INT16  sSarMax;          /*��SAR���޶��������*/
    UINT16 usChType;         /*�ŵ�����*/
    INT16  sPowerIn;
    UINT16 usPdmVal;
    INT16  sAptCmp;
    INT16  sPwrAftPd;
    UINT16 usTxFreqCmpNum;   /*����õĲ���Ƶ�����*/
    UINT32 ulCentPoint;      /*��ǰ���������Ƶ��*/
    INT16  sFreqCmpVal;
    INT16  sTempIndex;
    INT16  sCurMaxPower;
    UINT16 usTempVal;
    UINT16 usPaLevel;        /*PA��λ*/
    UINT16 usDbbAttWord;
    UINT16 usAbbAttWord;
    UINT16 usRfCode;         /*RF������*/
    INT16  sFilterCmp;
    INT16  sBandWithCmp;
    UINT16 usPdDela;
    UINT16 usRsv2;
}BT_TX_CMP_OM_INFO_STRU;

typedef struct
{
    UINT16 usAgcLevel;
	UINT16 usTempVol;
    UINT16 usFreq;
	UINT16 usBandWidth;

    INT16  sFreqCmpVal0;
    INT16  sTempCmpVal0;
    INT16  sCmpVal0;
    INT16  sPreRsrp0;
    INT16  sPostRsrp0;

    INT16  sFreqCmpVal1;
    INT16  sTempCmpVal1;
    INT16  sCmpVal1;
    INT16  sPreRsrp1;
    INT16  sPostRsrp1;
}BT_RX_CMP_OM_INFO_STRU;

/************************************************************
                    4. TRACE���ݽṹ����
************************************************************/

/************************************************************
                    5. ERROR���ݽṹ����
************************************************************/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif 

