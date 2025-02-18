#include<stdio.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main()
{
    int newsocket=socket(AF_INET,SOCK_STREAM,0);
    fcntl(newsocket,F_SETFL,O_NONBLOCK); // non block socket
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8080);
    addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(newsocket,(struct sockaddr*)&addr,sizeof(addr))<0)
    {
        printf("BINDING FAILED..");
    }
    listen(newsocket,1);
    printf("LISTENING...\n");
    socklen_t client_len=sizeof(addr);
    int new=accept(newsocket,(struct sockaddr*)&addr,&client_len); // non accept
    if(new<0)
    {
        printf("NO ACCEPT\n");
    }
    else
    printf("ACCEPTED\n");
}