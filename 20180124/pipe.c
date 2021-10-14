#include"func.h"

int main(){
	int fd[2];
	pipe(fd);
	pid_t pid=fork();
	if(pid==0){
		close(fd[0]);
		char arr[6]="hello";
		write(fd[1],arr,sizeof(arr));
		return 0;	
	}else{
		close(fd[1]);
		char brr[6]={0};
		read(fd[0],brr,sizeof(brr));
		printf("%s\n",brr);
		wait(NULL);
		return 0;
	}
}
