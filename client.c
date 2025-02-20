#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>

int main()
{
    int client_fd=socket(AF_INET,SOCK_STREAM,0);
    printf("FD:%d\n",client_fd);
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
    if(connect(client_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("NOT CONNECTED..");
        return -1;
    }
    int addr_len=sizeof(server_addr);
    if(getpeername(client_fd,(struct sockaddr*)&server_addr,(socklen_t*)&addr_len)==0)
    {
     printf("IP ADDRESS:%s\nport:%d\n",inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port));
    }
    char buff[]="HELLO FROM CLIENT";
    send(client_fd,buff,sizeof(buff),0);
    char buff1[1024];
    recv(client_fd,buff1,sizeof(buff1),0);
    printf("SERVER MESSAGE:%s",buff1);
}