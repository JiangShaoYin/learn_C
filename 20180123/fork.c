#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	pid_t pid=fork();
if(pid==0){
	printf("son\n,slef pid:%d,father pid:%d\n",getpid(),getppid());
	sleep(60);
}
else{
	printf("father\n,slef pid:%d,son pid:%d\n",getpid(),pid);
	sleep(60);
}
	return 0;
}
