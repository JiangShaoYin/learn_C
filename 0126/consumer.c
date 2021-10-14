#include"func.h"
//consumer
int main(){
	int semid=semget(123,2,0600);
	if(semid==-1){
		perror("semget");
	}
	struct sembuf sopp={0,-1,SEM_UNDO},sopv={1,1,SEM_UNDO};
	while(1){			//0号信号量为product，初始值为0
		printf("\nproduct is %d\n",semctl(semid,0,GETVAL));//号信号量为empty，初始值为10
		printf("empty is %d\n",semctl(semid,1,GETVAL));
			semop(semid,&sopp,1);
				printf("	product is %d\n",semctl(semid,0,GETVAL));
				printf("	empty is %d\n",semctl(semid,1,GETVAL));
				printf("	消费中...\n");
				sleep(2);
		int ret=semop(semid,&sopv,1);
			if(ret==-1)
					printf("v error\n");
		printf("product is %d\n",semctl(semid,0,GETVAL));//号信号量为empty，初始值为10
		printf("empty is %d\n",semctl(semid,1,GETVAL));
	}
}
