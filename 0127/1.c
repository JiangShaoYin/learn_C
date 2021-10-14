#include"func.h"

void sig(int signum,siginfo_t *pSigInfo,void *pReserved){
		printf("before sleep,i am %d\n",signum);
			sleep(3);
		sigset_t pend;
			sigemptyset(&pend);
			sigpending(&pend);
		if(sigismember(&pend,SIGQUIT))
				printf("3 is be blocked\n");
		else
				printf("3 was not in the blocked queue\n");
		printf("after sleep,i am %d\n",signum);
}


int main(){
	struct sigaction act={0};

	act.sa_flags=SA_SIGINFO|SA_NODEFER;
	act.sa_sigaction=sig;
		sigemptyset(&act.sa_mask);
		sigaddset(&act.sa_mask,SIGQUIT);

	sigaction(SIGINT,&act,NULL);
	sigaction(SIGQUIT,&act,NULL);
	while(1);

}
