#include "types.h"
#include "user.h"
#include "thread.h"

int matC[4][4], row1 = 4, col1 = 4, row2 = 4, col2 = 4, divi = -1;

int matA[4][4] = { { 1, 1, 1, 1 },
                       { 2, 2, 2, 2 },
                       { 3, 3, 3, 3 }, 
                       { 4, 4, 4, 4 } };

int matB[4][4] = { { 1, 1, 1, 1 },
                       { 2, 2, 2, 2 },
                       { 3, 3, 3, 3 },
                       { 4, 4, 4, 4 } };

void mult1(void *a, void *b) {
    int i, j, k;
    divi++;
    for(i = (divi)*row1/3; i < (divi+1)*row1/3; i++) {
        for(j = 0; j < col2; j++) {
            matC[i][j] = 0;
            for(k = 0; k < col1; k++) {
                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
    exit();
}

void level4(void *a, void *b) {
   printf(1, "Thread Killed\n");
   pthread_kill(getpid(), gettid(), 2);
   printf(1, "%s%s\n\n", (char *)a, (char *)b);
   exit();
}

void level1(void *a, void *b) {
   printf(1, "%s%s\n\n", (char *)a, (char *)b);
   exit();
}

void level3(void *a, void *b) {
   char c[20] = "Clone Calling ";
   char d[20] = "Clone";
   int flags = CLONE_VM;
   printf(1, "%s%s\n\n", (char *)a, (char *)b);
   int pid = pthread_create((void *)&level1, c, d, flags);
   pthread_join(pid);
   exit();
}


void level5(void *a, void *b) {
    char *lstest[] = {"ls"};
   int pid = fork();
   if (pid < 0) {
      printf(1, "fork failed\n");
   }
   if (pid == 0) {
      printf(1, "child process\n");
      exec("ls", lstest);
   }
   else {
      printf(1, "parent process\n");
      wait();
   }
   exit();
}

int main(int argc, char *argv[]) {
   int flag = CLONE_VM;
   char a[20] = "I am in Level 1";
   char b[20] = " Testing Function";
   printf(1, "\nLevel 1 Testing, Testing Clone and Join with no flag\n................\n");
   int pid = pthread_create((void *)&level1, a, b, flag);
   pthread_join(pid);
   printf(1, "in parent\n\n");


   printf(1, "\nLevel 1 Testing, Testing Clone and Join with CLONE_VM flag\n................\n");
   flag = CLONE_VM;
   pid = pthread_create((void *)&level1, a, b, flag);
   pthread_join(pid);

   printf(1, "\nLevel 1 Testing, Testing Clone and Join with CLONE_THREAD flag\n................\n");
   flag = CLONE_THREAD;
   pid = pthread_create((void *)&level1, a, b, flag);
   pthread_join(pid);

   printf(1, "\nLevel 1 Testing, Testing Clone and Join with CLONE_THREAD and CLONE_VM flag\n................\n");
   flag = CLONE_THREAD | CLONE_VM;
   pid = pthread_create((void *)&level1, a, b, flag);
   pthread_join(pid);


   printf(1, "\nMatrix Multiplication\n........................\n");
   int threadid[100];
   for(int i = 0; i < 3; i++)
      threadid[i] = pthread_create((void *)&mult1, a, b, flag);

   for(int i = 0; i < 3; i++)
      pthread_join(threadid[i]);

   for(int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            printf(1, "%d ", matC[i][j]);
        }
        printf(1, "\n");
    }
   
   printf(1, "\nLevel 2 Testing, Stress Testing\n....................\n");
   strcpy(a, "I am in Level 2");
   int  i;
   for(i = 0; i < 60; i++) {
      threadid[i] = pthread_create((void *)&level1, a, b, flag);
   }
   for(i = 0; i < 60; i++)
      pthread_join(threadid[i]);


   printf(1, "\nLevel 3 Testing, clone calling clone\n....................\n");
   strcpy(a, "I am in Level 3");
   pid = pthread_create((void *)&level3, a, b, flag);
   pthread_join(pid);

   printf(1, "\nLevel 4 Testing, pthread_self and pthread_kill\n....................\n");
   pid = pthread_create((void *)&level4, a, b, flag);
   pthread_join(pid);

   printf(1, "\nLevel 5 Testing, Fork Exec in Thread\n.............................\n");
   pid = pthread_create((void *)&level5, a, b, flag);
   pthread_join(pid);

   exit();
}