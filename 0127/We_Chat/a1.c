#include"func.h"


struct sembuf sopp={1,-1,SEM_UNDO},sopv={1,1,SEM_UNDO};
int shmid,semid;
typedef struct{
	int flag;
	int who;
	char xiaoxi[3072];
}MSG;

int main(){
	char buf[3072];
	shmid=shmget(123,4096,IPC_CREAT|0600);
	MSG *p=(MSG*)shmat(shmid,NULL,0);
  		semid=semget(123,1,IPC_CREAT|0600);
        semctl(semid,0,SETVAL,1);
	while(1){
		if(p->flag==1){
        semop(semid,&sopp,1);
		memcpy(buf,p->xiaoxi,strlen(p->xiaoxi));
//		puts(p->xiaoxi);
//		puts(buf);
			if(p->who==1){
				printf("my session:%s\n",buf);
			}
			if(p->who==2){
				printf("%60s:friend's session\n",buf);
			}
			p->flag=0;
			bzero(p->xiaoxi,sizeof(p->xiaoxi));
			bzero(buf,sizeof(buf));
		semop(semid,&sopv,1);
		}
		if(p->flag==2){ //直接去共享内存看flag，如果是2，表明对话程序要退出
			shmctl(shmid,IPC_RMID,NULL);
			semctl(semid,0,IPC_RMID);
			exit(0);
		}
	}
}

