#include"func.h"
#define N 10000000

int main(){
	int shmid=shmget(123,4096,IPC_CREAT|0600);
	int *p=(int *)shmat(shmid,NULL,0);
		p[0]=0;
	int pid=fork();
	int i;
	time_t start,end;
	if(pid==0){
		for(i=0;i<N;i++)
			p[0]++;	
	}else{
		start=time(NULL);
		for(i=0;i<N;i++)
			p[0]++;	
		wait(NULL);
		end=time(NULL);
		printf("total=%d,time=%ld",p[0],end-start);		
	}
	return 0;



}
