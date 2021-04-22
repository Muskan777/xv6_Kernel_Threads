#include "types.h"
#include "user.h"
#include "x86.h"
#include "thread.h"
#include "param.h"


int pthread_create(void(*fcn)(void *, void *), void *arg1, void *arg2) {
    void *stack = malloc(4096);
    int pid = clone((void *)fcn, (void *)arg1, (void *)arg2,(void *) stack);
    if ( pid < 0 ) {
         printf(1, "ERROR: Unable to create the child process.\n");
         exit();
    }
    sleep(2);
    free(stack);
    return pid;
}

int pthread_join(int threadid) {
    int pid = join(threadid);
    return pid;
}

int pthread_self() {
    return getpid();
}

int pthread_equal(int pid1, int pid2) {
    return pid1 == pid2;
}

int pthread_kill(int pid) {
    kill(pid);
    return pid;
}