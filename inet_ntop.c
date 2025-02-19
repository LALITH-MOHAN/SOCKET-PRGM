#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>

int main()
{
    char buff[INET_ADDRSTRLEN];
    struct in_addr addr;
    addr.s_addr=inet_addr("127.0.0.1"); //converts human readable to binary 
    inet_ntop(AF_INET,&addr,buff,sizeof(buff)); //convert binary to human readable
    printf("IP ADDRESS IS : %s\n",buff);
}