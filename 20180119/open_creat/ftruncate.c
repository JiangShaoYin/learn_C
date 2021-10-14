#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
int main(int args,char**argv){

int fd=open(argv[1],O_RDWR|O_CREAT,0666);
if(fd==-1){
		perror("open failed\n");
		exit(-1);
}
int ret=ftruncate(fd,1000);
	if(ret==-1)
		perror("ftruncate error");
	return 0;



}
