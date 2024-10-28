#include <stdlib.h>

#define SIZE 64

int main(void) {
    int *p = malloc(sizeof(int) * SIZE);

    free(p);

    return 0;
}
