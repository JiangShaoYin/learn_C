#include"func.h"


int shmid,semid;
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

int main(){
	char buf[3072];
int	msgid=msgget(123,IPC_CREAT|0600);
	msgbuf.mtype=1;
	while(1){
	msgrcv(msgid,&msgbuf,sizeof(MSG),1,0);	
		if(msgbuf.p.flag==1){//flag=1是显示对话消息，flag=2是处理退出
			if(msgbuf.p.who==1){
				printf("my session:%s\n",msgbuf.p.xiaoxi);
			}
			if(msgbuf.p.who==2){
				printf("%60s:friend's session\n",msgbuf.p.xiaoxi);
			}
		}
		if(msgbuf.p.flag==2){
			msgctl(msgid,IPC_RMID,NULL);
			exit(0);
		}
	}
}

