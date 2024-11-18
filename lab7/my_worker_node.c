#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) {
    int worker_id = atoi(argv[1]);

    printf("[worker %d] started...\n", worker_id);

    srand(time(NULL) + worker_id);

    int steps = rand() % 10;
    printf("[worker %d] %d steps to do\n", worker_id, steps);

    while (steps--) {
        sleep(2);
        printf("[worker %d] process smth\n", worker_id);
    }

    return 0;
}
