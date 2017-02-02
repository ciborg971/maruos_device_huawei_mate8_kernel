/*
 * Device driver for PMU DRIVER
 *
 * Copyright (c) 2011 Hisilicon Co. Ltd
 *
 */
#include "hisi_pmic_mntn_inner.h"

#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>

static struct dsm_dev dsm_pmic_ocp = {
      .name = "dsm_pmu_ocp",
      .device_name = NULL,
      .ic_name = NULL,
      .module_name = NULL,
      .fops = NULL,
      .buff_size = 1024,
};

#define HISI_PMIC_OCP_MASK_STATE 0xFF

const char *pmic_ocp_name1[] = {
      [7] = "ocpbuck0",     [15] = "ocpldo3",   [23] = "ocpldo12",    [31] = "ocpldo21",
      [6] = "ocpbuck1",     [14] = "ocpldo4",   [22] = "ocpldo13",    [30] = "ocpldo22",
      [5] = "ocpbuck2",     [13] = "ocpldo5",   [21] = "ocpldo14",    [29] = "ocpldo23",
      [4] = "ocpbuck3",     [12] = "ocpldo7",   [20] = "ocpldo15",    [28] = "ocpldo24",
      [3] = "ocpbuck4",     [11] = "ocpldo8",   [19] = "ocpldo16",    [27] = "ocpldo25",
      [2] = "ocpldo0",       [10] = "ocpldo9",   [18] = "ocpldo17",    [26] = "ocpldo26",
      [1] = "ocpldo1",       [9]  = "ocpldo10",  [17] = "ocpldo19",    [25] = "ocpldo27",
      [0] = "ocpldo2",       [8]  = "ocpldo11",  [16] = "ocpldo20",    [24] = "ocpldo28",
};
const char *pmic_ocp_name2[] = {
      [7] = "ocpldo29",       [15] = "reserved_scp",
      [6] = "ocpldo30",       [14] = "reserved_scp",
      [5] = "ocpldo31",       [13] = "reserved_scp",
      [4] = "ocpldo32",       [12] = "buck0_scp",
      [3] = "ocp_reserved", [11] = "buck1_scp",
      [2] = "ocp_reserved", [10] = "buck2_scp",
      [1] = "ocp_reserved", [9]  = "buck3_scp",
      [0] = "classd_ocp",    [8]  = "buck4_scp",
};

static struct dsm_client *pmic_ocp_dclient = NULL;
#endif

static PMIC_MNTN_DESC *g_pmic_mntn = NULL;


static void hisi_pmic_panic_handler(void)
{
#ifdef CONFIG_HISI_BB
    rdr_syserr_process_for_ap(MODID_AP_S_PMU, 0, 0);
#else
    machine_restart("AP_S_PMU");
#endif
    return;
}

static int hisi_pmic_sdcard_ocp_handler(char *power_name)
{
    static struct regulator *power_sd = NULL;
    static struct regulator *power_sdio = NULL;
    int ret = 0;

    if (NULL == power_sd) {
        power_sd = regulator_get(NULL, SUPPLY_SD);
        if (IS_ERR(power_sd)) {
            pr_err("[%s]sd regulator found.\n", __func__);
            return ENODEV;
        }
    }
    if (IS_ERR(power_sd)) {
        pr_err("[%s]sd regulator found.\n", __func__);
        return ENODEV;
    }
    ret = regulator_force_disable(power_sd);
    if (ret) {
        pr_err("[%s]disable sd regulator error.\n", __func__);
        return ret;
    }

    if (NULL == power_sdio) {
        power_sdio = regulator_get(NULL, SUPPLY_SD_IO);
        if (IS_ERR(power_sdio)) {
            pr_err("[%s]sdio regulator found.\n", __func__);
            return ENODEV;
        }
    }
    if (IS_ERR(power_sdio)) {
            pr_err("[%s]sdio regulator found.\n", __func__);
        return ENODEV;
    }
    ret = regulator_force_disable(power_sdio);
    if (ret) {
        pr_err("[%s]disable sdio regulator error.\n", __func__);
        return ret;
    }

    return ret;
}

int hisi_pmic_special_ocp_register(char *power_name, pmic_ocp_callback handler)
{
    PMIC_MNTN_DESC *pmic_mntn = g_pmic_mntn;
    struct special_ocp_attr *head, *cur;

    if (!pmic_mntn) {
        pr_err("[%s]pmic mntn is null.\n", __func__);
        return -EPERM;
    }
    if (!power_name) {
        pr_err("[%s]power_name is null.\n", __func__);
        return -EPERM;
    }
    if (!handler) {
        pr_err("[%s]handler is null.\n", __func__);
        return -EPERM;
    }

    head = pmic_mntn->ocp_list_head;
    cur  = pmic_mntn->ocp_list_tail;
    if(!head)
    {
        head = kzalloc(sizeof(struct special_ocp_attr), GFP_KERNEL);
		if (!head) {
			pr_err("[%s]head kzalloc is null.\n", __func__);
			return -ENOMEM;
		}
        cur  = head;
        pmic_mntn->ocp_list_head = head;
    }
    else
    {
        cur->next = kzalloc(sizeof(struct special_ocp_attr), GFP_KERNEL);
		if (!cur->next) {
			pr_err("[%s]cur->next kzalloc is null.\n", __func__);
			return -ENOMEM;
		}
        cur = cur->next;
    }
    pmic_mntn->ocp_list_tail = cur;

    cur->power_name = power_name;
    cur->handler = handler;

    pr_info("[%s]%s registered\n", __func__, power_name);

    return 0;
}
EXPORT_SYMBOL(hisi_pmic_special_ocp_register);

static int hisi_pmic_register_special_ocp(void)
{
    int ret = 0;

    if (!check_himntn(HIMNTN_SD2JTAG) && !check_himntn(HIMNTN_SD2DJTAG)) {
        ret = hisi_pmic_special_ocp_register(SUPPLY_SD, hisi_pmic_sdcard_ocp_handler);
        if (ret) {
            pr_err("[%s]supply_sd register error.\n", __func__);
            return ret;
        }

        ret = hisi_pmic_special_ocp_register(SUPPLY_SD_IO, hisi_pmic_sdcard_ocp_handler);
        if (ret) {
            pr_err("[%s]supply_sd_io register error.\n", __func__);
            return ret;
        }
    }

    return ret;
}

static int hisi_pmic_ocp_special_handler(char *power_name, PMIC_MNTN_DESC *pmic_mntn)
{
    struct special_ocp_attr *cur = pmic_mntn->ocp_list_head;
    int ret;

    if (!cur) {
        pr_err("[%s]no power registered.\n", __func__);
        return PMIC_OCP_NONE;
    }

    do {
        if (!strcmp(cur->power_name, power_name)) {
            ret = cur->handler(power_name);
            if (ret) {
                return PMIC_OCP_NONE;
            } else {
                return PMIC_OCP_HANDLED;
            }
        }
        cur = cur->next;
    } while (cur);

    return PMIC_OCP_NONE;
}

static void get_pmu_register_info(void)
{
	int i;

	/*PMU CTRL*/
	for (i = 0; i <= 279; i++){
		pr_err("addr[0x%x] = value[0x%x]\n", i, hisi_pmic_reg_read(i));
	}
	/*PMU IRQ*/
	for (i = 282; i <= 299; i++){
		pr_err("addr[0x%x] = value[0x%x]\n", i, hisi_pmic_reg_read(i));
	}
	/*PMU RTC*/
	for (i = 300; i <= 325; i++){
		pr_err("addr[0x%x] = value[0x%x]\n", i, hisi_pmic_reg_read(i));
	}
	/*PMU COUL*/
	for (i = 331; i <= 440; i++){
		pr_err("addr[0x%x] = value[0x%x]\n", i, hisi_pmic_reg_read(i));
	}
	return;
}
static void get_pmu_key_register_info(PMIC_MNTN_DESC *pmic_mntn)
{
	int i;

	for( i = 0; i < pmic_mntn->pmu_record_reg_n; i++) {
		pr_err("[%s]addr[0x%x] = value[0x%x]\n", __func__, pmic_mntn->pmu_record_regs[i], hisi_pmic_reg_read(pmic_mntn->pmu_record_regs[i]));
	}

    return;
}
static void hisi_pmic_ocp_scan(PMIC_MNTN_DESC *pmic_mntn)
{
    int index, bit;
    int *reg_buff;
    PMIC_EXCH_REG *exch_desc;
    int reg_num;
    unsigned care_bit = 0;
    char *bit_name = NULL;
    char *cur_str = NULL;
    unsigned int bit_reg = 0;
    int ret = 0;

#if defined (CONFIG_HUAWEI_DSM)
    int pmic_ocp_error_offset = 0;
#endif

    reg_buff  = pmic_mntn->ocp_event_buff;
    exch_desc = pmic_mntn->ocp_exch_desc;
    reg_num   = pmic_mntn->ocp_reg_n;
    cur_str   = pmic_mntn->irq_log_show;

    for (index = 0; index < reg_num; index++) {
#if defined (CONFIG_HUAWEI_DSM)
        pmic_ocp_error_offset = PMU_REG_WIDTH * index;
#endif
        if (reg_buff[index]) {
            pr_err("[%s]reg = 0x%x, value = 0x%x\n", __func__, pmic_mntn->ocp_regs[index], reg_buff[index]);
            for (bit = 0; bit < pmic_mntn->data_width; bit++) {
                care_bit = reg_buff[index] & BIT(bit);
                if (care_bit) {
                    bit_name = exch_desc[index].event_bit_name[bit];
                    bit_reg = exch_desc[index].event_ops_reg[bit];
                    snprintf(cur_str + strlen(cur_str), PMIC_PRINT_BUF_SIZE, "PMU EVENT TYPE:ocp_%s\n", bit_name);
                    if (pmic_mntn->ocp_mold_switch)
                        get_pmu_register_info();
                    else
                        get_pmu_key_register_info(pmic_mntn);

#if defined (CONFIG_HUAWEI_DSM)
                   if (!pmic_mntn->reset_when_ocp[pmic_ocp_error_offset])
                   {
                        if (dsm_client_ocuppy(pmic_ocp_dclient)) {
                             pr_err("pmic_ocp_dclient dsm_client_ocuppy failed");
                        } else {
                             if (pmic_ocp_error_offset < 32) {
                                 pr_warn("hi6421 %s pmic_ocp_error happened, please pay attention!\n\r", pmic_ocp_name1[pmic_ocp_error_offset]);
                                 dsm_client_record(pmic_ocp_dclient, "hi6421 %s pmic_ocp_error happened, please pay attention!\n", pmic_ocp_name1[pmic_ocp_error_offset]);
                             } else {
                                 pr_warn("hi6421 %s pmic_ocp_error happened, please pay attention!\n\r", pmic_ocp_name2[pmic_ocp_error_offset -32]);
                                 dsm_client_record(pmic_ocp_dclient, "hi6421 %s pmic_ocp_error happened, please pay attention!\n", pmic_ocp_name2[pmic_ocp_error_offset -32]);
                             }
                             dsm_client_notify(pmic_ocp_dclient, DSM_PMU_OCP_ERROR_NO_BASE + pmic_ocp_error_offset);
                        }
                   }
#endif
                    /*close ldo*/
                    if (INVALID_REG_ADDR != bit_reg) {
                        hisi_pmic_reg_write(bit_reg, CLOSE_REGULATOR_CONTROL);
                    }
                    /*clear interrupt*/
                    hisi_pmic_reg_write(pmic_mntn->ocp_regs[index], care_bit);

                    if (!pmic_mntn->ocp_mold_switch)
                        ret = hisi_pmic_ocp_special_handler(bit_name, pmic_mntn);
                    if (PMIC_OCP_NONE == ret) {
                        if (care_bit & exch_desc[index].inacceptable_event) {
                            pmic_mntn->health |= BIT(PMIC_HEALTH_OCP_EXCH_HAPPENED);
                        }
                    }
                }
#if defined (CONFIG_HUAWEI_DSM)
                pmic_ocp_error_offset++;
#endif
            }
        }
    }

    return;
}

static void hisi_pmic_record_events(PMIC_MNTN_DESC *pmic_mntn)
{
    int index;

#if defined (CONFIG_HUAWEI_DSM)
    int pmic_record_error_offset = 0;
    int i = 0;
    int pmic_record_error_found = -1;
#endif

    snprintf(pmic_mntn->init_log_show, PMIC_PRINT_BUF_SIZE, "\nPMIC REGISTER DUMP\n");
    snprintf(pmic_mntn->init_log_show + strlen(pmic_mntn->init_log_show), PMIC_PRINT_BUF_SIZE, "  addr     data \n");

    for (index = 0; index < pmic_mntn->record_reg_n; index++) {
        pmic_mntn->record_event_buff[index] = hisi_pmic_reg_read(pmic_mntn->record_regs[index]);

#if defined (CONFIG_HUAWEI_DSM)
      pmic_record_error_found = -1;
      if (!dsm_client_ocuppy(pmic_ocp_dclient))
      {
          pmic_record_error_found++;
      }

      pmic_record_error_offset = PMU_REG_WIDTH * index;
      if ((index < 6) && pmic_record_error_found >= 0 && \
           (pmic_mntn->record_event_buff[index] & HISI_PMIC_OCP_MASK_STATE)) {
           pmic_record_error_found++;
           for (i = 0; i < PMU_REG_WIDTH; i++) {
                if (pmic_mntn->reset_when_ocp[pmic_record_error_offset] \
                    && (pmic_mntn->record_event_buff[index] & (0x01 << i))) {
                    if (pmic_record_error_offset < 32) {
                         pr_warn("hi6421 %s pmic_ocp_error happened, please pay attention!\n\r", pmic_ocp_name1[pmic_record_error_offset]);
                         dsm_client_record(pmic_ocp_dclient, "hi6421 %s pmic_ocp_error happened, please pay attention!\n", pmic_ocp_name1[pmic_record_error_offset]);
                    } else if (pmic_record_error_offset < 48) {
                         pr_warn("hi6421 %s pmic_ocp_error happened, please pay attention!\n\r", pmic_ocp_name2[pmic_record_error_offset -32]);
                         dsm_client_record(pmic_ocp_dclient, "hi6421 %s pmic_ocp_error happened, please pay attention!\n", pmic_ocp_name2[pmic_record_error_offset -32]);
                    } else {
                        pr_err("hisi_pmic_record_events in error condition.");
                    }
                    dsm_client_notify(pmic_ocp_dclient, DSM_PMU_OCP_ERROR_NO_BASE + pmic_record_error_offset);
                }
                pmic_record_error_offset++;
          }
      }

      if (!pmic_record_error_found) {
          dsm_client_unocuppy(pmic_ocp_dclient);
      }
#endif

        hisi_pmic_reg_write(pmic_mntn->record_regs[index], pmic_mntn->record_event_buff[index]);
        snprintf(pmic_mntn->init_log_show + strlen(pmic_mntn->init_log_show), PMIC_PRINT_BUF_SIZE,
            "  0x%0x    0x%0x \n", pmic_mntn->record_regs[index], pmic_mntn->record_event_buff[index]);
    }
    pr_err("%s", pmic_mntn->init_log_show);

    return;
}

static void hisi_pmic_clear_ocp(PMIC_MNTN_DESC *pmic_mntn)
{
    int index;

    for (index = 0; index < pmic_mntn->ocp_reg_n; index++) {
        pmic_mntn->ocp_event_buff[index] = hisi_pmic_reg_read(pmic_mntn->ocp_regs[index]);
        hisi_pmic_reg_write(pmic_mntn->ocp_regs[index], pmic_mntn->ocp_event_buff[index]);
    }

    memset((void *)pmic_mntn->ocp_event_buff, 0, sizeof(u32)*pmic_mntn->ocp_reg_n);

    return;
}

static irqreturn_t hisi_pmic_ocp_irq_handler(int irq, void *data)
{
    struct irq_desc *desc = NULL ;
    PMIC_MNTN_DESC *pmu_mntn = (PMIC_MNTN_DESC *)data;

    desc = irq_to_desc(irq);
    if (!desc) {
        pr_err("[%s]irq_to_desc failed\n", __func__);
        return IRQ_NONE;
    }

    if (NULL != desc->irq_data.chip->irq_mask) {
        desc->irq_data.chip->irq_mask(&desc->irq_data);
    }

    queue_work(pmu_mntn->ocp_wq, &pmu_mntn->ocp_wk);
    return IRQ_HANDLED;
}

static void hisi_pmic_ocp_wq_handler(struct work_struct *work)
{
    int index;
    struct irq_desc *desc = NULL;
    PMIC_MNTN_DESC *pmic_mntn = NULL;

    pmic_mntn = container_of(work, PMIC_MNTN_DESC, ocp_wk);

    memset((void *)pmic_mntn->irq_log_show, '\0', PMIC_PRINT_BUF_SIZE);

    for (index = 0; index < pmic_mntn->ocp_reg_n; index++) {
        pmic_mntn->ocp_event_buff[index] = hisi_pmic_reg_read(pmic_mntn->ocp_regs[index]);
    }

    hisi_pmic_ocp_scan(pmic_mntn);
    pr_info("\n%s\n", pmic_mntn->irq_log_show);

    desc = irq_to_desc(pmic_mntn->ocp_irq);
    if (!desc) {
        pr_err("[%s]irq_to_desc(pmic_mntn->ocp_irq) error.\n", __func__);
        return ;
    }

    if (NULL != desc->irq_data.chip->irq_unmask) {
        desc->irq_data.chip->irq_unmask(&desc->irq_data);
    }

    if (pmic_mntn->health & BIT(PMIC_HEALTH_OCP_EXCH_HAPPENED)) {
        hisi_pmic_panic_handler();
    }

}

static irqreturn_t hisi_pmic_otmp_irq_handler(int irq, void *data)
{
    struct irq_desc *desc = NULL ;
    PMIC_MNTN_DESC  *pmic_mntn = (PMIC_MNTN_DESC *)data;

    desc = irq_to_desc(irq);
    if (!desc) {
        pr_err("[%s]irq_to_desc failed\n", __func__);
        return IRQ_NONE;
    }

    if (NULL != desc->irq_data.chip->irq_mask) {
        desc->irq_data.chip->irq_mask(&desc->irq_data);
    }

    queue_work(pmic_mntn->otmp_wq, &pmic_mntn->otmp_wk);
    return IRQ_HANDLED;
}

static void hisi_pmic_otmp_wk_handler(struct work_struct *work)
{
    struct irq_desc *desc = NULL;
    PMIC_MNTN_DESC  *pmic_mntn;
    pmic_mntn = container_of(work, PMIC_MNTN_DESC, otmp_wk);

    memset((void *)pmic_mntn->irq_log_show, '\0', PMIC_PRINT_BUF_SIZE);
    snprintf(pmic_mntn->irq_log_show, PMIC_PRINT_BUF_SIZE, "%s", "PMIC OTMP EVENT HAPPEN.\n");
    pr_info("\n%s\n", pmic_mntn->irq_log_show);

    desc = irq_to_desc(pmic_mntn->otmp_irq);
    if (!desc) {
        pr_err("[%s]irq_to_desc err\n", __func__);
        return;
    }

    if (NULL != desc->irq_data.chip->irq_unmask) {
        desc->irq_data.chip->irq_unmask(&desc->irq_data);
    }

    hisi_pmic_panic_handler();

    return;
}

static int hisi_pmic_otmp_mntn_initial(struct platform_device *pdev, PMIC_MNTN_DESC *pmic_mntn)
{

    struct device_node *root = NULL;
    struct device *dev = &pdev->dev;
    struct device_node *np = dev->of_node;
    unsigned char reg_value = 0;
    s32 ret = 0;

    root = of_find_compatible_node(np, NULL, "hisilicon,pmic-mntn-otmp");
    if (!root) {
        dev_err(dev, "[%s]no hisilicon,pmic-mntn-otmp root node\n", __func__);
        return -ENODEV;
    }

    ret |= of_property_read_u32_array(root, "hisilicon,otmp-threshold-val", (u32 *)&pmic_mntn->otmp_thshd_val, 0x1);
    ret |= of_property_read_u32_array(root, "hisilicon,otmp-threshold-reg", (u32 *)&pmic_mntn->otmp_thshd_reg, 0x3);
    if (ret) {
        dev_err(dev, "[%s]get pmic otmp attribute failed.\n", __func__);
        return -ENODEV;
    }

    /*Set the otmp threshold*/
    reg_value = hisi_pmic_reg_read(pmic_mntn->otmp_thshd_reg.addr);
    SET_REG_BIT(reg_value, pmic_mntn->otmp_thshd_reg.shift, pmic_mntn->otmp_thshd_reg.mask, pmic_mntn->otmp_thshd_val);
    hisi_pmic_reg_write(pmic_mntn->otmp_thshd_reg.addr, reg_value);

    pmic_mntn->otmp_irq = platform_get_irq_byname(pdev, "otmp");
    if (pmic_mntn->ocp_irq  < 0) {
        dev_err(dev, "[%s]platform_get_irq_byname otmp_irq failed.\n", __func__);
        return -ENODEV;
    }

    pmic_mntn->otmp_wq = create_singlethread_workqueue("pmic-otmp-wq");
    INIT_WORK(&pmic_mntn->otmp_wk, (void *)hisi_pmic_otmp_wk_handler);

    ret = devm_request_irq(dev, pmic_mntn->otmp_irq, hisi_pmic_otmp_irq_handler, IRQF_DISABLED|IRQF_NO_SUSPEND,
        "pmic-otmp-irq", (void *)pmic_mntn);
    if (ret) {
        dev_err(dev, "[%s] request_irq otmp_irq err\n", __func__);
        return -ENODEV;
    }

    return 0;

}

static int hisi_pmic_smpl_mntn_initial(struct platform_device *pdev, PMIC_MNTN_DESC *pmic_mntn)
{

    struct device_node *root = NULL;
    struct device *dev = &pdev->dev;
    struct device_node *np = dev->of_node;
    unsigned char reg_value = 0;
    s32 ret = 0;

    root = of_find_compatible_node(np, NULL, "hisilicon,pmic-mntn-smpl");
    if (!root) {
        dev_err(dev, "[%s]no hisilicon,pmic-mntn-smpl root node\n", __func__);
        return -ENODEV;
    }

    ret |= of_property_read_u32_array(root, "hisilicon,smpl-ctrl-en", &pmic_mntn->smpl_en_val, 0x1);
    ret |= of_property_read_u32_array(root, "hisilicon,smpl-ctrl-en-reg", (u32 *)&pmic_mntn->smpl_en_reg, 0x3);
    ret |= of_property_read_u32_array(root, "hisilicon,smpl-ctrl-time", &pmic_mntn->smpl_tm_val, 0x1);
    ret |= of_property_read_u32_array(root, "hisilicon,smpl-ctrl-time-reg", (u32 *)&pmic_mntn->smpl_tm_reg, 0x3);
    if (ret) {
        dev_err(dev, "[%s]get pmic smpl attribute failed.\n", __func__);
        return -ENODEV;
    }

    /*Set SMPL on/off*/
    reg_value = hisi_pmic_reg_read(pmic_mntn->smpl_en_reg.addr);
    SET_REG_BIT(reg_value, pmic_mntn->smpl_en_reg.shift, pmic_mntn->smpl_en_reg.mask, pmic_mntn->smpl_en_val);
    hisi_pmic_reg_write(pmic_mntn->smpl_en_reg.addr, reg_value);

    /*Set SMPL effective time*/
    reg_value = hisi_pmic_reg_read(pmic_mntn->smpl_tm_reg.addr);
    SET_REG_BIT(reg_value, pmic_mntn->smpl_tm_reg.shift, pmic_mntn->smpl_tm_reg.mask, pmic_mntn->smpl_tm_val);
    hisi_pmic_reg_write(pmic_mntn->smpl_tm_reg.addr, reg_value);

    return 0;

}

static int hisi_pmic_ocp_mntn_initial(struct platform_device *pdev, PMIC_MNTN_DESC *pmic_mntn)
{

    struct device_node *root = NULL;
    struct device *dev = &pdev->dev;
    struct device_node *np = dev->of_node;
    PMIC_EXCH_REG *exch_reg_tmp;
    unsigned int index, bit;
    s32 ret = 0;
    char compatible_string[PMIC_DTS_ATTR_LEN] = {0};

    ret = of_property_read_u32(np, "hisilicon,ocp-reg-num", (u32 *)&pmic_mntn->ocp_reg_n);
    if (ret) {
        dev_err(dev, "[%s]get ocp-reg-num attribute failed.\n", __func__);
        return -ENODEV;
    }

    pmic_mntn->ocp_regs = (u32 *)devm_kzalloc(dev, sizeof(u32)*pmic_mntn->ocp_reg_n, GFP_KERNEL);
    if (!pmic_mntn->ocp_regs) {
        dev_err(dev, "[%s]kzalloc ocp_regs buffer failed.\n", __func__);
        return -ENOMEM;
    }

    ret = of_property_read_u32_array(np, "hisilicon,ocp-regs", pmic_mntn->ocp_regs, pmic_mntn->ocp_reg_n);
    if (ret) {
        dev_err(dev, "[%s]get ocp-regs attribute failed.\n", __func__);
        return -ENODEV;
    }

#if defined (CONFIG_HUAWEI_DSM)
    ret = of_property_read_u32(np, "hisilicon,reset-when-ocp-n", (u32 *)&pmic_mntn->reset_when_ocp_n);
    if (ret) {
        dev_err(dev, "[%s]get reset-when-ocp-n attribute failed.\n", __func__);
        return -ENODEV;
    }

    pmic_mntn->reset_when_ocp= (u32 *)devm_kzalloc(dev, sizeof(u32)*pmic_mntn->reset_when_ocp_n, GFP_KERNEL);
    if (!pmic_mntn->reset_when_ocp) {
        dev_err(dev, "[%s]kzalloc reset_when_ocp buffer failed.\n", __func__);
        return -ENOMEM;
    }

    ret = of_property_read_u32_array(np, "hisilicon,reset-when-ocp", pmic_mntn->reset_when_ocp, pmic_mntn->reset_when_ocp_n);
    if (ret) {
        dev_err(dev, "[%s]get reset-when-ocp attribute failed.\n", __func__);
        return -ENODEV;
    }
#endif

    pmic_mntn->ocp_exch_desc = (PMIC_EXCH_REG *)devm_kzalloc(dev, sizeof(PMIC_EXCH_REG)*pmic_mntn->ocp_reg_n, GFP_KERNEL);
    if (!pmic_mntn->ocp_exch_desc) {
        dev_err(dev, "[%s]kzalloc ocp_exch_desc buff failed.\n", __func__);
        return -ENOMEM;
    }
    exch_reg_tmp = pmic_mntn->ocp_exch_desc;

    for (index = 0; index < pmic_mntn->ocp_reg_n; index++) {
        snprintf(compatible_string, PMIC_DTS_ATTR_LEN, "hisilicon,pmic-mntn-ocp-reg0x%0x", pmic_mntn->ocp_regs[index]);
        root = of_find_compatible_node(np, NULL, compatible_string);
        if (!root) {
            dev_err(dev, "[%s]no %s root node.\n", __func__, compatible_string);
            return -ENODEV;
        }

        exch_reg_tmp[index].event_bit_name = (char **)devm_kzalloc(dev, pmic_mntn->data_width*sizeof(char *), GFP_KERNEL);
        if (NULL == exch_reg_tmp[index].event_bit_name) {
            dev_err(dev, "[%s]devm_kzalloc event_bit_name error.\n", __func__);
            return -ENOMEM;
        }

        exch_reg_tmp[index].event_ops_reg = (u32 *)devm_kzalloc(dev, pmic_mntn->data_width*sizeof(u32), GFP_KERNEL);
        if (NULL == exch_reg_tmp[index].event_ops_reg) {
            dev_err(dev, "[%s]devm_kzalloc event_ops_reg error.\n", __func__);
            return -ENOMEM;
        }

        ret = of_property_read_u32(root, "hisilicon,inacceptable-event", (u32 *)&exch_reg_tmp[index].inacceptable_event);
        for (bit = 0; bit < pmic_mntn->data_width; bit++) {
            ret |= of_property_read_string_index(root, "hisilicon,event-bit-name",
                        bit, (const char **)&exch_reg_tmp[index].event_bit_name[bit]);
        }

        ret |= of_property_read_u32_array(root, "hisilicon,event-ops-reg",
                (u32 *)exch_reg_tmp[index].event_ops_reg, pmic_mntn->data_width);

        if (ret) {
            dev_err(dev, "[%s]read attribute of %s.\n", __func__, compatible_string);
            return -ENODEV;
        }
    }

    pmic_mntn->ocp_event_buff = (u32 *)devm_kzalloc(dev, sizeof(u32)*pmic_mntn->ocp_reg_n, GFP_KERNEL);
    if (!pmic_mntn->ocp_event_buff) {
        dev_err(dev, "[%s]kzalloc ocp_event_buff failed.\n", __func__);
        return -ENOMEM;
    }

    hisi_pmic_clear_ocp(pmic_mntn);

    pmic_mntn->ocp_irq = platform_get_irq_byname(pdev, "ocp");
    if (pmic_mntn->ocp_irq < 0) {
        dev_err(dev, "[%s] platform_get_irq_byname ocp failed.\n", __func__);
        return -ENODEV;
    }

    pmic_mntn->ocp_wq = create_singlethread_workqueue("pmu-ocp-wq");
    INIT_WORK(&pmic_mntn->ocp_wk, hisi_pmic_ocp_wq_handler);

    ret = devm_request_irq(dev, pmic_mntn->ocp_irq, hisi_pmic_ocp_irq_handler, IRQF_DISABLED|IRQF_NO_SUSPEND,
          "pmu-ocp-irq", (void *)pmic_mntn);
    if (ret) {
        dev_err(dev, "[%s]request_irq ocp_irq failed.\n", __func__);
        return -ENODEV;
    }

    return 0;
}

static int hisi_pmic_record_mntn_initial(struct platform_device *pdev, PMIC_MNTN_DESC *pmic_mntn)
{
    struct device_node *root = NULL;
    struct device *dev = &pdev->dev;
    struct device_node *np = dev->of_node;
    PMIC_EXCH_REG *exch_reg_tmp;
    unsigned int index, bit;
    s32 ret = 0;
    char compatible_string[PMIC_DTS_ATTR_LEN] = {0};

    ret = of_property_read_u32(np, "hisilicon,record-reg-num", (u32 *)&pmic_mntn->record_reg_n);
    if (ret) {
        dev_err(dev, "[%s]get record-reg-num attribute failed.\n", __func__);
        return -ENODEV;
    }

    pmic_mntn->record_regs = (u32 *)devm_kzalloc(dev, sizeof(u32)*pmic_mntn->record_reg_n, GFP_KERNEL);
    if (!pmic_mntn->record_regs) {
        dev_err(dev, "[%s]kzalloc record_regs buffer failed.\n", __func__);
        return -ENOMEM;
    }

    ret = of_property_read_u32_array(np, "hisilicon,record-regs", pmic_mntn->record_regs, pmic_mntn->record_reg_n);
    if (ret) {
        dev_err(dev, "[%s]get record-regs attribute failed.\n", __func__);
        return -ENODEV;
    }

    pmic_mntn->record_exch_desc = (PMIC_EXCH_REG *)devm_kzalloc(dev, sizeof(PMIC_EXCH_REG)*pmic_mntn->record_reg_n, GFP_KERNEL);
    if (!pmic_mntn->record_exch_desc) {
        dev_err(dev, "[%s]kzalloc record_exch_desc buff failed.\n", __func__);
        return -ENOMEM;
    }
    exch_reg_tmp = pmic_mntn->record_exch_desc;

    for (index = 0; index < pmic_mntn->record_reg_n; index++) {
        snprintf(compatible_string, PMIC_DTS_ATTR_LEN, "hisilicon,pmic-mntn-record-reg0x%0x", pmic_mntn->record_regs[index]);
        root = of_find_compatible_node(np, NULL, compatible_string);
        if (!root) {
            dev_err(dev, "[%s]no %s root node.\n", __func__, compatible_string);
            return -ENODEV;
        }

        exch_reg_tmp[index].event_bit_name = (char **)devm_kzalloc(dev, pmic_mntn->data_width*sizeof(char *), GFP_KERNEL);
        if (NULL == exch_reg_tmp[index].event_bit_name) {
            dev_err(dev, "[%s]devm_kzalloc event_bit_name error.\n", __func__);
            return -ENOMEM;
        }

        ret = of_property_read_u32(root, "hisilicon,inacceptable-event", (u32 *)&exch_reg_tmp[index].inacceptable_event);
        for (bit = 0; bit < pmic_mntn->data_width; bit++) {
            ret |= of_property_read_string_index(root, "hisilicon,event-bit-name",
                        bit, (const char **)&exch_reg_tmp[index].event_bit_name[bit]);
        }

        if (ret) {
            dev_err(dev, "[%s]read attribute of %s.\n", __func__, compatible_string);
            return -ENODEV;
        }
    }

    pmic_mntn->record_event_buff = (u32 *)devm_kzalloc(dev, sizeof(u32)*pmic_mntn->record_reg_n, GFP_KERNEL);
    if (!pmic_mntn->record_event_buff) {
        dev_err(dev, "[%s]kzalloc record_event_buff failed.\n", __func__);
        return -ENOMEM;
    }

    return 0;
}

static int hisi_pmu_key_register_record_initial(struct platform_device *pdev, PMIC_MNTN_DESC *pmic_mntn)
{
    struct device *dev = &pdev->dev;
    struct device_node *np = dev->of_node;
    s32 ret = 0;

    ret = of_property_read_u32(np, "hisilicon,pmu-record-reg-num", (u32 *)&pmic_mntn->pmu_record_reg_n);
    if (ret) {
        dev_err(dev, "[%s]get hisilicon,pmu-record-reg-num attribute failed.\n", __func__);
        return -ENODEV;
    }

    if (pmic_mntn->pmu_record_reg_n <= 0)
        return ret;

    pmic_mntn->pmu_record_regs = (u32 *)devm_kzalloc(dev, sizeof(u32)*pmic_mntn->pmu_record_reg_n, GFP_KERNEL);
    if (!pmic_mntn->pmu_record_regs) {
        dev_err(dev, "[%s]kzalloc hisilicon,pmu-record-regs buffer failed.\n", __func__);
        return -ENOMEM;
    }

    ret = of_property_read_u32_array(np, "hisilicon,pmu-record-regs", pmic_mntn->pmu_record_regs, pmic_mntn->pmu_record_reg_n);
    if (ret) {
        dev_err(dev, "[%s]get hisilicon,pmu-record-regs attribute failed.\n", __func__);
        return -ENODEV;
    }

    return ret;
}

static int hisi_ocp_mold_switch_initial(struct platform_device *pdev, PMIC_MNTN_DESC *pmic_mntn)
{
    struct device *dev = &pdev->dev;
    struct device_node *np = dev->of_node;
    s32 ret = 0;
    int i = 0;

    ret = of_property_read_u32(np, "hisilicon,ocp-mold-set-switch", &pmic_mntn->ocp_mold_switch);
    if (ret) {
        dev_err(dev, "[%s]get pmic ocp-mold-set-switch failed.\n", __func__);
        return -ENODEV;
    }

    if (!pmic_mntn->ocp_mold_switch)
        return ret;

    ret = of_property_read_u32(np, "hisilicon,ocp-ctrl-num", (u32 *)&pmic_mntn->ocp_ctrl_n);
    if (ret) {
        dev_err(dev, "[%s]get ocp-ctrl-num attribute failed.\n", __func__);
        return -ENODEV;
    }

    pmic_mntn->ocp_ctrl_regs = (u32 *)devm_kzalloc(dev, sizeof(u32)*pmic_mntn->ocp_ctrl_n, GFP_KERNEL);
    if (!pmic_mntn->ocp_ctrl_regs) {
        dev_err(dev, "[%s]kzalloc ocp_ctrl_regs buffer failed.\n", __func__);
        return -ENOMEM;
    }

    ret = of_property_read_u32_array(np, "hisilicon,ocp-ctrl-regs", pmic_mntn->ocp_ctrl_regs, pmic_mntn->ocp_ctrl_n);
    if (ret) {
        dev_err(dev, "[%s]get ocp-ctrl-regs attribute failed.\n", __func__);
        return -ENODEV;
    }

    pmic_mntn->ocp_ctrl_val = (u32 *)devm_kzalloc(dev, sizeof(u32)*pmic_mntn->ocp_ctrl_n, GFP_KERNEL);
    if (!pmic_mntn->ocp_ctrl_val) {
        dev_err(dev, "[%s]kzalloc ocp_ctrl_regs buffer failed.\n", __func__);
        return -ENOMEM;
    }

    ret = of_property_read_u32_array(np, "hisilicon,ocp-ctrl-value", pmic_mntn->ocp_ctrl_val, pmic_mntn->ocp_ctrl_n);
    if (ret) {
        dev_err(dev, "[%s]get ocp-ctrl-regs attribute failed.\n", __func__);
        return -ENODEV;
    }

    for (i = 0; i < pmic_mntn->ocp_ctrl_n; i++) {
        hisi_pmic_reg_write(pmic_mntn->ocp_ctrl_regs[i], pmic_mntn->ocp_ctrl_val[i]);
    }

    return ret;
}

static struct of_device_id hisi_pmic_mntn_match_tbl[] = {
    {
        .compatible = "hisilicon,hi6421v500-mntn",
    },
    {
        .compatible = "hisilicon,hi6555v100-mntn",
    },
    { /* end */ }
};

static int hisi_pmic_mntn_probe(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;
    struct device_node *np = dev->of_node;
    PMIC_MNTN_DESC *pmic_mntn = NULL;
    int ret = 0;

    pmic_mntn = (PMIC_MNTN_DESC *)devm_kzalloc(dev, sizeof(*pmic_mntn), GFP_KERNEL);
    if (NULL == pmic_mntn) {
        dev_err(dev, "[%s]devm_kzalloc pmic_mntn err\n", __func__);
        return -ENOMEM;
    }

    g_pmic_mntn = pmic_mntn;
    pmic_mntn->health = PMIC_HEALTH_STATUS_NORMAL;

    pmic_mntn->init_log_show = (char *)devm_kzalloc(dev, PMIC_PRINT_BUF_SIZE, GFP_KERNEL);
    if (NULL == pmic_mntn->init_log_show) {
        dev_err(dev, "[%s]devm_kzalloc init_log_show err\n", __func__);
        return -ENOMEM;
    }

    pmic_mntn->irq_log_show = (char *)devm_kzalloc(dev, PMIC_PRINT_BUF_SIZE, GFP_KERNEL);
    if (NULL == pmic_mntn->irq_log_show) {
        dev_err(dev, "[%s]devm_kzalloc irq_log_show err\n", __func__);
        return -ENOMEM;
    }

    ret = of_property_read_u32(np, "hisilicon,data-width", &pmic_mntn->data_width);
    if (ret) {
        dev_err(dev, "[%s]get pmic data-width failed.\n", __func__);
        return -ENODEV;
    }

    ret = hisi_ocp_mold_switch_initial(pdev, pmic_mntn);
    if (ret) {
        dev_err(dev, "[%s]hisi_ocp_mold_switch_initial error.\n", __func__);
        return ret;
    }

    ret = hisi_pmu_key_register_record_initial(pdev, pmic_mntn);
    if (ret) {
        dev_err(dev, "[%s]hisi_pmu_key_register_record_initial error.\n", __func__);
        return ret;
    }

    ret = hisi_pmic_otmp_mntn_initial(pdev, pmic_mntn);
    if (ret) {
        dev_err(dev, "[%s]hisi_pmic_otmp_mntn_initial error.\n", __func__);
        return ret;
    }

    ret = hisi_pmic_smpl_mntn_initial(pdev, pmic_mntn);
    if (ret) {
        dev_err(dev, "[%s]hisi_pmic_smpl_mntn_initial error.\n", __func__);
        return ret;
    }

    ret = hisi_pmic_ocp_mntn_initial(pdev, pmic_mntn);
    if (ret) {
        dev_err(dev, "[%s]hisi_pmic_ocp_mntn_initial error.\n", __func__);
        return ret;
    }

    ret = hisi_pmic_record_mntn_initial(pdev, pmic_mntn);
    if (ret) {
        dev_err(dev, "[%s]hisi_pmic_record_mntn_initial error.\n", __func__);
        return ret;
    }

#if defined (CONFIG_HUAWEI_DSM)
    if (!pmic_ocp_dclient) {
        pmic_ocp_dclient = dsm_register_client(&dsm_pmic_ocp);
    }
#endif

    hisi_pmic_record_events(pmic_mntn);

    ret = hisi_pmic_register_special_ocp();
    if (ret) {
        dev_err(dev, "[%s]hisi_pmic_register_special_ocp error.\n", __func__);
        return ret;
    }

    return 0;
}

static int hisi_pmic_mntn_remove(struct platform_device *pdev)
{
    return 0;
}

#ifdef CONFIG_PM
static int hisi_pmic_mntn_suspend(struct platform_device *pdev, pm_message_t pm)
{
    return 0;
}

static int hisi_pmic_mntn_resume(struct platform_device *pdev)
{
    return 0;
}
#endif

static struct platform_driver hisi_pmic_mntn_driver = {
    .driver = {
        .name = "hisilicon,hisi-pmic-mntn",
        .owner = THIS_MODULE,
        .of_match_table = hisi_pmic_mntn_match_tbl,
    },
    .probe   = hisi_pmic_mntn_probe,
    .remove  = hisi_pmic_mntn_remove,
#ifdef CONFIG_PM
    .suspend = hisi_pmic_mntn_suspend,
    .resume  = hisi_pmic_mntn_resume,
#endif
};

static int __init hisi_pmic_mntn_init(void)
{
    int ret = 0;
    pr_info("\n===============[in %s ]=============\n", __func__);

    ret = platform_driver_register(&hisi_pmic_mntn_driver);
    if (ret) {
        pr_err("[%s]platform_driver_register failed \n", __func__);
    }

    return ret;
}

static void __exit hisi_pmic_mntn_exit(void)
{
    platform_driver_unregister(&hisi_pmic_mntn_driver);
}

module_init(hisi_pmic_mntn_init);
module_exit(hisi_pmic_mntn_exit);

MODULE_AUTHOR("wanghuan<wanghuan4@huawei.com>");
MODULE_DESCRIPTION("HISI PMU MNTN Driver");
MODULE_LICENSE("GPL V2");

