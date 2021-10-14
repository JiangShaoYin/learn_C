#include"func.h"

typedef struct{
	long mtype;
	char buf[80];
}MSG;

int main(){
	MSG msg={0};
	msg.mtype=1;
	if(!fork()){
	bzero(&msg,sizeof(msg));
	int msgid=msgget(123,IPC_CREAT|0600);
	msgrcv(msgid,&msg,sizeof(msg.buf),1,0);
	puts(msg.buf);
	return 0;
	}
	else{
	int msgid=msgget(123,IPC_CREAT|0600);
	strcpy(msg.buf,"hello");
	msgsnd(msgid,&msg,sizeof(msg.buf),0);
	wait(NULL);
	msgctl(msgid,IPC_RMID,NULL);
	return 0;
	
	}




}
