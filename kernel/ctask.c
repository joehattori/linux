#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/cgroup.h>

asmlinkage long __x64_sys_ctask_start(void)
{
	struct task_struct *p = current;
	p->se.ctask_start_ns = ktime_get_real_fast_ns();
	return 0;
}

asmlinkage long __x64_sys_ctask_end(void)
{
	record_ctask_latency();
	return 0;
}
