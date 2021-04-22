#include "types.h"
#include "user.h"
#include "thread.h"

void level4(void *a, void *b) {
   printf(1, "Thread Killed\n");
   pthread_kill(pthread_self());
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
   printf(1, "%s%s\n\n", (char *)a, (char *)b);
   int pid = pthread_create((void *)&level1, c, d);
   pthread_join(pid);
   exit();
}



int main(int argc, char *argv[]) {
   int pid;
   char a[20] = "I am in Level 1";
   char b[20] = " Testing Function";
   printf(1, "\nLevel 1 Testing, Testing Clone and Join\n................\n");
   pid = pthread_create((void *)&level1, a, b);
   pthread_join(pid);

   printf(1, "\nLevel 2 Testing, Stress Testing\n....................\n");
   strcpy(a, "I am in Level 2");
   int threadid[3], i;
   for(i = 0; i < 3; i++) {
      threadid[i] = pthread_create((void *)&level1, a, b);
   }
   for(i = 0; i < 3; i++)
      pthread_join(threadid[i]);

   printf(1, "\nLevel 3 Testing, clone calling clone\n....................\n");
   strcpy(a, "I am in Level 3");
   pid = pthread_create((void *)&level3, a, b);
   pthread_join(pid);

   printf(1, "\nLevel 4 Testing, pthread_self and pthread_kill\n....................\n");
   pid = pthread_create((void *)&level4, a, b);
   pthread_join(pid);
   exit();
}