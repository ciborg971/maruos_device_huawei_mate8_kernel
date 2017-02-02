
/*lint -save -e537*/
#include "product_config.h"
#include <bsp_version.h>
#include "bsp_bbp.h"
#include "bbp_balong.h"

#ifdef CONFIG_BBP
/*��������ģ����ýӿ�*/
/*****************************************************************************
* �� �� : bsp_bbp_power_status
* �� �� : dpmģ����ã����ڲ鿴bbpģ�����µ�״̬
* �� �� : ģʽ��������
* �� �� : ��
* �� �� : 0:�ɹ�����0ʧ��
* ˵ �� :
*****************************************************************************/
int bsp_bbp_power_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return bbp_power_status(enModeId,enModuleId,enModemId);
}
/*****************************************************************************
* �� �� : bsp_bbp_power_up
* �� �� : dpmģ����ã����ڸ�bbpģ���ϵ�
* �� �� : ģʽ��������
* �� �� : ��
* �� �� : 0:�ɹ�����0ʧ��
* ˵ �� :
*****************************************************************************/
int bsp_bbp_power_up(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return bbp_power_up(enModeId,enModuleId,enModemId);
}
/*****************************************************************************
* �� �� : bsp_bbp_power_down
* �� �� : dpmģ����ã����ڸ�bbpģ���µ�
* �� �� : ģʽ��ģ�飬������
* �� �� : ��
* �� �� : 0:�ɹ�����0ʧ��
* ˵ �� :
*****************************************************************************/
int bsp_bbp_power_down(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return bbp_power_down(enModeId,enModuleId,enModemId);
}
/*****************************************************************************
* �� �� : bsp_bbp_dfs_status
* �� �� : dpmģ����ã����ڻ�ȡbbp pll ״̬
* �� �� : ģʽ��ģ�飬������
* �� �� : ��
* �� �� : 0x20:�رգ�0x10:����
* ˵ �� :
*****************************************************************************/
int bsp_bbp_dfs_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return PWRCTRL_COMM_ON;
}
/*****************************************************************************
* �� �� : bsp_bbp_dfs_enable
* �� �� : dpmģ����ã����ڴ�bbp pll
* �� �� : ģʽ��ģ�飬������
* �� �� : ��
* �� �� : 0x20:�رգ�0x10:����
* ˵ �� :
*****************************************************************************/
int bsp_bbp_dfs_enable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return BBP_OK;
}
/*****************************************************************************
* �� �� : bsp_bbp_dfs_disable
* �� �� : dpmģ����ã����ڹر�bbp pll
* �� �� : ģʽ��ģ�飬������
* �� �� : ��
* �� �� : 0x20:�رգ�0x10:����
* ˵ �� :
*****************************************************************************/
int bsp_bbp_dfs_disable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return BBP_OK;
}
/*****************************************************************************
* �� �� : bsp_bbp_get_wakeup_time
* �� �� : ������͹��ĵ��ã�������ѯ˯�߳�ʱʱ��
* �� �� : void
* �� �� : void
* �� �� : bbp˯��ʣ��ʱ�䣬��λΪ32.768KHzʱ�Ӽ���
* ˵ �� : �͹��Ĳ������ĸ�ģ���ж೤ʱ�䱻�滽�ѣ�
            ֻ��Ҫ������С��ʱ�伴��
*****************************************************************************/
u32 bsp_bbp_get_wakeup_time(void)
{
    u32 l_time=0;
    u32 t_time=0;

    l_time = bbp_get_wakeup_time(PWC_COMM_MODE_LTE);
    t_time = bbp_get_wakeup_time(PWC_COMM_MODE_TDS);
    return l_time>t_time?t_time:l_time;
}
u32 bsp_bbp_get_gubbp_wakeup_status(void)
{
    return bbp_get_gubbp_wakeup_status();
}
/*****************************************************************************
* �� �� : bsp_bbp_part_addr_get
* �� �� : bbp ��ģ�����ַ��ȡ
* �� �� : void
* �� �� : void
* �� �� : ʹ��bbp�ռ��ģ�����
* ˵ �� :
*****************************************************************************/
void* bsp_bbp_part_addr_get(BBP_PART_ID_E part_id)
{
    return bbp_part_addr_get(part_id);
}

/*****************************************************************************
* �� �� : bsp_bbp_dma_tran
* �� �� : ʹ��bbp dma�������ݰ���
* �� �� : Ŀ���ַ��Դ��ַ������
* �� �� : vo
* �� �� :
* ˵ �� :
*****************************************************************************/
void bsp_bbp_dma_tran(struct bbp_dma_cfg dma_config)
{
    bbp_dma_tran(dma_config);
}

/*****************************************************************************
* �� �� : bsp_bbp_dma_finish
* �� �� : �ȴ�bbp dma�������
* �� �� : Ŀ���ַ��Դ��ַ������
* �� �� : vo
* �� �� :
* ˵ �� :
*****************************************************************************/
void bsp_bbp_dma_finish(struct bbp_dma_cfg dma_config)
{
    bbp_dma_finish(dma_config);
}
/*****************************************************************************
* �� �� : bsp_bbp_init
* �� �� : bbp ��ʼ��
* �� �� : void
* �� �� : void
* �� �� : ����ģ�����
* ˵ �� :
*****************************************************************************/
s32 bsp_bbp_init(void)
{
    return bbp_init();
}

/*�������ģ���׮*/
#else

/*��������ģ��׮�ӿ�*/
/*****************************************************************************
* �� �� : bsp_bbp_power_status
* �� �� : dpmģ����ã����ڲ鿴bbpģ�����µ�״̬
* �� �� : ģʽ��������
* �� �� : ��
* �� �� : 0:�ɹ�����0ʧ��
* ˵ �� :
*****************************************************************************/
int bsp_bbp_power_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return 0;
}
/*****************************************************************************
* �� �� : bsp_bbp_power_up
* �� �� : dpmģ����ã����ڸ�bbpģ���ϵ�
* �� �� : ģʽ��������
* �� �� : ��
* �� �� : 0:�ɹ�����0ʧ��
* ˵ �� :
*****************************************************************************/
int bsp_bbp_power_up(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return 0;
}
/*****************************************************************************
* �� �� : bsp_bbp_power_down
* �� �� : dpmģ����ã����ڸ�bbpģ���µ�
* �� �� : ģʽ��ģ�飬������
* �� �� : ��
* �� �� : 0:�ɹ�����0ʧ��
* ˵ �� :
*****************************************************************************/
int bsp_bbp_power_down(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return 0;
}
/*****************************************************************************
* �� �� : bsp_bbp_dfs_status
* �� �� : dpmģ����ã����ڻ�ȡbbp pll ״̬
* �� �� : ģʽ��ģ�飬������
* �� �� : ��
* �� �� : 0x20:�رգ�0x10:����
* ˵ �� :
*****************************************************************************/
int bsp_bbp_dfs_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return PWRCTRL_COMM_ON;
}
/*****************************************************************************
* �� �� : bsp_bbp_dfs_enable
* �� �� : dpmģ����ã����ڴ�bbp pll
* �� �� : ģʽ��ģ�飬������
* �� �� : ��
* �� �� : 0x20:�رգ�0x10:����
* ˵ �� :
*****************************************************************************/
int bsp_bbp_dfs_enable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return BBP_OK;
}
/*****************************************************************************
* �� �� : bsp_bbp_dfs_disable
* �� �� : dpmģ����ã����ڹر�bbp pll
* �� �� : ģʽ��ģ�飬������
* �� �� : ��
* �� �� : 0x20:�رգ�0x10:����
* ˵ �� :
*****************************************************************************/
int bsp_bbp_dfs_disable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return BBP_OK;
}
/*****************************************************************************
* �� �� : bsp_bbp_get_wakeup_time
* �� �� : ���͹��ĵ��ã�������ѯ˯�߳�ʱʱ��
* �� �� : void
* �� �� : void
* �� �� : bbp˯��ʣ��ʱ�䣬��λΪ32.768KHzʱ�Ӽ���
* ˵ �� : �͹��Ĳ������ĸ�ģ���ж೤ʱ�䱻�滽�ѣ�
            ֻ��Ҫ������С��ʱ�伴��
*****************************************************************************/
u32 bsp_bbp_get_wakeup_time(void)
{
    return 0xffffffff;
}
u32 bsp_bbp_get_gubbp_wakeup_status(void)
{
    return 0;
}
/*****************************************************************************
* �� �� : bsp_bbp_part_addr_get
* �� �� : bbp ��ģ�����ַ��ȡ
* �� �� : void
* �� �� : void
* �� �� : ʹ��bbp�ռ��ģ�����
* ˵ �� :
*****************************************************************************/
void* bsp_bbp_part_addr_get(BBP_PART_ID_E part_id)
{
    return NULL;
}

/*****************************************************************************
* �� �� : bsp_bbp_dma_tran
* �� �� : ʹ��bbp dma�������ݰ���
* �� �� : Ŀ���ַ��Դ��ַ������
* �� �� : vo
* �� �� :
* ˵ �� :
*****************************************************************************/
void bsp_bbp_dma_tran(struct bbp_dma_cfg dma_config)
{
    return;
}

/*****************************************************************************
* �� �� : bsp_bbp_dma_finish
* �� �� : �ȴ�bbp dma�������
* �� �� : Ŀ���ַ��Դ��ַ������
* �� �� : vo
* �� �� :
* ˵ �� :
*****************************************************************************/
void bsp_bbp_dma_finish(struct bbp_dma_cfg dma_config)
{
    return;
}
/*****************************************************************************
* �� �� : bsp_bbp_init
* �� �� : bbp ��ʼ��
* �� �� : void
* �� �� : void
* �� �� : ģ��ü�ʱ����׮
* ˵ �� :
*****************************************************************************/
s32 bsp_bbp_init(void)
{
    return 0;
}
#endif

/*lint -restore*/