#include "sched.h"

#include <linux/cgroup.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/slab.h>

inline struct task_group *seq_file_tg(struct seq_file *s)
{
	struct cgroup_subsys_state *css = seq_css(s);
	return container_of(css, struct task_group, css);
}

u8 group_sched_policy(struct seq_file *s)
{
	struct task_group *tg = seq_file_tg(s);
	struct group_rq *grq = tg->grq;
	if (!grq)
		return 0;
	return grq->policy;
}

void set_group_sched_policy(struct seq_file *s, u8 policy)
{
	struct task_group *tg = seq_file_tg(s);
	if (!tg->grq) {
		tg->grq = kmalloc(sizeof(struct task_group), GFP_KERNEL);
		tg->grq->rt_rq = NULL;
	}
	tg->grq->policy = policy;
}

void free_group_sched(struct task_group *tg)
{
	struct group_rq *grq = tg->grq;
	if (grq) {
		struct rt_rq *rt_rq = grq->rt_rq;
		if (rt_rq)
			kfree(rt_rq);
		kfree(grq);
	}
}
