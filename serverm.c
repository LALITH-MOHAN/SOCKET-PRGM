#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 6

int main() 
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) 
    {
        perror("SOCKET CREATION FAILED");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int optval = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("BINDING FAILED");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        perror("LISTENING FAILED");
        exit(EXIT_FAILURE);
    }

    printf("LISTENING ON PORT %d...\n", PORT);

    socklen_t client_len = sizeof(client_addr);
    int newsocket = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (newsocket < 0) {
        perror("ACCEPT FAILED");
        exit(EXIT_FAILURE);
    }

    printf("CLIENT CONNECTED FROM: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    char buffer[BUFFER_SIZE];
    char *full_message = NULL;
    int total_received = 0;
    int len;

    while ((len = recv(newsocket, buffer, BUFFER_SIZE - 1, 0)) > 0) 
    {
        buffer[len] = '\0';
        char *temp = realloc(full_message, total_received + len + 1);
        if (!temp) 
        {
            perror("MEMORY ALLOCATION FAILED");
            free(full_message);
            close(newsocket);
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        full_message = temp;
        memcpy(full_message + total_received, buffer, len);
        total_received += len;

        if (strcmp(buffer, "exit") == 0) 
        {
            printf("CLIENT REQUESTED DISCONNECTION.\n");
            break;
        }
    }

    if (len < 0) 
    {
        perror("RECEIVE FAILED");
    } else 
    {
        // Remove "exit" if at the end
        int msg_len = strlen(full_message);
        if (msg_len >= 4 && strcmp(full_message + msg_len - 4, "exit") == 0) {
            full_message[msg_len - 4] = '\0';
        }

        printf("FULL MESSAGE FROM CLIENT: %s\n", full_message);
    }

    send(newsocket, "ALL DATA RECEIVED", 17, 0);

    free(full_message);
    close(newsocket);
    close(server_fd);
    return 0;
}
