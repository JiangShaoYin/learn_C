#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char**argv){

	int fd=open(argv[1],O_RDWR);
	write(fd,"hello",10);	
	printf("authority change\n");
	return 0;

}
