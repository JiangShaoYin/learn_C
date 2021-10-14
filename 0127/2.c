#include"func.h"

int main(){
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask,SIGINT);
		sigprocmask(SIG_BLOCK,&mask,NULL);
			sleep(10);
				sigset_t pend;
				sigemptyset(&pend);
				sigpending(&pend);
					if(sigismember(&pend,SIGINT))
						printf("2 was blocked\n");
					else
						printf("2 was not blocked\n");
		sigprocmask(SIG_UNBLOCK,&mask,NULL);
		
	return 0;
	
}
