#include"func.h"

int main(){
	pid_t pid=fork();
	if(pid==0){
		printf("son\n");
	
	}else{
	
	printf("father\n");
	
		while(1);
	}
return 0;



}
