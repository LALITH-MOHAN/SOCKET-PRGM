#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
   fd_set set;
   FD_ZERO(&set);
   int n=0;
   for(int i=0;i<64;i++)
   {
      FD_SET(n+10,&set);
      n=n+10;
   }
   for(int i=0;i<FD_SETSIZE;i++)
   {
     if(FD_ISSET(i,&set))
     {
        printf("%d ",i);
     }
   }
   printf("\n");
}