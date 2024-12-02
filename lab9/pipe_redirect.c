#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void) {
    // pipe_fd[0] -> for reading
    // pipe_fd[1] -> for writing
    int pipe_fd[2];

    pipe(pipe_fd);      // Create the pipe

    int pid = fork();   // Fork to create a child process

    if (pid == 0) {
        // Child process
        printf("CHILD process wants to send something to the pipe\n");

        close(pipe_fd[0]);          // Close the read end

        dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);          // Close the write end since we have it duplicated on stdout

        // exec should be a better example
        printf("hi redirected");
    } else {
        // Parent process
        printf("PARENT process wants to read something from the pipe\n");

        char buf[BUFSIZ];

        close(pipe_fd[1]);          // Close the write end

        ssize_t n = read(pipe_fd[0], buf, sizeof(buf)); // Read data from the pipe into buf

        buf[n] = '\0';                                  // Null-terminate the received string
        printf("Parent received: %s\n", buf);           // Output the received message
    }

    return 0;
}
