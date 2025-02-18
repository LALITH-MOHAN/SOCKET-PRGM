#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
    int socket_fd;
    socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd<0)
    {
        printf("ERROR");
        exit(EXIT_FAILURE);
    }
    printf("SOCKET FD: %d\n",socket_fd);
}