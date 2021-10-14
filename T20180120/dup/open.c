#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int fd;
	fd=open(argv[1],O_RDWR);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	int fd1;
	fd1=fd;
	close(fd);
	printf("fd=%d,fd1=%d\n",fd,fd1);	
	char buf[128]={0};
	int ret=read(fd1,buf,sizeof(buf));
	printf("ret=%d,buf=%s\n",ret,buf);
	return 0;
}
