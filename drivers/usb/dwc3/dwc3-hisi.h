
#ifndef _DWC3_HISI_H_
#define _DWC3_HISI_H_

#define REG_BASE_PERI_CRG                		(0xFFF35000)
#define PERI_CRG_CLK_EN4				(0x40)
#define PERI_CRG_CLK_DIS4				(0x44)
#define PERI_CRG_RSTDIS4                   		(0x94)
#define PERI_CRG_RSTEN4                     		(0x90)
#define PERI_CRG_ISODIS                     		(0x148)
#define PERI_CRG_ISOSTAT				(0x14C)
#define STCL_ADDR					(0xFFF0A214)

#define PERI_CRG_ISOSTAT_MODEMSUBSYSISOEN		(1 << 4)
#define PERI_CRG_ISODIS_MODEMSUBSYSISOEN		(1 << 4)

#define PCTRL_PERI_CTRL24				(0x64)

#define IP_RST_USB3OTG_MUX				(1 << 8)
#define IP_RST_USB3OTG_AHBIF				(1 << 7)
#define IP_RST_USB3OTG_32K				(1 << 6)
#define IP_RST_USB3OTG					(1 << 5)
#define IP_RST_USB3OTGPHY_POR				(1 << 3)

#define GT_CLK_USB3OTG_REF				(1 << 0)
#define GT_ACLK_USB3OTG					(1 << 1)
#define GT_CLK_USB3PHY_REF				(1 << 2)

/*
 * hisi dwc3 otg bc registers
 */
#define USBOTG3_CTRL0		0x00		/* ѡ����ƼĴ���0 */
#define USBOTG3_CTRL1		0x04		/* ѡ����ƼĴ���1 */
#define USBOTG3_CTRL2		0x08		/* ѡ����ƼĴ���2 */
#define USBOTG3_CTRL3		0x0C		/* ѡ����ƼĴ���3 */
#define USBOTG3_CTRL4		0x10		/* ѡ����ƼĴ���4 */
#define USBOTG3_CTRL5		0x14		/* ѡ����ƼĴ���5 */
#define USBOTG3_CTRL6		0x18		/* ѡ����ƼĴ���6 */
#define USBOTG3_CTRL7		0x1C		/* ѡ����ƼĴ���7 */
#define USBOTG3_STS0		0x20		/* ״̬�Ĵ���0 */
#define USBOTG3_STS1		0x24		/* ״̬�Ĵ���1 */
#define USBOTG3_STS2		0x28		/* ״̬�Ĵ���2 */
#define USBOTG3_STS3		0x2C		/* ״̬�Ĵ���3 */
#define BC_CTRL0		0x30		/* BC�������Ĵ���0 */
#define BC_CTRL1		0x34		/* BC�������Ĵ���1 */
#define BC_CTRL2		0x38		/* BC�������Ĵ���2 */
#define BC_STS0			0x3C		/* BC״̬�Ĵ���0 */
#define RAM_CTRL		0x40		/* RAM���ƼĴ��� */
#define USBOTG3_STS4		0x44		/* ״̬�Ĵ���4 */
#define USB3PHY_CTRL		0x48		/* PHY���ƼĴ��� */
#define USB3PHY_STS		0x4C		/* PHY״̬�Ĵ��� */
#define USB3PHY_CR_STS		0x50		/* PHY�ڲ��Ĵ���״̬ */
#define USB3PHY_CR_CTRL		0x54		/* PHY�ڲ��Ĵ������� */
#define USB3_RES		0x58		/* USBԤ���Ĵ��� */

/* USTOTG3_CTRL0 */
# define USBOTG3CTRL0_SESSVLD_SEL              (1 << 14)
# define USBOTG3CTRL0_SC_SESSVLD               (1 << 13)
# define USBOTG3CTRL0_POWERPRESENT_SEL         (1 << 12)
# define USBOTG3CTRL0_SC_POWERPRESENT          (1 << 11)
# define USBOTG3CTRL0_BVALID_SEL               (1 << 10)
# define USBOTG3CTRL0_SC_BVALID                (1 << 9)
# define USBOTG3CTRL0_AVALID_SEL               (1 << 8)
# define USBOTG3CTRL0_SC_AVALID                (1 << 7)
# define USBOTG3CTRL0_VBUSVALID_SEL            (1 << 6)
# define USBOTG3CTRL0_DRVVBUS                  (1 << 5)
# define USBOTG3CTRL0_DRVVBUS_SEL              (1 << 4)
# define USBOTG3CTRL0_IDDIG                    (1 << 3)
# define USBOTG3CTRL0_IDDIG_SEL                (1 << 2)
# define USBOTG3CTRL0_IDPULLUP                 (1 << 1)
# define USBOTG3CTRL0_IDPULLUP_SEL             (1 << 0)

/* USTOTG3_CTRL2 */
# define USBOTG3CTRL2_POWERDOWN_HSP             (1 << 0)
# define USBOTG3CTRL2_POWERDOWN_SSP             (1 << 1)

/* USBOTG3_CTRL3 */
# define USBOTG3_CTRL3_VBUSVLDEXT	(1 << 6)
# define USBOTG3_CTRL3_VBUSVLDEXTSEL	(1 << 5)
# define USBOTG3_CTRL3_TXBITSTUFFEHN	(1 << 4)
# define USBOTG3_CTRL3_TXBITSTUFFEN	(1 << 3)
# define USBOTG3_CTRL3_RETENABLEN	(1 << 2)
# define USBOTG3_CTRL3_OTGDISABLE	(1 << 1)
# define USBOTG3_CTRL3_COMMONONN	(1 << 0)

/* USBOTG3_CTRL4 */
# define USBOTG3_CTRL4_TXVREFTUNE(x)            (((x) << 22) & (0xf << 22))
# define USBOTG3_CTRL4_TXRISETUNE(x)            (((x) << 20) & (3 << 20))
# define USBOTG3_CTRL4_TXRESTUNE(x)             (((x) << 18) & (3 << 18))
# define USBOTG3_CTRL4_TXPREEMPPULSETUNE        (1 << 17)
# define USBOTG3_CTRL4_TXPREEMPAMPTUNE(x)       (((x) << 15) & (3 << 15))
# define USBOTG3_CTRL4_TXHSXVTUNE(x)            (((x) << 13) & (3 << 13))
# define USBOTG3_CTRL4_TXFSLSTUNE(x)            (((x) << 9) & (0xf << 9))
# define USBOTG3_CTRL4_SQRXTUNE(x)              (((x) << 6) & (7 << 6))
# define USBOTG3_CTRL4_OTGTUNE_MASK             (7 << 3)
# define USBOTG3_CTRL4_OTGTUNE(x)               (((x) << 3) & USBOTG3_CTRL4_OTGTUNE_MASK)
# define USBOTG3_CTRL4_COMPDISTUNE_MASK         7
# define USBOTG3_CTRL4_COMPDISTUNE(x)           ((x) & USBOTG3_CTRL4_COMPDISTUNE_MASK)

/* USBOTG3_CTRL6 */
#define TX_VBOOST_LVL_MASK			7
#define TX_VBOOST_LVL(x)			((x) & TX_VBOOST_LVL_MASK)

/* BC_CTRL0 */
# define BC_CTRL0_BC_IDPULLUP		(1 << 10)
# define BC_CTRL0_BC_SUSPEND_N		(1 << 9)
# define BC_CTRL0_BC_DMPULLDOWN		(1 << 8)
# define BC_CTRL0_BC_DPPULLDOWN		(1 << 7)
# define BC_CTRL0_BC_TXVALIDH		(1 << 6)
# define BC_CTRL0_BC_TXVALID		(1 << 5)
# define BC_CTRL0_BC_TERMSELECT		(1 << 4)
# define BC_CTRL0_BC_XCVRSELECT(x)	((x) << 2) & (3 << 2)
# define BC_CTRL0_BC_OPMODE(x)		((x) & 3)

/* BC_CTRL1 */
# define BC_CTRL1_BC_MODE	1

/* BC_CTRL2 */
# define BC_CTRL2_BC_PHY_VDATDETENB	(1 << 4)
# define BC_CTRL2_BC_PHY_VDATARCENB	(1 << 3)
# define BC_CTRL2_BC_PHY_CHRGSEL		(1 << 2)
# define BC_CTRL2_BC_PHY_DCDENB		(1 << 1)
# define BC_CTRL2_BC_PHY_ACAENB		(1 << 0)

/* BC_STS0 */
# define BC_STS0_BC_LINESTATE(x)	(((x) << 9) & (3 << 9))
# define BC_STS0_BC_PHY_CHGDET		(1 << 8)
# define BC_STS0_BC_PHY_FSVMINUS	(1 << 7)
# define BC_STS0_BC_PHY_FSVPLUS		(1 << 6)
# define BC_STS0_BC_RID_GND		(1 << 5)
# define BC_STS0_BC_RID_FLOAT		(1 << 4)
# define BC_STS0_BC_RID_C		(1 << 3)
# define BC_STS0_BC_RID_B		(1 << 2)
# define BC_STS0_BC_RID_A		(1 << 1)
# define BC_STS0_BC_SESSVLD		(1 << 0)

/* USB3PHY_CR_STS */
#define USB3OTG_PHY_CR_DATA_OUT(x)	(((x) >> 1) & 0xffff)
#define USB3OTG_PHY_CR_ACK		(1 << 0)

/* USB3PHY_CR_CTRL */
#define USB3OTG_PHY_CR_DATA_IN(x)	(((x) << 4) & (0xffff << 4))
#define USB3OTG_PHY_CR_WRITE		(1 << 3)
#define USB3OTG_PHY_CR_READ		(1 << 2)
#define USB3OTG_PHY_CR_CAP_DATA		(1 << 1)
#define USB3OTG_PHY_CR_CAP_ADDR		(1 << 0)

#endif /* _DWC3_HISI_H_ */
