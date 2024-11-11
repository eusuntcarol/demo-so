#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void)
{
    pid_t pid;
    pid_t ppid;
    pid_t my_pid;

    printf("Test - \n");

    pid = fork();

    if (pid == 0) {
        // child
        sleep(20);

        ppid   = getppid();
        my_pid = getpid();

        printf("child,  child pid %5d, my pid %5d, ppid %5d\n", pid, my_pid, ppid);

        exit(0);
    } else if (pid > 0) {
        //parent
        ppid   = getppid();
        my_pid = getpid();

        printf("parent, child pid %5d, my pid %5d, ppid %5d\n", pid, my_pid, ppid);

        // wait(NULL);
    } else {
        // error
        exit(1);
    }
}
