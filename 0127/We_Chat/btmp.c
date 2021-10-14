#include"func.h"

pid_t pid_ot,pid_my;
int fdr,fdw;
struct sembuf sopp={1,-1,SEM_UNDO},sopv={1,1,SEM_UNDO};
int shmid,semid;
char buf[3076];

typedef struct{
	int flag;
	int who;
	char xiaoxi[3072];
}MSG;

MSG *p;

void handler(int signum){
	close(fdr);
	close(fdw);
	kill(pid_ot,SIGINT);
	p->flag=2;
	semctl(semid,0,IPC_RMID);
	exit(0);
}

void dui_hua_kuang(char *buf,int shen_fen){
	semop(semid,&sopp,1);
			if(shen_fen==1){
					p->who=1; 	//1是自己说的话
				}else{
					p->who=2;
				}
			p->flag=1;	//1是写入
			memcpy(p->xiaoxi,buf,strlen(buf)-1);
//	puts(buf);
//	puts(p->xiaoxi);
	semop(semid,&sopv,1);	

} 

int main(){
	int me=1,ot=2;
	fdw=open("./1",O_WRONLY);
	fdr=open("./2",O_RDONLY);
		pid_my=getpid();
	read(fdr,&pid_ot,sizeof(pid_t));
	write(fdw,&pid_my,sizeof(pid_t));
	printf("pid_a is %d\n",pid_my);
	printf("pid_b is %d\n",pid_ot);
	printf("b is ready:\n");
		shmid=shmget(1234,4096,IPC_CREAT|0600);
			p=(MSG*)shmat(shmid,NULL,0);
		semid=semget(1234,1,IPC_CREAT|0600);
		semctl(semid,0,SETVAL,1);
	while(1){
			signal(SIGINT,handler);
		fd_set fdset;
		FD_ZERO(&fdset);
		FD_SET(0,&fdset);
		FD_SET(fdr,&fdset);
		int ret=select(fdr+1,&fdset,NULL,NULL,NULL);
		int ret_read;
		if(ret>0){
				if(FD_ISSET(0,&fdset)){
					bzero(buf,sizeof(buf));
					ret_read=read(0,buf,sizeof(buf));
						dui_hua_kuang(buf,me);
						system("clear");
					write(fdw,buf,sizeof(buf));
				}
				if(FD_ISSET(fdr,&fdset)){
					bzero(buf,sizeof(buf));
					read(fdr,buf,sizeof(buf));
						dui_hua_kuang(buf,ot);
				}		
		}
	}
}
