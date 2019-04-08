#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

int main()
{
    int fd[2];
    pipe(fd);//fd[0]是读，fd[1]是写
    while(1){
    	    if(fork() != 0)
    {
        close(fd[0]);
        write(fd[1],"helloworld",10);
        printf("parent have writen msg:helloworld\n");
    }
    else
    {
        close(fd[1]);
        char buf[128] = {0};
        read(fd[0],buf,127);
        printf("child have receive msg:");
        printf("%s\n",buf);
    }
    sleep(3);
    }
    return 0;
}