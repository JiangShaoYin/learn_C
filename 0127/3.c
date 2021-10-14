#include"func.h"
void sig(int signum){}

int main(){
	signal(SIGALRM,sig);
	alarm(3);
	pause();
	printf("okay\n");
	return 0;


}
