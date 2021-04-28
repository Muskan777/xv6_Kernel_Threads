#define CLONE_THREAD 1
#define CLONE_VM     2
#define CLONE_FS     4
#define CLONE_PARENT 8
#define CLONE_FILE   16

int pthread_create(void(*)(void *, void *), void *, void *, int);
int pthread_join(int);
int pthread_self();
int pthread_equal();
int pthread_kill(int, int, int);

typedef struct thread {
    int tid;
    char *stack;
}thread;