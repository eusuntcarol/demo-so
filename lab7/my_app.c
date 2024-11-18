#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("server started...\n");

    while(1) {
        sleep(1);
        printf("doing server stuff...\n");
    }

    return 0;
}
