#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("SOCKET CREATION FAILED");
        return 1;
    }
    printf("SERVER_FD: %d\n", server_fd);

    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("BINDING FAILED");
        return 1;
    }

    char buff[1024];
    while (1) {
        ssize_t recv_len = recvfrom(server_fd, buff, sizeof(buff) - 1, 0, 
                                    (struct sockaddr*)&client_addr, &client_len);
        if (recv_len > 0) {
            buff[recv_len] = '\0'; 
            printf("IP: %s, PORT: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            printf("MESSAGE: %s\n", buff);
            
            sendto(server_fd, "RECEIVED", 8, 0, (struct sockaddr*)&client_addr, client_len);
        }
    }

    close(server_fd);
    return 0;
}
