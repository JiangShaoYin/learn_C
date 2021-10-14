#include"func.h"

int main(){
	int shmid=shmget(123,4096,IPC_CREAT|0666);
		char*p;
		p=(char*)shmat(shmid,NULL,0);
		if((char*)-1==p){
			perror("shmat");
			return -1;
		}
while(1)
		printf("%s\n",p);
	return 0;
}
