#include"func.h"

void clean(void *p){
	printf("i am clean\n");
	free(p);
	
}

void *thread_func(void*p){
	printf("child:p=%ld\n",(long)p);
	void *tmp=malloc(8);
	pthread_cleanup_push(clean,tmp);
	char buf[100];
	read(0,buf,100);
	pthread_exit((void*)2);
	pthread_cleanup_pop(0);


}

int main(){
	pthread_t thread;
	void*i;
	pthread_create(&thread,NULL,thread_func,(void*)1);
	sleep(1);
	pthread_cancel(thread);

	pthread_join(thread,&i);



}
