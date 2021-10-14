#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
//写一个整型数组到磁盘
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int fd;
	fd=open(argv[1],O_RDWR|O_CREAT,0666);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	int a[5]={1,2,3,4,5};
	int ret;
	ret=write(fd,a,sizeof(a));
	if(-1==ret)
	{
		perror("write");
		return -1;
	}
	printf("ret=%d",ret);
	close(fd);
	return 0;
}
