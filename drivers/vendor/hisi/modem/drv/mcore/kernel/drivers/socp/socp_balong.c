
/*lint -save -e506 -e740*/
#include <osl_common.h>
#include <libfdt.h>
#ifdef K3V3_LPM3_HAS_MODEM_FEATURE
#include "m3_modem.h"
#endif
#include "socp_balong.h"
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
#include "bsp_icc.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif

__ao_data SOCP_GBL_STATE g_strSocpStat = {0};

/*****************************************************************************
* �� �� ��  : socp_memcpy
*
* ��������  : memcpy for socp
*
* �������  :  dst       dst buffer
               src       src buffer
*
* �������  : ��
*
* �� �� ֵ  :  ��
*****************************************************************************/
__ao_func void socp_memcpy(u32 *_dst, const u32 *_src, u32 len)
{
    u32 *dst = _dst;
    const u32 *src = _src;

    while(len-- > 0)
    {
        *dst++ = *src++;
    }

}

#ifndef K3V3_LPM3_HAS_MODEM_FEATURE
/*****************************************************************************
* �� �� ��  : socp_get_idle_buffer
*
* ��������  : ��ѯ���л�����
*
* �������  :  pRingBuffer       ����ѯ�Ļ���buffer
                    pRWBuffer         ����Ļ���buffer
*
* �������  : ��
*
* �� �� ֵ  :  ��
*****************************************************************************/
void socp_get_idle_buffer(SOCP_RING_BUF_S *pRingBuffer, SOCP_BUFFER_RW_STRU *pRWBuffer)
{
    if (pRingBuffer->u32Write < pRingBuffer->u32Read)
    {
        /* ��ָ�����дָ�룬ֱ�Ӽ��� */
        pRWBuffer->pBuffer   = (char *)(pRingBuffer->u32Write);
        pRWBuffer->u32Size   = (u32)(pRingBuffer->u32Read - pRingBuffer->u32Write - 1);
        pRWBuffer->pRbBuffer = NULL;
        pRWBuffer->u32RbSize = 0;
    }
    else
    {
        /* дָ����ڶ�ָ�룬��Ҫ���ǻؾ� */
        if (pRingBuffer->u32Read != pRingBuffer->u32Start)
        {
            pRWBuffer->pBuffer   = (char *)(pRingBuffer->u32Write);
            pRWBuffer->u32Size   = (u32)(pRingBuffer->u32End - pRingBuffer->u32Write + 1);
            pRWBuffer->pRbBuffer = (char *)(pRingBuffer->u32Start);
            pRWBuffer->u32RbSize = (u32)(pRingBuffer->u32Read - pRingBuffer->u32Start - 1);
        }
        else
        {
            pRWBuffer->pBuffer   = (char *)(pRingBuffer->u32Write);
            pRWBuffer->u32Size   = (u32)(pRingBuffer->u32End - pRingBuffer->u32Write);
            pRWBuffer->pRbBuffer = NULL;
            pRWBuffer->u32RbSize = 0;
        }
    }

    return;
}

/*****************************************************************************
* �� �� ��  : socp_write_done
*
* ��������  : ���»�������дָ��
*
* �������  :  pRingBuffer       �����µĻ���buffer
                    u32Size          ���µ����ݳ���
*
* �������  : ��
*
* �� �� ֵ  :  ��
*****************************************************************************/
void socp_write_done(SOCP_RING_BUF_S *pRingBuffer, u32 u32Size)
{
    u32 tmp_size;

    tmp_size = pRingBuffer->u32End - pRingBuffer->u32Write + 1;
    if (tmp_size > u32Size)
    {
        pRingBuffer->u32Write += u32Size;
    }
    else
    {
        u32 rb_size = u32Size - tmp_size;
        pRingBuffer->u32Write = pRingBuffer->u32Start + rb_size;
    }

    return;
}
#endif

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
typedef s32 (*socp_power_cb_func)(s32 flag);
extern s32 socp_power_on(socp_power_cb_func func);
extern s32 socp_power_off(socp_power_cb_func func);
/*****************************************************************************
* �� �� ��  : socp_power_req_cb
*
* ��������  : powerctrlִ�����ϡ��µ�����󣬻ص�
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : �ͷųɹ����ı�ʶ��
*****************************************************************************/
__ao_func s32 socp_power_req_cb(s32 data)
{
    socp_vote_cnf_stru cnf_data;
    u32 chan_id;

    if(data == 0)
    {
        cnf_data.vote_rst = 1;
    }
    else
    {
        cnf_data.vote_rst = 0;
    }

    /* iccͨ���������� */
	chan_id = (ICC_CHN_MCORE_CCORE << 16) | MCORE_CCORE_FUNC_SOCP;
	(void)bsp_icc_send(ICC_CPU_MODEM, chan_id, (u8*)&cnf_data, sizeof(socp_vote_cnf_stru));

    return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : socp_icc_read_cb
*
* ��������  : iccͨ�����ص�����
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : �ͷųɹ����ı�ʶ��
*****************************************************************************/
__ao_func s32 socp_icc_read_cb(u32 id, u32 len, void * context)
{
	s32 ret = 0;
    socp_vote_req_stru req_data;

	ret = bsp_icc_read(id, (u8 *)&req_data, len);
	if(len != (u32)ret)
	{
        return BSP_ERROR;
	}

    if(req_data.type == SOCP_VOTE_FOR_WAKE)
    {
        socp_power_on(socp_power_req_cb);
    }
    else
    {
        socp_power_off(socp_power_req_cb);
    }

	return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : socp_icc_chan_init
*
* ��������  : iccͨ����ʼ��
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : �ͷųɹ����ı�ʶ��
*****************************************************************************/
s32 socp_icc_chan_init(void)
{
    u32 chan_id;

	chan_id = (ICC_CHN_MCORE_CCORE << 16) | MCORE_CCORE_FUNC_SOCP;
	if(ICC_OK != bsp_icc_event_register(chan_id, socp_icc_read_cb, NULL, (write_cb_func)NULL, (void *)NULL))
	{
        return BSP_ERROR;
	}

    return BSP_OK;
}
#endif

/*****************************************************************************
* �� �� ��  : socpInit
*
* ��������  : ģ���ʼ������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��ʼ���ɹ��ı�ʶ��
*****************************************************************************/
void socp_m3_init(void)
{
    u32 i;
    u32 u32ResetValue = 0;
	u32 u32BufAddr = 0;
    struct device_node* dev = NULL;
    u32 version;

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    if(BSP_OK != socp_icc_chan_init())
    {
        return;
    }
#endif

    if (BSP_TRUE == g_strSocpStat.bInitFlag)
    {
        return ;
    }
    memset(&g_strSocpStat, 0, sizeof(SOCP_GBL_STATE));

    dev = of_find_compatible_node(NULL,NULL,"hisilicon,socp_balong_lpm3");
    if(NULL == dev)
    {
        return ;
    }
    g_strSocpStat.baseAddr = (u32)of_iomap(dev,0);
    printk("socp base addr :0x%x\n",g_strSocpStat.baseAddr);
    if(0 == g_strSocpStat.baseAddr)
    {
        return ;
    }



	/* ��ȫ�ּĴ������и�λ */
    SOCP_REG_WRITE(SOCP_REG_GBLRST, 1);
    /* �ȴ�ͨ����λ״̬���� */
    for(i=0; i<SOCP_RESET_TIME; i++)
    {
        SOCP_REG_READ(SOCP_REG_GBLRST, u32ResetValue);
        if(0 == u32ResetValue)
        {
            break;
        }
        if((SOCP_RESET_TIME -1) == i)
        {
			return ;
        }
    }

    /* ����ram�мĴ����ĸ�λ����*/
    for(i=0; i<SOCP_MAX_ENCSRC_CHN; i++)
    {
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(i),0);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFCFG0(i),0);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQWPTR(i),0);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQRPTR(i),0);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQADDR(i),0);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQCFG(i),0);
    }
    for(i=0; i<SOCP_MAX_ENCDST_CHN; i++)
    {
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFADDR(i),0);
    }

    /* ���ô����жϳ�ʱʱ���buffer�����ʱʱ�� */
    SOCP_REG_WRITE(SOCP_REG_INTTIMEOUT, SOCP_TRANS_TIMEOUT_DEFAULT);
    SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 31, 1, 0);
    SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 0, 16, SOCP_OVERFLOW_TIMEOUT_DEFAULT);
    /* ���ý���ͨ·���������üĴ���*/
    SOCP_REG_SETBITS(SOCP_REG_DEC_PKTLEN, 0, 12,  SOCP_DEC_PKTLGTH_MAX);
    SOCP_REG_SETBITS(SOCP_REG_DEC_PKTLEN, 12, 5,  SOCP_DEC_PKTLGTH_MIN);
    /* ʱ���ſأ�����ʱʱ���Զ��ر� */
    writel(0xffffffff, SOCP_REG_BASEADDR + 0x14);

    /* �����ж� */
    SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, 0, 7, 0x7f);
    SOCP_REG_WRITE(SOCP_REG_APP_MASK1, 0xffffffff);
    SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 0, 7, 0x7f);
    SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 16, 7, 0x7f);
    SOCP_REG_WRITE(SOCP_REG_APP_MASK3, 0xffffffff);
    SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, 0, 16, 0xffff);
    SOCP_REG_SETBITS(SOCP_REG_DEC_MASK1, 0, 24, 0xffffff);
    SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK2, 0, 16, 0xffff);


	for (i = 0; i < SOCP_ENCSRC_M3_NUM; i++)
    {
#ifdef K3V3_LPM3_HAS_MODEM_FEATURE
        u32BufAddr = SOCP_M3_LPM3_ENCSRC_ADDR + i*SOCP_M3_CHN_SIZE + K3V3_SHARRED_DDR_SHIFT;
#else
        u32BufAddr = SOCP_M3_LPM3_ENCSRC_ADDR + i*SOCP_M3_CHN_SIZE;
#endif

		SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR((i + SOCP_ENCSRC_LPM3_BASE)), u32BufAddr);
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR((i + SOCP_ENCSRC_LPM3_BASE)), u32BufAddr);
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR((i + SOCP_ENCSRC_LPM3_BASE)), u32BufAddr);

		/*config0 */
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0((i + SOCP_ENCSRC_LPM3_BASE)), 0, 27, SOCP_M3_CHN_SIZE);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0((i + SOCP_ENCSRC_LPM3_BASE)), 27, 5, 0);

        /*����SOCP ����*/
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1((i + SOCP_ENCSRC_LPM3_BASE)), 0, 1, 0);
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1((i + SOCP_ENCSRC_LPM3_BASE)), 1, 2, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1((i + SOCP_ENCSRC_LPM3_BASE)), 4, 4, SOCP_CODER_DST_OM_IND);
        if(0==i)
		{
			SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1((i + SOCP_ENCSRC_LPM3_BASE)), 8, 2, 1);
		}
		else
		{
			SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1((i + SOCP_ENCSRC_LPM3_BASE)), 8, 2, 0);
		}
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1((i + SOCP_ENCSRC_LPM3_BASE)), 10, 1, 0);

        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1((i + SOCP_ENCSRC_LPM3_BASE)), 11, 1, 0);

        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1((i + SOCP_ENCSRC_LPM3_BASE)), 16, 8, 0);

        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1((i + SOCP_ENCSRC_LPM3_BASE)), 31, 1, 0);

        /* ʹ���ж�*/
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT1, (SOCP_ENCSRC_LPM3_BASE + i), 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, (SOCP_ENCSRC_LPM3_BASE + i), 1, 0);

		g_strSocpStat.u32IntEncDstTfr = 0;

    }

    SOCP_REG_READ(SOCP_REG_SOCP_VERSION, version);
    if(SOCP_NEW_VERSION == version)
    {
        /*���߼�ͳһ���ñ���Դ��ȫʹ��*/
        /*0~3��10��ͨ��Ϊ�ǰ�ȫͨ����������Ϊ��ȫͨ��*/
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_SEC_CTRL, 0xffff7bf0);
    }

    /* ���ó�ʼ��״̬ */
    g_strSocpStat.bInitFlag = BSP_TRUE;

    return ;
}

#ifndef K3V3_LPM3_HAS_MODEM_FEATURE
/*****************************************************************************
* �� �� ��  : bsp_socp_get_write_buff
*
* ��������  : �ϲ��ȡд����buffer����
*
* �������  : u32SrcChanID    Դͨ��ID
* �������  : pBuff           ��ȡ��buffer
*
* �� �� ֵ  : ��ȡ�ɹ����ı�ʶ��
*****************************************************************************/
/*lint -save -e18 -e516 */
s32 bsp_socp_get_write_buff(u32 u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff)
{
    u32 u32ChanID;
    u32 u32ChanType;
	SOCP_RING_BUF_S pTempBuff;

    /* �ж��Ƿ��Ѿ���ʼ�� */
    SOCP_CHECK_INIT();

    /* �жϲ�����Ч�� */
    SOCP_CHECK_PARA(pBuff);

	/* �ж�ͨ��ID�Ƿ���Ч */
    u32ChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

	if(SOCP_CODER_SRC_CHAN != u32ChanType)
	{
#ifdef K3V3_LPM3_HAS_MODEM_FEATURE
		PRINT_ERR(BSP_MODU_SOCP,"bsp_socp_get_write_buff:chan id is wrong!\n");
#else
		printk("get_write_buf:wrong chan id\n");
#endif

		return BSP_ERROR;
	}

	/* ���ݶ�дָ���ȡbuffer */
	SOCP_REG_READ(SOCP_REG_ENCSRC_BUFADDR(u32ChanID), pTempBuff.u32Start);
	SOCP_REG_READ(SOCP_REG_ENCSRC_BUFCFG0(u32ChanID), pTempBuff.u32Length);
    SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(u32ChanID), pTempBuff.u32Read);
    SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), pTempBuff.u32Write);

	pTempBuff.u32IdleSize         = 0;
	pTempBuff.u32End  			  = pTempBuff.u32Start+pTempBuff.u32Length-1;

    socp_get_idle_buffer(&pTempBuff, pBuff);

    return BSP_OK;
}
/*lint -restore */
/*****************************************************************************
* �� �� ��  : bsp_socp_write_done
*
* ��������  : д������ɺ���
*
* �������  : u32SrcChanID    Դͨ��ID
              u32WrtSize      д�����ݵĳ���
*
* �������  :
*
* �� �� ֵ  : ����������ı�ʶ��
*****************************************************************************/
s32 bsp_socp_write_done(u32 u32SrcChanID, u32 u32WrtSize)
{
    u32 u32ChanID;
    u32 u32ChanType;
    u32 u32WrtPad;

    SOCP_BUFFER_RW_STRU RwBuff;
	SOCP_RING_BUF_S  pTempBuff;

    /* �ж��Ƿ��Ѿ���ʼ�� */
    SOCP_CHECK_INIT();

    /* �жϲ�����Ч�� */
    SOCP_CHECK_PARA(u32WrtSize);

	/* �ж�ͨ��ID�Ƿ���Ч */
    u32ChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

	if(SOCP_CODER_SRC_CHAN != u32ChanType)
	{
#ifdef K3V3_LPM3_HAS_MODEM_FEATURE
		PRINT_ERR(BSP_MODU_SOCP,"bsp_socp_write_done:chan id is wrong!\n");
#else
		printk("write_done:wrong chan id\n");
#endif
		return BSP_ERROR;
	}

    u32WrtPad = u32WrtSize % 8;
    if (0 != u32WrtPad)
    {
        u32WrtSize += (8 - u32WrtPad);
    }

	SOCP_REG_READ(SOCP_REG_ENCSRC_BUFADDR(u32ChanID), pTempBuff.u32Start);
	SOCP_REG_READ(SOCP_REG_ENCSRC_BUFCFG0(u32ChanID), pTempBuff.u32Length);
    SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(u32ChanID), pTempBuff.u32Read);
    SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), pTempBuff.u32Write);

	pTempBuff.u32IdleSize         = 0;
	pTempBuff.u32End  			  = pTempBuff.u32Start+pTempBuff.u32Length-1;

    socp_get_idle_buffer(&pTempBuff, &RwBuff);
	if(RwBuff.u32Size + RwBuff.u32RbSize <u32WrtSize)
	{
#ifdef K3V3_LPM3_HAS_MODEM_FEATURE
		PRINT_ERR(BSP_MODU_SOCP,"bsp_socp_write_done:write length is larger than idle length!\n");
#else
		printk("write_done:write_len>idle_len\n");
#endif
		return BSP_ERROR;
	}

    /* ���ö�дָ�� */
    socp_write_done(&pTempBuff, u32WrtSize);

    /* д��дָ�뵽дָ��Ĵ���*/
    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), pTempBuff.u32Write);

    return BSP_OK;
}
/*****************************************************************************
* �� �� ��  : bsp_socp_enable
*
* ��������  : ʹ��socp ͨ���������M3 �ϵ�����ͨ��
*
* �������  :
*
* �������  :
*
* �� �� ֵ  : ����������ı�ʶ��
*****************************************************************************/
void bsp_socp_enable(u32 u32SrcChanId)
{
	/**/
	if((u32SrcChanId != SOCP_ENCSRC_LPM3_BASE) && (u32SrcChanId != SOCP_ENCSRC_IOM3_BASE))
	{
		printk("socp_enable:wrong chan id %d\n",u32SrcChanId);

		return ;
	}

	if(!SOCP_REG_GETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32SrcChanId), 0, 1))
	{
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32SrcChanId), 0, 1, 1);
	}

}
#endif

/*****************************************************************************
* �� �� ��  : bsp_socp_get_state
*
* ��������  : ��ȡSOCP״̬
*
* �� �� ֵ  : SOCP_IDLE    ����
*             SOCP_BUSY    æµ
*****************************************************************************/
s32 bsp_socp_get_drx_state(void)
{
    u32 u32EncChanState;
    u32 u32DecChanState;

    SOCP_REG_READ(SOCP_REG_ENCSTAT, u32EncChanState);
    SOCP_REG_READ(SOCP_REG_DECSTAT, u32DecChanState);
    if(u32EncChanState != 0 || u32DecChanState != 0)
    {
        return SOCP_BUSY;
    }

    return SOCP_IDLE;
}

/*****************************************************************************
* �� �� ��  : bsp_socp_drx_backup_reg
*
* ��������  :
*
* �� �� ֵ  :
*****************************************************************************/
s32 bsp_socp_drx_backup_reg(void)
{
	u32 i = 0;
	u32 *g_pu32SocpDrxGlobal = (u32 *)(SOCP_DRX_BACKUP_DDR_ADDR);

	/* judge state */
	if(BSP_OK!=bsp_socp_get_drx_state())
	{
       /* printk("bsp_socp_drx_backup_reg:socp state is not OK!\n"); */
		return BSP_ERROR;
	}

	/* backup regs: global and int  */
    socp_memcpy(g_pu32SocpDrxGlobal, (u32 *)SOCP_REG_ADDR_DRX(SOCP_REG_GBLRST), SOCP_DRX_REG_GBLRST_NUM);
	g_pu32SocpDrxGlobal += SOCP_DRX_REG_GBLRST_NUM;

    socp_memcpy(g_pu32SocpDrxGlobal, (u32 *)SOCP_REG_ADDR_DRX(SOCP_REG_GBL_INTSTAT), SOCP_DRX_REG_ENCINT_NUM);
	g_pu32SocpDrxGlobal +=SOCP_DRX_REG_ENCINT_NUM;

    socp_memcpy(g_pu32SocpDrxGlobal, (u32 *)SOCP_REG_ADDR_DRX(SOCP_REG_DEC_CORE0MASK0), SOCP_DRX_REG_DECINT_NUM);
	g_pu32SocpDrxGlobal +=SOCP_DRX_REG_DECINT_NUM;

	/* backup regs: channel type */
	for(i=0;i<SOCP_MAX_ENCDST_CHN;i++)
	{
		socp_memcpy(g_pu32SocpDrxGlobal, (u32 *)SOCP_REG_ADDR_DRX(SOCP_REG_ENCDEST_BUFWPTR(i)), (sizeof(SOCP_DRX_ENCDST_S)/sizeof(u32)));
		g_pu32SocpDrxGlobal += (sizeof(SOCP_DRX_ENCDST_S)/sizeof(u32));
	}

	for(i=0;i<SOCP_MAX_DECDST_CHN;i++)
	{
		socp_memcpy(g_pu32SocpDrxGlobal, (u32 *)SOCP_REG_ADDR_DRX(SOCP_REG_DECDEST_BUFWPTR(i)), (sizeof(SOCP_DRX_DECDST_S)/sizeof(u32)));
		g_pu32SocpDrxGlobal += (sizeof(SOCP_DRX_DECDST_S)/sizeof(u32));
	}

	for(i=0;i<SOCP_MAX_ENCSRC_CHN;i++)
	{
		socp_memcpy(g_pu32SocpDrxGlobal, (u32 *)SOCP_REG_ADDR_DRX(SOCP_REG_ENCSRC_BUFWPTR(i)), (sizeof(SOCP_DRX_ENCSRC_S)/sizeof(u32)));
		g_pu32SocpDrxGlobal += (sizeof(SOCP_DRX_ENCSRC_S)/sizeof(u32));
	}

	for(i=0;i<SOCP_MAX_DECSRC_CHN;i++)
	{
		socp_memcpy(g_pu32SocpDrxGlobal, (u32 *)SOCP_REG_ADDR_DRX(SOCP_REG_DECSRC_BUFWPTR(i)), (sizeof(SOCP_DRX_DECSRC_S)/sizeof(u32)));
		g_pu32SocpDrxGlobal += (sizeof(SOCP_DRX_DECSRC_S)/sizeof(u32));
	}

    for(i=0;i<SOCP_MAX_ENCSRC_CHN;i++)
    {
        SOCP_REG_SETBITS (SOCP_REG_ENCSRC_BUFCFG1(i), 0, 1, 0);
    }

    for(i=0;i<(SOCP_MAX_DECSRC_CHN);i++)
    {
        SOCP_REG_SETBITS (SOCP_REG_DECSRC_BUFCFG0(i), 30, 1,0);
    }

	return BSP_OK ;
}

/*****************************************************************************
* �� �� ��  : bsp_socp_drx_restore_reg
*
* ��������  :
*
* �� �� ֵ  :
*****************************************************************************/
__ao_func void bsp_socp_drx_restore_reg(void)
{

	u32 i = 0;
	u32 *g_pu32SocpDrxGlobal = (u32 *)(SOCP_DRX_BACKUP_DDR_ADDR);
	SOCP_DRX_ENCSRC_S *a_SocpDrxEncSrc;
	SOCP_DRX_ENCDST_S *a_SocpDrxEncDst;
	SOCP_DRX_DECSRC_S *a_SocpDrxDecSrc;
	SOCP_DRX_DECDST_S *a_SocpDrxDecDst;

	/* backup regs: global and int */
    socp_memcpy((u32 *)SOCP_REG_ADDR_DRX(SOCP_REG_GBLRST), g_pu32SocpDrxGlobal, SOCP_DRX_REG_GBLRST_NUM);
	g_pu32SocpDrxGlobal += SOCP_DRX_REG_GBLRST_NUM;

    socp_memcpy((u32 *)SOCP_REG_ADDR_DRX(SOCP_REG_GBL_INTSTAT), g_pu32SocpDrxGlobal, SOCP_DRX_REG_ENCINT_NUM);
	g_pu32SocpDrxGlobal += SOCP_DRX_REG_ENCINT_NUM;

    socp_memcpy((u32 *)SOCP_REG_ADDR_DRX(SOCP_REG_DEC_CORE0MASK0), g_pu32SocpDrxGlobal, SOCP_DRX_REG_DECINT_NUM);
	g_pu32SocpDrxGlobal += SOCP_DRX_REG_DECINT_NUM;;

    /*lint -save -e740*/
	/* resume regs: channel type */
	for(i=0;i<SOCP_MAX_ENCDST_CHN;i++)
	{
		a_SocpDrxEncDst = (SOCP_DRX_ENCDST_S *)g_pu32SocpDrxGlobal;

		SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFADDR(i), a_SocpDrxEncDst->u32StartAddr);
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFRPTR(i), a_SocpDrxEncDst->u32ReadAddr);
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFWPTR(i), a_SocpDrxEncDst->u32WriteAddr);
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFCFG(i), a_SocpDrxEncDst->u32Config);
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFTHRH(i), a_SocpDrxEncDst->u32Thrh);
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFTHRESHOLD(i), a_SocpDrxEncDst->u32Threshold);

        /*  clean buffer for encdst 1 */


		g_pu32SocpDrxGlobal += (sizeof(SOCP_DRX_ENCDST_S)/sizeof(u32));
	}

	for(i=0;i<SOCP_MAX_DECDST_CHN;i++)
	{
		a_SocpDrxDecDst = (SOCP_DRX_DECDST_S *)g_pu32SocpDrxGlobal;

		SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFADDR(i), a_SocpDrxDecDst->u32StartAddr);
        SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFRPTR(i), a_SocpDrxDecDst->u32ReadAddr);
        SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFWPTR(i), a_SocpDrxDecDst->u32WriteAddr);
        SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFCFG(i),  a_SocpDrxDecDst->u32Config);

		g_pu32SocpDrxGlobal += (sizeof(SOCP_DRX_DECDST_S)/sizeof(u32));
	}

	for(i=0;i<SOCP_MAX_ENCSRC_CHN;i++)
	{
		a_SocpDrxEncSrc= (SOCP_DRX_ENCSRC_S *)g_pu32SocpDrxGlobal;

		SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(i), a_SocpDrxEncSrc->u32StartAddr);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(i), a_SocpDrxEncSrc->u32WriteAddr);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(i), a_SocpDrxEncSrc->u32ReadAddr);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFCFG0(i), a_SocpDrxEncSrc->u32Config0);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQADDR(i), a_SocpDrxEncSrc->u32RDStartAddr);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQRPTR(i), a_SocpDrxEncSrc->u32RDReadAddr);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQWPTR(i), a_SocpDrxEncSrc->u32RDWriteAddr);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQCFG(i),  a_SocpDrxEncSrc->u32RDConfig);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFCFG1(i), a_SocpDrxEncSrc->u32Config1);

		g_pu32SocpDrxGlobal += (sizeof(SOCP_DRX_ENCSRC_S)/sizeof(u32));
	}

	for(i=0;i<SOCP_MAX_DECSRC_CHN;i++)
	{
		a_SocpDrxDecSrc = (SOCP_DRX_DECSRC_S *)g_pu32SocpDrxGlobal;

		SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFADDR(i), a_SocpDrxDecSrc->u32StartAddr);
        SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(i), a_SocpDrxDecSrc->u32WriteAddr);
        SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFRPTR(i), a_SocpDrxDecSrc->u32ReadAddr);
        SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFCFG0(i), a_SocpDrxDecSrc->u32Config );

		g_pu32SocpDrxGlobal += (sizeof(SOCP_DRX_DECSRC_S)/sizeof(u32));
	}
    /*lint -restore*/

	return ;
}

/*****************************************************************************
* �� �� ��  : bsp_socp_suspend
*
* ��������  :
*
* �� �� ֵ  :
*****************************************************************************/
s32 bsp_socp_suspend(void)
{
	return bsp_socp_drx_backup_reg();
}

/*****************************************************************************
* �� �� ��  : bsp_socp_resume
*
* ��������  :
*
* �� �� ֵ  :
*****************************************************************************/
__ao_func void bsp_socp_resume(void)
{
	bsp_socp_drx_restore_reg();
}

/* modem reset */
/*****************************************************************************
* �� �� ��  : bsp_ccore_reset_stop_channel
*
* ��������  :
*
* �� �� ֵ  :
*****************************************************************************/
#ifdef K3V3_LPM3_HAS_MODEM_FEATURE
void bsp_socp_ccore_reset_stop_channel(void)
{
    u32    u32ChanID = 0;

    for (u32ChanID = SOCP_CODER_SRC_LOM_IND2; u32ChanID <= SOCP_CODER_SRC_TDBBP2; u32ChanID++)
    {
		if(u32ChanID == SOCP_CODER_SRC_HIFI)
		{
			continue;
		}

        SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, u32ChanID, 1, 1);

        if(SOCP_ENCSRC_CHNMODE_LIST == SOCP_REG_GETBITS((SOCP_REG_ENCSRC_BUFCFG1(u32ChanID)), 1, 2))
        {
            SOCP_REG_SETBITS(SOCP_REG_MODEM_MASK3, u32ChanID, 1, 1);
        }

        /* ����ͨ���ر�״̬*/
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 0, 1, 0);
    }

    return ;
}

#endif

#ifdef __cplusplus
}
#endif

/*lint -restore*/



