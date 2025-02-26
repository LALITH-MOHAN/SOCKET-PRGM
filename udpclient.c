#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0) {
        perror("SOCKET CREATION FAILED");
        return 1;
    }
    printf("CLIENT_FD: %d\n", client_fd);

    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char buff[] = "HELLO FROM CLIENT";
    sendto(client_fd, buff, strlen(buff), 0, (struct sockaddr*)&server_addr, server_len);

    char buff1[1024] = {0};
    ssize_t n = recvfrom(client_fd, buff1, sizeof(buff1) - 1, 0, (struct sockaddr*)&server_addr, &server_len);
    if (n > 0) {
        buff1[n] = '\0'; // Null-terminate received message
        printf("Server Response: %s\n", buff1);
    }

    close(client_fd);
    return 0;
}
