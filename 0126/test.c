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
	printf("i=%d\n",*(int*)msg.buf);
	return 0;
	}
	else{
	int msgid=msgget(123,IPC_CREAT|0600);
	int i=555;
	memcpy(msg.buf,&i,sizeof(i));
	msgsnd(msgid,&msg,sizeof(msg.buf),0);
	wait(NULL);
	msgctl(msgid,IPC_RMID,NULL);
	return 0;
	
	}




}
