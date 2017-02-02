#ifndef _ARCH_ARM_MACH_HISI_DISRESET_H_
#define _ARCH_ARM_MACH_HISI_DISRESET_H_

#define SELECT_CLUSTER_A7			0x0
#define SELECT_CLUSTER_A15			0x1

#define REG_BASE_CRGPERI_PHY         (0xFFF35000)

#define REG_BASE_SYSCTRL_PHY         (0xFFF0A000)

#define REG_BASE_PMCCTRL_PHY         (0xFFF31000)

#define REG_BASE_VIVOBUS_PHY         (0xE86D0000)

#define ISP_RD_QOS_PRIORITY          (0x8)
#define ISP_RD_QOS_MODE              (0xC)
#define ISP_WR_QOS_PRIORITY          (0x88)
#define ISP_WR_QOS_MODE              (0x8C)
#define A7T0VIVOBUS_RD_QOS_PRIORITY  (0x108)
#define A7T0VIVOBUS_RD_QOS_MODE      (0x10C)
#define A7T0VIVOBUS_WR_QOS_PRIORITY  (0x188)
#define A7T0VIVOBUS_WR_QOS_MODE      (0x18C)

#define QOS_FIX_MODE 0x0
#define QOS_BYPASS_MODE 0x2
#define QOS_PRIO_1 0x0
#define QOS_PRIO_2 0x101
#define QOS_PRIO_3 0x202
#define QOS_PRIO_4 0x303

#define CRG_PERIPHPER_BASE                      (0x000)
#define CRG_PERIPHPEREN0                        (CRG_PERIPHPER_BASE + 0x000)
#define CRG_PERIPHPEREN1                        (CRG_PERIPHPER_BASE + 0x010)
#define CRG_PERIPHPEREN2                        (CRG_PERIPHPER_BASE + 0x020)
#define CRG_PERIPHPEREN3                        (CRG_PERIPHPER_BASE + 0x030)
#define CRG_PERIPHPERDIS3                       (CRG_PERIPHPER_BASE + 0x034)
#define CRG_PERIPHPERCLKEN3                     (CRG_PERIPHPER_BASE + 0x038)
#define CRG_PERIPHPEREN4                        (CRG_PERIPHPER_BASE + 0x040)
#define CRG_PERIPHPEREN5                        (CRG_PERIPHPER_BASE + 0x050)
#define CRG_PERIPHPERDIS5                       (CRG_PERIPHPER_BASE + 0x054)
#define CRG_PERIPHPERCLKEN5                     (CRG_PERIPHPER_BASE + 0x058)
#define CRG_PERIPHCLKDIV24                      (CRG_PERIPHPER_BASE + 0x108)



#define SCTRLSCPER_BASE                       (0x000)
#define SCTRLSCPEREN0                         (SCTRLSCPER_BASE + 0x30)
#define SCTRLSCPEREN1                         (SCTRLSCPER_BASE + 0x40)

#define CRG_PERIPHPERRST_BASE               (0x060)
#define CRG_PERIPHPERRSTDIS0                (CRG_PERIPHPERRST_BASE + 0x04)
#define CRG_PERIPHPERRSTDIS1                (CRG_PERIPHPERRST_BASE + 0x10)
#define CRG_PERIPHPERRSTDIS2                (CRG_PERIPHPERRST_BASE + 0x1C)
#define CRG_PERIPHPERRSTDIS3                (CRG_PERIPHPERRST_BASE + 0x28)
#define CRG_PERIPHPERRSTDIS4                (CRG_PERIPHPERRST_BASE + 0x34)
#define CRG_PERIPHPERRSTDIS5                (CRG_PERIPHPERRST_BASE + 0x40)

#define SCTRLSCPERRST_BASE                  (0x080)
#define SCTRLSCPERRSTDIS0                   (SCTRLSCPERRST_BASE + 0x04)
#define SCTRLSCPERRSTDIS1                   (SCTRLSCPERRST_BASE + 0x10)

#define SCTRLSCCLKDIV_BASE                  (0x100)
#define SCTRLSCCLKDIV2                      (SCTRLSCCLKDIV_BASE + 0x08)

#define CRG_PERIPHCLKDIV_BASE               (0x0A8)
#define CRG_PERIPHCLKDIV16                  (CRG_PERIPHCLKDIV_BASE + 0x40)
#define CRG_PERIPHCLKDIV18                  (CRG_PERIPHCLKDIV_BASE + 0x48)
#define CRG_PERIPHCLKDIV20                  (CRG_PERIPHCLKDIV_BASE + 0x50)

#define CRGPERI_A7_BASE                 (0x340)
#define CRGPERI_A7_CLKEN                (CRGPERI_A7_BASE + 0x00)
#define CRGPERI_A7_RSTEN                (CRGPERI_A7_BASE + 0x04)
#define CRGPERI_A7_RSTDIS               (CRGPERI_A7_BASE + 0x08)
#define CRGPERI_A7_RSTSTAT              (CRGPERI_A7_BASE + 0x0C)
#define CRGPERI_A7_STAT                 (CRGPERI_A7_BASE + 0x14)
#define CRGPERI_ISP_SEC_RSTEN           (CRGPERI_A7_BASE + 0x940)
#define CRGPERI_A7_SEC_RSTDIS           (CRGPERI_A7_BASE + 0x944)
#define CRGPERI_A7_SEC_RSTSTAT          (CRGPERI_A7_BASE + 0x948)

#define TIMEOUT_4_NOCIDLE           (4000)
#define NOC_POWER_IDLEREQ           (0x380)
#define NOC_POWER_IDLEACK           (0x384)
#define NOC_POWER_IDLE              (0x388)

#define REG_BASE_TZPC_PHY        (0xE8A21000)
#define DECPROT0SET              (0x804)
#define DECPROT4SET              (0x834)
#define DECPROT5SET              (0x840)
#define REG_BASE_GIC_PHY         (0xE82B1000)
#define GIC_A7_1                 (0x834)
#define GIC_A7_2                 (0x850)

#define CRGPERI_ISPA7_CTRL_BASE            0xC90
#define ISPA7_DBGPWRDUP                    (0x1 << 2)
#define ISPA7_VINITHI_HIGH                 (0x1 << 1)
#define ISPA7_REMAP_ENABLE                 (0x1 << 11)
#define ISPA7_REMAP_OFFSET(BASE)           ((BASE) << 16)

#define CRGPERI_PERPWREN                 (0x150)
#define CRGPERI_ISODIS                   (0x148)
#define CRGPERI_ISOEN                    (0x144)
#define CRGPERI_PERPWRDIS                (0x154)
#define CRGPERI_PERPWRSTAT               (0x158)

#define CLK_ISP_SNCLK_DIV                   (0x1 << 3)
#define CLK_ISP_SNCLK_EN                    (0x1 << 2)




#endif /*_ARCH_ARM_MACH_HISI_DISRESET_H_*/
