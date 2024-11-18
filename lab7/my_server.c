#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    printf("[server] started...\n");

    pid_t pids[3] = { 0 };

    for (int i = 0; i < 3; ++i) {
        pid_t pid = fork();

        pids[i] = pid;

        if (pid == 0) {
            char buff[20] = { 0 };
            sprintf(buff, "%d", i);

            char *const argv[] = {"./my_worker_node", buff, NULL};
            execvp(argv[0], argv);
        } else {
            printf("[server] worker %d created\n", i);
        }
    }

    for (int i = 0; i < 3; ++i) {
        int status;
        pid_t pid = waitpid(pids[i], &status, 0);
        printf("[server] worker %d (pid %d) exited with status %d\n", i, pid, status);
    }

    return 0;
}
