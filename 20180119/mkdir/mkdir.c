include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int ret;
	char*p=NULL;
	char c;
	c=*p;
	ret=mkdir(argv[1],0777);
	if(-1==ret)
	{
		perror("mkdir");
		return -1;
	}
	return 0;
}

