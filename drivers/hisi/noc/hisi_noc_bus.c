#include <linux/module.h>
#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/syscore_ops.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/debugfs.h>
#include <asm/io.h>
#include <linux/string.h>
#include <linux/hisi/util.h>

#include "hisi_noc_bus.h"
#include "hisi_noc.h"

char *cfg_initflow_array[CFG_INITFLOW_ARRAY_SIZE] = {
    "SD3(noc_mmc1bus_sd3)",
    "Sdio1(noc_mmc1bus_sdio1)",
    "A7(noc_a7tocfg)",
    "Audio(noc_asp_mst)",
    "ACPU(noc_cci2sysbus)",
    "DJTAG(noc_djtag_mst)",
    "DMA Controller(noc_dmac_mst)",
    "EMMC0(noc_emmc0)",
    "EMMC1(noc_emmc1)(del)",
    "SensorHub(noc_iomcu_ahb_mst)",
    "SensorHub(noc_iomcu_axi_mst)",
    "DMA-SensorHub(noc_iomcu_dma_mst)",
    "IVP32-DSP(noc_ivp32_mst)",
    "LPM3(noc_lpmcu_mst)",
    "SDIO0(noc_mmc0bus_sdio0)",
    "MODEM(noc_modem_mst)",
    "PERF_STAT_DEBUG(noc_perf_stat)",
    "SECURITY(noc_sec_p)",
    "SECURITY(noc_sec_s)",
    "SOCP_DEBUG(noc_socp)",
    "CORESIGHT(noc_top_cssys)",
    "USB3(noc_usb3)"
};

char *cfg_targetflow_array[CFG_TARGETFLOW_ARRAY_SIZE] = {
    "Audio(aspbus_service_target)",
    "Service_target(cfgbus_service_target)",
    "Service_target(dbgbus_service_target)",
    "Service_target(dmabus_service_target)",
    "Service_target(ivp32_peri_bus_service_target)",
    "Service_target(mmc0bus_service_target)",
    "Service_target(mmc1bus_service_target)",
    "Service_target(modembus_service_target)",
    "AO-MMBUF(noc_aobus_mmbuf)",
    "Audio(noc_asp_cfg)",
    "Vivo(noc_cfg2vivo)",
    "debug(noc_debug_apb_cfg)",
    "DMA controller(noc_dmac_cfg)",
    "EMMC0(noc_emmc0_cfg)",
    "sdio0(noc_emmc0bus_apb_cfg)",
    "GIC(noc_gic)",
    "SSI(noc_hkadc_ssi)",
    "IOMCU(noc_iomcu_ahb_slv)",
    "IOMCU(noc_iomcu_apb_slv)",
    "IVP32-DSP(noc_ivp32_cfg)",
    "LPM3(noc_lpmcu_slv)",
    "SDIO1/SD3(noc_mmc1bus_apb_cfg)",
    "MODEM(noc_modem_cfg)",
    "DEBUG(noc_socp_cfg)",
    "DDRC(noc_sys2ddrc)",
    "HKMEM(noc_sys2hkmem)",
    "CFG(noc_sys_peri0_cfg)",
    "CFG(noc_sys_peri1_cfg)",
    "DMA(noc_sys_peri2_cfg)",
    "DMA(noc_sys_peri3_cfg)",
    "CORESIGHT(noc_top_cssys_slv)",
    "USB3(noc_usb3_cfg)",
    "Service_target(sysbus_service_target)",
};


char *vivo_initflow_array[VIVO_INITFLOW_ARRAY_SIZE] = {
    "A7_RD(noc_a7tovivobus_rd)",
    "A7_WR (noc_a7tovivobus_wr)",
    "DSS0_RD(noc_dss0_rd)",
    "dss0_WR (noc_dss0_wr)",
    "DSS1_RD (noc_dss1_rd)",
    "DSS1_WR(noc_dss1_wr)",
    "ISP_RD(noc_isp_rd)",
    "ISP_WR(noc_isp_wr)",
    "VIVO(noc_vivo_cfg)",
};

char *vivo_targetflow_array[VIVO_TARGETFLOW_ARRAY_SIZE] = {
	"service_target (dss_service_target)",
	"service_target (isp_service_target)",
	"service_target (noc_dss_cfg)",
	"ISP(noc_isp_cfg)",
	"DDRC(noc_vivobus_ddrc0_rd)",
	"DDRC (noc_vivobus_ddrc0_wr)",
	"DDRC (noc_vivobus_ddrc1_rd)",
	"DDRC (noc_vivobus_ddrc1_wr)"
};


char *vcodec_initflow_array[VCODEC_INITFLOW_ARRAY_SIZE] = {
	"VCODEC(noc_vcodec_cfg)",
	"VDEC(noc_vdec)",
	"VENC(noc_venc)",
};

char *vcodec_targetflow_array[VCODEC_TARGETFLOW_ARRAY_SIZE] = {
	"DDRC(noc_vcodecbus_ddrc0)",
	"DDRC(noc_vcodecbus_ddrc1)",
	"VDEC(noc_vdec_cfg)",
	"VENC(noc_venc_cfg)",
	"service_target (vcodec_bus_service_target)",
	"service_target (vdec_service_target)",
	"venc_service_target",
};
struct noc_mid_info hi3xxx_noc_mid[]=
{
     // Bus ID,	init_flow	,mid_val	,mid name
	{0, 		15,		0x12,	"MCPU"}, //noc_modem_mst,
	{0, 		15,		0x13,	"BBE16"}, //noc_modem_mst,
	{0, 		15,		0x14,	"BBP_DMA_0"}, //noc_modem_mst,
	{0, 		15,		0x15,	"BBP_DMA_1"}, //noc_modem_mst,
	{0, 		15,		0x16,	"GU_BBP_MST"}, //noc_modem_mst,
	{0, 		15,		0x17,	"GU_BBP_MST"}, //noc_modem_mst,
	{0, 		15,		0x18,	"UICC"}, //noc_modem_mst,
	{0, 		15,		0x19,	"EDMA"}, //noc_modem_mst,
	{0, 		15,		0x1A,	"CIPHER"}, //noc_modem_mst,
	{0, 		15,		0x1B,	"IPF"}, //noc_modem_mst,
	{0, 		15,		0x1C,	"UPACC"}, //noc_modem_mst,
	{0, 		15,		0x1D,	"CICOM_0"}, //noc_modem_mst,
	{0, 		15,		0x1E,	"CICOM_1"}, //noc_modem_mst,
	{0xffffffff, 	0,		0,		0} // empty
};

static const struct noc_bus_info hi3xxx_noc_buses_info[]= {
	[0] = {
		.name = "cfg_sys_noc_bus",
		.initflow_mask = ((0x1f) << 17),
		.targetflow_mask = ((0x3f) << 11),
		.targ_subrange_mask = ((0x3) << 9),
		.seq_id_mask = (0x1FF),
		.initflow_array = cfg_initflow_array,
		.initflow_array_size = CFG_INITFLOW_ARRAY_SIZE,
		.targetflow_array = cfg_targetflow_array,
		.targetflow_array_size = CFG_TARGETFLOW_ARRAY_SIZE,
	},
	[1] = {
		.name = "vcodec_bus",
		.initflow_mask = ((0x3) << 14),
		.targetflow_mask = ((0x7) << 11),
		.targ_subrange_mask = ((0x7) << 8),
		.seq_id_mask = (0xFF) ,
		.initflow_array = vcodec_initflow_array,
		.initflow_array_size = VCODEC_INITFLOW_ARRAY_SIZE,
		.targetflow_array = vcodec_targetflow_array,
		.targetflow_array_size = VCODEC_TARGETFLOW_ARRAY_SIZE,
	},
	[2] = {
		.name = "vivo_bus",
		.initflow_mask = ((0xf) << 14),
		.targetflow_mask = ((0x7) << 11),
		.targ_subrange_mask = ((0x7) << 8),
		.seq_id_mask = (0xFF),
		.initflow_array = vivo_initflow_array,
		.initflow_array_size = VIVO_INITFLOW_ARRAY_SIZE,
		.targetflow_array = vivo_targetflow_array,
		.targetflow_array_size = VIVO_TARGETFLOW_ARRAY_SIZE,
	}
};

char *cfg_initflow_array_hi6250[] = {
	"SD3(noc_mmc1bus_sd3)",
	"Sdio1(noc_mmc1bus_sdio1)",
	"A7(noc_a7tocfg)",
	"Audio(noc_asp_mst)",
	"ACPU(noc_cci2sysbus)",
	"DJTAG(noc_djtag_mst)",
	"DMA Controller(noc_dmac_mst)",
	"EMMC0(noc_emmc0)",
	"SensorHub(noc_iomcu_ahb_mst)",
	"SensorHub(noc_iomcu_axi_mst)",
	"DMA-SensorHub(noc_iomcu_dma_mst)",
	"(noc_ipf)",
	"LPM3(noc_lpmcu_mst)",
	"MODEM(noc_modem_mst)",
	"PERF_STAT_DEBUG(noc_perf_stat)",
	"SECURITY(noc_sec_p)",
	"SECURITY(noc_sec_s)",
	"SOCP_DEBUG(noc_socp)",
	"CORESIGHT(noc_top_cssys)",
	"USB2(noc_usb2)",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
};

char *cfg_targetflow_array_hi6250[] = {
	"Audio(aspbus_service_target)",
	"Service_target(cfgbus_service_target)",
	"Service_target(dbgbus_service_target)",
	"Service_target(dmabus_service_target)",
	"Service_target(mmc0bus_service_target)",
	"Service_target(mmc1bus_service_target)",
	"Service_target(modembus_service_target)",
	"AO-MMBUF(noc_aobus_mmbuf)",
	"Audio(noc_asp_cfg)",
	"(noc_cci_cfg)",
	"Vivo(noc_cfg2vivo)",
	"debug(noc_debug_ahb_cfg)",
	"debug(noc_debug_apb_cfg)",
	"DMA controller(noc_dmac_cfg)",
	"EMMC0(noc_emmc0_cfg)",
	"GIC(noc_gic)",
	"SSI(noc_hkadc_ssi)",
	"IOMCU(noc_iomcu_ahb_slv)",
	"IOMCU(noc_iomcu_apb_slv)",
	"LPM3(noc_lpmcu_slv)",
	"SDIO1/SD3(noc_mmc1bus_apb_cfg)",
	"MODEM(noc_modem_cfg)",
	"DDRC(noc_sys2ddrc)",
	"HKMEM(noc_sys2hkmem)",
	"CFG(noc_sys_peri0_cfg)",
	"CFG(noc_sys_peri1_cfg)",
	"DMA(noc_sys_peri2_cfg)",
	"DMA(noc_sys_peri3_cfg)",
	"CORESIGHT(noc_top_cssys_slv)",
	"Service_target(sysbus_service_target)",
	"RESERVED",
	"RESERVED",
};

char *vcodec_initflow_array_hi6250[] = {
	"VCODEC(noc_vcodec_cfg)",
	"VDEC(noc_vdec)",
	"VENC(noc_venc)",
	"RESERVED",
};

char *vcodec_targetflow_array_hi6250[] = {
	"DDRC(noc_vcodecbus_ddrc)",
	"VDEC(noc_vdec_cfg)",
	"VENC(noc_venc_cfg)",
	"service_target (vcodec_bus_service_target)",
	"service_target (vdec_service_target)",
	"venc_service_target",
	"RESERVED",
	"RESERVED",
};

char *vivo_initflow_array_hi6250[] = {
	"A7_RD(noc_a7tovivobus_rd)",
	"A7_WR (noc_a7tovivobus_wr)",
	"DSS0_RD(noc_dss0_rd)",
	"DSS1_RD (noc_dss1_rd)",
	"DSS1_WR(noc_dss1_wr)",
	"ISP_RD(noc_isp_rd)",
	"ISP_WR(noc_isp_wr)",
	"VIVO(noc_vivo_cfg)",
};

struct noc_mid_info hi6250_noc_mid[]=
{ // Bus ID,	init_flow	,mid_val	,mid name
	{0, 		13,		0x12,	"MCPU"}, //noc_modem_mst,
	{0, 		13,		0x13,	"TL_BBE16"}, //noc_modem_mst,
	{0, 		13,		0x02,	"CBBE16"}, //noc_modem_mst,
	{0, 		13,		0x14,	"BBP_DMA_0"}, //noc_modem_mst,
	{0, 		13,		0x15,	"BBP_DMA_1"}, //noc_modem_mst,
	{0, 		13,		0x16,	"GU_BBP_MST"}, //noc_modem_mst,
	{0, 		13,		0x17,	"GU_BBP_MST"}, //noc_modem_mst,
	{0, 		13,		0x19,	"EDMA"}, //noc_modem_mst,
	{0, 		13,		0x18,	"EDMA1"}, //noc_modem_mst,
	{0, 		13,		0x1A,	"CIPHER"}, //noc_modem_mst,
	{0, 		13,		0x1C,	"UPACC"}, //noc_modem_mst,
	{0, 		13,		0x1D,	"CICOM_0"}, //noc_modem_mst,
	{0, 		13,		0x1E,	"HDLC"}, //noc_modem_mst,
	{0xffffffff, 	0,		0,		0} // empty
};

static const struct noc_bus_info hi6250_noc_buses_info[]= {
	[0] = {
		.name = "cfg_sys_noc_bus",
		.initflow_mask = ((0x1f) << 16),
		.targetflow_mask = ((0x1f) << 11),
		.targ_subrange_mask = ((0x3) << 9),
		.seq_id_mask = (0x1FF),
		.initflow_array = cfg_initflow_array_hi6250,
		.initflow_array_size = 32,
		.targetflow_array = cfg_targetflow_array_hi6250,
		.targetflow_array_size = 32,
	},
	[1] = {
		.name = "vcodec_bus",
		.initflow_mask = ((0x3) << 12),
		.targetflow_mask = ((0x7) << 9),
		.targ_subrange_mask = ((0x1) << 8),
		.seq_id_mask = (0xFF) ,
		.initflow_array = vcodec_initflow_array_hi6250,
		.initflow_array_size = 4,
		.targetflow_array = vcodec_targetflow_array_hi6250,
		.targetflow_array_size = 8,
	},
	[2] = {
		.name = "vivo_bus",
		.initflow_mask = ((0x7) << 12),
		.targetflow_mask = ((0x7) << 9),
		.targ_subrange_mask = ((0x1) << 8),
		.seq_id_mask = (0xFF),
		.initflow_array = vivo_initflow_array_hi6250,
		.initflow_array_size = 8,
		.targetflow_array = vivo_targetflow_array,
		.targetflow_array_size = 8,
	}
};

static struct noc_arr_info noc_buses_i;
static struct noc_mid_info *pt_mid_info;

/*================================= FUNCTION START =================================*/

/*
Function: noc_set_bus_info
Description: set noc_bus_info from platform_id
input: unsigned int platform_id -> platform_id input
output: none
return: 0 -> success
*/
int noc_set_buses_info(unsigned int platform_id)
{
	switch (platform_id) {
	default:
	case HISI_NOC_HI3650:
		noc_buses_i.ptr = hi3xxx_noc_buses_info;
		noc_buses_i.len = 3;
		pt_mid_info = hi3xxx_noc_mid;
		break;
	case HISI_NOC_HI6250:
		noc_buses_i.ptr = hi6250_noc_buses_info;
		noc_buses_i.len = 3;
		pt_mid_info = hi6250_noc_mid;
		break;
	}
	return 0;
}

/*
Function: noc_get_mid_info
Description: noc get mid_info
input: none
output: none
return: noc_mid_info pointer
*/
struct noc_mid_info* noc_get_mid_info(void)
{
	return pt_mid_info;
}

/*
Function: noc_get_buses_info
Description: get noc_bus_info
input: none
output: none
return: noc_arr_info pointer
*/
struct noc_arr_info* noc_get_buses_info(void)
{
	return &noc_buses_i;
}

/*
Function: noc_get_bus_info
Description: get noc_bus_info from bus_id
input: int bus_id -> bus id input
output: none
return: noc_bus_info
*/
const struct noc_bus_info* noc_get_bus_info(int bus_id)
{
	const struct noc_bus_info* noc_bus = NULL;

	if (bus_id < noc_buses_i.len) {
		noc_bus = noc_buses_i.ptr;
		noc_bus += bus_id;
	}
	return noc_bus;
}


