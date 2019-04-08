#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/types.h>

sem_t* ts_r = NULL;//1000
sem_t* ts_s = NULL;//0
sem_t* a = NULL;//1
sem_t* b = NULL;//1
int ts_rr = 1000;
int ts_ss = 0;

void* worker1(void *arg){
while(1){
	sem_wait(ts_r);
	//sem_wait(a);
	ts_rr--;
	//sem_post(a);
	printf("after sell tickets remaining : %d\n",ts_rr);
	//sem_wait(b);
	ts_ss++;
	//sem_post(b);
	printf("after sell tickets sold : %d\n",ts_ss);
	sem_post(ts_s);
	sleep(0.54);
}


}
void* worker2(void *arg){
while(1){
	sem_wait(ts_s);
	//sem_wait(a);
	int temp = ts_rr;
	pthread_yield();
	temp++;
	pthread_yield();
	ts_rr = temp;
	//sem_post(a);
	printf("after return tickets remaining : %d\n",ts_rr);
	//sem_wait(b);
	ts_ss--;
	printf("after return tickets sold : %d\n",ts_ss);
	//sem_post(b);
	sem_post(ts_r);
	sleep(0.56);
}


}

int main(){

	ts_r = sem_open("tsr", O_CREAT, 0666, 1000);
	ts_s = sem_open("tss", O_CREAT, 0666, 0);
	a = sem_open("aa", O_CREAT, 0666, 1);
	b = sem_open("bb", O_CREAT, 0666, 1);
	pthread_t p1,p2;
	pthread_create(&p1,NULL,worker1,NULL);
	pthread_create(&p2,NULL,worker2,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	sem_close(ts_r);
	sem_close(ts_s);
	sem_close(a);
	sem_close(b);
	sem_unlink("tsr");
	sem_unlink("tss");
	sem_unlink("aa");
	sem_unlink("bb");
	return 0;

}


