#include<stdio.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main(int args,char**argv){
	if(args!=2){
			printf("args error\n");
			return -1;
	}
	int fd=open(argv[1],O_RDWR|O_CREAT,0666);
	if(fd==-1){
	perror("open");
	return -1;
	}
	char*buf="hello";
	int ret=write(fd,buf,strlen(buf));
	if(ret==-1){
	perror("write");
	return -1;
	}
	char*p=(char*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(p==(char*)-1){
		perror("mmap");
		return -1;	
	}
	char*c="world";
	memcpy(p,c,strlen(c));
	int unmap=munmap(p,4096);
close(fd);

}
