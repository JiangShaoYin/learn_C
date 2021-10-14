#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//管道的写端
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int fd;
	fd=open(argv[1],O_WRONLY);//必须O_WRONLY
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	printf("I am pipe O_WRONLY\n");
	char buf[128];

	int ret;
	while(1)
	{
		memset(buf,0,sizeof(buf));
		ret=read(0,buf,sizeof(buf));
		write(fd,buf,strlen(buf)-1);
	}
	return 0;
}
