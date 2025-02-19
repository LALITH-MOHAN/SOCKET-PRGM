#include<arpa/inet.h>
#include<stdio.h>
#include<netdb.h>

int main()
{
    struct hostent *host;
    char buff[]="google.com";
    host=gethostbyname(buff);
    if(host==NULL)
    {
        printf("NO HOST FOUND");
        return 1;
    }
    else
    {
        printf("HOST NAME: %s\n",host->h_name);
        char **adrr_len=host->h_addr_list;
        while(*adrr_len!=NULL)
        {
            printf("IP ADDRESS: %s\n",inet_ntoa(*(struct in_addr *)*adrr_len));
            adrr_len++;
        }
        printf("\n");
    }
    
}