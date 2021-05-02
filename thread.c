#include "types.h"
#include "user.h"
#include "x86.h"
#include "thread.h"
#include "param.h"

thread th[120];
int i = 0;

int pthread_create(void(*fcn)(void *, void *), void *arg1, void *arg2, int flags) {
    void *stack = malloc(4096);
    int pid = clone((void *)fcn, (void *)arg1, (void *)arg2, (void *) stack, flags);
    if ( pid < 0 ) {
        return pid;
    }
    th[i].tid = pid;
    th[i++].stack = stack;
    sleep(2);
    //free(stack);
    return pid;
}

int pthread_join(int threadid) {
    int pid = join(threadid);
    int j;
    for(j = 0; j< i; j++) {
        if (th[j].tid == pid) {
            free(th[j].stack);
            break;
        }
    }
    for(; j < i - 1; j++) {
        th[j].tid = th[j+1].tid;
        th[j].stack = th[j+1].stack;
    }
    i--;
    return pid;
}

int pthread_self() {
    return getpid();
}

int pthread_equal(int pid1, int pid2) {
    return pid1 == pid2;
}

int pthread_kill(int tgid, int tid, int signal) {
    tgkill(tgid, tid, signal);
    return tid;
}

int pthread_gettid() {
    return gettid();
}
