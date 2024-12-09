#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    char *myfifo = "./myfifo";
    char arr1[100] = { 0 };
    int fd, ret;

    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_RDONLY);

    if (fd < 0) {
        perror("Error opening FIFO for write");
        return 1;
    }

    int i = 0;
    do {
        ret = read(fd, &arr1[i], 1);

        if (ret == 0) break;
    } while (arr1[i++] != '\0');

    printf("Received message: %s", arr1);

    close(fd);

    return 0;
}
