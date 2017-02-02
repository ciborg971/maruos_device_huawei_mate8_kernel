#include "osl_thread.h"
#include "osl_sem.h"
#include "osl_types.h"
#include "string.h"
#include "bsp_sci.h"
#include "mdrv_sci.h"
#include "osl_bio.h"
#include "sci_appl131.h"


#define  sci_test_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SCI, "[sci]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  sci_test_info(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_SCI, "[sci]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  sci_test_debug(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_SCI, "[sci]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  sci_test_warning(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_WARNING, BSP_MODU_SCI, "[sci]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

extern SCI_STATE_STRU g_strSciState;


int sci_test_001()
{
   	int ulCardStatus;

	ulCardStatus = mdrv_sci_get_cardstatus();
	sci_test_error("ulCardStatus = %d\n", (BSP_U32) ulCardStatus,0,0,0,0,0); 
    return BSP_OK;
}


int sci_test_002()
{
    u32 u32Result = 0;
	u32 ulCardStatus;
	u32Result = mdrv_sci_reset(COLD_RESET);
	sci_test_error("\r\n bsp_sci_reset u32Result = %d",u32Result,0,0,0,0,0);
	osl_task_delay(50);
	ulCardStatus = mdrv_sci_get_cardstatus();
    if(ulCardStatus == SCI_CARD_STATE_READY)
    {
        sci_test_error("sim card reset success\n");
    }
    else
    {
	    sci_test_error("sim card reset fail\nulCardStatus = %d\n", (BSP_U32) ulCardStatus,0,0,0,0,0);
        return BSP_ERROR;
    }
    mdrv_sci_deact();
    return BSP_OK;
}

//int mdrv_sci_send_data(unsigned int u32DataLength, unsigned char * pu8DataBuffer);

int sci_test_003()
{
    s32 s32Ret = 0;
    u32 send0_len = 5;
    u8 send0[5] = {0xa0,0xa4,0x00,0x00,0x02};


    s32Ret = mdrv_sci_reset(COLD_RESET);
    if(s32Ret)
    {
        sci_test_error("reset fail\n",__LINE__, send0_len);
    }
    
	osl_task_delay(50);
    s32Ret = mdrv_sci_get_cardstatus();
    if(s32Ret == SCI_CARD_STATE_READY)
    {
        s32Ret = (BSP_S32)bsp_sci_data_send(send0_len,send0);
        if(s32Ret != BSP_OK)
        {
            sci_test_error("bsp_sci_data_send fail,ret:%x\n",s32Ret);
            return BSP_ERROR;
        }
        else
        {
            sci_test_error("send success\n");
        }
    }
    else
    {
	    sci_test_error("sim card reset fail\nulCardStatus = %d\n", (BSP_U32) s32Ret,0,0,0,0,0);
        return BSP_ERROR;
    }
    mdrv_sci_deact();
    return BSP_OK;


}

//int mdrv_sci_recv(unsigned int u32DataLength, unsigned char * pu8DataBuffer);

int sci_test_004()
{
    
    BSP_U32 realRecvLen = 0;
    BSP_U8 realRecvData[256] = {0};
    BSP_S32 s32Ret = 0;
    BSP_U32 send0_len = 5;
    BSP_U8 send0[5] = {0xa0,0xa4,0x00,0x00,0x02};
    BSP_U32 recv0_len = 1;
    BSP_U32 send1_len = 2;
    BSP_U8 send1[2] = {0x7f,0x20};
    BSP_U32 recv1_len = 2;
    BSP_S32 i = 0;
    BSP_S32 recv1length = 0;
    

    
    s32Ret = mdrv_sci_reset(COLD_RESET);
    if(s32Ret !=BSP_OK)
    {
        sci_test_error("reset fail\n",__LINE__, send0_len);
        return BSP_ERROR;
    }
    
	osl_task_delay(50);

    s32Ret = (BSP_S32)bsp_sci_data_send(send0_len,send0);
    if(s32Ret != BSP_OK)
    {
        sci_test_error("bsp_sci_data_send fail,ret:%x\n",s32Ret);
        return BSP_ERROR;
    }

    s32Ret = (BSP_S32)bsp_sci_data_read_sync(recv0_len,realRecvData);
    if(s32Ret != BSP_OK)
    {

        s32Ret = (BSP_S32)bsp_sci_all_data_read(&realRecvLen,realRecvData);
        if(s32Ret != BSP_OK)
        {
            sci_test_error("bsp_sci_all_data_read fail,ret:%x\n",s32Ret);
            return BSP_ERROR;
        }
        sci_test_error("realRecvLen:%d\n",realRecvLen);
        for(i = 0; i <(BSP_S32)realRecvLen; i++)
        {
            sci_test_error("realRecvData[%d]:0x%x\n",i,realRecvData[i]);
        }
            return BSP_ERROR;
        }
        for(i = 0; i <(BSP_S32)recv0_len; i++)
        {
            sci_test_error("realRecvData[%d]:0x%x\n",i,realRecvData[i]);
        }   

    
        s32Ret = (BSP_S32)bsp_sci_data_send(send1_len,send1);
        if(s32Ret != BSP_OK)
        {
            sci_test_error("bsp_sci_data_send fail,ret:%x\n",s32Ret);
            return BSP_ERROR;
        }
        s32Ret = (BSP_S32)bsp_sci_data_read_sync(recv1_len,realRecvData);
        if(s32Ret != BSP_OK)
        {
            s32Ret = (BSP_S32)bsp_sci_all_data_read(&realRecvLen,realRecvData);
            if(s32Ret != BSP_OK)
            {
                sci_test_error("bsp_sci_all_data_read fail,ret:%x\n",s32Ret);
                return BSP_ERROR;
            }

            for(i = 0; i <(BSP_S32)realRecvLen; i++)
            {
                sci_test_error("realRecvData[%d]:0x%x\n",i,realRecvData[i]);
            }
            return BSP_ERROR;
        }
        for(i = 0; i <(BSP_S32)recv1_len; i++)
        {
            sci_test_error("realRecvData[%d]:0x%x\n",i,realRecvData[i]);
        }
        recv1length = realRecvData[recv1_len-1];
        sci_test_error("recv success %d\n",recv1length);
        
        mdrv_sci_deact();
        return BSP_OK;
}

//int mdrv_sci_get_atr(unsigned long * u32DataLength, unsigned char * pu8ATR,SCI_ATRINFO_S* stSCIATRInfo);

int sci_test_005()
{
    SCI_ATRINFO_S sci_atr_info;
    s32 s32Ret = 0;
    u32 ulCardStatus;
    u32 revlen;
    u8 atr[40] = {'\0',};
    u32 i ;
    s32Ret = mdrv_sci_reset(COLD_RESET);
    if(s32Ret == BSP_OK)
    {
    
        osl_task_delay(50);
        ulCardStatus = mdrv_sci_get_cardstatus();
        if(ulCardStatus == SCI_CARD_STATE_READY)
        {
            sci_test_error("sim card reset success\n");
            mdrv_sci_get_atr((unsigned long*)&revlen, atr, &sci_atr_info);
            sci_test_error("atr is:\n");
            for(i = 0; i < revlen;i++)
            {
                sci_test_error(" 0x%.2x \n",atr[i]);
            }
        }
        else
        {
            sci_test_error("sim card reset fail\nulCardStatus = %d\n", (BSP_U32) ulCardStatus,0,0,0,0,0);
            return BSP_ERROR;
        }
    
        mdrv_sci_deact();
    }
	return BSP_OK;

}
//unsigned int  mdrv_sci_show_voltage(unsigned int* pu32Vltgval);


//int  mdrv_sci_switch_class(void);
int sci_test_006()
{
    u32 u32Result = 0;
	u32 ulCardStatus;
    u32 vltg;
	u32Result = mdrv_sci_reset(COLD_RESET);
	sci_test_error("\r\n bsp_sci_reset u32Result = %d",u32Result,0,0,0,0,0);
	osl_task_delay(50);
	ulCardStatus = mdrv_sci_get_cardstatus();
    if(ulCardStatus == SCI_CARD_STATE_READY)
    {
        mdrv_sci_show_voltage(&vltg);
        if(vltg == PL131_SCI_Class_C)
        {
            mdrv_sci_switch_class();
                        
            mdrv_sci_show_voltage(&vltg);
            if(vltg == PL131_SCI_Class_B)
            {
                sci_test_error("class switch success\n");
            }
        }
    }
    else
    {
	    sci_test_error("sim card reset fail\nulCardStatus = %d\n", (BSP_U32) ulCardStatus,0,0,0,0,0);
        return BSP_ERROR;
    }
    
    mdrv_sci_deact();
    return BSP_OK;

}

//int mdrv_sci_stop_tm(SCI_CLK_STOP_TYPE_E enTimeStopCfg);

int sci_test_007()
{
    u32 u32Result = 0;
	u32 ulCardStatus;
	u32Result = mdrv_sci_reset(COLD_RESET);
	sci_test_error("\r\n bsp_sci_reset u32Result = %d",u32Result,0,0,0,0,0);
	osl_task_delay(50);
	ulCardStatus = mdrv_sci_get_cardstatus();
    if(ulCardStatus == SCI_CARD_STATE_READY)
    {
        ulCardStatus = mdrv_sci_stop_tm(SCI_CLK_STATE_LOW);
        if(ulCardStatus != BSP_OK)
        {
            
            ulCardStatus = mdrv_sci_stop_tm(SCI_CLK_STATE_HIGH);
            if(ulCardStatus == BSP_OK)
            {
                sci_test_error("stop success\n");
            }
        }
        else
        {
            sci_test_error("stop success\n");
        }

    }
    else
    {
	    sci_test_error("sim card reset fail\nulCardStatus = %d\n", (BSP_U32) ulCardStatus,0,0,0,0,0);
        return BSP_ERROR;
    }
    
    mdrv_sci_deact();
    return BSP_OK;

}

//unsigned int mdrv_sci_deact(void);

int sci_test_008()
{
    u32 u32Result = 0;
	u32 ulCardStatus;
	u32Result = mdrv_sci_reset(COLD_RESET);
	sci_test_error("\r\n bsp_sci_reset u32Result = %d",u32Result,0,0,0,0,0);
	osl_task_delay(50);
	ulCardStatus = mdrv_sci_get_cardstatus();
    if(ulCardStatus == SCI_CARD_STATE_READY)
    {
        sci_test_error("sim card reset success\n");
    }
    else
    {
	    sci_test_error("sim card reset fail\nulCardStatus = %d\n", (BSP_U32) ulCardStatus,0,0,0,0,0);
        return BSP_ERROR;
    }
    mdrv_sci_deact();
    
	if(g_strSciState.eCurrentState == PL131_STATE_INACTIVECARD)
    {
        sci_test_error("deactive succsess\n");
    }   
    return BSP_OK;
    

}

//unsigned int mdrv_sci_get_clkstat(unsigned int * pu32SciClkStatus);
int sci_test_009()
{
    u32 u32Result = 0;
	u32 ulCardStatus;
	u32Result = mdrv_sci_reset(COLD_RESET);
	sci_test_error("\r\n bsp_sci_reset u32Result = %d",u32Result,0,0,0,0,0);
	osl_task_delay(50);
	ulCardStatus = mdrv_sci_get_cardstatus();
    if(ulCardStatus == SCI_CARD_STATE_READY)
    {
        mdrv_sci_get_clkstat(&ulCardStatus);
        sci_test_error("clk status is %d\n",ulCardStatus);
    }
    else
    {
	    sci_test_error("sim card reset fail\nulCardStatus = %d\n", (BSP_U32) ulCardStatus,0,0,0,0,0);
        return BSP_ERROR;
    }
    mdrv_sci_deact();
    return BSP_OK;

}


//unsigned int mdrv_sci_get_clkfreq(unsigned long * pLen,unsigned char * pBuf);
int sci_test_010()
{
    u8   aucSimClkFreq[16];
    int  ulLen = 0;
    int  ulResult;
    u32   ulCardStatus;
	ulResult = mdrv_sci_reset(COLD_RESET);
	sci_test_error("\r\n bsp_sci_reset u32Result = %d",ulResult,0,0,0,0,0);
	osl_task_delay(50);
	ulCardStatus = mdrv_sci_get_cardstatus();
    if(ulCardStatus == SCI_CARD_STATE_READY)
    {
        sci_test_error("sim card reset success\n");
    }
    else
    {
	    sci_test_error("sim card reset fail\nulCardStatus = %d\n", (BSP_U32) ulCardStatus,0,0,0,0,0);
        
        return BSP_ERROR;
    }

    ulResult = mdrv_sci_get_clkfreq((unsigned long*)&ulLen, aucSimClkFreq);
    if(ulResult == BSP_OK)
    {
        sci_test_error("sci_get clkfreq ulLen = %d success\n",ulLen);
        sci_test_error("aucSimClkFreq:\n");

        for(ulResult = 0 ; ulResult < 16;ulResult++)
        {
            sci_test_error(" 0x%.2x\n ");
        }
    }
    mdrv_sci_deact();
    return BSP_OK;



}

//unsigned int mdrv_sci_get_baudrate(unsigned long * pLen, unsigned char * pBuf);

int sci_test_011()
{
    u8 aucSimBaudRate[16];
    u32  ulLen = 0;
    u32  ulResult;
    u32   ulCardStatus;
	ulResult = mdrv_sci_reset(COLD_RESET);
	sci_test_error("\r\n bsp_sci_reset u32Result = %d",ulResult,0,0,0,0,0);
	osl_task_delay(50);
	ulCardStatus = mdrv_sci_get_cardstatus();
    if(ulCardStatus == SCI_CARD_STATE_READY)
    {
        sci_test_error("sim card reset success\n");
    }
    else
    {
	    sci_test_error("sim card reset fail\nulCardStatus = %d\n", (BSP_U32) ulCardStatus,0,0,0,0,0);
        
        return BSP_ERROR;
    }

    ulResult = mdrv_sci_get_baudrate((unsigned long*)&ulLen, aucSimBaudRate);
    if(ulResult == BSP_OK)
    {
        sci_test_error("mdrv_sci_get_baudrate ulLen = %d success\n",ulLen);
        sci_test_error("aucSimBaudRate:\n");

        for(ulResult = 0 ; ulResult < 16;ulResult++)
        {
            sci_test_error(" 0x%.2x\n ");
        }
    }
    mdrv_sci_deact();
    return BSP_OK;

}

//unsigned int mdrv_sci_get_parameter(unsigned char * pBuf);
int sci_test_012()
{
    u8  aucSimPara[5];
    u32  ulResult;
    u32   ulCardStatus;
    ulResult = mdrv_sci_reset(COLD_RESET);
    sci_test_error("\r\n bsp_sci_reset u32Result = %d",ulResult,0,0,0,0,0);
    osl_task_delay(50);
    ulCardStatus = mdrv_sci_get_cardstatus();
    if(ulCardStatus == SCI_CARD_STATE_READY)
    {
        sci_test_error("sim card reset success\n");
    }
    else
    {
         sci_test_error("sim card reset fail\nulCardStatus = %d\n", (BSP_U32) ulCardStatus,0,0,0,0,0);
         return BSP_ERROR;
    }
   
    ulResult = mdrv_sci_get_parameter(aucSimPara);
    if(ulResult == BSP_OK)
    {
        sci_test_error("aucSimPara:\n");

        for(ulResult = 0 ; ulResult < 16;ulResult ++)
        {
            sci_test_error(" 0x%.2x ");
        }
    }
    mdrv_sci_deact();
    return BSP_OK;

}

//void mdrv_sci_save_recorddata(void);
int sci_test_013()
{
    u32 u32Result = 0;
	u32 ulCardStatus;
	u32Result = mdrv_sci_reset(COLD_RESET);
	sci_test_error("\r\n bsp_sci_reset u32Result = %d\n",u32Result,0,0,0,0,0);
	osl_task_delay(50);
	ulCardStatus = mdrv_sci_get_cardstatus();
    if(ulCardStatus == SCI_CARD_STATE_READY)
    {
       mdrv_sci_save_recorddata();
       sci_test_error("save record success\n");
    }
    else
    {
	    sci_test_error("sim card reset fail\nulCardStatus = %d\n", (BSP_U32) ulCardStatus,0,0,0,0,0);
        return BSP_OK;
    }
    mdrv_sci_deact();
    return BSP_OK;
}

void sci_callbck(u32 status)
{
}

//void mdrv_sci_register_callback(OMSCIFUNCPTR omSciFuncPtr);

int sci_test_014()
{
    mdrv_sci_register_callback(sci_callbck) ;
    sci_test_error("register success\n");
    return BSP_OK;
}


















