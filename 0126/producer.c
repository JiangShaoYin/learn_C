#include"func.h"
//producer
int main(){
	int semid=semget(123,2,0600);
	struct sembuf sopp={1,-1,0},sopv={0,1,0};
	int i=10;
	while(i){			//0号信号量为product，初始值为0
		i--;
		printf("\nproduct is %d\n",semctl(semid,0,GETVAL));//号信号量为empty，初始值为10
		printf("empty is %d\n",semctl(semid,1,GETVAL));
			semop(semid,&sopp,1);
			printf("生产者...\n");
			
			semop(semid,&sopv,1);
		printf("product is %d\n",semctl(semid,0,GETVAL));//号信号量为empty，初始值为10
		printf("empty is %d\n",semctl(semid,1,GETVAL));	
	}
	return 0;
}
