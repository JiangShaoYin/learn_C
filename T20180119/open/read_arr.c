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
	fd=open(argv[1],O_RDWR|O_CREAT,0666);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	int a[5]={0};
	int ret;
	ret=read(fd,a,sizeof(a));
	if(-1==ret)
	{
		perror("read");
		return -1;
	}
	printf("%d %d %d\n",a[0],a[1],a[2]);
	close(fd);
	return 0;
}
