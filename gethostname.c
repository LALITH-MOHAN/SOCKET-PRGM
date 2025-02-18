#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{
    char buff[100];
    if(gethostname(buff,sizeof(buff))<0)
    {
        printf("ERROR");
    }
    else
    printf("HOSTNAME: %s\n",buff);
}