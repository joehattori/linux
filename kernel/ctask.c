#include <linux/sched.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(ctask_start)
{
	return ctask_start();
}

SYSCALL_DEFINE1(ctask_end, unsigned int, ctask_id)
{
	return ctask_end(ctask_id);
}
