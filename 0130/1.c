#include"func.h"
typedef struct{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}data;

void *func(void *t){
	data *p=(data*)t;
	pthread_mutex_lock(&p->mutex);
		pthread_cond_wait(&p->cond,&p->mutex);
	pthread_mutex_unlock(&p->mutex);
	printf("i am son thread\n");
	pthread_exit(NULL);
}

int main(){
	data t;
	pthread_t thread;
	pthread_mutex_init(&t.mutex,NULL);
	pthread_cond_init(&t.cond,NULL);
		pthread_create(&thread,NULL,func,&t);
	sleep(1);
	pthread_cond_signal(&t.cond);
	pthread_join(thread,NULL);
	return 0;
}
