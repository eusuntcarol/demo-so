#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SOCKET_PATH "./unix_socket"
#define BUFFER_SIZE 100
#define MAX_CONNECTIONS 5

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;

    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    unlink(SOCKET_PATH);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        exit(1);
    }

    if (listen(server_fd, MAX_CONNECTIONS) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(1);
    }
    printf("Server listening on %s\n", SOCKET_PATH);

    int clients[MAX_CONNECTIONS];

    for (int i = 0; i < MAX_CONNECTIONS; i++) { 
        clients[i] = -1;
    }

    while (1) {
        client_len = sizeof(client_addr);
	printf("Waiting for a connection...\n");
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

	for (int i = 0; i < MAX_CONNECTIONS; i++) {
	    if (clients[i] == client_fd) break;

            if (clients[i] == -1) {
                clients[i] = client_fd;
		break;
	    }
        }

        if (client_fd == -1) {
            perror("accept failed");
            close(server_fd);
            exit(1);
        }
        printf("Client connected.\n");

        for (int i = 0; i < MAX_CONNECTIONS; i++) {
	    if (clients[i] == -1) {
		continue;
	    }

            memset(buffer, 0, BUFFER_SIZE);

            ssize_t bytes_read = read(clients[i], buffer, BUFFER_SIZE - 1);

            if (bytes_read <= 0) {
                printf("Client disconnected.\n");
		close(clients[i]);
		clients[i] = -1;
                break;
            }
            printf("Received (from %d): %s\n", clients[i], buffer);
            write(clients[i], buffer, strlen(buffer));
        }
    }

    close(server_fd);
    unlink(SOCKET_PATH);
    return 0;
}
