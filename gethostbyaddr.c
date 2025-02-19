#include<stdio.h>
#include<arpa/inet.h>
#include<netdb.h>

int main()
{
    struct in_addr addr;
    struct hostent *host;
    addr.s_addr=inet_addr("8.8.8.8");
    host=gethostbyaddr(&addr,sizeof(addr),AF_INET);
    if(host==NULL)
    {
        printf("NO HOST FOUND");
        return 1;
    }
    else{
        printf("HOST NAME:%s",host->h_name);
         for(char **alias=host->h_aliases;*alias!=NULL;alias++)
         {
            printf("ALIAS: %s",*alias);
         }
    }
}