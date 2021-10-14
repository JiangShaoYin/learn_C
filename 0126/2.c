#include"func.h"

void handler(int sig_num){		
	printf("sig_num is %d\n",sig_num);
	exit(1);
}

int main(){
	signal(SIGINT,handler);
	while(1);
//	sleep(10);
	return 0;

}
