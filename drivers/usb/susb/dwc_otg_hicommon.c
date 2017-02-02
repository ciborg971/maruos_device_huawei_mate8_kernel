#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/mutex.h>
#include <linux/wakelock.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/delay.h>
#include <linux/of_address.h>
#include <linux/regulator/consumer.h>
#include <linux/clk.h>
#include <linux/of_gpio.h>

#include <linux/huawei/usb/hisi_usb.h>

#include "lm.h"
#include "dwc_otg_pcd.h"
#include "dwc_otg_pcd_if.h"
#include "dwc_otg_core_if.h"
#include "dwc_otg_cil.h"
#include "dwc_otg_driver.h"
#include "dwc_otg_hcd.h"

#include "dwc_otg_hicommon.h"
#include "hisi_usb_otg_type.h"
#include <linux/mfd/hisi_pmic.h>
#include <pmic_interface.h>

atomic_t is_event_work_ready = ATOMIC_INIT(0);
atomic_t is_power_on = ATOMIC_INIT(0);

struct otg_dev * otg_dev_p;
static unsigned int release_wakelock;
#define ENABLE_USB_OTG_TEST 1

#if ENABLE_USB_OTG_TEST

#define USB_AHBIF_REGS_COUNT 20
static uint32_t ahbif_regs_value[USB_AHBIF_REGS_COUNT+1];

#ifdef is_need_restore
#undef is_need_restore
#endif
static unsigned is_need_restore;

static ssize_t ahbif_reg_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int i;
	ssize_t ret = 0;

	ret += scnprintf((buf + ret), PAGE_SIZE-ret, "usb ahbif regs value:\n");
	for (i = 0; i < USB_AHBIF_REGS_COUNT; i++) {
		ret += scnprintf((buf + ret), PAGE_SIZE-ret, "0x%02x - 0x%08lx\n",
			i * sizeof(ahbif_regs_value[0]),
			ahbif_regs_value[i]);
	}
	return ret;
}

/**
 * return 0 means get option value sucess, other failed!
 */
static int get_opt_value(const char *buf, const char *opt,
		unsigned *value)
{
	char *p = NULL;

	p = strstr(buf, opt);
	if (!p)
		return -1;

	for (; *p; p++) {
		if (*p == '=') {
			if (sscanf(p + 1, "%x", value) == 0)
				return -1;
			break;
		}
	}

	return 0;
}
static ssize_t ahbif_reg_store(struct device *pdev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned off, value;

	if ((0 == get_opt_value(buf, "offset", &off))
			&& (0 == get_opt_value(buf, "value", &value))) {
		if (USB_AHBIF_REGS_COUNT >= (off >> 2)) {
			ahbif_regs_value[(off >> 2)] = value;
			printk(KERN_INFO "set ahbif_regs_value[%d] as 0x%08x\n",
				(off >> 2), ahbif_regs_value[(off >> 2)]);
			is_need_restore = 1;
		}
	} else {
		printk(KERN_INFO "USAGE: echo \"offset=0x?,value=0x?\" > ahbif_reg\n");
	}
	return size;
}

DEVICE_ATTR(ahbif_reg, (S_IRUGO | S_IWUSR), ahbif_reg_show, ahbif_reg_store);

void ahbif_reg_save(void)
{
	struct otg_dev *p = otg_dev_p;
	int i;

	for (i = 0; i < USB_AHBIF_REGS_COUNT; i++) {
		ahbif_regs_value[i] = readl(p->usb_ahbif_base + i * 4);
	}
}

void ahbif_reg_restore(void)
{
	struct otg_dev *p = otg_dev_p;
	struct usb_ahbif_registers *ahbif
			= (struct usb_ahbif_registers *)p->usb_ahbif_base;
	int i;

	usb_dbg("[%s]\n", __func__);

#define AHBIF_REG_RESTORE(reg_addr)	\
	do {				\
		i = (((void *)(reg_addr))					\
			    - (void *)otg_dev_p->usb_ahbif_base) >> 2;	\
		writel(ahbif_regs_value[i], reg_addr);				\
		usb_dbg("addr: %p, value: 0x%x\n",				\
				reg_addr, ahbif_regs_value[i]);			\
	} while (0)

	AHBIF_REG_RESTORE(&(ahbif->usbotg2_ctrl0));
	AHBIF_REG_RESTORE(&(ahbif->usbotg2_ctrl2));
	AHBIF_REG_RESTORE(&(ahbif->usbotg2_ctrl3));
	AHBIF_REG_RESTORE(&(ahbif->usbotg2_ctrl4));

	/* update saved value from register */
	ahbif_reg_save();
}

static ssize_t plugusb_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	char *s;
	switch (otg_dev_p->status) {
	case OTG_DEV_OFF:
		s = "OTG_DEV_OFF";
		break;
	case OTG_DEV_DEVICE:
		s = "OTG_DEV_DEVICE";
		break;
	case OTG_DEV_HOST:
		s = "OTG_DEV_HOST";
		break;
	case OTG_DEV_SUSPEND:
		s = "OTG_DEV_SUSPEND";
		break;
	default :
		s = "unknown";
		break;
	}
	return scnprintf(buf, PAGE_SIZE, "usb otg status: %s\n"
		"write hoston/hostoff/deviceon/deviceoff to change the state.\n", s);
}
static ssize_t plugusb_store(struct device *pdev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	if (!strncmp(buf, "hoston", 6)) {
		hisi_usb_otg_event(ID_FALL_EVENT);
	} else if (!strncmp(buf, "hostoff", 6)) {
		hisi_usb_otg_event(ID_RISE_EVENT);
	} else if (!strncmp(buf, "deviceon", 8)) {
		hisi_usb_otg_event(CHARGER_CONNECT_EVENT);
	} else if (!strncmp(buf, "deviceoff", 8)) {
		hisi_usb_otg_event(CHARGER_DISCONNECT_EVENT);
	} else {
		printk(KERN_ERR "I dot know that!\n");
	}
	return size;
}
DEVICE_ATTR(plugusb, (S_IRUGO | S_IWUSR), plugusb_show, plugusb_store);

static const char *charger_type_array[] = {
	[CHARGER_TYPE_SDP]     = "sdp",       /* Standard Downstreame Port */
	[CHARGER_TYPE_CDP]     = "cdp",       /* Charging Downstreame Port */
	[CHARGER_TYPE_DCP]     = "dcp",       /* Dedicate Charging Port */
	[CHARGER_TYPE_UNKNOWN] = "unknown",   /* non-standard */
	[CHARGER_TYPE_NONE]    = "none",      /* not connected */
	[PLEASE_PROVIDE_POWER] = "provide"   /* host mode, provide power */
};

static enum hisi_charger_type get_charger_type_from_str(const char *buf, size_t size)
{
	int i = 0;
	enum hisi_charger_type ret = CHARGER_TYPE_NONE;

	for(i = 0; i < sizeof(charger_type_array) / sizeof(charger_type_array[0]); i++) {
		if(!strncmp(buf, charger_type_array[i], size-1)) {
			ret = (enum hisi_charger_type)i;
			break;
		}
	}

	return ret;
}

static ssize_t charger_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct otg_dev *dev_p = dev_get_drvdata(dev);
	enum hisi_charger_type charger_type = CHARGER_TYPE_NONE;

	if (!dev_p) {
		printk(KERN_ERR "platform_get_drvdata return null\n");
		return scnprintf(buf, PAGE_SIZE, "platform_get_drvdata return null\n");
	}

	charger_type = dev_p->charger_type;

	return scnprintf(buf, PAGE_SIZE, "[(%d):Charger type = %s]\n"
			     "----------------------------------------------------------------\n"
			     "usage: echo {str} > chargertest\n"
			     "       sdp:        Standard Downstreame Port\n"
                             "       cdp:        Charging Downstreame Port\n"
                             "       dcp:        Dedicate Charging Port\n"
                             "       unknown:    non-standard\n"
                             "       none:       not connected\n"
                             "       provide:    host mode, provide power\n"
			     , charger_type, charger_type_array[charger_type] );
}

static void notify_charger_type(struct otg_dev *dev_p);
static ssize_t charger_store(struct device *pdev, struct device_attribute *attr, const char *buf, size_t size)
{
	struct otg_dev *dev_p = dev_get_drvdata(pdev);
	enum hisi_charger_type charger_type = get_charger_type_from_str(buf, size);

	if (!dev_p) {
		printk(KERN_ERR "platform_get_drvdata return null\n");
		return size;
	}

	dev_p->charger_type = charger_type;
	notify_charger_type(dev_p);

	return size;
}

DEVICE_ATTR(charger, (S_IRUGO | S_IWUSR), charger_show, charger_store);

static ssize_t eyetest_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	return scnprintf(buf, PAGE_SIZE, "usage: echo x > eyetest\n");
}
static ssize_t eyetest_store(struct device *pdev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct otg_dev *dev_p = dev_get_drvdata(pdev);
	dwc_otg_device_t *dwc_otg_dev = lm_get_drvdata(dev_p->lm_dev);

	if (dwc_otg_is_host_mode(dwc_otg_dev->core_if)) {
		hprt0_data_t reg_value;
		reg_value.d32 = dwc_otg_get_hprt0(dwc_otg_dev->core_if);
		reg_value.b.prttstctl = 4;
		dwc_otg_set_hprt0(dwc_otg_dev->core_if, reg_value.d32);
		printk(KERN_INFO "[USB]ENTER HOST EYE DIAGRAM TEST!\n");
	} else {
		dctl_data_t reg_value;
		reg_value.d32 = DWC_READ_REG32(&dwc_otg_dev->core_if->dev_if->dev_global_regs->dctl);
		reg_value.b.tstctl = 4;
		DWC_WRITE_REG32(&dwc_otg_dev->core_if->dev_if->dev_global_regs->dctl, reg_value.d32);
		printk(KERN_INFO "[USB]ENTER DEVICE EYE DIAGRAM TEST!\n");
	}

	return size;
}
DEVICE_ATTR(eyetest, (S_IRUGO | S_IWUSR), eyetest_show, eyetest_store);

static ssize_t release_wakelock_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	return scnprintf(buf, PAGE_SIZE, "%d\n", release_wakelock);
}
static void do_disconnect(void);
static ssize_t release_wakelock_store(struct device *pdev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	long val = 0;
	struct otg_dev *dev_p = dev_get_drvdata(pdev);
	if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 1))
		return -EINVAL;
	release_wakelock = val;
	usb_dbg("set release_wakelock = %d!\n", release_wakelock);
	if (release_wakelock)
		do_disconnect();
	else
		dwc_otg_hicommon_wake_lock();

	return size;
}
DEVICE_ATTR(release_wakelock, (S_IRUGO | S_IWUSR), release_wakelock_show, release_wakelock_store);

int create_attr_file(struct device *dev)
{
	int ret = 0;
	struct class* hisi_usb_class;
	struct device* hisi_usb_dev;

	ret |= device_create_file(dev, &dev_attr_plugusb);
	ret |= device_create_file(dev, &dev_attr_ahbif_reg);
	ret |= device_create_file(dev, &dev_attr_eyetest);
	ret |= device_create_file(dev, &dev_attr_release_wakelock);
	ret |= device_create_file(dev, &dev_attr_charger);
	hisi_usb_class = class_create(THIS_MODULE,"hisi_usb_class");
	if (NULL == hisi_usb_class)
	{
		usb_dbg("create hisi_usb_class error!\n");
	}
	else
	{
		hisi_usb_dev= device_create(hisi_usb_class, NULL, 0, NULL, "hisi_usb_dev");
		if (NULL == hisi_usb_dev)
		{
			usb_dbg("create hisi_usb_dev error!\n");
		}
		else
		{
			ret |= sysfs_create_link(&hisi_usb_dev->kobj, &dev->kobj, "interface");
		}
	}
	if (ret) {
		usb_dbg("create attr file error!\n");
	}
	usb_dbg("create_attr_file %s!\n", ret ? "error" : "done");
	return ret;
}
#else
static inline int create_attr_file(struct device *dev){return 0;}
static inline void ahbif_reg_save(void){}
static inline void ahbif_reg_restore(void){}
#endif

#if ENABLE_USB_OTG_TEST
#define CHECK_USB_CABLE_STRICTLY 0
#else
#define CHECK_USB_CABLE_STRICTLY 1
#endif

/*
 * 读dts配置
 * 目前以下是USB2.0公共的dts
 * 随着平台的增加，差异有可能会出现，
 * 那时再把dts差异部分移植到平台特性
 * 文件中
 */
int get_resource(struct otg_dev *dev)
{
	int ret = 0;
	struct device_node *np = NULL;
	struct device *base_dev = &(dev->pdev->dev);

	/*
	 * get registers base address
	 */
	np = of_find_compatible_node(NULL, NULL, "hisilicon,usb-otg-ahbif");
	if (np) {
		dev->usb_ahbif_base = of_iomap(np, 0);
	}

	/*
	 * get pctrl base address
	 */
	np = of_find_compatible_node(NULL, NULL, "hisilicon,pctrl");
	if (np) {
		dev->pctrl_reg_base = of_iomap(np, 0);
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,crgctrl");
	if (np) {
		dev->pericrg_base = of_iomap(np, 0);
	}

	ret = of_property_read_u32(dev->pdev->dev.of_node, "eye_diagram_param", &(dev->eyePattern));
	if (ret) {
		usb_err("get eye_diagram_param failed !!! \n");
		dev->eyePattern = 0x059066DB;
		ret = 0;
	}

	if (!dev->usb_ahbif_base || !dev->pericrg_base || !dev->pctrl_reg_base) {
		usb_err("get registers base address failed![a:%x],[peri:%x],[pctrl:%x]\n",dev->usb_ahbif_base, dev->pericrg_base, dev->pctrl_reg_base);
		return -ENXIO;
	}

	/*
	 * get ldo handlers
	 */
	dev->otgdebugsubsys_regu.supply = "otgdebugsubsys";
	ret = devm_regulator_bulk_get(&dev->pdev->dev, 1, &dev->otgdebugsubsys_regu);
	if (ret) {
		usb_err("couldn't get regulator otgdebugsubsys\n");
	}

	/*
	 * get abb clk handler
	 */
	dev->clk = devm_clk_get(&dev->pdev->dev, "clk_abb_192");
	if (IS_ERR_OR_NULL(dev->clk)) {
		usb_err("get usb clk failed\n");
		return -EINVAL;
	}

	/*
	 * get hclk handler
	 */
	dev->hclk_usb2otg = devm_clk_get(&dev->pdev->dev, "hclk_usb2otg");
	if (IS_ERR_OR_NULL(dev->hclk_usb2otg)) {
		usb_err("get aclk_usb3otg failed\n");
		return -EINVAL;
	}

	if (of_property_read_u32(base_dev->of_node, "fpga_flag", &(dev->fpga_flag))) {
		dev->fpga_flag = 0;
		dev->fpga_usb_mode_gpio = -1;
		usb_dbg("in asic mode!\n");
	} else {
		dev->fpga_usb_mode_gpio = of_get_named_gpio(base_dev->of_node, "fpga_usb_mode_gpio", 0);
		if(dev->fpga_usb_mode_gpio > 0) {
			usb_dbg("in fpga mode:%d!\n", dev->fpga_usb_mode_gpio);
		} else {
			usb_err("[fpga mode]:get gpio_number failure errno:%d!\n", dev->fpga_usb_mode_gpio);
		}
	}

	usb_dbg("get resource %s!\n", ret ? "error" : "done");
	return ret;
}

static void put_resource(struct otg_dev *dev)
{
	usb_dbg("put resource done.\n");
	return;
}

int open_ldo(struct otg_dev *otg_device)
{
	int ret = 0;

	if (0 != otg_device->is_regu_on) {
		usb_dbg("ldo already opened!\n");
		return 0;
	}

	ret = regulator_bulk_enable(1, &otg_device->otgdebugsubsys_regu);
	if (ret) {
		usb_err("enable regulator otgdebugsubsys failed\n");
	}

	otg_device->is_regu_on = 1;

	return ret;
}

void close_ldo(struct otg_dev *otg_device)
{
	if (0 == otg_device->is_regu_on) {
		usb_dbg("ldo already closed!\n");
		return;
	}

	regulator_bulk_disable(1, &otg_device->otgdebugsubsys_regu);
	otg_device->is_regu_on = 0;
}

void init_usb_otg_phy(struct otg_dev *otg_device, int is_host_mode)
{
	struct usb_phy_ops *usb_phy_ops = get_usb_phy_ops(otg_device);
	if(usb_phy_ops) {
		usb_phy_ops->init(otg_device, is_host_mode);
	} else {
		printk(KERN_ERR "[%s]:get phy ops error!\n", __func__);
	}
}

void close_usb_otg_phy(struct otg_dev *otg_device)
{
	struct usb_phy_ops *usb_phy_ops = get_usb_phy_ops(otg_device);
	if(usb_phy_ops) {
		usb_phy_ops->close(otg_device);
	} else {
		printk(KERN_ERR "[%s]:get phy ops error!\n", __func__);
	}
}

static void show_pericrg_status(void)
{
	void __iomem *pericrg_base = otg_dev_p->pericrg_base;
	printk(KERN_INFO "PERI_CRG_RSTEN4: 0x%08x, PERI_CRG_RSTDIS4: 0x%08x,"
		" PERI_CRG_RSTSTAT4: 0x%08x\n",
		readl(pericrg_base + PERI_CRG_RSTEN4),
		readl(pericrg_base + PERI_CRG_RSTDIS4),
		readl(pericrg_base + PERI_CRG_RSTSTAT4)
		);
}

static int hw_setup(struct otg_dev *otg_device, int is_host_mode)
{
	int ret;
	struct usb_phy_ops *usb_phy_ops = get_usb_phy_ops(otg_device);

	ret = open_ldo(otg_device);
	if (ret) {
		usb_err("open ldo error!");
		return ret;
	}

	/* enable clk */
	if(usb_phy_ops) {
		usb_phy_ops->enable_clk(otg_device);
	} else {
		usb_err("[USB2.0]:Can't register enable clk!\n");
	}

	init_usb_otg_phy(otg_device, is_host_mode);
	show_pericrg_status();
	atomic_set(&is_power_on, 1);

	otg_device->hcd_status = HCD_ON;

	if (otg_device->dwc_otg_irq_enabled == false) {
		enable_irq(otg_device->lm_dev->irq);
		otg_device->dwc_otg_irq_enabled = true;
	}
	return 0;
}

static void hw_shutdown(struct otg_dev *otg_device)
{
	dwc_otg_device_t *dwc_otg_dev;
	struct usb_phy_ops *usb_phy_ops = get_usb_phy_ops(otg_device);
	unsigned long flags;

	if ((!otg_device) || (!otg_device->lm_dev))
		return;

	dwc_otg_dev = lm_get_drvdata(otg_device->lm_dev);

	if (!dwc_otg_dev)
		return;

	/* get spin lock, wait for irq handler finish */
	DWC_SPINLOCK_IRQSAVE(dwc_otg_dev->core_if->lock, &flags);
	atomic_set(&is_power_on, 0);
	DWC_SPINUNLOCK_IRQRESTORE(dwc_otg_dev->core_if->lock, flags);

	/* work or timer may enable global interrupts, close it now */
	dwc_otg_disable_global_interrupts(dwc_otg_dev->core_if);

	close_usb_otg_phy(otg_device);

	/* disable clk */
	if(usb_phy_ops) {
		usb_phy_ops->disable_clk(otg_device);
	} else {
		usb_err("[USB2.0]:Can't register disable clk!\n");
	}

	close_ldo(otg_device);
	show_pericrg_status();

	otg_device->hcd_status = HCD_OFF;

	if (otg_device->dwc_otg_irq_enabled == true) {
		disable_irq(otg_device->lm_dev->irq);
		otg_device->dwc_otg_irq_enabled = false;
	}

	return;
}

int dwc_otg_hcd_setup(void)
{
	struct otg_dev * p = otg_dev_p;
	mutex_lock(&p->lock);

	if ((OTG_DEV_OFF == p->status) && (HCD_OFF == p->hcd_status)) {
		usb_dbg("p->status: %d, hcd_status: %d\n", p->status, p->hcd_status);
		if (open_ldo(p)) {
			usb_err("open ldo failed!\n");
			mutex_unlock(&p->lock);
			return -1;
		}
		init_usb_otg_phy(p, 1);
		p->hcd_status = HCD_ON;;
	}

	mutex_unlock(&p->lock);
	return 0;
}

void dwc_otg_hcd_shutdown(void)
{
	struct otg_dev * p = otg_dev_p;
	mutex_lock(&p->lock);

	if ((OTG_DEV_OFF == p->status) && (HCD_ON == p->hcd_status)) {
		usb_dbg("p->status: %d, hcd_status: %d\n", p->status, p->hcd_status);
		close_usb_otg_phy(p);
		close_ldo(p);
		p->hcd_status = HCD_OFF;
	}

	mutex_unlock(&p->lock);
}

static char * charger_type_string(enum hisi_charger_type type)
{
	char *s = NULL;
	if (type == CHARGER_TYPE_SDP)
		s = "SDP";
	else if (type == CHARGER_TYPE_CDP)
		s = "CDP";
	else if (type == CHARGER_TYPE_DCP)
		s = "DCP";
	else if (type == CHARGER_TYPE_UNKNOWN)
		s = "UNKNOWN";
	else if (type == CHARGER_TYPE_NONE)
		s = "NONE";
	else
		s = "ilegal charger";
	return s;
}

void dump_bc_reg(struct otg_dev *dev_p)
{
	/* for debug */
	struct usb_ahbif_registers *ahbif = (struct usb_ahbif_registers *)otg_dev_p->usb_ahbif_base;

	usb_err("bc_ctrl0:[%x]\n", ahbif->bc_ctrl0.reg);
	usb_err("bc_ctrl1:[%x]\n", ahbif->bc_ctrl1.reg);
	usb_err("bc_ctrl2:[%x]\n", ahbif->bc_ctrl2.reg);
	usb_err("bc_ctrl3:[%x]\n", ahbif->bc_ctrl3.reg);
	usb_err("bc_ctrl4:[%x]\n", ahbif->bc_ctrl4.reg);
	usb_err("bc_ctrl5:[%x]\n", ahbif->bc_ctrl5.reg);
	usb_err("bc_ctrl6:[%x]\n", ahbif->bc_ctrl6.reg);
	usb_err("bc_ctrl7:[%x]\n", ahbif->bc_ctrl7.reg);
	usb_err("bc_ctrl8:[%x]\n", ahbif->bc_ctrl8.reg);
	usb_err("bc_sts0:[%x]\n", ahbif->bc_sts0.reg);
	usb_err("bc_sts1:[%x]\n", ahbif->bc_sts1.reg);
	usb_err("bc_sts2:[%x]\n", ahbif->bc_sts2.reg);
	usb_err("bc_sts3:[%x]\n", ahbif->bc_sts3.reg);
	usb_err("bc_sts4:[%x]\n", ahbif->bc_sts4.reg);
}

static void detect_charger_type(struct otg_dev *dev_p)
{
	struct usb_ahbif_registers *ahbif
		= (struct usb_ahbif_registers *)otg_dev_p->usb_ahbif_base;
	enum hisi_charger_type type = CHARGER_TYPE_NONE;
	union bc_ctrl4 bc_ctrl4;
	union bc_ctrl5 bc_ctrl5;
	union bc_sts2 bc_sts2;
	unsigned long jiffies_expire;
	int i = 0;

	/* enable BC */
	writel(1, &ahbif->bc_ctrl3);

	/* phy suspend */
	bc_ctrl4.reg = readl(&ahbif->bc_ctrl4);
	bc_ctrl4.bits.bc_suspendm = 0;
	bc_ctrl4.bits.bc_dmpulldown = 1;
	writel(bc_ctrl4.reg, &ahbif->bc_ctrl4);

	/* enable DCD */
	bc_ctrl5.reg = readl(&ahbif->bc_ctrl5);
	bc_ctrl5.bits.bc_dcd_en = 1;
	writel(bc_ctrl5.reg, &ahbif->bc_ctrl5);

	jiffies_expire = jiffies + msecs_to_jiffies(3000);
	msleep(50);
	while (i < 10) {
		union bc_sts2 bc_sts2;

		bc_sts2.reg = readl(&ahbif->bc_sts2);
		if (bc_sts2.bits.bc_fs_vplus == 0) {
			i++;
		} else if (i) {
			usb_dbg("USB D+ D- not connected!\n");
			i = 0;
		}

		msleep(1);

		if (time_after(jiffies, jiffies_expire)) {
			type = CHARGER_TYPE_UNKNOWN;
			break;
		}
	}

	/* disable DCD */
	bc_ctrl5.reg = readl(&ahbif->bc_ctrl5);
	bc_ctrl5.bits.bc_dcd_en = 0;
	writel(bc_ctrl5.reg, &ahbif->bc_ctrl5);

	if (type == CHARGER_TYPE_NONE) {
		/* enable vdect */
		bc_ctrl5.reg = readl(&ahbif->bc_ctrl5);
		bc_ctrl5.bits.bc_chrg_sel = 0;
		bc_ctrl5.bits.bc_vdat_src_en = 1;
		bc_ctrl5.bits.bc_vdat_det_en = 1;
		writel(bc_ctrl5.reg, &ahbif->bc_ctrl5);

		msleep(10);

		/* we can detect sdp or cdp dcp */
		bc_sts2.reg = readl(&ahbif->bc_sts2);
		if (bc_sts2.bits.bc_chg_det == 0) {
			type = CHARGER_TYPE_SDP;
		}

		/* disable vdect */
		bc_ctrl5.reg = readl(&ahbif->bc_ctrl5);
		bc_ctrl5.bits.bc_vdat_src_en = 0;
		bc_ctrl5.bits.bc_vdat_det_en = 0;
		writel(bc_ctrl5.reg, &ahbif->bc_ctrl5);
	}

	/* bc_suspend = 1, nomal mode */
	bc_ctrl4.reg = readl(&ahbif->bc_ctrl4);
	bc_ctrl4.bits.bc_suspendm = 1;
	writel(bc_ctrl4.reg, &ahbif->bc_ctrl4);

	msleep(10);

	/* disable BC */
	writel(0, &ahbif->bc_ctrl3);

	if (type == CHARGER_TYPE_NONE) {
		type = CHARGER_TYPE_DCP;
	}

	otg_dev_p->charger_type = type;
	usb_dbg("charger type: %s\n", charger_type_string(type));
	return;
}

int hisi_charger_type_notifier_register(struct notifier_block *nb)
{
	int ret = -1;
	if (otg_dev_p)
		ret = atomic_notifier_chain_register(
			    &otg_dev_p->charger_type_notifier, nb);
	else
		printk(KERN_ERR "Notifier head not yet init.\n");
	return ret;
}

int hisi_charger_type_notifier_unregister(struct notifier_block *nb)
{
	int ret = -1;
	if (otg_dev_p)
		ret = atomic_notifier_chain_unregister(
			    &otg_dev_p->charger_type_notifier, nb);
	else
		printk(KERN_ERR "Notifier head not yet init.\n");
	return ret;
}


enum hisi_charger_type hisi_get_charger_type(void)
{
	struct otg_dev *dev_p = otg_dev_p;
	enum hisi_charger_type type = dev_p->charger_type;
	usb_dbg("charger type: %s\n", charger_type_string(type));
	return type;
}

static void notify_charger_type(struct otg_dev *dev_p)
{
	atomic_notifier_call_chain(&dev_p->charger_type_notifier,
				dev_p->charger_type, dev_p);
}

void update_charger_type(void)
{
	if (otg_dev_p->charger_type == CHARGER_TYPE_DCP) {
		otg_dev_p->charger_type = CHARGER_TYPE_CDP;
		notify_charger_type(otg_dev_p);
		usb_dbg("charger type: %s\n", charger_type_string(
				otg_dev_p->charger_type));
	}
}

void clear_charger_interrupt(void)
{
	struct otg_dev *dev = otg_dev_p;

	if(!dev->fpga_flag) {
		hisi_pmic_reg_write(PMIC_IRQ_MASK_1_ADDR(0), (VBUS_COMP_VBAT_F | VBUS_COMP_VBAT_R));
	}
	return;
}

static int is_usb_cable_connected(void)
{
	struct otg_dev *dev = otg_dev_p;
	int ret = 1;

	if(!dev->fpga_flag) {
		ret = (hisi_pmic_reg_read(PMIC_STATUS0_ADDR(0)) & (VBUS4P3_D10 | VBUS_COMP_VBAT_D20));
	}
	return ret;
}

int dwc_otg_hicommon_is_power_on(void)
{
	return atomic_read(&is_power_on);
}

void dwc_otg_hicommon_set_prtpower(unsigned int val)
{
	struct otg_dev *p = otg_dev_p;
	enum hisi_charger_type new;

	if (0 == val) {
		new = CHARGER_TYPE_NONE;
	} else {
		new = PLEASE_PROVIDE_POWER;
	}
	if (p->charger_type != new) {
		usb_dbg("set port power %d\n", val);
		p->charger_type = new;
		notify_charger_type(p);
	}
}

static void do_disconnect(void)
{
	struct otg_dev *p = otg_dev_p;
	struct dwc_otg_device *dwc_otg_dev = lm_get_drvdata(p->lm_dev);
	if (OTG_DEV_OFF == p->status) {
		usb_dbg("Charger disconnect interrupt, but Already in OFF mode.\n");
	} else if (OTG_DEV_DEVICE == p->status) {
		/* For send uevent of disconnect. */
		dwc_otg_dev->pcd->fops->disconnect(dwc_otg_dev->pcd);

		dwc_otg_disable_global_interrupts(dwc_otg_dev->core_if);
		dwc_otg_mask_all_interrupts(dwc_otg_dev->core_if);
		dwc_otg_clear_all_interrupts(dwc_otg_dev->core_if);

		msleep(100);

		hw_shutdown(p);

		p->charger_type = CHARGER_TYPE_NONE;
		notify_charger_type(p);

		p->status = OTG_DEV_OFF;

		/* allow system go to sleep */
		dwc_otg_hicommon_wake_unlock();

		usb_dbg("hisi usb status: DEVICE -> OFF\n");
	} else if (OTG_DEV_HOST == p->status) {
		usb_dbg("Charger disconnect intrrupt in HOST mode\n");
	} else if (OTG_DEV_SUSPEND == p->status) {
		usb_dbg("Charger disconnect intrrupt in SUSPEND mode\n");
	}
}
static void event_work(struct work_struct *work)
{
	unsigned long flags;
	enum otg_dev_event_type event;
	int usb_cable_status;
	struct otg_dev *p = otg_dev_p;
	struct dwc_otg_device *dwc_otg_dev = lm_get_drvdata(p->lm_dev);

	mutex_lock(&p->lock);

	usb_dbg("+\n");

	/* get event type */
	spin_lock_irqsave(&(p->event_lock), flags);
	event = p->event;
	spin_unlock_irqrestore(&(p->event_lock), flags);
	usb_dbg("event type: %d\n", event);

	usb_cable_status = is_usb_cable_connected();

	switch (event) {
	case CHARGER_CONNECT_EVENT:
#if CHECK_USB_CABLE_STRICTLY
		if (0 == usb_cable_status) {
			usb_dbg("USB cable not connected.\n");
			goto error;
		}
#endif
		if (OTG_DEV_DEVICE == p->status) {
			usb_dbg("Already in device mode, do nothing.\n");
		} else if ((OTG_DEV_OFF == p->status)
				|| (OTG_DEV_SUSPEND == p->status)) {

			/* do not go to sleep */
			dwc_otg_hicommon_wake_lock();

			/* open ldo and clock */
			if (hw_setup(p, 0)) {
				dwc_otg_hicommon_wake_unlock();
				goto error;
			}

			/* disable usb core interrupt */
			dwc_otg_disable_global_interrupts(dwc_otg_dev->core_if);

			/* Get charger type. */
			detect_charger_type(p);
			notify_charger_type(p);

			/* reinit usb core */
			if (!dwc_otg_dev->core_if->core_params->dma_desc_enable) {
				usb_dbg("enable desc dma\n");
				dwc_otg_dev->core_if->core_params->dma_desc_enable = 1;
			}
			dwc_otg_core_init(dwc_otg_dev->core_if);
			if (dwc_otg_is_device_mode(dwc_otg_dev->core_if)) {
				cil_pcd_start(dwc_otg_dev->core_if);
				dwc_otg_dev->core_if->op_state = B_PERIPHERAL;
			} else {
				usb_dbg("error in host mode!\n");
			}

			/* enable usb core interrupt */
			dwc_otg_enable_global_interrupts(dwc_otg_dev->core_if);

			/* do software disconnect and connect for host enum again */
			dwc_otg_pcd_disconnect_us(dwc_otg_dev->pcd, 50);
			udelay(100);

			if (p->gadget_initialized)
				dwc_otg_pcd_connect_us(dwc_otg_dev->pcd, 50);
			else
				usb_dbg("gadget is not initialized!\n");

			p->status = OTG_DEV_DEVICE;

			usb_dbg("hisi usb status: OFF -> DEVICE\n");
		} else if (OTG_DEV_HOST == p->status) {
			usb_dbg("Charger connect intrrupt in HOST mode \n");
		}

		break;

	case CHARGER_DISCONNECT_EVENT:
#if CHECK_USB_CABLE_STRICTLY
		if (0 != usb_cable_status) {
			usb_dbg("Charger disconnect interrupt,"
				" but USB cable still connected!\n");
			goto error;
		}
#endif
		if (OTG_DEV_OFF == p->status) {
			usb_dbg("Charger disconnect interrupt, but Already in OFF mode.\n");
		} else if (OTG_DEV_DEVICE == p->status) {
			/* For send uevent of disconnect. */
			dwc_otg_dev->pcd->fops->disconnect(dwc_otg_dev->pcd);

			dwc_otg_disable_global_interrupts(dwc_otg_dev->core_if);
			dwc_otg_mask_all_interrupts(dwc_otg_dev->core_if);
			dwc_otg_clear_all_interrupts(dwc_otg_dev->core_if);

			msleep(100);

			hw_shutdown(p);

			p->charger_type = CHARGER_TYPE_NONE;
			notify_charger_type(p);

			p->status = OTG_DEV_OFF;

			/* allow system go to sleep */
			dwc_otg_hicommon_wake_unlock();

			usb_dbg("hisi usb status: DEVICE -> OFF\n");
		} else if (OTG_DEV_HOST == p->status) {
			usb_dbg("Charger disconnect intrrupt in HOST mode\n");
		} else if (OTG_DEV_SUSPEND == p->status) {
			usb_dbg("Charger disconnect intrrupt in SUSPEND mode\n");
		}
		break;

	case ID_FALL_EVENT:
		if ((OTG_DEV_OFF == p->status) || (OTG_DEV_SUSPEND == p->status)) {
			unsigned int count = 0;

			if (hw_setup(p, 1)) {
				goto error;
			}

			if (dwc_otg_dev->core_if->core_params->dma_desc_enable) {
				usb_dbg("disable desc dma\n");
				dwc_otg_dev->core_if->core_params->dma_desc_enable = 0;
			}
			dwc_otg_disable_global_interrupts(dwc_otg_dev->core_if);
			while (!dwc_otg_is_host_mode(dwc_otg_dev->core_if)) {
				msleep(10);
				if(++count > 100) {
					printk(KERN_ERR "wait host mode timeout\n");
					goto error;
				}
			}
			dwc_otg_core_init(dwc_otg_dev->core_if);

			msleep(100);
			if (dwc_otg_is_host_mode(dwc_otg_dev->core_if)) {
				dwc_otg_dev->core_if->op_state = A_HOST;
				usb_dbg("dwc otg is host mode.\n");
			} else {
				usb_dbg("error in device mode!\n");
			}

			cil_hcd_start(dwc_otg_dev->core_if);
			dwc_otg_hicommon_set_prtpower(1);
			p->status = OTG_DEV_HOST;

			usb_dbg("hisi usb_status: OFF -> HOST\n");
		} else if (OTG_DEV_DEVICE == p->status) {
			usb_dbg("hisi usb_status: DEVICE -> HOST\n");
			p->status = OTG_DEV_HOST;
		} else if (OTG_DEV_HOST == p->status) {
			usb_dbg("ID fall event, already in host mode\n");
		}
		break;
	case ID_RISE_EVENT:
		if (OTG_DEV_HOST == p->status) {

			extern atomic_t dwc_otg_hcd_bus_state;
			while (0 != atomic_read(&dwc_otg_hcd_bus_state)) {
				msleep(200);
				usb_dbg("wait for dwc_otg_bus_suspend\n");
			}

			dwc_otg_disable_global_interrupts(dwc_otg_dev->core_if);
			dwc_otg_mask_all_interrupts(dwc_otg_dev->core_if);
			dwc_otg_clear_all_interrupts(dwc_otg_dev->core_if);
			hw_shutdown(p);
			p->status = OTG_DEV_OFF;

			dwc_otg_hicommon_set_prtpower(0);
#ifndef FORCE_ID_STATE
#if defined (CONFIG_SWITCH_FSA9685)
			{
				extern int fsa9685_manual_detach(void);
				fsa9685_manual_detach();
			}
#endif
#endif

			usb_dbg("hiusb_status: HOST -> OFF\n");
		} else if (OTG_DEV_DEVICE == p->status) {
			usb_dbg("hiusb_status: HOST -> DEVICE\n");
		} else if (OTG_DEV_OFF == p->status) {
			usb_dbg("ID rise event, Already in OFF mode\n");
		} else if (OTG_DEV_SUSPEND == p->status) {
			usb_dbg("ID rise in SUSPEND mode\n");
			p->status = OTG_DEV_OFF;
		}
		break;
	default:
		usb_dbg("illegal event type!\n");
		break;
	}

error:
	usb_dbg("-\n");
	mutex_unlock(&p->lock);
	return;
}

static int event_type_check(enum otg_dev_event_type last_event,
		enum otg_dev_event_type current_event)
{
	int ret = 0;

	if (last_event == NONE_EVENT)
		return 1;

	switch (current_event) {
	case CHARGER_CONNECT_EVENT:
		if ((last_event == CHARGER_DISCONNECT_EVENT)
				|| (last_event == ID_RISE_EVENT))
			ret = 1;
		break;
	case CHARGER_DISCONNECT_EVENT:
		if (last_event == CHARGER_CONNECT_EVENT)
			ret = 1;
		break;
	case ID_FALL_EVENT:
		if ((last_event == CHARGER_DISCONNECT_EVENT)
				|| (last_event == ID_RISE_EVENT))
			ret = 1;
		break;
	case ID_RISE_EVENT:
		if (last_event == ID_FALL_EVENT)
			ret = 1;
		break;
	default:
		break;
	}
	return ret;
}

int hisi_usb_otg_event(enum otg_dev_event_type event)
{
	struct otg_dev *dev_p = otg_dev_p;
	unsigned long flags;
	int ret = 0;

	if (0 == atomic_read(&is_event_work_ready)) {
		return 0;
	}

	spin_lock_irqsave(&(dev_p->event_lock), flags);
	if (event_type_check(dev_p->event, event)) {
		usb_dbg("event: %d\n", event);
		dev_p->event = event;

		if (CHARGER_CONNECT_EVENT == event)
			dwc_otg_hicommon_wake_lock();

		ret = schedule_delayed_work(&dev_p->event_work, 0);
	}
	spin_unlock_irqrestore(&(dev_p->event_lock), flags);
	return ret;
}

void dwc_otg_hicommon_wake_lock(void)
{
	if (!wake_lock_active(&otg_dev_p->wake_lock)) {
		usb_dbg("usb otg wake lock\n");
		wake_lock(&otg_dev_p->wake_lock);
	}
}

void dwc_otg_hicommon_wake_unlock(void)
{
	if (wake_lock_active(&otg_dev_p->wake_lock)) {
		usb_dbg("usb otg wake unlock\n");
		wake_unlock(&otg_dev_p->wake_lock);
	}
}

int dwc_otg_hicommon_pullup(struct usb_gadget *gadget, int is_on)
{
	dwc_otg_device_t *dwc_otg_dev;

	if (gadget == 0) {
		return -ENODEV;
	}

	dwc_otg_dev = lm_get_drvdata(otg_dev_p->lm_dev);

	/* lock */
	mutex_lock(&otg_dev_p->lock);

	if (is_on) {
		otg_dev_p->gadget_initialized = 1;
	} else {
		otg_dev_p->gadget_initialized = 0;
	}

	if ((OTG_DEV_DEVICE == otg_dev_p->status)) {
		if (is_on)
			dwc_otg_pcd_connect_us(dwc_otg_dev->pcd,50);
		else
			dwc_otg_pcd_disconnect_us(dwc_otg_dev->pcd,50);
	}

	/* unlock */
	mutex_unlock(&otg_dev_p->lock);
	return 0;
}

extern struct usb_gadget_ops dwc_otg_pcd_ops;

int dwc_otg_hicommon_probe_stage2(void)
{
	struct otg_dev * otg_device = otg_dev_p;
	dwc_otg_device_t *dwc_otg_dev = lm_get_drvdata(otg_device->lm_dev);

	usb_dbg("[%s]+\n", __func__);

	mutex_lock(&otg_device->lock);

	dwc_otg_pcd_ops.pullup = dwc_otg_hicommon_pullup;

	atomic_set(&is_event_work_ready, 1);
	usb_dbg("is_event_work_ready: %d\n", atomic_read(&is_event_work_ready));

	if (dwc_otg_is_host_mode(dwc_otg_dev->core_if)) {
		usb_dbg("host mode\n");
		if (dwc_otg_dev->core_if->core_params->dma_desc_enable) {
		        usb_dbg("disable desc dma\n");
		        dwc_otg_dev->core_if->core_params->dma_desc_enable = 0;
			/* reinit controller with buffer dma */
			dwc_otg_core_init(dwc_otg_dev->core_if);
			cil_hcd_start(dwc_otg_dev->core_if);
			dwc_otg_hicommon_set_prtpower(1);
		}
		otg_device->status = OTG_DEV_HOST;
	} else if (0 == is_usb_cable_connected()) {
		usb_dbg("USB cable disconnected, hw shutdown.\n");
		hw_shutdown(otg_device);
		otg_device->status = OTG_DEV_OFF;
	} else {
		usb_dbg("USB cable connected.\n");

		/*
		 * detect charger type
		 */
		detect_charger_type(otg_device);
		notify_charger_type(otg_device);

		/*
		 * detect charger type will cause controller abnormal
		 * so, we need initialize it again!
		 */
		dwc_otg_disable_global_interrupts(dwc_otg_dev->core_if);
		dwc_otg_core_init(dwc_otg_dev->core_if);
		if (dwc_otg_is_device_mode(dwc_otg_dev->core_if)) {
			cil_pcd_start(dwc_otg_dev->core_if);
			dwc_otg_dev->core_if->op_state = B_PERIPHERAL;
		}

		dwc_otg_pcd_disconnect_us(dwc_otg_dev->pcd, 50);
		udelay(100);

		if (otg_device->gadget_initialized) {
			usb_dbg("gadget is initialized\n");
			dwc_otg_pcd_connect_us(dwc_otg_dev->pcd, 50);
		}

		usb_dbg("enable global interrupts\n");
		dwc_otg_enable_global_interrupts(dwc_otg_dev->core_if);
		otg_device->status = OTG_DEV_DEVICE;

		/* do not go to sleep when USB connected */
		dwc_otg_hicommon_wake_lock();
	}

	mutex_unlock(&otg_device->lock);

	usb_dbg("[%s]-\n", __func__);
	return 0;
}

int dwc_otg_hicommon_probe(struct otg_dev *dev_p)
{
	int ret = 0;
	int irq = 0;
	struct lm_device *lm_dev = NULL;
	struct platform_device *pdev = dev_p->pdev;
	struct resource *res = NULL;

	usb_dbg("[%s]+\n", __func__);

	platform_set_drvdata(pdev, dev_p);

	dev_p->event = NONE_EVENT;
	dev_p->charger_type = CHARGER_TYPE_NONE;
	dev_p->status = OTG_DEV_OFF;
	dev_p->hcd_status = HCD_OFF;
	dev_p->gadget_initialized = 0;
	dev_p->dwc_otg_irq_enabled = true;
	dev_p->is_regu_on = 0;
	INIT_DELAYED_WORK(&dev_p->event_work, event_work);
	wake_lock_init(&dev_p->wake_lock, WAKE_LOCK_SUSPEND, "usb_wake_lock");
	spin_lock_init(&dev_p->event_lock);
	mutex_init(&dev_p->lock);
	ATOMIC_INIT_NOTIFIER_HEAD(&dev_p->charger_type_notifier);

	/* save dev_p to global for myself */
	otg_dev_p = dev_p;

	ret = get_resource(dev_p);
	if (ret) {
		usb_err("get resource failed 1!\n");
		return ret;
	}

	if(dev_p->fpga_usb_mode_gpio > 0) {
		ret = gpio_request(dev_p->fpga_usb_mode_gpio, NULL);
		if(ret) {
			/* request gpio failure! */
			usb_err("request gpio fail.[%d], gpio num:%d!\n", ret, dev_p->fpga_usb_mode_gpio);
		}
	}

	ret = hw_setup(dev_p, 0);
	if (ret) {
		usb_err("hw setup failed!\n");
		put_resource(dev_p);
		return ret;
	}

	dev_p->status = OTG_DEV_DEVICE;

	ret = create_attr_file(&pdev->dev);
	if (ret) {
		usb_err("create_attr_file failed!\n");
		goto error;
	}

	/*
	 * register the dwc otg device
	 */

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		usb_err("get resource failed 2!\n");
		ret = -EBUSY;
		goto error;
	}

	usb_dbg("res start: 0x%llx, res end: 0x%llx, res flags: %ld\n",
		res->start, res->end, res->flags);

	irq = platform_get_irq(pdev, 0);
	if (!irq) {
		usb_err("get irq failed!\n");
		ret = -EBUSY;
		goto error;
	}

	lm_dev = devm_kzalloc(&pdev->dev, sizeof(*lm_dev), GFP_KERNEL);
	if (!lm_dev) {
		usb_err("alloc lm_dev failed! not enough memory\n");
		ret = -ENOMEM;
		goto error;
	}

	dev_p->lm_dev = lm_dev;

	lm_dev->resource.start = res->start;
	lm_dev->resource.end = res->end;
	lm_dev->resource.flags = res->flags;
	lm_dev->irq = irq;
	lm_dev->id = -1;
	lm_dev->dev.init_name = "hisi-usb-otg";
	//lm_dev->dev.parent = &pdev->dev;

	ret = lm_device_register(lm_dev);
	if (ret) {
		usb_err("register dwc otg device failed\n");
		goto error;
	}
	usb_dbg("register dwc otg device done\n");

	dwc_otg_hicommon_probe_stage2();

	usb_dbg("[%s]-\n", __func__);

	return 0;
error:
	hw_shutdown(dev_p);
	put_resource(dev_p);
	return ret;

}

int dwc_otg_hicommon_remove(struct otg_dev *dev_p)
{
	if ((dev_p->status == OTG_DEV_DEVICE) || (dev_p->status == OTG_DEV_HOST)) {
		hw_shutdown(dev_p);
	}
	put_resource(dev_p);
	return 0;
}

static int dwc_otg_hicommon_suspend(struct device *dev)
{
	struct otg_dev *dev_p = dev_get_drvdata(dev);
	usb_dbg("\n");
	mutex_lock(&dev_p->lock);
	return 0;
}

static int dwc_otg_hicommon_resume(struct device *dev)
{
	struct otg_dev *dev_p = dev_get_drvdata(dev);
	struct otg_dev *p = otg_dev_p;
	usb_dbg("\n");
	mutex_unlock(&dev_p->lock);
	if (1 == release_wakelock)
	{
		p->status = OTG_DEV_OFF;
		p->event = CHARGER_CONNECT_EVENT;
		release_wakelock = 0;
		schedule_delayed_work(&dev_p->event_work, 0);
	}
	return 0;
}

#ifdef CONFIG_PM
struct dev_pm_ops dwc_otg_dev_pm_ops = {
	.prepare = NULL,
	.complete = NULL,
	.suspend = dwc_otg_hicommon_suspend,
	.resume = dwc_otg_hicommon_resume,

	.runtime_suspend = NULL,
	.runtime_resume = NULL,
	.runtime_idle = NULL,
};
#endif
