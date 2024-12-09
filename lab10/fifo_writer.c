#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    char *myfifo = "./myfifo";
    char arr1[100] = { 0 };
    int fd;

    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_WRONLY);

    if (fd < 0) {
        perror("Error opening FIFO for write");
        return 1;
    }

    printf("Enter message: ");
    fgets(arr1, 99, stdin);

    write(fd, arr1, strlen(arr1) + 1);

    close(fd);

    return 0;
}
