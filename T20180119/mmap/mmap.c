#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
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
	char *pstart;
	pstart=(char*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if((char*)-1==pstart)
	{
		perror("mmap");
		return -1;
	}
	pstart[0]='h';
	int ret=munmap(pstart,4096);
	if(-1==ret)
	{
		perror("munmap");
		return -1;
	}
	return 0;
}
