int pthread_create(void(*)(void *, void *), void *, void *);
int pthread_join(int);
int pthread_self();
int pthread_equal();
int pthread_kill(int);