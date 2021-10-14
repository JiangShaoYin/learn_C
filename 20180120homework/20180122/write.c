#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int args,char**argv){
	if(args!=2){
		printf("args error\n");
		return -1;
	}
int	fd=open(argv[1],O_WRONLY);

	if(fd==-1){
	perror("open");
	return -1;	
	}
	printf("i am ready to write:\n");
	char buf[128]={0};
	int ret;
	while(1){
	memset(buf,0,sizeof(buf));
	ret=read(0,buf,sizeof(buf));
	if(ret>0)
	{
		write(fd,buf,strlen(buf)-1);
	}else{
		printf("byebye\n");
		close(fd);
		break;
	}
	}
return 0;
}
