#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void perform_ls(char *dir) {
    printf("child preparing exec...\n");

    char *const argv[] = {"ls", "-l", dir, NULL};
    execvp(argv[0], argv);
}

void perform_cat(char *dir) {
    printf("child preparing exec...\n");

    char *const argv[] = {"cat", dir, NULL};
    execvp(argv[0], argv);
}

void perform_my_app() {
    char *const argv[] = {"./my_app", NULL};
    execvp(argv[0], argv);
}

int main(int argc, char *argv[])
{
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("child: pid %d\n\n", getpid());

        switch (atoi(argv[1])) {
            case 1:
                perform_ls(argv[2]);
            case 2:
                perform_cat(argv[2]);
            case 3:
                perform_my_app();
            default:
                printf("child: unknown app to exec\n");
        }

        exit(0);
    } else if (pid > 0) {
        printf("parent: waiting for child...\n");

        wait(NULL);

        printf("parent: stopping\n");
    } else {
        // error
        exit(1);
    }
}
