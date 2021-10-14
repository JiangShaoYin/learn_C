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
	printf("\n");
	int fd1=dup(fd);
	printf("fd1=%d fd==%d\n",fd1,fd);
	
	close(fd);
	char buf[100];
	int ret=read(fd1,buf,100);
//	printf()
	if(ret==-1)
		perror("read");
	puts(buf);
}
