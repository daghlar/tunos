#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/fs.h>

#include <linux/cred.h>
#include <linux/nsproxy.h>
#include <linux/mount.h>
#include <linux/pid_namespace.h>
#include <linux/sched/task.h>
#include <linux/slab.h>

#define MAX_PROFILES 8
#define MAX_APPS 128

#include <linux/seccomp.h>
#include <linux/filter.h>

static int disable_ipc_syscalls(void) {
    struct sock_filter filter[] = {
        BPF_STMT(BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, nr)),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_shmget, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_shmat, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_shmdt, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_shmctl, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_semget, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_semop, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_semctl, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_msgget, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_msgsnd, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_msgrcv, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_msgctl, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
    };
    struct sock_fprog prog = {
        .len = (unsigned short)(sizeof(filter)/sizeof(filter[0])),
        .filter = filter,
    };
    return seccomp(SECCOMP_SET_MODE_FILTER, 0, &prog);
}

static int sandbox_task(struct task_struct *task, int profile_id, int app_id) {
    kuid_t uid = KUIDT_INIT(10000 + profile_id * MAX_APPS + app_id);
    kgid_t gid = KGIDT_INIT(10000 + profile_id * MAX_APPS + app_id);
    struct cred *new_creds = prepare_creds();
    if (!new_creds)
        return -ENOMEM;
    new_creds->uid = uid;
    new_creds->gid = gid;
    new_creds->euid = uid;
    new_creds->egid = gid;
    new_creds->suid = uid;
    new_creds->sgid = gid;
    new_creds->fsuid = uid;
    new_creds->fsgid = gid;
    commit_creds(new_creds);
    set_fs(USER_DS);
    task->flags |= PF_NOFREEZE;
    unshare(CLONE_NEWUSER | CLONE_NEWNS | CLONE_NEWPID);
    kern_path("/appsandbox", LOOKUP_FOLLOW, &task->fs->root);
    return 0;
}

static int __init sandbox_init(void) {
    return 0;
}

static void __exit sandbox_exit(void) {}

module_init(sandbox_init);
module_exit(sandbox_exit);
MODULE_LICENSE("GPL"); 