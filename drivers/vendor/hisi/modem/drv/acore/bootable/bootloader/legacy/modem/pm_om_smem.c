#include <boot.h>
#include "nv_boot.h"
#include <bsp_pm_om.h>

struct pm_om_fastboot
{
	struct pm_om_smem_cfg *smem;
	int init_flag;
};

struct pm_om_fastboot g_pm_om_fastboot;

void pm_om_smem_init(void)
{
	u32 mem_size = 0;
	struct pm_om_smem_cfg *smem = NULL;
	DRV_PM_OM_CFG_STRU nv_cfg;

	/* NV控制是否打开pm log */
	memset((void *)&nv_cfg, 0, sizeof(nv_cfg));
	if(NV_OK != bsp_nvm_read(NV_ID_DRV_PM_OM, (u8*)&(nv_cfg), sizeof(nv_cfg)))
	{
		cprintf("[%s]: nv[0x%x] read fail\n", __FUNCTION__, NV_ID_DRV_PM_OM);
	}

	if (PM_OM_USE_SHARED_DDR == nv_cfg.mem_ctrl)
	{
		smem     = (struct pm_om_smem_cfg *)PM_OM_LOG_AREA; ;/*lint !e826 !e835*/
		mem_size = SHM_SIZE_PM_OM;
	}
	else
	{
		smem     = (struct pm_om_smem_cfg *)(DDR_SOCP_ADDR + PM_OM_SOCP_OFFSET);
		mem_size = (DDR_SOCP_SIZE - PM_OM_SOCP_OFFSET) ;
	}

	/* 文件头初始化 */
	smem->file_head.magic    = PM_OM_MAGIC_PMLG;
	smem->file_head.len      = mem_size;
	smem->file_head.version  = 0;
	smem->file_head.reserved = PM_OM_PROT_MAGIC1;

	smem->sn                 = 0;
	smem->fwrite_sw          = 0;
	memcpy((void *)&(smem->nv_cfg), (void *)&nv_cfg, sizeof(nv_cfg));

	/* log: ring buffer信息结构初始化 */
	smem->rb_info.protect_magic = PM_OM_PROT_MAGIC1;
	smem->rb_info.read          = 0;
	smem->rb_info.write         = 0;
	smem->rb_info.size          = mem_size - sizeof(struct pm_om_smem_cfg);

	g_pm_om_fastboot.smem = smem;
	g_pm_om_fastboot.init_flag = 1;
}

