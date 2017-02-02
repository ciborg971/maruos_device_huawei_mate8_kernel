/* drivers/misc/lowmemorykiller.c
 *
 * The lowmemorykiller driver lets user-space specify a set of memory thresholds
 * where processes with a range of oom_score_adj values will get killed. Specify
 * the minimum oom_score_adj values in
 * /sys/module/lowmemorykiller/parameters/adj and the number of free pages in
 * /sys/module/lowmemorykiller/parameters/minfree. Both files take a comma
 * separated list of numbers in ascending order.
 *
 * For example, write "0,8" to /sys/module/lowmemorykiller/parameters/adj and
 * "1024,4096" to /sys/module/lowmemorykiller/parameters/minfree to kill
 * processes with a oom_score_adj value of 8 or higher when the free memory
 * drops below 4096 pages and kill processes with a oom_score_adj value of 0 or
 * higher when the free memory drops below 1024 pages.
 *
 * The driver considers memory used for caches to be free, but if a large
 * percentage of the cached memory is locked this can be very inaccurate
 * and processes may not get killed until the normal oom killer is triggered.
 *
 * Copyright (C) 2007-2008 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/oom.h>
#include <linux/sched.h>
#include <linux/rcupdate.h>
#include <linux/notifier.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/swap.h>
#include <linux/fs.h>
#include <linux/freezer.h>
#include <linux/atomic.h>
#include <linux/kobject.h>

#define MULTIPLE_PREKILLER_DEPTH (20)
#define PER_PROCESS_TASK_SIZE    (60 << 20)
#define MAX_ALLOC_SIZE           (1200 << 20)
#define MULTIPLE_PREKILLER_LEVL  (100 << 20)
#define MIN_ADJ  (176)

static int lowmem_debug_level = 1;

#define MULTIPLE_PREKILLER_ATTR(_name) \
	static struct kobj_attribute _name##_attr = \
		__ATTR(_name, 0640, _name##_show, _name##_store)


#define lowmem_print(level, x...)			\
	do {						\
		if (lowmem_debug_level >= (level))	\
			pr_info(x);			\
	} while (0)


static int test_task_flag(struct task_struct *p, int flag)
{
        struct task_struct *t = p;

        do {
                task_lock(t);
                if (test_tsk_thread_flag(t, flag)) {
                        task_unlock(t);
                        return 1;
                }
                task_unlock(t);
        } while_each_thread(p, t);

        return 0;
}


static void dump_tasks(void)
{
	struct task_struct *p;
	struct task_struct *task;

	pr_info("[ pid ]   uid  tgid total_vm      rss nr_ptes swapents oom_score_adj name\n");
	rcu_read_lock();
	for_each_process(p) {
		task = find_lock_task_mm(p);
		if (!task) {
			/*
			 * This is a kthread or all of p's threads have already
			 * detached their mm's.  There's no need to report
			 * them; they can't be oom killed anyway.
			 */
			continue;
		}

		pr_info("[%5d] %5d %5d %8lu %8lu %7lu %8lu         %5hd %s\n",
			task->pid, from_kuid(&init_user_ns, task_uid(task)),
			task->tgid, task->mm->total_vm, get_mm_rss(task->mm),
			task->mm->nr_ptes,
			get_mm_counter(task->mm, MM_SWAPENTS),
			task->signal->oom_score_adj, task->comm);
		task_unlock(task);
	}
	rcu_read_unlock();
}

static void dump_meminfo(void)
{
	show_mem(SHOW_MEM_FILTER_NODES);
	dump_tasks();
}

static int multiple_prekiller(int alloc_depth, long *reclaim_size, int pid)
{
	int i;
	int depth;
	long tasksize;
	long freed_size = 0;
	short min_score_adj = MIN_ADJ;
	int all_selected = 0;
	int max_selected_idx = 0;
	struct task_struct *tsk = NULL;

	struct task_struct *selected[MULTIPLE_PREKILLER_DEPTH] = {NULL,};
	int selected_tasksize[MULTIPLE_PREKILLER_DEPTH] = {0,};
	int selected_score_adj[MULTIPLE_PREKILLER_DEPTH] = {OOM_ADJUST_MAX,};

	depth = alloc_depth <= MULTIPLE_PREKILLER_DEPTH ? alloc_depth : MULTIPLE_PREKILLER_DEPTH;

	if (depth <= 0) {
		return 0;
	}
	/* init all select_xxx array */
	for (i = 0; i < depth; i++){
		selected_score_adj[i] = min_score_adj;
		selected_tasksize[i] = 0;
		selected[i] = NULL;
	}

	rcu_read_lock();
	for_each_process(tsk) {
		struct task_struct *p;
		int oom_score_adj;
		int is_exist_task = 0;

		if (tsk->flags & PF_KTHREAD)
			continue;

		/* may be select task already is killed */
		if (test_task_flag(tsk, TIF_MEMDIE))
			continue;

		p = find_lock_task_mm(tsk);
		if (!p)
			continue;

		oom_score_adj = p->signal->oom_score_adj;
		if (oom_score_adj < min_score_adj) {
			task_unlock(p);
			continue;
		}

		tasksize = get_mm_rss(p->mm);
		task_unlock(p);
		if (tasksize <= 0)
			continue;

		if (p->pid == pid){
			continue;
		}

		if (all_selected < depth) {
			for (i = 0; i < depth; i++) {
				if (!selected[i]) {
					is_exist_task = 1;
					max_selected_idx = i;
					break;
				}
			}
		} else if (selected_score_adj[max_selected_idx] < oom_score_adj ||
			(selected_score_adj[max_selected_idx] == oom_score_adj &&
			selected_tasksize[max_selected_idx] < tasksize)) {
			is_exist_task = 1;
		}

		if (is_exist_task) {
			selected[max_selected_idx] = p;
			selected_tasksize[max_selected_idx] = tasksize;
			selected_score_adj[max_selected_idx] = oom_score_adj;

			if (all_selected < depth) {
				all_selected++;
			}
			else if (all_selected == depth) {
				for (i = 0; i < depth; i++) {
					if (selected_score_adj[i] < selected_score_adj[max_selected_idx])
						max_selected_idx = i;
					else if (selected_score_adj[i] == selected_score_adj[max_selected_idx] &&
						selected_tasksize[i] < selected_tasksize[max_selected_idx])
						max_selected_idx = i;
				}
			}

			lowmem_print(2, "prekill: max_selected_idx(%d) select %d (%s), adj %d, \
					size %ld, to kill\n",
				max_selected_idx, p->pid, p->comm, oom_score_adj, (tasksize * PAGE_SIZE));
		}
	}
	for (i = 0; i < depth; i++) {
		if (selected[i]) {
			lowmem_print(1, "prekill: send sigkill to %d (%s), adj %d,\
				     size %d\n",
				     selected[i]->pid, selected[i]->comm,
				     selected_score_adj[i],
				     selected_tasksize[i] * PAGE_SIZE);
			send_sig(SIGKILL, selected[i], 0);
			set_tsk_thread_flag(selected[i], TIF_MEMDIE);

			freed_size += (selected_tasksize[i] * PAGE_SIZE);
		}
	}
	*reclaim_size = freed_size;
	rcu_read_unlock();

	return !(all_selected < depth);
}


int sysctl_multiple_prekiller_handler(long size, int pid)
{
	int ret = 0;
	int free_page = 0;
	int file_page = 0;
	int kill_depth = 0;
	long avail_size= 0;
	long anon_size = 0;
	long alloc_size = 0;
	long need_size = 0;
	long reclaim_size = 0;
	struct shrink_control sc;

	alloc_size = size;

	/* calc per-zone free-memory file-cache anonmous-memory*/
	free_page = global_page_state(NR_FREE_PAGES);

	if (global_page_state(NR_SHMEM) + total_swapcache_pages() <
		global_page_state(NR_FILE_PAGES))
		file_page = global_page_state(NR_FILE_PAGES)
						- global_page_state(NR_SHMEM)
						- total_swapcache_pages();
	else
		file_page = 0;

	file_page = 0;

	//tune_lmk_param(&free_page, &file_page, &sc);

	anon_size = (global_page_state(NR_INACTIVE_ANON) + global_page_state(NR_ACTIVE_ANON)) * PAGE_SIZE;
	avail_size = (file_page + free_page) * PAGE_SIZE;

#if 0
	if (alloc_size > MAX_ALLOC_SIZE){
		lowmem_print(1, "alloc size %ld > %d\n", alloc_size, MAX_ALLOC_SIZE);
		alloc_size = MAX_ALLOC_SIZE;
	}

	if (anon_size + avail_size < alloc_size){
		dump_meminfo();
		return -1;
	}
#endif

	need_size = (alloc_size - avail_size);
	if (need_size < 0){
		lowmem_print(1, "prekill: need_size < 0\n");
		return 0;
	}

	//dump_tasks();

	/* according to the pressure and kill ? number processes */
	kill_depth = need_size/(PER_PROCESS_TASK_SIZE) + 1;
	lowmem_print(1,"kill_depth %ld\n", kill_depth);

	do {
		reclaim_size = 0;
		ret = multiple_prekiller(1, &reclaim_size, pid);
		need_size -= reclaim_size;
		lowmem_print(2,"need_size %ld reclaim_size %ld kill_depth %d\n",  need_size, reclaim_size, kill_depth);
	}
	while (ret && need_size > 0 && kill_depth--);

	return 0;
}

static ssize_t hisi_mul_prekiller_show(struct kobject *kobj,
				    struct kobj_attribute *attr, char *buf)
{
	return 0;
}

static ssize_t hisi_mul_prekiller_store(struct kobject *kobj,
				     struct kobj_attribute *attr,
				     const char *buf, size_t count)
{
	int flag = 0;
	long size;
	long pid = 0;
	char *pid_buf;
	char *tmp = buf;

	while(*tmp){
		if (*tmp == ',')
		{
			*tmp = '\0';
			flag = 1;
			break;
		}
		tmp++;
	}
	size = simple_strtol(buf, NULL, 10);
	if (flag){
		pid_buf = buf + strlen(buf) + 1;
		pid = simple_strtol(pid_buf, NULL, 10);
	}

	pr_info("%ld pid %d\n", size, pid);
	sysctl_multiple_prekiller_handler(size, pid);

	return count;
}

MULTIPLE_PREKILLER_ATTR(hisi_mul_prekiller);

static struct attribute *mul_prekiller_attrs[] = {
	&hisi_mul_prekiller_attr.attr,
	NULL,
};

static struct attribute_group mul_prekiller_attr_group = {
	.attrs = mul_prekiller_attrs,
	.name = "multiple_prekiller",
};

static int __init multipleprekiller_init(void)
{

	int err;
	err = sysfs_create_group(mm_kobj, &mul_prekiller_attr_group);
	if (err) {
		printk(KERN_ERR "multipleprekiller: register sysfs failed\n");
	}

	return 0;
}
module_init(multipleprekiller_init);
