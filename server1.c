#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main()
{
    int server_fd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr,client_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("BINDING FAILED..\n");
        exit(EXIT_FAILURE);
    }
    if(listen(server_fd,1)<0)
    {
        printf("LISTENING FAILED");
        exit(EXIT_FAILURE);
    }
    printf("LISTENING...\n");
    socklen_t client_len=sizeof(client_addr);
    int newsocket=accept(server_fd,(struct sockaddr*)&client_addr,&client_len);
    if(newsocket<0)
    {
        printf("ACCEPT FAILED\n");
        exit(EXIT_FAILURE);
    }
    char buff[1024];
    int len=recv(newsocket,buff,1024,0);
    buff[len]='\0';
    printf("MESSAGE FROM CLIENT: %s",buff);
    char buff1[]="CLIENT MESSAGE RECEVIED";
    send(newsocket,buff1,strlen(buff1),0);
    printf("\n");
}