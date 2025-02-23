#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("BINDING FAILED");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        perror("LISTENING FAILED");
        exit(EXIT_FAILURE);
    }

    printf("LISTENING...\n");

    int new_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (new_socket < 0) {
        perror("ACCEPT FAILED");
        exit(EXIT_FAILURE);
    }

    char buff[1024] = {0};  // Initialize buffer
    int bytes_received = recv(new_socket, buff, sizeof(buff) - 1, 0);
    
    if (bytes_received > 0) {
        buff[bytes_received] = '\0';  // Ensure string is null-terminated
        printf("Message from client: %s\n", buff);

        char response[] = "MESSAGE RECEIVED";
        send(new_socket, response, strlen(response), 0);  // Send only valid bytes
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
