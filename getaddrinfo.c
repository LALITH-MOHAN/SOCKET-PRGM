#include<stdio.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdlib.h>
int main()
{
    struct addrinfo hints,*res;
    char ip[INET6_ADDRSTRLEN];
    hints.ai_flags=AI_PASSIVE;
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    if(getaddrinfo("google.com",NULL,&hints,&res)==0)
    {
        void *addr=&((struct sockaddr_in*)res->ai_addr)->sin_addr;
        inet_ntop(res->ai_family,addr,ip,sizeof(ip));
        printf("GOOGLE IP: %s",ip);
        freeaddrinfo(res);
    }
    printf("\n");
    return 0;
}