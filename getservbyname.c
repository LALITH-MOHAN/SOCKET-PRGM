#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<netdb.h>
int main()
{
    struct servent *serv;
    serv=getservbyname("telnet","tcp");
    if(serv==NULL)
    {
        printf("INVALID SERVICE\n");
        exit(EXIT_FAILURE);
    }
    printf("SERVICE NAME:%s\n",serv->s_name);
    printf("PORT NO:%d\n",ntohs(serv->s_port));
    printf("PROTOCOL:%s\n",serv->s_proto);
}