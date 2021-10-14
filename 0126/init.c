#include"func.h"

int main(){
	int semid=semget(123,2,IPC_CREAT|0600);
	unsigned short arr[2]={0,10};
		semctl(semid,0,SETALL,arr);
   printf("empty is %d\n",semctl(semid,0,GETVAL));
   printf("full is %d\n",semctl(semid,1,GETVAL));
	
	return 0;
	
}
