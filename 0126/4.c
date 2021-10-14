#include"func.h"

void sig(int signum,siginfo_t *pSigInfo,void *pReserved){
		printf("before sleep,i am %d\n",signum);
			sleep(3);
		printf("after sleep,i am %d\n",signum);
}


int main(){
	struct sigaction act={0};

	act.sa_flags=SA_SIGINFO|SA_NODEFER;
	act.sa_sigaction=sig;

	sigaction(SIGINT,&act,NULL);
	while(1);

}
