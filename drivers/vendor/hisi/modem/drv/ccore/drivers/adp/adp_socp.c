

#include "bsp_socp.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef ENABLE_BUILD_SOCP /* do not build socp, stub */
/*****************************************************************************
* �� �� ��  : DRV_SOCP_INIT
*
* ��������  : ģ���ʼ������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��ʼ���ɹ��ı�ʶ��
*****************************************************************************/
int DRV_SOCP_INIT()
{
    return 0;
}
int socp_init(void)
{
    return 0;
}


/*****************************************************************************
 �� �� ��  : DRV_SOCP_CORDER_SET_SRC_CHAN
 ��������  : �˽ӿ����SOCP������Դͨ���ķ��䣬���ݱ�����Դͨ����������ͨ�����ԣ�����Ŀ��ͨ�������غ���ִ�н����
 �������  : pSrcAttr:������Դͨ�������ṹ��ָ�롣
             pSrcChanID:���뵽��Դͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:����Դͨ������ɹ���
             SOCP_ERROR:����Դͨ������ʧ�ܡ�
*****************************************************************************/
int mdrv_socp_corder_set_src_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID, SOCP_CODER_SRC_CHAN_S *pSrcAttr)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_FREE_CHANNEL
 ��������  : �˽ӿڸ���ͨ��ID�ͷŷ���ı����ͨ����
 �������  : u32ChanID:ͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:ͨ���ͷųɹ���
             SOCP_ERROR:ͨ���ͷ�ʧ�ܡ�
*****************************************************************************/
int DRV_SOCP_FREE_CHANNEL(unsigned int u32ChanID)
{
    return 0;
}

/*****************************************************************************
* �� �� ��  : DRV_SOCP_CLEAN_ENCSRC_CHAN
*
* ��������  : ��ձ���Դͨ����ͬ��V9 SOCP�ӿ�
*
* �������  : enSrcChanID       ����ͨ����
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK
*****************************************************************************/
unsigned int DRV_SOCP_CLEAN_ENCSRC_CHAN(SOCP_CODER_SRC_ENUM_U32 enSrcChanID)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_REGISTER_EVENT_CB
 ��������  : �˽ӿ�Ϊ����ͨ��ע���¼��ص�������
 �������  : u32ChanID:ͨ��ID��
             EventCB:�¼��ص��������ο�socp_event_cb��������
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:ע���¼��ص������ɹ���
             SOCP_ERROR:ע���¼��ص�����ʧ�ܡ�
*****************************************************************************/
int DRV_SOCP_REGISTER_EVENT_CB(unsigned int u32ChanID, socp_event_cb EventCB)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_START
 ��������  : �˽ӿ�����Դͨ��������������߽��롣
 �������  : u32SrcChanID:Դͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:�������������ɹ���
             SOCP_ERROR:������������ʧ�ܡ�
*****************************************************************************/
int mdrv_socp_start(unsigned int u32SrcChanID)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : mdrv_socp_stop
 ��������  : �˽ӿ�����Դͨ����ֹͣ������߽��롣
 �������  : u32SrcChanID:Դͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��������ֹͣ�ɹ���
             SOCP_ERROR:��������ֹͣʧ�ܡ�
*****************************************************************************/
int mdrv_socp_stop(unsigned int u32SrcChanID)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_CHAN_SOFT_RESET
 ��������  : Դͨ����λ
 �������  : u32ChanID:ͨ��ID
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:�踴λ�ɹ���
             ����ֵ:��λʧ��
*****************************************************************************/
int DRV_SOCP_CHAN_SOFT_RESET(unsigned int u32ChanID)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_GET_WRITE_BUFF
 ��������  : �˽ӿ����ڻ�ȡд����buffer��
 �������  : u32SrcChanID:Դͨ��ID
             pBuff:           :д����buffer

 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��ȡд����buffer�ɹ���
             SOCP_ERROR:��ȡд����bufferʧ��
*****************************************************************************/
int mdrv_socp_get_write_buff( unsigned int u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : mdrv_socp_write_done
 ��������  : �ýӿ��������ݵ�д�������ṩд�����ݵĳ��ȡ�
 �������  : u32SrcChanID:Դͨ��ID
             u32WrtSize:   ��д�����ݵĳ���
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:д�����ݳɹ���
             SOCP_ERROR:д������ʧ��
*****************************************************************************/
int mdrv_socp_write_done(unsigned int u32SrcChanID, unsigned int u32WrtSize)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_REGISTER_RD_CB
 ��������  : �ýӿ�����ע���RD�������ж�ȡ���ݵĻص�������
 �������  : u32SrcChanID:Դͨ��ID
             RdCB:  �¼��ص�����
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:ע��RD���λ����������ݻص������ɹ���
             SOCP_ERROR:ע��RD���λ����������ݻص�����ʧ��
*****************************************************************************/
int DRV_SOCP_REGISTER_RD_CB(unsigned int u32SrcChanID, socp_rd_cb RdCB)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : mdrv_socp_get_rd_buffer
 ��������  : �ô˽ӿ����ڻ�ȡRD buffer������ָ�롣
 �������  : u32SrcChanID:Դͨ��ID
             pBuff:  RD buffer
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��ȡRD���λ������ɹ�
             SOCP_ERROR:��ȡRD���λ�����ʧ��
*****************************************************************************/
int mdrv_socp_get_rd_buffer( unsigned int u32SrcChanID,SOCP_BUFFER_RW_STRU *pBuff)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : bsp_socp_read_rd_done
 ��������  : �˽ӿ������ϲ�֪ͨSOCP��������RD buffer��ʵ�ʶ�ȡ�����ݡ�
 �������  : u32SrcChanID:Դͨ��ID
             u32RDSize:  ��RD buffer��ʵ�ʶ�ȡ�����ݳ���
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��ȡRDbuffer�е����ݳɹ�
             SOCP_ERROR:��ȡRDbuffer�е�����ʧ��
*****************************************************************************/
int mdrv_socp_read_rd_done(unsigned int u32SrcChanID, unsigned int u32RDSize)
{
    return 0;
}

/*****************************************************************************
* �� �� ��  : DRV_SOCP_DSPCHN_START
* ��������  : enable DSP channel
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
void  DRV_SOCP_DSPCHN_START(void)
{
    return;
}

/*****************************************************************************
* �� �� ��  : DRV_SOCP_DSPCHN_STOP
* ��������  : disable DSP channel
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
void  DRV_SOCP_DSPCHN_STOP(void)
{
    return;
}

/*****************************************************************************
* �� �� ��  : DRV_BBPDMA_DRX_BAK_REG
* ��������  : BBPDMA����
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
int  DRV_BBPDMA_DRX_BAK_REG(void)
{
    return 0;
}

/*****************************************************************************
* �� �� ��  : DRV_BBPDMA_DRX_RESTORE_REG
* ��������  : �ָ�BBPDMA
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
int  DRV_BBPDMA_DRX_RESTORE_REG(void)
{
    return 0;
}


/*****************************************************************************
* �� �� ��  : DRV_SOCP_GET_STATE
*
* ��������  : ��ȡSOCP״̬
*
* �� �� ֵ  : SOCP_IDLE    ����
*             SOCP_BUSY    æµ
*****************************************************************************/
SOCP_STATE_ENUM_UINT32 DRV_SOCP_GET_STATE(void)
{
    return 0;
}

unsigned int  DRV_SOCP_INIT_LTE_DSP(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize)
{
    return 0;
}

unsigned int  DRV_SOCP_INIT_LTE_BBP_LOG(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize)
{
    return 0;
}

unsigned int  DRV_SOCP_INIT_LTE_BBP_DS(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize)
{
    return 0;
}

void DRV_SOCP_ENABLE_LTE_BBP_DSP(unsigned int ulChanId)
{
    return;
}

/*****************************************************************************
* �� �� ��  : DRV_SOCP_VOTE_TO_MCORE
* ��������  : SOCPͶƱ�ӿڣ��ýӿ�ֻ��C���ṩ������LDSP�״μ��ص�SOCP�ϵ�����
* �������  : type --- ͶƱ����
* �������  : ��
* �� �� ֵ  : int 0 --- ͶƱ�ɹ���0xFFFFFFFF --- ͶƱʧ��
*****************************************************************************/
int DRV_SOCP_VOTE_TO_MCORE(SOCP_VOTE_TYPE_ENUM_U32 type)
{
    return 0;
}

#else
/*****************************************************************************
* �� �� ��  : DRV_SOCP_INIT
*
* ��������  : ģ���ʼ������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��ʼ���ɹ��ı�ʶ��
*****************************************************************************/
int DRV_SOCP_INIT()
{
    return socp_init();
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_CORDER_SET_SRC_CHAN
 ��������  : �˽ӿ����SOCP������Դͨ���ķ��䣬���ݱ�����Դͨ����������ͨ�����ԣ�����Ŀ��ͨ�������غ���ִ�н����
 �������  : pSrcAttr:������Դͨ�������ṹ��ָ�롣
             pSrcChanID:���뵽��Դͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:����Դͨ������ɹ���
             SOCP_ERROR:����Դͨ������ʧ�ܡ�
*****************************************************************************/
int mdrv_socp_corder_set_src_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID, SOCP_CODER_SRC_CHAN_S *pSrcAttr)
{
    return bsp_socp_coder_set_src_chan(enSrcChanID, pSrcAttr);
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_FREE_CHANNEL
 ��������  : �˽ӿڸ���ͨ��ID�ͷŷ���ı����ͨ����
 �������  : u32ChanID:ͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:ͨ���ͷųɹ���
             SOCP_ERROR:ͨ���ͷ�ʧ�ܡ�
*****************************************************************************/
int DRV_SOCP_FREE_CHANNEL(unsigned int u32ChanID)
{
    return bsp_socp_free_channel(u32ChanID);
}

/*****************************************************************************
* �� �� ��  : DRV_SOCP_CLEAN_ENCSRC_CHAN
*
* ��������  : ��ձ���Դͨ����ͬ��V9 SOCP�ӿ�
*
* �������  : enSrcChanID       ����ͨ����
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK
*****************************************************************************/
unsigned int DRV_SOCP_CLEAN_ENCSRC_CHAN(SOCP_CODER_SRC_ENUM_U32 enSrcChanID)
{
    return bsp_socp_clean_encsrc_chan(enSrcChanID);
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_REGISTER_EVENT_CB
 ��������  : �˽ӿ�Ϊ����ͨ��ע���¼��ص�������
 �������  : u32ChanID:ͨ��ID��
             EventCB:�¼��ص��������ο�socp_event_cb��������
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:ע���¼��ص������ɹ���
             SOCP_ERROR:ע���¼��ص�����ʧ�ܡ�
*****************************************************************************/
int DRV_SOCP_REGISTER_EVENT_CB(unsigned int u32ChanID, socp_event_cb EventCB)
{
    return bsp_socp_register_event_cb(u32ChanID, EventCB);
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_START
 ��������  : �˽ӿ�����Դͨ��������������߽��롣
 �������  : u32SrcChanID:Դͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:�������������ɹ���
             SOCP_ERROR:������������ʧ�ܡ�
*****************************************************************************/
int mdrv_socp_start(unsigned int u32SrcChanID)
{
    return bsp_socp_start(u32SrcChanID);
}

/*****************************************************************************
 �� �� ��  : mdrv_socp_stop
 ��������  : �˽ӿ�����Դͨ����ֹͣ������߽��롣
 �������  : u32SrcChanID:Դͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��������ֹͣ�ɹ���
             SOCP_ERROR:��������ֹͣʧ�ܡ�
*****************************************************************************/
int mdrv_socp_stop(unsigned int u32SrcChanID)
{
    return bsp_socp_stop(u32SrcChanID);
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_CHAN_SOFT_RESET
 ��������  : Դͨ����λ
 �������  : u32ChanID:ͨ��ID
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:�踴λ�ɹ���
             ����ֵ:��λʧ��
*****************************************************************************/
int DRV_SOCP_CHAN_SOFT_RESET(unsigned int u32ChanID)
{
    return bsp_socp_chan_soft_reset(u32ChanID);
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_GET_WRITE_BUFF
 ��������  : �˽ӿ����ڻ�ȡд����buffer��
 �������  : u32SrcChanID:Դͨ��ID
             pBuff:           :д����buffer

 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��ȡд����buffer�ɹ���
             SOCP_ERROR:��ȡд����bufferʧ��
*****************************************************************************/
int mdrv_socp_get_write_buff( unsigned int u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff)
{
    return bsp_socp_get_write_buff(u32SrcChanID, pBuff);
}

/*****************************************************************************
 �� �� ��  : mdrv_socp_write_done
 ��������  : �ýӿ��������ݵ�д�������ṩд�����ݵĳ��ȡ�
 �������  : u32SrcChanID:Դͨ��ID
             u32WrtSize:   ��д�����ݵĳ���
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:д�����ݳɹ���
             SOCP_ERROR:д������ʧ��
*****************************************************************************/
int mdrv_socp_write_done(unsigned int u32SrcChanID, unsigned int u32WrtSize)
{
    return bsp_socp_write_done(u32SrcChanID, u32WrtSize);
}

/*****************************************************************************
 �� �� ��  : DRV_SOCP_REGISTER_RD_CB
 ��������  : �ýӿ�����ע���RD�������ж�ȡ���ݵĻص�������
 �������  : u32SrcChanID:Դͨ��ID
             RdCB:  �¼��ص�����
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:ע��RD���λ����������ݻص������ɹ���
             SOCP_ERROR:ע��RD���λ����������ݻص�����ʧ��
*****************************************************************************/
int DRV_SOCP_REGISTER_RD_CB(unsigned int u32SrcChanID, socp_rd_cb RdCB)
{
    return bsp_socp_register_rd_cb(u32SrcChanID, RdCB);
}

/*****************************************************************************
 �� �� ��  : mdrv_socp_get_rd_buffer
 ��������  : �ô˽ӿ����ڻ�ȡRD buffer������ָ�롣
 �������  : u32SrcChanID:Դͨ��ID
             pBuff:  RD buffer
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��ȡRD���λ������ɹ�
             SOCP_ERROR:��ȡRD���λ�����ʧ��
*****************************************************************************/
int mdrv_socp_get_rd_buffer( unsigned int u32SrcChanID,SOCP_BUFFER_RW_STRU *pBuff)
{
    return bsp_socp_get_rd_buffer(u32SrcChanID, pBuff);
}

/*****************************************************************************
 �� �� ��  : bsp_socp_read_rd_done
 ��������  : �˽ӿ������ϲ�֪ͨSOCP��������RD buffer��ʵ�ʶ�ȡ�����ݡ�
 �������  : u32SrcChanID:Դͨ��ID
             u32RDSize:  ��RD buffer��ʵ�ʶ�ȡ�����ݳ���
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��ȡRDbuffer�е����ݳɹ�
             SOCP_ERROR:��ȡRDbuffer�е�����ʧ��
*****************************************************************************/
int mdrv_socp_read_rd_done(unsigned int u32SrcChanID, unsigned int u32RDSize)
{
    return bsp_socp_read_rd_done(u32SrcChanID, u32RDSize);
}

/*****************************************************************************
* �� �� ��  : DRV_SOCP_DSPCHN_START
* ��������  : enable DSP channel
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
void  DRV_SOCP_DSPCHN_START(void)
{
    bsp_socp_start_dsp();
}

/*****************************************************************************
* �� �� ��  : DRV_SOCP_DSPCHN_STOP
* ��������  : disable DSP channel
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
void  DRV_SOCP_DSPCHN_STOP(void)
{
    bsp_socp_stop_dsp();
}

/*****************************************************************************
* �� �� ��  : DRV_BBPDMA_DRX_BAK_REG
* ��������  : BBPDMA����
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
extern int BSP_BBPDMA_DrxBakReg(void);
int  DRV_BBPDMA_DRX_BAK_REG(void)
{
    return (int)BSP_BBPDMA_DrxBakReg();
}

/*****************************************************************************
* �� �� ��  : DRV_BBPDMA_DRX_RESTORE_REG
* ��������  : �ָ�BBPDMA
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
extern int BSP_BBPDMA_DrxRestoreReg(void);
int  DRV_BBPDMA_DRX_RESTORE_REG(void)
{
    return BSP_BBPDMA_DrxRestoreReg();
}


/*****************************************************************************
* �� �� ��  : DRV_SOCP_GET_STATE
*
* ��������  : ��ȡSOCP״̬
*
* �� �� ֵ  : SOCP_IDLE    ����
*             SOCP_BUSY    æµ
*****************************************************************************/
SOCP_STATE_ENUM_UINT32 DRV_SOCP_GET_STATE(void)
{
    return bsp_socp_get_state();
}

extern unsigned int bsp_socp_init_lte_dsp(u32 ulChanId,u32 ulPhyAddr,u32 ulSize);
unsigned int DRV_SOCP_INIT_LTE_DSP(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize)
{
    return bsp_socp_init_lte_dsp(ulChanId,ulPhyAddr,ulSize);
}

extern unsigned int bsp_socp_init_lte_bbp_log(u32 ulChanId,u32 ulPhyAddr,u32 ulSize);
unsigned int DRV_SOCP_INIT_LTE_BBP_LOG(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize)
{
    return bsp_socp_init_lte_bbp_log(ulChanId,ulPhyAddr,ulSize);
}

extern unsigned int bsp_socp_int_lte_bbp_ds(u32 ulChanId,u32 ulPhyAddr,u32 ulSize);
unsigned int DRV_SOCP_INIT_LTE_BBP_DS(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize)
{
    return bsp_socp_int_lte_bbp_ds(ulChanId,ulPhyAddr,ulSize);
}

extern void bsp_socp_enable_lte_dsp_bbp(u32 ulChanId);
void DRV_SOCP_ENABLE_LTE_BBP_DSP(unsigned int ulChanId)
{
    bsp_socp_enable_lte_dsp_bbp(ulChanId);
}

/*****************************************************************************
* �� �� ��  : DRV_SOCP_VOTE_TO_MCORE
* ��������  : SOCPͶƱ�ӿڣ��ýӿ�ֻ��C���ṩ������LDSP�״μ��ص�SOCP�ϵ�����
* �������  : type --- ͶƱ����
* �������  : ��
* �� �� ֵ  : int 0 --- ͶƱ�ɹ���0xFFFFFFFF --- ͶƱʧ��
*****************************************************************************/
int DRV_SOCP_VOTE_TO_MCORE(SOCP_VOTE_TYPE_ENUM_U32 type)
{
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    return bsp_socp_vote_to_mcore(type);
#else
    return 0;
#endif
}

#endif /* ENABLE_BUILD_SOCP */

void BSP_SOCP_RefreshSDLogCfg(unsigned int ulTimerLen)
{
	return;
}
/*****************************************************************************
* �� �� ��  : mdrv_socp_set_log_int_timeout
*
* ��������  : ʹ��CMD LINE�еĳ�ʱʱ��������LOG2.0 SOCP��ʱ����
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
void mdrv_socp_set_log_int_timeout(void)
{
    return;
}
/*****************************************************************************
* �� �� ��  : mdrv_socp_set_log_int_default_timeout
*
* ��������  : ʹ��Ĭ�ϵĳ�ʱʱ��������LOG2.0 SOCP��ʱ����
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
void mdrv_socp_set_log_int_default_timeout(void)
{
    return;
}


#ifdef __cplusplus
}
#endif

