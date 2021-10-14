#include"func.h"

int main(){
	pid_t pid=fork();
	int status;
	if(pid==0){
		printf("son\n");
		exit(10);	
	}else{
		pid_t pid=wait(&status);
		int	a=WIFEXITED(status);
		if(a){
		int exitinfo=WEXITSTATUS(status);
		printf("son return:%d",exitinfo);
			}
	}
return 0;
}
