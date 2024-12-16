#include <sys/socket.h>
#include <sys/un.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SOCKET_PATH "./unix_socket"
#define BUFFER_SIZE 100
#define MAX_EVENTS 10

int main() {
    int server_fd, epoll_fd;
    struct sockaddr_un server_addr;
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

    if (listen(server_fd, 10) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(1);
    }
    printf("Server listening on %s\n", SOCKET_PATH);

    epoll_fd = epoll_create(MAX_EVENTS);
    if (epoll_fd == -1) {
        perror("epoll_create failed");
        close(server_fd);
        exit(1);
    }

    struct epoll_event ev, events[MAX_EVENTS];
    ev.events = EPOLLIN;
    ev.data.fd = server_fd;

    int clients[MAX_EVENTS];

    for (int i = 0; i < MAX_EVENTS; i++) {
    	clients[i] = -1;
    }

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) == -1) {
        perror("epoll_ctl: server_fd failed");
        close(server_fd);
        close(epoll_fd);
        exit(1);
    }

    while (1) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait failed");
            close(server_fd);
            close(epoll_fd);
            exit(1);
        }

        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == server_fd) {
                // accept new client connection
                struct sockaddr_un client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
		
		// add client_fd to the list of clients
		for (int i = 0; i < MAX_EVENTS; i++) {
		    if (clients[i] == -1) {
		        clients[i] = client_fd;
			break;
		    }
		}

                if (client_fd == -1) {
                    perror("Accept failed");
                    continue;
                }

                printf("Client connected.\n");
                ev.events = EPOLLIN;
                ev.data.fd = client_fd;

                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
                    perror("epoll_ctl: client_fd failed");
                    close(client_fd);
                    continue;
                }
            } else {
                // handle client data
                int client_fd = events[i].data.fd;
                memset(buffer, 0, BUFFER_SIZE);
                ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);

                if (bytes_read <= 0) {
                    printf("Client disconnected.\n");

	 	    // remove client_fd from the list of clients
                    for (int i = 0; i < MAX_EVENTS; i++) {
                        if (clients[i] == client_fd) {
                            clients[i] = -1;
                            break;
                        }
                    }

		    close(client_fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
                } else {
                    printf("Received (from %d): %s\n", client_fd, buffer);

		    for (int i = 0; i < MAX_EVENTS; i++) {
		    	if (clients[i] != -1) {
			    write(clients[i], buffer, strlen(buffer));
			}
		    }
                }
            }
        }
    }

    close(server_fd);
    close(epoll_fd);
    unlink(SOCKET_PATH);
    return 0;
}

