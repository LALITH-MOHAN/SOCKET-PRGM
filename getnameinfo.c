#include<stdio.h>
#include<arpa/inet.h>
#include<netdb.h>

int main()
{
    struct sockaddr_in addr;
    char buff[1000];
    addr.sin_family=AF_INET;
    inet_pton(AF_INET,"8.8.8.8",&addr.sin_addr);
    if(getnameinfo((struct sockaddr*)&addr,sizeof(addr),buff,sizeof(buff),NULL,0,0)==0)
    {
        printf("HOSTNAME: %s\n",buff);
    }
}