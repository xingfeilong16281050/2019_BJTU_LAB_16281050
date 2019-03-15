#include<stdio.h>
#include<stdlib.h>

int int main(int argc, char const *argv[])
{
	int p,p11,p12,p111,p112;
	while((p=fork())==-1);
	if (!p)
	{
		printf("PID：%d,PPID:%d",getpid(),getppid());
		while((p11=fork())==-1);
		if (!p11)
		{
			printf("PID：%d,PPID:%d",getpid(),getppid());
			while((p111=fork())==-1);
			if (!p111)
			{
				printf("PID：%d,PPID:%d",getpid(),getppid());
				exit(0);
			}
			else
				wait(0);
			while((p112=fork())==-1);
			if (!p112)
			{
				printf("PID：%d,PPID:%d",getpid(),getppid());
				exit(0);
			}
			else
				wait(0);
			exit(0);
		}
		else
			wait(0);
		while((p12=fork())==-1);
		if (!p12)
		{
			printf("PID：%d,PPID:%d",getpid(),getppid());
			exit(0);
		}
		else
			wait(0);
		exit(0);
	}
	return 0;
}