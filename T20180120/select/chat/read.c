#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//管道的读端
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int fd;
	fd=open(argv[1],O_RDONLY);//必须O_RDONLY
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	printf("I am O_RDONLY\n");
	char buf[128]={0};
	while(1)
	{
		memset(buf,0,sizeof(buf));
		read(fd,buf,sizeof(buf));//如果管道内没有数据，read会阻塞
		printf("%s\n",buf);
	}
	return 0;
}
