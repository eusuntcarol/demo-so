#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DUP

int main(void)
{
	int fd1, fd2, fd3, fd4, fd5;

	fd1 = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0640);
	printf("fd1 = %d\n", fd1);

	fd2 = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0640);
	printf("fd2 = %d\n", fd2);

	fd3 = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0640);
	printf("fd3 = %d\n", fd3);

    write(fd1, "hi\n", 3);

    // lseek(fd2, 0, SEEK_END);
    write(fd2, "there\n", 6);

    // lseek(fd3, 0, SEEK_END);
    write(fd3, "fds\n", 4);

    // return 0;

	close(fd2);

	fd4 = open("file2.txt", O_RDWR | O_CREAT | O_TRUNC, 0640);
	printf("fd4 = %d\n", fd4);

	fd5 = dup(fd4);
	printf("fd5 = %d\n", fd5);

	// STDOUT
	write(1, "Test fd\n", 8);	

#ifdef DUP
	close(1);
	dup(fd4);
	printf("Test dup after redirect\n");
#elif defined(DUP2)
	// we want that our oldfd (fd4) to point to the newfd (1)
	dup2(fd4, 1);
	printf("Test dup2 after redirect\n");
#endif

	printf("Test fd after redirect\n");

	close(fd1);
	close(fd3);
	close(fd4);
	close(fd5);

	return 0;
}
