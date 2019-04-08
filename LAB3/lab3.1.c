#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/types.h>

sem_t* A = NULL;
sem_t* B = NULL;
sem_t* C = NULL;



int main(int argc, char const *argv[])
{
	A = sem_open("A_name",O_CREAT,0666,1);
	B = sem_open("B_name",O_CREAT,0666,0);
	C = sem_open("C_name",O_CREAT,0666,0);
	int p1,p2,p3,p4;
	while((p1=fork())==-1);
	if(p1==0){
		while(1){
			sem_wait(A);
			printf("I am p1\n");
			sleep(1);
			sem_post(B);
		}		
		
	}
	while((p2=fork())==-1);
	if(p2==0){
		while(1){
			sem_wait(B);
			printf("I am p2\n");
			sleep(1);
			sem_post(C);
		}
	}
	while((p3=fork())==-1);
	if(!p3){
		while(1){
			sem_wait(B);
			printf("I am p3\n");
			sleep(1);
			sem_post(C);
		}
	}
	while((p4=fork())==-1);
	if(!p4){
		while(1){
			sem_wait(C);
			printf("I am p4\n");
			sleep(1);
			sem_post(A);
		}
	}
	return 0;
}
