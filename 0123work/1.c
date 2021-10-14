#include"func.h"

int main(){
	pid_t pid=fork();
	if(pid==0){
		printf("son pid:%d\n",getpid());
		while(1);
	
	}else{
	
	printf("father pid:%d\n",getpid());
		while(1);
	
	}
return 0;



}
