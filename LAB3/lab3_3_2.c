#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

sem_t* buf_space = NULL;
sem_t* buf_data = NULL;
char buf[10];

void*worker1(void *arg){
   int i = 0; 
	while(1){
		//sem_wait(buf_space);
		scanf("%c",&buf[i]);
		i = (i+1)%10;
		//sem_post(buf_data);
	}
    return NULL;
}

void*worker2(void *arg){
	int j = 0; 
    while(1){
		//sem_wait(buf_data);
		sleep(1);
		if (buf[j%10]!='\n') {
			printf("output:%c\n",buf[j%10]);//吃掉回车
		}
		j=(j+1)%10;
		//sem_post(buf_space);
	}
    return NULL;
}

int main(int argc, char *argv[]){
	buf_space = sem_open("mySemName_1", O_CREAT, 0666, 10);
	buf_data = sem_open("mySemName_2", O_CREAT, 0666, 0);
    pthread_t p1,p2;
    printf("Input str length must less than 10.\n");
    pthread_create(&p1,NULL,worker1,NULL);
    pthread_create(&p2,NULL,worker2,NULL);
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
	sem_close(buf_space);
	sem_close(buf_data);
	sem_unlink("mySemName_1");
	sem_unlink("mySemName_2");
    return 0;
}
