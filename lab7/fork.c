#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int a = 325;

int main(void)
{
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("child pid %d\n", getpid());
        printf("child (a) - %d\n", a);
        printf("child (a) - %p\n", &a);

        getchar();

        a++;

        printf("updated child (a) - %d\n", a);
        printf("updated child (a) - %p\n", &a);

        getchar();

        printf("stopping child\n");
        exit(0);
    } else if (pid > 0) {
        printf("parent pid %d\n", getpid());
        printf("parent (a) - %d\n", a);
        printf("parent (a) - %p\n", &a);

        getchar();

        a++;

        printf("updated parent (a) - %d\n", a);
        printf("updated parent (a) - %p\n", &a);

        wait(NULL);
        printf("stopping parent\n");
    } else {
        // error
        exit(1);
    }
}
