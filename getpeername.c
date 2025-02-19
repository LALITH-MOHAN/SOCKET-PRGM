#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() 
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);
    char ipstr[INET_ADDRSTRLEN];
    int port;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);
    
    printf("Waiting for a client...\n");

    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);
    printf("Client connected.\n");

    getpeername(client_fd, (struct sockaddr*)&client_addr, &addr_size);
    inet_ntop(AF_INET, &client_addr.sin_addr, ipstr, sizeof(ipstr));
    port = ntohs(client_addr.sin_port);

    printf("Client IP: %s\n", ipstr);
    printf("Client Port: %d\n", port);

    close(client_fd);
    close(server_fd);
    return 0;
}
