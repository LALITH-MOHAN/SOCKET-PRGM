#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024  // Increased buffer size

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("SOCKET CREATION FAILED");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("CONNECTION FAILED");
        exit(EXIT_FAILURE);
    }

    printf("CONNECTED TO SERVER. ENTER LINES OF TEXT (type 'exit' to quit):\n");

    char buffer[BUFFER_SIZE];
    while (1) {
        printf("> ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
    
        send(client_fd, buffer, strlen(buffer), 0);
    
        // break if exit.
        if (strcmp(buffer, "exit") == 0) 
        {
            break;
        }
    }

    // Receive server acknowledgment
    char response[1024];  
    int len = recv(client_fd, response, sizeof(response) - 1, 0);
    if (len > 0) {
        response[len] = '\0';
        printf("SERVER RESPONSE: %s\n", response);
    } else {
        perror("RECEIVE FAILED");
    }

    close(client_fd);
    return 0;
}
