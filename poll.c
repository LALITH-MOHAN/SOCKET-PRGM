#include<stdio.h>
#include<poll.h>

int main()
{
    struct pollfd pfds[1];
    pfds[0].events=POLLIN;
    pfds[0].fd=0; //stdin
    printf("ENTER");
    int num=poll(pfds,1,-1); // wait indefinitly 
    if(num==0)
    {
        printf("POLL TIMED OUT\n");
    }
    else
    {
        int k=pfds[0].revents&POLLIN;
        if(k)
        {
            printf("FD:%d IS READY OT READ\n",pfds[0].fd);
            printf("%d\n",pfds[0].revents);
        }
        else
        {
            printf("UNEXPECTED EVENT OCCURED : %d \n",pfds[0].revents);
        }
    }
}