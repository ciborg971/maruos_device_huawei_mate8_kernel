/*
 * ARM big.LITTLE Platforms CPUFreq support
 *
 * Copyright (C) 2013 ARM Ltd.
 * Sudeep KarkadaNagesha <sudeep.karkadanagesha@arm.com>
 *
 * Copyright (C) 2013 Linaro.
 * Viresh Kumar <viresh.kumar@linaro.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/clk.h>
#include <linux/cpu.h>
#include <linux/cpufreq.h>
#include <linux/cpumask.h>
#include <linux/export.h>
#include <linux/mutex.h>
#include <linux/of_platform.h>
#include <linux/opp.h>
#include <linux/slab.h>
#include <linux/topology.h>
#include <linux/types.h>
#include <linux/thermal.h>
#include <asm/bL_switcher.h>

#include "arm_big_little.h"

#ifdef CONFIG_HISI_CPUFREQ_WITH_HOTPLUG
#include "cpufreq_governor.h"
#include <linux/sched.h>
#include <linux/sched/rt.h>
#include <linux/kthread.h>
#endif

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <linux/hw_dev_dec.h>
#endif

#ifdef CONFIG_BL_SWITCHER
bool bL_switching_enabled;
#endif

#define ACTUAL_FREQ(cluster, freq)	((cluster == A7_CLUSTER) ? freq << 1 : freq)
#define VIRT_FREQ(cluster, freq)	((cluster == A7_CLUSTER) ? freq >> 1 : freq)

#define CONFIG_ARCH_HISI_MAXFREQ

#ifdef CONFIG_ARCH_HISI_MAXFREQ
typedef struct _soc_freq{
	unsigned int id;
	int val;
}soc_freq;

typedef struct _soc_freq_long{
	unsigned long id;
	unsigned long val;
}soc_freq_long;

#define BIG_CLUSTER			1
#define MAX_FREQ_LIMIT 2304000000
#define EFUSE_TABLE_LEN 4
#define DEFAULT_EFUSE_FREQ_LEVEL 6
#define DEFAULT_ADJUST_FREQ_LEVEL 0
#define EFUSE_ADJUST_LEN 1

enum SOC_EFUSE_FREQ_ENUM{
    SOC_EFUSE_FREQ_0 = 0x00,/*480000*/
    SOC_EFUSE_FREQ_1 = 0x01,/*807000*/
    SOC_EFUSE_FREQ_2 = 0x02,/*1210000*/
    SOC_EFUSE_FREQ_3 = 0x03,/*1517000*/
    SOC_EFUSE_FREQ_4 = 0x04,/*1805000*/
    SOC_EFUSE_FREQ_5 = 0x05,/*2016000*/
    SOC_EFUSE_FREQ_6 = 0x06,/*2304000*/
    SOC_EFUSE_FREQ_7 = 0x07,/*2516000*/
    SOC_EFUSE_FREQ_MAX,/*max*/
};

/*the table will sync with dts*/
soc_freq_long freq_prof_val_table[SOC_EFUSE_FREQ_MAX]={
	{SOC_EFUSE_FREQ_0,480000000},
	{SOC_EFUSE_FREQ_1,807000000},
	{SOC_EFUSE_FREQ_2,1210000000},
	{SOC_EFUSE_FREQ_3,1517000000},
	{SOC_EFUSE_FREQ_4,1805000000},
	{SOC_EFUSE_FREQ_5,2016000000},
	{SOC_EFUSE_FREQ_6,2304000000},
	{SOC_EFUSE_FREQ_7,2516000000},
};

soc_freq soc_efuse_freq_table[EFUSE_TABLE_LEN]=
{
	{0x00,SOC_EFUSE_FREQ_6},
	{0x01,SOC_EFUSE_FREQ_6},
	{0x10,SOC_EFUSE_FREQ_7},
	{0x11,SOC_EFUSE_FREQ_6},
};


extern int get_efuse_freq_value(unsigned char *pu8Buffer, unsigned int u32Length);

#endif

static struct cpufreq_arm_bL_ops *arm_bL_ops;
static struct clk *clk[MAX_CLUSTERS];
static struct cpufreq_frequency_table *freq_table[MAX_CLUSTERS + 1];
static atomic_t cluster_usage[MAX_CLUSTERS + 1] = {ATOMIC_INIT(0),
	ATOMIC_INIT(0)};

static unsigned int clk_big_min;	/* (Big) clock frequencies */
static unsigned int clk_little_max;	/* Maximum clock frequency (Little) */

static DEFINE_PER_CPU(unsigned int, physical_cluster);
static DEFINE_PER_CPU(unsigned int, cpu_last_req_freq);

static struct mutex cluster_lock[MAX_CLUSTERS];
static bool cpufreq_suspended[MAX_CLUSTERS];

#ifdef CONFIG_HISI_CPUFREQ_WITH_HOTPLUG
#define HOTPLUG_UP	1
#define HOTPLUG_DOWN	0
#define NEED_HOTPLUG_THRESHOLD_FREQ 2016000

static struct task_struct *hotplug_task;
static spinlock_t need_hotplug_lock;
static bool hotplug_up;
static bool hotplug_down;
static bool hotplugged_by_cpufreq;
static unsigned int target;
/* get from dt*/
static unsigned int coefficient;
static unsigned int hotplug_threshold_freq;

bool cpufreq_hotplugged(unsigned int cpu)
{
	if(cpu == 6 || cpu == 7)
		return hotplugged_by_cpufreq;
	else
		return false;
}
EXPORT_SYMBOL_GPL(cpufreq_hotplugged);
#endif


static unsigned int find_cluster_maxfreq(int cluster)
{
	int j;
	u32 max_freq = 0, cpu_freq;

	for_each_online_cpu(j) {
		cpu_freq = per_cpu(cpu_last_req_freq, j);

		if ((cluster == per_cpu(physical_cluster, j)) &&
				(max_freq < cpu_freq))
			max_freq = cpu_freq;
	}

	pr_debug("%s: cluster: %d, max freq: %d\n", __func__, cluster,
			max_freq);

	return max_freq;
}

static unsigned int clk_get_cpu_rate(unsigned int cpu)
{
	u32 cur_cluster = per_cpu(physical_cluster, cpu);
	u32 rate = clk_get_rate(clk[cur_cluster]) / 1000;

	/* For switcher we use virtual A15 clock rates */
	if (is_bL_switching_enabled())
		rate = VIRT_FREQ(cur_cluster, rate);

	pr_debug("%s: cpu: %d, cluster: %d, freq: %u\n", __func__, cpu,
			cur_cluster, rate);

	return rate;
}

static unsigned int bL_cpufreq_get_rate(unsigned int cpu)
{
	if (is_bL_switching_enabled()) {
		pr_debug("%s: freq: %d\n", __func__, per_cpu(cpu_last_req_freq,
					cpu));

		return per_cpu(cpu_last_req_freq, cpu);
	} else {
		return clk_get_cpu_rate(cpu);
	}
}

static int
bL_cpufreq_set_rate(u32 cpu, u32 old_cluster, u32 new_cluster, u32 rate)
{
	u32 new_rate, prev_rate;
	int ret;
	bool bLs = is_bL_switching_enabled();

	mutex_lock(&cluster_lock[new_cluster]);

	if (bLs) {
		prev_rate = per_cpu(cpu_last_req_freq, cpu);
		per_cpu(cpu_last_req_freq, cpu) = rate;
		per_cpu(physical_cluster, cpu) = new_cluster;

		new_rate = find_cluster_maxfreq(new_cluster);
		new_rate = ACTUAL_FREQ(new_cluster, new_rate);
	} else {
		new_rate = rate;
	}

	pr_debug("%s: cpu: %d, old cluster: %d, new cluster: %d, freq: %d\n",
			__func__, cpu, old_cluster, new_cluster, new_rate);

	ret = clk_set_rate(clk[new_cluster], new_rate * 1000);
	if (WARN_ON(ret)) {
		pr_err("clk_set_rate failed: %d, new cluster: %d\n", ret,
				new_cluster);
		if (bLs) {
			per_cpu(cpu_last_req_freq, cpu) = prev_rate;
			per_cpu(physical_cluster, cpu) = old_cluster;
		}

		mutex_unlock(&cluster_lock[new_cluster]);

		return ret;
	}

	mutex_unlock(&cluster_lock[new_cluster]);

	/* Recalc freq for old cluster when switching clusters */
	if (old_cluster != new_cluster) {
		pr_debug("%s: cpu: %d, old cluster: %d, new cluster: %d\n",
				__func__, cpu, old_cluster, new_cluster);

		/* Switch cluster */
		bL_switch_request(cpu, new_cluster);

		mutex_lock(&cluster_lock[old_cluster]);

		/* Set freq of old cluster if there are cpus left on it */
		new_rate = find_cluster_maxfreq(old_cluster);
		new_rate = ACTUAL_FREQ(old_cluster, new_rate);

		if (new_rate) {
			pr_debug("%s: Updating rate of old cluster: %d, to freq: %d\n",
					__func__, old_cluster, new_rate);

			if (clk_set_rate(clk[old_cluster], new_rate * 1000))
				pr_err("%s: clk_set_rate failed: %d, old cluster: %d\n",
						__func__, ret, old_cluster);
		}
		mutex_unlock(&cluster_lock[old_cluster]);
	}

	return 0;
}

/* Validate policy frequency range */
static int bL_cpufreq_verify_policy(struct cpufreq_policy *policy)
{
	u32 cur_cluster = cpu_to_cluster(policy->cpu);

	return cpufreq_frequency_table_verify(policy, freq_table[cur_cluster]);
}

#ifdef CONFIG_HISI_CPUFREQ_WITH_HOTPLUG
static int cpu_hotplug(int cpuid, int onoff)
{
	struct device *cpu_dev = get_cpu_device(cpuid);
	int from_nid, to_nid;
	int ret;

#ifdef CONFIG_ARCH_HISI
	hisi_cpu_hotplug_lock();
#endif
	cpu_hotplug_driver_lock();
	switch (onoff) {
	case 0:
		cpuidle_pause();

		ret = cpu_down(cpuid);
		cpuidle_resume();
		if (!ret)
			kobject_uevent(&cpu_dev->kobj, KOBJ_OFFLINE);
		break;
	case 1:
		from_nid = cpu_to_node(cpuid);
		cpuidle_pause();
		ret = cpu_up(cpuid);
		cpuidle_resume();

		/*
		 * When hot adding memory to memoryless node and enabling a cpu
		 * on the node, node number of the cpu may internally change.
		 */
		to_nid = cpu_to_node(cpuid);
		if (from_nid != to_nid)
			change_cpu_under_node(cpuid, from_nid, to_nid);

		if (!ret)
			kobject_uevent(&cpu_dev->kobj, KOBJ_ONLINE);
		break;
	default:
		ret = -EINVAL;
	}
	cpu_hotplug_driver_unlock();

#ifdef CONFIG_ARCH_HISI
	hisi_cpu_hotplug_unlock();
#endif

	return ret;
}

static int cpufreq_bL_hotplug_task(void *data)
{
	struct cpufreq_freqs freqs;
	int ret;
	unsigned long flags;

	while(1) {
		set_current_state(TASK_INTERRUPTIBLE);
		spin_lock_irqsave(&need_hotplug_lock, flags);

		if ((!hotplug_up) && (!hotplug_down)) {
			spin_unlock_irqrestore(&need_hotplug_lock, flags);
			schedule();

			if (kthread_should_stop())
				break;

			spin_lock_irqsave(&need_hotplug_lock, flags);
		}

		set_current_state(TASK_RUNNING);
		spin_unlock_irqrestore(&need_hotplug_lock, flags);

		if(hotplug_down) {
			hotplug_down = false;
			if(!cpu_is_offline(6))
				cpu_hotplug(6, HOTPLUG_DOWN);
			if(!cpu_is_offline(7))
				cpu_hotplug(7, HOTPLUG_DOWN);
			hotplugged_by_cpufreq = true;
		}

		ret = bL_cpufreq_set_rate(4, A7_CLUSTER, A7_CLUSTER, target);

		if(hotplug_up) {
			hotplug_up = false;
			if(cpu_is_offline(6))
				cpu_hotplug(6, HOTPLUG_UP);
			if(cpu_is_offline(7))
				cpu_hotplug(7, HOTPLUG_UP);
			hotplugged_by_cpufreq = false;
		}
	}
	return 0;
}
#endif

/* Set clock frequency */
static int bL_cpufreq_set_target(struct cpufreq_policy *policy,
		unsigned int target_freq, unsigned int relation)
{
	struct cpufreq_freqs freqs;
	u32 cpu = policy->cpu, freq_tab_idx, cur_cluster, new_cluster,
	    actual_cluster;
	int ret = 0;
#ifdef CONFIG_HISI_CPUFREQ_WITH_HOTPLUG
	unsigned int j;
	unsigned int total_loads = 0;
	unsigned long flags;
#endif

	cur_cluster = cpu_to_cluster(cpu);
	new_cluster = actual_cluster = per_cpu(physical_cluster, cpu);

	if(cpufreq_suspended[cur_cluster])
		return 0;

	freqs.old = bL_cpufreq_get_rate(cpu);

	/* Determine valid target frequency using freq_table */
	ret = cpufreq_frequency_table_target(policy, freq_table[cur_cluster],
			target_freq, relation, &freq_tab_idx);
	if (ret)
		return ret;

	freqs.new = freq_table[cur_cluster][freq_tab_idx].frequency;

	pr_debug("%s: cpu: %d, cluster: %d, oldfreq: %d, target freq: %d, new freq: %d\n",
			__func__, cpu, cur_cluster, freqs.old, target_freq,
			freqs.new);

#ifdef CONFIG_HISI_IPA_THERMAL
	freqs.new = ipa_freq_limit(cur_cluster,freqs.new);
#endif
	if (freqs.old == freqs.new)
		return 0;

	if (is_bL_switching_enabled()) {
		if ((actual_cluster == A15_CLUSTER) &&
				(freqs.new < clk_big_min)) {
			new_cluster = A7_CLUSTER;
		} else if ((actual_cluster == A7_CLUSTER) &&
				(freqs.new > clk_little_max)) {
			new_cluster = A15_CLUSTER;
		}
	}

#ifdef CONFIG_HISI_CPUFREQ_WITH_HOTPLUG
	if (cur_cluster == A7_CLUSTER) {
		if(freqs.old <= hotplug_threshold_freq && freqs.new > hotplug_threshold_freq) {
			/* decide freq up to hotplug_threshold_freq or
				higher than hotplug_threshold_freq */
			for_each_cpu(j, policy->cpus)
				total_loads += per_cpu(j, load);
			if(total_loads > coefficient * policy->max / policy->cur / 100) {
				freqs.new = hotplug_threshold_freq;
				if (freqs.old == freqs.new)
					return 0;

				goto normal_set;
			}
			target = freqs.new;
			spin_lock_irqsave(&need_hotplug_lock, flags);
			hotplug_down = true;
			spin_unlock_irqrestore(&need_hotplug_lock, flags);
			cpufreq_notify_transition(policy, &freqs, CPUFREQ_PRECHANGE);
			wake_up_process(hotplug_task);
			policy->cur = freqs.new;
			cpufreq_notify_transition(policy, &freqs, CPUFREQ_POSTCHANGE);
			return 0;
		}

		if(freqs.old > hotplug_threshold_freq && freqs.new <= hotplug_threshold_freq) {
			target = freqs.new;
			spin_lock_irqsave(&need_hotplug_lock, flags);
			hotplug_up = true;
			spin_unlock_irqrestore(&need_hotplug_lock, flags);
			cpufreq_notify_transition(policy, &freqs, CPUFREQ_PRECHANGE);
			wake_up_process(hotplug_task);
			policy->cur = freqs.new;
			cpufreq_notify_transition(policy, &freqs, CPUFREQ_POSTCHANGE);
			return 0;
		}
	}
normal_set:
#endif

	cpufreq_notify_transition(policy, &freqs, CPUFREQ_PRECHANGE);
	ret = bL_cpufreq_set_rate(cpu, actual_cluster, new_cluster, freqs.new);
	if (ret)
		return ret;

	policy->cur = freqs.new;

	cpufreq_notify_transition(policy, &freqs, CPUFREQ_POSTCHANGE);

	return ret;
}

static inline u32 get_table_count(struct cpufreq_frequency_table *table)
{
	u32 count;

	for (count = 0; table[count].frequency != CPUFREQ_TABLE_END; count++)
		;

	return count;
}

/* get the minimum frequency in the cpufreq_frequency_table */
static inline u32 get_table_min(struct cpufreq_frequency_table *table)
{
	int i;
	uint32_t min_freq = ~0;
	for (i = 0; (table[i].frequency != CPUFREQ_TABLE_END); i++)
		if (table[i].frequency < min_freq)
			min_freq = table[i].frequency;
	return min_freq;
}

/* get the maximum frequency in the cpufreq_frequency_table */
static inline u32 get_table_max(struct cpufreq_frequency_table *table)
{
	int i;
	uint32_t max_freq = 0;
	for (i = 0; (table[i].frequency != CPUFREQ_TABLE_END); i++)
		if (table[i].frequency > max_freq)
			max_freq = table[i].frequency;
	return max_freq;
}

static int merge_cluster_tables(void)
{
	int i, j, k = 0, count = 1;
	struct cpufreq_frequency_table *table;

	for (i = 0; i < MAX_CLUSTERS; i++)
		count += get_table_count(freq_table[i]);

	table = kzalloc(sizeof(*table) * count, GFP_KERNEL);
	if (!table)
		return -ENOMEM;

	freq_table[MAX_CLUSTERS] = table;

	/* Add in reverse order to get freqs in increasing order */
	for (i = MAX_CLUSTERS - 1; i >= 0; i--) {
		for (j = 0; freq_table[i][j].frequency != CPUFREQ_TABLE_END;
				j++) {
			table[k].frequency = VIRT_FREQ(i,
					freq_table[i][j].frequency);
			pr_debug("%s: index: %d, freq: %d\n", __func__, k,
					table[k].frequency);
			k++;
		}
	}

	table[k].index = k;
	table[k].frequency = CPUFREQ_TABLE_END;

	pr_debug("%s: End, table: %p, count: %d\n", __func__, table, k);

	return 0;
}

static void _put_cluster_clk_and_freq_table(struct device *cpu_dev)
{
	u32 cluster = cpu_to_cluster(cpu_dev->id);

	if (!atomic_dec_return(&cluster_usage[cluster])) {
		clk_put(clk[cluster]);
		opp_free_cpufreq_table(cpu_dev, &freq_table[cluster]);
		dev_dbg(cpu_dev, "%s: cluster: %d\n", __func__, cluster);
	}
}

static void put_cluster_clk_and_freq_table(struct device *cpu_dev)
{
	u32 cluster = cpu_to_cluster(cpu_dev->id);
	int i;

	if (cluster < MAX_CLUSTERS)
		return _put_cluster_clk_and_freq_table(cpu_dev);

	if (atomic_dec_return(&cluster_usage[MAX_CLUSTERS]))
		return;

	for (i = 0; i < MAX_CLUSTERS; i++) {
		struct device *cdev = get_cpu_device(i);
		if (!cdev) {
			pr_err("%s: failed to get cpu%d device\n", __func__, i);
			return;
		}

		_put_cluster_clk_and_freq_table(cdev);
	}

	/* free virtual table */
	kfree(freq_table[MAX_CLUSTERS]);
}

#ifdef CONFIG_ARCH_HISI_MAXFREQ
int of_target_cpu(unsigned long * freq)
{
	struct device_node *np;
	char * target_cpu;
	unsigned int target_max_freq = 0;
	int ret;
	unsigned int index;

	np = of_find_compatible_node(NULL,NULL,"hisi,targetcpu");
	if (!np)
		return -1;
	ret = of_property_read_string(np,"target_cpu",(const char**)(&target_cpu));
	if (ret)
		return -1;
	pr_info("target_cpu:%s.\n", target_cpu);

	np = of_find_compatible_node(NULL,NULL,"hisi,supportedtarget");
	if (!np)
		return -1;

	index = of_property_match_string(np, "support_name", target_cpu);
	pr_info("%s: index :%u.\n", __func__,index);

	ret = of_property_read_u32_index(np,"support_value",index, &target_max_freq);
	if (ret)
		return -1;

	*freq = target_max_freq*1000;
	/*if parse error,set 2.3G as default*/
	if ((*freq < freq_prof_val_table[SOC_EFUSE_FREQ_0].val) || \
		(*freq > freq_prof_val_table[SOC_EFUSE_FREQ_7].val)){
		*freq = freq_prof_val_table[SOC_EFUSE_FREQ_6].val;
	}
	pr_info("%s: target_max_freq:%llu.\n", __func__,(long long unsigned int)(*freq));

	return 0;
}
int of_init_efuse_freq_table(soc_freq_long* efuse_req)
{
	struct device_node *np;
	const struct property *prop;
	const __be32 *val;
	int nr;
	int i = 0;

	np = of_find_node_by_path("/cpus/cpu@100");
	if (!np) {
		pr_err("cpu@100 not found.\n");
		return -1;
	}
	prop = of_find_property(np, "operating-points", NULL);
	if (!prop) {
		pr_err("operating-points node not found.\n");
		return -1;
	}
	if (!prop->value) {
		pr_err("operating-points value not found.\n");
		return -1;
	}

	/*
	 * Each OPP is a set of tuples consisting of frequency and
	 * voltage like <freq-kHz vol-uV>.
	 */
	nr = prop->length / sizeof(u32);
	if (nr % 2) {
		pr_err("%s: Invalid OPP list\n", __func__);
		return -1;
	}

	val = prop->value;
	i = 0;
	while (nr) {
		unsigned long freq = be32_to_cpup(val++) * 1000;
		val++;

		pr_info("id:0x%lu,freq:%llu.\n",freq_prof_val_table[i].id,(long long unsigned int)freq_prof_val_table[i].val);

		efuse_req[i].id = i;
		efuse_req[i].val= freq;

		i++;
		nr -= 2;
	}

	return 0;
}

int check_cpu_profile(unsigned long* freq_val,unsigned int prof_len)
{
	int _max_prof = SOC_EFUSE_FREQ_6;/*the final level*/
    unsigned int max_prof = 0x10;/* 1718-1721 */
    unsigned int max_prof_adjust = 0x0;/* 1714-1717 */
    unsigned int adjust_symbol = 0;
    unsigned int efuse_val = 0;

	pr_err("%s:read freq_efuse start.\n",__func__);

    if (0 != get_efuse_freq_value((unsigned char *)(&efuse_val),4)) {
		pr_err("%s:read freq_efuse fail,val:0x%x.\n",__func__,efuse_val);
		return -1;
    }
	pr_info("%s:read freq_efuse ok,val:0x%x.\n",__func__,efuse_val);

	/*efuse 0,default 2.3G*/
	if (efuse_val != 0) {
		max_prof = (efuse_val >> 4)&0xf;
		max_prof_adjust = efuse_val&0x7;
		adjust_symbol = (efuse_val >> 3)&0x1;
	} else {
		max_prof = DEFAULT_EFUSE_FREQ_LEVEL;
		max_prof_adjust = DEFAULT_ADJUST_FREQ_LEVEL;
	}

	pr_info("%s:max_prof:0x%x,adjust_prof:0x%x,symbol:%d.\n",__func__,max_prof,max_prof_adjust,adjust_symbol);

	if (max_prof >= EFUSE_TABLE_LEN) {
		_max_prof = soc_efuse_freq_table[0].val;
		pr_err("%s:ATE efuse:0x%x err.\n",__func__,max_prof);
	} else {
		_max_prof = soc_efuse_freq_table[max_prof].val;
	}

	pr_info("%s:efuse_max_freq:0x%x.\n",__func__,_max_prof);

	/*adjust limit to 1 level*/
	if (max_prof_adjust > EFUSE_ADJUST_LEN) {
		pr_err("%s:ATE efuse adjust:0x%x err.\n",__func__,max_prof_adjust);
		return -1;
	} else {
		if (adjust_symbol == 0)
			_max_prof += max_prof_adjust;
		else
			_max_prof -= max_prof_adjust;
	}

	if(_max_prof < 0 || _max_prof >= SOC_EFUSE_FREQ_MAX) {
		_max_prof = DEFAULT_EFUSE_FREQ_LEVEL;
		pr_err("%s: efuse adjust overflow,set to default.\n",__func__);
	}

	pr_info("%s:efuse_adjust_freq:0x%x.\n",__func__,_max_prof);

	if (_max_prof > prof_len -1) {
		pr_err("%s:CHIP WARNING,efuse_adjust_freq real prof:0x%x > max prof:0x%x.\n",__func__,_max_prof,prof_len-1);
		_max_prof = prof_len -1;
	}

	*freq_val = freq_prof_val_table[_max_prof].val;
	/*prevent adjust level too low*/
	if (*freq_val < MAX_FREQ_LIMIT) {
		pr_err("%s:freq adjust result:%llu error,set to MAX_FREQ_LIMIT.\n",__func__,(long long unsigned int)*freq_val);
		*freq_val = MAX_FREQ_LIMIT;
	}
	pr_info("%s:efuse real freq:%llu.\n",__func__,(long long unsigned int)*freq_val);

	return 0;
}
EXPORT_SYMBOL_GPL(check_cpu_profile);
#endif

static int _get_cluster_clk_and_freq_table(struct device *cpu_dev)
{
	u32 cluster = cpu_to_cluster(cpu_dev->id);
	char name[14] = "cpu-cluster.X";
	int ret;
#ifdef CONFIG_ARCH_HISI_MAXFREQ
	unsigned long max_freq_efuse = 0;
	unsigned long freq = ULONG_MAX;
	unsigned long target_freq = ULONG_MAX;
	struct opp *temp_opp;
	bool set_flag = true;
#endif

	if (atomic_inc_return(&cluster_usage[cluster]) != 1)
		return 0;

	ret = arm_bL_ops->init_opp_table(cpu_dev);
	if (ret) {
		dev_err(cpu_dev, "%s: init_opp_table failed, cpu: %d, err: %d\n",
				__func__, cpu_dev->id, ret);
		goto atomic_dec;
	}

#ifdef CONFIG_ARCH_HISI_MAXFREQ
	if (cluster == BIG_CLUSTER) {
		/*sync freq_table with dts*/
		if (0 != of_init_efuse_freq_table((soc_freq_long*)(&freq_prof_val_table))) {
			set_flag = false;
			max_freq_efuse = freq_prof_val_table[SOC_EFUSE_FREQ_6].val;
			goto dev_check_chip_freq;
		}

		/*parse target_cpu to find max_freq of dts*/
		if (0 != of_target_cpu(&target_freq)) {
			pr_err("of_target_cpu parse error.\n");
			set_flag = false;
			goto dev_check_chip_freq;
		}

		/*get the target freq and disable unused prof*/
		rcu_read_lock();
		opp_find_freq_floor(cpu_dev, &freq);
		rcu_read_unlock();
		pr_info("dts floor_freq:%llu.\n",(long long unsigned int)freq);

		while (freq > target_freq) {
			opp_disable(cpu_dev, freq);

			rcu_read_lock();
			temp_opp = opp_find_freq_floor(cpu_dev, &freq);
			rcu_read_unlock();

			/* check if no opp left, break the infinite loop */
			if (IS_ERR(temp_opp))
				break;
		}
		pr_info("target floor_freq:%llu.\n",(long long unsigned int)freq);

		/*get freq efuse level/adjust level*/
		if (0 != check_cpu_profile(&max_freq_efuse,SOC_EFUSE_FREQ_MAX)) {
			set_flag = false;
			max_freq_efuse = freq_prof_val_table[DEFAULT_EFUSE_FREQ_LEVEL].val;
			goto dev_check_chip_freq;
		}
		pr_info("max_freq_efuse:%llu.\n",(long long unsigned int)max_freq_efuse);

		/*if check failed,just delete the max profile*/
		if (freq > max_freq_efuse) {
			set_flag = false;
			/*SLT/UDP plat,set 2.5G as max_freq in dts*/
			opp_disable(cpu_dev, freq);
			pr_err("Chip_check FAIL.firmware_freq:%llu > efuse_freq:%llu.\n",(long long unsigned int)freq,(long long unsigned int)max_freq_efuse);
		}
		else if (freq == max_freq_efuse) {
			pr_err("Chip_check SUCC.OK, firmware_freq = efuse_freq:%llu.\n",(long long unsigned int)freq);
		} else {
			pr_err("Chip_check SUCC.WARNING,firmware_freq:%llu < efuse_freq:%llu.\n",(long long unsigned int)freq,(long long unsigned int)max_freq_efuse);
		}

	dev_check_chip_freq:
		/*detect current device successful, set the flag */
		if (set_flag == true) {
		#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			set_hw_dev_flag(DEV_I2C_CPU_CHIP);
		#endif

		}
	}
#endif
	ret = opp_init_cpufreq_table(cpu_dev, &freq_table[cluster]);
	if (ret) {
		dev_err(cpu_dev, "%s: failed to init cpufreq table, cpu: %d, err: %d\n",
				__func__, cpu_dev->id, ret);
		goto atomic_dec;
	}

	name[12] = cluster + '0';

	clk[cluster] = clk_get_sys(NULL, name);
	if (!IS_ERR(clk[cluster])) {
		dev_dbg(cpu_dev, "%s: clk: %p & freq table: %p, cluster: %d\n",
				__func__, clk[cluster], freq_table[cluster],
				cluster);
		return 0;
	}

	dev_err(cpu_dev, "%s: Failed to get clk for cpu: %d, cluster: %d\n",
			__func__, cpu_dev->id, cluster);
	ret = PTR_ERR(clk[cluster]);
	opp_free_cpufreq_table(cpu_dev, &freq_table[cluster]);

atomic_dec:
	atomic_dec(&cluster_usage[cluster]);
	dev_err(cpu_dev, "%s: Failed to get data for cluster: %d\n", __func__,
			cluster);
	return ret;
}

static int get_cluster_clk_and_freq_table(struct device *cpu_dev)
{
	u32 cluster = cpu_to_cluster(cpu_dev->id);
	int i, ret;

	if (cluster < MAX_CLUSTERS)
		return _get_cluster_clk_and_freq_table(cpu_dev);

	if (atomic_inc_return(&cluster_usage[MAX_CLUSTERS]) != 1)
		return 0;

	/*
	 * Get data for all clusters and fill virtual cluster with a merge of
	 * both
	 */
	for (i = 0; i < MAX_CLUSTERS; i++) {
		struct device *cdev = get_cpu_device(i);
		if (!cdev) {
			pr_err("%s: failed to get cpu%d device\n", __func__, i);
			return -ENODEV;
		}

		ret = _get_cluster_clk_and_freq_table(cdev);
		if (ret)
			goto put_clusters;
	}

	ret = merge_cluster_tables();
	if (ret)
		goto put_clusters;

	/* Assuming 2 cluster, set clk_big_min and clk_little_max */
	clk_big_min = get_table_min(freq_table[0]);
        /*lint -e666*/
	clk_little_max = VIRT_FREQ(1, get_table_max(freq_table[1]));
        /*lint +e666*/

	pr_debug("%s: cluster: %d, clk_big_min: %d, clk_little_max: %d\n",
			__func__, cluster, clk_big_min, clk_little_max);

	return 0;

put_clusters:
	while (i--) {
		struct device *cdev = get_cpu_device(i);
		if (!cdev) {
			pr_err("%s: failed to get cpu%d device\n", __func__, i);
			ret = -ENODEV;
		} else {
			_put_cluster_clk_and_freq_table(cdev);
		}
	}

	atomic_dec(&cluster_usage[MAX_CLUSTERS]);

	return ret;
}

static int bL_cpufreq_suspend(struct cpufreq_policy *policy)
{
	u32 cur_cluster = cpu_to_cluster(policy->cpu);
	cpufreq_suspended[cur_cluster] = true;

	return 0;
}

static int bL_cpufreq_resume(struct cpufreq_policy *policy)
{
	u32 cur_cluster = cpu_to_cluster(policy->cpu);
	cpufreq_suspended[cur_cluster] = false;

	return 0;
}

/* Per-CPU initialization */
static int bL_cpufreq_init(struct cpufreq_policy *policy)
{
	u32 cur_cluster = cpu_to_cluster(policy->cpu);
	struct device *cpu_dev;
	int ret;

	cpu_dev = get_cpu_device(policy->cpu);
	if (!cpu_dev) {
		pr_err("%s: failed to get cpu%d device\n", __func__,
				policy->cpu);
		return -ENODEV;
	}

	ret = get_cluster_clk_and_freq_table(cpu_dev);
	if (ret)
		return ret;

	ret = cpufreq_frequency_table_cpuinfo(policy, freq_table[cur_cluster]);
	if (ret) {
		dev_err(cpu_dev, "CPU %d, cluster: %d invalid freq table\n",
				policy->cpu, cur_cluster);
		put_cluster_clk_and_freq_table(cpu_dev);
		return ret;
	}

	cpufreq_frequency_table_get_attr(freq_table[cur_cluster], policy->cpu);

	if (cur_cluster < MAX_CLUSTERS) {
		int cpu;

		cpumask_copy(policy->cpus, topology_core_cpumask(policy->cpu));

		for_each_cpu(cpu, policy->cpus)
			per_cpu(physical_cluster, cpu) = cur_cluster;
	} else {
		/* Assumption: during init, we are always running on A15 */
		per_cpu(physical_cluster, policy->cpu) = A15_CLUSTER;
	}

	if (arm_bL_ops->get_transition_latency)
		policy->cpuinfo.transition_latency =
			arm_bL_ops->get_transition_latency(cpu_dev);
	else
		policy->cpuinfo.transition_latency = CPUFREQ_ETERNAL;

	policy->cur = clk_get_cpu_rate(policy->cpu);

	if (is_bL_switching_enabled())
		per_cpu(cpu_last_req_freq, policy->cpu) = policy->cur;

	dev_info(cpu_dev, "%s: CPU %d initialized\n", __func__, policy->cpu);
	return 0;
}

/* Export freq_table to sysfs */
static struct freq_attr *bL_cpufreq_attr[] = {
	&cpufreq_freq_attr_scaling_available_freqs,
	NULL,
};

static struct cpufreq_driver bL_cpufreq_driver = {
	.name			= "arm-big-little",
	.flags			= CPUFREQ_STICKY,
	.verify			= bL_cpufreq_verify_policy,
	.target			= bL_cpufreq_set_target,
	.get			= bL_cpufreq_get_rate,
	.init			= bL_cpufreq_init,
	.suspend		= bL_cpufreq_suspend,
	.resume			= bL_cpufreq_resume,
	.have_governor_per_policy = true,
	.attr			= bL_cpufreq_attr,
};

static int bL_cpufreq_switcher_notifier(struct notifier_block *nfb,
					unsigned long action, void *_arg)
{
	pr_debug("%s: action: %ld\n", __func__, action);

	switch (action) {
	case BL_NOTIFY_PRE_ENABLE:
	case BL_NOTIFY_PRE_DISABLE:
		cpufreq_unregister_driver(&bL_cpufreq_driver);
		break;

	case BL_NOTIFY_POST_ENABLE:
		set_switching_enabled(true);
		cpufreq_register_driver(&bL_cpufreq_driver);
		break;

	case BL_NOTIFY_POST_DISABLE:
		set_switching_enabled(false);
		cpufreq_register_driver(&bL_cpufreq_driver);
		break;

	default:
		pr_err("%s: unexpected action%d\n", __func__, action);
		return NOTIFY_DONE;
	}

	return NOTIFY_OK;
}

static struct notifier_block bL_switcher_notifier = {
	.notifier_call = bL_cpufreq_switcher_notifier,
};

int bL_cpufreq_register(struct cpufreq_arm_bL_ops *ops)
{
	int ret, i;
#ifdef CONFIG_HISI_CPUFREQ_WITH_HOTPLUG
	struct sched_param param = { .sched_priority = MAX_RT_PRIO-1 };
#endif
	if (arm_bL_ops) {
		pr_debug("%s: Already registered: %s, exiting\n", __func__,
				arm_bL_ops->name);
		return -EBUSY;
	}

	if (!ops || !strlen(ops->name) || !ops->init_opp_table) {
		pr_err("%s: Invalid arm_bL_ops, exiting\n", __func__);
		return -ENODEV;
	}

	arm_bL_ops = ops;

	ret = bL_switcher_get_enabled();
	set_switching_enabled(ret);

	for (i = 0; i < MAX_CLUSTERS; i++) {
		mutex_init(&cluster_lock[i]);
		cpufreq_suspended[i] = false;
	}

	ret = cpufreq_register_driver(&bL_cpufreq_driver);
	if (ret) {
		pr_info("%s: Failed registering platform driver: %s, err: %d\n",
				__func__, ops->name, ret);
		arm_bL_ops = NULL;
	} else {
		ret = bL_switcher_register_notifier(&bL_switcher_notifier);
		if (ret) {
			cpufreq_unregister_driver(&bL_cpufreq_driver);
			arm_bL_ops = NULL;
		} else {
#ifdef CONFIG_HISI_CPUFREQ_WITH_HOTPLUG
			hotplugged_by_cpufreq = false;
			hotplug_up = false;
			hotplug_down = false;
			hotplug_task = kthread_create(cpufreq_bL_hotplug_task, NULL, "bLhotplug");
			if (IS_ERR(hotplug_task)) {
				pr_err("%s: hotplug task create fail\n", __func__);
				ret = PTR_ERR(hotplug_task);
			} else {
				sched_setscheduler_nocheck(hotplug_task, SCHED_FIFO, &param);
				get_task_struct(hotplug_task);

				/* NB: wake up so the thread does not look hung to the freezer */
				wake_up_process(hotplug_task);
			}
#endif
			pr_info("%s: Registered platform driver: %s\n",
					__func__, ops->name);
		}
	}

	bL_switcher_put_enabled();
	return ret;
}
EXPORT_SYMBOL_GPL(bL_cpufreq_register);

void bL_cpufreq_unregister(struct cpufreq_arm_bL_ops *ops)
{
	if (arm_bL_ops != ops) {
		pr_err("%s: Registered with: %s, can't unregister, exiting\n",
				__func__, arm_bL_ops->name);
		return;
	}

	bL_switcher_get_enabled();
#ifdef CONFIG_HISI_CPUFREQ_WITH_HOTPLUG
	kthread_stop(hotplug_task);
	put_task_struct(hotplug_task);
#endif
	bL_switcher_unregister_notifier(&bL_switcher_notifier);
	cpufreq_unregister_driver(&bL_cpufreq_driver);
	bL_switcher_put_enabled();
	pr_info("%s: Un-registered platform driver: %s\n", __func__,
			arm_bL_ops->name);

	/* For saving table get/put on every cpu in/out */
	if (is_bL_switching_enabled()) {
		put_cluster_clk_and_freq_table(get_cpu_device(0));
	} else {
		int i;

		for (i = 0; i < MAX_CLUSTERS; i++) {
			struct device *cdev = get_cpu_device(i);
			if (!cdev) {
				pr_err("%s: failed to get cpu%d device\n",
						__func__, i);
				return;
			}

			put_cluster_clk_and_freq_table(cdev);
		}
	}

	arm_bL_ops = NULL;
}
EXPORT_SYMBOL_GPL(bL_cpufreq_unregister);
