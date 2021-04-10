#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"



void fcn(void *a, void *b) {
   printf(1, "In function\n");
   printf(1, "A is - ");
   printf(1, "%d", (int)a);
   printf(1, "B is - ");
   printf(1, "%s", (int)b);
}

int main(int argc, char *argv[]) {
    void *pchild_stack = malloc(4096*2);
    int a = 2;
    int b = 3;
    int pid = clone((void *)fcn, &a, (void *)b, pchild_stack);
    printf(1, "%d\n", pid);
    if ( pid < 0 ) {
        printf(1, "ERROR: Unable to create the child process.\n");
        exit();
   }

    wait();

    free(pchild_stack);

    printf(1, "INFO: Child process terminated.\n");
    exit();
}