#include"func.h"

void *thread_func(void*p){
	printf("child:p=%ld\n",(long)p);
	return (void*)2;


}

int main(){
	pthread_t thread;
	void*i;
	pthread_create(&thread,NULL,thread_func,(void*)1);
	pthread_join(thread,&i);
	printf("main:%ld",(long)i);



}
