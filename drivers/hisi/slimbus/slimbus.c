/*
 *	slimbus is a kernel driver which is used to manager SLIMbus devices
 *	Copyright (C) 2014	Hisilicon

 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/mfd/hi3630_asp_irq.h>
#include <linux/regulator/consumer.h>
#include <linux/of.h>

#include "slimbus.h"
#include "slimbus_device.h"
#include "slimbus_drv.h"
#include "hi3630_asp_common.h"
#include "slimbus_utils.h"
#include <hisi/hilog.h>

extern int	create_hi6402_slimbus_device(
				struct platform_device	 *pdev,
				slimbus_device_t **dev);
extern int	release_hi6402_slimbus_device(
				slimbus_device_t *dev);
extern void  hi6402_param_init(
				slimbus_device_t *dev);

struct slimbus_private_data
{
	void __iomem			*base_addr; 		/* SoC SLIMbus base address (virtual address) */
	void __iomem			*asp_reg_base_addr; /* asp address(virtual address) */
	int 					irq;				/* SoC SLIMbus irq num */
	struct regulator		*regu_asp;			/* regulator of asp */
	struct pinctrl			*pctrl;
	struct pinctrl_state	*pin_default;		/* pinctrl default */
	struct pinctrl_state	*pin_idle;			/* pinctrl idle */
	struct clk				*pmu_audio_clk; 	/* codec 19.2M clk */
	uint32_t				portstate;
	slimbus_device_type_t	framerstate;
	slimbus_device_type_t	lastframer;
	platform_type_t			platform_type;
	struct timer_list		timer;
};

static struct slimbus_private_data *pdata;
slimbus_device_t *slimbus_devices[SLIMBUS_DEVICE_NUM] = {0};
uint32_t slimbus_log_count		= 300;
uint32_t slimbus_rdwrerr_times	= 0;
/*
 * SLIMbus bus configuration
 */
slimbus_bus_config_t bus_config[SLIMBUS_BUS_CONFIG_MAX] = {
	/* normal run */
	{
		.sm = SLIMBUS_SM_4_CSW_32_SL,						/* control space:4; subframe length:32; */
		.cg = SLIMBUS_CG_10,								/* clock gear*/
		.rf = SLIMBUS_RF_1, 								/* root frequency: 24.576MHZ*/
	},
	/* img download */
	{
		.sm = SLIMBUS_SM_3_CSW_8_SL,						/* control space:3; subframe length:8; */
		.cg = SLIMBUS_CG_10,								/* clock gear*/
		.rf = SLIMBUS_RF_1, 								/* root frequency: 24.576MHZ*/
	},
	/* switch framer */
	{
		.sm = SLIMBUS_SM_4_CSW_32_SL,						 /* control space:4; subframe length:32; */
		.cg = SLIMBUS_CG_8, 								/* clock gear*/
		.rf = SLIMBUS_RF_1, 								/* root frequency: 24.576MHZ*/
	},
	/* reg write img download */
	{
		.sm = SLIMBUS_SM_8_CSW_8_SL,						/* control space:8; subframe length:8; */
		.cg = SLIMBUS_CG_10,								/* clock gear*/
		.rf = SLIMBUS_RF_1, 								/* root frequency: 24.576MHZ*/
	},
};

uint32_t slimbus_logcount_get(void)
{
	return slimbus_log_count;
}
EXPORT_SYMBOL(slimbus_logcount_get);

void slimbus_logcount_set(uint32_t count)
{
	slimbus_log_count = count;
}
EXPORT_SYMBOL(slimbus_logcount_set);

uint32_t slimbus_logtimes_get(void)
{
	return slimbus_rdwrerr_times;
}
EXPORT_SYMBOL(slimbus_logtimes_get);

void slimbus_logtimes_set(uint32_t times)
{
	slimbus_rdwrerr_times = times;
}
EXPORT_SYMBOL(slimbus_logtimes_set);

int slimbus_track_configure(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track,
				slimbus_track_param_t	*params)
{
	int ret = 0;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(track >= SLIMBUS_TRACK_MAX);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	ret = slimbus_devices[dev_type]->track_configure(
										slimbus_devices[dev_type],
										track,
										params);
	return ret;
}
EXPORT_SYMBOL(slimbus_track_configure);

int slimbus_track_activate(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track)
{
	int ret = 0;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(track >= SLIMBUS_TRACK_MAX);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	ret = slimbus_devices[dev_type]->track_activate(
										slimbus_devices[dev_type],
										track);
	return ret;
}
EXPORT_SYMBOL(slimbus_track_activate);

int slimbus_track_deactivate(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track)
{
	int ret = 0;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(track >= SLIMBUS_TRACK_MAX);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	ret = slimbus_devices[dev_type]->track_deactivate(
										slimbus_devices[dev_type],
										track);
	return ret;
}
EXPORT_SYMBOL(slimbus_track_deactivate);

int slimbus_track_remove(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track)
{
	int ret = 0;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(track >= SLIMBUS_TRACK_MAX);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	ret = slimbus_devices[dev_type]->track_remove(
										slimbus_devices[dev_type],
										track);
	return ret;
}
EXPORT_SYMBOL(slimbus_track_remove);

int slimbus_switch_framer(
				slimbus_device_type_t	dev_type,
				slimbus_device_type_t	framer_type)
{
	int ret = -1;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(framer_type >= SLIMBUS_DEVICE_NUM);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	if (framer_type == SLIMBUS_DEVICE_HI6402) {
		/*  modify soc slimbus clk to 24.576M */
		slimbus_freq_change_to_nomal(pdata->asp_reg_base_addr);
		ret = slimbus_devices[dev_type]->switch_framer(
										framer_type,
										&bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER]);

	} else if (framer_type == SLIMBUS_DEVICE_SOC) {
		ret = slimbus_devices[dev_type]->switch_framer(
										framer_type,
										&bus_config[SLIMBUS_BUS_CONFIG_NORMAL]);

		/*  modify soc slimbus clk to low to avoid signal interference to GPS */
		slimbus_freq_change_to_low(pdata->asp_reg_base_addr);
	} else {
		ret = -EINVAL;
	}

	if (EOK == ret) {
		pdata->framerstate =  framer_type;
	} else {
		pr_err("slimbus_switch_framer faild, ret = %d, framer_type = %d!\n", ret, framer_type);
	}

	return ret;
}
EXPORT_SYMBOL(slimbus_switch_framer);

int slimbus_pause_clock(
				slimbus_device_type_t	dev_type,
				slimbus_restart_time_t	newrestarttime)
{
	int ret = 0;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	ret = slimbus_devices[dev_type]->pause_clock(newrestarttime);

	return ret;
}
EXPORT_SYMBOL(slimbus_pause_clock);

int slimbus_param_set(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track,
				slimbus_track_param_t  *params)
{
	int ret = 0;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(track >= SLIMBUS_TRACK_MAX);
	BUG_ON(NULL == params);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	ret = slimbus_devices[dev_type]->param_set(
										slimbus_devices[dev_type],
										track,
										params);

	return ret;
}
EXPORT_SYMBOL(slimbus_param_set);

slimbus_bus_config_t *slimbus_bus_config_get(void)
{
	return bus_config;
}
EXPORT_SYMBOL(slimbus_bus_config_get);

int slimbus_bus_configure(slimbus_bus_config_type_t type)
{
	int ret = 0;

	BUG_ON(type >= SLIMBUS_BUS_CONFIG_MAX);

	ret = slimbus_drv_bus_configure(&bus_config[type]);

	return ret;
}
EXPORT_SYMBOL(slimbus_bus_configure);

static int slimbus_probe(struct platform_device *pdev)
{
	struct slimbus_private_data *pd;
	struct device	*dev = &pdev->dev;
	struct resource *resource;
	const char *platformtype = NULL;
	int   ret          = 0;

	pd = devm_kzalloc(dev, sizeof(struct slimbus_private_data), GFP_KERNEL);
	if (!pd) {
		dev_err(dev, "not enough memory for slimbus_private_data\n");
		return -ENOMEM;
	}

	/* get pmu audio clk */
	pd->pmu_audio_clk = devm_clk_get(dev, "clk_pmuaudioclk");
	if (IS_ERR_OR_NULL(pd->pmu_audio_clk)) {
		dev_err(dev, "devm_clk_get: pmu_audio_clk not found!\n");
		HiLOGE("audio", "Slimbus", "_clk_get: pmu_audio_clk not found!\n");
		ret = PTR_ERR(pd->pmu_audio_clk);
		goto get_pmu_audio_clk_err;
	}

	ret = clk_prepare_enable(pd->pmu_audio_clk);
	if (ret) {
		dev_err(dev, "pmu_audio_clk :clk prepare enable failed !\n");
		HiLOGE("audio","Slimbus", "pmu_audio_clk :clk prepare enable failed !\n");
		goto  pmu_audio_clk_enable_err;
	}
	mdelay(1);

	/* SLIMbus base address */
	resource = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!resource) {
		dev_err(dev, "get IORESOURCE_MEM failed\n");
		goto pmu_audio_clk_enable_err;
	}

	pd->base_addr = ioremap(resource->start, resource_size(resource));
	if (!pd->base_addr) {
		dev_err(dev, "remap base address %p failed\n", (void*)resource->start);
		goto pmu_audio_clk_enable_err;
	}

	resource = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!resource) {
		dev_err(dev, "get IORESOURCE_MEM failed\n");
		goto get_aspres_err;
	}

	pd->asp_reg_base_addr = ioremap(resource->start, resource_size(resource));
	if (!pd->asp_reg_base_addr) {
		dev_err(dev, "remap base address %p failed\n", (void*)resource->start);
		goto get_aspres_err;
	}

	dev_info(dev, "[%s:%d] virtual address slimbus:%p, asp:%p!\n", __FUNCTION__, __LINE__,pd->base_addr, pd->asp_reg_base_addr);

	/* SLIMbus irq */
	pd->irq = platform_get_irq_byname(pdev, "asp_irq_slimbus");
	if (pd->irq < 0) {
		dev_err(dev, "get irq failed\n");
		goto map_asp_err;
	}

	pd->regu_asp = devm_regulator_get(dev, "slimbus-reg");
	if (IS_ERR(pd->regu_asp)) {
		dev_err(dev, "couldn't get regulators !\n");
		goto map_asp_err;
	}

	ret = regulator_enable(pd->regu_asp);
	if (ret) {
		dev_err(dev, "couldn't enable regulators %d\n", ret);
		goto map_asp_err;
	}

	/* ssi&slimbus iomux config */
	pd->pctrl = pinctrl_get(dev);
	if (IS_ERR(pd->pctrl)) {
		dev_err(dev, "could not get pinctrl\n");
		goto get_pinctrl_err;
	}
	pd->pin_default = pinctrl_lookup_state(pd->pctrl, PINCTRL_STATE_DEFAULT);
	if (IS_ERR(pd->pin_default)) {
		dev_err(dev, "%s : could not get defstate (%li)\n", __FUNCTION__ , PTR_ERR(pd->pin_default));
		goto ops_pinctrl_err;
	}
	pd->pin_idle = pinctrl_lookup_state(pd->pctrl, PINCTRL_STATE_IDLE);
	if (IS_ERR(pd->pin_idle)) {
		dev_err(dev, "%s : could not get defstate (%li)\n", __FUNCTION__ , PTR_ERR(pd->pin_idle));
		goto ops_pinctrl_err;
	}

	ret = pinctrl_select_state(pd->pctrl, pd->pin_default);
	if (ret) {
		dev_err(dev, "%s : could not set pins to default state\n", __FUNCTION__);
		HiLOGE("audio","Slimbus", "%s : could not set pins to default state\n", __FUNCTION__);
		goto ops_pinctrl_err;
	}

	ret = create_hi6402_slimbus_device(pdev, &slimbus_devices[SLIMBUS_DEVICE_HI6402]);
	if (ret) {
		dev_err(dev, "slimbus hi6402 device create failed! \n");
		goto ops_pinctrl_err;
	}

	ret = of_property_read_string(pdev->dev.of_node, "platform-type", &platformtype);
	if(ret)
	{
		dev_err(dev, "of_property_read_string return error! ret:%d\n", ret);
		goto ops_pinctrl_err;
	}

	pr_info("[%s:%d] platform type:%s!\n", __FUNCTION__, __LINE__, platformtype);
	slimbus_devices[SLIMBUS_DEVICE_HI6402]->rf = SLIMBUS_RF_6144;
	slimbus_devices[SLIMBUS_DEVICE_HI6402]->slimbusclk_drv = 0xA0;
	slimbus_devices[SLIMBUS_DEVICE_HI6402]->slimbusdata_drv = 0xA3;
	pd->platform_type = PLATFORM_PHONE;

	if(NULL == platformtype){
		dev_err(dev, "[%s:%d] platform not define! default:ASIC!\n", __FUNCTION__, __LINE__);
		slimbus_devices[SLIMBUS_DEVICE_HI6402]->rf = SLIMBUS_RF_24576;
		bus_config[SLIMBUS_BUS_CONFIG_NORMAL].sm = SLIMBUS_SM_8_CSW_32_SL;
		bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].sm = SLIMBUS_SM_8_CSW_32_SL;
		bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].cg = SLIMBUS_CG_10;
	} else {
		if (!strcmp(platformtype, "ASIC")) {
			slimbus_devices[SLIMBUS_DEVICE_HI6402]->rf = SLIMBUS_RF_24576;
			bus_config[SLIMBUS_BUS_CONFIG_NORMAL].sm = SLIMBUS_SM_8_CSW_32_SL;
			bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].sm = SLIMBUS_SM_8_CSW_32_SL;
			bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].cg = SLIMBUS_CG_10;
		} else if (!strcmp(platformtype, "UDP")) {
			slimbus_devices[SLIMBUS_DEVICE_HI6402]->rf = SLIMBUS_RF_24576;
			slimbus_devices[SLIMBUS_DEVICE_HI6402]->slimbusclk_drv = 0xC0;
			slimbus_devices[SLIMBUS_DEVICE_HI6402]->slimbusdata_drv = 0xC3;
			bus_config[SLIMBUS_BUS_CONFIG_NORMAL].sm = SLIMBUS_SM_8_CSW_32_SL;
			bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].sm = SLIMBUS_SM_8_CSW_32_SL;
			bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].cg = SLIMBUS_CG_10;
			pd->platform_type = PLATFORM_UDP;
		} else if (!strcmp(platformtype, "FPGA")) {
			slimbus_devices[SLIMBUS_DEVICE_HI6402]->rf = SLIMBUS_RF_6144;
			pd->platform_type = PLATFORM_FPGA;
		} else {
			dev_err(dev, "platform type define err!\n");
			goto release_6402dev;
		}
	}

	hi6402_param_init(slimbus_devices[SLIMBUS_DEVICE_HI6402]);

	slimbus_module_enable(slimbus_devices[SLIMBUS_DEVICE_HI6402], pd ->asp_reg_base_addr, 1);

	ret = slimbus_drv_init(pd->platform_type, pd->base_addr, pd->asp_reg_base_addr, pd->irq);
	if (ret) {
		dev_err(dev, "slimbus drv init failed!\n");
		goto slimbus_err;
	}

	ret = slimbus_bus_configure(SLIMBUS_BUS_CONFIG_NORMAL);
	if (ret) {
		dev_err(dev, "slimbus bus configure failed!!\n");
		slimbus_drv_release(pd->irq);
		goto slimbus_err;
	}

	pd->framerstate = SLIMBUS_DEVICE_SOC;
	pd->lastframer	= SLIMBUS_DEVICE_SOC;
	platform_set_drvdata(pdev, pd);
	pdata = pd;

	return 0;

slimbus_err:
release_6402dev:
	release_hi6402_slimbus_device(slimbus_devices[SLIMBUS_DEVICE_HI6402]);
ops_pinctrl_err:
	pinctrl_put(pd->pctrl);
get_pinctrl_err:
	regulator_disable(pd->regu_asp);
map_asp_err:
	iounmap(pd->asp_reg_base_addr);
get_aspres_err:
	iounmap(pd->base_addr);
pmu_audio_clk_enable_err:
	clk_disable_unprepare(pd->pmu_audio_clk);
get_pmu_audio_clk_err:
	devm_clk_put(dev, pd->pmu_audio_clk);

	devm_kfree(&pdev->dev, pd);

	return -EFAULT;
}

static int slimbus_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct slimbus_private_data *pd = platform_get_drvdata(pdev);
	struct device	*dev = &pdev->dev;

	BUG_ON(NULL == pd);

	ret = slimbus_switch_framer(SLIMBUS_DEVICE_HI6402, SLIMBUS_DEVICE_SOC);
	if (ret) {
		dev_err(dev, "switch framer to SLIMBUS_DEVICE_SOC fail, ret:%d\n", ret);
	}

	slimbus_drv_release(pd->irq);
	release_hi6402_slimbus_device(slimbus_devices[SLIMBUS_DEVICE_HI6402]);
	pinctrl_put(pd->pctrl);
	ret = regulator_disable(pd->regu_asp);
	if (ret) {
		dev_err(dev, "regulator disable failed!, ret:%d\n", ret);
	}

	iounmap(pd->asp_reg_base_addr);
	iounmap(pd->base_addr);
	clk_disable_unprepare(pd->pmu_audio_clk);
	devm_clk_put(dev, pd->pmu_audio_clk);
	devm_kfree(dev, pd);

	platform_set_drvdata(pdev, NULL);

	return 0;
}

static int slimbus_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct slimbus_private_data *pd = platform_get_drvdata(pdev);
	struct device	*dev = &pdev->dev;
	int ret = 0;

	BUG_ON(NULL == pd);

	pd->portstate = slimbus_port_state_get(pd->base_addr);
	pr_info("[%s:%d] portstate:%#x + \n", __FUNCTION__, __LINE__,  pd->portstate);

	if (!pd->portstate) {
		/*
		* while fm, hi6402 pll is in high freq, slimbus framer is in codec side
		* we need to switch to soc in this case, and switch to 6402 in resume
		*/
		if (pd->framerstate == SLIMBUS_DEVICE_HI6402) {
			ret = slimbus_switch_framer(SLIMBUS_DEVICE_HI6402, SLIMBUS_DEVICE_SOC);
			pd->lastframer = SLIMBUS_DEVICE_HI6402;
		} else {
			pd->lastframer = SLIMBUS_DEVICE_SOC;
		}

		ret = slimbus_drv_stop();
		if (ret) {
			pr_err("%s : slimbus stop failed!\n", __FUNCTION__);
		}

		/* set pin to  low power mode */
		ret = pinctrl_select_state(pd->pctrl, pd->pin_idle);
		if (ret) {
			dev_err(dev, "%s : could not set pins to idle state\n", __FUNCTION__);
			HiLOGE("audio", "Slimbus", "%s : could not set pins to idle state\n", __FUNCTION__);
			goto exit;
		}

		clk_disable_unprepare(pd->pmu_audio_clk);

		ret = regulator_disable(pd->regu_asp);
		if (ret) {
			dev_err(dev, "%s : regulator disable failed! \n", __FUNCTION__);
			goto exit;
		}
	}

exit:
	pr_info("[%s:%d] - \n", __FUNCTION__, __LINE__);

	return ret;
}

static int slimbus_resume(struct platform_device *pdev)
{
	struct slimbus_private_data *pd = platform_get_drvdata(pdev);
	struct device	*dev = &pdev->dev;
	int ret = 0;

	pr_info("[%s:%d] + \n", __FUNCTION__, __LINE__);

	BUG_ON(NULL == pd);

	if (!pd->portstate) {
		ret = regulator_enable(pd->regu_asp);
		if (ret) {
			dev_err(dev, "couldn't enable regulators %d\n", ret);
			goto exit;
		}

		ret = clk_prepare_enable(pd->pmu_audio_clk);
		if (ret) {
			dev_err(dev, "pmu_audio_clk :clk prepare enable failed !\n");
			goto exit;
		}
		mdelay(1);

		ret = pinctrl_select_state(pd->pctrl, pd->pin_default);
		if (ret) {
			dev_err(dev, "could not set pins to default state\n");
			HiLOGE("audio","Slimbus", "%s : could not set pins to default state\n", __FUNCTION__);
			goto exit;
		}

		slimbus_module_enable(slimbus_devices[SLIMBUS_DEVICE_HI6402], pd->asp_reg_base_addr, true);
		ret = slimbus_dev_init(pd->platform_type);
		if (ret) {
			dev_err(dev, "slimbus drv init failed!\n");
			ret = slimbus_drv_reset_bus();
			if (ret > 0)
				goto exit;
		}

		ret = slimbus_bus_configure(SLIMBUS_BUS_CONFIG_NORMAL);
		if (ret) {
			dev_err(dev, "slimbus bus configure failed!!\n");
			goto exit;
		}

		if (pd->lastframer == SLIMBUS_DEVICE_HI6402) {
			ret = slimbus_switch_framer(SLIMBUS_DEVICE_HI6402, SLIMBUS_DEVICE_HI6402);
			pr_info("[%s:%d] switch_framer:%#x + \n", __FUNCTION__, __LINE__,  pdata->lastframer);
		}
	}

exit:
	pr_info("[%s:%d] portstate:%#x -\n", __FUNCTION__, __LINE__, pd->portstate);
	return ret;
}

static const struct of_device_id slimbus_match[] = {
	{
		.compatible = "candance,slimbus",
	},
	{},
};
MODULE_DEVICE_TABLE(of, slimbus_match);

static struct platform_driver slimbus_driver = {
	.probe	= slimbus_probe,
	.remove = slimbus_remove,
	.suspend = slimbus_suspend,
	.resume  = slimbus_resume,
	.driver = {
		.name	= "hisilicon,slimbus",
		.owner	= THIS_MODULE,
		.of_match_table = slimbus_match,
	},
};

static int __init slimbus_init(void)
{
	int ret;

	ret = platform_driver_register(&slimbus_driver);
	if (ret) {
		pr_err("driver register failed\n");
		HiLOGE("audio","Slimbus", "driver register failed\n");
	}

	return ret;
}

static void __exit slimbus_exit(void)
{
	platform_driver_unregister(&slimbus_driver);
}
fs_initcall(slimbus_init);
module_exit(slimbus_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon");

