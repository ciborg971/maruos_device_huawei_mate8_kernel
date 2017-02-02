
#ifndef __DSP_TEST_INTERFACE_H__
#define __DSP_TEST_INTERFACE_H__

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "TLPhyInterface.h"

/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

#define LPHY_MAILBOX_BASE_ADDR_DSP          (LPHY_MAILBOX_BASE_ADDR)                          /*���乲����ض���*/
#define TL_PHY_MAILBOX_SOC_TEST_ADDR        (LPHY_MAILBOX_BASE_ADDR_DSP + 0x4000)   /*DSPѹ�����������������ַ*/

typedef union
{
    struct
    {
        unsigned int ulPPTR :8;
        unsigned int ulCPTR :8;
        unsigned int ulMsgID:16;
    }bits;
    unsigned int ulReg32;
}DSP_DRV_MAIL_HEAD;

typedef union
{
    struct
    {
        unsigned int ulAddr;
        unsigned int ulLen;
        unsigned int ulResult;
        unsigned int ulNum;
    }writeReadTest;
    struct
    {
        unsigned int ulSrcAddr;
        unsigned int ulDestinAddr;
        unsigned int ulLen;
        unsigned int ulNum;
    }readWriteTest;
    struct
    {
        unsigned int ulFuncID;
        unsigned int ulCycle;
        unsigned int ulNum;
        unsigned int ulRsvd;
    }funcCycleCalc;
}DSP_DRV_MAIL_BODY;


typedef struct _DSP_DRV_MAIL_
{
	DSP_DRV_MAIL_HEAD strMailHead;
    DSP_DRV_MAIL_BODY strMailBody;
    unsigned int      ulRunCount;
}DSP_DRV_MAIL;

typedef enum
{
	WRITE_READ_TEST = 0,
	READ_WRITE_TEST,
	FUNC_CYCLE_CALC,
}MSG_TYPE_ENUM;

typedef enum
{
	FUNC_DHRYSTONE = 0,
	FUNC_WAITI,
	FUNC_NULL,
}FUNC_TYPE_ENUM;



/************************************************************
                             �ӿں�������
 ************************************************************/
#if (defined(TENSILICA_PLATFORM) && defined(CONFIG_MODULE_BUSSTRESS))
void BBE_OnBoardTest(void);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DSPTEST_H__ */
