#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int JudgeArgs(int ,int);
int main(int args,char *argv[])
{
	if(JudgeArgs(args,2))
		return -1;
	int fd;
	fd=open(argv[1],O_RDWR);
	if(-1==fd)
	{
		perror("fd");
		return -1;
	}
	char *p;
	p=(char*)mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if((char*)-1==p)
	{
		perror("mmap");
		return -1;
	}
	char *str="world";
	int len=strlen(str);
	for(int i=0;i<len;i++)
		p[i]=str[i];
	int ret=munmap(p,1024);
	if(-1==ret)
	{
		perror("mumap");
		return -1;
	}
	return 0;
}
