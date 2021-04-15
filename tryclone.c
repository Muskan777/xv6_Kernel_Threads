#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"



void fcn(void *a, void *b) {
   printf(1, "In function\n");
   printf(1, "\nA is - ");
   printf(1, "%d", (int)a);
   printf(1, "\nB is - ");
   printf(1, "%s\n", (char *)b);
   exit();
}

int main(int argc, char *argv[]) {
    int a = 2;
    char b[10] = "Manish";
    for(int i = 0; i < 6; i++) {
        void *pchild_stack = malloc(4096);
        if (!pchild_stack) {
            printf(1, "Malloc Failed");
            exit();
        }
        int pid = clone(&fcn, (void *)a, (void *)b, pchild_stack);
        join(pid);
        printf(1, "PID is %d   \n", pid);
        if ( pid < 0 ) {
            printf(1, "ERROR: Unable to create the child process.\n");
            exit();
        }
        free(pchild_stack);

        printf(1, "INFO: Child process terminated.\n");
    }
    
    exit();
}