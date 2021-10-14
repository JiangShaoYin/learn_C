#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	pid_t pid;
	pid_t ppid;
	printf("pid=%d,ppid=%d\n",getpid(),getppid());
	return 0;


}
