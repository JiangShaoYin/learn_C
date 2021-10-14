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
	sleep(10);
	char *p="I am shuaige";
	int	ret=write(fd,p,strlen(p));
	printf("ret=%d\n",ret);
	while(1);
	return 0;
}
