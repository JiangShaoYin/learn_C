#include"func.h"

void handler(int sig_num){		
	printf("before sleep:sig_num is %d\n",sig_num);
	sleep(3);
	printf("after sleep:sig_num is %d\n",sig_num);
}

int main(){
	signal(SIGINT,handler);
	signal(SIGQUIT,handler);

	while(1);
//	sleep(10);
	return 0;

}
