#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int sock=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8080);
    addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sock,(struct sockaddr*)&addr,sizeof(addr))<0)
    {
        perror("BINDING FAILED\n");
        exit(EXIT_FAILURE);
    }
    if(listen(sock,1)<0)
    {
        perror("LISTENING FAILED");
        exit(EXIT_FAILURE);
    }
    sleep(10);
    printf("SOCKET_FD: %d\n",sock);
    close(sock);
}