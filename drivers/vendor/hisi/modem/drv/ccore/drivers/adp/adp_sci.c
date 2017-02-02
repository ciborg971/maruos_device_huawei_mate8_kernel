
#include "product_config.h"
#include "mdrv_sci.h"
#include "bsp_om.h"
#include "bsp_sci.h"

SCI_API_MODE sci_api_mode = SCI_API_NORMAL;


/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_RST
*
* ��������  : ���ӿ����ڸ�λSCI��Smart Card Interface��������USIM��Universal 
*           Subscriber Identity Module����
*
* �������  :  ��
* �������  : ��
*
* �� �� ֵ  : OK  ��λ�ɹ�
*
* �޸ļ�¼  :  Yangzhi create
*
*****************************************************************************/
int mdrv_sci_reset(RESET_MODE_E rstMode)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
    
    #if defined(INSTANCE_1)
            return ((int)I1_bsp_sci_reset(rstMode));    
    #elif defined(INSTANCE_2)
            return ((int)I2_bsp_sci_reset(rstMode));
    #else
            return ((int)bsp_sci_reset(rstMode));
    #endif
    }
    else
    {
        return MDRV_ERROR;
    }
}
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_GET_CARD_STAU
*
* ��������  : ���ӿ����ڻ�ÿ���ǰ��״̬
*
* �������  : ��  
* �������  : ��
                 
* �� �� ֵ  :    ��״̬
*           
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
int mdrv_sci_get_cardstatus(BSP_VOID)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
    #if defined(INSTANCE_1)
        return ((int)I1_bsp_sci_card_status_get());
    #elif defined(INSTANCE_2)
        return ((int)I2_bsp_sci_card_status_get());
    #else
        return ((int)bsp_sci_card_status_get());
    #endif
    }
    else
    {
        return SCI_CARD_STATE_NOCARD;
    }


}

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_SND_DATA
*
* ��������  : ���ӿ����ڷ���һ�����ݵ�USIM��
*
* �������  : u32 u32DataLength �������ݵ���Ч���ȡ�ȡֵ��Χ1��256����λΪ�ֽ�  
*             u8 *pu8DataBuffer �������������ڴ���׵�ַ�����Ƕ�̬���䣬���ýӿ�
*                                   ���������ͷţ�������Ӳ����������
* �������  : ��
*
* �� �� ֵ  : OK
*           BSP_ERR_SCI_NOTINIT
*           BSP_ERR_SCI_INVALIDPARA
*           BSP_ERR_SCI_DISABLED
*           BSP_ERR_SCI_NOCARD
*           BSP_ERR_SCI_NODATA
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
int mdrv_sci_send_data(unsigned int u32DataLength,unsigned char * pu8DataBuffer)
{
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
    #if defined(INSTANCE_1)
        return ((int)I1_bsp_sci_data_send(u32DataLength, pu8DataBuffer));
    #elif defined(INSTANCE_2)
        return ((int)I2_bsp_sci_data_send(u32DataLength, pu8DataBuffer));
    #else
        return ((int)bsp_sci_data_send(u32DataLength, pu8DataBuffer));
    #endif
    }
    else
    {
        return MDRV_ERROR;
    }

}

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_RCV
*
* ��������  : ���ӿ�����USIM Manager��ȡ����SCI Driver�Ŀ���������
*             �ýӿ�Ϊ�����ӿڣ�ֻ��SCI���յ��㹻����������Ż᷵�أ�
*             �ýӿڵĳ�ʱ����Ϊ1s
*
* �������  : u32  u32DataLength USIM Manager����SCI Driver��ȡ�����ݳ��ȡ�
* �������  : u8 *pu8DataBuffer USIM Managerָ����Buffer��SCI Driver�����ݿ�������Buffer��
* �� �� ֵ  : OK
*             BSP_ERR_SCI_NOTINIT
*             BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
int mdrv_sci_recv(unsigned int u32DataLength,unsigned char * pu8DataBuffer)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return ((int)I1_bsp_sci_data_read_sync(u32DataLength, pu8DataBuffer));
#elif defined(INSTANCE_2)
        return ((int)I2_bsp_sci_data_read_sync(u32DataLength, pu8DataBuffer));
#else
        return ((int)bsp_sci_data_read_sync(u32DataLength, pu8DataBuffer));

#endif
    }
    else
    {
        return MDRV_ERROR;
    }


}
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_RCV_ALL
*
* ��������  : ���ӿ�����USIM Manager�ڶ�����ʱ��ʱ�򣬵��ñ���������ȡ�������ݻ����е���������
*
* �������  : ��  
* �������  : u32 *u32DataLength Driver��ȡ�����ݳ��ȣ����ظ�USIM Manager��ȡֵ��Χ1��256����λ���ֽ�
*           u8 * pu8DataBuffer USIM Managerָ����Buffer��SCI Driver�����ݿ�������Buffer
*
* �� �� ֵ  : OK
*          BSP_ERR_SCI_NOTINIT
*          BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : 
*
*****************************************************************************/
unsigned int mdrv_sci_recv_all(unsigned int *u32DataLength,unsigned char * pu8DataBuffer)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return ((unsigned int)I1_bsp_sci_all_data_read(u32DataLength, pu8DataBuffer));
#elif defined(INSTANCE_2)
        return ((unsigned int)I2_bsp_sci_all_data_read(u32DataLength, pu8DataBuffer));
#else
        return ((unsigned int)bsp_sci_all_data_read(u32DataLength, pu8DataBuffer));

#endif
    }
    else
    {
        return MDRV_OK;
    }


}
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_GET_ATR
*
* ��������  : ���ӿ����ڽ�Driver�㻺���ATR���ݺ����ݸ������ظ�USIM Manager��
*
* �������  : void  
* �������  : u8 *u8DataLength  Driver��ȡ��ATR���ݳ��ȣ����ظ�USIM Manager��
*                                   ȡֵ��Χ0��32����λ���ֽ�
*           u8 *pu8ATR          USIM Managerָ����Buffer��SCI Driver��ATR
*                                   ���ݿ�������Buffer��һ��Ϊ����ϵͳ������̬����
*                                   ���߾�̬����ĵ�ַ
* 
*
* �� �� ֵ  : OK
*          BSP_ERR_SCI_NOTINIT
*          BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
int mdrv_sci_get_atr(unsigned long * u32DataLength, unsigned char * pu8ATR,SCI_ATRINFO_S* stSCIATRInfo)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return ((int)I1_bsp_sci_atr_get((u8 *)u32DataLength, pu8ATR,stSCIATRInfo));
#elif defined(INSTANCE_2)
        return ((int)I2_bsp_sci_atr_get((u8 *)u32DataLength, pu8ATR,stSCIATRInfo));
#else
        return ((int)bsp_sci_atr_get((u8 *)u32DataLength, pu8ATR,stSCIATRInfo));

#endif
    }
    else
    {
        return MDRV_ERROR;
    }


}
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_CLASS_SWITCH
*
* ��������  : ���ӿ�����֧��PS�Կ��ĵ�ѹ���ͽ����л�����1.8V�л���3V
*
* �������  : BSP_VOID  
* �������  : ��
*
* �� �� ֵ  :  OK    ��ǰ��ѹ������ߵģ����е�ѹ�л�����
*           BSP_ERR_SCI_CURRENT_STATE_ERR �л�ʧ�� current SCI driver state is ready/rx/tx 
*           BSP_ERR_SCI_VLTG_HIGHEST   ��ǰ��ѹ�Ѿ�����ߵ�ѹ��û�н��е�ѹ�л�
*           BSP_ERR_SCI_NOTINIT
*           BSP_ERR_SCI_CURRENT_VLTG_ERR ��ǰ��ѹֵ�쳣����class B����C��
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
int  mdrv_sci_switch_class(void)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return ((int)I1_bsp_sci_vltg_class_switch());
#elif defined(INSTANCE_2)
        return ((int)I2_bsp_sci_vltg_class_switch());
#else
        return ((int)bsp_sci_vltg_class_switch());

#endif
    }
    else
    {
        return MDRV_ERROR;
    }

}
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_SHOW_VLT
*
* ��������  : ���ӿ�������ʾ��ǰSIM���ӿڵ�ѹ
*
* �������  : ��  
* �������  :u32 * pu32Vltgval ��ǰ��ѹ
*
* �� �� ֵ  : OK
*          BSP_ERR_SCI_NOTINIT
*          BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : 
*
*****************************************************************************/
unsigned int  mdrv_sci_show_voltage(unsigned int* pu32Vltgval)
{
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return ((unsigned int)I1_bsp_sci_show_vltg_val(pu32Vltgval));
#elif defined(INSTANCE_2)
        return ((unsigned int)I2_bsp_sci_show_vltg_val(pu32Vltgval));
#else
        return ((unsigned int)bsp_sci_show_vltg_val(pu32Vltgval));

#endif
    }
    else
    {
        return MDRV_OK;
    }

}
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_TM_STOP
*
* ��������  : ���ӿ�����֧��PS�ر�SIM��ʱ��
*
* �������  : 
*           SCI_CLK_STOP_TYPE_E enTimeStopCfg ʱ��ֹͣģʽ
*   
* �������  : ��
*
* �� �� ֵ  : OK - successful completion
*               ERROR - failed
*               BSP_ERR_SCI_NOTINIT
*               BSP_ERR_SCI_INVALIDPARA - invalid mode specified
*               BSP_ERR_SCI_UNSUPPORTED - not support such a operation
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
int mdrv_sci_stop_tm(SCI_CLK_STOP_TYPE_E enTimeStopCfg)
{
        
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return I1_bsp_sci_clk_status_cfg((u32)enTimeStopCfg);
#elif defined(INSTANCE_2)
        return I2_bsp_sci_clk_status_cfg((u32)enTimeStopCfg);
#else
        return bsp_sci_clk_status_cfg((u32)enTimeStopCfg);

#endif

     }
     else
     {
        return MDRV_ERROR;
     }

}
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_DEACT
*
* ��������  : ���ӿ����ڶ�SIM����ȥ�������
*
* �������  : ��
*   
* �������  : ��
*
* �� �� ֵ  : OK
*             BSP_ERR_SCI_NOTINIT
* �޸ļ�¼  : 
*
*****************************************************************************/
unsigned int mdrv_sci_deact(void)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return I1_bsp_sci_deactive();
#elif defined(INSTANCE_2)
        return I2_bsp_sci_deactive();
#else
        return bsp_sci_deactive();

#endif
    }
    else
    {
        return MDRV_OK;
    }


}
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_GET_CLK_STAU
*
* ��������  : ���ӿ����ڻ�ȡ��ǰSIM��ʱ��״̬
*
* �������  : u32 *pu32SciClkStatus   ����ָ�룬���ڷ���SIM��ʱ��״̬��
*                                       0��ʱ���Ѵ򿪣�
*                                       1��ʱ��ֹͣ 
* �������  : ��
*
* �� �� ֵ  : OK    �����ɹ�
*          BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : 
*
*****************************************************************************/
unsigned int mdrv_sci_get_clkstat(unsigned int * pu32SciClkStatus)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return (unsigned int)I1_bsp_sci_get_clk_status(pu32SciClkStatus);
#elif defined(INSTANCE_2)
        return (unsigned int)I2_bsp_sci_get_clk_status(pu32SciClkStatus);
#else
        return (unsigned int)bsp_sci_get_clk_status(pu32SciClkStatus);

#endif
    }
    else
    {
        return MDRV_OK;
    }

}

/*****************************************************************************
* �� �� ��  : DRV_PCSC_GET_CLK_FREQ
*
* ��������  : ���ӿ����ڻ�ȡ��ǰSIM��ʱ��Ƶ��
*
* �������  : ��
*
* �������  : BSP_U32 *pLen   ʱ��Ƶ�����ݵĳ���
*             BSP_U8 *pBuf    ʱ��Ƶ������
* �� �� ֵ  : OK    �����ɹ�
*             BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_sci_get_clkfreq(unsigned long * pLen,unsigned char * pBuf)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
    
#if defined(INSTANCE_1)
        return (unsigned int)I1_appl131_get_clk_freq((u32*)pLen, pBuf);
#elif defined(INSTANCE_2)
        return (unsigned int)I2_appl131_get_clk_freq((u32*)pLen, pBuf);
#else
        return (unsigned int)appl131_get_clk_freq((u32*)pLen, pBuf);

#endif
    }
    else
    {
        return MDRV_OK;
    }
}

/*****************************************************************************
* �� �� ��  : DRV_PCSC_GET_BAUD_RATE
*
* ��������  : ���ӿ����ڻ�ȡ��ǰSIM��������
*
* �������  : ��
*
* �������  : BSP_U32 *pLen   ���������ݵĳ���
*             BSP_U8 *pBuf    ����������
*
* �� �� ֵ  : OK    �����ɹ�
*             BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : 
*
*****************************************************************************/
unsigned int mdrv_sci_get_baudrate(unsigned long * pLen, unsigned char * pBuf)
{
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
    
#if defined(INSTANCE_1)
        return (unsigned int)I1_appl131_get_baud_rate((u32*)pLen, pBuf);
#elif defined(INSTANCE_2)
        return (unsigned int)I2_appl131_get_baud_rate((u32*)pLen, pBuf);
#else
        return (unsigned int)appl131_get_baud_rate((u32*)pLen, pBuf);

#endif
    }
    else
    {
        return MDRV_OK;
    }
}


/*****************************************************************************
* �� �� ��  : DRV_PCSC_GET_SCI_PARA
*
* ��������  : ���ӿ����ڻ�ȡ��ǰSIM����PCSC��ز���
*
* �������  : ��
*
* �������  : u8 *pBuf    PCSC��ز���
*
* �� �� ֵ  : OK    �����ɹ�
*             BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_sci_get_parameter(unsigned char * pBuf)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
    
#if defined(INSTANCE_1)
        return (unsigned int)I1_appl131_get_pcsc_paremeter(pBuf);
#elif defined(INSTANCE_2)
        return (unsigned int)I2_appl131_get_pcsc_paremeter(pBuf);
#else
        return (unsigned int)appl131_get_pcsc_paremeter(pBuf);

#endif
    }
    else
    {
        return MDRV_OK;
    }

}


/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_FUNC_REGISTER
*
* ��������  : ���ӿ�����ע��OAM  �ص�����
* �������  : void  
* �������  : ��
*
* �� �� ֵ  : OK  ��λ�ɹ�
*
* �޸ļ�¼  : 
*
*****************************************************************************/
void mdrv_sci_register_callback(OMSCIFUNCPTR omSciFuncPtr)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        I1_bsp_sci_func_register(omSciFuncPtr);
#elif defined(INSTANCE_2)
        I2_bsp_sci_func_register(omSciFuncPtr);
#else
        bsp_sci_func_register(omSciFuncPtr);

#endif
    }

}

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_RECORD_DATA_SAVE
*
* ��������  : ���ӿڿ�ά�ɲ���Ϣ��¼
* �������  : void  
* �������  : ��
*
* �� �� ֵ  : OK  �ɹ�
*
* �޸ļ�¼  : 
*
*****************************************************************************/
void mdrv_sci_save_recorddata(void) 
{
    SCI_LOG_MODE log_mode = SCI_LOG_RESET_FAIL;
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        (void)I1_bsp_sci_record_data_save(log_mode);
#elif defined(INSTANCE_2)
        (void)I2_bsp_sci_record_data_save(log_mode);
#else
        (void)bsp_sci_record_data_save(log_mode);

#endif
    }
}

/* T=1 add Begin:*/

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_SETBWT
*
* ��������  : ���ӿ��������ÿ�ȴ�ʱ��
*
* �������  : BSP_U32 nBWT :���ó�ʱʱ��ΪBWT��nBWT��
*
* �������  : ��
*
* �� �� ֵ  : OK/ERROR
* �޸ļ�¼  : 2013��10��15��   liuyi  creat
*
*****************************************************************************/
int mdrv_sci_set_bwt(unsigned int nBWT)
{
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return (int)I1_bsp_sci_set_bwt(nBWT);
#elif defined(INSTANCE_2)
        return (int)I2_bsp_sci_set_bwt(nBWT);
#else
        return (int)bsp_sci_set_bwt(nBWT);

#endif
    }
    else
    {
        return MDRV_ERROR;
    }

}

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_PROTOCOL_SWITCH
*
* ��������  : ���ӿ�����֪ͨ�������T=0��T=1Э�������л�
*
* �������  : RESET_MODE enSIMProtocolMode:��Ҫ�л�Ϊ��Э������
*
* �������  : ��
*
* �� �� ֵ  : OK/ERROR
* �޸ļ�¼  : 2013��10��15��   liuyi  creat
*
*****************************************************************************/
int mdrv_sci_switch_protocol(PROTOCOL_MODE_E enSIMProtocolMode)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return (int)I1_bsp_sci_protocol_switch(enSIMProtocolMode);
#elif defined(INSTANCE_2)
        return (int)I2_bsp_sci_protocol_switch(enSIMProtocolMode);
#else
        return (int)bsp_sci_protocol_switch(enSIMProtocolMode);

#endif
    }
    else
    {
        return MDRV_ERROR;
    }

}

/*****************************************************************************
* �� �� ��  : BSP_SCI_BLK_Receive
* ��������  : ���ӿ�������T=1ʱUSIM Manager��ȡ����SCI Driver�Ŀ��������ݣ�
*             �������BWT��ʱ�������ݶ�ȡʱ����һ����ʱ��ֵSCI_TIMEOUT
*
* �������  : ��
* �������  : BSP_U8 *pu8Data USIM Managerָ����Buffer��SCI Driver�����ݿ�������Buffer��
              BSP_U32 *pulLength SCI Driver���յ������ݳ��ȡ�

* �� �� ֵ  : OK : 0
              ERROR : -1
              SCI_TIMEOUT : 1
*
* �޸ļ�¼  : 2013��10��15��   liuyi  creat
*
*****************************************************************************/
int mdrv_sci_rcv_blk(unsigned char *pu8Data, unsigned int *pulLength)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return (int)I1_bsp_sci_blk_rcv(pu8Data, pulLength);
#elif defined(INSTANCE_2)
        return (int)I2_bsp_sci_blk_rcv(pu8Data, pulLength);
#else
        return (int)bsp_sci_blk_rcv(pu8Data, pulLength);

#endif
    }
    else
    {
        return MDRV_ERROR;
    }
}

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_RECORDLOG_READ
*
* ��������  : ���ӿڻ�ȡsim���쳣ʱ��λ��Ϣ
* �������  : pucDataBuff: ��ȡ��λ��Ϣ��buffer
              ulMaxLength: ���ֵ���ж�ʹ��
*
* �� �� ֵ  : pulLength: ��ȡ���ݳ���
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 

*
* �޸ļ�¼  : 
*
*****************************************************************************/
int  mdrv_sci_read_recordlog(unsigned char *pucDataBuff, unsigned int * pulLength, unsigned int ulMaxLength)
{
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return I1_bsp_sci_record_log_read(pucDataBuff, pulLength, ulMaxLength);
#elif defined(INSTANCE_2)
        return I2_bsp_sci_record_log_read(pucDataBuff, pulLength, ulMaxLength);
#else
        return bsp_sci_record_log_read(pucDataBuff, pulLength, ulMaxLength);

#endif
    }
    else
    {
        return MDRV_ERROR;
    }

}

/* T=1 add End */
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_GET_ERRNO
*
* ��������  : ���ӿڻ�ȡ�ӿڵ��÷��صĴ�����
* �������  :  ��
* �������  :  ��
*
* �� �� ֵ  : ������
*
* �޸ļ�¼  : 
*
*****************************************************************************/
int mdrv_sci_get_errno(void) 
{
	return BSP_OK;
}

/*****************************************************************************
 * �� �� ��  : mdrv_sci_slot_switch
 *
 * ��������  : �л����뿨�۵Ķ�Ӧ��ϵ
 * �������  : sci_slot0 ����0������״̬
 *                           sci_slot1 ����1������״̬
 *
 * �� �� ֵ  : �л����
 *
 *
 * �� �� ֵ  : ��
 *
 * �޸ļ�¼  :
 *
 *****************************************************************************/
int mdrv_sci_slot_switch(SCI_SLOT sci_slot0,SCI_SLOT sci_slot1,SCI_SLOT sci_slot2)
{
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return I1_bsp_sci_slot_switch(sci_slot0,sci_slot1,sci_slot2);
#elif defined(INSTANCE_2)
        return I2_bsp_sci_slot_switch(sci_slot0,sci_slot1,sci_slot2);
#else
        return bsp_sci_slot_switch(sci_slot0,sci_slot1,sci_slot2);

#endif
    }
    else
    {
        return MDRV_ERROR;
    }

}

/*****************************************************************************
 * �� �� ��  : mdrv_sci_get_slot_state
 *
 * ��������  : ��ȡ���۵Ķ�Ӧ��ϵ
 * �������  : sci_slot0 ����0��״̬
 *                           sci_slot1 ����1��״̬
 *
 * �� �� ֵ  : �л����
 *
 *
 * �� �� ֵ  : ��
 *
 * �޸ļ�¼  :
 *
 *****************************************************************************/

int mdrv_sci_get_slot_state(SCI_SLOT* sci_slot0,SCI_SLOT* sci_slot1,SCI_SLOT* sci_slot2)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
            return I1_bsp_sci_get_slot_state(sci_slot0,sci_slot1,sci_slot2);
#elif defined(INSTANCE_2)
            return I2_bsp_sci_get_slot_state(sci_slot0,sci_slot1,sci_slot2);
#else
            return bsp_sci_get_slot_state(sci_slot0,sci_slot1,sci_slot2);

#endif
    }
    else
    {
        return MDRV_ERROR;
    }


}


