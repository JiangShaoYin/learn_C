#include"func.h"
#define N 10000000

int main(){
	int shmid=shmget(123,4096,IPC_CREAT|0600);
	int *p=(int *)shmat(shmid,NULL,0);
		p[0]=0;
	int semid=semget(123,1,IPC_CREAT|0600);
	int ret=semctl(semid,0,SETVAL,1);
		struct sembuf sopp={0};
		struct sembuf sopv={0};
		sopp.sem_op=-1;
		sopp.sem_flg=SEM_UNDO;
		sopv.sem_op=1;
		sopv.sem_flg=SEM_UNDO;
	int pid=fork();
	int i;
	time_t start,end;
	if(pid==0){
		for(i=0;i<N;i++){
		semop(semid,&sopp,1);
			p[0]++;	
		semop(semid,&sopv,1);}		
	}else{
		start=time(NULL);
		for(i=0;i<N;i++){
		semop(semid,&sopp,1);
			p[0]++;	
		semop(semid,&sopv,1);}
		wait(NULL);
		end=time(NULL);
		printf("total=%d,time=%ld",p[0],end-start);		
		semctl(semid,0,IPC_RMID);
		shmctl(shmid,IPC_RMID,NULL);
	}
	return 0;



}
