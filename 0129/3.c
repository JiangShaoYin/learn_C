#include"func.h"
#define N 50000000
typedef struct{
	pthread_mutex_t mutex;
	int i;
}DATA;

void *thread_func(void*p){
	DATA *tmp=(DATA*)p;
		for(int j=0;j<N;j++){
			pthread_mutex_lock(&tmp->mutex);	
			tmp->i++;
			pthread_mutex_unlock(&tmp->mutex);
		}
	pthread_exit(NULL);
}

int main(){
	pthread_t thread;
	DATA t={0};
	pthread_mutex_init(&t.mutex,NULL);
	pthread_create(&thread,NULL,thread_func,(void*)&t);
		for(int j=0;j<N;j++){
			pthread_mutex_lock(&t.mutex);
				t.i++;
			pthread_mutex_unlock(&t.mutex);
		}
	pthread_join(thread,NULL);
	printf("main:%d",t.i);



}
