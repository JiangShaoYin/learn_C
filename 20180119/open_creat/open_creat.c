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
puts(argv[1]);
printf("fd=%d\n",fd);
char buf[100]={0};
int ret=read(fd,buf,sizeof(buf));
printf("ret=%d %s",ret,buf);
char *a="jiang";
lseek(fd,0,SEEK_SET);
int ret_wr=write(fd,a,sizeof(a));
if(ret_wr==-1)
		perror("write");
printf("read is done\n");
return 0;
}
