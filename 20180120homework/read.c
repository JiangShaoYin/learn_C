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

int	fd=open(argv[1],O_RDONLY);

	if(fd==-1){
		perror("open");
		return -1;	
		}
	printf("i am ready to read:\n");

	char buf[100]={0};
	int ret;
	while(1){

	memset(buf,0,sizeof(buf));
	ret=read(fd,buf,sizeof(buf));
//	if(ret==0)
//	{ perror("read");
//	  return -1;
//	}
		printf("%s\n",buf);
	}
return 0;
}
