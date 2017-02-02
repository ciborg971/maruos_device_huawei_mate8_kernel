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
#include <linux/jiffies.h>
#include <linux/workqueue.h>

#define SECONDS 3

static void dump_meminfo_wk(struct work_struct *work);
static unsigned long long before_jiffies = 0;
static DECLARE_WORK(lowmem_dbg_wk, dump_meminfo_wk);

static const char state_to_char[] = TASK_STATE_TO_CHAR_STR;

static int task_state_char(unsigned long state)
{
	int bit = state ? __ffs(state) + 1 : 0;

	return bit < sizeof(state_to_char) - 1 ? state_to_char[bit] : '?';
}

static void dump_tasks(void)
{
	struct task_struct *p;
	struct task_struct *task;

	pr_info("[ pid ] uid tgid total_vm rss nr_ptes swapents oom_score_adj s name\n");
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

		pr_info("[%5d] %5d %5d %8lu %8lu %7lu %8lu %5hd %c %s\n",
			task->pid, from_kuid(&init_user_ns, task_uid(task)),
			task->tgid, task->mm->total_vm, get_mm_rss(task->mm),
			task->mm->nr_ptes,
			get_mm_counter(task->mm, MM_SWAPENTS),
			task->signal->oom_score_adj,
			task_state_char(task->state),
			task->comm);
		task_unlock(task);
	}
	rcu_read_unlock();
}

static void dump_meminfo_wk(struct work_struct *work)
{
	before_jiffies = get_jiffies_64();
	show_mem(SHOW_MEM_FILTER_NODES);
	dump_tasks();
}

void lowmem_dbg(void)
{
	unsigned long long now_jiffies = get_jiffies_64();
	if (time_after64(now_jiffies, (before_jiffies + SECONDS * HZ))) {
		schedule_work(&lowmem_dbg_wk);
	}

	return;
}

EXPORT_SYMBOL(lowmem_dbg);
