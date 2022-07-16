#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>
#include <linux/cgroup.h>

asmlinkage long __x64_sys_ctask_start(void)
{
	u64 now = ktime_get_real_fast_ns();
	struct task_struct *p = current;
	p->ctask_start_ns = now;
	return 0;
}

asmlinkage long __x64_sys_ctask_end(void)
{
	u64 now = ktime_get_real_fast_ns();
	struct task_struct *p = current;
	u64 elapsed_time = now - p->ctask_start_ns;
	record_ctask_latency(elapsed_time);
	return 0;
}
