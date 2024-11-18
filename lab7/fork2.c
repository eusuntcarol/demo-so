#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>


int main(void)
{
    pid_t pid;

    int *p = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED  | MAP_ANONYMOUS, -1, 0);
    int *q = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    p[0] = 1;
    q[0] = 1;

    pid = fork();

    if (pid == 0) {
        printf("child pid %d\n", getpid());
        printf("child (p[0]) - %d\n", p[0]);
        printf("child (p) - %p\n", p);
        printf("child (q[0]) - %d\n", q[0]);
        printf("child (q) - %p\n", q);

        getchar();

        p[0]++;
        q[0]++;

        printf("updated child (p) - %d\n", p[0]);
        printf("updated child (q) - %d\n", q[0]);

        getchar();

        printf("stopping child\n");
        exit(0);
    } else if (pid > 0) {
        printf("parent pid %d\n", getpid());
        printf("parent (p[0]) - %d\n", p[0]);
        printf("parent (p) - %p\n", p);
        printf("parent (q[0]) - %d\n", q[0]);
        printf("parent (q) - %p\n", q);

        getchar();

        p[0]++;
        q[0]++;

        printf("parent child (p) - %d\n", p[0]);
        printf("parent child (q) - %d\n", q[0]);

        wait(NULL);
        printf("stopping parent\n");
    } else {
        // error
        exit(1);
    }

    munmap(p, 4096);
    munmap(q, 4096);
}
