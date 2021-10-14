#include"func.h"

int main(){
	pid_t pid=fork();
	if(pid==0){
		int sid=setsid();	
		chdir("/");
		umask(0);
		for(int i=0;i<3;i++)
				close(i);
		int fd=open("/tmp/file",O_RDWR|O_CREAT,0666);
		printf("sid=%d\n",sid);
		while(1){
		write(fd,"I have sleep 3 second\n",27);		
		sleep(3);
		}

	}else{
		exit(0);	
			}

return 0;
}
