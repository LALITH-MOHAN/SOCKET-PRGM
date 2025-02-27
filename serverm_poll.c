#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MAX 6  
#define TIMEOUT 10000  // 10 seconds timeout

typedef struct 
{
    char *data;
    size_t size;
} ClientMessages;

int main() 
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    struct pollfd fds[MAX + 1]; 
    int client_ct = 0;
    char buff[1024];

    ClientMessages messages[MAX];
    for (int i = 0; i < MAX; i++) 
    {
        messages[i].data = NULL;
        messages[i].size = 0;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("BINDING FAILED");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX) < 0) {
        perror("LISTENING FAILED");
        exit(EXIT_FAILURE);
    }

    printf("LISTENING ON PORT: %d...\n", ntohs(server_addr.sin_port));

    // Initialize poll
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;
    for (int i = 1; i <= MAX; i++) 
    {
        fds[i].fd = -1;  // Initialize all client slots to -1
    }

    while (1) 
    {
        int activity = poll(fds, MAX + 1, TIMEOUT);
        
        if (activity == 0) 
        {  
            printf("NO NEW CLIENTS FOR 10 SECONDS. EXITING...\n");
            break;
        } else if (activity < 0) 
        {
            perror("POLL ERROR");
            exit(EXIT_FAILURE);
        }

        // Check for new client connection
        if (fds[0].revents & POLLIN) 
        {
            int new_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
            if (new_socket < 0) 
            {
                perror("ACCEPT FAILED");
                continue;
            }

            // Get client IP and port
            char client_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
            printf("NEW CLIENT CONNECTED: FD %d, IP: %s, PORT: %d\n", new_socket, client_ip, ntohs(client_addr.sin_port));

            // Add new client to poll list
            for (int i = 1; i <= MAX; i++) 
            {
                if (fds[i].fd == -1) 
                {
                    fds[i].fd = new_socket;
                    fds[i].events = POLLIN;
                    client_ct++;
                    break;
                }
            }
        }

        // Handle client messages
        for (int i = 1; i <= MAX; i++) 
        {
            int client_fd = fds[i].fd;
            if (client_fd > 0 && (fds[i].revents & POLLIN)) 
            {
                memset(buff, 0, sizeof(buff));
                int valread = recv(client_fd, buff, sizeof(buff) - 1, 0);
                
                if (valread <= 0) 
                {  // Client disconnected
                    printf("CLIENT DISCONNECTED: FD %d\n", client_fd);
                    close(client_fd);
                    fds[i].fd = -1;  
                    client_ct--;
                } else 
                {
                    buff[valread] = '\0';

                    // Dynamically append received message
                    size_t new_size = messages[i - 1].size + valread + 1;
                    char *new_data = realloc(messages[i - 1].data, new_size);
                    if (new_data) 
                    {
                        messages[i - 1].data = new_data;
                        strcat(messages[i - 1].data, buff);  // Append new message
                        messages[i - 1].size = new_size - 1;
                    } 
                    else 
                    {
                        perror("MEMORY ALLOCATION FAILED");
                        exit(EXIT_FAILURE);
                    }

                    send(client_fd, "MESSAGE RECEIVED", 16, 0);
                }
            }
        }
    }

    // Print all stored messages at once
    printf("\n=== ALL CLIENT MESSAGES ===\n");
    for (int i = 0; i < MAX; i++) 
    {
        if (messages[i].data) 
        {
            printf("%s\n", messages[i].data);
            free(messages[i].data);  // Free allocated memory
        }
    }
    printf("\n");
    close(server_fd);
    return 0;
}
