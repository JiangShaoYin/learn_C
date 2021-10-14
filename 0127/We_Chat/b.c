#include"func.h"
#define tuichu 3

pid_t pid_ot,pid_my;
int fdr,fdw;

int msgid;

char buf[3076];

typedef struct{
	int flag;
	int who;
	char xiaoxi[3072];
}MSG;

typedef struct msg_buf{
	long mtype;
	MSG p;
}MSG_BUF;

MSG_BUF msgbuf={0};


void dui_hua_kuang(char *buf,int shen_fen){
	MSG tmp={0};
			if(shen_fen==1){
					tmp.who=1; 	//1是自己说的话
				}else{
					tmp.who=2;
				}
		tmp.flag=1;	
			if(shen_fen==tuichu)
				tmp.flag=2;	
			puts("line 35");
			memcpy(tmp.xiaoxi,buf,strlen(buf)-1);
			memcpy(&msgbuf.p,&tmp,sizeof(tmp));
	int ret=msgsnd(msgid,&msgbuf,sizeof(MSG),0);
		if(ret==-1)
				printf("line 43\n");

//	puts(buf);
//	puts(p.xiaoxi);

} 
void handler(int signum){
	close(fdr);
	close(fdw);
	kill(pid_ot,SIGINT);
	msgbuf.p.flag=2;
	dui_hua_kuang(buf,tuichu);//将buf里的东西发往对话框，对话框里的消息类型是退出
	exit(0);
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
	msgid=msgget(123,IPC_CREAT|0600);
	if(msgid==-1) perror("line 61");
		msgbuf.mtype=1;	
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
//						system("clear");
				int ret_w=write(fdw,buf,sizeof(buf));
//					printf("ret_w=%d\n",ret_w);
				}
				if(FD_ISSET(fdr,&fdset)){
					bzero(buf,sizeof(buf));
					read(fdr,buf,sizeof(buf));
	//				puts(buf);
						dui_hua_kuang(buf,ot);
				}		
		}
	}
}
