#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/io.h>
#include <linux/wakelock.h>
#include <linux/regulator/consumer.h>
#include <linux/usb/ch9.h>

#include <linux/huawei/usb/hisi_usb.h>

#include "dwc3-hisi.h"
#include "core.h"
#include "dwc3-otg.h"
#include "hisi_usb_vbus.h"

#define usb_dbg(format, arg...)    \
	do {                 \
		printk(KERN_INFO "[USB3][%s]"format, __func__, ##arg); \
	} while (0)

#define usb_err(format, arg...)    \
	do {                 \
		printk(KERN_ERR "[USB3][%s]"format, __func__, ##arg); \
	} while (0)

#define ENABLE_USB_TEST_PORT

enum hisi_usb_state {
	USB_STATE_UNKNOWN = 0,
	USB_STATE_OFF,
	USB_STATE_DEVICE,
	USB_STATE_HOST,
};

struct hisi_dwc3_device {
	struct platform_device *pdev;

	void __iomem *otg_bc_reg_base;
	void __iomem *pericfg_reg_base;
	void __iomem *pctrl_reg_base;

	struct regulator *otgdebugsubsys_regu;
	struct regulator *usbldo10_regu;
	unsigned int is_regu_on;
	unsigned int runtime_suspended;

	enum hisi_usb_state state;
	enum hisi_charger_type charger_type;
	enum hisi_charger_type fake_charger_type;

	enum otg_dev_event_type event;
	spinlock_t event_lock;

	struct mutex lock;
	struct wake_lock wake_lock;
	struct atomic_notifier_head charger_type_notifier;
	struct work_struct event_work;

	u32 eye_diagram_param;	/* this param will be set to USBOTG3_CTRL4 */
	u32 eye_diagram_host_param;
	u32 usb3_phy_cr_param;
	u32 usb3_phy_host_cr_param;
	u32 usb3_phy_tx_vboost_lvl;
	unsigned int host_flag;

	u32 fpga_flag;

	struct clk *clk;
	struct clk *gt_aclk_usb3otg;

	int eventmask;
};

struct hisi_dwc3_device *hisi_dwc3_dev;
atomic_t hisi_dwc3_power_on = ATOMIC_INIT(0);


#ifdef ENABLE_USB_TEST_PORT

static ssize_t plugusb_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct hisi_dwc3_device *hisi_dwc3 = platform_get_drvdata(pdev);
	char *s;

	if (!hisi_dwc3) {
		usb_err("hisi_dwc3 NULL\n");
		return scnprintf(buf,PAGE_SIZE, "hisi_dwc3 NULL\n");
	}

	switch (hisi_dwc3->state) {

	case USB_STATE_UNKNOWN:
		s = "USB_STATE_UNKNOWN";
		break;
	case USB_STATE_OFF:
		s = "USB_STATE_OFF";
		break;
	case USB_STATE_DEVICE:
		s = "USB_STATE_DEVICE";
		break;
	case USB_STATE_HOST:
		s = "USB_STATE_HOST";
		break;
	default :
		s = "unknown";
		break;
	}
	return scnprintf(buf,PAGE_SIZE, "current state: %s\n" "usage: %s\n", s,
		"echo hoston/hostoff/deviceon/deviceoff > plugusb\n");
}
static ssize_t plugusb_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	if (!strncmp(buf, "hoston", strlen("hoston"))) {
		hisi_usb_otg_event(ID_FALL_EVENT);
	} else if (!strncmp(buf, "hostoff", strlen("hostoff"))) {
		hisi_usb_otg_event(ID_RISE_EVENT);
	} else if (!strncmp(buf, "deviceon", strlen("deviceon"))) {
		hisi_usb_otg_event(CHARGER_CONNECT_EVENT);
	} else if (!strncmp(buf, "deviceoff", strlen("deviceoff"))) {
		hisi_usb_otg_event(CHARGER_DISCONNECT_EVENT);
	} else
		usb_err("input state is ilegal!\n");

	return size;
}

/*lint -save -e750 */
DEVICE_ATTR(plugusb, (S_IRUGO | S_IWUSR), plugusb_show, plugusb_store);
/*lint -restore */


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
	struct hisi_dwc3_device *hisi_dwc = platform_get_drvdata(to_platform_device(dev));
	enum hisi_charger_type charger_type = CHARGER_TYPE_NONE;

	if (!hisi_dwc) {
		dev_err(dev, "platform_get_drvdata return null\n");
		return scnprintf(buf,PAGE_SIZE, "platform_get_drvdata return null\n");
	}

	mutex_lock(&hisi_dwc->lock);
	charger_type = hisi_dwc->charger_type;
	mutex_unlock(&hisi_dwc->lock);

	return scnprintf( buf,PAGE_SIZE, "[(%d):Charger type = %s]\n"
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

static void notify_charger_type(struct hisi_dwc3_device *hisi_dwc3);
static ssize_t charger_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	struct hisi_dwc3_device *hisi_dwc = platform_get_drvdata(to_platform_device(dev));
	enum hisi_charger_type charger_type = get_charger_type_from_str(buf, size);

	if (!hisi_dwc) {
		dev_err(dev, "platform_get_drvdata return null\n");
		return size;
	}

	mutex_lock(&hisi_dwc->lock);
	hisi_dwc->charger_type = charger_type;
	notify_charger_type(hisi_dwc);
	mutex_unlock(&hisi_dwc->lock);

	return size;
}

DEVICE_ATTR(charger, (S_IRUGO | S_IWUSR), charger_show, charger_store);

static ssize_t fakecharger_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct hisi_dwc3_device *hisi_dwc = platform_get_drvdata(to_platform_device(dev));

	if (!hisi_dwc) {
		dev_err(dev, "platform_get_drvdata return null\n");
		return scnprintf(buf, PAGE_SIZE,"platform_get_drvdata return null\n");
	}

	return scnprintf( buf,PAGE_SIZE, "[fake charger type: %s]\n",
		hisi_dwc->fake_charger_type == CHARGER_TYPE_NONE ? "not fake" :
		charger_type_array[hisi_dwc->fake_charger_type] );
}

static ssize_t fakecharger_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct hisi_dwc3_device *hisi_dwc = platform_get_drvdata(to_platform_device(dev));
	enum hisi_charger_type charger_type = get_charger_type_from_str(buf, size);

	if (!hisi_dwc) {
		dev_err(dev, "platform_get_drvdata return null\n");
		return size;
	}

	mutex_lock(&hisi_dwc->lock);
	hisi_dwc->fake_charger_type = charger_type;
	mutex_unlock(&hisi_dwc->lock);

	return size;
}

DEVICE_ATTR(fakecharger, (S_IRUGO | S_IWUSR), fakecharger_show, fakecharger_store);

static ssize_t eventmask_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct hisi_dwc3_device *hisi_dwc = platform_get_drvdata(to_platform_device(dev));

	if (!hisi_dwc) {
		dev_err(dev, "platform_get_drvdata return null\n");
		return scnprintf(buf,PAGE_SIZE, "platform_get_drvdata return null\n");
	}

	return scnprintf(buf,PAGE_SIZE, "%d\n", hisi_dwc->eventmask);
}

static ssize_t eventmask_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct hisi_dwc3_device *hisi_dwc = platform_get_drvdata(to_platform_device(dev));
	int eventmask;

	if (!hisi_dwc) {
		dev_err(dev, "platform_get_drvdata return null\n");
		return size;
	}

	if (sscanf(buf, "%1d", &eventmask) != 1) {
		return size;
	}

	hisi_dwc->eventmask = eventmask;

	return size;
}

/*lint -save -e750 */
DEVICE_ATTR(eventmask, (S_IRUGO | S_IWUSR), eventmask_show, eventmask_store);
/*lint -restore */

static int create_attr_file(struct device *dev)
{
	int ret = 0;
	usb_dbg("+\n");
	ret |= device_create_file(dev, &dev_attr_plugusb);
	ret |= device_create_file(dev, &dev_attr_charger);
	ret |= device_create_file(dev, &dev_attr_fakecharger);
	ret |= device_create_file(dev, &dev_attr_eventmask);
	if (ret) {
		dev_err(dev, "create attr file error!\n");
	}
	usb_dbg("-\n");
	return ret;
}
#else
static inline int create_attr_file(struct device *dev){return 0;}
#endif

static void dwc3_reset(struct hisi_dwc3_device *hisi_dwc)
{
	void __iomem *pericfg_base = hisi_dwc->pericfg_reg_base;
	void __iomem *otg_bc_base = hisi_dwc->otg_bc_reg_base;

	/* reset phy */
	writel(IP_RST_USB3OTG, pericfg_base + PERI_CRG_RSTEN4);
	writel(IP_RST_USB3OTGPHY_POR, pericfg_base + PERI_CRG_RSTEN4);
	/* dealy 100us */
	udelay(100);

	/* power down high speed and super speed */
	writel(USBOTG3CTRL2_POWERDOWN_HSP | USBOTG3CTRL2_POWERDOWN_SSP,
			otg_bc_base + USBOTG3_CTRL2);
	/* delay 100us */
	udelay(100);
}


static void phy_cr_wait_ack(void __iomem *otg_bc_base)
{
	int i = 1000;

	while(1) {
		if ((readl(otg_bc_base + USB3PHY_CR_STS) & USB3OTG_PHY_CR_ACK) == 1)
			break;
		udelay(50);
		if (i-- < 0) {
			usb_err("wait phy_cr_ack timeout!\n");
			break;
		}
	}
}

static void phy_cr_set_addr(void __iomem *otg_bc_base, u32 addr)
{
	u32 reg;

	/* set addr */
	reg = USB3OTG_PHY_CR_DATA_IN(addr);
	writel(reg, otg_bc_base + USB3PHY_CR_CTRL);

	udelay(100);

	/* cap addr */
	reg = readl(otg_bc_base + USB3PHY_CR_CTRL);
	reg |= USB3OTG_PHY_CR_CAP_ADDR;
	writel(reg, otg_bc_base + USB3PHY_CR_CTRL);

	phy_cr_wait_ack(otg_bc_base);

	/* clear ctrl reg */
	writel(0, otg_bc_base + USB3PHY_CR_CTRL);
}

static u16 phy_cr_read(void __iomem *otg_bc_base, u32 addr)
{
	u32 reg;
	int i = 1000;

	phy_cr_set_addr(otg_bc_base, addr);

	/* read cap */
	writel(USB3OTG_PHY_CR_READ, otg_bc_base + USB3PHY_CR_CTRL);

	udelay(100);

	while(1) {
		reg = readl(otg_bc_base + USB3PHY_CR_STS);
		if ((reg & USB3OTG_PHY_CR_ACK) == 1) {
			break;
		}
		udelay(50);
		if (i-- < 0) {
			usb_err("wait phy_cr_ack timeout!\n");
			break;
		}
	}

	/* clear ctrl reg */
	writel(0, otg_bc_base + USB3PHY_CR_CTRL);

	return (u16)USB3OTG_PHY_CR_DATA_OUT(reg);
}

static void phy_cr_write(void __iomem *otg_bc_base, u32 addr, u32 value)
{
	u32 reg;

	phy_cr_set_addr(otg_bc_base, addr);

	reg = USB3OTG_PHY_CR_DATA_IN(value);
	writel(reg, otg_bc_base + USB3PHY_CR_CTRL);

	/* cap data */
	reg = readl(otg_bc_base + USB3PHY_CR_CTRL);
	reg |= USB3OTG_PHY_CR_CAP_DATA;
	writel(reg, otg_bc_base + USB3PHY_CR_CTRL);

	/* wait ack */
	phy_cr_wait_ack(otg_bc_base);

	/* clear ctrl reg */
	writel(0, otg_bc_base + USB3PHY_CR_CTRL);

	reg = USB3OTG_PHY_CR_WRITE;
	writel(reg, otg_bc_base + USB3PHY_CR_CTRL);

	/* wait ack */
	phy_cr_wait_ack(otg_bc_base);
}

void set_usb3_phy_cr_param(u32 addr, u32 value)
{
	if (!hisi_dwc3_dev) {
		pr_err("hisi dwc3 device not ready!\n");
		return;
	}

	phy_cr_write(hisi_dwc3_dev->otg_bc_reg_base, addr, value);
}
EXPORT_SYMBOL_GPL(set_usb3_phy_cr_param);

void read_usb3_phy_cr_param(u32 addr)
{
	if (!hisi_dwc3_dev) {
		pr_err("hisi dwc3 device not ready!\n");
		return;
	}

	usb_dbg("read usb3 phy cr param 0x%x\n",
		phy_cr_read(hisi_dwc3_dev->otg_bc_reg_base, addr));
}
EXPORT_SYMBOL_GPL(read_usb3_phy_cr_param);

static void dwc3_release(struct hisi_dwc3_device *hisi_dwc)
{
	void __iomem *pericfg_base = hisi_dwc->pericfg_reg_base;
	void __iomem *otg_bc_base = hisi_dwc->otg_bc_reg_base;
	uint32_t reg;

	/* reset controller ahbif */
	writel(IP_RST_USB3OTG_MUX | IP_RST_USB3OTG_AHBIF | IP_RST_USB3OTG_32K,
			pericfg_base + PERI_CRG_RSTEN4);
	/* delay 100us */
	 udelay(100);

	/* unreset controller ahbif */
	writel(IP_RST_USB3OTG_MUX | IP_RST_USB3OTG_AHBIF | IP_RST_USB3OTG_32K,
			pericfg_base + PERI_CRG_RSTDIS4);

	/* reset phy */
	writel(IP_RST_USB3OTGPHY_POR | IP_RST_USB3OTG, pericfg_base + PERI_CRG_RSTEN4);
	udelay(100);

	/* set ref_ssp_en: Reference Clock Enable for SS function. */
	reg = readl(otg_bc_base + USBOTG3_CTRL7);
	writel((reg | 0x10000), otg_bc_base + USBOTG3_CTRL7);
	udelay(100);

	/* unreset phy */
	writel(IP_RST_USB3OTGPHY_POR, pericfg_base + PERI_CRG_RSTDIS4);
	udelay(100);

	/* unreset controller */
	writel(IP_RST_USB3OTG, pericfg_base + PERI_CRG_RSTDIS4);
	msleep(10);

	/* fake vbus valid signal */
	reg = readl(otg_bc_base + USBOTG3_CTRL3);
	reg |= (USBOTG3_CTRL3_VBUSVLDEXT | USBOTG3_CTRL3_VBUSVLDEXTSEL);
	writel(reg, otg_bc_base + USBOTG3_CTRL3);

	if (!hisi_dwc->fpga_flag) {
		/* set high speed phy parameter */
		if (hisi_dwc->host_flag) {
			writel(hisi_dwc->eye_diagram_host_param, otg_bc_base + USBOTG3_CTRL4);
			usb_dbg("set hs phy param 0x%x for host\n",
					readl(otg_bc_base + USBOTG3_CTRL4));
		} else {
			writel(hisi_dwc->eye_diagram_param, otg_bc_base + USBOTG3_CTRL4);
			usb_dbg("set hs phy param 0x%x for device\n",
					readl(otg_bc_base + USBOTG3_CTRL4));
		}

		/* set usb3 phy cr config for usb3.0 */

		if (hisi_dwc->host_flag) {
			phy_cr_write(otg_bc_base, 0x1006, hisi_dwc->usb3_phy_host_cr_param);
		} else {
			phy_cr_write(otg_bc_base, 0x1006, hisi_dwc->usb3_phy_cr_param);
		}

		usb_dbg("set ss phy rx equalization 0x%x\n", phy_cr_read(otg_bc_base, 0x1006));

		reg = readl(otg_bc_base + USBOTG3_CTRL6);
		reg &= ~TX_VBOOST_LVL_MASK;
		reg |= TX_VBOOST_LVL(hisi_dwc->usb3_phy_tx_vboost_lvl);
		writel(reg, otg_bc_base + USBOTG3_CTRL6);
		usb_dbg("set ss phy tx vboost lvl 0x%x\n", readl(otg_bc_base + USBOTG3_CTRL6));
	}
}

int hisi_charger_type_notifier_register(struct notifier_block *nb)
{
	if (!hisi_dwc3_dev) {
		pr_err("hisi dwc3 device not ready!\n");
		return -EBUSY;
	}
	if (!nb)
		return -EINVAL;
	return atomic_notifier_chain_register(&hisi_dwc3_dev->charger_type_notifier, nb);
}
EXPORT_SYMBOL_GPL(hisi_charger_type_notifier_register);

int hisi_charger_type_notifier_unregister(struct notifier_block *nb)
{
	if (!hisi_dwc3_dev) {
		pr_err("hisi dwc3 device not ready!\n");
		return -EBUSY;
	}
	if (!nb)
		return -EINVAL;
	return atomic_notifier_chain_unregister(&hisi_dwc3_dev->charger_type_notifier, nb);
}
EXPORT_SYMBOL_GPL(hisi_charger_type_notifier_unregister);

/* BC1.2 Spec:
 * If a PD detects that D+ is greater than VDAT_REF, it knows that it is
 * attached to a DCP. It is then required to enable VDP_SRC or pull D+
 * to VDP_UP through RDP_UP */
static void disable_vdp_src(struct hisi_dwc3_device *hisi_dwc3)
{
	void __iomem *base = hisi_dwc3->otg_bc_reg_base;
	uint32_t reg;

	usb_dbg("Disconnect from DCP, diaable VDP_SRC\n");

	reg = readl(base + BC_CTRL2);
	reg &= ~(BC_CTRL2_BC_PHY_VDATARCENB | BC_CTRL2_BC_PHY_VDATDETENB);
	writel(reg, base + BC_CTRL2);

	reg = readl(base + BC_CTRL0);
	reg |= BC_CTRL0_BC_SUSPEND_N;
	writel(reg, base + BC_CTRL0);

	writel((readl(base + BC_CTRL1) & ~BC_CTRL1_BC_MODE), base + BC_CTRL1);
}

static enum hisi_charger_type detect_charger_type(struct hisi_dwc3_device
				*hisi_dwc3)
{
	enum hisi_charger_type type = CHARGER_TYPE_NONE;
	void __iomem *base = hisi_dwc3->otg_bc_reg_base;
	uint32_t reg;
	unsigned long jiffies_expire;
	int i = 0;

	if (hisi_dwc3->fpga_flag) {
		usb_dbg("this is fpga platform, charger is SDP\n");
		return CHARGER_TYPE_SDP;
	}

	if (hisi_dwc3->fake_charger_type != CHARGER_TYPE_NONE) {
		usb_dbg("fake type: %d\n", hisi_dwc3->fake_charger_type);
		return hisi_dwc3->fake_charger_type;
	}

	writel(BC_CTRL1_BC_MODE, base + BC_CTRL1);

	/* phy suspend */
	reg = readl(base + BC_CTRL0);
	reg &= ~BC_CTRL0_BC_SUSPEND_N;
	writel(reg, base + BC_CTRL0);

	/* enable DCD */
	reg = readl(base + BC_CTRL2);
	reg |= BC_CTRL2_BC_PHY_DCDENB;
	writel(reg, base + BC_CTRL2);

	reg = readl(base + BC_CTRL0);
	reg |= BC_CTRL0_BC_DMPULLDOWN;
	writel(reg, base + BC_CTRL0);

	jiffies_expire = jiffies + msecs_to_jiffies(900);
	msleep(50);
	while (1) {
		reg = readl(base + BC_STS0);
		if ((reg & BC_STS0_BC_PHY_FSVPLUS) == 0) {
			i++;
			if (i >= 10)
				break;
		} else {
			i = 0;
		}

		msleep(10);

		if (time_after(jiffies, jiffies_expire)) {
			usb_dbg("DCD timeout!\n");
			type = CHARGER_TYPE_UNKNOWN;
			break;
		}
	}

	reg = readl(base + BC_CTRL0);
	reg &= ~BC_CTRL0_BC_DMPULLDOWN;
	writel(reg, base + BC_CTRL0);

	/* disable DCD */
	reg = readl(base + BC_CTRL2);
	reg &= ~BC_CTRL2_BC_PHY_DCDENB;
	writel(reg, base + BC_CTRL2);

	usb_dbg("DCD done\n");

	if (type == CHARGER_TYPE_NONE) {
		/* enable vdect */
		reg = readl(base + BC_CTRL2);
		reg &= ~BC_CTRL2_BC_PHY_CHRGSEL;
		reg |= (BC_CTRL2_BC_PHY_VDATARCENB | BC_CTRL2_BC_PHY_VDATDETENB);
		writel(reg, base + BC_CTRL2);

		msleep(10);

		/* we can detect sdp or cdp dcp */
		reg = readl(base + BC_STS0);
		if ((reg & BC_STS0_BC_PHY_CHGDET) == 0) {
			type = CHARGER_TYPE_SDP;
		}

		/* disable vdect */
		reg = readl(base + BC_CTRL2);
		reg &= ~(BC_CTRL2_BC_PHY_VDATARCENB | BC_CTRL2_BC_PHY_VDATDETENB);
		writel(reg, base + BC_CTRL2);
	}

	usb_dbg("Primary Detection done\n");

	if (type == CHARGER_TYPE_NONE) {
		/* enable vdect */
		reg = readl(base + BC_CTRL2);
		reg |= (BC_CTRL2_BC_PHY_VDATARCENB | BC_CTRL2_BC_PHY_VDATDETENB
				| BC_CTRL2_BC_PHY_CHRGSEL);
		writel(reg, base + BC_CTRL2);

		msleep(10);

		/* we can detect sdp or cdp dcp */
		reg = readl(base + BC_STS0);
		if ((reg & BC_STS0_BC_PHY_CHGDET) == 0)
			type = CHARGER_TYPE_CDP;
		else
			type = CHARGER_TYPE_DCP;

		/* disable vdect */
		reg = readl(base + BC_CTRL2);
		reg &= ~(BC_CTRL2_BC_PHY_VDATARCENB | BC_CTRL2_BC_PHY_VDATDETENB
				| BC_CTRL2_BC_PHY_CHRGSEL);
		writel(reg, base + BC_CTRL2);
	}

	usb_dbg("Secondary Detection done\n");

	/* If a PD detects that D+ is greater than VDAT_REF, it knows that it is
	 * attached to a DCP. It is then required to enable VDP_SRC or pull D+
	 * to VDP_UP through RDP_UP */
	if (type == CHARGER_TYPE_DCP) {
		usb_dbg("charger is DCP, enable VDP_SRC\n");
		reg = readl(base + BC_CTRL2);
		reg &= ~BC_CTRL2_BC_PHY_CHRGSEL;
		reg |= (BC_CTRL2_BC_PHY_VDATARCENB | BC_CTRL2_BC_PHY_VDATDETENB);
		writel(reg, base + BC_CTRL2);
	} else {
		/* bc_suspend = 1, nomal mode */
		reg = readl(base + BC_CTRL0);
		reg |= BC_CTRL0_BC_SUSPEND_N;
		writel(reg, base + BC_CTRL0);

		msleep(10);

		/* disable BC */
		writel((readl(base + BC_CTRL1) & ~BC_CTRL1_BC_MODE), base + BC_CTRL1);
	}

	usb_dbg("type: %d\n", type);

	return type;
}

enum hisi_charger_type hisi_get_charger_type(void)
{
	if (!hisi_dwc3_dev) {
		pr_err("[%s]hisi_dwc3 not yet probed!\n", __func__);
		return CHARGER_TYPE_NONE;
	}

	pr_info("[%s]type: %d\n", __func__, hisi_dwc3_dev->charger_type);
	return hisi_dwc3_dev->charger_type;
}
EXPORT_SYMBOL_GPL(hisi_get_charger_type);

static void notify_charger_type(struct hisi_dwc3_device *hisi_dwc3)
{
	atomic_notifier_call_chain(&hisi_dwc3->charger_type_notifier,
				hisi_dwc3->charger_type, hisi_dwc3);
}

static void set_vbus_power(struct hisi_dwc3_device *hisi_dwc3, unsigned int is_on)
{
	enum hisi_charger_type new;

	if (0 == is_on) {
		new = CHARGER_TYPE_NONE;
	} else {
		new = PLEASE_PROVIDE_POWER;
	}
	if (hisi_dwc3->charger_type != new) {
		usb_dbg("set port power %d\n", is_on);
		hisi_dwc3->charger_type = new;
		notify_charger_type(hisi_dwc3);
	}
}

static void hisi_dwc3_wake_lock(struct hisi_dwc3_device *hisi_dwc3)
{
	if (!wake_lock_active(&hisi_dwc3->wake_lock)) {
		usb_dbg("usb otg wake lock\n");
		wake_lock(&hisi_dwc3->wake_lock);
	}
}

static void hisi_dwc3_wake_unlock(struct hisi_dwc3_device *hisi_dwc3)
{
	if (wake_lock_active(&hisi_dwc3->wake_lock)) {
		usb_dbg("usb otg wake unlock\n");
		wake_unlock(&hisi_dwc3->wake_lock);
	}
}

static void event_work(struct work_struct *work)
{
	unsigned long flags;
	enum otg_dev_event_type event;
	struct hisi_dwc3_device *hisi_dwc = container_of(work,
				    struct hisi_dwc3_device, event_work);
	int ret;

	mutex_lock(&hisi_dwc->lock);

	usb_dbg("+\n");

	spin_lock_irqsave(&(hisi_dwc->event_lock), flags);
	event = hisi_dwc->event;
	spin_unlock_irqrestore(&(hisi_dwc->event_lock), flags);

	usb_dbg("event type: %d\n", event);

	switch (event) {
	case CHARGER_CONNECT_EVENT:
		if (USB_STATE_DEVICE == hisi_dwc->state) {
			usb_dbg("Already in device mode, do nothing\n");
		} else if (USB_STATE_OFF == hisi_dwc->state) {
			hisi_dwc->host_flag = 0;

			/* due to detect charger type, must resume hisi_dwc */
			ret = pm_runtime_get_sync(&hisi_dwc->pdev->dev);
			if (ret < 0) {
				usb_err("resume hisi_dwc failed (ret %d)\n", ret);
				goto error;
			}

			/* detect charger type */
			hisi_dwc->charger_type = detect_charger_type(hisi_dwc);
			notify_charger_type(hisi_dwc);

			/* do not start peripheral if real charger connected */
			if (hisi_dwc->charger_type != CHARGER_TYPE_DCP) {
				/* start peripheral */
				ret = dwc3_otg_work(dwc_otg_handler,
					    DWC3_OTG_EVT_VBUS_SET);
				if (ret) {
					pm_runtime_put(&hisi_dwc->pdev->dev);
					hisi_dwc3_wake_unlock(hisi_dwc);
					usb_err("start peripheral error\n");
					goto error;
				}
			} else {
				usb_dbg("a real charger connected\n");
			}

			hisi_dwc->state = USB_STATE_DEVICE;

			if ((hisi_dwc->charger_type == CHARGER_TYPE_DCP)
				    || (hisi_dwc->charger_type == CHARGER_TYPE_UNKNOWN))
				hisi_dwc3_wake_unlock(hisi_dwc);
			else
				hisi_dwc3_wake_lock(hisi_dwc);

			usb_dbg("hisi usb status: OFF -> DEVICE\n");
		} else if (USB_STATE_HOST == hisi_dwc->state) {
			usb_dbg("Charger connect intrrupt in HOST mode\n");
		}

		break;

	case CHARGER_DISCONNECT_EVENT:
		if (USB_STATE_OFF == hisi_dwc->state) {
			usb_dbg("Already in off mode, do nothing\n");
		} else if (USB_STATE_DEVICE == hisi_dwc->state) {

			/* peripheral not started, if real charger connected */
			if (hisi_dwc->charger_type != CHARGER_TYPE_DCP) {
				/* stop peripheral */
				ret = dwc3_otg_work(dwc_otg_handler, DWC3_OTG_EVT_VBUS_CLEAR);
				if (ret) {
					usb_err("stop peripheral error\n");
					goto error;
				}
			} else {
				usb_dbg("connected is a real charger\n");
				disable_vdp_src(hisi_dwc);
			}

			/* usb cable disconnect, notify no charger */
			hisi_dwc->charger_type = CHARGER_TYPE_NONE;
			notify_charger_type(hisi_dwc);

			hisi_dwc->state = USB_STATE_OFF;
			hisi_dwc3_wake_unlock(hisi_dwc);
			pm_runtime_put(&hisi_dwc->pdev->dev);

			usb_dbg("hisi usb status: DEVICE -> OFF\n");
		} else if (USB_STATE_HOST == hisi_dwc->state) {
			usb_dbg("Charger disconnect intrrupt in HOST mode\n");
		}

		break;

	case ID_FALL_EVENT:
		if (USB_STATE_OFF == hisi_dwc->state) {
			set_vbus_power(hisi_dwc, 1);

			hisi_dwc->host_flag = 1;

			/* start host */
			ret = dwc3_otg_work(dwc_otg_handler, DWC3_OTG_EVT_ID_CLEAR);
			if (ret) {
				usb_err("start host error\n");
				set_vbus_power(hisi_dwc, 0);
				goto error;
			}

			hisi_dwc->state = USB_STATE_HOST;
			hisi_dwc3_wake_lock(hisi_dwc);

			usb_dbg("hisi usb_status: OFF -> HOST\n");
		} else if (USB_STATE_DEVICE == hisi_dwc->state) {
			usb_dbg("id fall intrrupt in DEVICE mode\n");
		} else if (USB_STATE_HOST == hisi_dwc->state) {
			usb_dbg("Already in host mode, do nothing\n");
		}
		break;
	case ID_RISE_EVENT:
		if (USB_STATE_HOST == hisi_dwc->state) {
			set_vbus_power(hisi_dwc, 0);

			/* stop host */
			ret = dwc3_otg_work(dwc_otg_handler, DWC3_OTG_EVT_ID_SET);
			if (ret) {
				usb_err("stop host error\n");
				goto error;
			}

			hisi_dwc->state = USB_STATE_OFF;
			hisi_dwc3_wake_unlock(hisi_dwc);

			usb_dbg("hiusb_status: HOST -> OFF\n");
		} else if (USB_STATE_DEVICE == hisi_dwc->state) {
			usb_dbg("id rise intrrupt in DEVICE mode\n");
		} else if (USB_STATE_OFF == hisi_dwc->state) {
			usb_dbg("Already in host mode, do nothing\n");
		}

		break;
	default:
		usb_dbg("illegal event type!\n");
		break;
	}

error:
	usb_dbg("-\n");
	mutex_unlock(&hisi_dwc->lock);
	return;
}

static int event_check(enum otg_dev_event_type last_event,
		enum otg_dev_event_type new_event)
{
	int ret = 0;

	if (last_event == NONE_EVENT)
		return 1;

	switch (new_event) {
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
	int ret = 0;
#ifdef CONFIG_USB_DWC3_OTG
	unsigned long flags;
	struct hisi_dwc3_device *hisi_dwc3 = hisi_dwc3_dev;

	if (!hisi_dwc3)
		return -EBUSY;

	if (hisi_dwc3->eventmask) {
		usb_dbg("eventmask enabled, mask all events.\n");
		return ret;
	}

	spin_lock_irqsave(&(hisi_dwc3->event_lock), flags);

	if (event_check(hisi_dwc3->event, event)) {
		usb_dbg("event: %d\n", event);
		hisi_dwc3->event = event;

		if ((CHARGER_CONNECT_EVENT == event)
				|| (CHARGER_DISCONNECT_EVENT == event))
			hisi_dwc3_wake_lock(hisi_dwc3);

		ret = schedule_work(&hisi_dwc3->event_work);
	}
	spin_unlock_irqrestore(&(hisi_dwc3->event_lock), flags);
#endif
	return ret;
}
EXPORT_SYMBOL_GPL(hisi_usb_otg_event);

static void switch_off_abb_clk(struct hisi_dwc3_device *hisi_dwc3)
{
	void __iomem *pctrl_base = hisi_dwc3->pctrl_reg_base;
	uint32_t temp;

	temp = readl(pctrl_base + PCTRL_PERI_CTRL24);
	temp &= ~(1 << 24);
	writel(temp, pctrl_base + PCTRL_PERI_CTRL24);
}

static void switch_on_abb_clk(struct hisi_dwc3_device *hisi_dwc3)
{
	void __iomem *pctrl_base = hisi_dwc3->pctrl_reg_base;
	void __iomem *pericfg_base = hisi_dwc3->pericfg_reg_base;
	uint32_t temp;

	/* disable modem iso */
	temp = readl(pericfg_base + PERI_CRG_ISOSTAT);
	if (temp & PERI_CRG_ISOSTAT_MODEMSUBSYSISOEN) {
		writel(PERI_CRG_ISODIS_MODEMSUBSYSISOEN,
			pericfg_base + PERI_CRG_ISODIS);
	}

	/* config and switch on abb clk */
	temp = readl(pctrl_base + PCTRL_PERI_CTRL24);
	temp &= ~(1 << 28);
	temp &= ~(3 << 25);
	temp |= (2 << 25);
	temp |= (1 << 24);
	writel(temp, pctrl_base + PCTRL_PERI_CTRL24);
}

static int open_ldo(struct hisi_dwc3_device *hisi_dwc3)
{
	int ret;

	if (0 != hisi_dwc3->is_regu_on) {
		usb_dbg("ldo already opened!\n");
		return 0;
	}

	/*
	 * For power saving, set usbldo10 to normal mode if usb cable is connected,
	 * and set it to idle mode if usb cable is disconnected (it's in close_ldo).
	 * And it's only for non fpga board.
	 */
	if (hisi_dwc3->fpga_flag == 0) {
		ret = regulator_set_mode(hisi_dwc3->usbldo10_regu, REGULATOR_MODE_NORMAL);
		if (ret) {
			usb_err("set regulator usbldo10 normal failed (ret %d)\n", ret);
			return ret;
		}
	}

	ret = regulator_enable(hisi_dwc3->otgdebugsubsys_regu);
	if (ret) {
		usb_err("enable regulator otgdebugsubsys failed (ret %d)\n", ret);
		return ret;
	}

	hisi_dwc3->is_regu_on = 1;

	return 0;
}

static int close_ldo(struct hisi_dwc3_device *hisi_dwc3)
{
	int ret;

	if (0 == hisi_dwc3->is_regu_on) {
		usb_dbg("ldo already closed!\n");
		return 0;
	}

	ret = regulator_disable(hisi_dwc3->otgdebugsubsys_regu);
	if (ret) {
		usb_err("disable regulator otgdebugsubsys failed (ret %d)\n", ret);
		return ret;
	}

	if (hisi_dwc3->fpga_flag == 0) {
		ret = regulator_set_mode(hisi_dwc3->usbldo10_regu, REGULATOR_MODE_IDLE);
		if (ret) {
			usb_err("set regulator usbldo10 idle failed (ret %d)\n", ret);
			return ret;
		}
	}

	hisi_dwc3->is_regu_on = 0;

	return 0;
}

static int hisi_dwc3_setup(struct hisi_dwc3_device *hisi_dwc3)
{
	int ret;

	usb_dbg("+\n");

	ret = open_ldo(hisi_dwc3);
	if (ret)
		return ret;

	/* set usb aclk 240MHz, for improve performance */
	ret = clk_set_rate(hisi_dwc3->gt_aclk_usb3otg, 240000000);
	if (ret) {
		usb_err("clk_set_rate failed\n");
		return ret;
	}

	switch_on_abb_clk(hisi_dwc3);
	ret = clk_prepare_enable(hisi_dwc3->clk);
	if (ret) {
		usb_err("clk_prepare_enable failed\n");
		return ret;
	}

	dwc3_release(hisi_dwc3);

	atomic_set(&hisi_dwc3_power_on, 1);

	usb_dbg("-\n");

	return 0;
}

static int hisi_dwc3_shutdown(struct hisi_dwc3_device *hisi_dwc3)
{
	int ret;

	usb_dbg("+\n");

	atomic_set(&hisi_dwc3_power_on, 0);

	dwc3_reset(hisi_dwc3);

	switch_off_abb_clk(hisi_dwc3);
	clk_disable_unprepare(hisi_dwc3->clk);

	ret = close_ldo(hisi_dwc3);
	if (ret)
		return ret;

	usb_dbg("-\n");

	return 0;
}

/**
 * get_usb_state() - get current USB cable state.
 * @hisi_dwc: the instance pointer of struct hisi_dwc3_device
 *
 * return current USB cable state according to VBUS status and ID status.
 */
static enum hisi_usb_state get_usb_state(struct hisi_dwc3_device *hisi_dwc)
{
	if (hisi_dwc->fpga_flag) {
		usb_dbg("this is fpga platform, usb is device mode\n");
		return USB_STATE_DEVICE;
	}

	if (dwc3_otg_id_value(dwc_otg_handler) == 0)
		return USB_STATE_HOST;
	else if (hisi_usb_vbus_value() == 0)
		return USB_STATE_OFF;
	else
		return USB_STATE_DEVICE;
}

static void get_phy_param(struct hisi_dwc3_device *hisi_dwc3)
{
	struct device *dev = &hisi_dwc3->pdev->dev;

	/* hs phy param for device mode */
	if (of_property_read_u32(dev->of_node, "eye_diagram_param",
			&(hisi_dwc3->eye_diagram_param))) {
		usb_dbg("get eye diagram param form dt failed, use default value\n");
		hisi_dwc3->eye_diagram_param = 0x1c466e3;
	}
	usb_dbg("eye diagram param: 0x%x\n", hisi_dwc3->eye_diagram_param);

	/* hs phy param for host mode */
	if (of_property_read_u32(dev->of_node, "eye_diagram_host_param",
			&(hisi_dwc3->eye_diagram_host_param))) {
		usb_dbg("get eye diagram host param form dt failed, use default value\n");
		hisi_dwc3->eye_diagram_host_param = 0x1c466e3;
	}
	usb_dbg("eye diagram host param: 0x%x\n", hisi_dwc3->eye_diagram_host_param);

	/* ss phy Rx Equalization */
	if (of_property_read_u32(dev->of_node, "usb3_phy_cr_param",
			&(hisi_dwc3->usb3_phy_cr_param))) {
		usb_dbg("get usb3_phy_cr_param form dt failed, use default value\n");
		//hisi_dwc3->usb3_phy_cr_param = (0x17 << 7);
		hisi_dwc3->usb3_phy_cr_param = (1 << 11) | (3 << 8) | (1 << 7);
	}

	/* ss phy Rx Equalization for host mode */
	if (of_property_read_u32(dev->of_node, "usb3_phy_host_cr_param",
			&(hisi_dwc3->usb3_phy_host_cr_param))) {
		usb_dbg("get usb3_phy_host_cr_param form dt failed, use default value\n");
		hisi_dwc3->usb3_phy_host_cr_param = (1 << 11) | (1 << 8) | (1 << 7);
	}

	usb_dbg("usb3_phy_cr_param: 0x%x\n", hisi_dwc3->usb3_phy_cr_param);
	usb_dbg("usb3_phy_host_cr_param: 0x%x\n", hisi_dwc3->usb3_phy_host_cr_param);

	/* tx_vboost_lvl */
	if (of_property_read_u32(dev->of_node, "usb3_phy_tx_vboost_lvl",
			&(hisi_dwc3->usb3_phy_tx_vboost_lvl))) {
		usb_dbg("get usb3_phy_tx_vboost_lvl form dt failed, use default value\n");
		hisi_dwc3->usb3_phy_tx_vboost_lvl = 5;
	}
	usb_dbg("usb3_phy_tx_vboost_lvl: %d\n", hisi_dwc3->usb3_phy_tx_vboost_lvl);
}

/**
 * get_resource() - prepare resources
 * @hisi_dwc3: the instance pointer of struct hisi_dwc3_device
 *
 * 1. get registers base address and map registers region.
 * 2. get regulator handler.
 */
static int get_resource(struct hisi_dwc3_device *hisi_dwc3)
{
	struct device *dev = &hisi_dwc3->pdev->dev;
	struct resource *res;
	struct device_node *np;

	/*
	 * map PERI CRG region
	 */
	np = of_find_compatible_node(NULL, NULL, "hisilicon,crgctrl");
	if (!np) {
		dev_err(dev, "get peri cfg node failed!\n");
		return -EINVAL;
	}
	hisi_dwc3->pericfg_reg_base = of_iomap(np, 0);

	/*
	 * map PCTRL region
	 */
	np = of_find_compatible_node(NULL, NULL, "hisilicon,pctrl");
	if (!np) {
		dev_err(dev, "get pctrl node failed!\n");
		return -EINVAL;
	}
	hisi_dwc3->pctrl_reg_base = of_iomap(np, 0);

	/*
	 * map OTG BC region
	 */
	res = platform_get_resource(hisi_dwc3->pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "missing memory base resource\n");
		return -EINVAL;
	}

	hisi_dwc3->otg_bc_reg_base = devm_ioremap_nocache(dev, res->start, resource_size(res));
	if (IS_ERR_OR_NULL(hisi_dwc3->otg_bc_reg_base)) {
		dev_err(dev, "ioremap res 0 failed\n");
		return -ENOMEM;
	}

	/*
	 * get ldo handlers
	 */
	hisi_dwc3->otgdebugsubsys_regu = devm_regulator_get(&hisi_dwc3->pdev->dev, "otgdebugsubsys");
	if (IS_ERR(hisi_dwc3->otgdebugsubsys_regu)) {
		dev_err(dev, "couldn't get regulator otgdebugsubsys\n");
                return -EINVAL;
	}

	get_phy_param(hisi_dwc3);

	/* get abb clk handler */
	hisi_dwc3->clk = devm_clk_get(&hisi_dwc3->pdev->dev, "clk_abb_192");
	if (IS_ERR_OR_NULL(hisi_dwc3->clk)) {
		dev_err(dev, "get usb clk failed\n");
		return -EINVAL;
	}

	/* get h clk handler */
	hisi_dwc3->gt_aclk_usb3otg = devm_clk_get(&hisi_dwc3->pdev->dev, "aclk_usb3otg");
	if (IS_ERR_OR_NULL(hisi_dwc3->gt_aclk_usb3otg)) {
		dev_err(dev, "get aclk_usb3otg failed\n");
		return -EINVAL;
	}

	/* judge fpga platform or not, from dts */
	if (of_property_read_u32(dev->of_node, "fpga_flag",
			    &(hisi_dwc3->fpga_flag))) {
		hisi_dwc3->fpga_flag = 0;
	}
	usb_dbg("this is %s platform (fpga flag %d)\n",
		hisi_dwc3->fpga_flag ? "fpga" : "asic", hisi_dwc3->fpga_flag);

	if (hisi_dwc3->fpga_flag == 0) {
		hisi_dwc3->usbldo10_regu = devm_regulator_get(&hisi_dwc3->pdev->dev, "usbldo10");
		if (IS_ERR(hisi_dwc3->usbldo10_regu)) {
			dev_err(dev, "couldn't get regulator usbldo10\n");
			return -EINVAL;
		}
	}

	return 0;
}

static int hisi_dwc3_probe(struct platform_device *pdev)
{
	int ret;
	struct hisi_dwc3_device *hisi_dwc;
	struct device *dev = &pdev->dev;
	struct device_node *node = pdev->dev.of_node;
	enum hisi_usb_state init_state;

	usb_dbg("+\n");

	hisi_dwc = devm_kzalloc(dev, sizeof(*hisi_dwc), GFP_KERNEL);
	if (!hisi_dwc) {
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, hisi_dwc);
	hisi_dwc->pdev = pdev;

	hisi_dwc3_dev = hisi_dwc;

	/*
	 * set hisi dwc3 dma mask, it should be 0xffffffff, because the ahb
	 * master of usb can only support 32bit width address.
	 */
	if (!dev->dma_mask)
		dev->dma_mask = &dev->coherent_dma_mask;
	if (!dev->coherent_dma_mask)
		dev->coherent_dma_mask = DMA_BIT_MASK(32);

	/*
	 * get resources from dts.
	 */
	ret = get_resource(hisi_dwc);
	if (ret) {
		dev_err(&pdev->dev, "get resource failed!\n");
		return ret;
	}

	/* create sysfs files. */
	ret = create_attr_file(dev);
	if (ret) {
		dev_err(&pdev->dev, "create_attr_file failed!\n");
		return ret;
	}

	/* initialize */
	hisi_dwc->charger_type = CHARGER_TYPE_SDP;
	hisi_dwc->fake_charger_type = CHARGER_TYPE_NONE;
	hisi_dwc->event = NONE_EVENT;
	hisi_dwc->host_flag = 0;
	hisi_dwc->eventmask = 0;
	spin_lock_init(&hisi_dwc->event_lock);
	INIT_WORK(&hisi_dwc->event_work, event_work);
	mutex_init(&hisi_dwc->lock);
	wake_lock_init(&hisi_dwc->wake_lock, WAKE_LOCK_SUSPEND, "usb_wake_lock");
	ATOMIC_INIT_NOTIFIER_HEAD(&hisi_dwc->charger_type_notifier);

	/* power on */
	hisi_dwc->is_regu_on = 0;
	ret = hisi_dwc3_setup(hisi_dwc);
	if (ret) {
		dev_err(&pdev->dev, "%s: hisi_dwc3_setup failed!\n", __func__);
		return ret;
	}

	/* if vbus is on, detect charger type */
	if (hisi_usb_vbus_value()) {
		hisi_dwc->charger_type = detect_charger_type(hisi_dwc);
		notify_charger_type(hisi_dwc);
	}

	/*
	 * enable runtime pm.
	 */
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);
	pm_runtime_get_sync(dev);
	pm_runtime_forbid(dev);

	/*
	 * probe child deivces
	 */
	ret = of_platform_populate(node, NULL, NULL, dev);
	if (ret) {
		printk(KERN_ERR "%s: register dwc3 failed!\n", __func__);
		goto err1;
	}

#ifdef CONFIG_USB_DWC3_OTG
	/* default device state  */
	hisi_dwc->state = USB_STATE_DEVICE;

	if ((hisi_dwc->charger_type == CHARGER_TYPE_DCP)
		    || (hisi_dwc->charger_type == CHARGER_TYPE_UNKNOWN))
		hisi_dwc3_wake_unlock(hisi_dwc);
	else
		hisi_dwc3_wake_lock(hisi_dwc);

	if (hisi_dwc->charger_type == CHARGER_TYPE_DCP) {
		/* stop peripheral */
		ret = dwc3_otg_work(dwc_otg_handler, DWC3_OTG_EVT_VBUS_CLEAR);
		if (ret) {
			usb_err("stop peripheral error\n");
		}
	}

	/* balance the put operation when disconnect */
	pm_runtime_get(dev);

	hisi_dwc->event = CHARGER_CONNECT_EVENT;
	init_state = get_usb_state(hisi_dwc);
	if (init_state == USB_STATE_OFF) {
		usb_dbg("init state: OFF\n");
		hisi_usb_otg_event(CHARGER_DISCONNECT_EVENT);
	} else if (init_state == USB_STATE_HOST) {
		usb_dbg("init state: HOST\n");
		hisi_usb_otg_event(CHARGER_DISCONNECT_EVENT);
		msleep(500);
		hisi_usb_otg_event(ID_FALL_EVENT);
	}
#endif

	pm_runtime_put_sync(dev);
	pm_runtime_allow(dev);

	usb_dbg("-\n");

	return 0;

err1:
	pm_runtime_put_sync(dev);
	pm_runtime_disable(dev);

	return ret;
}

static int hisi_dwc3_remove_child(struct device *dev, void *unused)
{
	struct platform_device *pdev = to_platform_device(dev);
	platform_device_unregister(pdev);
	return 0;
}

static int hisi_dwc3_remove(struct platform_device *pdev)
{
	struct hisi_dwc3_device *hisi_dwc3 = platform_get_drvdata(pdev);
	int ret;

	if (!hisi_dwc3) {
		usb_err("hisi_dwc3 NULL\n");
		return -EBUSY;
	}

	device_for_each_child(&pdev->dev, NULL, hisi_dwc3_remove_child);
	pm_runtime_disable(&pdev->dev);
	ret = hisi_dwc3_shutdown(hisi_dwc3);
	if (ret) {
		usb_err("hisi_dwc3_shutdown error\n");
	}
	return 0;
}

#ifdef CONFIG_PM_SLEEP

static int hisi_dwc3_prepare(struct device *dev)
{
	struct hisi_dwc3_device *hisi_dwc = platform_get_drvdata(
				to_platform_device(dev));
	int ret = 0;

	if (!hisi_dwc)
		return -ENODEV;

	mutex_lock(&hisi_dwc->lock);

	switch (hisi_dwc->state) {
	case USB_STATE_OFF:
		pr_info("%s: off state.\n", __func__);
		break;
	case USB_STATE_DEVICE:
		pr_info("%s: device state.\n", __func__);

		if (hisi_dwc->charger_type != CHARGER_TYPE_DCP) {
			/* stop peripheral */
			ret = dwc3_otg_work(dwc_otg_handler, DWC3_OTG_EVT_VBUS_CLEAR);
			if (ret) {
				usb_err("stop peripheral error\n");
				goto error;
			}
		} else {
			usb_dbg("connected is a real charger\n");
			disable_vdp_src(hisi_dwc);
		}

		break;
	case USB_STATE_HOST:
		usb_err("%s: host mode, should not go to sleep!\n", __func__);
		ret = -EFAULT;
		goto error;
		break;
	default:
		pr_err("%s: ilegal state!\n", __func__);
		ret = -EFAULT;
		goto error;
		break;
	}

	return ret;
error:
	mutex_unlock(&hisi_dwc->lock);
	return ret;
}

static void hisi_dwc3_complete(struct device *dev)
{
	struct hisi_dwc3_device *hisi_dwc = platform_get_drvdata(
				to_platform_device(dev));
	int ret = 0;

	if (!hisi_dwc) {
		usb_err("hisi_dwc NULL !\n");
		return;
	}

	switch (hisi_dwc->state) {
	case USB_STATE_OFF:
		usb_dbg("%s: off state.\n", __func__);
		break;
	case USB_STATE_DEVICE:
		usb_dbg("%s: device state.\n", __func__);

		/* update charger type */
		hisi_dwc->charger_type = detect_charger_type(hisi_dwc);

		/* do not start peripheral if real charger connected */
		if (hisi_dwc->charger_type != CHARGER_TYPE_DCP) {
			/* start peripheral */
			ret = dwc3_otg_work(dwc_otg_handler, DWC3_OTG_EVT_VBUS_SET);
			if (ret) {
				usb_err("start peripheral error\n");
				hisi_dwc->state = USB_STATE_OFF;
				pm_runtime_put(&hisi_dwc->pdev->dev);
				goto error;
			}
		} else {
			usb_dbg("a real charger connected\n");
		}

		break;
	case USB_STATE_HOST:
		usb_err("%s: host mode, should not go to sleep!\n", __func__);
		break;
	default:
		usb_err("%s: ilegal state!\n", __func__);
		break;
	}

error:
	mutex_unlock(&hisi_dwc->lock);
}

static int hisi_dwc3_suspend(struct device *dev)
{
	struct hisi_dwc3_device *hisi_dwc3 = platform_get_drvdata(to_platform_device(dev));
	int ret = 0;

	usb_dbg("+\n");

	if (!hisi_dwc3) {
		usb_err("hisi_dwc3 NULL\n");
		return -EBUSY;
	}

	if (hisi_dwc3->runtime_suspended) {
		usb_dbg("runtime_suspended\n");
	} else {
		ret = hisi_dwc3_shutdown(hisi_dwc3);
		if (ret)
			usb_err("hisi_dwc3_shutdown failed\n");
	}

	usb_dbg("-\n");

	return ret;
}

static int hisi_dwc3_resume(struct device *dev)
{
	struct hisi_dwc3_device *hisi_dwc3 = platform_get_drvdata(to_platform_device(dev));
	int ret = 0;

	usb_dbg("+\n");

	if (!hisi_dwc3) {
		usb_err("hisi_dwc3 NULL\n");
		return -EBUSY;
	}

	if (hisi_dwc3->runtime_suspended) {
		usb_dbg("runtime_suspended\n");
	} else {
		ret = hisi_dwc3_setup(hisi_dwc3);
		if (ret)
			usb_err("hisi_dwc3_setup failed\n");

		pm_runtime_disable(dev);
		pm_runtime_set_active(dev);
		pm_runtime_enable(dev);
	}

	usb_dbg("-\n");

	return ret;
}
#endif

#ifdef CONFIG_PM_RUNTIME
static int hisi_dwc3_runtime_suspend(struct device *dev)
{
	int ret;
	struct hisi_dwc3_device *hisi_dwc3 = platform_get_drvdata(to_platform_device(dev));

	usb_dbg("+\n");

	if (!hisi_dwc3) {
		usb_err("hisi_dwc3 NULL\n");
		return -EBUSY;
	}

	ret = hisi_dwc3_shutdown(hisi_dwc3);
	if (ret) {
		return ret;
	}
	hisi_dwc3->runtime_suspended = 1;
	usb_dbg("-\n");

	return 0;
}

static int hisi_dwc3_runtime_resume(struct device *dev)
{
	int ret = 0;
	struct hisi_dwc3_device *hisi_dwc3 = platform_get_drvdata(to_platform_device(dev));

	usb_dbg("+\n");

	if (!hisi_dwc3) {
		usb_err("hisi_dwc3 NULL\n");
		return -EBUSY;
	}

	ret = hisi_dwc3_setup(hisi_dwc3);
	if (ret) {
		return ret;
	}
	hisi_dwc3->runtime_suspended = 0;
	usb_dbg("-\n");

	return ret;
}

static int hisi_dwc3_runtime_idle(struct device *dev)
{
	int ret;

	usb_dbg("+\n");
	ret = pm_runtime_autosuspend(dev);
	if (ret)
		dev_err(dev, "pm_runtime_autosuspend error\n");
	usb_dbg("-\n");

	return ret;
}
#endif /* CONFIG_PM_RUNTIME */

static const struct dev_pm_ops hisi_dwc3_dev_pm_ops = {
	.prepare	= hisi_dwc3_prepare,
	.complete	= hisi_dwc3_complete,
	SET_SYSTEM_SLEEP_PM_OPS(hisi_dwc3_suspend, hisi_dwc3_resume)
	SET_RUNTIME_PM_OPS(hisi_dwc3_runtime_suspend, hisi_dwc3_runtime_resume,
			hisi_dwc3_runtime_idle)
};

#ifdef CONFIG_OF
static const struct of_device_id hisi_dwc3_match[] = {
	{ .compatible = "hisilicon,hi3650-dwc3" },
	{},
};
MODULE_DEVICE_TABLE(of, hisi_dwc3_match);
#else
#define hisi_dwc3_match NULL
#endif

static struct platform_driver hisi_dwc3_driver = {
	.probe		= hisi_dwc3_probe,
	.remove		= hisi_dwc3_remove,
	.driver		= {
		.name	= "hisi-usb3",
		.of_match_table = of_match_ptr(hisi_dwc3_match),
		.pm	= &hisi_dwc3_dev_pm_ops,
	},
};
module_platform_driver(hisi_dwc3_driver);
MODULE_LICENSE("GPL");
