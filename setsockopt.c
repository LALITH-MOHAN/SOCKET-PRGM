#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080  // Define port

int main() {
    int socketfd, new_socket;
    struct sockaddr_in addr, client_addr;
    socklen_t addrlen = sizeof(client_addr);
    int optval = 1;

    // Create socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set socket option to reuse address
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        perror("setsockopt failed");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    // Initialize address structure
    addr.sin_family = AF_INET; 
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    // Bind socket
    if (bind(socketfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Binding failed");
        close(socketfd);
        exit(EXIT_FAILURE);
    }
    printf("Binding successful.\n");

    // Listen for incoming connections
    if (listen(socketfd, 5) < 0) {
        perror("Listening failed");
        close(socketfd);
        exit(EXIT_FAILURE);
    }
    printf("Listening on port %d...\n", PORT);

    while (1) {
        // Accept incoming connection
        new_socket = accept(socketfd, (struct sockaddr *)&client_addr, &addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        printf("Connection accepted from %s:%d\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Close client socket
        close(new_socket);
    }

    // Close server socket
    close(socketfd);

    return 0;
}
