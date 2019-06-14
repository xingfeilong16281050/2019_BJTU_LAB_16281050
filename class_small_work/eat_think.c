#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/types.h>

//C:\Users\emrick\Desktop\2019_BJTU_LAB_16281050\class_small_work\eat_think.c

sem_t* k1 = NULL;//筷子1
sem_t* k2 = NULL;//筷子2
sem_t* k3 = NULL;//筷子3
sem_t* k4 = NULL;//筷子4


void* worker1(void *arg)//哲学家1
{
while(1){
	sem_wait(k4);
    sem_wait(k1);
    printf("哲学家1在进餐");
    sleep(0.5);
    sem_post(k4);
    sem_post(k1);
    printf("哲学家1在思考");
    sleep(0.4);
}

void* worker2(void *arg)//哲学家2
{
while(1){
	sem_wait(k1);
    sem_wait(k2);
    printf("哲学家2在进餐");
    sleep(0.5);
    sem_post(k1);
    sem_post(k2);
    printf("哲学家2在思考");
    sleep(0.4);
}
void* worker3(void *arg)//哲学家3
{
while(1){
	sem_wait(k2);
    sem_wait(k3);
    printf("哲学家3在进餐");
    sleep(0.5);
    sem_post(k2);
    sem_post(k3);
    printf("哲学家3在思考");
    sleep(0.4);
}
void* worker4(void *arg)//哲学家4
{
while(1){
	sem_wait(k3);
    sem_wait(k4);
    printf("哲学家4在进餐");
    sleep(0.5);
    sem_post(k3);
    sem_post(k4);
    printf("哲学家4在思考");
    sleep(0.4);
}



int main(){

	k1 = sem_open("k1n", O_CREAT, 0666, 1);
    k2 = sem_open("k2n", O_CREAT, 0666, 1);
    k3 = sem_open("k3n", O_CREAT, 0666, 1);
    k4 = sem_open("k4n", O_CREAT, 0666, 1);
	pthread_t p1,p2,p3,p4;
	pthread_create(&p1,NULL,worker1,NULL);
	pthread_create(&p2,NULL,worker2,NULL);
    pthread_create(&p3,NULL,worker3,NULL);
    pthread_create(&p4,NULL,worker4,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
    pthread_join(p3,NULL);
    pthread_join(p4,NULL);
	sem_close(k1);
	sem_close(k2);
    sem_close(k3);
    sem_close(k4);
	sem_unlink("k1n");
	sem_unlink("k2n");
	sem_unlink("k3n");
	sem_unlink("k4n");
	return 0;
}


