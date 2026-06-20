#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>
#include <linux/cred.h>
#include <linux/uidgid.h>
#include <linux/module.h>
#include <linux/list.h>

static const struct task_struct module_target_data = { .flags = 42 };

static int __init taskinfo_init(void)
{
    struct task_struct *p;

    pr_info("taskinfo: loaded\n");
    pr_info("    offsetof(task_struct, pid)=%zu\n", offsetof(struct task_struct, pid));
    pr_info("    offsetof(task_struct, tgid)=%zu\n", offsetof(struct task_struct, tgid));
    pr_info("    offsetof(task_struct, cred)=%zu\n", offsetof(struct task_struct, cred));
    pr_info("    offsetof(task_struct, real_parent)=%zu\n", offsetof(struct task_struct, real_parent));
    pr_info("    offsetof(task_struct, comm)=%zu\n", offsetof(struct task_struct, comm));
    pr_info("    offsetof(task_struct, __state)=%zu\n", offsetof(struct task_struct, __state));
    pr_info("    offsetof(task_struct, flags)=%zu\n", offsetof(struct task_struct, flags));
    pr_info("    offsetof(task_struct, prio)=%zu\n", offsetof(struct task_struct, prio));
    pr_info("    offsetof(task_struct, policy)=%zu\n", offsetof(struct task_struct, policy));

    pr_info("datapin flags value is %u (should be 42)\n", module_target_data.flags);

    pr_info("=== Task List ===\n");

    rcu_read_lock();

    for_each_process(p) {
        const struct cred *cred;
        struct task_struct *parent;

        cred = rcu_dereference(p->cred);
        parent = rcu_dereference(p->real_parent);

        pr_info("task: pid=%d tgid=%d ppid=%d uid=%u gid=%u comm=%s state=%u flags=0x%x prio=%d policy=%u\n",
                p->pid,
                p->tgid,
                parent ? parent->tgid : -1,
                __kuid_val(cred->uid),
                __kgid_val(cred->gid),
                p->comm,
                READ_ONCE(p->__state),
                p->flags,
                p->prio,
                p->policy);
    }

    rcu_read_unlock();

    return 0;
}

static void __exit taskinfo_exit(void)
{
    pr_info("taskinfo: unloaded\n");
}

module_init(taskinfo_init);
module_exit(taskinfo_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("List modules and tasks (task_struct stress)");
